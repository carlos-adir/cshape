#ifndef NURBS_H
#define NURBS_H

#include <iostream>
#include <vector>

typedef double parameter;
typedef unsigned short ushort;

namespace Math{
    ushort binom(const ushort n, const ushort i);
    parameter bezier(const parameter u, const ushort p, const ushort i);
};


class KnotVector
{
private:
    const std::vector<parameter> internal;
public:
    KnotVector(const std::vector<parameter> &init_vector);
    ~KnotVector() = default;
    const parameter& operator[](const ushort index) const;
    const ushort degree;
    const ushort npts;
    ushort span(const parameter node);
    ushort mult(const parameter node);
};


std::ostream& operator<<(std::ostream &os, const KnotVector & knotvector);


namespace GeneratorKnotVector{
    KnotVector bezier(const ushort degree);
    KnotVector uniform(const ushort degree, const ushort npts);
};

#endif