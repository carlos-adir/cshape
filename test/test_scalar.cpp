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


TEST(AngleTest, Constructor)
{
    Angle::turns(0);
    Angle::turns(0.1);
    Angle::turns(0.125);
    Angle::turns(0.25);
    Angle::turns(0.375);
    Angle::turns(0.5);
    Angle::turns(0.675);
    Angle::turns(0.875);
    Angle::turns(1);
    Angle::turns(-0.1);
    Angle::turns(-0.125);
    Angle::turns(-0.25);
    Angle::turns(-0.375);
    Angle::turns(-0.5);
    Angle::turns(-0.675);
    Angle::turns(-0.875);
    Angle::turns(-1);


    Angle::degrees(0);
    Angle::degrees(15);
    Angle::degrees(30);
    Angle::degrees(45);
    Angle::degrees(60);
    Angle::degrees(90);
    Angle::degrees(135);
    Angle::degrees(180);
    Angle::degrees(225);
    Angle::degrees(270);
    Angle::degrees(314);
    Angle::degrees(315);
    Angle::degrees(360);
    Angle::degrees(390);
    Angle::degrees(780);
    Angle::degrees(-15);
    Angle::degrees(-30);
    Angle::degrees(-45);
    Angle::degrees(-60);
    Angle::degrees(-90);
    Angle::degrees(-135);
    Angle::degrees(-180);
    Angle::degrees(-225);
    Angle::degrees(-270);
    Angle::degrees(-314);
    Angle::degrees(-315);
    Angle::degrees(-360);
    Angle::degrees(-390);
    Angle::degrees(-780);


    Angle::radians(0);
    Angle::radians(15);
    Angle::radians(30);
    Angle::radians(45);
    Angle::radians(60);
    Angle::radians(90);
    Angle::radians(135);
    Angle::radians(180);
    Angle::radians(225);
    Angle::radians(270);
    Angle::radians(314);
    Angle::radians(315);
    Angle::radians(360);
    Angle::radians(390);
    Angle::radians(780);
    Angle::radians(-15);
    Angle::radians(-30);
    Angle::radians(-45);
    Angle::radians(-60);
    Angle::radians(-90);
    Angle::radians(-135);
    Angle::radians(-180);
    Angle::radians(-225);
    Angle::radians(-270);
    Angle::radians(-314);
    Angle::radians(-315);
    Angle::radians(-360);
    Angle::radians(-390);
    Angle::radians(-780);
}


TEST(AngleTest, Compare)
{
    EXPECT_EQ(Angle::turns(0), Angle::turns(0));
    EXPECT_EQ(Angle::turns(0), Angle::turns(1));
    EXPECT_EQ(Angle::turns(0), Angle::turns(2));
    EXPECT_EQ(Angle::turns(0), Angle::turns(3));
    EXPECT_EQ(Angle::turns(0), Angle::turns(-1));
    EXPECT_EQ(Angle::turns(0), Angle::turns(-2));
    EXPECT_EQ(Angle::turns(0), Angle::turns(-3));

    EXPECT_EQ(Angle::degrees(0), Angle::degrees(0));
    EXPECT_EQ(Angle::degrees(0), Angle::degrees(360));
    EXPECT_EQ(Angle::degrees(0), Angle::degrees(720));
    EXPECT_EQ(Angle::degrees(0), Angle::degrees(1080));
    EXPECT_EQ(Angle::degrees(0), Angle::degrees(-360));
    EXPECT_EQ(Angle::degrees(0), Angle::degrees(-720));
    EXPECT_EQ(Angle::degrees(0), Angle::degrees(-1080));

    EXPECT_EQ(Angle::radians(0), Angle::radians(0));
    EXPECT_EQ(Angle::radians(0), Angle::radians(TAU));
    EXPECT_EQ(Angle::radians(0), Angle::radians(2*TAU));
    EXPECT_EQ(Angle::radians(0), Angle::radians(3*TAU));
    EXPECT_EQ(Angle::radians(0), Angle::radians(-TAU));
    EXPECT_EQ(Angle::radians(0), Angle::radians(-2*TAU));
    EXPECT_EQ(Angle::radians(0), Angle::radians(-3*TAU));

    EXPECT_EQ(Angle::turns(0.000), Angle::degrees(0));
    EXPECT_EQ(Angle::turns(0.125), Angle::degrees(45));
    EXPECT_EQ(Angle::turns(0.250), Angle::degrees(90));
    EXPECT_EQ(Angle::turns(0.375), Angle::degrees(135));
    EXPECT_EQ(Angle::turns(0.500), Angle::degrees(180));
    EXPECT_EQ(Angle::turns(0.625), Angle::degrees(225));
    EXPECT_EQ(Angle::turns(0.750), Angle::degrees(270));
    EXPECT_EQ(Angle::turns(0.875), Angle::degrees(315));
    EXPECT_EQ(Angle::turns(1.000), Angle::degrees(360));
}



TEST(AngleTest, ExtractBack)
{
    EXPECT_EQ(Angle::turns(0.000).turns(), 0);
    EXPECT_EQ(Angle::turns(0.125).turns(), 0.125);
    EXPECT_EQ(Angle::turns(0.250).turns(), 0.250);
    EXPECT_EQ(Angle::turns(0.375).turns(), 0.375);
    EXPECT_EQ(Angle::turns(0.500).turns(), 0.500);
    EXPECT_EQ(Angle::turns(0.625).turns(), -0.375);
    EXPECT_EQ(Angle::turns(0.750).turns(), -0.250);
    EXPECT_EQ(Angle::turns(0.875).turns(), -0.125);
    EXPECT_EQ(Angle::turns(1.000).turns(), 0.000);
}



TEST(AngleTest, SinCos)
{
    const Scalar cos45 = (Scalar)M_SQRT1_2;
    const Scalar cos30 = (Scalar)sqrtf128(3) / 2;

    EXPECT_NEAR(Angle::degrees(0).cos(), 1, 1e-15);
    EXPECT_NEAR(Angle::degrees(30).cos(), cos30, 1e-15);
    EXPECT_NEAR(Angle::degrees(45).cos(), cos45, 1e-15);
    EXPECT_NEAR(Angle::degrees(60).cos(), 0.5, 1e-15);
    EXPECT_NEAR(Angle::degrees(90).cos(), 0, 1e-15);
    EXPECT_NEAR(Angle::degrees(120).cos(), -0.5, 1e-15);
    EXPECT_NEAR(Angle::degrees(135).cos(), -cos45, 1e-15);
    EXPECT_NEAR(Angle::degrees(150).cos(), -cos30, 1e-15);
    EXPECT_NEAR(Angle::degrees(180).cos(), -1, 1e-15);
    EXPECT_NEAR(Angle::degrees(210).cos(), -cos30, 1e-15);
    EXPECT_NEAR(Angle::degrees(225).cos(), -cos45, 1e-15);
    EXPECT_NEAR(Angle::degrees(240).cos(), -0.5, 1e-15);
    EXPECT_NEAR(Angle::degrees(270).cos(), 0, 1e-15);
    EXPECT_NEAR(Angle::degrees(300).cos(), 0.5, 1e-15);
    EXPECT_NEAR(Angle::degrees(315).cos(), cos45, 1e-15);
    EXPECT_NEAR(Angle::degrees(330).cos(), cos30, 1e-15);
    EXPECT_NEAR(Angle::degrees(360).cos(), 1, 1e-15);

    EXPECT_NEAR(Angle::degrees(0).sin(), 0, 1e-15);
    EXPECT_NEAR(Angle::degrees(30).sin(), 0.5, 1e-15);
    EXPECT_NEAR(Angle::degrees(45).sin(), cos45, 1e-15);
    EXPECT_NEAR(Angle::degrees(60).sin(), cos30, 1e-15);
    EXPECT_NEAR(Angle::degrees(90).sin(), 1, 1e-15);
    EXPECT_NEAR(Angle::degrees(120).sin(), cos30, 1e-15);
    EXPECT_NEAR(Angle::degrees(135).sin(), cos45, 1e-15);
    EXPECT_NEAR(Angle::degrees(150).sin(), 0.5, 1e-15);
    EXPECT_NEAR(Angle::degrees(180).sin(), 0, 1e-15);
    EXPECT_NEAR(Angle::degrees(210).sin(), -0.5, 1e-15);
    EXPECT_NEAR(Angle::degrees(225).sin(), -cos45, 1e-15);
    EXPECT_NEAR(Angle::degrees(240).sin(), -cos30, 1e-15);
    EXPECT_NEAR(Angle::degrees(270).sin(), -1, 1e-15);
    EXPECT_NEAR(Angle::degrees(300).sin(), -cos30, 1e-15);
    EXPECT_NEAR(Angle::degrees(315).sin(), -cos45, 1e-15);
    EXPECT_NEAR(Angle::degrees(330).sin(), -0.5, 1e-15);
    EXPECT_NEAR(Angle::degrees(360).sin(), 0, 1e-15);
}



TEST(AngleTest, SumAngles)
{
    const Angle deg00 = Angle::degrees(00);
    const Angle deg05 = Angle::degrees(05);
    const Angle deg10 = Angle::degrees(10);
    const Angle deg15 = Angle::degrees(15);
    const Angle deg30 = Angle::degrees(30);
    const Angle deg45 = Angle::degrees(45);
    const Angle deg60 = Angle::degrees(60);
    const Angle deg90 = Angle::degrees(60);

    EXPECT_EQ(deg00 + deg00, deg00);
    EXPECT_EQ(deg00 + deg05, deg05);
    EXPECT_EQ(deg05 + deg00, deg05);
    EXPECT_EQ(deg05 + deg05, deg10);
    EXPECT_EQ(deg00 + deg10, deg10);
    EXPECT_EQ(deg10 + deg00, deg10);
    EXPECT_EQ(deg05 + deg10, deg15);
    EXPECT_EQ(deg10 + deg05, deg15);

    EXPECT_EQ(deg15 + deg15, deg30);
    EXPECT_EQ(deg30 + deg15, deg45);
    EXPECT_EQ(deg15 + deg30, deg45);
    EXPECT_EQ(deg30 + deg30, deg60);
    EXPECT_EQ(deg30 + deg60, deg90);
    EXPECT_EQ(deg45 + deg45, deg90);
    EXPECT_EQ(deg60 + deg30, deg90);
}


TEST(AngleTest, Arg)
{
    EXPECT_EQ(Angle::arg(0, 0), Angle::degrees(0));
}


