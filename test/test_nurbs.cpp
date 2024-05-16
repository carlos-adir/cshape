#include <gtest/gtest.h>
#include "cshape/nurbs.h"

TEST(KnotVectorTest, Bezier0)
{
    KnotVector knotvector({0, 1});
    EXPECT_EQ(knotvector.degree, 0);
    EXPECT_EQ(knotvector.npts, 1);
    EXPECT_EQ(knotvector[0], 0);
    EXPECT_EQ(knotvector[1], 1);
}

TEST(KnotVectorTest, Bezier1)
{
    KnotVector knotvector({0, 0, 1, 1});
    EXPECT_EQ(knotvector.degree, 1);
    EXPECT_EQ(knotvector.npts, 2);
    EXPECT_EQ(knotvector[0], 0);
    EXPECT_EQ(knotvector[1], 0);
    EXPECT_EQ(knotvector[2], 1);
    EXPECT_EQ(knotvector[3], 1);
}

TEST(KnotVectorTest, Bezier2)
{
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

TEST(KnotVectorTest, Bezier3)
{
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

TEST(KnotVectorTest, Uniform0)
{
    KnotVector knotvector({0, 0.5, 1});
    EXPECT_EQ(knotvector.degree, 0);
    EXPECT_EQ(knotvector.npts, 2);
    EXPECT_EQ(knotvector[0], 0);
    EXPECT_EQ(knotvector[1], 0.5);
    EXPECT_EQ(knotvector[2], 1);
}

TEST(KnotVectorTest, Uniform1)
{
    KnotVector knotvector({0, 0, 0.5, 1, 1});
    EXPECT_EQ(knotvector.degree, 1);
    EXPECT_EQ(knotvector.npts, 3);
    EXPECT_EQ(knotvector[0], 0);
    EXPECT_EQ(knotvector[1], 0);
    EXPECT_EQ(knotvector[2], 0.5);
    EXPECT_EQ(knotvector[3], 1);
    EXPECT_EQ(knotvector[4], 1);
}

TEST(KnotVectorTest, Uniform2)
{
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

TEST(GeneratorKnotVectorTest, Bezier)
{
    unsigned short degree, npts;
    for (degree = 0; degree < 10; degree++)
    {
        npts = degree + 1;
        KnotVector knotvector = GeneratorKnotVector::bezier(degree);
        EXPECT_EQ(knotvector.degree, degree);
        EXPECT_EQ(knotvector.npts, degree + 1);
        EXPECT_EQ(knotvector[0], 0);
        EXPECT_EQ(knotvector[degree], 0);
        EXPECT_EQ(knotvector[npts], 1);
        EXPECT_EQ(knotvector[degree + npts], 1);
    }
}

TEST(GeneratorKnotVectorTest, Uniform)
{
    unsigned short degree, npts;
    for (degree = 0; degree < 10; degree++)
    {
        for (npts = degree + 1; npts < degree + 10; npts++)
        {
            KnotVector knotvector = GeneratorKnotVector::uniform(degree, npts);
            EXPECT_EQ(knotvector.degree, degree);
            EXPECT_EQ(knotvector.npts, npts);
            EXPECT_EQ(knotvector[0], 0);
            EXPECT_EQ(knotvector[degree], 0);
            EXPECT_EQ(knotvector[npts], 1);
            EXPECT_EQ(knotvector[degree + npts], 1);
        }
    }
}

TEST(KnotVectorTest, BezierSpan)
{
    unsigned short degree;
    for (degree = 0; degree < 10; degree++)
    {
        KnotVector knotvector = GeneratorKnotVector::bezier(degree);
        EXPECT_EQ(knotvector.span(0), degree);
        EXPECT_EQ(knotvector.span(0.5), degree);
        EXPECT_EQ(knotvector.span(1), degree);
    }
}

TEST(KnotVectorTest, UniformSpan)
{
    unsigned short degree, npts;
    for (degree = 0; degree < 4; degree++)
    {
        for (npts = degree + 1; npts < degree + 5; npts++)
        {
            KnotVector knotvector = GeneratorKnotVector::uniform(degree, npts);
            EXPECT_EQ(knotvector.span(0), degree);
            EXPECT_EQ(knotvector.span(1), npts - 1);
        }
    }
}

TEST(KnotVectorTest, BezierMult)
{
    unsigned short degree;
    for (degree = 0; degree < 10; degree++)
    {
        KnotVector knotvector = GeneratorKnotVector::bezier(degree);
        EXPECT_EQ(knotvector.mult(0), degree + 1);
        EXPECT_EQ(knotvector.mult(0.5), 0);
        EXPECT_EQ(knotvector.mult(1), degree + 1);
    }
}

TEST(KnotVectorTest, UniformMult)
{
    unsigned short degree, npts;
    for (degree = 0; degree < 4; degree++)
    {
        for (npts = degree + 1; npts < degree + 5; npts++)
        {
            KnotVector knotvector = GeneratorKnotVector::uniform(degree, npts);
            EXPECT_EQ(knotvector.mult(0), degree + 1);
            EXPECT_EQ(knotvector.mult(1), degree + 1);
        }
    }
}

TEST(KnotVectorTest, CustomSpan)
{
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

TEST(KnotVectorTest, CustomMult)
{
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

TEST(BasisEvalTest, Bezier0)
{
    const double tolerance = 1e-15;
    const KnotVector knotvector({0, 1});
    const Basis basis(knotvector);

    EXPECT_NEAR(basis(0.0, 0), 1., tolerance);
    EXPECT_NEAR(basis(0.5, 0), 1., tolerance);
    EXPECT_NEAR(basis(1.0, 0), 1., tolerance);
}

TEST(BasisEvalTest, Custom1)
{
    const double tolerance = 1e-15;
    const KnotVector knotvector({0, 0, 0, 0, 0, 1. / 3, 2. / 3, 1, 1, 1, 1, 1});
    const Basis basis(knotvector);

    EXPECT_EQ(knotvector.degree, 4);
    EXPECT_EQ(knotvector.npts, 7);

    EXPECT_NEAR(basis(0., 0), 1., tolerance);
    EXPECT_NEAR(basis(0., 1), 0., tolerance);
    EXPECT_NEAR(basis(0., 2), 0., tolerance);
    EXPECT_NEAR(basis(0., 3), 0., tolerance);
    EXPECT_NEAR(basis(0., 4), 0., tolerance);
    EXPECT_NEAR(basis(0., 5), 0., tolerance);
    EXPECT_NEAR(basis(0., 6), 0., tolerance);
    EXPECT_NEAR(basis(1. / 8, 0), 625. / 4096, tolerance);
    EXPECT_NEAR(basis(1. / 8, 1), 18561. / 32768, tolerance);
    EXPECT_NEAR(basis(1. / 8, 2), 8253. / 32768, tolerance);
    EXPECT_NEAR(basis(1. / 8, 3), 459. / 16384, tolerance);
    EXPECT_NEAR(basis(1. / 8, 4), 9. / 8192, tolerance);
    EXPECT_NEAR(basis(1. / 8, 5), 0., tolerance);
    EXPECT_NEAR(basis(1. / 8, 6), 0., tolerance);
    EXPECT_NEAR(basis(1. / 4, 0), 1. / 256, tolerance);
    EXPECT_NEAR(basis(1. / 4, 1), 609. / 2048, tolerance);
    EXPECT_NEAR(basis(1. / 4, 2), 1053. / 2048, tolerance);
    EXPECT_NEAR(basis(1. / 4, 3), 171. / 1024, tolerance);
    EXPECT_NEAR(basis(1. / 4, 4), 9. / 512, tolerance);
    EXPECT_NEAR(basis(1. / 4, 5), 0., tolerance);
    EXPECT_NEAR(basis(1. / 4, 6), 0., tolerance);
    EXPECT_NEAR(basis(3. / 8, 0), 0., tolerance);
    EXPECT_NEAR(basis(3. / 8, 1), 2401. / 32768, tolerance);
    EXPECT_NEAR(basis(3. / 8, 2), 15297. / 32768, tolerance);
    EXPECT_NEAR(basis(3. / 8, 3), 3039. / 8192, tolerance);
    EXPECT_NEAR(basis(3. / 8, 4), 2913. / 32768, tolerance);
    EXPECT_NEAR(basis(3. / 8, 5), 1. / 32768, tolerance);
    EXPECT_NEAR(basis(3. / 8, 6), 0., tolerance);
    EXPECT_NEAR(basis(1. / 2, 0), 0., tolerance);
    EXPECT_NEAR(basis(1. / 2, 1), 1. / 128, tolerance);
    EXPECT_NEAR(basis(1. / 2, 2), 33. / 128, tolerance);
    EXPECT_NEAR(basis(1. / 2, 3), 15. / 32, tolerance);
    EXPECT_NEAR(basis(1. / 2, 4), 33. / 128, tolerance);
    EXPECT_NEAR(basis(1. / 2, 5), 1. / 128, tolerance);
    EXPECT_NEAR(basis(1. / 2, 6), 0., tolerance);
    EXPECT_NEAR(basis(5. / 8, 0), 0., tolerance);
    EXPECT_NEAR(basis(5. / 8, 1), 1. / 32768, tolerance);
    EXPECT_NEAR(basis(5. / 8, 2), 2913. / 32768, tolerance);
    EXPECT_NEAR(basis(5. / 8, 3), 3039. / 8192, tolerance);
    EXPECT_NEAR(basis(5. / 8, 4), 15297. / 32768, tolerance);
    EXPECT_NEAR(basis(5. / 8, 5), 2401. / 32768, tolerance);
    EXPECT_NEAR(basis(5. / 8, 6), 0., tolerance);
    EXPECT_NEAR(basis(3. / 4, 0), 0., tolerance);
    EXPECT_NEAR(basis(3. / 4, 1), 0., tolerance);
    EXPECT_NEAR(basis(3. / 4, 2), 9. / 512, tolerance);
    EXPECT_NEAR(basis(3. / 4, 3), 171. / 1024, tolerance);
    EXPECT_NEAR(basis(3. / 4, 4), 1053. / 2048, tolerance);
    EXPECT_NEAR(basis(3. / 4, 5), 609. / 2048, tolerance);
    EXPECT_NEAR(basis(3. / 4, 6), 1. / 256, tolerance);
    EXPECT_NEAR(basis(7. / 8, 0), 0., tolerance);
    EXPECT_NEAR(basis(7. / 8, 1), 0., tolerance);
    EXPECT_NEAR(basis(7. / 8, 2), 9. / 8192, tolerance);
    EXPECT_NEAR(basis(7. / 8, 3), 459. / 16384, tolerance);
    EXPECT_NEAR(basis(7. / 8, 4), 8253. / 32768, tolerance);
    EXPECT_NEAR(basis(7. / 8, 5), 18561. / 32768, tolerance);
    EXPECT_NEAR(basis(7. / 8, 6), 625. / 4096, tolerance);
    EXPECT_NEAR(basis(1., 0), 0., tolerance);
    EXPECT_NEAR(basis(1., 1), 0., tolerance);
    EXPECT_NEAR(basis(1., 2), 0., tolerance);
    EXPECT_NEAR(basis(1., 3), 0., tolerance);
    EXPECT_NEAR(basis(1., 4), 0., tolerance);
    EXPECT_NEAR(basis(1., 5), 0., tolerance);
    EXPECT_NEAR(basis(1., 6), 1., tolerance);
}

void test_eval_vector()
{
    const double tolerance = 1e-15;
    const unsigned short degree = 4;
    const unsigned short npts = 7;

    const KnotVector knotvector = GeneratorKnotVector::uniform(degree, npts);
    const Basis basis(knotvector);

    std::vector<double> output(npts);
    std::vector<double> results = {0., 1. / 32768, 2913. / 32768, 3039. / 8192, 15297. / 32768, 2401. / 32768, 0.};

    basis.evaluate(5. / 8, output);
    for (unsigned short i = 0; i < npts; i++)
        EXPECT_NEAR(output[i], results[i], tolerance);
}
