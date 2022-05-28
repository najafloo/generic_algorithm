#include "genericalgorithm.h"

namespace Optimizer {

void printVector(vector<double> vec)
{
    cout << "[ ";

    unsigned len = vec.size();

    for(unsigned i = 0; i < len; i++)
    {
        cout << vec[i];
        if(i != len - 1)
            cout << " , ";
    }

    cout << " ]" << endl;
}

void printPopulation(vector<Portfolio> portfolios)
{
    cout << "[ ";

    unsigned len = portfolios.size();

    for(unsigned i = 0; i < len; i++)
    {
        cout << portfolios[i].fitness;
        if(i != len - 1)
            cout << " , ";
    }

    cout << " ]" << endl;
}

// Generate random numbers in given range
int random_num(int start, int end)
{
    int range = (end - start) + 1;
    int random_int = start + (rand() % range);
    return random_int;
}

// Create random genes for mutation
char mutated_genes()
{
    int len = static_cast<int>(GENES.size());
    int r = random_num(0, len - 1);
    return GENES[static_cast<unsigned>(r)];
}

// Generate chromosome - string of genes
string create_gnome(std::size_t len)
{
    string gnome = "";

    for(int i = 0; i < static_cast<int>(len); i++)
        gnome += mutated_genes();

    return gnome;
}

// map characters to their values
// Example: 'A' -> 0.0 , 'B' -> 0.1 , ... , 'a' -> 0.26 , b -> 'b'
double mapToDigit(char ch)
{
    if(ch > 90) return (ch - 71) / 100.0;
    else return (ch - 65) / 100.0;
}

// Get vector from map string
// CMeNSFBT = [ 0.02 , 0.12 , 0.3 , 0.13 , 0.18 , 0.05 , 0.01 , 0.19 ]
vector<double> mapVector(string map_str)
{
    vector<double> outout;

    for(unsigned i = 0; i < map_str.length(); i++) {
        outout.push_back(mapToDigit(map_str.at(i)));
    }

    return outout;
}

// Calculate total elemens of vector
double totalElements(vector<double> vec)
{
    double sum = 0.0;

    for(auto i = begin(vec); i != end(vec); i++){
        sum += *i;
    }

    return sum;
}

Portfolio::Portfolio(string chromosome, std::shared_ptr<MarkowitzPortfolio> markowitz_portfolio)
{
    this->chromosome = chromosome;
    this->markowitz_portfolio = markowitz_portfolio;
    fitness = fitness_calculation(mapVector(chromosome));

//    if(totalElements(mapVector(chromosome)) == 1.0)
//    {
//        fitness = fitness_calculation(mapVector(chromosome));
//    }
};

// Overloading < operator so that can sort items
bool operator<(const Portfolio &portfolio1, const Portfolio &portfolio2)
{
    return portfolio1.fitness < portfolio2.fitness;
}

// Merge and generate new children
Portfolio Portfolio::crossover(Portfolio other_portfolio)
{
    // Child chromosome
    string child_chromosome = "";

    unsigned len = chromosome.size();

    for(unsigned i = 0; i < len; i++)
    {
        // random probability
        float p = random_num(0, 100) / 100;

        // if p is less than 0.45, get gene from parent 1
        if(p < 0.30f)
            child_chromosome += chromosome[i];

        // if p is between 0.45 and 0.90, get gene from parent 2
        else if(p < 0.60f)
            child_chromosome += other_portfolio.chromosome[i];

        // otherwise insert random mutation gene
        else
            child_chromosome += mutated_genes();
    }

    // Generate new Portfolio as new children using from generated chromosome
    return Portfolio(child_chromosome, this->markowitz_portfolio);
};

// Calculate fitness score and زheck that
// the total check portfolio assets should be equal to 1
double Portfolio::fitness_calculation(vector<double> assets)
{
    double fitness = 0.0;
    double sum = totalElements(assets);

    fitness = markowitz_portfolio->evaluate_objective(assets);

        if(sum != 1.0)
//    if(sum <= 0.9 || sum >= 1.1)
        fitness = 0.0;

    return fitness;
};

}
