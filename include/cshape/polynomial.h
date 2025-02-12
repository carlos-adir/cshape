#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>

#include "analytic.h"

template <typename I, typename O>
class Polynomial : public LinearAnalytic<I, O> {
   public:
    explicit Polynomial(const O value = 0);
    Polynomial(const std::vector<O> &coefs);
    Polynomial(const std::initializer_list<O> &coefs);
    Polynomial(const Polynomial<I, O> &other);

    using LinearAnalytic<I, O>::operator=;
    using LinearAnalytic<I, O>::operator+=;
    using LinearAnalytic<I, O>::operator-=;
    using LinearAnalytic<I, O>::operator*=;
    using LinearAnalytic<I, O>::operator/=;
    using LinearAnalytic<I, O>::operator%=;

    Polynomial &operator*=(const Polynomial<I, O> &other);
    Polynomial &operator/=(const Polynomial<I, O> &other);
    Polynomial &operator%=(const Polynomial<I, O> &other);
    Polynomial operator*(const Polynomial<I, O> &other) const;
    Polynomial operator/(const Polynomial<I, O> &other) const;
    Polynomial operator%(const Polynomial<I, O> &other) const;

    virtual Polynomial<I, O> operator+(const O other) const final;
    virtual Polynomial<I, O> operator-(const O other) const final;
    virtual Polynomial<I, O> operator*(const O other) const final;
    virtual Polynomial<I, O> operator/(const O other) const final;
    virtual Polynomial<I, O> operator%(const O other) const final;
    virtual Polynomial<I, O> operator-() const final;

    virtual Polynomial<I, O> operator+(
        const Polynomial<I, O> &other) const final;
    virtual Polynomial<I, O> operator-(
        const Polynomial<I, O> &other) const final;

    O eval(const I node, const uint1 deriv = 0) const;
};

template <typename I, typename O>
std::ostream &operator<<(std::ostream &os, const Polynomial<I, O> &poly);

template class Polynomial<int, int>;

#endif
