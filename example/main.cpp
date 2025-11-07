#include <iostream>
#include <unistd.h>

// #include "cshape/polynomial.h"
#include "cshape/scalar.h"

#define EXPECT_TRUE(x) std::cout << (bool(x) ? "    " : "####") << ": Expected true, received " << (bool(x) ? "true" : "false") << std::endl
#define EXPECT_FALSE(x) std::cout << (bool(x) ? "####" : "    ") << ": Expected false, received " << (bool(x) ? "true" : "false") << std::endl

int main(){
    std::cout << "Hello world" << std::endl;
    
    // Polynomial<int, int> poly(10);

    
    /*
    std::cout << "----------" << std::endl;
    // EMPTY and WHOLE
    EXPECT_TRUE(EMPTY == EMPTY);
    EXPECT_FALSE(EMPTY == WHOLE);
    EXPECT_FALSE(WHOLE == EMPTY);
    EXPECT_TRUE(WHOLE == WHOLE);

    std::cout << "----------" << std::endl;
    EXPECT_FALSE(EMPTY != EMPTY);
    EXPECT_TRUE(EMPTY != WHOLE);
    EXPECT_TRUE(WHOLE != EMPTY);
    EXPECT_FALSE(WHOLE != WHOLE);
    
    std::cout << "----------" << std::endl;
    // EMPTY and WHOLE and INF
    EXPECT_FALSE(EMPTY == BOTINF);
    EXPECT_FALSE(WHOLE == BOTINF);
    EXPECT_FALSE(EMPTY == TOPINF);
    EXPECT_FALSE(WHOLE == TOPINF);

    std::cout << "----------" << std::endl;
    EXPECT_FALSE(BOTINF == EMPTY);
    EXPECT_FALSE(BOTINF == WHOLE);
    EXPECT_FALSE(TOPINF == EMPTY);
    EXPECT_FALSE(TOPINF == WHOLE);
    
    std::cout << "----------" << std::endl;
    EXPECT_TRUE(EMPTY != BOTINF);
    EXPECT_TRUE(WHOLE != BOTINF);
    EXPECT_TRUE(EMPTY != TOPINF);
    EXPECT_TRUE(WHOLE != TOPINF);
    
    std::cout << "----------" << std::endl;
    EXPECT_TRUE(BOTINF != EMPTY);
    EXPECT_TRUE(BOTINF != WHOLE);
    EXPECT_TRUE(TOPINF != EMPTY);
    EXPECT_TRUE(TOPINF != WHOLE);

    std::cout << "----------" << std::endl;
    // BOT with BOT
    EXPECT_TRUE(BOTINF == BOTINF);
    EXPECT_FALSE(BOTINF != BOTINF);
    EXPECT_FALSE(BOTINF < BOTINF);
    EXPECT_TRUE(BOTINF <= BOTINF);
    EXPECT_TRUE(BOTINF >= BOTINF);
    EXPECT_FALSE(BOTINF > BOTINF);

    std::cout << "----------" << std::endl;
    // TOP with TOP
    EXPECT_TRUE(TOPINF == TOPINF);
    EXPECT_FALSE(TOPINF != TOPINF);
    EXPECT_FALSE(TOPINF < TOPINF);
    EXPECT_TRUE(TOPINF <= TOPINF);
    EXPECT_TRUE(TOPINF >= TOPINF);
    EXPECT_FALSE(TOPINF > TOPINF);

    std::cout << "----------" << std::endl;
    // BOT with TOP
    EXPECT_FALSE(BOTINF == TOPINF);
    EXPECT_TRUE(BOTINF != TOPINF);
    EXPECT_TRUE(BOTINF < TOPINF);
    EXPECT_TRUE(BOTINF <= TOPINF);
    EXPECT_FALSE(BOTINF >= TOPINF);
    EXPECT_FALSE(BOTINF > TOPINF);
    
    std::cout << "----------" << std::endl;
    // TOP with BOT
    EXPECT_FALSE(TOPINF == BOTINF);
    EXPECT_TRUE(TOPINF != BOTINF);
    EXPECT_FALSE(TOPINF < BOTINF);
    EXPECT_FALSE(TOPINF <= BOTINF);
    EXPECT_TRUE(TOPINF >= BOTINF);
    EXPECT_TRUE(TOPINF > BOTINF);
    */
}