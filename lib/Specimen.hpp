#pragma once
#include <vector>

class Specimen {
private:
    std::vector<int> path;
public:
    Specimen() = delete;
    Specimen(const int numOfCities);
    ~Specimen() = default;

    int getNumberOfCities() const;
};