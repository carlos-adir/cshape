#include <vector>
#include <iostream>
#include <stdexcept>
#include "cshape/polynomial.h"


Polynomial::Polynomial() : LinearAnalytic(0){};
template<typename Scalar>
Polynomial::Polynomial(const Scalar constant) : LinearAnalytic(constant){};
template<typename Scalar>
Polynomial::Polynomial(const std::vector<Scalar> &coefs) : LinearAnalytic(coefs) {};
template<typename Scalar>
Polynomial::Polynomial(const std::initializer_list<Scalar> &coefs) : LinearAnalytic(coefs) {};




bool Polynomial::operator==(const Polynomial &other) const{
    if (this->size() != other.size())
        return false;
    for (uint1 i = 0; i < this->size(); i++)
        if (this->internal[i] != other.internal[i])
            return false;
    return true;
};



bool Polynomial::operator!=(const Polynomial &other) const{
    return !((*this) == other);
};


Polynomial &Polynomial::operator=(const Polynomial &other){
    this->resize(other.size());
    for(uint1 i = 0; i < other.size(); i++)
        this->internal[i] = other.internal[i];
    return *this;
}

Polynomial &Polynomial::operator+=(const Polynomial &other){
    if(this->internal.size() < other.internal.size())
        this->resize(other.internal.size());
    for(uint1 i = 0; i < other.internal.size(); i++)
        this->internal[i] += other.internal[i];
    this->clean();
    return *this;
}


Polynomial &Polynomial::operator-=(const Polynomial &other){
    if(this->internal.size() < other.internal.size())
        this->resize(other.internal.size());
    for(uint1 i = 0; i < other.internal.size(); i++)
        this->internal[i] -= other.internal[i];
    this->clean();
    return *this;
}

Polynomial &Polynomial::operator*=(const Polynomial &other){
    Polynomial outpoly = (*this) * other;
    this->resize(outpoly.size());
    for (uint1 i = 0; i < outpoly.size(); i++)
        this->internal[i] = outpoly.internal[i];
    this->clean();
    return *this;
}


Polynomial &Polynomial::operator/=(const Polynomial &other){
    Polynomial outpoly = (*this) / other;
    this->resize(outpoly.size());
    for (uint1 i = 0; i < outpoly.size(); i++)
        this->internal[i] = outpoly.internal[i];
    this->clean();
    return *this;
}



Polynomial &Polynomial::operator%=(const Polynomial &other){
    Polynomial outpoly = (*this) % other;
    this->resize(outpoly.size());
    for (uint1 i = 0; i < outpoly.size(); i++)
        this->internal[i] = outpoly.internal[i];
    this->clean();
    return *this;
}


Polynomial Polynomial::operator+(const Polynomial &other) const{
    Polynomial outpoly(this->internal);
    outpoly += other;
    return outpoly;
}


Polynomial Polynomial::operator-(const Polynomial &other) const{
    Polynomial outpoly(this->internal);
    outpoly -= other;
    return outpoly;
}


Polynomial Polynomial::operator*(const Polynomial &other) const{
    Polynomial outpoly;
    outpoly.resize(this->size() - 1 + other.size());
    for (uint1 i = 0; i < this->size(); i++)
        for (uint1 j = 0; j < other.size(); j++)
            outpoly.internal[i+j] += this->internal[i] * other[j];
    outpoly.clean();
    return outpoly;
}

Polynomial Polynomial::operator/(const Polynomial &other) const{
    if (other.size() == 1)
        return (*this) / other[0];
    const uint1 tdeg = this->degree();
    const uint1 odeg = other.degree();
    Polynomial quotpoly;
    Polynomial residual(this->internal);
    Coordinate ratio;
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


Polynomial Polynomial::operator%(const Polynomial &other) const{
    if (other.size() == 1)
        return (*this) / other[0];
    const uint1 tdeg = this->degree();
    const uint1 odeg = other.degree();
    Polynomial quotpoly;
    Polynomial residual(this->internal);
    Coordinate ratio;
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




template<typename Scalar>
Coordinate Polynomial::eval(const Scalar node, const uint1 deriv) const{
    Coordinate result = 0;
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


std::ostream &operator<<(std::ostream &os, const Polynomial &poly){
    const uint1 degree = poly.degree();
    os << "Poly[";
    for (uint1 i = 0; i < degree; i++)
        os << poly[i] << ", ";
    os << poly[degree] << "]";
    return os;
};


template Polynomial::Polynomial(const int constant);
template Polynomial::Polynomial(const std::vector<int> &coefs);
template Polynomial::Polynomial(const std::initializer_list<int> &coefs);
template Coordinate Polynomial::eval(const int node, const uint1 deriv) const;




template Polynomial::Polynomial(const double constant);
template Polynomial::Polynomial(const std::vector<double> &coefs);
template Polynomial::Polynomial(const std::initializer_list<double> &coefs);
template Coordinate Polynomial::eval(const double node, const uint1 deriv) const;





template Polynomial::Polynomial(const Coordinate constant);
template Polynomial::Polynomial(const std::vector<Coordinate> &coefs);
template Polynomial::Polynomial(const std::initializer_list<Coordinate> &coefs);
template Coordinate Polynomial::eval(const Parameter node, const uint1 deriv) const;




