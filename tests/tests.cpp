#include <gtest/gtest.h>
#include "../lib/Specimen.hpp"

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