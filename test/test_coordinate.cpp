#include <gtest/gtest.h>
#include "cshape/coordinate.h"

TEST(CoordinateTest, Attribute)
{
    Coordinate node;
    EXPECT_EQ(node, 0);
    node = 10;
    EXPECT_EQ(node, 10);
}

TEST(CoordinateTest, Add)
{
    Coordinate nodea, nodeb;
    nodea = 10;
    nodeb = 30;
    EXPECT_EQ(nodea + nodeb, 10 + 30);
    nodea = 2;
    nodeb = 8;
    EXPECT_EQ(nodea + nodeb, 2 + 8);
}

TEST(CoordinateTest, Sub)
{
    Coordinate nodea, nodeb;
    nodea = 10;
    nodeb = 30;
    EXPECT_EQ(nodea - nodeb, 10 - 30);
    nodea = 2;
    nodeb = 8;
    EXPECT_EQ(nodea - nodeb, 2 - 8);
}


TEST(CoordinateTest, Mul)
{
    Coordinate nodea, nodeb;
    nodea = 10;
    nodeb = 30;
    EXPECT_EQ(nodea * nodeb, 10 * 30);
    nodea = 2;
    nodeb = 8;
    EXPECT_EQ(nodea * nodeb, 2 * 8);
}


TEST(CoordinateTest, Div)
{
    Coordinate nodea, nodeb;
    nodea = 10;
    nodeb = 40;
    EXPECT_EQ(nodea / nodeb, 10. / 40);
    nodea = 8;
    nodeb = 2;
    EXPECT_EQ(nodea / nodeb, 8. / 2);
}
