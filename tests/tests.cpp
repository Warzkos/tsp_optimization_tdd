#include <gtest/gtest.h>
#include "../lib/Specimen.hpp"
#include "../lib/Population.hpp"

struct SpecimenClass : public ::testing::Test{
    Specimen s = Specimen(4, 2);
};

TEST(SpecimenConstructor, NoDefaultConstructor){
    EXPECT_FALSE(std::is_default_constructible<Specimen>::value);
}

TEST_F(SpecimenClass, GetPath){
    int pathLength = static_cast<int>(s.getPath().size());
    EXPECT_EQ(pathLength, 5);
    EXPECT_EQ(s.getPath().front(), 2);
    EXPECT_EQ(s.getPath().back(), 2);
    EXPECT_NE(s.getPath(), std::vector<int>({2,0,1,3,2}));
}

TEST_F(SpecimenClass, Mutate){
    for (int i = 0; i < 100; i++){
        s.mutate();
    }
    EXPECT_EQ(s.getPath().front(), 2);
    EXPECT_EQ(s.getPath().back(), 2);
    EXPECT_NE(s.getPath(), std::vector<int>({2,0,1,3,2}));
}

TEST(PopulationClass, CityReader){
    std::vector<std::vector<int>> actualCities = {
        {999, 2, 8, 4}, 
        {2, 999, 3, 5}, 
        {8, 3, 999, 6}, 
        {4, 5, 6, 999}
    };
    Population::readCities("cities.txt");
    EXPECT_EQ(Population::getCities(), actualCities);

    Population::readCities("cities.txt");
    EXPECT_EQ(Population::getCities(), actualCities);
}