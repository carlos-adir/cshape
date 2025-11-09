#ifndef UNIDIMBOOL_H
#define UNIDIMBOOL_H

#include <vector>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string>
#include <memory>
#include <set>

#include "scalar.h"

typedef unsigned long uint8;
typedef unsigned int uint4;
typedef unsigned short uint2;
typedef unsigned short uint1;

class SubSetR1;

enum class SubSetR1Typo
{
    Empty = 0,
    Whole,
    Point,
    Interval,
    Disjoint
};

typedef struct IntervalR1
{
    const scalar start;
    const scalar end;
    const bool closed_left;
    const bool closed_right;
    bool operator==(const IntervalR1 &other) const;
    bool operator!=(const IntervalR1 &other) const {return !this->operator==(other);};
    bool contains(const scalar &other) const;
    bool contains(const IntervalR1 &other) const;
} IntervalR1;

class SubSetR1{
private:
    const std::vector<scalar> finites;
    const std::vector<IntervalR1> intervals;
    
    SubSetR1(const std::vector<scalar> &finites,
             const std::vector<IntervalR1> &intervals,
             const SubSetR1Typo typo);

public:
    SubSetR1(const SubSetR1 &other); // Copy constructor
    SubSetR1(const std::string &str);
    SubSetR1(const std::vector<scalar> &finites,
             const std::vector<IntervalR1> &intervals);

    bool contains(const scalar &other) const;
    bool contains(const IntervalR1 &other) const;
    bool contains(const SubSetR1 &other) const;

    static const SubSetR1 Empty();
    static const SubSetR1 Whole();
    static const SubSetR1 Point(const scalar &value);
    static const SubSetR1 Lower(const scalar &value, const bool closed = true);
    static const SubSetR1 Bigger(const scalar &value, const bool closed = true);
    static const SubSetR1 Between(const scalar &sta,
                                  const scalar &end,
                                  const bool closed_left = true,
                                  const bool closed_right = true);

    SubSetR1 operator~() const;
    SubSetR1 operator|(const SubSetR1 &other) const;
    SubSetR1 operator&(const SubSetR1 &other) const;

    bool operator==(const SubSetR1 &other) const;
    bool operator!=(const SubSetR1 &other) const {return !this->operator==(other);};

    const SubSetR1Typo typo;

    operator std::string() const;
    friend std::ostream &operator<<(std::ostream &os, const SubSetR1 &obj);
};

#endif
