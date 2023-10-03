#include <iostream>
#include <vector>
#include "../lib/Population.hpp"
#include "../lib/Specimen.hpp"

int main(int, char **) { 
    std::cout << "Hello, from tsp_optimization_tdd!\n" << std::endl; 

    Population::readCities("FRI26.txt");
    Population::setStaticStartCity(0);

    std::cout << "Cost of best possible route: 937" << std::endl;
    std::cout << "Best possible route: 1 25 24 23 26 22 21 17 18 20 19 16 11 12 13 15 14 10 9 8 7 5 6 4 3 2 1" << std::endl;
    std::cout << std::endl;

    int numberOfRuns = 15;
    int stopAfterNoBetter = 150;
    int numberOfSpecimensInPopulation = 250;

    int populationSubstitutionPercentage = 25;
    int mutationChancePercentage = 30;
    int numberOfMutations = 4;


    int bestFitness = __INT_MAX__;
    std::vector<int> bestPath;
    std::string foundAt;

    for(int j = 1; j<numberOfRuns+1; j++){
        std::cout << "Population: " << j << std::endl;
        Population population = Population(numberOfSpecimensInPopulation);
        int earlyStop = 0; 
        int generation=0;
        int bestLocalFitness=__INT_MAX__;
        while(earlyStop<stopAfterNoBetter){
            population.nextGeneration(populationSubstitutionPercentage, mutationChancePercentage, numberOfMutations);
            int currFitness = population.getBestSpecimen().getFitness();

            if(currFitness < bestLocalFitness){
                earlyStop=0;
                bestLocalFitness = currFitness;
            } else {
                earlyStop++;
            }
            
            if(currFitness < bestFitness){
                    bestFitness = currFitness;
                    bestPath = population.getBestSpecimen().getPath();
                    foundAt = "population: " + std::to_string(j) + ", generation: " + std::to_string(generation);
            }
            generation++;
        }

        std::cout << "Generation: " << generation << std::endl;
        std::cout << "Best specimen: " << population.getBestSpecimen().getFitness() << std::endl;
        std::cout << "Best specimen path: ";
        for(auto &city: population.getBestSpecimen().getPath()){
            std::cout << city+1 << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Best specimen fitness: " << bestFitness << std::endl;
    std::cout << "Best specimen path: ";
    for(auto &city: bestPath){
        std::cout << city+1 << " ";
    }
    std::cout << std::endl;
    std::cout << "Found at " << foundAt << std::endl;
    std::cout << std::endl;
}
