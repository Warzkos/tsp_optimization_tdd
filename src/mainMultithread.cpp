#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include "../lib/Population.hpp"
#include "../lib/Specimen.hpp"

struct threadOutputData{
    int bestFitness;
    std::vector<int> bestPath;

    bool operator<(const threadOutputData &other) const{
        return bestFitness < other.bestFitness;
    }
};

void runPopulation(std::promise<threadOutputData> &&output, 
                   int stopAfterNoBetter,
                   int numberOfSpecimensInPopulation,
                   int populationSubstitutionPercentage,
                   int mutationChancePercentage,
                   int numberOfMutations);

int main(int, char **) { 
    std::cout << "Hello, from multithread tsp_optimization_tdd!" << std::endl; 

    Population::readCities("***DIRECT_PATH_TO_FILE***");
    Population::setStaticStartCity(0);

    int numberOfThreads = 10;
    int numberOfRuns = 20;

    int stopAfterNoBetter = 150;
    int numberOfSpecimensInPopulation = 500;

    int populationSubstitutionPercentage = 25;
    int mutationChancePercentage = 30;
    int numberOfMutations = 5;

    int bestFitness = __INT_MAX__;
    std::vector<int> bestPath = {};

    std::cout << "Starting" << std::endl;

    for(int j = 0; j<numberOfRuns; j++){
        
        std::vector<std::thread> threadVector;
        std::vector<std::future<threadOutputData>> futureVector;
        
        for(int i = 0; i<numberOfThreads; i++){
            std::promise<threadOutputData> promise;
            futureVector.emplace_back(promise.get_future());
            threadVector.emplace_back(
                std::move(
                    std::thread(
                        &runPopulation, 
                        std::move(promise),
                        stopAfterNoBetter, 
                        numberOfSpecimensInPopulation, 
                        populationSubstitutionPercentage, 
                        mutationChancePercentage, 
                        numberOfMutations
                    )
                )
            );
        }

        for(auto &thread: threadVector){
            thread.join();
        }

        std::vector<threadOutputData> outputVector;
        for(auto &future: futureVector){
            outputVector.emplace_back(future.get());
        }

        std::sort(outputVector.begin(), outputVector.end());
        if(bestFitness > outputVector.front().bestFitness){
            bestFitness = outputVector.front().bestFitness;
            bestPath = outputVector.front().bestPath;
        }

        std::cout << "Run " << j+1 << ", best fitness: " << outputVector.front().bestFitness <<  std::endl;
    }

    std::cout << std::endl;
    std::cout << "Best overall fitness: " << bestFitness << std::endl;
    std::cout << "Best overall path: ";
    for(auto &city: bestPath){
        std::cout << city+1 << " ";
    }
}

void runPopulation(std::promise<threadOutputData> &&output, 
                   int stopAfterNoBetter,
                   int numberOfSpecimensInPopulation,
                   int populationSubstitutionPercentage,
                   int mutationChancePercentage,
                   int numberOfMutations){

    Population population = Population(numberOfSpecimensInPopulation);
    int bestFitness = __INT_MAX__;
    std::vector<int> bestPath;

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
        }
        generation++;
    }
    output.set_value({bestFitness, bestPath});
}
