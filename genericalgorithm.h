#ifndef GENERICALGORITHM_H
#define GENERICALGORITHM_H

#include<Utils.h>
#include <bits/stdc++.h>

using namespace std;

namespace Optimizer {

const string GENES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcde";

class Portfolio
{
public:
    string chromosome;
    double fitness;
    std::size_t len;
    std::shared_ptr<MarkowitzPortfolio> markowitz_portfolio;

    Portfolio(string, std::size_t, std::shared_ptr<MarkowitzPortfolio>);
    Portfolio crossover(Portfolio parent2);
    double fitness_calculation(vector<double>);
};

bool operator<(const Portfolio&, const Portfolio&);

string create_gnome(std::size_t);
void printVector(vector<double>);
double mapToDigit(char);
vector<double> mapVector(string);
int random_num(int, int);
double totalElements(vector<double>);
void printPopulation(vector<Portfolio>);

}

#endif // GENERICALGORITHM_H
