#ifndef GENERICALGORITHM_H
#define GENERICALGORITHM_H

#include<utils.h>
#include <bits/stdc++.h>

using namespace std;

namespace Optimizer {

const string GENES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcde";

class Individual
{
public:
    string chromosome;
    double fitness;
    std::size_t len;
    Individual(string chromosome, std::size_t len, std::shared_ptr<MarkowitzPortfolio> markowitz_portfolio);
    Individual mate(Individual parent2);
    double cal_fitness(vector<double> assets);
    std::shared_ptr<MarkowitzPortfolio> markowitz_portfolio;
};
}

#endif // GENERICALGORITHM_H
