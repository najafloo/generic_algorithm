#ifndef GENERICMETHOD_H
#define GENERICMETHOD_H

#include <bits/stdc++.h>

using namespace std;

// Number of individuals in each generation
#define POPULATION_SIZE 100

// Valid Genes
const string _GENES = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOP"\
"QRSTUVWXYZ 1234567890, .-;:_!\"#%&/()=?@${[]}";

// Target string to be generated
const string TARGET = "I love GeeksforGeeks";

// Class representing individual in population
class Individual
{
public:
    string chromosome;
    int fitness;
    Individual(string chromosome);
    Individual _mate(Individual parent2);
    int _cal_fitness();
};



#endif // GENERICMETHOD_H
