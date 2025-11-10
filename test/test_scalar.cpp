#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "cshape/loggers.h"
#include "cshape/scalar.h"




TEST(ScalarTest, ConstructorSingleton)
{
    EXPECT_TRUE(0 < POSINF);
    EXPECT_TRUE(NEGINF < 0);
}


TEST(ScalarTest, CompareSingleton)
{
    // BOT with BOT
    EXPECT_TRUE(NEGINF == NEGINF);
    EXPECT_FALSE(NEGINF != NEGINF);
    EXPECT_FALSE(NEGINF < NEGINF);
    EXPECT_TRUE(NEGINF <= NEGINF);
    EXPECT_TRUE(NEGINF >= NEGINF);
    EXPECT_FALSE(NEGINF > NEGINF);

    // TOP with TOP
    EXPECT_TRUE(POSINF == POSINF);
    EXPECT_FALSE(POSINF != POSINF);
    EXPECT_FALSE(POSINF < POSINF);
    EXPECT_TRUE(POSINF <= POSINF);
    EXPECT_TRUE(POSINF >= POSINF);
    EXPECT_FALSE(POSINF > POSINF);

    // BOT with TOP
    EXPECT_FALSE(NEGINF == POSINF);
    EXPECT_TRUE(NEGINF != POSINF);
    EXPECT_TRUE(NEGINF < POSINF);
    EXPECT_TRUE(NEGINF <= POSINF);
    EXPECT_FALSE(NEGINF >= POSINF);
    EXPECT_FALSE(NEGINF > POSINF);
    
    // TOP with BOT
    EXPECT_FALSE(POSINF == NEGINF);
    EXPECT_TRUE(POSINF != NEGINF);
    EXPECT_FALSE(POSINF < NEGINF);
    EXPECT_FALSE(POSINF <= NEGINF);
    EXPECT_TRUE(POSINF >= NEGINF);
    EXPECT_TRUE(POSINF > NEGINF);
}


TEST(ScalarTest, CompareIntInfinity)
{
    int finite = 10;

    EXPECT_TRUE(NEGINF < finite);
    EXPECT_TRUE(NEGINF <= finite);
    EXPECT_FALSE(NEGINF >= finite);
    EXPECT_FALSE(NEGINF > finite);
    EXPECT_FALSE(NEGINF == finite);
    EXPECT_TRUE(NEGINF != finite);
    
    EXPECT_FALSE(finite < NEGINF);
    EXPECT_FALSE(finite <= NEGINF);
    EXPECT_TRUE(finite >= NEGINF);
    EXPECT_TRUE(finite > NEGINF);
    EXPECT_FALSE(finite == NEGINF);
    EXPECT_TRUE(finite != NEGINF);

    EXPECT_FALSE(POSINF < finite);
    EXPECT_FALSE(POSINF <= finite);
    EXPECT_TRUE(POSINF >= finite);
    EXPECT_TRUE(POSINF > finite);
    EXPECT_FALSE(POSINF == finite);
    EXPECT_TRUE(POSINF != finite);
    
    EXPECT_TRUE(finite < POSINF);
    EXPECT_TRUE(finite <= POSINF);
    EXPECT_FALSE(finite >= POSINF);
    EXPECT_FALSE(finite > POSINF);
    EXPECT_FALSE(finite == POSINF);
    EXPECT_TRUE(finite != POSINF);
}

TEST(ScalarTest, CompareDoubleInfinity)
{
    double finite = 10;

    EXPECT_TRUE(NEGINF < finite);
    EXPECT_TRUE(NEGINF <= finite);
    EXPECT_FALSE(NEGINF >= finite);
    EXPECT_FALSE(NEGINF > finite);
    EXPECT_FALSE(NEGINF == finite);
    EXPECT_TRUE(NEGINF != finite);
    
    EXPECT_FALSE(finite < NEGINF);
    EXPECT_FALSE(finite <= NEGINF);
    EXPECT_TRUE(finite >= NEGINF);
    EXPECT_TRUE(finite > NEGINF);
    EXPECT_FALSE(finite == NEGINF);
    EXPECT_TRUE(finite != NEGINF);

    EXPECT_FALSE(POSINF < finite);
    EXPECT_FALSE(POSINF <= finite);
    EXPECT_TRUE(POSINF >= finite);
    EXPECT_TRUE(POSINF > finite);
    EXPECT_FALSE(POSINF == finite);
    EXPECT_TRUE(POSINF != finite);
    
    EXPECT_TRUE(finite < POSINF);
    EXPECT_TRUE(finite <= POSINF);
    EXPECT_FALSE(finite >= POSINF);
    EXPECT_FALSE(finite > POSINF);
    EXPECT_FALSE(finite == POSINF);
    EXPECT_TRUE(finite != POSINF);
}


TEST(ScalarTest, FromString)
{
    
    EXPECT_EQ(string_to_scalar("-10"), -10);
    EXPECT_EQ(string_to_scalar("-5"), -5);
    EXPECT_EQ(string_to_scalar("-1"), -1);
    EXPECT_EQ(string_to_scalar("-0"), 0);
    EXPECT_EQ(string_to_scalar("+0"), 0);
    EXPECT_EQ(string_to_scalar("+1"), 1);
    EXPECT_EQ(string_to_scalar("+5"), 5);

}