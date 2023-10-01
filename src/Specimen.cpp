#include "../lib/Specimen.hpp"

std::minstd_rand0 Specimen::rng = std::default_random_engine{};

Specimen::Specimen(const int &numOfCities, const int &startCity) {
    path.push_back(startCity);
    for (int i = 0; i < numOfCities; i++) {
        if (i != startCity) {
            path.push_back(i);
        }
    }
    path.push_back(startCity);

    std::shuffle(path.begin() + 1, path.end() - 1, rng);
}

Specimen::Specimen(const std::vector<int> &path) {
    if (path.front() != path.back()) {
        throw std::invalid_argument("Path must start and end with the same city");
    }
    for (int i = 0; i < path.size()-1; i++) {
        if (std::count(path.begin(), path.end(), i) != 1 && i != path.front()) {
            throw std::invalid_argument("Path must contain each city exactly once");
        }
    }
    this->path = path;
}

std::vector<int> Specimen::getPath() const { return path; }

void Specimen::mutate(int probability, int numOfMutations) {
    for (int i = 0; i < numOfMutations; i++) {
        if (rng() % 100 < probability) {
            int firstCity = rng() % (path.size() - 2) + 1;
            int secondCity = rng() % (path.size() - 2) + 1;
            std::swap(path[firstCity], path[secondCity]);
        }
    }
}

void Specimen::calcFitness(const std::vector<std::vector<int>> &citiesDistanceMatrix) {
    auto fitness = 0;
    auto prevCity = path.front();
    for (auto city : path | std::views::drop(1)) {
        fitness += citiesDistanceMatrix[prevCity][city];
        prevCity = city;
    }
    this->fitness = fitness;
}

int Specimen::getFitness() const { return fitness; }

std::vector<int> codeGenes(const auto &path){
    std::vector<int> genes(path.size(), 0);
    for (int i = 0; i < path.size(); ++i) {
        for(int m = 0; path[m] != i; ++m){
            if(path[m] > i){
                ++genes[i];
            }
        }
    }
    return genes;
}

std::vector<int> decodeGenes(const std::vector<int> &genes){
    std::vector<int> position(genes.size(), 0);
    for (int i = genes.size()-1; i >= 0; --i) {
        for (int m = i; m < genes.size(); ++m) {
            if (position[m] >= genes[i]) {
                ++position[m];
            }
            position[i] = genes[i];
        }
    }

    std::vector<int> path(genes.size(), 0);
    for (int i = 0; i < genes.size(); ++i) {
        path[position[i]] = i;
    }
    path.insert(path.begin(), path.back());
    return path;
}


std::pair<Specimen, Specimen> Specimen::generateOffspring(const Specimen &otherParent) const {

    if(path.size() != otherParent.getPath().size()){
        throw std::invalid_argument("Specimens must have the same path size");
    }
    if(path.front() != otherParent.getPath().front() || path.back() != otherParent.getPath().back()){
        throw std::invalid_argument("Specimens must have the same start city");
    }

    auto genesParent1 = codeGenes(path | std::views::drop(1));
    auto otherParentPath = otherParent.getPath();
    auto genesParent2 = codeGenes(otherParentPath | std::views::drop(1));

    std::uniform_int_distribution<int> distribution(1, genesParent1.size()-1);  
    std::swap_ranges(genesParent1.begin(), genesParent1.begin()+distribution(rng), genesParent2.begin());

    std::pair<Specimen, Specimen> offspring = {
        Specimen(decodeGenes(genesParent1)),
        Specimen(decodeGenes(genesParent2))
    };

    return offspring;
}