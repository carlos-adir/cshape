#ifndef ANALYTIC_H
#define ANALYTIC_H

#include <iostream>
#include <vector>
#include "rbool.h"

typedef unsigned long uint8;
typedef unsigned int uint4;
typedef unsigned short uint2;
typedef unsigned short uint1;

const static uint1 MAXSIZE = 100;

template <typename I, typename O>
class IAnalytic {
    public:
        IAnalytic() {};
        const SubSetR1 domain = SubSetR1::Whole();
        IAnalytic(const IAnalytic<I, O>& other);  // copy
        virtual O operator()(const I& node) const final { return eval(node);};
        virtual O eval(const I node, const uint1 deriv = 0) const = 0;
        // virtual bool operator!=(const O& other) const final {return !(this->operator==(other));};
        // virtual bool operator!=(const IAnalytic<I, O> &other) const final {return !(this->operator==(other));};
};

template <typename I, typename O>
class BaseAnalytic : public IAnalytic<I, O>
{
    public:
        BaseAnalytic() {};
};
template <typename I, typename O>
class CompositionAnalytic : BaseAnalytic<I, O> {};

template <typename I, typename O>
class Polynomial : public BaseAnalytic<I, O>
{
    public:
        const uint1 degree;
        const std::vector<O> coefficients;
        Polynomial(const O constant = 0);
        Polynomial(const std::vector<O> &coefs);
        Polynomial(const std::initializer_list<O> &coefs);
        Polynomial(const Polynomial<I, O> &other);

        virtual bool operator==(const O& other) const final;
        virtual bool operator!=(const O& other) const final {return !(this->operator==(other));};
        virtual bool operator==(const Polynomial<I, O> &other) const final;
        virtual bool operator!=(const Polynomial<I, O> &other) const final {return !(this->operator==(other));};
        virtual O operator[](const uint1 index) const final { return index > degree ? O(0) : coefficients[index];};
        
        Polynomial<I, O> operator-() const;
        Polynomial<I, O> operator+(const O& other) const;
        Polynomial<I, O> operator-(const O& other) const;
        Polynomial<I, O> operator*(const O& other) const;
        Polynomial<I, O> operator/(const O& other) const;
        Polynomial<I, O> operator%(const O& other) const;
        Polynomial<I, O> operator+(const Polynomial<I, O>& other) const;
        Polynomial<I, O> operator-(const Polynomial<I, O>& other) const;
        Polynomial<I, O> operator*(const Polynomial<I, O>& other) const;
        Polynomial<I, O> operator/(const Polynomial<I, O>& other) const;
        Polynomial<I, O> operator%(const Polynomial<I, O>& other) const;

        operator std::string() const;
        template <typename A, typename B>
        friend std::ostream &operator<<(std::ostream &os, const Polynomial<A, B> &obj);

        O eval(const I node, const uint1 deriv = 0) const override final;
};



template <typename I, typename O>
std::ostream &
operator<< (std::ostream &os, const Polynomial<I, O> &poly)
{
    const uint1 degree = poly.degree ();
    os << "Poly[";
    for (uint1 i = 0; i < degree; i++)
        os << poly[i] << ", ";
    os << poly[degree] << "]";
    return os;
};

template <typename I, typename O>
Polynomial<I, O> operator+ (const O& scalar, const Polynomial<I, O> &poly)
{
    return poly + scalar;
}
template <typename I, typename O>
Polynomial<I, O> operator- (const O& scalar, const Polynomial<I, O> &poly)
{
    return (-poly) + scalar;
}
template <typename I, typename O>
Polynomial<I, O> operator* (const O& scalar, const Polynomial<I, O> &poly)
{
    return poly * scalar;
}


template class Polynomial<int, int>;
template class Polynomial<int, scalar>;
template class Polynomial<scalar, int>;
template class Polynomial<scalar, scalar>;

#endif