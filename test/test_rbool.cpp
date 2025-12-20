#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "cshape/logging.h"
#include "cshape/rbool.h"

static Logger& logger = Logger::getInstance("test.rbool");

TEST(Bool1DTest, BuildsSpecial)
{
    SubSetR1<Scalar> empty = SubSetR1<Scalar>::Empty();
    SubSetR1<Scalar> whole = SubSetR1<Scalar>::Whole();
}

TEST(Bool1DTest, BuildsSingleValue)
{
    SubSetR1<Scalar> point = SubSetR1<Scalar>::Point(10);
}

TEST(Bool1DTest, BuildsInterval)
{
    double fa(-10), fb(10);
    
    logger << "Initialize BuildsInterval";
    logger << SubSetR1<Scalar>::Between(SubSetR1<Scalar>::NEGINF, fa);
    logger << SubSetR1<Scalar>::Between(SubSetR1<Scalar>::NEGINF, fb);
    logger << SubSetR1<Scalar>::Between(fa, fb);
    logger << SubSetR1<Scalar>::Between(fa, SubSetR1<Scalar>::POSINF);
    logger << SubSetR1<Scalar>::Between(fb, SubSetR1<Scalar>::POSINF);
    logger << SubSetR1<Scalar>::Lower(fa);
    logger << SubSetR1<Scalar>::Lower(fb);
    logger << SubSetR1<Scalar>::Bigger(fa);
    logger << SubSetR1<Scalar>::Bigger(fb);
    logger << "Finish Builds Interval";
}


TEST(Bool1DTest, Printing)
{
    EXPECT_EQ(std::string(SubSetR1<Scalar>::Empty()), "{}");
    EXPECT_EQ(std::string(SubSetR1<Scalar>::Whole()), "(-inf, inf)");
    EXPECT_EQ(std::string(SubSetR1<Scalar>::Point(-10)), "{-10}");
    EXPECT_EQ(std::string(SubSetR1<Scalar>::Point(10)), "{10}");
    EXPECT_EQ(std::string(SubSetR1<Scalar>::Between(-10, 10)), "[-10, 10]");
    EXPECT_EQ(std::string(SubSetR1<Scalar>::Between(SubSetR1<Scalar>::NEGINF, 10)), "(-inf, 10]");
    EXPECT_EQ(std::string(SubSetR1<Scalar>::Lower(10)), "(-inf, 10]");
    EXPECT_EQ(std::string(SubSetR1<Scalar>::Between(-10, SubSetR1<Scalar>::POSINF)), "[-10, inf)");
    EXPECT_EQ(std::string(SubSetR1<Scalar>::Bigger(10)), "[10, inf)");
}


TEST(Bool1DTest, BuildsFromString)
{
    SubSetR1<Scalar> obj1("{}");
    SubSetR1<Scalar> obj2("(-inf, inf)");
    SubSetR1<Scalar> obj3("{10}");
    SubSetR1<Scalar> obj4("{-10}");
    SubSetR1<Scalar> obj5("[-10, 10]");
}


TEST(Bool1DTest, CompareSingleton)
{
    SubSetR1<Scalar> empty = SubSetR1<Scalar>::Empty();
    SubSetR1<Scalar> whole = SubSetR1<Scalar>::Whole();
    // empty and whole
    EXPECT_TRUE(empty == empty);
    EXPECT_FALSE(empty == whole);
    EXPECT_FALSE(whole == empty);
    EXPECT_TRUE(whole == whole);

    EXPECT_FALSE(empty != empty);
    EXPECT_TRUE(empty != whole);
    EXPECT_TRUE(whole != empty);
    EXPECT_FALSE(whole != whole);
}




TEST(Bool1DTest, CompareSingleEmptyWhole)
{
    SubSetR1<Scalar> empty = SubSetR1<Scalar>::Empty();
    SubSetR1<Scalar> whole = SubSetR1<Scalar>::Whole();
    SubSetR1<Scalar> finite = SubSetR1<Scalar>::Point(0);

    EXPECT_FALSE(empty == finite);
    EXPECT_TRUE(empty != finite);
    EXPECT_FALSE(finite == empty);
    EXPECT_TRUE(finite != empty);

    EXPECT_FALSE(whole == finite);
    EXPECT_TRUE(whole != finite);
    EXPECT_FALSE(finite == whole);
    EXPECT_TRUE(finite != whole);
};



TEST(Bool1DTest, ContainsSingleton)
{
    SubSetR1<Scalar> empty = SubSetR1<Scalar>::Empty();
    SubSetR1<Scalar> whole = SubSetR1<Scalar>::Whole();
    EXPECT_FALSE(empty.contains(empty));
    EXPECT_FALSE(empty.contains(whole));
    EXPECT_TRUE(whole.contains(empty));
    EXPECT_TRUE(whole.contains(whole));
};


TEST(Bool1DTest, ContainsFinite)
{
    SubSetR1<Scalar> empty = SubSetR1<Scalar>::Empty();
    SubSetR1<Scalar> whole = SubSetR1<Scalar>::Whole();
    SubSetR1<Scalar> finite = SubSetR1<Scalar>::Point(10);

    EXPECT_TRUE(finite.contains(finite));

    EXPECT_TRUE(finite.contains(empty));
    EXPECT_FALSE(finite.contains(whole));

    EXPECT_FALSE(empty.contains(finite));
    EXPECT_TRUE(whole.contains(finite));
};




TEST(Bool1DTest, ContainsInterval)
{
    double fa(-10), fb(10);
    SubSetR1<Scalar> empty = SubSetR1<Scalar>::Empty();
    SubSetR1<Scalar> whole = SubSetR1<Scalar>::Whole();
    SubSetR1<Scalar> n2a = SubSetR1<Scalar>::Between(SubSetR1<Scalar>::NEGINF, fa);
    SubSetR1<Scalar> n2b = SubSetR1<Scalar>::Between(SubSetR1<Scalar>::NEGINF, fb);
    SubSetR1<Scalar> a2b = SubSetR1<Scalar>::Between(fa, fb);
    SubSetR1<Scalar> a2p = SubSetR1<Scalar>::Between(fa, SubSetR1<Scalar>::POSINF);
    SubSetR1<Scalar> b2p = SubSetR1<Scalar>::Between(fb, SubSetR1<Scalar>::POSINF);

    // Contains empty
    EXPECT_TRUE(n2a.contains(empty));
    EXPECT_TRUE(n2b.contains(empty));
    EXPECT_TRUE(a2b.contains(empty));
    EXPECT_TRUE(a2p.contains(empty));
    EXPECT_TRUE(b2p.contains(empty));

    // Contains whole
    EXPECT_FALSE(n2a.contains(whole));
    EXPECT_FALSE(n2b.contains(whole));
    EXPECT_FALSE(a2b.contains(whole));
    EXPECT_FALSE(a2p.contains(whole));
    EXPECT_FALSE(b2p.contains(whole));

    // Contains A value
    EXPECT_TRUE(n2a.contains(fa));
    EXPECT_TRUE(n2b.contains(fa));
    EXPECT_TRUE(a2b.contains(fa));
    EXPECT_TRUE(a2p.contains(fa));
    EXPECT_FALSE(b2p.contains(fa));

    // Contains B value
    EXPECT_FALSE(n2a.contains(fb));
    EXPECT_TRUE(n2b.contains(fb));
    EXPECT_TRUE(a2b.contains(fb));
    EXPECT_TRUE(a2p.contains(fb));
    EXPECT_TRUE(b2p.contains(fb));

    // Contains (-inf, A)
    EXPECT_TRUE(n2a.contains(n2a));
    EXPECT_TRUE(n2b.contains(n2a));
    EXPECT_FALSE(a2b.contains(n2a));
    EXPECT_FALSE(a2p.contains(n2a));
    EXPECT_FALSE(b2p.contains(n2a));

    // Contains (-inf, B)
    EXPECT_FALSE(n2a.contains(n2b));
    EXPECT_TRUE(n2b.contains(n2b));
    EXPECT_FALSE(a2b.contains(n2b));
    EXPECT_FALSE(a2p.contains(n2b));
    EXPECT_FALSE(b2p.contains(n2b));

    // Contains (A, B)
    EXPECT_FALSE(n2a.contains(a2b));
    EXPECT_TRUE(n2b.contains(a2b));
    EXPECT_TRUE(a2b.contains(a2b));
    EXPECT_TRUE(a2p.contains(a2b));
    EXPECT_FALSE(b2p.contains(a2b));

    // Contains (A, inf)
    EXPECT_FALSE(n2a.contains(a2p));
    EXPECT_FALSE(n2b.contains(a2p));
    EXPECT_FALSE(a2b.contains(a2p));
    EXPECT_TRUE(a2p.contains(a2p));
    EXPECT_FALSE(b2p.contains(a2p));

    // Contains (B, inf)
    EXPECT_FALSE(n2a.contains(b2p));
    EXPECT_FALSE(n2b.contains(b2p));
    EXPECT_FALSE(a2b.contains(b2p));
    EXPECT_TRUE(a2p.contains(b2p));
    EXPECT_TRUE(b2p.contains(b2p));
};





TEST(Bool1DTest, InvertInterval)
{
    double fa(-10), fb(10);
    SubSetR1<Scalar> empty = SubSetR1<Scalar>::Empty();
    SubSetR1<Scalar> whole = SubSetR1<Scalar>::Whole();
    EXPECT_TRUE(empty == empty);
    EXPECT_TRUE(whole == whole);
    EXPECT_TRUE(~empty == whole);
    EXPECT_TRUE(~whole == empty);


    SubSetR1<Scalar> n2a = SubSetR1<Scalar>::Between(SubSetR1<Scalar>::NEGINF, fa);
    SubSetR1<Scalar> n2b = SubSetR1<Scalar>::Between(SubSetR1<Scalar>::NEGINF, fb);
    SubSetR1<Scalar> a2b = SubSetR1<Scalar>::Between(fa, fb);
    SubSetR1<Scalar> a2p = SubSetR1<Scalar>::Between(fa, SubSetR1<Scalar>::POSINF);
    SubSetR1<Scalar> b2p = SubSetR1<Scalar>::Between(fb, SubSetR1<Scalar>::POSINF);

    EXPECT_TRUE(empty == empty);
    EXPECT_TRUE(whole == whole);
    EXPECT_TRUE(~empty == whole);
    EXPECT_TRUE(~whole == empty);

    /*
    EXPECT_EQ(~n2a, "(-10, inf)");
    EXPECT_EQ(~n2b, "(10, inf)");
    EXPECT_EQ(~a2b, "(-inf, -10) U (10, inf)");
    EXPECT_EQ(~a2p, "(-inf, -10)");
    EXPECT_EQ(~b2p, "(-inf, 10)");
    */

    EXPECT_EQ(~(~n2a), n2a);
    EXPECT_EQ(~(~n2b), n2b);
    EXPECT_EQ(~(~a2b), a2b);
    EXPECT_EQ(~(~a2p), a2p);
    EXPECT_EQ(~(~b2p), b2p);

}