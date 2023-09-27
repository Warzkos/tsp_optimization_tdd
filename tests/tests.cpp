#include <gtest/gtest.h>

namespace{
    int GetMeaningOfLife() {return 42;}
}

TEST(LifeMeaning, getMeaningOfLife){
    ASSERT_EQ(GetMeaningOfLife(), 42);
}