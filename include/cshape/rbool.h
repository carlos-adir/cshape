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

enum class SubSetR1Typo
{
    Empty = 0,
    Whole,
    Point,
    Interval,
    Disjoint
};

template<typename T>
struct IntervalR1
{
    const T start;
    const T end;
    const bool closed_left;
    const bool closed_right;
    bool operator==(const IntervalR1<T> &other) const;
    bool operator!=(const IntervalR1<T> &other) const {return !this->operator==(other);};
    bool contains(const T &other) const;
    bool contains(const IntervalR1<T> &other) const;
};

template<typename T>
class SubSetR1{
private:
    const std::vector<T> finites;
    const std::vector<IntervalR1<T>> intervals;
    
    SubSetR1(const std::vector<T> &finites,
             const std::vector<IntervalR1<T>> &intervals,
             const SubSetR1Typo typo);

public:
    static constexpr T NEGINF = -std::numeric_limits<T>::infinity();
    static constexpr T POSINF = std::numeric_limits<T>::infinity();

    SubSetR1(const SubSetR1 &other); // Copy constructor
    SubSetR1(const std::string &str);
    SubSetR1(const std::vector<T> &finites,
             const std::vector<IntervalR1<T>> &intervals);

    bool contains(const T &other) const;
    bool contains(const IntervalR1<T> &other) const;
    bool contains(const SubSetR1<T> &other) const;

    static const SubSetR1<T> Empty();
    static const SubSetR1<T> Whole();
    static const SubSetR1<T> Point(const T &value);
    static const SubSetR1<T> Lower(const T &value, const bool closed = true);
    static const SubSetR1<T> Bigger(const T &value, const bool closed = true);
    static const SubSetR1<T> Between(const T &sta,
                                     const T &end,
                                     const bool closed_left = true,
                                     const bool closed_right = true);

    SubSetR1<T> operator~() const;
    SubSetR1<T> operator|(const SubSetR1<T> &other) const;
    SubSetR1<T> operator&(const SubSetR1<T> &other) const;

    bool operator==(const SubSetR1<T> &other) const;
    bool operator!=(const SubSetR1<T> &other) const {return !this->operator==(other);};

    const SubSetR1Typo typo;

    operator std::string() const;
    template<typename U>
    friend std::ostream &operator<<(std::ostream &os, const SubSetR1<U> &obj);
};


template class SubSetR1<int>;
template class SubSetR1<Scalar>;

#endif
