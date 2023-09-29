#include "../lib/Specimen.hpp"

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