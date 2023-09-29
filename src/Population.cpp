#include "../lib/Population.hpp"
#include <iostream>
std::vector<std::vector<int>> Population::cities;

Population::Population(const int &populationSize) {
    if(cities.empty()){
        throw std::invalid_argument("CitiesDistanceMatrix not found; Use Population::readCities() or Population::setCitiesDistanceMatrix()");
    } else {
        std::cout << cities.size() << std::endl;
        for (int i = 0; i < populationSize; i++) {
            population.push_back(Specimen(cities.size(), 0));
        }
    }
}

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

std::vector<std::vector<int>> Population::getCitiesDistanceMatrix() { return cities; }

int Population::getPopulationSize() const { return population.size(); }