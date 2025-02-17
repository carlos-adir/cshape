#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "cshape/parameter.h"




TEST(ParameterTest, ConstructorSingleton)
{
    const NegativeInfinity& botinf = NegativeInfinity::getInstance();
    const PositiveInfinity& topinf = PositiveInfinity::getInstance();
    const EmptyR1& empty = EmptyR1::getInstance();
    const WholeR1& whole = WholeR1::getInstance();
    
    EXPECT_TRUE(&topinf == &POSINF);
    EXPECT_TRUE(&botinf == &NEGINF);
    EXPECT_TRUE(&empty == &EMPTYR1);
    EXPECT_TRUE(&whole == &WHOLER1);
}


TEST(ParameterTest, CompareSingleton)
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
    
    // EMPTYR1 and INF
    EXPECT_FALSE(EMPTYR1 == NEGINF);
    EXPECT_FALSE(EMPTYR1 == POSINF);
    EXPECT_TRUE(EMPTYR1 != NEGINF);
    EXPECT_TRUE(EMPTYR1 != POSINF);

    EXPECT_FALSE(NEGINF == EMPTYR1);
    EXPECT_FALSE(POSINF == EMPTYR1);
    EXPECT_TRUE(NEGINF != EMPTYR1);
    EXPECT_TRUE(POSINF != EMPTYR1);

    // WHOLER1 and INF
    EXPECT_FALSE(WHOLER1 == NEGINF);
    EXPECT_FALSE(WHOLER1 == POSINF);
    EXPECT_TRUE(WHOLER1 != NEGINF);
    EXPECT_TRUE(WHOLER1 != POSINF);  

    EXPECT_FALSE(NEGINF == WHOLER1);
    EXPECT_FALSE(POSINF == WHOLER1);
    EXPECT_TRUE(NEGINF != WHOLER1);
    EXPECT_TRUE(POSINF != WHOLER1);

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


TEST(ParameterTest, BuildsSingleValue)
{
    double value = 10;
    FiniteSingleValue param(value);
}



TEST(ParameterTest, BuildsInterval)
{
    const double da = -10, db = 10;
    FiniteSingleValue fa(da), fb(db);

    IntervalR1 interv1(NEGINF, fa);
    IntervalR1 interv2(NEGINF, fb);
    IntervalR1 interv3(fa, fb);
    IntervalR1 interv4(fa, POSINF);
    IntervalR1 interv5(fb, POSINF);

    EXPECT_THROW(IntervalR1(fa, fa), std::invalid_argument);
    EXPECT_THROW(IntervalR1(fb, fa), std::invalid_argument);
    EXPECT_THROW(IntervalR1(fb, fb), std::invalid_argument);
}



TEST(ParameterTest, CompareFiniteInfinity)
{
    double double_value = 10;
    FiniteSingleValue finite(double_value);

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


TEST(ParameterTest, CompareTwoFinites)
{
    double douba = -10;
    double doubb = 10;
    FiniteSingleValue finia(douba);
    FiniteSingleValue finib(doubb);

    EXPECT_TRUE(finia < finib);
    EXPECT_TRUE(finia <= finib);
    EXPECT_FALSE(finia >= finib);
    EXPECT_FALSE(finia > finib);
    EXPECT_FALSE(finia == finib);
    EXPECT_TRUE(finia != finib);

    EXPECT_FALSE(finib < finia);
    EXPECT_FALSE(finib <= finia);
    EXPECT_TRUE(finib >= finia);
    EXPECT_TRUE(finib > finia);
    EXPECT_FALSE(finib == finia);
    EXPECT_TRUE(finib != finia);
};


TEST(ParameterTest, CompareFiniteEmptyWhole)
{
    double double_value = 10;
    FiniteSingleValue finite(double_value);

    EXPECT_FALSE(EMPTYR1 == finite);
    EXPECT_TRUE(EMPTYR1 != finite);
    EXPECT_FALSE(finite == EMPTYR1);
    EXPECT_TRUE(finite != EMPTYR1);

    EXPECT_FALSE(WHOLER1 == finite);
    EXPECT_TRUE(WHOLER1 != finite);
    EXPECT_FALSE(finite == WHOLER1);
    EXPECT_TRUE(finite != WHOLER1);
};



TEST(ParameterTest, ContainsSingleton)
{
    EXPECT_TRUE(EMPTYR1.contains(EMPTYR1));
    EXPECT_FALSE(EMPTYR1.contains(NEGINF));
    EXPECT_FALSE(EMPTYR1.contains(POSINF));
    EXPECT_FALSE(EMPTYR1.contains(WHOLER1));

    EXPECT_TRUE(NEGINF.contains(EMPTYR1));
    EXPECT_TRUE(NEGINF.contains(NEGINF));
    EXPECT_FALSE(NEGINF.contains(POSINF));
    EXPECT_FALSE(NEGINF.contains(WHOLER1));

    EXPECT_TRUE(POSINF.contains(EMPTYR1));
    EXPECT_FALSE(POSINF.contains(NEGINF));
    EXPECT_TRUE(POSINF.contains(POSINF));
    EXPECT_FALSE(POSINF.contains(WHOLER1));
    
    EXPECT_TRUE(WHOLER1.contains(EMPTYR1));
    EXPECT_TRUE(WHOLER1.contains(NEGINF));
    EXPECT_TRUE(WHOLER1.contains(POSINF));
    EXPECT_TRUE(WHOLER1.contains(WHOLER1));
};


TEST(ParameterTest, ContainsFinite)
{
    double double_value = 10;
    FiniteSingleValue finite(double_value);

    EXPECT_TRUE(finite.contains(finite));

    EXPECT_TRUE(finite.contains(EMPTYR1));
    EXPECT_FALSE(finite.contains(NEGINF));
    EXPECT_FALSE(finite.contains(POSINF));
    EXPECT_FALSE(finite.contains(WHOLER1));

    EXPECT_FALSE(EMPTYR1.contains(finite));
    EXPECT_FALSE(NEGINF.contains(finite));
    EXPECT_FALSE(POSINF.contains(finite));
    EXPECT_TRUE(WHOLER1.contains(finite));
};




TEST(ParameterTest, ContainsInterval)
{
    FiniteSingleValue fa(-10), fb(10);
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

    // Contains BOT INFINITY
    EXPECT_TRUE(n2a.contains(NEGINF));
    EXPECT_TRUE(n2b.contains(NEGINF));
    EXPECT_FALSE(a2b.contains(NEGINF));
    EXPECT_FALSE(a2p.contains(NEGINF));
    EXPECT_FALSE(b2p.contains(NEGINF));
    
    // Contains TOP INFINITY
    EXPECT_FALSE(n2a.contains(POSINF));
    EXPECT_FALSE(n2b.contains(POSINF));
    EXPECT_FALSE(a2b.contains(POSINF));
    EXPECT_TRUE(a2p.contains(POSINF));
    EXPECT_TRUE(b2p.contains(POSINF));

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



