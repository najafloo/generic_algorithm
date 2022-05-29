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

unsigned findFirstEmptyCell(string gnome, int index)
{
    int empty_index = 0;

    for(unsigned i = 0; i < gnome.size(); i++)
    {
        if(gnome[i] == '0')
        {
            if(empty_index == index)
                return i;

            empty_index++;

        }
    }

    return 0;
}

string genarateNewValidGnome(int len)
{
    string gnome(static_cast<unsigned>(len), '0');
    double sum = 0.0;

    do{
        string g(static_cast<unsigned>(len), '0');
        gnome = g;
        sum = 0.0;
        int iteration = 0;
        int max_space = static_cast<int>(GENES.length()) - 1;

        cout << "0 ==== max_space = " << max_space << endl;

        while (iteration < len - 1)
        {
            int random_index = random_num(0, len - iteration - 1);
            cout << "1 ==== random index = " << random_index << ", max range for index = " << (len - iteration - 1) << endl;
            int remained_space = ((1.0 - sum) >= 0.3)? max_space : (1.0 - sum) * 100.0;
            cout << "2 ==== remained_space = " << remained_space << ", 1 - sum = " << ( 1.0 - sum ) << endl;

            unsigned index = findFirstEmptyCell(gnome, random_index);
            int random_value = random_num(0, remained_space);


            char random_char = GENES[static_cast<unsigned>(random_value)];
            gnome[index] = random_char;
            cout << "3 ==== random_value = " << random_value << ", random_char = " << random_char << ", mapToDigit(random_char) = " << mapToDigit(random_char) << ", gnome = " << gnome << endl;
            sum += mapToDigit(random_char);
            iteration++;
        }
        unsigned lastEmptyIndex = findFirstEmptyCell(gnome, 0);
        gnome[lastEmptyIndex] = GENES[static_cast<unsigned>((1.0 - sum) * 100)];

        if(sum != 1.0) cout << "RRRRRRRRREJECTTTTTTTTTTTTTTtED sum = " << sum << ", gnome = " << gnome << endl;

    } while (sum != 1.0);

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

    int index = random_num(0, 7);

    for(unsigned i = 0; i < len; i++)
    {
        // random probability
        /*float p = random_num(0, 100) / 100;

        // if p is less than 0.45, get gene from parent 1
        if(p < 0.30f)
            child_chromosome += chromosome[i];

        // if p is between 0.45 and 0.90, get gene from parent 2
        else if(p < 0.60f)
            child_chromosome += other_portfolio.chromosome[i];

        // otherwise insert random mutation gene
        else
            child_chromosome += mutated_genes();*/


        if(i < index)
            child_chromosome += chromosome[i];
        else
            child_chromosome += other_portfolio.chromosome[i];
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
