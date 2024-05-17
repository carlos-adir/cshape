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

TEST(CurveEvalTest, Bezier0)
{
    const double tolerance = 1e-15;
    const KnotVector knotvector({0, 1});
    EXPECT_EQ(knotvector.degree, 0);
    EXPECT_EQ(knotvector.npts, 1);

    const std::vector<double> xcoords = {0};
    const std::vector<double> ycoords = {1};
    const Curve curve(knotvector, xcoords, ycoords);

    EXPECT_NEAR(curve(0.0)[0], 0, tolerance);
    EXPECT_NEAR(curve(0.5)[0], 0, tolerance);
    EXPECT_NEAR(curve(1.0)[0], 0, tolerance);
    EXPECT_NEAR(curve(0.0)[1], 1, tolerance);
    EXPECT_NEAR(curve(0.5)[1], 1, tolerance);
    EXPECT_NEAR(curve(1.0)[1], 1, tolerance);
}

TEST(CurveEvalTest, Bezier1)
{
    const double tolerance = 1e-15;
    const KnotVector knotvector({0, 0, 1, 1});
    EXPECT_EQ(knotvector.degree, 1);
    EXPECT_EQ(knotvector.npts, 2);

    const std::vector<double> xcoords = {0, 7};
    const std::vector<double> ycoords = {1, -6};
    const Curve curve(knotvector, xcoords, ycoords);

    EXPECT_NEAR(curve(0.0)[0], 0, tolerance);
    EXPECT_NEAR(curve(0.5)[0], 3.5, tolerance);
    EXPECT_NEAR(curve(1.0)[0], 7, tolerance);
    EXPECT_NEAR(curve(0.0)[1], 1, tolerance);
    EXPECT_NEAR(curve(0.5)[1], -2.5, tolerance);
    EXPECT_NEAR(curve(1.0)[1], -6, tolerance);
}

TEST(CurveEvalTest, Bezier2_1)
{
    const double tolerance = 1e-15;
    const KnotVector knotvector({0, 0, 0, 1, 1, 1});
    EXPECT_EQ(knotvector.degree, 2);
    EXPECT_EQ(knotvector.npts, 3);
    const std::vector<double> xcoords = {8, 1, 3};
    const std::vector<double> ycoords = {3, 6, 5};
    const Curve curve(knotvector, xcoords, ycoords);

    EXPECT_NEAR(curve(0.000)[0], 8., tolerance);
    EXPECT_NEAR(curve(0.000)[1], 3., tolerance);
    EXPECT_NEAR(curve(0.125)[0], 409. / 64, tolerance);
    EXPECT_NEAR(curve(0.125)[1], 59. / 16, tolerance);
    EXPECT_NEAR(curve(0.250)[0], 81. / 16, tolerance);
    EXPECT_NEAR(curve(0.250)[1], 17. / 4, tolerance);
    EXPECT_NEAR(curve(0.375)[0], 257. / 64, tolerance);
    EXPECT_NEAR(curve(0.375)[1], 75. / 16, tolerance);
    EXPECT_NEAR(curve(0.500)[0], 13. / 4, tolerance);
    EXPECT_NEAR(curve(0.500)[1], 5., tolerance);
    EXPECT_NEAR(curve(0.625)[0], 177. / 64, tolerance);
    EXPECT_NEAR(curve(0.625)[1], 83. / 16, tolerance);
    EXPECT_NEAR(curve(0.750)[0], 41. / 16, tolerance);
    EXPECT_NEAR(curve(0.750)[1], 21. / 4, tolerance);
    EXPECT_NEAR(curve(0.875)[0], 169. / 64, tolerance);
    EXPECT_NEAR(curve(0.875)[1], 83. / 16, tolerance);
    EXPECT_NEAR(curve(1.000)[0], 3., tolerance);
    EXPECT_NEAR(curve(1.000)[1], 5., tolerance);
}

TEST(CurveEvalTest, Bezier2_2)
{
    const double tolerance = 1e-15;
    const KnotVector knotvector({0, 0, 0, 1, 1, 1});
    EXPECT_EQ(knotvector.degree, 2);
    EXPECT_EQ(knotvector.npts, 3);
    const std::vector<double> xcoords = {2, 3, 8};
    const std::vector<double> ycoords = {1, 9, 6};
    const std::vector<double> weights = {1, 1, 1};
    const Curve curve(knotvector, xcoords, ycoords);

    EXPECT_NEAR(curve(0.000)[0], 2., tolerance);
    EXPECT_NEAR(curve(0.000)[1], 1., tolerance);
    EXPECT_NEAR(curve(0.125)[0], 37. / 16, tolerance);
    EXPECT_NEAR(curve(0.125)[1], 181. / 64, tolerance);
    EXPECT_NEAR(curve(0.250)[0], 11. / 4, tolerance);
    EXPECT_NEAR(curve(0.250)[1], 69. / 16, tolerance);
    EXPECT_NEAR(curve(0.375)[0], 53. / 16, tolerance);
    EXPECT_NEAR(curve(0.375)[1], 349. / 64, tolerance);
    EXPECT_NEAR(curve(0.500)[0], 4., tolerance);
    EXPECT_NEAR(curve(0.500)[1], 25. / 4, tolerance);
    EXPECT_NEAR(curve(0.625)[0], 77. / 16, tolerance);
    EXPECT_NEAR(curve(0.625)[1], 429. / 64, tolerance);
    EXPECT_NEAR(curve(0.750)[0], 23. / 4, tolerance);
    EXPECT_NEAR(curve(0.750)[1], 109. / 16, tolerance);
    EXPECT_NEAR(curve(0.875)[0], 109. / 16, tolerance);
    EXPECT_NEAR(curve(0.875)[1], 421. / 64, tolerance);
    EXPECT_NEAR(curve(1.000)[0], 8., tolerance);
    EXPECT_NEAR(curve(1.000)[1], 6., tolerance);
}

TEST(CurveEvalTest, Bezier2_3)
{
    const double tolerance = 1e-15;
    const KnotVector knotvector({0, 0, 0, 1, 1, 1});
    EXPECT_EQ(knotvector.degree, 2);
    EXPECT_EQ(knotvector.npts, 3);
    const std::vector<double> xcoords = {9, 4, 7};
    const std::vector<double> ycoords = {7, 5, 7};
    const std::vector<double> weights = {5, 5, 6};
    const Curve curve(knotvector, xcoords, ycoords, weights);

    EXPECT_NEAR(curve(0.000)[0], 9., tolerance);
    EXPECT_NEAR(curve(0.000)[1], 7., tolerance);
    EXPECT_NEAR(curve(0.125)[0], 2527. / 321, tolerance);
    EXPECT_NEAR(curve(0.125)[1], 2107. / 321, tolerance);
    EXPECT_NEAR(curve(0.250)[0], 7., tolerance);
    EXPECT_NEAR(curve(0.250)[1], 169. / 27, tolerance);
    EXPECT_NEAR(curve(0.375)[0], 2103. / 329, tolerance);
    EXPECT_NEAR(curve(0.375)[1], 2003. / 329, tolerance);
    EXPECT_NEAR(curve(0.500)[0], 127. / 21, tolerance);
    EXPECT_NEAR(curve(0.500)[1], 127. / 21, tolerance);
    EXPECT_NEAR(curve(0.625)[0], 137. / 23, tolerance);
    EXPECT_NEAR(curve(0.625)[1], 141. / 23, tolerance);
    EXPECT_NEAR(curve(0.750)[0], 543. / 89, tolerance);
    EXPECT_NEAR(curve(0.750)[1], 563. / 89, tolerance);
    EXPECT_NEAR(curve(0.875)[0], 2383. / 369, tolerance);
    EXPECT_NEAR(curve(0.875)[1], 2443. / 369, tolerance);
    EXPECT_NEAR(curve(1.000)[0], 7., tolerance);
    EXPECT_NEAR(curve(1.000)[1], 7., tolerance);
}

TEST(CurveEvalTest, Bezier2_4)
{
    const double tolerance = 1e-15;
    const KnotVector knotvector({0, 0, 0, 1, 1, 1});
    EXPECT_EQ(knotvector.degree, 2);
    EXPECT_EQ(knotvector.npts, 3);
    const std::vector<double> xcoords = {0, 7, 4};
    const std::vector<double> ycoords = {9, 6, 7};
    const std::vector<double> weights = {5, 4, 7};
    const Curve curve(knotvector, xcoords, ycoords, weights);

    EXPECT_NEAR(curve(0.000)[0], 0., tolerance);
    EXPECT_NEAR(curve(0.000)[1], 9., tolerance);
    EXPECT_NEAR(curve(0.125)[0], 15. / 11, tolerance);
    EXPECT_NEAR(curve(0.125)[1], 185. / 22, tolerance);
    EXPECT_NEAR(curve(0.250)[0], 49. / 19, tolerance);
    EXPECT_NEAR(curve(0.250)[1], 299. / 38, tolerance);
    EXPECT_NEAR(curve(0.375)[0], 39. / 11, tolerance);
    EXPECT_NEAR(curve(0.375)[1], 1143. / 154, tolerance);
    EXPECT_NEAR(curve(0.500)[0], 21. / 5, tolerance);
    EXPECT_NEAR(curve(0.500)[1], 71. / 10, tolerance);
    EXPECT_NEAR(curve(0.625)[0], 77. / 17, tolerance);
    EXPECT_NEAR(curve(0.625)[1], 235. / 34, tolerance);
    EXPECT_NEAR(curve(0.750)[0], 105. / 23, tolerance);
    EXPECT_NEAR(curve(0.750)[1], 315. / 46, tolerance);
    EXPECT_NEAR(curve(0.875)[0], 441. / 101, tolerance);
    EXPECT_NEAR(curve(0.875)[1], 1391. / 202, tolerance);
    EXPECT_NEAR(curve(1.000)[0], 4., tolerance);
    EXPECT_NEAR(curve(1.000)[1], 7., tolerance);
}

TEST(CurveEvalTest, Uniform48_1)
{
    const double tolerance = 1e-15;
    const KnotVector knotvector({0., 0., 0., 0., 0., 1. / 4, 1. / 2, 3. / 4, 1., 1., 1., 1., 1.});
    EXPECT_EQ(knotvector.degree, 4);
    EXPECT_EQ(knotvector.npts, 8);
    const std::vector<double> xcoords = {5, 8, 5, 4, 1, 6, 4, 9};
    const std::vector<double> ycoords = {1, 3, 2, 0, 9, 4, 7, 8};
    const std::vector<double> weights = {5, 4, 6, 5, 5, 5, 4, 6};
    const Curve curve(knotvector, xcoords, ycoords, weights);

    EXPECT_NEAR(curve(0.000)[0], 5., tolerance);
    EXPECT_NEAR(curve(0.000)[1], 1., tolerance);
    EXPECT_NEAR(curve(0.125)[0], 34585. / 5596, tolerance);
    EXPECT_NEAR(curve(0.125)[1], 12567. / 5596, tolerance);
    EXPECT_NEAR(curve(0.250)[0], 1873. / 388, tolerance);
    EXPECT_NEAR(curve(0.250)[1], 687. / 388, tolerance);
    EXPECT_NEAR(curve(0.375)[0], 22753. / 6048, tolerance);
    EXPECT_NEAR(curve(0.375)[1], 13967. / 6048, tolerance);
    EXPECT_NEAR(curve(0.500)[0], 20. / 7, tolerance);
    EXPECT_NEAR(curve(0.500)[1], 56. / 13, tolerance);
    EXPECT_NEAR(curve(0.625)[0], 16789. / 5755, tolerance);
    EXPECT_NEAR(curve(0.625)[1], 6783. / 1151, tolerance);
    EXPECT_NEAR(curve(0.750)[0], 1429. / 351, tolerance);
    EXPECT_NEAR(curve(0.750)[1], 2027. / 351, tolerance);
    EXPECT_NEAR(curve(0.875)[0], 26293. / 5247, tolerance);
    EXPECT_NEAR(curve(0.875)[1], 31451. / 5247, tolerance);
    EXPECT_NEAR(curve(1.000)[0], 9., tolerance);
    EXPECT_NEAR(curve(1.000)[1], 8., tolerance);
}

TEST(CurveEvalTest, Uniform48_2)
{
    const double tolerance = 1e-15;
    const KnotVector knotvector({0., 0., 0., 0., 0., 1. / 4, 1. / 2, 3. / 4, 1., 1., 1., 1., 1.});
    EXPECT_EQ(knotvector.degree, 4);
    EXPECT_EQ(knotvector.npts, 8);
    const std::vector<double> xcoords = {8, 7, 7, 8, 0, 5, 4, 2};
    const std::vector<double> ycoords = {8, 1, 2, 1, 9, 8, 7, 7};
    const std::vector<double> weights = {6, 7, 4, 6, 5, 6, 5, 6};
    const Curve curve(knotvector, xcoords, ycoords, weights);

    EXPECT_NEAR(curve(0.000)[0], 8., tolerance);
    EXPECT_NEAR(curve(0.000)[1], 8., tolerance);
    EXPECT_NEAR(curve(0.125)[0], 47317. / 6652, tolerance);
    EXPECT_NEAR(curve(0.125)[1], 2870. / 1663, tolerance);
    EXPECT_NEAR(curve(0.250)[0], 2581. / 364, tolerance);
    EXPECT_NEAR(curve(0.250)[1], 158. / 91, tolerance);
    EXPECT_NEAR(curve(0.375)[0], 38397. / 6100, tolerance);
    EXPECT_NEAR(curve(0.375)[1], 4134. / 1525, tolerance);
    EXPECT_NEAR(curve(0.500)[0], 221. / 49, tolerance);
    EXPECT_NEAR(curve(0.500)[1], 232. / 49, tolerance);
    EXPECT_NEAR(curve(0.625)[0], 10049. / 3140, tolerance);
    EXPECT_NEAR(curve(0.625)[1], 1091. / 157, tolerance);
    EXPECT_NEAR(curve(0.750)[0], 717. / 200, tolerance);
    EXPECT_NEAR(curve(0.750)[1], 393. / 50, tolerance);
    EXPECT_NEAR(curve(0.875)[0], 12669. / 3128, tolerance);
    EXPECT_NEAR(curve(0.875)[1], 15. / 2, tolerance);
    EXPECT_NEAR(curve(1.000)[0], 2., tolerance);
    EXPECT_NEAR(curve(1.000)[1], 7., tolerance);
}

TEST(CurveEvalTest, Uniform48_3)
{
    const double tolerance = 1e-14;
    const KnotVector knotvector({0., 0., 0., 0., 0., 1. / 4, 1. / 2, 3. / 4, 1., 1., 1., 1., 1.});
    EXPECT_EQ(knotvector.degree, 4);
    EXPECT_EQ(knotvector.npts, 8);
    const std::vector<double> xcoords = {8, 5, 3, 6, 5, 5, 1, 0};
    const std::vector<double> ycoords = {0, 0, 1, 9, 2, 8, 6, 1};
    const std::vector<double> weights = {6, 5, 4, 7, 5, 4, 7, 4};
    const Curve curve(knotvector, xcoords, ycoords, weights);

    EXPECT_NEAR(curve(0.000)[0], 8., tolerance);
    EXPECT_NEAR(curve(0.000)[1], 0., tolerance);
    EXPECT_NEAR(curve(0.125)[0], 2910. / 617, tolerance);
    EXPECT_NEAR(curve(0.125)[1], 6187. / 5553, tolerance);
    EXPECT_NEAR(curve(0.250)[0], 190. / 41, tolerance);
    EXPECT_NEAR(curve(0.250)[1], 1627. / 369, tolerance);
    EXPECT_NEAR(curve(0.375)[0], 35374. / 6689, tolerance);
    EXPECT_NEAR(curve(0.375)[1], 42331. / 6689, tolerance);
    EXPECT_NEAR(curve(0.500)[0], 71. / 13, tolerance);
    EXPECT_NEAR(curve(0.500)[1], 155. / 26, tolerance);
    EXPECT_NEAR(curve(0.625)[0], 3440. / 659, tolerance);
    EXPECT_NEAR(curve(0.625)[1], 30349. / 5931, tolerance);
    EXPECT_NEAR(curve(0.750)[0], 1504. / 347, tolerance);
    EXPECT_NEAR(curve(0.750)[1], 1981. / 347, tolerance);
    EXPECT_NEAR(curve(0.875)[0], 848. / 379, tolerance);
    EXPECT_NEAR(curve(0.875)[1], 39229. / 6443, tolerance);
    EXPECT_NEAR(curve(1.000)[0], 0., tolerance);
    EXPECT_NEAR(curve(1.000)[1], 1., tolerance);
}

TEST(CurveEvalTest, Weighted_1)
{
    const double tolerance = 1e-15;
    const KnotVector knotvector({0., 0., 0., 2. / 7, 5. / 7, 1., 1., 1.});
    EXPECT_EQ(knotvector.degree, 2);
    EXPECT_EQ(knotvector.npts, 5);
    const std::vector<double> xcoords = {4, 1, 6, 1, 5};
    const std::vector<double> ycoords = {7, 1, 9, 7, 1};
    const std::vector<double> weights = {4, 5, 5, 6, 5};
    const Curve curve(knotvector, xcoords, ycoords, weights);

    EXPECT_NEAR(curve(0.000)[0], 4., tolerance);
    EXPECT_NEAR(curve(0.000)[1], 7., tolerance);
    EXPECT_NEAR(curve(0.125)[0], 2661. / 1199, tolerance);
    EXPECT_NEAR(curve(0.125)[1], 357. / 109, tolerance);
    EXPECT_NEAR(curve(0.250)[0], 821. / 319, tolerance);
    EXPECT_NEAR(curve(0.250)[1], 1127. / 319, tolerance);
    EXPECT_NEAR(curve(0.375)[0], 767. / 193, tolerance);
    EXPECT_NEAR(curve(0.375)[1], 5737. / 965, tolerance);
    EXPECT_NEAR(curve(0.500)[0], 453. / 103, tolerance);
    EXPECT_NEAR(curve(0.500)[1], 771. / 103, tolerance);
    EXPECT_NEAR(curve(0.625)[0], 19511. / 5161, tolerance);
    EXPECT_NEAR(curve(0.625)[1], 41117. / 5161, tolerance);
    EXPECT_NEAR(curve(0.750)[0], 4367. / 1817, tolerance);
    EXPECT_NEAR(curve(0.750)[1], 13549. / 1817, tolerance);
    EXPECT_NEAR(curve(0.875)[0], 17727. / 7177, tolerance);
    EXPECT_NEAR(curve(0.875)[1], 39069. / 7177, tolerance);
    EXPECT_NEAR(curve(1.000)[0], 5., tolerance);
    EXPECT_NEAR(curve(1.000)[1], 1., tolerance);
}
