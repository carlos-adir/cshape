#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "cshape/polynomial.h"

TEST(PolynomialTest, Constructor)
{
    Polynomial polya;
    Polynomial polyb(0);
    Polynomial polyc(10);

    std::vector<double> coefs;
    Polynomial polyd(coefs);
    coefs.push_back(10);
    coefs.push_back(-20);
    for (int i = 0; i < coefs.size(); i++)
        std::cout << coefs[i] << ", ";
    std::cout << std::endl;
    Polynomial polye(coefs);
    
    Polynomial polyf({1, 0, 2});
    Polynomial polyg = {3, 0, 4};
}


TEST(PolynomialTest, Degree)
{
    Polynomial polya;
    EXPECT_EQ(polya.degree(), 0);
    Polynomial polyb(0);
    EXPECT_EQ(polyb.degree(), 0);
    Polynomial polyc(10);
    EXPECT_EQ(polyc.degree(), 0);

    std::vector<double> coefs;
    Polynomial polyd(coefs);
    EXPECT_EQ(polyd.degree(), 0);
    coefs.push_back(10);
    coefs.push_back(-20);
    Polynomial polye(coefs);
    EXPECT_EQ(polye.degree(), 1);
}


TEST(PolynomialTest, CompareConstant)
{
    Polynomial poly(10);
    EXPECT_EQ(poly.degree(), 0);
    EXPECT_TRUE(poly == 10);
    EXPECT_FALSE(poly == 20);
    EXPECT_FALSE(poly != 10);
    EXPECT_TRUE(poly != 20);

    EXPECT_TRUE(poly == 10.);
    EXPECT_FALSE(poly == 20.);
    EXPECT_FALSE(poly != 10.);
    EXPECT_TRUE(poly != 20.);
    EXPECT_EQ(poly.degree(), 0);
}

TEST(PolynomialTest, OperateIntConstant)
{
    Polynomial poly(10);
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


TEST(PolynomialTest, OperateDoubleConstant)
{
    Polynomial poly(10.);
    EXPECT_TRUE(poly == 10.);
    poly = 20.;
    EXPECT_TRUE(poly == 20.);
    poly += 10.;
    EXPECT_TRUE(poly == 30.);
    poly -= 5.;
    EXPECT_TRUE(poly == 25.);
    poly *= 4.;
    EXPECT_TRUE(poly == 100.);
    poly /= 20.;
    EXPECT_TRUE(poly == 5.);
    poly %= 2.;
    EXPECT_TRUE(poly == 0.);

    poly = 10.;
    EXPECT_TRUE(poly == 10.);
    EXPECT_TRUE(poly + 10. == 20.);
    EXPECT_TRUE(poly - 5. == 5.);
    EXPECT_TRUE(poly * 5. == 50.);
    EXPECT_TRUE(poly / 2. == 5.);
    EXPECT_TRUE(poly % 3. == 0.);
}


TEST(PolynomialTest, Evaluate)
{
    Polynomial poly = {1, -2, 4};
    EXPECT_EQ(poly.degree(), 2);

    EXPECT_EQ(poly.eval(-2), 21);
    EXPECT_EQ(poly.eval(-1), 7);
    EXPECT_EQ(poly.eval(0), 1);
    EXPECT_EQ(poly.eval(1), -3);
    EXPECT_EQ(poly.eval(2), 13);

    EXPECT_EQ(poly(-2), 21);
    EXPECT_EQ(poly(-1), 7);
    EXPECT_EQ(poly(0), 1);
    EXPECT_EQ(poly(1), -3);
    EXPECT_EQ(poly(2), 13);
}


TEST(PolynomialTest, AddPoly)
{
    Polynomial polya = {1, 0, 2};
    Polynomial polyb = {3, 0, 4};
    Polynomial polyc = {4, 0, 6};

    EXPECT_TRUE(polya + polyb == polyc);
}

TEST(PolynomialTest, SubPoly)
{
    Polynomial polya = {1, 0, 2};
    Polynomial polyb = {3, 0, 4};
    Polynomial polyc = {-2, 0, -2};

    EXPECT_TRUE(polya - polyb == polyc);
}

TEST(PolynomialTest, MulPoly)
{
    Polynomial polya = {1, 0, 2};
    Polynomial polyb = {3, 0, 4};
    Polynomial polyc = {3, 0, 8, 0, 8};

    EXPECT_TRUE(polya * polyb == polyc);
}


TEST(PolynomialTest, DivPoly)
{
    Polynomial polya = {1, 0, 2};
    Polynomial polyb = {3, 0, 4};
    Polynomial polyc = {3, 0, 8, 0, 8};

    EXPECT_TRUE(polyc / polyb == polya);
    EXPECT_TRUE(polyc / polya == polyb);
}

TEST(PolynomialTest, ModPoly)
{
    Polynomial polya = {1, 0, 2};
    Polynomial polyb = {3, 0, 4};
    Polynomial polyc = {3, 0, 8, 0, 8};

    EXPECT_TRUE(polyc % polyb == 0);
    EXPECT_TRUE(polyc % polya == 0);
}

