#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include "cshape/bool1d.h"


TEST(Bool1DTest, BuildsSpecial)
{
    SubSetR1 obj;
    obj = SubSetR1::empty();
    obj = SubSetR1::whole();
}

TEST(Bool1DTest, BuildsSingleValue)
{
    SubSetR1 sing;
    sing = SubSetR1::single(10);
}

TEST(Bool1DTest, BuildsInterval)
{
    double fa(-10), fb(10);

    SubSetR1 interval;
    interval = SubSetR1::interval(NEGINF, fa);
    interval = SubSetR1::interval(NEGINF, fb);
    interval = SubSetR1::interval(fa, fb);
    interval = SubSetR1::interval(fa, POSINF);
    interval = SubSetR1::interval(fb, POSINF);
    interval = SubSetR1::lower(fa);
    interval = SubSetR1::lower(fb);
    interval = SubSetR1::bigger(fa);
    interval = SubSetR1::bigger(fb);
}


TEST(Bool1DTest, Printing)
{
    EXPECT_EQ(std::string(SubSetR1::empty()), "{}");
    EXPECT_EQ(std::string(SubSetR1::whole()), "(-inf, +inf)");
    EXPECT_EQ(std::string(SubSetR1::single(-10)), "{-10}");
    EXPECT_EQ(std::string(SubSetR1::single(10)), "{10}");
    EXPECT_EQ(std::string(SubSetR1::interval(-10, 10)), "[-10, 10]");
    EXPECT_EQ(std::string(SubSetR1::interval(NEGINF, 10)), "(-inf, 10]");
    EXPECT_EQ(std::string(SubSetR1::lower(10)), "(-inf, 10]");
    EXPECT_EQ(std::string(SubSetR1::interval(-10, POSINF)), "[-10, +inf)");
    EXPECT_EQ(std::string(SubSetR1::bigger(10)), "[10, +inf)");
}


TEST(Bool1DTest, BuildsFromString)
{
    SubSetR1 obj1("{}");
    SubSetR1 obj2("(-inf, +inf)");
    SubSetR1 obj3("{10}");
    SubSetR1 obj4("{-10}");
    SubSetR1 obj5("[-10, 10]");
    


}


// TEST(Bool1DTest, CompareSingleton)
// {
//     // EMPTYR1 and WHOLER1
//     EXPECT_TRUE(EMPTYR1 == EMPTYR1);
//     EXPECT_FALSE(EMPTYR1 == WHOLER1);
//     EXPECT_FALSE(WHOLER1 == EMPTYR1);
//     EXPECT_TRUE(WHOLER1 == WHOLER1);

//     EXPECT_FALSE(EMPTYR1 != EMPTYR1);
//     EXPECT_TRUE(EMPTYR1 != WHOLER1);
//     EXPECT_TRUE(WHOLER1 != EMPTYR1);
//     EXPECT_FALSE(WHOLER1 != WHOLER1);
// }




// TEST(Bool1DTest, CompareSingleEmptyWhole)
// {
//     SingleValue finite(10);

//     EXPECT_FALSE(EMPTYR1 == finite);
//     EXPECT_TRUE(EMPTYR1 != finite);
//     EXPECT_FALSE(finite == EMPTYR1);
//     EXPECT_TRUE(finite != EMPTYR1);

//     EXPECT_FALSE(WHOLER1 == finite);
//     EXPECT_TRUE(WHOLER1 != finite);
//     EXPECT_FALSE(finite == WHOLER1);
//     EXPECT_TRUE(finite != WHOLER1);
// };



// TEST(Bool1DTest, ContainsSingleton)
// {
//     EXPECT_TRUE(EMPTYR1.contains(EMPTYR1));
//     EXPECT_FALSE(EMPTYR1.contains(WHOLER1));
//     EXPECT_TRUE(WHOLER1.contains(EMPTYR1));
//     EXPECT_TRUE(WHOLER1.contains(WHOLER1));
// };


// TEST(Bool1DTest, ContainsFinite)
// {
//     SingleValue finite(10);

//     EXPECT_TRUE(finite.contains(finite));

//     EXPECT_TRUE(finite.contains(EMPTYR1));
//     EXPECT_FALSE(finite.contains(WHOLER1));

//     EXPECT_FALSE(EMPTYR1.contains(finite));
//     EXPECT_TRUE(WHOLER1.contains(finite));
// };




// TEST(Bool1DTest, ContainsInterval)
// {
//     double fa(-10), fb(10);
//     SubSetR1 n2a(NEGINF, fa);
//     SubSetR1 n2b(NEGINF, fb);
//     SubSetR1 a2b(fa, fb);
//     SubSetR1 a2p(fa, POSINF);
//     SubSetR1 b2p(fb, POSINF);

//     // Contains EMPTYR1
//     EXPECT_TRUE(n2a.contains(EMPTYR1));
//     EXPECT_TRUE(n2b.contains(EMPTYR1));
//     EXPECT_TRUE(a2b.contains(EMPTYR1));
//     EXPECT_TRUE(a2p.contains(EMPTYR1));
//     EXPECT_TRUE(b2p.contains(EMPTYR1));

//     // Contains WHOLER1
//     EXPECT_FALSE(n2a.contains(WHOLER1));
//     EXPECT_FALSE(n2b.contains(WHOLER1));
//     EXPECT_FALSE(a2b.contains(WHOLER1));
//     EXPECT_FALSE(a2p.contains(WHOLER1));
//     EXPECT_FALSE(b2p.contains(WHOLER1));

//     // Contains A value
//     EXPECT_TRUE(n2a.contains(fa));
//     EXPECT_TRUE(n2b.contains(fa));
//     EXPECT_TRUE(a2b.contains(fa));
//     EXPECT_TRUE(a2p.contains(fa));
//     EXPECT_FALSE(b2p.contains(fa));

//     // Contains B value
//     EXPECT_FALSE(n2a.contains(fb));
//     EXPECT_TRUE(n2b.contains(fb));
//     EXPECT_TRUE(a2b.contains(fb));
//     EXPECT_TRUE(a2p.contains(fb));
//     EXPECT_TRUE(b2p.contains(fb));

//     // Contains (-inf, A)
//     EXPECT_TRUE(n2a.contains(n2a));
//     EXPECT_TRUE(n2b.contains(n2a));
//     EXPECT_FALSE(a2b.contains(n2a));
//     EXPECT_FALSE(a2p.contains(n2a));
//     EXPECT_FALSE(b2p.contains(n2a));

//     // Contains (-inf, B)
//     EXPECT_FALSE(n2a.contains(n2b));
//     EXPECT_TRUE(n2b.contains(n2b));
//     EXPECT_FALSE(a2b.contains(n2b));
//     EXPECT_FALSE(a2p.contains(n2b));
//     EXPECT_FALSE(b2p.contains(n2b));

//     // Contains (A, B)
//     EXPECT_FALSE(n2a.contains(a2b));
//     EXPECT_TRUE(n2b.contains(a2b));
//     EXPECT_TRUE(a2b.contains(a2b));
//     EXPECT_TRUE(a2p.contains(a2b));
//     EXPECT_FALSE(b2p.contains(a2b));

//     // Contains (A, +inf)
//     EXPECT_FALSE(n2a.contains(a2p));
//     EXPECT_FALSE(n2b.contains(a2p));
//     EXPECT_FALSE(a2b.contains(a2p));
//     EXPECT_TRUE(a2p.contains(a2p));
//     EXPECT_FALSE(b2p.contains(a2p));

//     // Contains (B, +inf)
//     EXPECT_FALSE(n2a.contains(b2p));
//     EXPECT_FALSE(n2b.contains(b2p));
//     EXPECT_FALSE(a2b.contains(b2p));
//     EXPECT_TRUE(a2p.contains(b2p));
//     EXPECT_TRUE(b2p.contains(b2p));
// };



