#include <iostream>
#include <unistd.h>

#include "cshape/polynomial.h"

#define EXPECT_TRUE(x) std::cout << "Expected true, received " << bool(x) << std::endl
#define EXPECT_FALSE(x) std::cout << "Expected false, received " << bool(x) << std::endl

int main(){
    std::cout << "Hello world" << std::endl;
    
    Polynomial<int, int> poly(10);
    std::cout << "a" << std::endl;
    EXPECT_TRUE(poly == 10);
    std::cout << "b" << std::endl;
    poly = 20;
    std::cout << "c" << std::endl;
    EXPECT_TRUE(poly == 20);
    std::cout << "d" << std::endl;
    poly += 10;
    std::cout << "e" << std::endl;
    EXPECT_TRUE(poly == 30);
    std::cout << "f" << std::endl;
    poly -= 5;
    EXPECT_TRUE(poly == 25);
    poly *= 4;
    EXPECT_TRUE(poly == 100);
    std::cout << "g" << std::endl;
    poly /= 20;
    std::cout << "h" << std::endl;
    EXPECT_TRUE(poly == 5);
    std::cout << "i" << std::endl;
    poly %= 2;
    EXPECT_TRUE(poly == 0);

    poly = 10;
    EXPECT_TRUE(poly == 10);
    EXPECT_TRUE(poly + 10 == 20);
    EXPECT_TRUE(poly - 5 == 5);
    EXPECT_TRUE(poly * 5 == 50);
    EXPECT_TRUE(poly / 2 == 5);
    EXPECT_TRUE(poly % 3 == 0);
    return 0;
}