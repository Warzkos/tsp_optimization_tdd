#pragma once

#include "Specimen.hpp"
#include <fstream>
#include <sstream>
#include <vector>

class Population {
  private:
    static std::vector<std::vector<int>> cities;
    std::vector<Specimen> population;

  public:
    Population() = delete;
    Population(const int &populationSize);
    ~Population() = default;
    int getPopulationSize() const;
    static void readCities(const std::string &fileName);
    static std::vector<std::vector<int>> getCitiesDistanceMatrix();
    static void setCitiesDistanceMatrix(const std::vector<std::vector<int>> &citiesDistanceMatrix);
};
