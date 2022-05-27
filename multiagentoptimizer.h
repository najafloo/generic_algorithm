#ifndef SRC_CPP_OPTIMIZER_H_
#define SRC_CPP_OPTIMIZER_H_

#include <limits>
#include <memory>
#include <vector>

#include "Utils.h"

namespace Optimizer {

/// This class represents a meta-heuristic optimizer

class MultiAgentOptimizer {
 public:
  /**
   * @brief Construct a new Multi Agent Optimizer object
   *
   * @param n dimension of the problem
   * @param upper_limits upper limits of the solution
   * @param lower_limits lower limits of the solution
   * @param markowitz_portfolio Markowitz Portfolio object
   * @param number_agents number of agents
   * @param number_iterations number of iterations
   */
  explicit MultiAgentOptimizer(std::size_t n, const std::vector<double>& upper_limits,
                               const std::vector<double>& lower_limits,
                               std::shared_ptr<MarkowitzPortfolio> markowitz_portfolio, std::size_t number_agents = 20,
                               std::size_t number_iterations = 1000);

  /**
   * @brief Optimize the solution
   *
   */
  void optimize();

  /**
   * @brief Get the best solution
   *
   * @return const std::vector<double>& best solution
   */
  const std::vector<double>& get_best_solution() const;

  /**
   * @brief Get the best value
   *
   * @return double best value
   */
  double get_best_value() const noexcept;

 private:
  size_t m_dimensions;
  std::vector<double> m_upper_limits;
  std::vector<double> m_lower_limits;
  std::shared_ptr<MarkowitzPortfolio> m_markowitz_portfolio;
  size_t m_number_agents;
  size_t m_number_iterations;
  std::vector<double> m_best_solution;
  double m_best_value = std::numeric_limits<double>::min();
};

}  // namespace Optimizer

#endif  // SRC_CPP_OPTIMIZER_H_
