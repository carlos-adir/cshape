#include <vector>
#include <iostream>
#include <stdexcept>
#include "cshape/polynomial.h"

template<typename I, typename O>
Polynomial<I, O>::Polynomial(const O constant) : LinearAnalytic<I, O>(constant){
    std::cout << "Polynomial constant construction with " << constant << std::endl;
};

template<typename I, typename O>
Polynomial<I, O>::Polynomial(const std::vector<O> &coefs) : LinearAnalytic<I, O>(coefs) {};

template<typename I, typename O>
Polynomial<I, O>::Polynomial(const std::initializer_list<O> &coefs) : LinearAnalytic<I, O>(coefs) {};

template<typename I, typename O>
Polynomial<I, O>::Polynomial(const Polynomial &other) : LinearAnalytic<I, O>(0) {
    const uint1 odegree = other.degree();
    for (uint1 i = 0; i <= odegree; i++)
        (*this)[i] = other[i];
};




template<typename I, typename O>
Polynomial<I, O> &Polynomial<I, O>::operator*=(const Polynomial<I, O> &other){
    std::cout << "Poly (" << *this << ") *= Poly (" << other << ")" << std::endl;
    Polynomial<I, O> outpoly = (*this) * other;
    *this = outpoly;
    return *this;
}

template<typename I, typename O>
Polynomial<I, O> &Polynomial<I, O>::operator/=(const Polynomial<I, O> &other){
    std::cout << "Poly (" << *this << ") /= Poly (" << other << ")" << std::endl;
    Polynomial<I, O> outpoly = (*this) / other;
    *this = outpoly;
    return *this;
}


template<typename I, typename O>
Polynomial<I, O> &Polynomial<I, O>::operator%=(const Polynomial<I, O> &other){
    std::cout << "Poly (" << *this << ") %= Poly (" << other << ")" << std::endl;
    Polynomial<I, O> outpoly = (*this) % other;
    *this = outpoly;
    return *this;
}

template<typename I, typename O>
Polynomial<I, O> Polynomial<I, O>::operator*(const Polynomial<I, O> &other) const{
    std::cout << "Poly (" << *this << ") * Poly (" << other << ")" << std::endl;
    Polynomial<I, O> outpoly;
    for (uint1 i = 0; i <= this->degree(); i++)
        for (uint1 j = 0; j <= other.degree(); j++)
            outpoly[i+j] += (*this)[i] * other[j];
    return outpoly;
}
template<typename I, typename O>
Polynomial<I, O> Polynomial<I, O>::operator/(const Polynomial<I, O> &other) const{
    std::cout << "Poly (" << *this << ") / Poly (" << other << ")" << std::endl;
    if (other.degree() == 0){
        Polynomial<I, O> newpoly = *this;
        newpoly /= other[0];
        return newpoly;
    }
    const uint1 tdeg = this->degree();
    const uint1 odeg = other.degree();
    Polynomial<I, O> quotpoly;
    Polynomial<I, O> residual;
    residual = *this;
    O ratio;
    for (uint1 r = tdeg; r >= odeg; r--){
        std::cout << "#";
        ratio = residual[r] / other[odeg];
        quotpoly[r - odeg] = ratio;
        residual[r] = 0;
        for (uint1 i = 0; i < odeg; i++)
            residual[i + r - odeg] -= ratio * other[i];
    }
    std::cout << std::endl;
    return quotpoly;
}

template<typename I, typename O>
Polynomial<I, O> Polynomial<I, O>::operator%(const Polynomial<I, O> &other) const{
    if (other.degree() == 0){
        Polynomial<I, O> newpoly = *this;
        newpoly /= other[0];
        return newpoly;
    }
    const uint1 tdeg = this->degree();
    const uint1 odeg = other.degree();
    Polynomial<I, O> quotpoly;
    Polynomial<I, O> residual;
    residual = *this;
    O ratio;
    std::cout << "O";
    for (uint1 r = residual.degree(); r >= odeg; r--){
        std::cout << ".";
        ratio = residual[r] / other[odeg];
        quotpoly[r - odeg] = ratio;
        residual[r] = 0;
        for (uint1 i = 0; i < odeg; i++)
            residual[i + r - odeg] -= ratio * other[i];
    }
    std::cout << std::endl;
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
        result += deriv_coef * (*this)[i];
    }
    result *= node;
    result += (*this)[deriv];
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



