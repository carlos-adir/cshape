#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "cshape/boolalg.h"




TEST(BoolalgTest, Constructor)
{
    StringBoolTree::factory->Build(Operations::False, {});
    StringBoolTree::factory->Build(Operations::True, {});
}

TEST(BoolalgTest, Inverse)
{
    auto a = StringBoolTree::factory->Build(Operations::False, {});
    auto b = ~(*a);
}


