#pragma once
#include <algorithm>
#include <random>
#include <vector>
#include <ranges>

class Specimen {
  private:
    std::minstd_rand0 rng = std::default_random_engine{};
    std::vector<int> path;
    int fitness;

  public:
    Specimen() = delete;
    Specimen(const int &numOfCities, const int &startCity);
    ~Specimen() = default;

    std::vector<int> getPath() const;
    void mutate(int probability = 10, int numOfMutations = 1);
    void calcFitness(const std::vector<std::vector<int>> &citiesDistanceMatrix);
    int getFitness() const;
};