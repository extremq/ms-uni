#include "common.h"
#include <iostream>

double genTp(int k, std::mt19937 &gen) {
  if (k == 0) {
    return gen_gauss(0.5, 0.05);
  }
  if (k == 1) {
    return gen_exp(1.0 / 2, gen);
  }
  if (k == 2) {
    return gen_exp(1.0 / 5, gen);
  }

  return 0;
}

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());

  int NS;
  std::cout << "NS = ";
  std::cin >> NS;
  double STR[3] = {0};
  int CT[3] = {0};
  int j, i = 0;

  double Ta = 0;
  int k = 0;
  double lambda[3] = {0.5, 0.1, 0.03};

  double P[3] = {0};
  auto l = lambda[0] + lambda[1] + lambda[2];
  P[0] = lambda[0] / l;
  P[1] = lambda[1] / l;
  P[2] = lambda[2] / l;
  
  std::uniform_real_distribution<> dist(0.0, 1.0); 
  while (i <= NS) {

    double Tp = genTp(k, gen);

    STR[k] += Ta + Tp;
    CT[k]++;

    double dis = gen_exp(l, gen);
    
    auto u = dist(gen);
    k = 0;
    if (u > P[0])
      k = 1;
    if (u > P[0] + P[1])
      k = 2;

    if (dis < Ta + Tp) {
      Ta = Ta + Tp - dis;
    } else {
      Ta = 0;
    }

    ++i;
  }

  std::cout << "TR0 = " << STR[0]/CT[0] << '\n';
  std::cout << "TR1 = " << STR[1]/CT[1] << '\n';
  std::cout << "TR2 = " << STR[2]/CT[2] << '\n';

  std::cout << "TR = " << (STR[0] + STR[1] + STR[2]) / NS << '\n';
}