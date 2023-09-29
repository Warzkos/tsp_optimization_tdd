#include "../lib/Population.hpp"

std::vector<std::vector<int>> Population::cities;

void Population::readCities(const std::string &fileName){
    cities.clear();
    std::ifstream file(fileName);
    std::string line;
    while(std::getline(file, line)){
        std::vector<int> city;
        std::stringstream ss(line);
        int distance;
        while(ss >> distance){
            city.push_back(distance);
        }
        cities.push_back(city);
    }
}

std::vector<std::vector<int>> Population::getCities(){
    return cities;
}