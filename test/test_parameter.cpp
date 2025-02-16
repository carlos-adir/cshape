#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "cshape/parameter.h"




TEST(ParameterTest, ConstructorSingleton)
{
    const NegativeInfinity& botinf = NegativeInfinity::getInstance();
    const PositiveInfinity& topinf = PositiveInfinity::getInstance();
    const EmptyParam& empty = EmptyParam::getInstance();
    const WholeParam& whole = WholeParam::getInstance();
    
    EXPECT_TRUE(&topinf == &TOPINF);
    EXPECT_TRUE(&botinf == &BOTINF);
    EXPECT_TRUE(&empty == &EMPTY);
    EXPECT_TRUE(&whole == &WHOLE);
}


TEST(ParameterTest, CompareSingleton)
{
    // EMPTY and WHOLE
    EXPECT_TRUE(EMPTY == EMPTY);
    EXPECT_FALSE(EMPTY == WHOLE);
    EXPECT_FALSE(WHOLE == EMPTY);
    EXPECT_TRUE(WHOLE == WHOLE);

    EXPECT_FALSE(EMPTY != EMPTY);
    EXPECT_TRUE(EMPTY != WHOLE);
    EXPECT_TRUE(WHOLE != EMPTY);
    EXPECT_FALSE(WHOLE != WHOLE);
    
    // EMPTY and INF
    EXPECT_FALSE(EMPTY == BOTINF);
    EXPECT_FALSE(EMPTY == TOPINF);
    EXPECT_TRUE(EMPTY != BOTINF);
    EXPECT_TRUE(EMPTY != TOPINF);

    EXPECT_FALSE(BOTINF == EMPTY);
    EXPECT_FALSE(TOPINF == EMPTY);
    EXPECT_TRUE(BOTINF != EMPTY);
    EXPECT_TRUE(TOPINF != EMPTY);

    // WHOLE and INF
    EXPECT_FALSE(WHOLE == BOTINF);
    EXPECT_FALSE(WHOLE == TOPINF);
    EXPECT_TRUE(WHOLE != BOTINF);
    EXPECT_TRUE(WHOLE != TOPINF);  

    EXPECT_FALSE(BOTINF == WHOLE);
    EXPECT_FALSE(TOPINF == WHOLE);
    EXPECT_TRUE(BOTINF != WHOLE);
    EXPECT_TRUE(TOPINF != WHOLE);

    // BOT with BOT
    EXPECT_TRUE(BOTINF == BOTINF);
    EXPECT_FALSE(BOTINF != BOTINF);
    EXPECT_FALSE(BOTINF < BOTINF);
    EXPECT_TRUE(BOTINF <= BOTINF);
    EXPECT_TRUE(BOTINF >= BOTINF);
    EXPECT_FALSE(BOTINF > BOTINF);

    // TOP with TOP
    EXPECT_TRUE(TOPINF == TOPINF);
    EXPECT_FALSE(TOPINF != TOPINF);
    EXPECT_FALSE(TOPINF < TOPINF);
    EXPECT_TRUE(TOPINF <= TOPINF);
    EXPECT_TRUE(TOPINF >= TOPINF);
    EXPECT_FALSE(TOPINF > TOPINF);

    // BOT with TOP
    EXPECT_FALSE(BOTINF == TOPINF);
    EXPECT_TRUE(BOTINF != TOPINF);
    EXPECT_TRUE(BOTINF < TOPINF);
    EXPECT_TRUE(BOTINF <= TOPINF);
    EXPECT_FALSE(BOTINF >= TOPINF);
    EXPECT_FALSE(BOTINF > TOPINF);
    
    // TOP with BOT
    EXPECT_FALSE(TOPINF == BOTINF);
    EXPECT_TRUE(TOPINF != BOTINF);
    EXPECT_FALSE(TOPINF < BOTINF);
    EXPECT_FALSE(TOPINF <= BOTINF);
    EXPECT_TRUE(TOPINF >= BOTINF);
    EXPECT_TRUE(TOPINF > BOTINF);
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

    Interval interv1(BOTINF, fa);
    Interval interv2(BOTINF, fb);
    Interval interv3(fa, fb);
    Interval interv4(fa, TOPINF);
    Interval interv5(fb, TOPINF);

    EXPECT_THROW(Interval(fa, BOTINF), std::invalid_argument);
    EXPECT_THROW(Interval(fb, BOTINF), std::invalid_argument);
    EXPECT_THROW(Interval(fb, fa), std::invalid_argument);
    EXPECT_THROW(Interval(TOPINF, fa), std::invalid_argument);
    EXPECT_THROW(Interval(TOPINF, fb), std::invalid_argument);
    EXPECT_THROW(Interval(BOTINF, BOTINF), std::invalid_argument);
    EXPECT_THROW(Interval(fa, fa), std::invalid_argument);
    EXPECT_THROW(Interval(fb, fb), std::invalid_argument);
    EXPECT_THROW(Interval(TOPINF, TOPINF), std::invalid_argument);
    EXPECT_THROW(Interval(BOTINF, TOPINF), std::invalid_argument);
}



TEST(ParameterTest, CompareFiniteInfinity)
{
    double double_value = 10;
    FiniteSingleValue finite(double_value);

    EXPECT_TRUE(BOTINF < finite);
    EXPECT_TRUE(BOTINF <= finite);
    EXPECT_FALSE(BOTINF >= finite);
    EXPECT_FALSE(BOTINF > finite);
    EXPECT_FALSE(BOTINF == finite);
    EXPECT_TRUE(BOTINF != finite);
    
    EXPECT_FALSE(finite < BOTINF);
    EXPECT_FALSE(finite <= BOTINF);
    EXPECT_TRUE(finite >= BOTINF);
    EXPECT_TRUE(finite > BOTINF);
    EXPECT_FALSE(finite == BOTINF);
    EXPECT_TRUE(finite != BOTINF);

    EXPECT_FALSE(TOPINF < finite);
    EXPECT_FALSE(TOPINF <= finite);
    EXPECT_TRUE(TOPINF >= finite);
    EXPECT_TRUE(TOPINF > finite);
    EXPECT_FALSE(TOPINF == finite);
    EXPECT_TRUE(TOPINF != finite);
    
    EXPECT_TRUE(finite < TOPINF);
    EXPECT_TRUE(finite <= TOPINF);
    EXPECT_FALSE(finite >= TOPINF);
    EXPECT_FALSE(finite > TOPINF);
    EXPECT_FALSE(finite == TOPINF);
    EXPECT_TRUE(finite != TOPINF);
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

    EXPECT_FALSE(EMPTY == finite);
    EXPECT_TRUE(EMPTY != finite);
    EXPECT_FALSE(finite == EMPTY);
    EXPECT_TRUE(finite != EMPTY);

    EXPECT_FALSE(WHOLE == finite);
    EXPECT_TRUE(WHOLE != finite);
    EXPECT_FALSE(finite == WHOLE);
    EXPECT_TRUE(finite != WHOLE);
};



TEST(ParameterTest, ContainsSingleton)
{
    EXPECT_TRUE(EMPTY.contains(EMPTY));
    EXPECT_FALSE(EMPTY.contains(BOTINF));
    EXPECT_FALSE(EMPTY.contains(TOPINF));
    EXPECT_FALSE(EMPTY.contains(WHOLE));

    EXPECT_TRUE(BOTINF.contains(EMPTY));
    EXPECT_TRUE(BOTINF.contains(BOTINF));
    EXPECT_FALSE(BOTINF.contains(TOPINF));
    EXPECT_FALSE(BOTINF.contains(WHOLE));

    EXPECT_TRUE(TOPINF.contains(EMPTY));
    EXPECT_FALSE(TOPINF.contains(BOTINF));
    EXPECT_TRUE(TOPINF.contains(TOPINF));
    EXPECT_FALSE(TOPINF.contains(WHOLE));
    
    EXPECT_TRUE(WHOLE.contains(EMPTY));
    EXPECT_TRUE(WHOLE.contains(BOTINF));
    EXPECT_TRUE(WHOLE.contains(TOPINF));
    EXPECT_TRUE(WHOLE.contains(WHOLE));
};


TEST(ParameterTest, ContainsFinite)
{
    double double_value = 10;
    FiniteSingleValue finite(double_value);

    EXPECT_TRUE(finite.contains(finite));

    EXPECT_TRUE(finite.contains(EMPTY));
    EXPECT_FALSE(finite.contains(BOTINF));
    EXPECT_FALSE(finite.contains(TOPINF));
    EXPECT_FALSE(finite.contains(WHOLE));

    EXPECT_FALSE(EMPTY.contains(finite));
    EXPECT_FALSE(BOTINF.contains(finite));
    EXPECT_FALSE(TOPINF.contains(finite));
    EXPECT_TRUE(WHOLE.contains(finite));
};




TEST(ParameterTest, ContainsInterval)
{
    const double da = -10, db = 10;
    FiniteSingleValue fa(da), fb(db);
    Interval n2a(BOTINF, fa);
    Interval n2b(BOTINF, fb);
    Interval a2b(fa, fb);
    Interval a2p(fa, TOPINF);
    Interval b2p(fb, TOPINF);

    // Contains EMPTY
    EXPECT_TRUE(n2a.contains(EMPTY));
    EXPECT_TRUE(n2b.contains(EMPTY));
    EXPECT_TRUE(a2b.contains(EMPTY));
    EXPECT_TRUE(a2p.contains(EMPTY));
    EXPECT_TRUE(b2p.contains(EMPTY));

    // Contains WHOLE
    EXPECT_FALSE(n2a.contains(WHOLE));
    EXPECT_FALSE(n2b.contains(WHOLE));
    EXPECT_FALSE(a2b.contains(WHOLE));
    EXPECT_FALSE(a2p.contains(WHOLE));
    EXPECT_FALSE(b2p.contains(WHOLE));

    // Contains BOT INFINITY
    EXPECT_TRUE(n2a.contains(BOTINF));
    EXPECT_TRUE(n2b.contains(BOTINF));
    EXPECT_FALSE(a2b.contains(BOTINF));
    EXPECT_FALSE(a2p.contains(BOTINF));
    EXPECT_FALSE(b2p.contains(BOTINF));
    
    // Contains TOP INFINITY
    EXPECT_FALSE(n2a.contains(TOPINF));
    EXPECT_FALSE(n2b.contains(TOPINF));
    EXPECT_FALSE(a2b.contains(TOPINF));
    EXPECT_TRUE(a2p.contains(TOPINF));
    EXPECT_TRUE(b2p.contains(TOPINF));

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



