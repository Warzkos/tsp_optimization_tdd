#include "../lib/Population.hpp"
#include "../lib/Specimen.hpp"
#include <gtest/gtest.h>
#include <ranges>
#include <algorithm>

struct SpecimenClass : public ::testing::Test {
    Specimen s = Specimen(4, 2);
};

TEST(SpecimenConstructor, NoDefaultConstructor) {
    EXPECT_FALSE(std::is_default_constructible<Specimen>::value);
}

TEST(SpecimenConstructor, PathConstructor) {
    EXPECT_NO_THROW(Specimen s = Specimen(std::vector<int>({2, 1, 3, 0, 2})));
    EXPECT_THROW(Specimen s = Specimen(std::vector<int>({2, 1, 3, 0, 1})),
                 std::invalid_argument);
    EXPECT_THROW(Specimen s = Specimen(std::vector<int>({2, 1, 3, 4, 2})),
                 std::invalid_argument);
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

TEST_F(SpecimenClass, SpecimensAreDifferent) {
    Specimen s2 = Specimen(4, 2);
    auto sPath = s.getPath();
    auto s2Path = s2.getPath();
    EXPECT_NE(sPath, s2Path);
}

TEST(PopulationClassTest, PopulationConstructor) {
    EXPECT_FALSE(std::is_default_constructible<Population>::value);
    EXPECT_THROW(Population population = Population(100),
                 std::invalid_argument);
}

TEST(PopulationClassTest, StartCityDefaultValue) {
    EXPECT_EQ(Population::getStaticStartCity(), 0);
}

struct PopulationClass : public ::testing::Test {
    std::vector<std::vector<int>> actualCities = {
        {999, 2, 8, 4}, {2, 999, 3, 5}, {8, 3, 999, 6}, {4, 5, 6, 999}};
};

TEST_F(PopulationClass, GetPopulationAndConstructor) {
    Population::setCitiesDistanceMatrix(actualCities);
    Population population = Population(100);
    EXPECT_EQ(population.getPopulation().size(), 100);
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

TEST_F(PopulationClass, SetStaticStartCity) {
    EXPECT_THROW(Population::setStaticStartCity(10), std::invalid_argument);
    Population::setStaticStartCity(3);
    EXPECT_EQ(Population::getStaticStartCity(), 3);
}

TEST_F(PopulationClass, GetStartCity) {
    Population::setStaticStartCity(3);
    Population p = Population(5);
    Population::setStaticStartCity(1);
    EXPECT_EQ(p.getStartCity(), 3);
}

TEST_F(PopulationClass, AddSpecimenToPopulation) {
    Population::setCitiesDistanceMatrix(actualCities);
    Population::setStaticStartCity(1);
    Population p = Population(5);
    Specimen s = Specimen(4, 2);
    EXPECT_THROW(p.addSpecimenToPopulation(s), std::invalid_argument);
    s = Specimen(3, 1);
    EXPECT_THROW(p.addSpecimenToPopulation(s), std::invalid_argument);
    s = Specimen(4, 1);
    EXPECT_NO_THROW(p.addSpecimenToPopulation(s));
}

TEST_F(PopulationClass, CalcPopulationFitness) {
    Population::setCitiesDistanceMatrix(actualCities);
    Population p = Population(100);
    auto population = p.getPopulation();
    EXPECT_TRUE(std::all_of(population.begin(), population.end(), [](const Specimen &s) {
        return s.getFitness() == 0;
    }));
    p.calcFitness();
    population = p.getPopulation();
    EXPECT_TRUE(std::all_of(population.begin(), population.end(), [](const Specimen &s) {
        return s.getFitness() != 0;
    }));
}

TEST_F(PopulationClass, SortPopulationByFitnessScore) {
    Population::setCitiesDistanceMatrix(actualCities);
    Population p = Population(100);
    p.calcFitness();
    p.sort();
    auto population = p.getPopulation();
    EXPECT_TRUE(std::is_sorted(population.begin(), population.end(), [](const Specimen &a, const Specimen &b) {
        return a.getFitness() < b.getFitness();
    }));
}

TEST(SpecimenClassTest, GenerateOffspring) {
    Specimen parent1 = Specimen(std::vector<int>({1, 2, 6, 4, 5, 3, 0, 1}));
    Specimen parent2 = Specimen(std::vector<int>({1, 4, 0, 3, 6, 2, 5, 1}));

    Specimen incompatibleParent1 =
        Specimen(std::vector<int>({0, 2, 6, 4, 5, 3, 1, 0}));
    Specimen incompatibleParent2 =
        Specimen(std::vector<int>({1, 4, 0, 3, 2, 5, 1}));

    EXPECT_THROW(parent1.generateOffspring(incompatibleParent1),
                 std::invalid_argument);
    EXPECT_THROW(parent1.generateOffspring(incompatibleParent2),
                 std::invalid_argument);

    std::pair<Specimen, Specimen> offspring =
        parent1.generateOffspring(parent2);

    std::vector<std::pair<Specimen, Specimen>> possibleOffspring = {
        std::pair<Specimen, Specimen>(
            Specimen(std::vector<int>({1, 2, 0, 6, 4, 5, 3, 1})),
            Specimen(std::vector<int>({1, 4, 3, 6, 2, 5, 0, 1}))),
        std::pair<Specimen, Specimen>(
            Specimen(std::vector<int>({1, 6, 0, 4, 5, 2, 3, 1})),
            Specimen(std::vector<int>({1, 2, 4, 3, 6, 5, 0, 1}))),
        std::pair<Specimen, Specimen>(
            Specimen(std::vector<int>({1, 6, 0, 3, 4, 2, 5, 1})),
            Specimen(std::vector<int>({1, 2, 4, 6, 5, 3, 0, 1}))),
        std::pair<Specimen, Specimen>(
            Specimen(std::vector<int>({1, 4, 0, 3, 6, 2, 5, 1})),
            Specimen(std::vector<int>({1, 2, 6, 4, 5, 3, 0, 1}))),
    };
    EXPECT_TRUE(
        std::any_of(possibleOffspring.begin(), possibleOffspring.end(),
                    [&offspring = std::as_const(offspring)](
                        std::pair<Specimen, Specimen> i) {
                        return i.first.getPath() == offspring.first.getPath() &&
                               i.second.getPath() == offspring.second.getPath();
                    }));
}

TEST(PopulationClassTest, CityReaderFileNameException) {
    EXPECT_THROW(Population::readCities("nonExistentFile.txt"),
                 std::invalid_argument);
}
