#include <iostream>
#include "nurbs.hpp"

#define IS_TRUE(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }




void test_binom(){
    IS_TRUE(Math::binom(0, 0) == 1);

    IS_TRUE(Math::binom(1, 0) == 1);
    IS_TRUE(Math::binom(1, 1) == 1);

    IS_TRUE(Math::binom(2, 0) == 1);
    IS_TRUE(Math::binom(2, 1) == 2);
    IS_TRUE(Math::binom(2, 0) == 1);

    IS_TRUE(Math::binom(3, 0) == 1);
    IS_TRUE(Math::binom(3, 1) == 3);
    IS_TRUE(Math::binom(3, 2) == 3);
    IS_TRUE(Math::binom(3, 0) == 1);
    
    IS_TRUE(Math::binom(4, 0) == 1);
    IS_TRUE(Math::binom(4, 1) == 4);
    IS_TRUE(Math::binom(4, 2) == 6);
    IS_TRUE(Math::binom(4, 3) == 4);
    IS_TRUE(Math::binom(4, 4) == 1);

    IS_TRUE(Math::binom(5, 0) == 1);
    IS_TRUE(Math::binom(5, 1) == 5);
    IS_TRUE(Math::binom(5, 2) == 10);
    IS_TRUE(Math::binom(5, 3) == 10);
    IS_TRUE(Math::binom(5, 4) == 5);
    IS_TRUE(Math::binom(5, 5) == 1);

    IS_TRUE(Math::binom(6, 0) == 1);
    IS_TRUE(Math::binom(6, 1) == 6);
    IS_TRUE(Math::binom(6, 2) == 15);
    IS_TRUE(Math::binom(6, 3) == 20);
    IS_TRUE(Math::binom(6, 4) == 15);
    IS_TRUE(Math::binom(6, 5) == 6);
    IS_TRUE(Math::binom(6, 6) == 1);

    IS_TRUE(Math::binom(7, 0) == 1);
    IS_TRUE(Math::binom(7, 1) == 7);
    IS_TRUE(Math::binom(7, 2) == 21);
    IS_TRUE(Math::binom(7, 3) == 35);
    IS_TRUE(Math::binom(7, 4) == 35);
    IS_TRUE(Math::binom(7, 5) == 21);
    IS_TRUE(Math::binom(7, 6) == 7);
    IS_TRUE(Math::binom(7, 7) == 1);

    IS_TRUE(Math::binom(8, 0) == 1);
    IS_TRUE(Math::binom(8, 1) == 8);
    IS_TRUE(Math::binom(8, 2) == 28);
    IS_TRUE(Math::binom(8, 3) == 56);
    IS_TRUE(Math::binom(8, 4) == 70);
    IS_TRUE(Math::binom(8, 5) == 56);
    IS_TRUE(Math::binom(8, 6) == 28);
    IS_TRUE(Math::binom(8, 7) == 8);
    IS_TRUE(Math::binom(8, 8) == 1);

    IS_TRUE(Math::binom(9, 0) == 1);
    IS_TRUE(Math::binom(9, 1) == 9);
    IS_TRUE(Math::binom(9, 2) == 36);
    IS_TRUE(Math::binom(9, 3) == 84);
    IS_TRUE(Math::binom(9, 4) == 126);

    IS_TRUE(Math::binom(10, 0) == 1);
    IS_TRUE(Math::binom(10, 1) == 10);
    IS_TRUE(Math::binom(10, 2) == 45);
    IS_TRUE(Math::binom(10, 3) == 120);
    IS_TRUE(Math::binom(10, 4) == 210);
    IS_TRUE(Math::binom(10, 5) == 252);

    IS_TRUE(Math::binom(11, 0) == 1);
    IS_TRUE(Math::binom(11, 1) == 11);
    IS_TRUE(Math::binom(11, 2) == 55);
    IS_TRUE(Math::binom(11, 3) == 165);
    IS_TRUE(Math::binom(11, 4) == 330);
    IS_TRUE(Math::binom(11, 5) == 462);

    IS_TRUE(Math::binom(12, 0) == 1);
    IS_TRUE(Math::binom(12, 1) == 12);
    IS_TRUE(Math::binom(12, 2) == 66);
    IS_TRUE(Math::binom(12, 3) == 220);
    IS_TRUE(Math::binom(12, 4) == 495);
    IS_TRUE(Math::binom(12, 5) == 792);
    IS_TRUE(Math::binom(12, 6) == 924);

    IS_TRUE(Math::binom(13, 0) == 1);
    IS_TRUE(Math::binom(13, 1) == 13);
    IS_TRUE(Math::binom(13, 2) == 78);
    IS_TRUE(Math::binom(13, 3) == 286);
    IS_TRUE(Math::binom(13, 4) == 715);
    IS_TRUE(Math::binom(13, 5) == 1287);
    IS_TRUE(Math::binom(13, 6) == 1716);

    IS_TRUE(Math::binom(14, 0) == 1);
    IS_TRUE(Math::binom(14, 1) == 14);
    IS_TRUE(Math::binom(14, 2) == 91);
    IS_TRUE(Math::binom(14, 3) == 364);
    IS_TRUE(Math::binom(14, 4) == 1001);
    IS_TRUE(Math::binom(14, 5) == 2002);
    IS_TRUE(Math::binom(14, 6) == 3003);
    IS_TRUE(Math::binom(14, 7) == 3432);

    IS_TRUE(Math::binom(15, 0) == 1);
    IS_TRUE(Math::binom(15, 1) == 15);
    IS_TRUE(Math::binom(15, 2) == 105);
    IS_TRUE(Math::binom(15, 3) == 455);
    IS_TRUE(Math::binom(15, 4) == 1365);
    IS_TRUE(Math::binom(15, 5) == 3003);
    IS_TRUE(Math::binom(15, 6) == 5005);
    IS_TRUE(Math::binom(15, 7) == 6435);

    IS_TRUE(Math::binom(16, 0) == 1);
    IS_TRUE(Math::binom(16, 1) == 16);
    IS_TRUE(Math::binom(16, 2) == 120);
    IS_TRUE(Math::binom(16, 3) == 560);
    IS_TRUE(Math::binom(16, 4) == 1820);
    IS_TRUE(Math::binom(16, 5) == 4368);
    IS_TRUE(Math::binom(16, 6) == 8008);
    IS_TRUE(Math::binom(16, 7) == 11440);
    IS_TRUE(Math::binom(16, 8) == 12870);

    IS_TRUE(Math::binom(17, 0) == 1);
    IS_TRUE(Math::binom(17, 1) == 17);
    IS_TRUE(Math::binom(17, 2) == 136);
    IS_TRUE(Math::binom(17, 3) == 680);
    IS_TRUE(Math::binom(17, 4) == 2380);
    IS_TRUE(Math::binom(17, 5) == 6188);
    IS_TRUE(Math::binom(17, 6) == 12376);
    IS_TRUE(Math::binom(17, 7) == 19448);
    IS_TRUE(Math::binom(17, 8) == 24310);

    IS_TRUE(Math::binom(18, 0) == 1);
    IS_TRUE(Math::binom(18, 1) == 18);
    IS_TRUE(Math::binom(18, 2) == 153);
    IS_TRUE(Math::binom(18, 3) == 816);
    IS_TRUE(Math::binom(18, 4) == 3060);
    IS_TRUE(Math::binom(18, 5) == 8568);
    IS_TRUE(Math::binom(18, 6) == 18564);
    IS_TRUE(Math::binom(18, 7) == 31824);
    IS_TRUE(Math::binom(18, 8) == 43758);
    // IS_TRUE(Math::binom(18, 9) == 48620);
}



void test_bezier()
{
    IS_TRUE(Math::bezier(0, 0, 0) == 1);
    IS_TRUE(Math::bezier(0.5, 0, 0) == 1);
    IS_TRUE(Math::bezier(1, 0, 0) == 1);
    IS_TRUE(Math::bezier(0, 1, 0) == 1);
    IS_TRUE(Math::bezier(0.5, 1, 0) == 0.5);
    IS_TRUE(Math::bezier(1, 1, 0) == 0);
    IS_TRUE(Math::bezier(0, 1, 1) == 0);
    IS_TRUE(Math::bezier(0.5, 1, 1) == 0.5);
    IS_TRUE(Math::bezier(1, 1, 1) == 1);
};



void test_degree()
{
    KnotVector<double> knotvector0({0, 1});
    IS_TRUE(knotvector0.degree == 0);
    KnotVector<double> knotvector1({0, 0, 1, 1});
    IS_TRUE(knotvector1.degree == 1);
    KnotVector<double> knotvector2({0, 0, 0, 1, 1, 1});
    IS_TRUE(knotvector2.degree == 2);
    KnotVector<double> knotvector3({0, 0, 0, 0, 1, 1, 1, 1});
    IS_TRUE(knotvector3.degree == 3);
    KnotVector<double> knotvector4({0, 0, 0.5, 1, 1});
    IS_TRUE(knotvector4.degree == 1);
    KnotVector<double> knotvector5({0, 0, 0, 0.5, 1, 1, 1});
    IS_TRUE(knotvector5.degree == 2);
    KnotVector<double> knotvector6({0, 0, 0, 0, 0.5, 1, 1, 1, 1});
    IS_TRUE(knotvector6.degree == 3);
};


void test_npts()
{
    KnotVector<double> knotvector0({0, 1});
    IS_TRUE(knotvector0.npts == 1);
    KnotVector<double> knotvector1({0, 0, 1, 1});
    IS_TRUE(knotvector1.npts == 2);
    KnotVector<double> knotvector2({0, 0, 0, 1, 1, 1});
    IS_TRUE(knotvector2.npts == 3);
    KnotVector<double> knotvector3({0, 0, 0, 0, 1, 1, 1, 1});
    IS_TRUE(knotvector3.npts == 4);
    KnotVector<double> knotvector4({0, 0, 0.5, 1, 1});
    IS_TRUE(knotvector4.npts == 3);
    KnotVector<double> knotvector5({0, 0, 0, 0.5, 1, 1, 1});
    IS_TRUE(knotvector5.npts == 4);
    KnotVector<double> knotvector6({0, 0, 0, 0, 0.5, 1, 1, 1, 1});
    IS_TRUE(knotvector6.npts == 5);
};



void test_generate_bezier(){
    unsigned short degree;
    for(degree=0; degree<10; degree++){
        const unsigned short npts = degree + 1;
        KnotVector<double> knotvector = GeneratorKnotVector::bezier<double>(degree);
        IS_TRUE(knotvector.degree == degree);
        IS_TRUE(knotvector.npts == degree+1);
        IS_TRUE(knotvector[0] == 0);
        IS_TRUE(knotvector[degree] == 0);
        IS_TRUE(knotvector[npts] == 1);
        IS_TRUE(knotvector[degree+npts] == 1);
    }
};


void test_generate_uniform(){
    unsigned short degree, npts;
    for(degree=0; degree<10; degree++)
        for(npts=degree+1; npts<degree+10; npts++){
            KnotVector<double> knotvector = GeneratorKnotVector::uniform<double>(degree, npts);
            IS_TRUE(knotvector.degree == degree);
            IS_TRUE(knotvector.npts == npts);
            IS_TRUE(knotvector[0] == 0);
            IS_TRUE(knotvector[degree] == 0);
            IS_TRUE(knotvector[npts] == 1);
            IS_TRUE(knotvector[degree+npts] == 1);
        }
};


void test_span(){
    unsigned short degree, npts;
    for(degree=0; degree<10; degree++){ // Bezier
        npts = degree + 1;
        KnotVector<double> knotvector = GeneratorKnotVector::bezier<double>(degree);
        IS_TRUE(knotvector.span(0) == degree);
        IS_TRUE(knotvector.span(0.5) == degree);
        IS_TRUE(knotvector.span(1) == degree);
    }
    
    for(degree=0; degree<4; degree++) // Uniform
        for(npts=degree+1; npts<degree+5; npts++){
            KnotVector<double> knotvector = GeneratorKnotVector::uniform<double>(degree, npts);
            IS_TRUE(knotvector.span(0) == degree);
            IS_TRUE(knotvector.span(1) == npts-1);
        }
    KnotVector<double> knotvector({0, 0, 0, 1, 2, 2, 3, 4, 4, 4});
    IS_TRUE(knotvector.span(0) == 2);
    IS_TRUE(knotvector.span(0.5) == 2);
    IS_TRUE(knotvector.span(1) == 3);
    IS_TRUE(knotvector.span(1.5) == 3);
    IS_TRUE(knotvector.span(2) == 5);
    IS_TRUE(knotvector.span(2.5) == 5);
    IS_TRUE(knotvector.span(3) == 6);
    IS_TRUE(knotvector.span(3.5) == 6);
    IS_TRUE(knotvector.span(4) == 6);
};


void test_mult(){
    unsigned short degree, npts;
    for(
        degree=0; degree<10; degree++){ // Bezier
        KnotVector<double> knotvector = GeneratorKnotVector::bezier<double>(degree);
        IS_TRUE(knotvector.mult(0) == degree + 1);
        IS_TRUE(knotvector.mult(0.5) == 0);
        IS_TRUE(knotvector.mult(1) == degree + 1);
    }
    for(degree=0; degree<10; degree++) // Uniform
        for(npts=degree+1; npts<degree+4; npts++){
            KnotVector<double> knotvector = GeneratorKnotVector::uniform<double>(degree, npts);
            IS_TRUE(knotvector.mult(0) == degree + 1);
            IS_TRUE(knotvector.mult(1) == degree + 1);
        }
    KnotVector<double> knotvector({0, 0, 0, 1, 2, 2, 3, 4, 4, 4});
    IS_TRUE(knotvector.mult(0) == 3);
    IS_TRUE(knotvector.mult(0.5) == 0);
    IS_TRUE(knotvector.mult(1) == 1);
    IS_TRUE(knotvector.mult(1.5) == 0);
    IS_TRUE(knotvector.mult(2) == 2);
    IS_TRUE(knotvector.mult(2.5) == 0);
    IS_TRUE(knotvector.mult(3) == 1);
    IS_TRUE(knotvector.mult(3.5) == 0);
    IS_TRUE(knotvector.mult(4) == 3);
};


void test_print(){
    KnotVector<double> knotvector = GeneratorKnotVector::uniform<double>(1, 3);
    std::cout << knotvector << std::endl;
};


int main() {
    test_binom();
    test_bezier();
    test_degree();
    test_npts();
    test_generate_bezier();
    test_generate_uniform();
    test_print();
    test_span();
    test_mult();
    return 0;
}
