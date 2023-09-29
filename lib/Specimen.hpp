#pragma once
#include <algorithm>
#include <random>
#include <vector>
#include <ranges>

class Specimen {
  private:
    static std::minstd_rand0 rng;
    std::vector<int> path;
    int fitness;

  public:
    Specimen() = delete;
    Specimen(const int &numOfCities, const int &startCity);
    Specimen(const std::vector<int> &path);
    ~Specimen() = default;

    std::vector<int> getPath() const;
    void mutate(int probability = 10, int numOfMutations = 1);
    void calcFitness(const std::vector<std::vector<int>> &citiesDistanceMatrix);
    int getFitness() const;
};