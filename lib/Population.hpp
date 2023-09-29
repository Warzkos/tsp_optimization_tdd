#pragma once

#include "Specimen.hpp"
#include <fstream>
#include <sstream>
#include <vector>

class Population {
  private:
    static std::vector<std::vector<int>> cities;

  public:
    static void readCities(const std::string &fileName);
    static std::vector<std::vector<int>> getCities();
    static void setCitiesDistanceMatrix(const std::vector<std::vector<int>> &citiesDistanceMatrix);
};
