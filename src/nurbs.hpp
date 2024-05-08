#ifndef NURBS_H
#define NURBS_H

#include <iostream>
#include <vector>

typedef unsigned short ushort;

namespace Math{
    ushort binom(const ushort n, const ushort i);
    template<typename parameter>
    parameter bezier(const parameter u, const ushort p, const ushort i);
};


template<typename parameter>
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

std::ostream& operator<<(std::ostream &os, const KnotVector<double>& knotvector);

namespace GeneratorKnotVector{
    template<typename parameter>
    KnotVector<parameter> bezier(const ushort degree);
    template<typename parameter>
    KnotVector<parameter> uniform(const ushort degree, const ushort npts);
};

#endif