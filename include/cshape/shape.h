#ifndef BIDIMBOOL_H
#define BIDIMBOOL_H

#include <vector>
#include <iostream>
#include <unistd.h>


typedef unsigned long uint8;
typedef unsigned int uint4;
typedef unsigned short uint2;
typedef unsigned short uint1;

typedef double basetype;

class SubSetR2;
class EmptyR2;
class WholeR2;

class IPoint;
class ICurve;
class IShape;
class BoolNot;
class BoolAnd;
class BoolOr;


enum SubSetR2Typo {
    Empty,
    Whole,
    Point,
    Curve,
    Simple,
    Nand,
};


class SubSetR2{
public:
    virtual bool operator==(const SubSetR2 &other) const = 0;
    virtual bool operator!=(const SubSetR2 &other) const = 0;
    virtual bool contains(const SubSetR2 &other) const = 0;

    const SubSetR2 &operator~() const; // Inversion
    virtual const SubSetR2 &operator|(const SubSetR2 &other) const; // Union
    virtual const SubSetR2 &operator&(const SubSetR2 &other) const; // Intersect

    virtual SubSetR2Typo tipo() const = 0; 
};







#endif
