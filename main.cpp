#include <QCoreApplication>
#include <bits/stdc++.h>
#include "genericmethod.cpp"
#include "multiagentoptimizer.h"
#include "utils.h"

using namespace std;

void calcSampleGen()
{
    srand(static_cast<unsigned>(time(0)));

    // current generation
    int generation = 0;

    vector<Individual> population;
    bool found = false;

    // create initial population
    for(int i = 0;i<POPULATION_SIZE;i++)
    {
        string gnome = _create_gnome();
        population.push_back(Individual(gnome));
    }

    while(! found)
    {
        // sort the population in increasing order of fitness score
        sort(population.begin(), population.end());

        // if the individual having lowest fitness score ie.
        // 0 then we know that we have reached to the target
        // and break the loop
        if(population[0].fitness <= 0)
        {
            found = true;
            break;
        }

        // Otherwise generate new offsprings for new generation
        vector<Individual> new_generation;

        // Perform Elitism, that mean 10% of fittest population
        // goes to the next generation
        int s = (10*POPULATION_SIZE)/100;
        for(int i = 0;i<s;i++)
            new_generation.push_back(population[i]);

        // From 50% of fittest population, Individuals
        // will mate to produce offspring
        s = (90*POPULATION_SIZE)/100;
        for(int i = 0;i<s;i++)
        {
            int len = population.size();
            int r = _random_num(0, 50);
            Individual parent1 = population[r];
            r = _random_num(0, 50);
            Individual parent2 = population[r];
            Individual offspring = parent1._mate(parent2);
            new_generation.push_back(offspring);
        }
        population = new_generation;
        cout<< "Generation: " << generation << "\t";
        cout<< "String: "<< population[0].chromosome <<"\t";
        cout<< "Fitness: "<< population[0].fitness << "\n";

        generation++;
    }
    cout<< "Generation: " << generation << "\t";
    cout<< "String: "<< population[0].chromosome <<"\t";
    cout<< "Fitness: "<< population[0].fitness << "\n";

}

void calcMarkoviztOptimom()
{
    std::vector<double> R = {0.34, 0.09, 0.36, 0.75, 1.5, 1.45, 0.08, 0.18};
    std::vector<double> sigma = {2.019, 4.202, 1.85, 4.04, 7.98, 6.91, 1.13, 2.19};
    std::vector<std::vector<double>> covariance =  {{1, 0.019, 0.028, 0.0053, -0.0015, -0.0013, 0.0006, 0.001},
                                                    {0.019, 1, 0.0064, 0.0034, -0.0031, -0.0043, 0.0005, 0.0009},
                                                    {0.028, 0.0064, 1, 0.0071, -0.0021, -0.0024, 0.0006, 0.0011},
                                                    {0.0053, 0.0034, 0.0071, 1, 0.0003, -0.0004, 0.0001, 0.0004},
                                                    {-0.0015, -0.0031, -0.0021, 0.003, 1, 0.054, -0.0008, 0.0005},
                                                    {-0.0013, -0.0043, -0.0024, -0.0004, 0.054, 1, -0.0002, 0.0001},
                                                    {0.0006, 0.0005, 0.0006, 0.0001, -0.0008, -0.0002, 1, 0.0052},
                                                    {0.001, 0.0009, 0.0011, 0.0004, 0.0005, 0.0001, 0.0052, 1}};


    std::shared_ptr<Optimizer::MarkowitzPortfolio> objective =
            std::shared_ptr<Optimizer::MarkowitzPortfolio>(new Optimizer::MarkowitzPortfolio(R, sigma, covariance));

    std::size_t n = R.size();

    std::vector<double> upper_limits(n, 0.3);
    std::vector<double> lower_limits(n, 0.0);

    Optimizer::MultiAgentOptimizer multiAgentOptimizer =
            Optimizer::MultiAgentOptimizer(n, upper_limits, lower_limits,objective, 20, 1000);

    multiAgentOptimizer.optimize();

    cout << "best value = " << multiAgentOptimizer.get_best_value() << endl;
    cout << "best solution = ";
    for(auto i = begin(multiAgentOptimizer.get_best_solution()); i  != end(multiAgentOptimizer.get_best_solution()); i++){
        cout << *i << " , ";
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//        calcSampleGen();

    calcMarkoviztOptimom();

    return a.exec();
}

