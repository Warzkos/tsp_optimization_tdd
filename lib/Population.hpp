#pragma once

#include <fstream>
#include <vector>
#include <sstream>
#include "Specimen.hpp"

class Population {
private:
    static std::vector<std::vector<int>> cities;
public:
    static void readCities(const std::string &fileName);
    static std::vector<std::vector<int>> getCities();
};
