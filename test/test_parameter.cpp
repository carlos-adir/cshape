#include <gtest/gtest.h>
#include "cshape/parameter.h"

TEST(ParameterTest, Attribute)
{
    Parameter node;
    EXPECT_EQ(node, 0);
    node = 10;
    EXPECT_EQ(node, 10);
}

TEST(ParameterTest, Add)
{
    Parameter nodea, nodeb;
    nodea = 10;
    nodeb = 30;
    EXPECT_EQ(nodea + nodeb, 10 + 30);
    nodea = 2;
    nodeb = 8;
    EXPECT_EQ(nodea + nodeb, 2 + 8);
}

TEST(ParameterTest, Sub)
{
    Parameter nodea, nodeb;
    nodea = 10;
    nodeb = 30;
    EXPECT_EQ(nodea - nodeb, 10 - 30);
    nodea = 2;
    nodeb = 8;
    EXPECT_EQ(nodea - nodeb, 2 - 8);
}


TEST(ParameterTest, Mul)
{
    Parameter nodea, nodeb;
    nodea = 10;
    nodeb = 30;
    EXPECT_EQ(nodea * nodeb, 10 * 30);
    nodea = 2;
    nodeb = 8;
    EXPECT_EQ(nodea * nodeb, 2 * 8);
}


TEST(ParameterTest, Div)
{
    Parameter nodea, nodeb;
    nodea = 10;
    nodeb = 40;
    EXPECT_EQ(nodea / nodeb, 10. / 40);
    nodea = 8;
    nodeb = 2;
    EXPECT_EQ(nodea / nodeb, 8. / 2);
}

