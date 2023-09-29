#include "../lib/Population.hpp"

std::vector<std::vector<int>> Population::cities;

void Population::readCities(const std::string &fileName) {
    cities.clear();
    std::ifstream file(fileName);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<int> city;
            std::stringstream ss(line);
            int distance;
            while (ss >> distance) {
                city.push_back(distance);
            }
            cities.push_back(city);
        }
    } else {
        throw std::invalid_argument("File not found; Check file name");
    }
}

void Population::setCitiesDistanceMatrix(const std::vector<std::vector<int>> &citiesDistanceMatrix) {
    cities = citiesDistanceMatrix;
}

std::vector<std::vector<int>> Population::getCities() { return cities; }