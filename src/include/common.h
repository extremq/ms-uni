#include <random>

double gen_exp(double lambda, std::mt19937& gen) {
  std::uniform_real_distribution<> dis(0.0, 1.0);

  return -1 / lambda * log(1 - dis(gen));
}

double gen_gauss(double medie, double sigma) {
  double sum = 0;
  int i;
  for (i = 1; i <= 12; ++i)
    sum += (double)rand() / RAND_MAX;
  return medie + sigma * (sum - 6);
}