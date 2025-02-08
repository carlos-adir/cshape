#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "analytic.h"
#include <vector>

template<typename I, typename O>
class Polynomial : public LinearAnalytic<I, O>{

public:

    explicit Polynomial(const O value = 0);
    Polynomial(const std::vector<O> &coefs);
    Polynomial(const std::initializer_list<O> &coefs);

    Polynomial &operator*=(const Polynomial<I, O> &other);
    Polynomial &operator/=(const Polynomial<I, O> &other);
    Polynomial &operator%=(const Polynomial<I, O> &other);
    Polynomial operator*(const Polynomial<I, O> &other) const;
    Polynomial operator/(const Polynomial<I, O> &other) const;
    Polynomial operator%(const Polynomial<I, O> &other) const;

    O eval(const I node, const uint1 deriv = 0) const;
//     Coordinate defintegral(const Parameter nodea, const Parameter nodeb) const;
//     Polynomial derivate(const uint1 times = 1) const;
//     Polynomial shift(const Parameter amount) const;
//     Polynomial scale(const Parameter amount) const;
};

template<typename I, typename O>
std::ostream &operator<<(std::ostream &os, const Polynomial<I, O> &poly);



template class Polynomial<int, int>;

#endif