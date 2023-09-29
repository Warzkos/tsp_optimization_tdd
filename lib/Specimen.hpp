#pragma once
#include <algorithm>
#include <random>
#include <vector>

class Specimen {
  private:
    std::minstd_rand0 rng = std::default_random_engine{};
    std::vector<int> path;

  public:
    Specimen() = delete;
    Specimen(const int &numOfCities, const int &startCity);
    ~Specimen() = default;

    std::vector<int> getPath() const;
    void mutate(int probability = 10, int numOfMutations = 1);
};