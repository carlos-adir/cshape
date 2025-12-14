#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "cshape/boolalg.h"




TEST(BoolalgTest, Constructor)
{
    auto f = StringBoolTree::factory->False();
    auto t = StringBoolTree::factory->True();
    EXPECT_TRUE(f->operation == Operations::False);
    EXPECT_TRUE(t->operation == Operations::True);
}


TEST(BoolalgTest, TrueFalseCompare)
{
    auto f0 = StringBoolTree::factory->False();
    auto f1 = StringBoolTree::factory->False();
    auto t0 = StringBoolTree::factory->True();
    auto t1 = StringBoolTree::factory->True();
    EXPECT_TRUE(f0 == f1);
    EXPECT_TRUE(t0 == t1);
    EXPECT_FALSE(f0 == t0);
    EXPECT_FALSE(t0 == f0);
}

TEST(BoolalgTest, TrueFalseInverse)
{
    auto f = StringBoolTree::factory->False();
    auto t = StringBoolTree::factory->True();
    EXPECT_TRUE((~f) == t);
    EXPECT_TRUE((~t) == f);
}

TEST(BoolalgTest, TrueFalseUnion)
{
    auto f = StringBoolTree::factory->False();
    auto t = StringBoolTree::factory->True();
    EXPECT_TRUE((f | f) == f);
    EXPECT_TRUE((f | t) == t);
    EXPECT_TRUE((t | f) == t);
    EXPECT_TRUE((t | t) == t);
}

TEST(BoolalgTest, TrueFalseIntersect)
{
    auto f = StringBoolTree::factory->False();
    auto t = StringBoolTree::factory->True();
    EXPECT_TRUE((f & f) == f);
    EXPECT_TRUE((f & t) == f);
    EXPECT_TRUE((t & f) == f);
    EXPECT_TRUE((t & t) == t);
}

TEST(BoolalgTest, TrueFalseXor)
{
    auto f = StringBoolTree::factory->False();
    auto t = StringBoolTree::factory->True();
    EXPECT_TRUE((f ^ f) == f);
    EXPECT_TRUE((f ^ t) == t);
    EXPECT_TRUE((t ^ f) == t);
    EXPECT_TRUE((t ^ t) == f);
}



TEST(BoolalgTest, SingleVariable)
{
    auto f = StringBoolTree::factory->False();
    auto t = StringBoolTree::factory->True();
    auto a = StringBoolVariable::build("a");

    EXPECT_TRUE(a != f);
    EXPECT_TRUE(f != a);
    EXPECT_TRUE(a != t);
    EXPECT_TRUE(t != a);
    EXPECT_TRUE(a == a);

    EXPECT_TRUE((~a) != a);
    EXPECT_TRUE((~(~a)) == a);
    
    // EXPECT_TRUE((a | a) == a);
    // EXPECT_TRUE((a & a) == a);
    // EXPECT_TRUE((a ^ a) == f);

}

