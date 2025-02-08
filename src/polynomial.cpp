#include <vector>
#include <iostream>
#include <stdexcept>
#include "cshape/polynomial.h"

template<typename I, typename O>
Polynomial<I, O>::Polynomial(const O constant) : LinearAnalytic<I, O>(constant){};
template<typename I, typename O>
Polynomial<I, O>::Polynomial(const std::vector<O> &coefs) : LinearAnalytic<I, O>(coefs) {};
template<typename I, typename O>
Polynomial<I, O>::Polynomial(const std::initializer_list<O> &coefs) : LinearAnalytic<I, O>(coefs) {};





template<typename I, typename O>
Polynomial<I, O> &Polynomial<I, O>::operator*=(const Polynomial<I, O> &other){
    Polynomial<I, O> outpoly = (*this) * other;
    this->resize(outpoly.size());
    for (uint1 i = 0; i < outpoly.size(); i++)
        this->internal[i] = outpoly.internal[i];
    this->clean();
    return *this;
}

template<typename I, typename O>
Polynomial<I, O> &Polynomial<I, O>::operator/=(const Polynomial<I, O> &other){
    Polynomial<I, O> outpoly = (*this) / other;
    this->resize(outpoly.size());
    for (uint1 i = 0; i < outpoly.size(); i++)
        this->internal[i] = outpoly.internal[i];
    this->clean();
    return *this;
}


template<typename I, typename O>
Polynomial<I, O> &Polynomial<I, O>::operator%=(const Polynomial<I, O> &other){
    Polynomial<I, O> outpoly = (*this) % other;
    this->resize(outpoly.size());
    for (uint1 i = 0; i < outpoly.size(); i++)
        this->internal[i] = outpoly.internal[i];
    this->clean();
    return *this;
}

template<typename I, typename O>
Polynomial<I, O> Polynomial<I, O>::operator*(const Polynomial<I, O> &other) const{
    Polynomial<I, O> outpoly;
    outpoly.resize(this->size() - 1 + other.size());
    for (uint1 i = 0; i < this->size(); i++)
        for (uint1 j = 0; j < other.size(); j++)
            outpoly.internal[i+j] += this->internal[i] * other[j];
    outpoly.clean();
    return outpoly;
}
template<typename I, typename O>
Polynomial<I, O> Polynomial<I, O>::operator/(const Polynomial<I, O> &other) const{
    if (other.size() == 1)
        return (*this) / other[0];
    const uint1 tdeg = this->degree();
    const uint1 odeg = other.degree();
    Polynomial<I, O> quotpoly;
    Polynomial<I, O> residual(this->internal);
    O ratio;
    for (uint1 r = tdeg; r >= odeg; r--){
        ratio = residual[r] / other[odeg];
        quotpoly[r - odeg] = ratio;
        residual[r] = 0;
        for (uint1 i = 0; i < odeg; i++)
            residual[i + r - odeg] -= ratio * other[i];
    }
    quotpoly.clean();
    return quotpoly;
}

template<typename I, typename O>
Polynomial<I, O> Polynomial<I, O>::operator%(const Polynomial<I, O> &other) const{
    if (other.size() == 1)
        return (*this) / other[0];
    const uint1 tdeg = this->degree();
    const uint1 odeg = other.degree();
    Polynomial<I, O> quotpoly;
    Polynomial<I, O> residual(this->internal);
    O ratio;
    for (uint1 r = residual.degree(); r >= odeg; r--){
        ratio = residual[r] / other[odeg];
        quotpoly[r - odeg] = ratio;
        residual[r] = 0;
        for (uint1 i = 0; i < odeg; i++)
            residual[i + r - odeg] -= ratio * other[i];
    }
    residual.clean();
    return residual;
}




template<typename I, typename O>
O Polynomial<I, O>::eval(const I node, const uint1 deriv) const{
    O result = 0;
    const uint1 degree = this->degree();
    uint4 deriv_coef;
    for (uint1 i = degree; i > deriv; i--){
        result *= node;
        deriv_coef = 1;
        for (uint1 j = 0; j < deriv; j++)
            deriv_coef *= i - j;
        result += deriv_coef * this->internal[i];
    }
    result *= node;
    result += this->internal[deriv];
    return result;
}

template<typename I, typename O>
std::ostream &operator<<(std::ostream &os, const Polynomial<I, O> &poly){
    const uint1 degree = poly.degree();
    os << "Poly[";
    for (uint1 i = 0; i < degree; i++)
        os << poly[i] << ", ";
    os << poly[degree] << "]";
    return os;
};



