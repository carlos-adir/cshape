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


TEST(BoolalgTest, CompareTrueFalse)
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

TEST(BoolalgTest, Inverse)
{
    auto f = StringBoolTree::factory->False();
    auto t = StringBoolTree::factory->True();
    EXPECT_TRUE((~f) == t);
    EXPECT_TRUE((~t) == f);
}

TEST(BoolalgTest, Union)
{
    auto f = StringBoolTree::factory->False();
    auto t = StringBoolTree::factory->True();
    EXPECT_TRUE((f | f) == f);
    EXPECT_TRUE((f | t) == t);
    EXPECT_TRUE((t | f) == t);
    EXPECT_TRUE((t | t) == t);
}

TEST(BoolalgTest, Intersect)
{
    auto f = StringBoolTree::factory->False();
    auto t = StringBoolTree::factory->True();
    EXPECT_TRUE((f & f) == f);
    EXPECT_TRUE((f & t) == f);
    EXPECT_TRUE((t & f) == f);
    EXPECT_TRUE((t & t) == t);
}

TEST(BoolalgTest, Xor)
{
    auto f = StringBoolTree::factory->False();
    auto t = StringBoolTree::factory->True();
    EXPECT_TRUE((f ^ f) == f);
    EXPECT_TRUE((f ^ t) == t);
    EXPECT_TRUE((t ^ f) == t);
    EXPECT_TRUE((t ^ t) == f);
}
