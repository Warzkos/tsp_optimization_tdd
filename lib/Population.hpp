#pragma once

#include "Specimen.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_set>

class Population {
  private:
    static std::vector<std::vector<int>> cities;
    static int startCity;
    int _startCity;
    std::vector<Specimen> population;

  public:
    Population() = delete;
    Population(const int &populationSize);
    ~Population() = default;
    std::vector<Specimen> getPopulation() const;
    int getStartCity() const;
    void addSpecimenToPopulation(const Specimen &specimen);
    void calcFitness();
    void sort();
    Specimen getBestSpecimen();
    void nextGeneration(const int &substitutionPercent = 25, const int &mutationChance = 10, const int &numOfMutations = 1);
    static void setStaticStartCity(const int &startCity);
    static int getStaticStartCity();
    static void readCities(const std::string &fileName);
    static std::vector<std::vector<int>> getCitiesDistanceMatrix();
    static void setCitiesDistanceMatrix(const std::vector<std::vector<int>> &citiesDistanceMatrix);
};
