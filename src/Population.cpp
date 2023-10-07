#include "../lib/Population.hpp"

std::vector<std::vector<int>> Population::cities;

int Population::startCity = 0;

Population::Population(const int &populationSize) {
    if(cities.empty()){
        throw std::invalid_argument("CitiesDistanceMatrix not found; Use Population::readCities() or Population::setCitiesDistanceMatrix()");
    } else {
        for (int i = 0; i < populationSize; i++) {
            population.push_back(Specimen(cities.size(), startCity));
        }
        _startCity = startCity;
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

std::vector<Specimen> Population::getPopulation() const { return population; }

int Population::getStartCity() const { return _startCity; }

void Population::addSpecimenToPopulation(const Specimen &specimen) {
    if (specimen.getPath().size() != cities.size() + 1) {
        throw std::invalid_argument("Specimen path size must be equal to the number of cities + 1");
    }
    if (specimen.getPath().front() != _startCity) {
        throw std::invalid_argument("Specimen start city is different than populations start city");
    }
    population.push_back(specimen);
}

void Population::calcFitness() {
    for (auto &specimen : population) {
        specimen.calcFitness(cities);
    }
}

void Population::sort() {
    std::sort(population.begin(), population.end(),
              [](const Specimen &a, const Specimen &b) {
                  return a.getFitness() < b.getFitness();
              });
}

void Population::setStaticStartCity(const int &startCity) { 
    if(!(startCity>cities.size())){
        Population::startCity = startCity; 
    } else {
        throw std::invalid_argument("Start city out of range; Check if CitiesDistanceMatrix is set");
    }
}

int Population::getStaticStartCity() { return startCity; }

Specimen Population::getBestSpecimen(){
    Population::calcFitness();
    return *(std::min_element(population.begin(), population.end(), [](const Specimen &a, const Specimen &b){
        return a.getFitness() < b.getFitness();
    }));
}

std::vector<std::pair<int, int>> generateParentIndexes(int numberOfParents, int populationSize) {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(0, populationSize - 1);

    std::unordered_set<int> parentIndexes = {};

    while(parentIndexes.size() < numberOfParents){
        parentIndexes.insert(distr(generator));
    }

    std::vector<std::pair<int, int>> parentPairsIndexes = {};

    for (auto it = parentIndexes.begin(); it!=parentIndexes.end(); ++it) {
        parentPairsIndexes.push_back(std::make_pair(*it, *(it++)));
    }

    return parentPairsIndexes;
}

void Population::nextGeneration(const int &substitutionPercent, const int &mutationChance, const int &numOfMutations) {
    Population::calcFitness();
    Population::sort();

    auto numberOfSubstitutedSpecimens = population.size() * 25 / 100;
    if (numberOfSubstitutedSpecimens%2==1) {
        numberOfSubstitutedSpecimens-=1;
    }

    population.erase(population.begin()+population.size()-numberOfSubstitutedSpecimens, population.end());
        
    std::vector<std::pair<int, int>> parentPairsIndexes = generateParentIndexes(numberOfSubstitutedSpecimens, population.size());

    for(auto &parentPairIndexes: parentPairsIndexes){
        std::pair<Specimen, Specimen> offspring = population[parentPairIndexes.first].generateOffspring(population[parentPairIndexes.second]);
        offspring.first.mutate(mutationChance, numOfMutations);
        offspring.second.mutate(mutationChance, numOfMutations);
        population.push_back(offspring.first);
        population.push_back(offspring.second);
    }
}