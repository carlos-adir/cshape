#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "cshape/boolalg/binary.h"


TEST(BinaryTest, Constructor)
{
    auto a0 = Binary(0, 1);
    auto a1 = Binary(1, 1);
    auto a2 = Binary(0, 2);
    auto a3 = Binary(1, 2);
    auto a4 = Binary(2, 2);
    auto a5 = Binary(3, 2);
}


TEST(BinaryTest, BoolOperate)
{
    auto a0 = Binary(3, 4);
    auto a1 = Binary(5, 4);
    EXPECT_EQ((a0 & a1), Binary(1, 4)) << "And failed";
    EXPECT_EQ((a0 | a1), Binary(7, 4)) << "Or failed";
    EXPECT_EQ((a0 ^ a1), Binary(6, 4)) << "Xor failed";
    
}
