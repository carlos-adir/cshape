#include <iostream>
#include <stdexcept>
#include <vector>

#include "cshape/polynomial.h"

template <typename I, typename O>
Polynomial<I, O>::Polynomial (const O constant)
    : LinearAnalytic<I, O> (constant){};

template <typename I, typename O>
Polynomial<I, O>::Polynomial (const std::vector<O> &coefs)
    : LinearAnalytic<I, O> (coefs){};

template <typename I, typename O>
Polynomial<I, O>::Polynomial (const std::initializer_list<O> &coefs)
    : LinearAnalytic<I, O> (coefs){};

template <typename I, typename O>
Polynomial<I, O>::Polynomial (const Polynomial &other)
    : LinearAnalytic<I, O> (0)
{
    const uint1 odegree = other.degree ();
    for (uint1 i = 0; i <= odegree; i++)
        (*this)[i] = other[i];
};

template <typename I, typename O>
Polynomial<I, O> &
Polynomial<I, O>::operator*= (const Polynomial<I, O> &other)
{
    Polynomial<I, O> outpoly = (*this) * other;
    *this = outpoly;
    return *this;
};

template <typename I, typename O>
Polynomial<I, O> &
Polynomial<I, O>::operator/= (const Polynomial<I, O> &other)
{
    Polynomial<I, O> outpoly = (*this) / other;
    *this = outpoly;
    return *this;
};

template <typename I, typename O>
Polynomial<I, O> &
Polynomial<I, O>::operator%= (const Polynomial<I, O> &other)
{
    Polynomial<I, O> outpoly = (*this) % other;
    *this = outpoly;
    return *this;
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator* (const Polynomial<I, O> &other) const
{
    Polynomial<I, O> outpoly;
    for (uint1 i = 0; i <= this->degree (); i++)
        for (uint1 j = 0; j <= other.degree (); j++)
            outpoly[i + j] += (*this)[i] * other[j];
    return outpoly;
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator/ (const Polynomial<I, O> &other) const
{
    if (other.degree () == 0)
        {
            Polynomial<I, O> newpoly = *this;
            newpoly /= other[0];
            return newpoly;
        }
    const uint1 tdeg = this->degree ();
    const uint1 odeg = other.degree ();
    Polynomial<I, O> quotpoly;
    Polynomial<I, O> residual;
    residual = *this;
    O ratio;
    for (uint1 r = tdeg; r >= odeg; r--)
        {
            ratio = residual[r] / other[odeg];
            quotpoly[r - odeg] = ratio;
            residual[r] = 0;
            for (uint1 i = 0; i < odeg; i++)
                residual[i + r - odeg] -= ratio * other[i];
        }
    return quotpoly;
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator% (const Polynomial<I, O> &other) const
{
    if (other.degree () == 0)
        {
            Polynomial<I, O> newpoly = *this;
            newpoly /= other[0];
            return newpoly;
        }
    const uint1 tdeg = this->degree ();
    const uint1 odeg = other.degree ();
    Polynomial<I, O> quotpoly;
    Polynomial<I, O> residual;
    residual = *this;
    O ratio;
    for (uint1 r = residual.degree (); r >= odeg; r--)
        {
            ratio = residual[r] / other[odeg];
            quotpoly[r - odeg] = ratio;
            residual[r] = 0;
            for (uint1 i = 0; i < odeg; i++)
                residual[i + r - odeg] -= ratio * other[i];
        }
    return residual;
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator+ (const O other) const
{
    Polynomial<I, O> newfunc;
    newfunc = *this;
    newfunc.internal[0] += other;
    return newfunc;
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator- (const O other) const
{
    Polynomial<I, O> newfunc;
    newfunc = *this;
    newfunc.internal[0] -= other;
    return newfunc;
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator* (const O other) const
{
    Polynomial<I, O> newfunc;
    newfunc = *this;
    newfunc *= other;
    return newfunc;
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator/ (const O other) const
{
    Polynomial<I, O> newfunc;
    newfunc = *this;
    newfunc /= other;
    return newfunc;
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator% (const O other) const
{
    if (other == 0)
        throw std::invalid_argument ("Math error: Attempted to divide by zero");
    return Polynomial<I, O> (0);
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator- () const
{
    Polynomial<I, O> newfunc;
    newfunc = *this;
    newfunc *= -1;
    return newfunc;
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator+ (const Polynomial<I, O> &other) const
{
    Polynomial<I, O> newfunc;
    newfunc = *this;
    newfunc += other;
    return newfunc;
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator- (const Polynomial<I, O> &other) const
{
    Polynomial<I, O> newfunc;
    newfunc = *this;
    newfunc -= other;
    return newfunc;
};

template <typename I, typename O>
O
Polynomial<I, O>::eval (const I node, const uint1 deriv) const
{
    const uint1 degree = this->degree ();
    if (deriv > degree)
        return 0;
    O result = 0;
    uint4 deriv_coef;
    for (uint1 i = degree; i > deriv; i--)
        {
            result *= node;
            deriv_coef = 1;
            for (uint1 j = 0; j < deriv; j++)
                deriv_coef *= i - j;
            result += deriv_coef * this->internal[i];
        }
    result *= node;
    deriv_coef = 1;
    for (uint1 j = 0; j < deriv; j++)
        deriv_coef *= deriv - j;
    result += deriv_coef * this->internal[deriv];
    return result;
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
inline Polynomial<I, O>
operator+ (const O scalar, const Polynomial<I, O> &poly)
{
    return poly + scalar;
};
template <typename I, typename O>
inline Polynomial<I, O>
operator- (const O scalar, const Polynomial<I, O> &poly)
{
    return (-poly) + scalar;
};
template <typename I, typename O>
inline Polynomial<I, O>
operator* (const O scalar, const Polynomial<I, O> &poly)
{
    return poly * scalar;
};

template std::ostream &operator<< (std::ostream &os,
                                   const Polynomial<int, int> &poly);
template Polynomial<int, int> operator+ (const int scalar,
                                         const Polynomial<int, int> &poly);
template Polynomial<int, int> operator- (const int scalar,
                                         const Polynomial<int, int> &poly);
template Polynomial<int, int> operator* (const int scalar,
                                         const Polynomial<int, int> &poly);
