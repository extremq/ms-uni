#include "common.h"
#include <iostream>

double genTp(int k, std::mt19937 &gen) {
  if (k == 1) {
    return gen_gauss(0.5, 0.05);
  }
  if (k == 2) {
    return gen_exp(1.0 / 2, gen);
  }
  if (k == 3) {
    return gen_exp(1.0 / 5, gen);
  }

  return 0;
}
constexpr int qsize = 10000;
int main() {
  std::random_device rd;
  std::mt19937 gen(rd());
  
  double lambda, miu;
  double C, DS, ceas = 0, STR = 0, CT = 0, Tsu;
  int n = 1, k = 1;
  struct coada {
    double MS = 0, Tp = 0;
  };
  coada Q[qsize];
  Q[1].MS = ceas;
  Q[1].Tp = genTp(k, gen);
  Tsu = gen_exp(lambda, gen);

  double ca;
  if (Q[1].Tp < C) {
    ca = Q[1].Tp;
  } else {
    ca = C;
  }
  Q[1].Tp -= ca;

  while (ceas < DS) {
    if (n == 0) {
      ceas += Tsu;
      n = 1;
      Q[n].MS = ceas;
      Q[n].Tp = genTp(k, gen);

      if (Q[1].Tp < C) {
        ca = Q[1].Tp;
      } else {
        ca = C;
      }
      Q[1].Tp -= ca;

      Tsu = gen_exp(lambda, gen);
    }
    else if (n > 0 && ca <= Tsu) {
      ceas += ca;
      Tsu -= ca;

      if (Q[1].Tp == 0) {
        n--, CT++;
        STR+=ceas - Q[1].MS;
      }
      else if (Q[1].Tp > 0) {
        Q[n+1]=Q[1];
      }

      if (n > 0) {
        for (int i = 1; i < qsize; ++i) {
          Q[i - 1] = Q[i];
        }
      }
    }
    else if (n > 0 && Tsu < ca) {
      ceas += Tsu;
      ca -= Tsu;

      n++;
      Q[n].MS = ceas;
      Q[n].Tp = genTp(k, gen);

      Tsu = gen_exp(lambda, gen);
    }
  }
  std::cout << "TRm = " << STR/CT <<'\n';
}