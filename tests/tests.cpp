#include <gtest/gtest.h>
#include "../lib/Specimen.hpp"

namespace{
    int GetMeaningOfLife() {return 42;}
}

TEST(LifeMeaning, getMeaningOfLife){
    ASSERT_EQ(GetMeaningOfLife(), 42);
}

TEST(Specimen, Constructor){
    EXPECT_FALSE(std::is_default_constructible<Specimen>::value);
    Specimen s = Specimen(4);
    EXPECT_EQ(s.getNumberOfCities(), 4);
}