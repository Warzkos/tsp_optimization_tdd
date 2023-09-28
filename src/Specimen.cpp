#include "../lib/Specimen.hpp"

Specimen::Specimen(const int &numOfCities, const int &startCity){
    path.push_back(startCity);
    for(int i = 0; i < numOfCities; i++){
        if(i != startCity){
            path.push_back(i);
        }
    }
    path.push_back(startCity);

    std::shuffle(path.begin()+1, path.end()-1, rng);
}

std::vector<int> Specimen::getPath() const{
    return path;
}