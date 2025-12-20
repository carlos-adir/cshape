#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "cshape/bidim/subsetr2.h"




TEST(SubSetR2Test, ConstructorSingleton)
{
    auto empty = SubSetR2::empty();
    auto whole = SubSetR2::whole();
}


TEST(SubSetR2Test, CompareSingleton)
{
    /*
    const auto empty = SubSetR2::empty();
    const auto whole = SubSetR2::whole();
    EXPECT_EQ(empty, empty);
    EXPECT_EQ(whole, whole);
    EXPECT_TRUE(empty != whole);
    EXPECT_TRUE(whole != empty);
    */
}


TEST(SubSetR2Test, BooleanSingleton)
{
    /*
    const auto empty = SubSetR2::empty();
    const auto whole = SubSetR2::whole();

    // UNION
    EXPECT_TRUE((empty | empty) == empty);
    EXPECT_TRUE((empty | whole) == whole);
    EXPECT_TRUE((whole | empty) == whole);
    EXPECT_TRUE((whole | whole) == whole);

    // INTERSECT
    EXPECT_TRUE((empty & empty) == empty);
    EXPECT_TRUE((empty & whole) == empty);
    EXPECT_TRUE((whole & empty) == empty);
    EXPECT_TRUE((whole & whole) == whole);

    // XOR
    EXPECT_TRUE((empty ^ empty) == empty);
    EXPECT_TRUE((empty ^ whole) == whole);
    EXPECT_TRUE((whole ^ empty) == whole);
    EXPECT_TRUE((whole ^ whole) == empty);
    */
}




TEST(SubSetR2Test, ContainsSingleton)
{
    
};
