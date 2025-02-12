#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "cshape/polynomial.h"




TEST(PolynomialTest, Constructor)
{
    Polynomial<int, int> polya;
    Polynomial<int, int> polyb(0);
    Polynomial<int, int> polyc(10);

    std::vector<int> coefs;
    Polynomial<int, int> polyd(coefs);
    coefs.push_back(10);
    coefs.push_back(-20);
    Polynomial<int, int> polye(coefs);
    
    Polynomial<int, int> polyf({1, 0, 2});
    Polynomial<int, int> polyg = {3, 0, 4};
}



TEST(PolynomialTest, SettingCoefs)
{
    Polynomial<int, int> polya, polyb;
    std::vector<int> coefs;
    polya = 0;
    polyb = 10;
    polyb = {};
    polyb = {10};
    polyb = {1, 2};
    polyb = {1, -3, 2};
    polya = polyb;
    polya[0] = 20;
    polya[1] = -3;
    polya[2] = 21;
    polyb = coefs;
}


TEST(PolynomialTest, CheckDegree)
{
    Polynomial<int, int> poly;

    EXPECT_EQ(poly.degree(), 0);
    poly = 0;
    EXPECT_EQ(poly.degree(), 0);
    poly = 10;
    EXPECT_EQ(poly.degree(), 0);
    poly = {};
    EXPECT_EQ(poly.degree(), 0);
    poly = {10};
    EXPECT_EQ(poly.degree(), 0);
    poly = {1, 2};
    EXPECT_EQ(poly.degree(), 1);
    poly = {1, -3, 2};
    EXPECT_EQ(poly.degree(), 2);
}


TEST(PolynomialTest, CheckCoefs)
{
    Polynomial<int, int> poly;
    EXPECT_EQ(poly[0], 0);
    
    poly = {1, -3, 2, -4, -7};
    EXPECT_EQ(poly[0], 1);
    EXPECT_EQ(poly[1], -3);
    EXPECT_EQ(poly[2], 2);
    EXPECT_EQ(poly[3], -4);
    EXPECT_EQ(poly[4], -7);

}

TEST(PolynomialTest, CompareWithConstant)
{
    Polynomial<int, int> poly(10);
    EXPECT_TRUE(poly == 10);
    EXPECT_FALSE(poly == 20);
    EXPECT_FALSE(poly != 10);
    EXPECT_TRUE(poly != 20);

}

TEST(PolynomialTest, OperateConstant)
{
    Polynomial<int, int> poly(10);
    EXPECT_TRUE(poly == 10);
    poly = 20;
    EXPECT_TRUE(poly == 20);
    poly += 10;
    EXPECT_TRUE(poly == 30);
    poly -= 5;
    EXPECT_TRUE(poly == 25);
    poly *= 4;
    EXPECT_TRUE(poly == 100);
    poly /= 20;
    EXPECT_TRUE(poly == 5);
    poly %= 2;
    EXPECT_TRUE(poly == 0);

    poly = 10;
    EXPECT_TRUE(poly == 10);
    EXPECT_TRUE(poly + 10 == 20);
    EXPECT_TRUE(poly - 5 == 5);
    EXPECT_TRUE(poly * 5 == 50);
    EXPECT_TRUE(poly / 2 == 5);
    EXPECT_TRUE(poly % 3 == 0);
}


TEST(PolynomialTest, EvaluateNatural)
{
    Polynomial<int, int> poly;

    poly = 4;
    EXPECT_EQ(poly.degree(), 0);
    EXPECT_EQ(poly.eval(-2), 4);
    EXPECT_EQ(poly.eval(-1), 4);
    EXPECT_EQ(poly.eval(0), 4);
    EXPECT_EQ(poly.eval(1), 4);
    EXPECT_EQ(poly.eval(2), 4);

    poly = {3, -4};
    EXPECT_EQ(poly.degree(), 1);
    EXPECT_EQ(poly.eval(-2), 11);
    EXPECT_EQ(poly.eval(-1), 7);
    EXPECT_EQ(poly.eval(0), 3);
    EXPECT_EQ(poly.eval(1), -1);
    EXPECT_EQ(poly.eval(2), -5);

    poly = {1, -2, 4};
    EXPECT_EQ(poly.degree(), 2);
    EXPECT_EQ(poly.eval(-2), 21);
    EXPECT_EQ(poly.eval(-1), 7);
    EXPECT_EQ(poly.eval(0), 1);
    EXPECT_EQ(poly.eval(1), 3);
    EXPECT_EQ(poly.eval(2), 13);
    
    poly = {1, -2, 4, -6};
    EXPECT_EQ(poly.degree(), 3);
    EXPECT_EQ(poly.eval(-2), 69);
    EXPECT_EQ(poly.eval(-1), 13);
    EXPECT_EQ(poly.eval(0), 1);
    EXPECT_EQ(poly.eval(1), -3);
    EXPECT_EQ(poly.eval(2), -35);
}


TEST(PolynomialTest, EvaluateDerivate)
{
    Polynomial<int, int> poly;

    poly = 4;
    EXPECT_EQ(poly.degree(), 0);
    EXPECT_EQ(poly.eval(-2, 1), 0);
    EXPECT_EQ(poly.eval(-1, 1), 0);
    EXPECT_EQ(poly.eval(0, 1), 0);
    EXPECT_EQ(poly.eval(1, 1), 0);
    EXPECT_EQ(poly.eval(2, 1), 0);

    poly = {3, -4};
    EXPECT_EQ(poly.degree(), 1);
    EXPECT_EQ(poly.eval(-2, 1), -4);
    EXPECT_EQ(poly.eval(-1, 1), -4);
    EXPECT_EQ(poly.eval(0, 1), -4);
    EXPECT_EQ(poly.eval(1, 1), -4);
    EXPECT_EQ(poly.eval(2, 1), -4);
    EXPECT_EQ(poly.eval(-2, 2), 0);
    EXPECT_EQ(poly.eval(-1, 2), 0);
    EXPECT_EQ(poly.eval(0, 2), 0);
    EXPECT_EQ(poly.eval(1, 2), 0);
    EXPECT_EQ(poly.eval(2, 2), 0);

    poly = {1, -2, 4};
    EXPECT_EQ(poly.degree(), 2);
    EXPECT_EQ(poly.eval(-2, 1), -18);
    EXPECT_EQ(poly.eval(-1, 1), -10);
    EXPECT_EQ(poly.eval(0, 1), -2);
    EXPECT_EQ(poly.eval(1, 1), 6);
    EXPECT_EQ(poly.eval(2, 1), 14);
    EXPECT_EQ(poly.eval(-2, 2), 8);
    EXPECT_EQ(poly.eval(-1, 2), 8);
    EXPECT_EQ(poly.eval(0, 2), 8);
    EXPECT_EQ(poly.eval(1, 2), 8);
    EXPECT_EQ(poly.eval(2, 2), 8);

    poly = {1, -2, 4, -6};
    EXPECT_EQ(poly.degree(), 3);
    EXPECT_EQ(poly.eval(-2, 1), -90);
    EXPECT_EQ(poly.eval(-1, 1), -28);
    EXPECT_EQ(poly.eval(0, 1), -2);
    EXPECT_EQ(poly.eval(1, 1), -12);
    EXPECT_EQ(poly.eval(2, 1), -58);
    EXPECT_EQ(poly.eval(-2, 2), 80);
    EXPECT_EQ(poly.eval(-1, 2), 44);
    EXPECT_EQ(poly.eval(0, 2), 8);
    EXPECT_EQ(poly.eval(1, 2), -28);
    EXPECT_EQ(poly.eval(2, 2), -64);
    EXPECT_EQ(poly.eval(-2, 3), -36);
    EXPECT_EQ(poly.eval(-1, 3), -36);
    EXPECT_EQ(poly.eval(0, 3), -36);
    EXPECT_EQ(poly.eval(1, 3), -36);
    EXPECT_EQ(poly.eval(2, 3), -36);
}


TEST(PolynomialTest, AddPoly)
{
    Polynomial<int, int> polya = {1, 0, 2};
    Polynomial<int, int> polyb = {3, 0, 4};
    Polynomial<int, int> polyc = {4, 0, 6};

    EXPECT_TRUE(polya + polyb == polyc);
}

TEST(PolynomialTest, SubPoly)
{
    Polynomial<int, int> polya = {1, 0, 2};
    Polynomial<int, int> polyb = {3, 0, 4};
    Polynomial<int, int> polyc = {-2, 0, -2};

    EXPECT_TRUE(polya - polyb == polyc);
}

TEST(PolynomialTest, MulPoly)
{
    Polynomial<int, int> polya = {1, 0, 2};
    Polynomial<int, int> polyb = {3, 0, 4};
    Polynomial<int, int> polyc = {3, 0, 10, 0, 8};

    EXPECT_TRUE(polya * polyb == polyc);
}


TEST(PolynomialTest, DivPoly)
{
    Polynomial<int, int> polya = {1, 0, 2};
    Polynomial<int, int> polyb = {3, 0, 4};
    Polynomial<int, int> polyc = {3, 0, 10, 0, 8};

    EXPECT_TRUE(polyc / polyb == polya);
    EXPECT_TRUE(polyc / polya == polyb);
}

TEST(PolynomialTest, ModPoly)
{
    Polynomial<int, int> polya = {1, 0, 2};
    Polynomial<int, int> polyb = {3, 0, 4};
    Polynomial<int, int> polyc = {3, 0, 10, 0, 8};

    EXPECT_TRUE(polyc % polyb == 0);
    EXPECT_TRUE(polyc % polya == 0);
}

TEST(PolynomialTest, SomeMultDivMod)
{
    Polynomial<int, int> polya, polyb, polyc, polyd;
    
    polya = {-2, 1};
    polyb = {4, 1};
    polyc = {11};
    polyd = polya * polyb + polyc;
    EXPECT_TRUE(polyd / polya == polyb);
    EXPECT_TRUE(polyd % polya == polyc);
    EXPECT_TRUE(polyd / polyb == polya);
    EXPECT_TRUE(polyd % polyb == polyc);

    polya = {-11, 2, 8};
    polyb = {9, -3, 2};
    polyc = {111, -75};
    polyd = polya * polyb + polyc;
    EXPECT_TRUE(polyd / polya == polyb);
    EXPECT_TRUE(polyd % polya == polyc);
    EXPECT_TRUE(polyd / polyb == polya);
    EXPECT_TRUE(polyd % polyb == polyc);

    polya = {13, -6, 2};
    polyb = {-2, 4, 3};
    polyc = {29, -70};
    polyd = polya * polyb + polyc;
    EXPECT_TRUE(polyd / polya == polyb);
    EXPECT_TRUE(polyd % polya == polyc);
    EXPECT_TRUE(polyd / polyb == polya);
    EXPECT_TRUE(polyd % polyb == polyc);

}



