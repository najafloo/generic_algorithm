#include "MultiAgentOptimizer.h"
#include "genericalgorithm.h"

#include <bits/stdc++.h>

using namespace std;

namespace Optimizer {

const bool DEBUG_MODE = true;

MultiAgentOptimizer::MultiAgentOptimizer(std::size_t n, const std::vector<double>& upper_limits,
                                         const std::vector<double>& lower_limits,
                                         std::shared_ptr<MarkowitzPortfolio> markowitz_portfolio,
                                         std::size_t number_agents, std::size_t number_iterations)
  : m_dimensions{ n },
    m_upper_limits{ upper_limits },
    m_lower_limits{ lower_limits },
    m_markowitz_portfolio{ markowitz_portfolio },
    m_number_agents{ number_agents },
    m_number_iterations{ number_iterations } {
}

void MultiAgentOptimizer::optimize() {

    srand(static_cast<unsigned>(time(0)));

    // Generation number
    int generation = 0;

    vector<Portfolio> population;

    // Initial population
    for(int i = 0; i < static_cast<int>(m_number_agents); i++)
    {
        string gnome = create_gnome(m_dimensions);
        if(DEBUG_MODE) cout << gnome << " , ";
        printVector(mapVector(gnome));
        population.push_back(Portfolio(gnome, m_dimensions, m_markowitz_portfolio));
    }

    int iteration = 1000;//static_cast<int>(m_number_iterations);
    m_best_value = 0;

    while(iteration > 0)
    {
        // Sort the population descending order of fitness score
        sort(population.rbegin(), population.rend());

        if(population[0].fitness >= m_best_value) {
//            if(totalElements(mapVector(population[0].chromosome)) == 1.0)
            {
                m_best_solution = mapVector(population[0].chromosome);
                m_best_value = population[0].fitness;
            }
        }

        // Generate new children for new generation
        vector<Portfolio> new_generation;

        //10% of fittest population goes to the next generation
        int s = (10 * m_number_agents) / 100;

//        cout << "population = ";
//        printPopulation(population);

        for(int i = 0; i < s; i++)
            new_generation.push_back(population[static_cast<unsigned>(i)]);

        s = ( 90 * m_number_agents ) / 100;

        // From half of fittest population, Portfolios will merge to produce children
        for(int i = 0; i < s; i++)
        {
            int r = random_num(0, m_number_agents / 2);
            Portfolio parent1 = population[static_cast<unsigned>(r)];

            r = random_num(0, m_number_agents / 2);
            Portfolio parent2 = population[static_cast<unsigned>(r)];

            Portfolio children = parent1.crossover(parent2);

            new_generation.push_back(children);
        }

        population = new_generation;

        if(DEBUG_MODE) cout<< "Generation: " << generation << "\t";
        if(DEBUG_MODE) cout<< "String: "<< population[0].chromosome <<"\t";
        if(DEBUG_MODE) cout<< "Fitness: "<< population[0].fitness << "\n";

        generation++;
        iteration--;
    }

//    if(DEBUG_MODE) cout<< "Generation: " << generation << "\t";
//    if(DEBUG_MODE) cout<< "String: "<< population[0].chromosome <<"\t";
//    if(DEBUG_MODE) cout<< "Fitness: "<< population[0].fitness << "\n";

//    m_best_value = population[0].fitness;
//    if(DEBUG_MODE) cout << "chromosome = " << population[0].chromosome << endl;

//    m_best_solution = mapVector(population[0].chromosome);
//    printVector(m_best_solution);

    double sum = totalElements(m_best_solution);

    if(DEBUG_MODE) cout << "sum = " << sum << endl;
}

const std::vector<double>& MultiAgentOptimizer::get_best_solution() const { return m_best_solution; }

double MultiAgentOptimizer::get_best_value() const noexcept { return m_best_value; }

}  // namespace Optimizer
