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

constexpr int qsize = 1000000;
double Q[4][qsize] = {0};
int main() {
  std::random_device rd;
  std::mt19937 gen(rd());

  int DS;
  std::cout << "DS = ";
  std::cin >> DS;

  double STR[4] = {0};
  double CT[4] = {0};
  double Tp[4] = {0};
  double ceas = 0;
  int n[4] = {0};
  int c = 0;
  double lambda[4] = {0, 0.5, 0.1, 0.03};
  double Dis[4] = {0, gen_exp(lambda[1], gen), gen_exp(lambda[2], gen),
                   gen_exp(lambda[3], gen)};

  double Tsu;
  int k = 1;
  Tsu = Dis[1];
  k = 1;
  if (Dis[2] < Tsu) {
    k = 2;
    Tsu = Dis[2];
  }
  if (Dis[3] < Tsu) {
    k = 3;
    Tsu = Dis[3];
  }

  Dis[1] -= Tsu;
  Dis[2] -= Tsu;
  Dis[3] -= Tsu;

  while (ceas < DS) {
    if (c == 0) {
      ceas += Tsu;
      n[k] = 1;
      Q[k][1] = ceas;
      c = k;
      Tp[c] = genTp(c, gen);

      Dis[k] = gen_exp(k, gen);

      Tsu = Dis[1];
      k = 1;
      if (Dis[2] < Tsu) {
        k = 2;
        Tsu = Dis[2];
      }
      if (Dis[3] < Tsu) {
        k = 3;
        Tsu = Dis[3];
      }

      Dis[1] -= Tsu;
      Dis[2] -= Tsu;
      Dis[3] -= Tsu;
    } else if (c > 0 && Tp[c] <= Tsu) {
      ceas += Tp[c];
      Tsu -= Tp[c];

      STR[c] += ceas - Q[c][1];
      n[c]--;
      CT[c]++;
      Tp[c] = 0;

      if (n[c] > 0) {
        for (int i = 1; i < qsize; ++i) {
          Q[c][i - 1] = Q[c][i];
        }
      }

      if (n[1] > 0) {
        c = 1;
      } else if (n[2] > 0) {
        c = 2;
      } else if (n[3] > 0) {
        c = 3;
      }

      if (c > 0 && Tp[c] == 0) {
        Tp[c] = genTp(c, gen);
      }
    } else if (c > 0 && Tsu < Tp[c]) {
      ceas += Tsu;
      Tp[c] -= Tsu;

      n[k]++;
      Q[k][n[k]] = ceas;

      if (k < c) {
        c = k;
        Tp[c] = genTp(c, gen);
      }

      Dis[k] = gen_exp(lambda[k], gen);
      Tsu = Dis[1];
      k = 1;
      if (Dis[2] < Tsu) {
        k = 2;
        Tsu = Dis[2];
      }
      if (Dis[3] < Tsu) {
        k = 3;
        Tsu = Dis[3];
      }

      Dis[1] -= Tsu;
      Dis[2] -= Tsu;
      Dis[3] -= Tsu;
    }
  }

  std::cout << "TR1 = " << STR[1] / CT[1] << '\n';
  std::cout << "TR2 = " << STR[2] / CT[2] << '\n';
  std::cout << "TR3 = " << STR[3] / CT[3] << '\n';

  std::cout << "TR1m = " << (STR[1]) / (CT[1]) << '\n';
  std::cout << "TR2m = " << (STR[1] + STR[2]) / (CT[1] + CT[2]) << '\n';
  std::cout << "TR3m = " << (STR[1] + STR[2] + STR[3]) / (CT[1] + CT[2] + CT[3]) << '\n';
}