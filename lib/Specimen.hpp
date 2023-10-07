#pragma once
#include <algorithm>
#include <random>
#include <vector>
#include <ranges>

/**
 * @class Specimen
 * @brief Represents an individual specimen in a genetic algorithm.
 */
class Specimen {
  private:
    /**
     * @brief Static random number generator for Specimen generation, mutation operations and offspring.
     */
    static std::minstd_rand0 rng;

    /**
     * @brief Represents the sequence of cities in the path.
     */
    std::vector<int> path;

    /**
     * @brief Represents the fitness of the specimen.
     */
    int fitness = 0;

  public:
    /**
     * @brief Deleted default constructor to ensure valid construction with parameters.
     */
    Specimen() = delete;

    /**
     * @brief Constructs a Specimen with a specified number of cities and starting city.
     * @param numOfCities The total number of cities.
     * @param startCity The starting city index.
     */
    Specimen(const int &numOfCities, const int &startCity);

    /**
     * @brief Constructs a Specimen with a given path.
     * @param path The sequence of cities representing the path.
     */
    Specimen(const std::vector<int> &path);

    /**
     * @brief Default destructor.
     */
    ~Specimen() = default;

    /**
     * @brief Getter for the path of the specimen.
     * @return The sequence of cities representing the path.
     */
    std::vector<int> getPath() const;

    /**
     * @brief Mutates the specimen's path with a given probability.
     * @param probability The probability of mutation (default is 10%).
     * @param numOfMutations The number of mutations to perform (default is 1).
     */
    void mutate(int probability = 10, int numOfMutations = 1);

    /**
     * @brief Calculates the fitness of the specimen based on a given distance matrix between cities.
     * @param citiesDistanceMatrix The matrix representing distances between cities.
     */
    void calcFitness(const std::vector<std::vector<int>> &citiesDistanceMatrix);
    
    /**
     * @brief Getter for the fitness of the specimen.
     * @return The fitness of the specimen.
     */
    int getFitness() const;

    /**
     * @brief Generates offspring by combining paths with another specimen.
     * @param other The other specimen to generate offspring with.
     * @return A pair of specimens representing offspring.
     */
    std::pair<Specimen, Specimen> generateOffspring(const Specimen &other) const;
};