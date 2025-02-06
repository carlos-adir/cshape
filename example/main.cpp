#include <iostream>

#include "cshape/polynomial.h"

#define EXPECT_TRUE(x) std::cout << "Expected true, received " << (x) << std::endl
#define EXPECT_FALSE(x) std::cout << "Expected false, received " << (x) << std::endl

int main(){
    std::cout << "Hello world" << std::endl;
    
    Polynomial poly(10);
    EXPECT_TRUE(poly == 10);
    poly = 20;
    EXPECT_TRUE(poly == 20);
    poly += 10;
    EXPECT_TRUE(poly == 30);
    poly -= 5;
    EXPECT_TRUE(poly == 25);
    poly *= 4;
    EXPECT_TRUE(poly == 100);
    poly /= 20;
    EXPECT_TRUE(poly == 5);
    // poly %= 2;
    // EXPECT_TRUE(poly == 0);

    poly = 10;
    EXPECT_TRUE(poly == 10);
    EXPECT_TRUE(poly + 10 == 20);
    EXPECT_TRUE(poly - 5 == 5);
    EXPECT_TRUE(poly * 5 == 50);
    EXPECT_TRUE(poly / 2 == 5);
    // EXPECT_TRUE(poly % 3 == 0);
    return 0;
}