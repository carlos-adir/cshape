#include <gtest/gtest.h>
#include "cshape/nurbs.h"

TEST(KnotVectorTest, Bezier0) {
    KnotVector knotvector({0, 1});
    EXPECT_EQ(knotvector.degree, 0);
    EXPECT_EQ(knotvector.npts, 1);
    EXPECT_EQ(knotvector[0], 0);
    EXPECT_EQ(knotvector[1], 1);
}

TEST(KnotVectorTest, Bezier1) {
    KnotVector knotvector({0, 0, 1, 1});
    EXPECT_EQ(knotvector.degree, 1);
    EXPECT_EQ(knotvector.npts, 2);
    EXPECT_EQ(knotvector[0], 0);
    EXPECT_EQ(knotvector[1], 0);
    EXPECT_EQ(knotvector[2], 1);
    EXPECT_EQ(knotvector[3], 1);
}

TEST(KnotVectorTest, Bezier2) {
    KnotVector knotvector({0, 0, 0, 1, 1, 1});
    EXPECT_EQ(knotvector.degree, 2);
    EXPECT_EQ(knotvector.npts, 3);
    EXPECT_EQ(knotvector[0], 0);
    EXPECT_EQ(knotvector[1], 0);
    EXPECT_EQ(knotvector[2], 0);
    EXPECT_EQ(knotvector[3], 1);
    EXPECT_EQ(knotvector[4], 1);
    EXPECT_EQ(knotvector[5], 1);
}

TEST(KnotVectorTest, Bezier3) {
    KnotVector knotvector({0, 0, 0, 0, 1, 1, 1, 1});
    EXPECT_EQ(knotvector.degree, 3);
    EXPECT_EQ(knotvector.npts, 4);
    EXPECT_EQ(knotvector[0], 0);
    EXPECT_EQ(knotvector[1], 0);
    EXPECT_EQ(knotvector[2], 0);
    EXPECT_EQ(knotvector[3], 0);
    EXPECT_EQ(knotvector[4], 1);
    EXPECT_EQ(knotvector[5], 1);
    EXPECT_EQ(knotvector[6], 1);
    EXPECT_EQ(knotvector[7], 1);
}

TEST(KnotVectorTest, Uniform0) {
    KnotVector knotvector({0, 0.5, 1});
    EXPECT_EQ(knotvector.degree, 0);
    EXPECT_EQ(knotvector.npts, 2);
    EXPECT_EQ(knotvector[0], 0);
    EXPECT_EQ(knotvector[1], 0.5);
    EXPECT_EQ(knotvector[2], 1);
}

TEST(KnotVectorTest, Uniform1) {
    KnotVector knotvector({0, 0, 0.5, 1, 1});
    EXPECT_EQ(knotvector.degree, 1);
    EXPECT_EQ(knotvector.npts, 3);
    EXPECT_EQ(knotvector[0], 0);
    EXPECT_EQ(knotvector[1], 0);
    EXPECT_EQ(knotvector[2], 0.5);
    EXPECT_EQ(knotvector[3], 1);
    EXPECT_EQ(knotvector[4], 1);
}

TEST(KnotVectorTest, Uniform2) {
    KnotVector knotvector({0, 0, 0, 0.5, 1, 1, 1});
    EXPECT_EQ(knotvector.degree, 2);
    EXPECT_EQ(knotvector.npts, 4);
    EXPECT_EQ(knotvector[0], 0);
    EXPECT_EQ(knotvector[1], 0);
    EXPECT_EQ(knotvector[2], 0);
    EXPECT_EQ(knotvector[3], 0.5);
    EXPECT_EQ(knotvector[4], 1);
    EXPECT_EQ(knotvector[5], 1);
    EXPECT_EQ(knotvector[6], 1);
}

TEST(GeneratorKnotVectorTest, Bezier){
    unsigned short degree, npts;
    for(degree=0; degree<10; degree++){
        npts = degree + 1;
        KnotVector knotvector = GeneratorKnotVector::bezier(degree);
        EXPECT_EQ(knotvector.degree, degree);
        EXPECT_EQ(knotvector.npts, degree+1);
        EXPECT_EQ(knotvector[0], 0);
        EXPECT_EQ(knotvector[degree], 0);
        EXPECT_EQ(knotvector[npts], 1);
        EXPECT_EQ(knotvector[degree+npts], 1);
    }
}

TEST(GeneratorKnotVectorTest, Uniform){
    unsigned short degree, npts;
    for(degree=0; degree<10; degree++){
        for(npts=degree+1; npts<degree+10; npts++){
            KnotVector knotvector = GeneratorKnotVector::uniform(degree, npts);
            EXPECT_EQ(knotvector.degree, degree);
            EXPECT_EQ(knotvector.npts, npts);
            EXPECT_EQ(knotvector[0], 0);
            EXPECT_EQ(knotvector[degree], 0);
            EXPECT_EQ(knotvector[npts], 1);
            EXPECT_EQ(knotvector[degree+npts], 1);
        }
    }
}

TEST(KnotVectorTest, BezierSpan){
    unsigned short degree;
    for(degree=0; degree<10; degree++){
        KnotVector knotvector = GeneratorKnotVector::bezier(degree);
        EXPECT_EQ(knotvector.span(0), degree);
        EXPECT_EQ(knotvector.span(0.5), degree);
        EXPECT_EQ(knotvector.span(1), degree);
    }
}


TEST(KnotVectorTest, UniformSpan){
    unsigned short degree, npts;
    for(degree=0; degree<4; degree++){
        for(npts=degree+1; npts<degree+5; npts++){
            KnotVector knotvector = GeneratorKnotVector::uniform(degree, npts);
            EXPECT_EQ(knotvector.span(0), degree);
            EXPECT_EQ(knotvector.span(1), npts-1);
        }
    }
}


TEST(KnotVectorTest, BezierMult){
    unsigned short degree;
    for(degree=0; degree<10; degree++){
        KnotVector knotvector = GeneratorKnotVector::bezier(degree);
        EXPECT_EQ(knotvector.mult(0), degree + 1);
        EXPECT_EQ(knotvector.mult(0.5), 0);
        EXPECT_EQ(knotvector.mult(1), degree + 1);
    }
}


TEST(KnotVectorTest, UniformMult){
    unsigned short degree, npts;
    for(degree=0; degree<4; degree++){
        for(npts=degree+1; npts<degree+5; npts++){
            KnotVector knotvector = GeneratorKnotVector::uniform(degree, npts);
            EXPECT_EQ(knotvector.mult(0), degree + 1);
            EXPECT_EQ(knotvector.mult(1), degree + 1);
        }
    }
}
    
TEST(KnotVectorTest, CustomSpan){
    KnotVector knotvector({0, 0, 0, 1, 2, 2, 3, 4, 4, 4});
    EXPECT_EQ(knotvector.span(0), 2);
    EXPECT_EQ(knotvector.span(0.5), 2);
    EXPECT_EQ(knotvector.span(1), 3);
    EXPECT_EQ(knotvector.span(1.5), 3);
    EXPECT_EQ(knotvector.span(2), 5);
    EXPECT_EQ(knotvector.span(2.5), 5);
    EXPECT_EQ(knotvector.span(3), 6);
    EXPECT_EQ(knotvector.span(3.5), 6);
    EXPECT_EQ(knotvector.span(4), 6);
}

TEST(KnotVectorTest, CustomMult){
    KnotVector knotvector({0, 0, 0, 1, 2, 2, 3, 4, 4, 4});
    EXPECT_EQ(knotvector.mult(0), 3);
    EXPECT_EQ(knotvector.mult(0.5), 0);
    EXPECT_EQ(knotvector.mult(1), 1);
    EXPECT_EQ(knotvector.mult(1.5), 0);
    EXPECT_EQ(knotvector.mult(2), 2);
    EXPECT_EQ(knotvector.mult(2.5), 0);
    EXPECT_EQ(knotvector.mult(3), 1);
    EXPECT_EQ(knotvector.mult(3.5), 0);
    EXPECT_EQ(knotvector.mult(4), 3);
}
