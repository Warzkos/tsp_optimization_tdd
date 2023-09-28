#include <gtest/gtest.h>
#include "../lib/Specimen.hpp"

TEST(SpecimenClass, ConstructorAndGetPath){
    EXPECT_FALSE(std::is_default_constructible<Specimen>::value);
    Specimen s = Specimen(4, 2);
    int pathLength = static_cast<int>(s.getPath().size());
    EXPECT_EQ(pathLength, 5);
    EXPECT_EQ(s.getPath()[0], 2);
    EXPECT_EQ(s.getPath()[pathLength-1], 2);
    EXPECT_NE(s.getPath(), std::vector<int>({2,0,1,3,2}));
}