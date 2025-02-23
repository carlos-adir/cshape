#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "cshape/bool1d.h"




TEST(Bool1DTest, ConstructorSingleton)
{
    const EmptyR1& empty = EmptyR1::getInstance();
    const WholeR1& whole = WholeR1::getInstance();
    
    EXPECT_TRUE(&empty == &EMPTYR1);
    EXPECT_TRUE(&whole == &WHOLER1);
}


TEST(Bool1DTest, BuildsSingleValue)
{
    SingleValue param(10);
}



TEST(Bool1DTest, BuildsInterval)
{
    double fa(-10), fb(10);

    IntervalR1 interv1(NEGINF, fa);
    IntervalR1 interv2(NEGINF, fb);
    IntervalR1 interv3(fa, fb);
    IntervalR1 interv4(fa, POSINF);
    IntervalR1 interv5(fb, POSINF);

    EXPECT_THROW(IntervalR1(fa, fa), std::invalid_argument);
    EXPECT_THROW(IntervalR1(fb, fa), std::invalid_argument);
    EXPECT_THROW(IntervalR1(fb, fb), std::invalid_argument);
}


TEST(Bool1DTest, BuildsDisjoint)
{
    double fa(-10), fb(10);

    std::vector<double> nodes = {-5, 0, 5};
    std::vector<IntervalR1> intervs;
    intervs.push_back(IntervalR1(NEGINF, -10));
    intervs.push_back(IntervalR1(10, POSINF));
    
    DisjointR1 disj1(nodes);
    DisjointR1 disj2(intervs);
    DisjointR1 disj3(nodes, intervs);

}


TEST(Bool1DTest, BuildsFromString)
{
    double fa(-10), fb(10);

    std::vector<double> nodes = {-5, 0, 5};
    std::vector<IntervalR1> intervs;
    intervs.push_back(IntervalR1(NEGINF, -10));
    intervs.push_back(IntervalR1(10, POSINF));
    
    DisjointR1 disj1(nodes);
    DisjointR1 disj2(intervs);
    DisjointR1 disj3(nodes, intervs);
}


TEST(Bool1DTest, CompareSingleton)
{
    // EMPTYR1 and WHOLER1
    EXPECT_TRUE(EMPTYR1 == EMPTYR1);
    EXPECT_FALSE(EMPTYR1 == WHOLER1);
    EXPECT_FALSE(WHOLER1 == EMPTYR1);
    EXPECT_TRUE(WHOLER1 == WHOLER1);

    EXPECT_FALSE(EMPTYR1 != EMPTYR1);
    EXPECT_TRUE(EMPTYR1 != WHOLER1);
    EXPECT_TRUE(WHOLER1 != EMPTYR1);
    EXPECT_FALSE(WHOLER1 != WHOLER1);
}




TEST(Bool1DTest, CompareSingleEmptyWhole)
{
    SingleValue finite(10);

    EXPECT_FALSE(EMPTYR1 == finite);
    EXPECT_TRUE(EMPTYR1 != finite);
    EXPECT_FALSE(finite == EMPTYR1);
    EXPECT_TRUE(finite != EMPTYR1);

    EXPECT_FALSE(WHOLER1 == finite);
    EXPECT_TRUE(WHOLER1 != finite);
    EXPECT_FALSE(finite == WHOLER1);
    EXPECT_TRUE(finite != WHOLER1);
};



TEST(Bool1DTest, ContainsSingleton)
{
    EXPECT_TRUE(EMPTYR1.contains(EMPTYR1));
    EXPECT_FALSE(EMPTYR1.contains(WHOLER1));
    EXPECT_TRUE(WHOLER1.contains(EMPTYR1));
    EXPECT_TRUE(WHOLER1.contains(WHOLER1));
};


TEST(Bool1DTest, ContainsFinite)
{
    SingleValue finite(10);

    EXPECT_TRUE(finite.contains(finite));

    EXPECT_TRUE(finite.contains(EMPTYR1));
    EXPECT_FALSE(finite.contains(WHOLER1));

    EXPECT_FALSE(EMPTYR1.contains(finite));
    EXPECT_TRUE(WHOLER1.contains(finite));
};




TEST(Bool1DTest, ContainsInterval)
{
    double fa(-10), fb(10);
    IntervalR1 n2a(NEGINF, fa);
    IntervalR1 n2b(NEGINF, fb);
    IntervalR1 a2b(fa, fb);
    IntervalR1 a2p(fa, POSINF);
    IntervalR1 b2p(fb, POSINF);

    // Contains EMPTYR1
    EXPECT_TRUE(n2a.contains(EMPTYR1));
    EXPECT_TRUE(n2b.contains(EMPTYR1));
    EXPECT_TRUE(a2b.contains(EMPTYR1));
    EXPECT_TRUE(a2p.contains(EMPTYR1));
    EXPECT_TRUE(b2p.contains(EMPTYR1));

    // Contains WHOLER1
    EXPECT_FALSE(n2a.contains(WHOLER1));
    EXPECT_FALSE(n2b.contains(WHOLER1));
    EXPECT_FALSE(a2b.contains(WHOLER1));
    EXPECT_FALSE(a2p.contains(WHOLER1));
    EXPECT_FALSE(b2p.contains(WHOLER1));

    // Contains A value
    EXPECT_TRUE(n2a.contains(fa));
    EXPECT_TRUE(n2b.contains(fa));
    EXPECT_TRUE(a2b.contains(fa));
    EXPECT_TRUE(a2p.contains(fa));
    EXPECT_FALSE(b2p.contains(fa));

    // Contains B value
    EXPECT_FALSE(n2a.contains(fb));
    EXPECT_TRUE(n2b.contains(fb));
    EXPECT_TRUE(a2b.contains(fb));
    EXPECT_TRUE(a2p.contains(fb));
    EXPECT_TRUE(b2p.contains(fb));

    // Contains (-inf, A)
    EXPECT_TRUE(n2a.contains(n2a));
    EXPECT_TRUE(n2b.contains(n2a));
    EXPECT_FALSE(a2b.contains(n2a));
    EXPECT_FALSE(a2p.contains(n2a));
    EXPECT_FALSE(b2p.contains(n2a));

    // Contains (-inf, B)
    EXPECT_FALSE(n2a.contains(n2b));
    EXPECT_TRUE(n2b.contains(n2b));
    EXPECT_FALSE(a2b.contains(n2b));
    EXPECT_FALSE(a2p.contains(n2b));
    EXPECT_FALSE(b2p.contains(n2b));

    // Contains (A, B)
    EXPECT_FALSE(n2a.contains(a2b));
    EXPECT_TRUE(n2b.contains(a2b));
    EXPECT_TRUE(a2b.contains(a2b));
    EXPECT_TRUE(a2p.contains(a2b));
    EXPECT_FALSE(b2p.contains(a2b));

    // Contains (A, +inf)
    EXPECT_FALSE(n2a.contains(a2p));
    EXPECT_FALSE(n2b.contains(a2p));
    EXPECT_FALSE(a2b.contains(a2p));
    EXPECT_TRUE(a2p.contains(a2p));
    EXPECT_FALSE(b2p.contains(a2p));

    // Contains (B, +inf)
    EXPECT_FALSE(n2a.contains(b2p));
    EXPECT_FALSE(n2b.contains(b2p));
    EXPECT_FALSE(a2b.contains(b2p));
    EXPECT_TRUE(a2p.contains(b2p));
    EXPECT_TRUE(b2p.contains(b2p));
};



