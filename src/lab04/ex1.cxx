#include "common.h"
#include <iostream>

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());

  double lambda, miu, NS;
  std::cout << "lambda: ";
  std::cin >> lambda;
  std::cout << "miu: ";
  std::cin >> miu;
  std::cout << "NS: ";
  std::cin >> NS;

  double STP, STS, STL;
  STP = STS = STL = 0.0;

  double Tp = gen_exp(miu, gen);
  STP += Tp;

  double MS = 0.0;
  double MT = Tp;

  for (int i = 0; i < NS; ++i) {
    STS += MT - MS;
    MS += gen_exp(lambda, gen);

    Tp = gen_exp(miu, gen);
    STP += Tp;

    if (MS > MT) {
      STL += MS - MT;
      MT = MS + Tp;
    } else {
      MT += Tp;
    }
  }

  std::cout << "TSm = " << STS / NS << '\n';
  std::cout << "O = " << STP / (STP + STL) * 100 << "%\n";
}