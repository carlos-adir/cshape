#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "cshape/shape.h"




TEST(ParameterTest, ConstructorSingleton)
{
    const EmptyR2& empty = EmptyR2::getInstance();
    const WholeR2& whole = WholeR2::getInstance();
    
    EXPECT_TRUE(&empty == &EMPTYR2);
    EXPECT_TRUE(&whole == &WHOLER2);
}


TEST(ParameterTest, CompareSingleton)
{
    // EMPTY and WHOLE
    EXPECT_TRUE(EMPTYR2 == EMPTYR2);
    EXPECT_FALSE(EMPTYR2 == WHOLER2);
    EXPECT_FALSE(WHOLER2 == EMPTYR2);
    EXPECT_TRUE(WHOLER2 == WHOLER2);

    EXPECT_FALSE(EMPTYR2 != EMPTYR2);
    EXPECT_TRUE(EMPTYR2 != WHOLER2);
    EXPECT_TRUE(WHOLER2 != EMPTYR2);
    EXPECT_FALSE(WHOLER2 != WHOLER2);
}


TEST(ParameterTest, BooleanSingleton)
{
    // UNION
    EXPECT_TRUE((EMPTYR2 | EMPTYR2) == EMPTYR2);
    EXPECT_TRUE((EMPTYR2 | WHOLER2) == WHOLER2);
    EXPECT_TRUE((WHOLER2 | EMPTYR2) == WHOLER2);
    EXPECT_TRUE((WHOLER2 | WHOLER2) == WHOLER2);

    // INTERSECT
    EXPECT_TRUE((EMPTYR2 & EMPTYR2) == EMPTYR2);
    EXPECT_TRUE((EMPTYR2 & WHOLER2) == EMPTYR2);
    EXPECT_TRUE((WHOLER2 & EMPTYR2) == EMPTYR2);
    EXPECT_TRUE((WHOLER2 & WHOLER2) == WHOLER2);

    // XOR
    EXPECT_TRUE((EMPTYR2 ^ EMPTYR2) == EMPTYR2);
    EXPECT_TRUE((EMPTYR2 ^ WHOLER2) == WHOLER2);
    EXPECT_TRUE((WHOLER2 ^ EMPTYR2) == WHOLER2);
    EXPECT_TRUE((WHOLER2 ^ WHOLER2) == EMPTYR2);

    // SUBTRACT
    EXPECT_TRUE((EMPTYR2 - EMPTYR2) == EMPTYR2);
    EXPECT_TRUE((EMPTYR2 - WHOLER2) == EMPTYR2);
    EXPECT_TRUE((WHOLER2 - EMPTYR2) == WHOLER2);
    EXPECT_TRUE((WHOLER2 - WHOLER2) == EMPTYR2);
}




TEST(ParameterTest, ContainsSingleton)
{
    EXPECT_TRUE(EMPTYR2.contains(EMPTYR2));
    EXPECT_FALSE(EMPTYR2.contains(WHOLER2));
    EXPECT_TRUE(WHOLER2.contains(EMPTYR2));
    EXPECT_TRUE(WHOLER2.contains(WHOLER2));
};
