<!-- omit in toc -->
# Traveling Salesman Problem Optimization using Genetic Algorithm
<!-- omit in toc -->
## Table of Contents
- [Installation](#installation)
- [Introduction](#introduction)
- [Project Overview](#project-overview)
- [Contributing](#contributing)
- [References](#references)

## Installation
Clone the repository and insert direct path in line 9 in **main.cpp** to the file containing data and build the project.

```bash
git clone https://github.com/Warzkos/tsp_optimization_tdd.git
cd tsp_optimization_tdd
# edit path in main.cpp
mkdir build && cd build
cmake ..
make
```

To run tests, uncommment lines 14-15 in **CMakeLists.txt** and rebuild the project.

To build multi-threaded version of the algorithm, set in line 11 to **TRUE** in **CMakeLists.txt** and build the project. Then insert direct path in line 27 in **mainMultiThread.cpp** to the file containing data and build the project.


## Introduction
While the primary objective is to devise an efficient algorithm for finding optimal routes in the Traveling Salesman Problem, the project also incorporates Test-Driven Development (TDD) practices to ensure robust code quality.

## Project Overview
The core components of the project include classes listed below:
- **Specimen**: Represents an individual in the genetic algorithm, with methods for path generation, mutation, fitness calculation, and offspring generation.
- **Population**: Represents a population of specimens, with methods for population generation, fitness calculation, sorting, and evolution.

File containing data should be made of intigers separated by whitespaces. The numbers represent the cost of moving from one city to another. Created array should have same number of rows and columns. For example:
```
0 9 5
3 0 7
6 2 0
```
is a valid array of 3 cities. First row represents distances from the first city to other cities, second row represents distances from second city to other cities and so on.

Crossover method was based on the paper by Üçoluk [[1]](#1). The algorithm was tested on the datasets from [[2]](#2) and it was able to find exact solution for 26 cities problem in under two minutes.

Project consists of two main files: **main.cpp** and **mainMultiThread.cpp** and there are same number of executable binary files generated. The first one is a single-threaded version of the algorithm and the second one is a multi-threaded version.

There are few parameters given to tweak the algorithm:
- **numberOfRuns** - number of times the algorithm will be run.
- **stopAfterNoBetter** - number of generations without finding better solution after which the algorithm will stop.
- **numberOfSpecimensInPopulation** - number of specimens in population.
- **populationSubstitutionPercentage** - percentage of population that will be substituted by offspring.
- **mutationChancePercentage** - chance of mutation in offspring.
- **numberOfMutations** - number of mutations in offspring.

Additionaly, in **mainMultiThread.cpp** there is a parameter: 
- **numberOfThreads** - which determines the number of threads used in the algorithm. Each thread runs independently a population, so in the same time it searches more solutions. 

A mutation is one swap of two cities in the path of a specimen.
## Contributing
Feel free to contribute to this project. You can open issues for bug reports or new features, and pull requests are welcome.

## References

<a id="1">[1]</a> Üçoluk, G. (2002). Genetic Algorithm Solution of the TSP Avoiding Special Crossover and Mutation. In Intelligent Automation &amp; Soft Computing (Vol. 8, Issue 3, pp. 265–272). Computers, Materials and Continua (Tech Science Press). https://doi.org/10.1080/10798587.2000.10642829 

<a id="2">[2]</a> TSP datasets https://people.sc.fsu.edu/~jburkardt/datasets/tsp/tsp.html