#pragma once

#include "Specimen.hpp"
#include <fstream>
#include <sstream>
#include <vector>

class Population {
  private:
    static std::vector<std::vector<int>> cities;
    static int startCity;
    std::vector<Specimen> population;

  public:
    Population() = delete;
    Population(const int &populationSize);
    ~Population() = default;
    int getPopulationSize() const;
    static void setStartCity(const int &startCity);
    static int getStartCity();
    static void readCities(const std::string &fileName);
    static std::vector<std::vector<int>> getCitiesDistanceMatrix();
    static void setCitiesDistanceMatrix(const std::vector<std::vector<int>> &citiesDistanceMatrix);
};
