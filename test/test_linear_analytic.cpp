#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "cshape/analytic.h"

TEST(AnalyticTest, Constructor)
{
    LinearAnalytic<int, int> lineara;
    LinearAnalytic<int, int> linearb(10);
    LinearAnalytic<int, int> linearc = 10;

    std::vector<int> coefs;
    LinearAnalytic<int, int> lineard(coefs);
    coefs.push_back(10);
    coefs.push_back(-20);
    LinearAnalytic<int, int> lineare(coefs);
    
    LinearAnalytic<int, int> linearf({1, 0, 2});
    LinearAnalytic<int, int> linearg = {3, 0, 4};
}


TEST(LinearAnalyticTest, Degree)
{
    LinearAnalytic<int, int> lineara;
    EXPECT_EQ(lineara.degree(), 0);
    LinearAnalytic<int, int> linearb(0);
    EXPECT_EQ(linearb.degree(), 0);
    LinearAnalytic<int, int> linearc = 10;
    EXPECT_EQ(linearc.degree(), 0);

    std::vector<int> coefs;
    LinearAnalytic<int, int> lineard(coefs);
    EXPECT_EQ(lineard.degree(), 0);
    coefs.push_back(10);
    coefs.push_back(-20);
    LinearAnalytic<int, int> lineare(coefs);
    EXPECT_EQ(lineare.degree(), 1);
}


TEST(LinearAnalyticTest, CompareConstant)
{
    LinearAnalytic<int, int> linear = 10;
    EXPECT_EQ(linear.degree(), 0);
    EXPECT_TRUE(linear == 10);
    EXPECT_FALSE(linear == 20);
    EXPECT_FALSE(linear != 10);
    EXPECT_TRUE(linear != 20);

    EXPECT_TRUE(linear == 10.);
    EXPECT_FALSE(linear == 20.);
    EXPECT_FALSE(linear != 10.);
    EXPECT_TRUE(linear != 20.);
    EXPECT_EQ(linear.degree(), 0);
}

TEST(LinearAnalyticTest, OperateConstant)
{
    LinearAnalytic<int, int> linear = 10;

    EXPECT_TRUE(linear == 10);
    linear = 20;
    EXPECT_TRUE(linear == 20);
    EXPECT_TRUE(linear + 10 == 30);
    EXPECT_TRUE(linear - 5 == 15);
    EXPECT_TRUE(linear * 5 == 100);
}





TEST(LinearAnalyticTest, OperateIntDivideConst)
{
    LinearAnalytic<int, int> linear = 100;
    EXPECT_TRUE(linear / 2 == 50);
    EXPECT_TRUE(linear % 3 == 0);
    EXPECT_TRUE(linear == 100);

    linear /= 20;
    EXPECT_TRUE(linear == 5);
    linear %= 2;
    EXPECT_TRUE(linear == 0);
}


TEST(LinearAnalyticTest, AddLinear)
{
    LinearAnalytic<int, int> lineara = {1, 0, 2};
    LinearAnalytic<int, int> linearb = {3, 0, 4};
    LinearAnalytic<int, int> linearc = {4, 0, 6};

    EXPECT_TRUE(lineara + linearb == linearc);
}

TEST(LinearAnalyticTest, SubLinear)
{
    LinearAnalytic<int, int> lineara = {1, 0, 2};
    LinearAnalytic<int, int> linearb = {3, 0, 4};
    LinearAnalytic<int, int> linearc = {-2, 0, -2};

    EXPECT_TRUE(lineara - linearb == linearc);
}

TEST(LinearAnalyticTest, MulLinear)
{
    LinearAnalytic<int, int> lineara = {1, 0, 2};
    LinearAnalytic<int, int> linearb = {2, 0, 4};

    EXPECT_TRUE(lineara * 2 == linearb);
}


TEST(LinearAnalyticTest, DivLinear)
{
    LinearAnalytic<int, int> lineara = {1, 0, 2};
    LinearAnalytic<int, int> linearb = {2, 0, 4};

    EXPECT_TRUE(linearb / 2 == lineara);
}



// TEST(LinearAnalyticTest, OperateInverted)
// {
//     LinearAnalytic<int, int> linear = 20;

//     EXPECT_TRUE(10 + linear == 30);
//     EXPECT_TRUE(5 - linear == -15);
//     EXPECT_TRUE(5 * linear == 100);

//     LinearAnalytic<int, int> lineara = {1, 0, 2};
//     LinearAnalytic<int, int> linearb = {2, 0, 4};

//     EXPECT_TRUE(2 * lineara == linearb);

// }