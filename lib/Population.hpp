#pragma once

#include "Specimen.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>

/**
 * @class Population
 * @brief Represents a population of specimens in a genetic algorithm.
 */
class Population {
  private:
    /**
     * @brief Static matrix representing distances between cities.
     */
    static std::vector<std::vector<int>> cities;

    /**
     * @brief Static index of the starting city for all populations.
     */
    static int startCity;

    /**
     * @brief Index of the starting city for this specific population.
     */
    int _startCity;
    
    /**
     * @brief Vector of specimens representing the population.
     */
    std::vector<Specimen> population;

  public:
    /**
     * @brief Deleted default constructor to ensure valid construction with parameters.
     */
    Population() = delete;

    /**
     * @brief Constructs a Population with a specified population size.
     * @param populationSize The size of the population.
     */
    Population(const int &populationSize);

    /**
     * @brief Default destructor.
     */
    ~Population() = default;

    /**
     * @brief Getter for the population.
     * @return Vector of specimens representing the population.
     */
    std::vector<Specimen> getPopulation() const;

    /**
     * @brief Getter for the starting city index for this population.
     * @return The index of the starting city.
     */
    int getStartCity() const;

    /**
     * @brief Adds a specimen to the population.
     * @param specimen The specimen to be added.
     */
    void addSpecimenToPopulation(const Specimen &specimen);
    
    /**
     * @brief Calculates the fitness of all specimens in the population.
     */
    void calcFitness();

    /**
     * @brief Sorts the population based on specimen fitness.
     */
    void sort();

    /**
     * @brief Getter for the best specimen in the population.
     * @return The best specimen based on fitness.
     */
    Specimen getBestSpecimen();

    /**
     * @brief Generates the next generation of the population.
     * @param substitutionPercent The percentage of specimens to be replaced in the next generation (default is 25%).
     * @param mutationChance The chance of mutation for each specimen (default is 10%).
     * @param numOfMutations The number of mutations for each specimen (default is 1).
     */
    void nextGeneration(const int &substitutionPercent = 25, const int &mutationChance = 10, const int &numOfMutations = 1);
    
    /**
     * @brief Sets the static starting city for all populations.
     * @param startCity The index of the starting city.
     */
    static void setStaticStartCity(const int &startCity);
    
    /**
     * @brief Getter for the static starting city index.
     * @return The index of the starting city for all populations.
     */
    static int getStaticStartCity();
    
    /**
     * @brief Reads cities and distances from a file and sets the static cities matrix.
     * @param fileName The name of the file containing city data.
     */
    static void readCities(const std::string &fileName);
    
    /**
     * @brief Getter for the static cities distance matrix.
     * @return The matrix representing distances between cities.
     */
    static std::vector<std::vector<int>> getCitiesDistanceMatrix();
    
    /**
     * @brief Sets the static cities distance matrix.
     * @param citiesDistanceMatrix The matrix representing distances between cities.
     */
    static void setCitiesDistanceMatrix(const std::vector<std::vector<int>> &citiesDistanceMatrix);
};
