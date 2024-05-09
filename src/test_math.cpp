#include <iostream>
#include <stdio.h>
#include "math.hpp"

#define ASSERT(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }


void test_binom(){
    ASSERT(Math::binom(0, 0) == 1);

    ASSERT(Math::binom(1, 0) == 1);
    ASSERT(Math::binom(1, 1) == 1);

    ASSERT(Math::binom(2, 0) == 1);
    ASSERT(Math::binom(2, 1) == 2);
    ASSERT(Math::binom(2, 0) == 1);

    ASSERT(Math::binom(3, 0) == 1);
    ASSERT(Math::binom(3, 1) == 3);
    ASSERT(Math::binom(3, 2) == 3);
    ASSERT(Math::binom(3, 0) == 1);
    
    ASSERT(Math::binom(4, 0) == 1);
    ASSERT(Math::binom(4, 1) == 4);
    ASSERT(Math::binom(4, 2) == 6);
    ASSERT(Math::binom(4, 3) == 4);
    ASSERT(Math::binom(4, 4) == 1);

    ASSERT(Math::binom(5, 0) == 1);
    ASSERT(Math::binom(5, 1) == 5);
    ASSERT(Math::binom(5, 2) == 10);
    ASSERT(Math::binom(5, 3) == 10);
    ASSERT(Math::binom(5, 4) == 5);
    ASSERT(Math::binom(5, 5) == 1);

    ASSERT(Math::binom(6, 0) == 1);
    ASSERT(Math::binom(6, 1) == 6);
    ASSERT(Math::binom(6, 2) == 15);
    ASSERT(Math::binom(6, 3) == 20);
    ASSERT(Math::binom(6, 4) == 15);
    ASSERT(Math::binom(6, 5) == 6);
    ASSERT(Math::binom(6, 6) == 1);

    ASSERT(Math::binom(7, 0) == 1);
    ASSERT(Math::binom(7, 1) == 7);
    ASSERT(Math::binom(7, 2) == 21);
    ASSERT(Math::binom(7, 3) == 35);
    ASSERT(Math::binom(7, 4) == 35);
    ASSERT(Math::binom(7, 5) == 21);
    ASSERT(Math::binom(7, 6) == 7);
    ASSERT(Math::binom(7, 7) == 1);

    ASSERT(Math::binom(8, 0) == 1);
    ASSERT(Math::binom(8, 1) == 8);
    ASSERT(Math::binom(8, 2) == 28);
    ASSERT(Math::binom(8, 3) == 56);
    ASSERT(Math::binom(8, 4) == 70);
    ASSERT(Math::binom(8, 5) == 56);
    ASSERT(Math::binom(8, 6) == 28);
    ASSERT(Math::binom(8, 7) == 8);
    ASSERT(Math::binom(8, 8) == 1);

    ASSERT(Math::binom(9, 0) == 1);
    ASSERT(Math::binom(9, 1) == 9);
    ASSERT(Math::binom(9, 2) == 36);
    ASSERT(Math::binom(9, 3) == 84);
    ASSERT(Math::binom(9, 4) == 126);

    ASSERT(Math::binom(10, 0) == 1);
    ASSERT(Math::binom(10, 1) == 10);
    ASSERT(Math::binom(10, 2) == 45);
    ASSERT(Math::binom(10, 3) == 120);
    ASSERT(Math::binom(10, 4) == 210);
    ASSERT(Math::binom(10, 5) == 252);

    ASSERT(Math::binom(11, 0) == 1);
    ASSERT(Math::binom(11, 1) == 11);
    ASSERT(Math::binom(11, 2) == 55);
    ASSERT(Math::binom(11, 3) == 165);
    ASSERT(Math::binom(11, 4) == 330);
    ASSERT(Math::binom(11, 5) == 462);

    ASSERT(Math::binom(12, 0) == 1);
    ASSERT(Math::binom(12, 1) == 12);
    ASSERT(Math::binom(12, 2) == 66);
    ASSERT(Math::binom(12, 3) == 220);
    ASSERT(Math::binom(12, 4) == 495);
    ASSERT(Math::binom(12, 5) == 792);
    ASSERT(Math::binom(12, 6) == 924);

    ASSERT(Math::binom(13, 0) == 1);
    ASSERT(Math::binom(13, 1) == 13);
    ASSERT(Math::binom(13, 2) == 78);
    ASSERT(Math::binom(13, 3) == 286);
    ASSERT(Math::binom(13, 4) == 715);
    ASSERT(Math::binom(13, 5) == 1287);
    ASSERT(Math::binom(13, 6) == 1716);

    ASSERT(Math::binom(14, 0) == 1);
    ASSERT(Math::binom(14, 1) == 14);
    ASSERT(Math::binom(14, 2) == 91);
    ASSERT(Math::binom(14, 3) == 364);
    ASSERT(Math::binom(14, 4) == 1001);
    ASSERT(Math::binom(14, 5) == 2002);
    ASSERT(Math::binom(14, 6) == 3003);
    ASSERT(Math::binom(14, 7) == 3432);

    ASSERT(Math::binom(15, 0) == 1);
    ASSERT(Math::binom(15, 1) == 15);
    ASSERT(Math::binom(15, 2) == 105);
    ASSERT(Math::binom(15, 3) == 455);
    ASSERT(Math::binom(15, 4) == 1365);
    ASSERT(Math::binom(15, 5) == 3003);
    ASSERT(Math::binom(15, 6) == 5005);
    ASSERT(Math::binom(15, 7) == 6435);

    ASSERT(Math::binom(16, 0) == 1);
    ASSERT(Math::binom(16, 1) == 16);
    ASSERT(Math::binom(16, 2) == 120);
    ASSERT(Math::binom(16, 3) == 560);
    ASSERT(Math::binom(16, 4) == 1820);
    ASSERT(Math::binom(16, 5) == 4368);
    ASSERT(Math::binom(16, 6) == 8008);
    ASSERT(Math::binom(16, 7) == 11440);
    ASSERT(Math::binom(16, 8) == 12870);

    ASSERT(Math::binom(17, 0) == 1);
    ASSERT(Math::binom(17, 1) == 17);
    ASSERT(Math::binom(17, 2) == 136);
    ASSERT(Math::binom(17, 3) == 680);
    ASSERT(Math::binom(17, 4) == 2380);
    ASSERT(Math::binom(17, 5) == 6188);
    ASSERT(Math::binom(17, 6) == 12376);
    ASSERT(Math::binom(17, 7) == 19448);
    ASSERT(Math::binom(17, 8) == 24310);

    ASSERT(Math::binom(18, 0) == 1);
    ASSERT(Math::binom(18, 1) == 18);
    ASSERT(Math::binom(18, 2) == 153);
    ASSERT(Math::binom(18, 3) == 816);
    ASSERT(Math::binom(18, 4) == 3060);
    ASSERT(Math::binom(18, 5) == 8568);
    ASSERT(Math::binom(18, 6) == 18564);
    ASSERT(Math::binom(18, 7) == 31824);
    ASSERT(Math::binom(18, 8) == 43758);
    // ASSERT(Math::binom(18, 9) == 48620);
}



void test_bezier()
{
    ASSERT(Math::bezier(0, 0, 0) == 1);
    ASSERT(Math::bezier(0.5, 0, 0) == 1);
    ASSERT(Math::bezier(1, 0, 0) == 1);
    ASSERT(Math::bezier(0, 1, 0) == 1);
    ASSERT(Math::bezier(0.5, 1, 0) == 0.5);
    ASSERT(Math::bezier(1, 1, 0) == 0);
    ASSERT(Math::bezier(0, 1, 1) == 0);
    ASSERT(Math::bezier(0.5, 1, 1) == 0.5);
    ASSERT(Math::bezier(1, 1, 1) == 1);
};


int main(int argc, char *argv[]) {
    test_binom();
    test_bezier();
    std::cout << "Finished test_math file" << std::endl;
    return 0;
}
