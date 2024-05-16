#include <gtest/gtest.h>
#include "cshape/nurbs.h"

TEST(PointTest, Attribute)
{
    Point point(0, 1);
    EXPECT_EQ(point[0], 0);
    EXPECT_EQ(point[1], 1);
}

TEST(PointTest, Inner1)
{
    Point pointa(1, 0);
    Point pointb(0, 1);
    EXPECT_EQ(pointa.inner(pointa), 1);
    EXPECT_EQ(pointa.inner(pointb), 0);
    EXPECT_EQ(pointb.inner(pointa), 0);
    EXPECT_EQ(pointb.inner(pointb), 1);
}

TEST(PointTest, Inner2)
{
    Point pointa(2, 0);
    Point pointb(0, 2);
    EXPECT_EQ(pointa.inner(pointa), 4);
    EXPECT_EQ(pointa.inner(pointb), 0);
    EXPECT_EQ(pointb.inner(pointa), 0);
    EXPECT_EQ(pointb.inner(pointb), 4);
}

TEST(PointTest, Cross)
{
    Point pointa(1, 0);
    Point pointb(0, 1);
    EXPECT_EQ(pointa.cross(pointa), 0);
    EXPECT_EQ(pointa.cross(pointb), 1);
    EXPECT_EQ(pointb.cross(pointa), -1);
    EXPECT_EQ(pointb.cross(pointb), 0);
}
