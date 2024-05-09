#include <iostream>
#include <stdio.h>
#include "nurbs.hpp"

#define ASSERT(x) { if (!(x)) std::cout << __FUNCTION__ << " failed on line " << __LINE__ << std::endl; }

bool near(double x, double y){
    double dist = abs(x - y);
    return dist < 1e-15;
}

void test_eval_single(){
    const unsigned short degree = 4;
    const unsigned short npts = 7;

    const KnotVector knotvector = GeneratorKnotVector::uniform(degree, npts);
    const Basis basis(knotvector);

    ASSERT(near(basis(0., 0), 1.));
    ASSERT(near(basis(0., 1), 0.));
    ASSERT(near(basis(0., 2), 0.));
    ASSERT(near(basis(0., 3), 0.));
    ASSERT(near(basis(0., 4), 0.));
    ASSERT(near(basis(0., 5), 0.));
    ASSERT(near(basis(0., 6), 0.));
    ASSERT(near(basis(1./8, 0), 625./4096));
    ASSERT(near(basis(1./8, 1), 18561./32768));
    ASSERT(near(basis(1./8, 2), 8253./32768));
    ASSERT(near(basis(1./8, 3), 459./16384));
    ASSERT(near(basis(1./8, 4), 9./8192));
    ASSERT(near(basis(1./8, 5), 0.));
    ASSERT(near(basis(1./8, 6), 0.));
    ASSERT(near(basis(1./4, 0), 1./256));
    ASSERT(near(basis(1./4, 1), 609./2048));
    ASSERT(near(basis(1./4, 2), 1053./2048));
    ASSERT(near(basis(1./4, 3), 171./1024));
    ASSERT(near(basis(1./4, 4), 9./512));
    ASSERT(near(basis(1./4, 5), 0.));
    ASSERT(near(basis(1./4, 6), 0.));
    ASSERT(near(basis(3./8, 0), 0.));
    ASSERT(near(basis(3./8, 1), 2401./32768));
    ASSERT(near(basis(3./8, 2), 15297./32768));
    ASSERT(near(basis(3./8, 3), 3039./8192));
    ASSERT(near(basis(3./8, 4), 2913./32768));
    ASSERT(near(basis(3./8, 5), 1./32768));
    ASSERT(near(basis(3./8, 6), 0.));
    ASSERT(near(basis(1./2, 0), 0.));
    ASSERT(near(basis(1./2, 1), 1./128));
    ASSERT(near(basis(1./2, 2), 33./128));
    ASSERT(near(basis(1./2, 3), 15./32));
    ASSERT(near(basis(1./2, 4), 33./128));
    ASSERT(near(basis(1./2, 5), 1./128));
    ASSERT(near(basis(1./2, 6), 0.));
    ASSERT(near(basis(5./8, 0), 0.));
    ASSERT(near(basis(5./8, 1), 1./32768));
    ASSERT(near(basis(5./8, 2), 2913./32768));
    ASSERT(near(basis(5./8, 3), 3039./8192));
    ASSERT(near(basis(5./8, 4), 15297./32768));
    ASSERT(near(basis(5./8, 5), 2401./32768));
    ASSERT(near(basis(5./8, 6), 0.));
    ASSERT(near(basis(3./4, 0), 0.));
    ASSERT(near(basis(3./4, 1), 0.));
    ASSERT(near(basis(3./4, 2), 9./512));
    ASSERT(near(basis(3./4, 3), 171./1024));
    ASSERT(near(basis(3./4, 4), 1053./2048));
    ASSERT(near(basis(3./4, 5), 609./2048));
    ASSERT(near(basis(3./4, 6), 1./256));
    ASSERT(near(basis(7./8, 0), 0.));
    ASSERT(near(basis(7./8, 1), 0.));
    ASSERT(near(basis(7./8, 2), 9./8192));
    ASSERT(near(basis(7./8, 3), 459./16384));
    ASSERT(near(basis(7./8, 4), 8253./32768));
    ASSERT(near(basis(7./8, 5), 18561./32768));
    ASSERT(near(basis(7./8, 6), 625./4096));
    ASSERT(near(basis(1., 0), 0.));
    ASSERT(near(basis(1., 1), 0.));
    ASSERT(near(basis(1., 2), 0.));
    ASSERT(near(basis(1., 3), 0.));
    ASSERT(near(basis(1., 4), 0.));
    ASSERT(near(basis(1., 5), 0.));
    ASSERT(near(basis(1., 6), 1.));
}

void test_eval_vector(){

    const unsigned short degree = 4;
    const unsigned short npts = 7;

    const KnotVector knotvector = GeneratorKnotVector::uniform(degree, npts);
    const Basis basis(knotvector);

    std::vector<double> output(npts);
    std::vector<double> results = {0., 1./32768, 2913./32768, 3039./8192, 15297./32768, 2401./32768, 0.};

    basis.evaluate(5./8, output);
    for(unsigned short i=0; i<npts; i++)
        ASSERT(near(output[i], results[i]));

}


int main() {
    test_eval_single();
    test_eval_vector();
    std::cout << "Finished test_basis file" << std::endl;
    return 0;
}
