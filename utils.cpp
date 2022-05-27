#include "Utils.h"

namespace Optimizer {

double total_returns(const std::vector<double>& x, const std::vector<double>& R) {
  return std::inner_product(x.begin(), x.end(), R.begin(), 0.0);
}

double total_variance(const std::vector<double>& x, const std::vector<double>& sigma,
                      const std::vector<std::vector<double>>& covariance) {
  const double number_assets = x.size();

  double total_covariance = 0.0;
  for (size_t i = 0; i < number_assets - 1; ++i) {
    for (size_t j = i + 1; j < number_assets; ++j) total_covariance += x[i] * x[j] * covariance[i][j];
  }

  return total_covariance + std::inner_product(x.begin(), x.end(), sigma.begin(), 0.0);
}

MarkowitzPortfolio::MarkowitzPortfolio(const std::vector<double>& R, const std::vector<double>& sigma,
                                       const std::vector<std::vector<double>>& covariance, double gamma)
  : R{ R }, sigma{ sigma }, covariance{ covariance }, gamma{ gamma } {}

double MarkowitzPortfolio::evaluate_objective(const std::vector<double>& x) const {
  return total_returns(x, R) - 0.5 * gamma * total_variance(x, sigma, covariance);
}

}  // namespace Optimizer
