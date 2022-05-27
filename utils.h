#ifndef SRC_CPP_UTILS_H_
#define SRC_CPP_UTILS_H_

#include <numeric>
#include <vector>

namespace Optimizer {

/**
 * @brief Total expected returns with given asset investment proportions
 *
 * @param x asset investment proportions [sum(x) == 1]
 * @param R expected return of the assets
 * @return double total returns
 */
double total_returns(const std::vector<double>& x, const std::vector<double>& R);

/**
 * @brief Total variance of portfolio with given asset investment proportions
 *
 * @param x asset investment proportions [sum(x) == 1]
 * @param sigma variance of the assets
 * @param covariance covariance between the assets
 * @return double variance of the portfolio
 */
double total_variance(const std::vector<double>& x, const std::vector<double>& sigma,
                      const std::vector<std::vector<double>>& covariance);

struct MarkowitzPortfolio {
  /**
   * @brief Construct a new Markowitz Portfolio object
   *
   * @param R expected return of the assets
   * @param sigma variance of the assets
   * @param covariance covariance between the assets
   * @param gamma risk aversion coefficient
   */
  MarkowitzPortfolio(const std::vector<double>& R, const std::vector<double>& sigma,
                     const std::vector<std::vector<double>>& covariance, double gamma = 0.1);

  /**
   * @brief Evaluates the objective with simplified Markowitz Portfolio Theory
   *
   * @param x asset investment proportions [sum(x) == 1]
   * @return double evaluate objective function
   */
  double evaluate_objective(const std::vector<double>& x) const;

  std::vector<double> R;
  std::vector<double> sigma;
  std::vector<std::vector<double>> covariance;
  double gamma;
};

}  // namespace Optimizer

#endif  // SRC_CPP_UTILS_H_
