#include "common.h"
#include <iostream>
#include <queue>

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());
  double Q[10000] = {0.0};

  double lambda, miu, DS;
  int C;
  std::cout << "lambda: ";
  std::cin >> lambda;
  std::cout << "miu: ";
  std::cin >> miu;
  std::cout << "DS: ";
  std::cin >> DS;
  std::cout << "C: ";
  std::cin >> C;

  double STS = 0.0;
  double CT = 0.0;
  double CR = 0.0;
  double ceas = 0.0;
  int n = 1;
  Q[1] = ceas;

  double Tp = gen_exp(miu, gen);
  double Tsu = gen_exp(lambda, gen);

  while (ceas < DS) {
    if (n == 0) {
      ceas += Tsu;
      n = 1;
      Q[1] = ceas;
      Tp = gen_exp(miu, gen);
      Tsu = gen_exp(lambda, gen);
    } else if (n > 0 && Tp <= Tsu) {
      ceas += Tp;
      Tsu -= Tp;

      STS += ceas - Q[1];
      n--;
      CT++;

      if (n > 0) {
        for (int i = 1; i < n; ++i) {
          Q[i - 1] = Q[i];
        }
        Tp = gen_exp(miu, gen);
      }
    } else if (n > 0 && Tsu < Tp) {
      ceas += Tsu;
      Tp -= Tsu;

      if (n == C) {
        CR++;
      } else {
        Q[n] = ceas;
      }
      Tsu = gen_exp(lambda, gen);
    }
  }

  std::cout << "TSm = " << STS / CT << '\n';
  std::cout << "Pcr = " << CR / (CT + CR + n) * 100 << "%\n";
}