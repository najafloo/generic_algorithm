#include "MultiAgentOptimizer.h"
#include "genericalgorithm.cpp"

#include <bits/stdc++.h>

using namespace std;

namespace Optimizer {

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

  // replace the following code
//  m_best_solution = m_upper_limits;
//  m_best_value = m_markowitz_portfolio->evaluate_objective(m_best_solution);
}

void MultiAgentOptimizer::optimize() {

    srand(static_cast<unsigned>(time(0)));

    // current generation
    int generation = 0;

    vector<Individual> population;

    // create initial population
    for(int i = 0;i<static_cast<int>(m_number_agents);i++)
    {
        string gnome = create_gnome(m_dimensions);
        cout << gnome << " , ";
        printVector(mapVector(gnome));
        population.push_back(Individual(gnome, m_dimensions, m_markowitz_portfolio));
    }

    int iteration = static_cast<int>(m_number_iterations);
    m_best_value = 0;

    while(iteration > 0)
    {
        // sort the population in increasing order of fitness score
        sort(population.begin(), population.end());

        if(population[0].fitness > m_best_value) {
            m_best_value = population[0].fitness;
            m_best_solution = mapVector(population[0].chromosome);
        }

        // Generate new offsprings for new generation
        vector<Individual> new_generation;

        // Perform Elitism, that mean 10% of fittest population
        // goes to the next generation
        int s = (10 * m_number_agents) / 100;

//        cout << "s1 = " << s << endl;

        for(int i = 0; i < s; i++)
            new_generation.push_back(population[static_cast<unsigned>(i)]);

        // From 50% of fittest population, Individuals
        // will mate to produce offspring
        s = ( 90 * m_number_agents ) / 100;

//        cout << "s2 = " << s << endl;

        for(int i = 0; i < s; i++)
        {
            int len = static_cast<int>(population.size());
            int r = random_num(0, m_number_agents / 2);
//            cout << "r1 = " << r << endl;
            Individual parent1 = population[static_cast<unsigned>(r)];
            r = random_num(0, m_number_agents / 2);
//            cout << "r2 = " << r << endl;
            Individual parent2 = population[static_cast<unsigned>(r)];

            Individual offspring = parent1.mate(parent2);
            new_generation.push_back(offspring);
        }

        population = new_generation;
        cout<< "Generation: " << generation << "\t";
        cout<< "String: "<< population[0].chromosome <<"\t";
        cout<< "Fitness: "<< population[0].fitness << "\n";

        generation++;
        iteration--;
    }

    cout<< "Generation: " << generation << "\t";
    cout<< "String: "<< population[0].chromosome <<"\t";
    cout<< "Fitness: "<< population[0].fitness << "\n";

//    m_best_value = population[0].fitness;
//    cout << "chromosome = " << population[0].chromosome << endl;

//    m_best_solution = mapVector(population[0].chromosome);
//    printVector(m_best_solution);

    double sum = 0.0;
    for(auto i = begin(m_best_solution); i != end(m_best_solution); i++){
        sum += *i;
    }

    cout << "sum = " << sum << endl;

}

const std::vector<double>& MultiAgentOptimizer::get_best_solution() const { return m_best_solution; }

double MultiAgentOptimizer::get_best_value() const noexcept { return m_best_value; }

}  // namespace Optimizer
