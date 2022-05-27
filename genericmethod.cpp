#include "genericmethod.h"


// Overloading < operator
bool operator<(const Individual &ind1, const Individual &ind2)
{
    return ind1.fitness < ind2.fitness;
}

// Function to generate random numbers in given range
int _random_num(int start, int end)
{
    int range = (end-start)+1;
    int random_int = start+(rand()%range);
    return random_int;
}

// Create random genes for mutation
char _mutated_genes()
{
    int len = static_cast<int>(_GENES.size());
    int r = _random_num(0, len-1);
    return _GENES[r];
}

// create chromosome or string of genes
string _create_gnome()
{
    int len = TARGET.size();
    string gnome = "";
    for(int i = 0;i<len;i++)
        gnome += _mutated_genes();
    return gnome;
}

Individual::Individual(string chromosome)
{
    if(chromosome.empty())
        cout << "chromosome = " << chromosome << endl;

    this->chromosome = chromosome;
    fitness = _cal_fitness();
};

// Perform mating and produce new offspring
Individual Individual::_mate(Individual par2)
{
    // chromosome for offspring
    string child_chromosome = "";

    int len = chromosome.size();
    for(int i = 0;i<len;i++)
    {
        // random probability
        float p = _random_num(0, 100)/100;

        // if prob is less than 0.45, insert gene
        // from parent 1
        if(p < 0.45)
            child_chromosome += chromosome[i];

        // if prob is between 0.45 and 0.90, insert
        // gene from parent 2
        else if(p < 0.90)
            child_chromosome += par2.chromosome[i];

        // otherwise insert random gene(mutate),
        // for maintaining diversity
        else
            child_chromosome += _mutated_genes();
    }

    // create new Individual(offspring) using
    // generated chromosome for offspring
    return Individual(child_chromosome);
};


// Calculate fitness score, it is the number of
// characters in string which differ from target
// string.
int Individual::_cal_fitness()
{
    int len = TARGET.size();
    int fitness = 0;
    for(int i = 0;i<len;i++)
    {
        if(chromosome[i] != TARGET[i])
            fitness++;
    }
    return fitness;
};
