#ifndef NURBS_H
#define NURBS_H

#include <iostream>
#include <vector>

namespace Math{
    unsigned short binom(const unsigned short n, const unsigned short i);
    template<typename parameter>
    parameter bezier(const parameter u, const unsigned short p, const unsigned short i);
};


template<typename parameter>
class KnotVector
{
private:
    const std::vector<parameter> internal;
public:
    KnotVector(const std::vector<parameter> &init_vector);
    ~KnotVector() = default;
    const parameter& operator[](const unsigned short index) const;
    const unsigned short degree;
    const unsigned short npts;
    unsigned short span(const parameter node);
    unsigned short mult(const parameter node);
};

std::ostream& operator<<(std::ostream &os, const KnotVector<double>& knotvector);

namespace GeneratorKnotVector{
    template<typename parameter>
    KnotVector<parameter> bezier(const unsigned short degree);
    template<typename parameter>
    KnotVector<parameter> uniform(const unsigned short degree, const unsigned short npts);
};

#endif