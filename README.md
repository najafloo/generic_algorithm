# Markowitz Portfolio Theory Optimization

## Markowitz Portfolio Theory
Modern Portfolio Theory is based on Harry Markowitz’s 1952 work on mean-variance portfolios. The theory is a mathematical framework for assembling a portfolio of assets such that the expected return is maximized.

## Description

The purpose of this application is to find the optimal return of a portfolio which is based on the Markowitz theory and also find the relevant data set that meets the following constrains:

![constaint_1](images/constraint_1.svg)

and

![constraint_2](images/constraint_2.svg)

and assets data is (*x<sub>1</sub>*, *x<sub>2</sub>* . . . *x<sub>n</sub>*)

## Inputs
```
n : Maximum number of assets
lower_limmits : Minimum amount of asset proportions
upper_limmits : Maximum amount of asset proportions
number_agents : Number of population
number_iterations : Number of optimizition steps
```
The assets are provided in the file ```data.json``` *(n = 8)*.

## Output

1. {*x<sub>1</sub>*, *x<sub>2</sub>* . . . *x<sub>n</sub>*} as best solution
2. highest value of the objective function

## Implementation environment
The calculation section of this program is written in language C++ which is imported and invoked as a library by the Python language. The program build operation is performed on Ubuntu 20.04.3 LTS operating system.

## Install dependencies
- Create a virtual env and activate it: ```python3 -m venv env; source env/bin/activate```
- Install dependencies: ```pip install -r requirements.txt -r dev-requirements.txt```
- Build C++ code as Python module: ```python3 setup.py install```

## How to run
Run the following command after installing dependencies

```python3 main.py data.json```

## sample run:
```bash
Best solution: [0.05, 0.0, 0.0, 0.2, 0.25, 0.17, 0.26, 0.07]
Best value: 0.595493228
```

## Optimization Algorithm
To find the most optimal answer *Genetic algorithm* has been used. Therefore, we considered assumptions for this algorithm.

### Gene representation
According to the project assumptions, each of our assets should be in the range of 0 to 0.3. Therefore, assuming that the size accuracy of each asset is one hundredth, this range is divided into 31 parts, each of them can be composed of the following characters: 

```C++
const string GENES = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcde";
```
therfore every character has a numerical value:
```
'A' = 0.00
'B' = 0.01
'C' = 0.02
 ...
'c' = 0.28
'd' = 0.29 and
'e' = 0.30
```
As we mention above ```n = 8``` every chromosome is represented as a ```string``` with ```length = 8``` like DbaWTcdZ and Its numerical value is equal to the sum of the numerical value of each character. For example:
```
value of CMeNSFBT = 0.02 + 0.12 + 0.3 + 0.13 + 0.18 + 0.05 + 0.01 + 0.19 = 1.0
```

### Presentation ```Class```
We represent every chromosome as a class which called ```Portfolio```
``` C++
class Portfolio
{
public:
    string chromosome;
    double fitness;
    std::shared_ptr<MarkowitzPortfolio> markowitz_portfolio;

    Portfolio(string, std::shared_ptr<MarkowitzPortfolio>);
    Portfolio crossover(Portfolio portfolio);
    double fitness_calculation(vector<double>);
};
```

### initialize
At First, we randomly generate 20 (```number_agents = 20```) genes that make up our zero generation.

```
********************** Initialize Population ********************** 
YHVdGDIC , [ 0.24 , 0.07 , 0.21 , 0.29 , 0.06 , 0.03 , 0.08 , 0.02 ]
OHLTNVLa , [ 0.14 , 0.07 , 0.11 , 0.19 , 0.13 , 0.21 , 0.11 , 0.26 ]
UVHDPBcM , [ 0.02 , 0.21 , 0.07 , 0.03 , 0.15 , 0.01 , 0.28 , 0.12 ]
JPLObKRS , [ 0.09 , 0.15 , 0.11 , 0.14 , 0.27 , 0.10 , 0.17 , 0.18 ]
PHQUIXWU , [ 0.15 , 0.07 , 0.16 , 0.02 , 0.08 , 0.23 , 0.22 , 0.20 ]
eAHKVSFK , [ 0.03 , 0.00 , 0.07 , 0.01 , 0.21 , 0.18 , 0.05 , 0.10 ]
GKOULLBT , [ 0.06 , 0.01 , 0.14 , 0.02 , 0.11 , 0.11 , 0.01 , 0.19 ]
YKCUTTID , [ 0.24 , 0.01 , 0.02 , 0.02 , 0.19 , 0.19 , 0.08 , 0.03 ]
YWXeOOUN , [ 0.24 , 0.22 , 0.23 , 0.03 , 0.14 , 0.14 , 0.20 , 0.13 ]
NbWDObOU , [ 0.13 , 0.27 , 0.22 , 0.03 , 0.14 , 0.27 , 0.14 , 0.20 ]
HaJQEJEc , [ 0.07 , 0.26 , 0.09 , 0.16 , 0.04 , 0.09 , 0.04 , 0.28 ]
TESHVYJM , [ 0.19 , 0.04 , 0.18 , 0.07 , 0.21 , 0.24 , 0.09 , 0.12 ]
PBMeOBKb , [ 0.15 , 0.01 , 0.12 , 0.03 , 0.14 , 0.01 , 0.10 , 0.27 ]
cBcJbJbB , [ 0.28 , 0.01 , 0.28 , 0.09 , 0.27 , 0.09 , 0.27 , 0.01 ]
EEPILSEc , [ 0.04 , 0.04 , 0.15 , 0.08 , 0.11 , 0.18 , 0.04 , 0.28 ]
WUDLNMXc , [ 0.22 , 0.02 , 0.03 , 0.11 , 0.13 , 0.12 , 0.23 , 0.28 ]
LEZXFFRA , [ 0.11 , 0.04 , 0.25 , 0.23 , 0.05 , 0.05 , 0.17 , 0.00 ]
EPHdWEeb , [ 0.04 , 0.15 , 0.07 , 0.29 , 0.22 , 0.04 , 0.30 , 0.27 ]
GNCRAEOW , [ 0.06 , 0.13 , 0.02 , 0.17 , 0.00 , 0.04 , 0.14 , 0.22 ]
YRCGbYCG , [ 0.24 , 0.17 , 0.02 , 0.06 , 0.27 , 0.24 , 0.02 , 0.06 ]
```

### main loop
In this loop we sort random chromosome by their score, if the top item pass the conditions(sum = 1 and new_fitness > old_fitness) the optimum value will update.
After that we use 10 percent of population and from top 90 percent of assets pair of chromosome will select and generate new childrens. The process will terminate after finish number of iteration.

``` C++
while(iteration > 0)
{
    // Sort the population descending order of fitness score
    sort(population.rbegin(), population.rend());

    if(population[0].fitness >= m_best_value) {
        m_best_solution = mapVector(population[0].chromosome);
        m_best_value = population[0].fitness;
    }

    // Generate new children for new generation
    vector<Portfolio> new_generation;

    //10% of best population goes to the next generation
    int best = (10 * m_number_agents) / 100;

    for(int i = 0; i < best; i++)
        new_generation.push_back(population[static_cast<unsigned>(i)]);

    best = ( 90 * m_number_agents ) / 100;

    // From top score parents select pairs to merge together and make new children
    for(int i = 0; i < best; i += 2)
    {
        Portfolio parent1 = population[static_cast<unsigned>(i)];
        Portfolio parent2 = population[static_cast<unsigned>(i+1)];

        Portfolio children = parent1.crossover(parent2);

        new_generation.push_back(children);
    }

    population = new_generation;

    iteration--;
}
```

### crossover
In crossover we randomly select a position and making a new child or in some cases mutate the gene:

``` C++
Portfolio Portfolio::crossover(Portfolio portfolio)
{
    // Child chromosome
    string child_chromosome = "";

    unsigned len = chromosome.size();

    // Make a random index and randomly select from parents
    // to generate a new children or mutate the children chromosome
    for(unsigned i = 0; i < len; i++)
    {
        float pos = random_number(0, 100) / 100;

        if(pos < 0.2f)
            child_chromosome += chromosome[i];
        else if(pos < 0.8f)
            child_chromosome += portfolio.chromosome[i];
        else
            child_chromosome += mutated_genes(); // Mutate chromosome
    }

    // Generate new Portfolio as new children using from generated chromosome
    return Portfolio(child_chromosome, this->markowitz_portfolio);
};
```

### mutation
make a random gene to mutate chromosome

``` C++
char mutated_genes()
{
    int len = static_cast<int>(GENES.size());
    int r = random_number(0, len - 1);
    return GENES[static_cast<unsigned>(r)];
}
```

### gene mapper to value
this function maps the gene to value: 'B' -> 0.01

``` C++
double mapToDigit(char ch)
{
    if(ch > 90) return (ch - 71) / 100.0;
    else return (ch - 65) / 100.0;
}
```

### check fitness value
Calculate the fitness value for selected portfolio

``` C++
double Portfolio::fitness_calculation(vector<double> assets)
{
    double fitness = 0.0;
    double sum = totalElements(assets);

    /************ Objective Function ************/
    fitness = markowitz_portfolio->evaluate_objective(assets);

    // Project constraint
    if(sum != 1.0)
        fitness = 0.0;

    return fitness;
};
```

### Comment
This algorithm, because there is no exact answer to the problem, provides a more appropriate and better answer by increasing the number of iterations, and of course it can not be claimed that the proposed method is the best choice, because even by changing coefficients or changing input parameters different answers achieved.

### Vision
- To improve the performance of the algorithm, the initialization process can be made more rigorous and only chromosomes can be produced with a total percentage of one. This increases the chances of achieving a better result, but the process of integration and mutation after zero generation will still be limited.
- Since we must always consider a portfolio as the correct result that is the sum of the capital equal to one, so this limits the calculation space and one of the solutions to compensate for this limitation is to increase the number of iterations.
- An penalty range can also be considered for the sum of the elements, and for example the range 0.9 to 1.1 can be considered for the sum of the assetsAnd only when we want to select the optimal principal value, we apply the condition equal to 1.

#### Auther
[Amin Najafloo](https://www.linkedin.com/in/amin-najafloo-38753b79/)
