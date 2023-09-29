#include "../lib/Population.hpp"
#include "../lib/Specimen.hpp"
#include <gtest/gtest.h>
#include <ranges>

struct SpecimenClass : public ::testing::Test {
    Specimen s = Specimen(4, 2);
};

TEST(SpecimenConstructor, NoDefaultConstructor) {
    EXPECT_FALSE(std::is_default_constructible<Specimen>::value);
}

TEST_F(SpecimenClass, GetPath) {
    int pathLength = static_cast<int>(s.getPath().size());
    EXPECT_EQ(pathLength, 5);
    EXPECT_EQ(s.getPath().front(), 2);
    EXPECT_EQ(s.getPath().back(), 2);
    EXPECT_NE(s.getPath(), std::vector<int>({2, 0, 1, 3, 2}));
}

TEST_F(SpecimenClass, Mutate) {
    for (int i = 0; i < 100; i++) {
        s.mutate();
    }
    EXPECT_EQ(s.getPath().front(), 2);
    EXPECT_EQ(s.getPath().back(), 2);
    EXPECT_NE(s.getPath(), std::vector<int>({2, 0, 1, 3, 2}));
}

TEST_F(SpecimenClass, CalcFitness) {
    std::vector<std::vector<int>> citiesDistanceMatrix = {
        {999, 2, 8, 4}, {2, 999, 3, 5}, {8, 3, 999, 6}, {4, 5, 6, 999}};
    auto actualFitness = 0;
    auto path = s.getPath();
    auto prevCity = path.front();
    for (auto city : path | std::views::drop(1)) {
        actualFitness += citiesDistanceMatrix[prevCity][city];
        prevCity = city;
    }
    s.calcFitness(citiesDistanceMatrix);
    EXPECT_EQ(s.getFitness(), actualFitness);
}

TEST_F(SpecimenClass, SpecimensAreDifferent){
    Specimen s2 = Specimen(4, 2);
    auto sPath = s.getPath();
    auto s2Path = s2.getPath();
    EXPECT_NE(sPath, s2Path);
}

TEST(PopulationClassConstructor, PopulationConstructor) {
    EXPECT_FALSE(std::is_default_constructible<Population>::value);
    EXPECT_THROW(Population population = Population(100), std::invalid_argument);
}

struct PopulationClass : public ::testing::Test
{
    std::vector<std::vector<int>> actualCities = {
        {999, 2, 8, 4}, {2, 999, 3, 5}, {8, 3, 999, 6}, {4, 5, 6, 999}};
};


TEST_F(PopulationClass, PopulationConstructor) {

    Population::setCitiesDistanceMatrix(actualCities);
    Population population = Population(100);
    EXPECT_EQ(population.getPopulationSize(), 100);
}

TEST_F(PopulationClass, CityReader) {
    Population::readCities("cities.txt");
    EXPECT_EQ(Population::getCitiesDistanceMatrix(), actualCities);

    Population::readCities("cities.txt");
    EXPECT_EQ(Population::getCitiesDistanceMatrix(), actualCities);
}

TEST_F(PopulationClass, SetCitiesDistanceMatrix) {
    Population::setCitiesDistanceMatrix(actualCities);
    EXPECT_EQ(Population::getCitiesDistanceMatrix(), actualCities);
}


TEST(PopulationClassReader, CityReaderFileNameException) {
    EXPECT_THROW(Population::readCities("nonExistentFile.txt"),
                 std::invalid_argument);
}

TEST_F(PopulationClass, SetStartCity) {
    EXPECT_THROW(Population::setStartCity(10));
    Population::setStartCity(3);
    EXPECT_EQ(Population::getStartCity(), 3);
}

// TEST(PopulationClass, AddSpecimenToPopulation) {
//     Population population = Population();
//     Specimen s = Specimen(4, 2);
//     population.addSpecimenToPopulation(s);
// }