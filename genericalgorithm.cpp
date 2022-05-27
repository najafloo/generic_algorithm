#include "genericalgorithm.h"

namespace Optimizer {

// Function to generate random numbers in given range
int random_num(int start, int end)
{
    int range = (end-start)+1;
    int random_int = start+(rand()%range);
    return random_int;
}

// Create random genes for mutation
char mutated_genes()
{
    int len = static_cast<int>(GENES.size());
    int r = random_num(0, len-1);
    return GENES[static_cast<unsigned>(r)];
}

// create chromosome or string of genes
string create_gnome(std::size_t len)
{
    string gnome = "";
    for(int i = 0; i<static_cast<int>(len); i++)
        gnome += mutated_genes();
    return gnome;
}

void printVector(vector<double> vec)
{
    cout << "[ ";

    for(auto i = begin(vec); i != end(vec); i++){
        cout << *i;
        cout << " , ";
    }

    cout << " ]" << endl;
}

double mapToDigit(char ch) {

    // convert character to value ex: 'A' -> 0.26
    if(ch > 90) return (ch - 71) / 100.0;
    else return (ch - 65) / 100.0;
}

vector<double> mapVector(string mapStr)
{
    vector<double> result;
    for(unsigned i = 0; i<mapStr.length(); i++) {
        result.push_back(mapToDigit(mapStr.at(i)));
    }

//    printVector(result);

    return result;
}

Individual::Individual(string chromosome, std::size_t len, std::shared_ptr<MarkowitzPortfolio> markowitz_portfolio)
{
    this->chromosome = chromosome;
    this->len = len;
    this->markowitz_portfolio = markowitz_portfolio;
    fitness = cal_fitness(mapVector(chromosome));
};

// Overloading < operator
bool operator<(const Individual &ind1, const Individual &ind2)
{
    return ind1.fitness > ind2.fitness;
}

// Perform mating and produce new offspring
Individual Individual::mate(Individual par2)
{
    // chromosome for offspring
    string child_chromosome = "";

    int len = chromosome.size();

    for(int i = 0;i<len;i++)
    {
        // random probability
        float p = random_num(0, 100)/100;

        // if prob is less than 0.45, insert gene
        // from parent 1
        if(p < 0.45f)
            child_chromosome += chromosome[i];

        // if prob is between 0.45 and 0.90, insert
        // gene from parent 2
        else if(p < 0.90f)
            child_chromosome += par2.chromosome[i];

        // otherwise insert random gene(mutate),
        // for maintaining diversity
        else
            child_chromosome += mutated_genes();
    }

    // create new Individual(offspring) using
    // generated chromosome for offspring
    return Individual(child_chromosome, this->len, this->markowitz_portfolio);
};

// Calculate fitness score, it is the number of
// characters in string which differ from target
// string.
double Individual::cal_fitness(vector<double> assets)
{
    double fitness = 0.0;
    double sum = 0;

    int len = sizeof(assets) / sizeof(assets[0]);

//    cout << " len = " << len;
//    printVector(assets);

//    for(int i = 0; i<len; i++)
//    {
//        cout << "ch = " << assets.at(i);
//        sum += assets.at(i);
//        if(chromosome[i] != TARGET[i])
//            fitness++;
//    }

    for(auto i = begin(assets); i != end(assets); i++){
        sum += *i;
    }

    fitness = markowitz_portfolio->evaluate_objective(assets);

//    cout << "sum = " << sum << endl;
    if(sum != 1.0)
        fitness = 0;
//    fitness = sum;

    return fitness;
};

}
