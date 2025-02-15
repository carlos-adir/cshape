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
    FiniteSingleValue<double> param(&value);
}



TEST(ParameterTest, CompareFiniteInfinity)
{
    double double_value = 10;
    FiniteSingleValue<double> finite(&double_value);

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
    FiniteSingleValue<double> finia(&douba);
    FiniteSingleValue<double> finib(&doubb);

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
}


TEST(ParameterTest, CompareFiniteEmptyWhole)
{
    double double_value = 10;
    FiniteSingleValue<double> finite(&double_value);

    EXPECT_FALSE(EMPTY == finite);
    EXPECT_TRUE(EMPTY != finite);
    EXPECT_FALSE(finite == EMPTY);
    EXPECT_TRUE(finite != EMPTY);

    EXPECT_FALSE(WHOLE == finite);
    EXPECT_TRUE(WHOLE != finite);
    EXPECT_FALSE(finite == WHOLE);
    EXPECT_TRUE(finite != WHOLE);
}



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
}


TEST(ParameterTest, ContainsFinite)
{
    double double_value = 10;
    FiniteSingleValue<double> finite(&double_value);

    EXPECT_TRUE(finite.contains(finite));

    EXPECT_TRUE(finite.contains(EMPTY));
    EXPECT_FALSE(finite.contains(BOTINF));
    EXPECT_FALSE(finite.contains(TOPINF));
    EXPECT_FALSE(finite.contains(WHOLE));

    EXPECT_FALSE(EMPTY.contains(finite));
    EXPECT_FALSE(BOTINF.contains(finite));
    EXPECT_FALSE(TOPINF.contains(finite));
    EXPECT_TRUE(WHOLE.contains(finite));
}


TEST(ParameterTest, BooleanSingleton)
{

}



