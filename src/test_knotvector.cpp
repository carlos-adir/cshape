#include <iostream>
#include <stdio.h>
#include "nurbs.hpp"

#define ASSERT(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }


void test_degree()
{
    KnotVector knotvector0({0, 1});
    ASSERT(knotvector0.degree == 0);
    KnotVector knotvector1({0, 0, 1, 1});
    ASSERT(knotvector1.degree == 1);
    KnotVector knotvector2({0, 0, 0, 1, 1, 1});
    ASSERT(knotvector2.degree == 2);
    KnotVector knotvector3({0, 0, 0, 0, 1, 1, 1, 1});
    ASSERT(knotvector3.degree == 3);
    KnotVector knotvector4({0, 0, 0.5, 1, 1});
    ASSERT(knotvector4.degree == 1);
    KnotVector knotvector5({0, 0, 0, 0.5, 1, 1, 1});
    ASSERT(knotvector5.degree == 2);
    KnotVector knotvector6({0, 0, 0, 0, 0.5, 1, 1, 1, 1});
    ASSERT(knotvector6.degree == 3);
};


void test_npts()
{
    KnotVector knotvector0({0, 1});
    ASSERT(knotvector0.npts == 1);
    KnotVector knotvector1({0, 0, 1, 1});
    ASSERT(knotvector1.npts == 2);
    KnotVector knotvector2({0, 0, 0, 1, 1, 1});
    ASSERT(knotvector2.npts == 3);
    KnotVector knotvector3({0, 0, 0, 0, 1, 1, 1, 1});
    ASSERT(knotvector3.npts == 4);
    KnotVector knotvector4({0, 0, 0.5, 1, 1});
    ASSERT(knotvector4.npts == 3);
    KnotVector knotvector5({0, 0, 0, 0.5, 1, 1, 1});
    ASSERT(knotvector5.npts == 4);
    KnotVector knotvector6({0, 0, 0, 0, 0.5, 1, 1, 1, 1});
    ASSERT(knotvector6.npts == 5);
};



void test_generate_bezier(){
    unsigned short degree;
    for(degree=0; degree<10; degree++){
        const unsigned short npts = degree + 1;
        KnotVector knotvector = GeneratorKnotVector::bezier(degree);
        ASSERT(knotvector.degree == degree);
        ASSERT(knotvector.npts == degree+1);
        ASSERT(knotvector[0] == 0);
        ASSERT(knotvector[degree] == 0);
        ASSERT(knotvector[npts] == 1);
        ASSERT(knotvector[degree+npts] == 1);
    }
};


void test_generate_uniform(){
    unsigned short degree, npts;
    for(degree=0; degree<10; degree++)
        for(npts=degree+1; npts<degree+10; npts++){
            KnotVector knotvector = GeneratorKnotVector::uniform(degree, npts);
            ASSERT(knotvector.degree == degree);
            ASSERT(knotvector.npts == npts);
            ASSERT(knotvector[0] == 0);
            ASSERT(knotvector[degree] == 0);
            ASSERT(knotvector[npts] == 1);
            ASSERT(knotvector[degree+npts] == 1);
        }
};


void test_span(){
    unsigned short degree, npts;
    for(degree=0; degree<10; degree++){ // Bezier
        npts = degree + 1;
        KnotVector knotvector = GeneratorKnotVector::bezier(degree);
        ASSERT(knotvector.span(0) == degree);
        ASSERT(knotvector.span(0.5) == degree);
        ASSERT(knotvector.span(1) == degree);
    }
    
    for(degree=0; degree<4; degree++) // Uniform
        for(npts=degree+1; npts<degree+5; npts++){
            KnotVector knotvector = GeneratorKnotVector::uniform(degree, npts);
            ASSERT(knotvector.span(0) == degree);
            ASSERT(knotvector.span(1) == npts-1);
        }
    KnotVector knotvector({0, 0, 0, 1, 2, 2, 3, 4, 4, 4});
    ASSERT(knotvector.span(0) == 2);
    ASSERT(knotvector.span(0.5) == 2);
    ASSERT(knotvector.span(1) == 3);
    ASSERT(knotvector.span(1.5) == 3);
    ASSERT(knotvector.span(2) == 5);
    ASSERT(knotvector.span(2.5) == 5);
    ASSERT(knotvector.span(3) == 6);
    ASSERT(knotvector.span(3.5) == 6);
    ASSERT(knotvector.span(4) == 6);
};


void test_mult(){
    unsigned short degree, npts;
    for(
        degree=0; degree<10; degree++){ // Bezier
        KnotVector knotvector = GeneratorKnotVector::bezier(degree);
        ASSERT(knotvector.mult(0) == degree + 1);
        ASSERT(knotvector.mult(0.5) == 0);
        ASSERT(knotvector.mult(1) == degree + 1);
    }
    for(degree=0; degree<10; degree++) // Uniform
        for(npts=degree+1; npts<degree+4; npts++){
            KnotVector knotvector = GeneratorKnotVector::uniform(degree, npts);
            ASSERT(knotvector.mult(0) == degree + 1);
            ASSERT(knotvector.mult(1) == degree + 1);
        }
    KnotVector knotvector({0, 0, 0, 1, 2, 2, 3, 4, 4, 4});
    ASSERT(knotvector.mult(0) == 3);
    ASSERT(knotvector.mult(0.5) == 0);
    ASSERT(knotvector.mult(1) == 1);
    ASSERT(knotvector.mult(1.5) == 0);
    ASSERT(knotvector.mult(2) == 2);
    ASSERT(knotvector.mult(2.5) == 0);
    ASSERT(knotvector.mult(3) == 1);
    ASSERT(knotvector.mult(3.5) == 0);
    ASSERT(knotvector.mult(4) == 3);
};


void test_print(){
    KnotVector knotvector = GeneratorKnotVector::uniform(1, 3);
    std::cout << knotvector << std::endl;
};


int main(int argc, char *argv[]) {
    test_degree();
    test_npts();
    test_generate_bezier();
    test_generate_uniform();
    test_print();
    std::cout << "Finished test_knotvector file" << std::endl;
    return 0;
}
