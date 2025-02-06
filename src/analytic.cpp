#include <vector>
#include <iostream>
#include <stdexcept>
#include "cshape/analytic.h"

template<typename Scalar>
LinearAnalytic::LinearAnalytic(const Scalar constant){
    this->resize(1);
    this->internal[0] = constant;
};
template<typename Scalar>
LinearAnalytic::LinearAnalytic(const std::vector<Scalar> &coefs) {
    const uint1 size = coefs.size();
    this->resize(size > 0 ? size : 1);
    for (uint1 i = 0; i < size; i++)
        this->internal[i] = coefs[i];
    this->clean();
};
template<typename Scalar>
LinearAnalytic::LinearAnalytic(const std::initializer_list<Scalar> &coefs){
    *this = coefs;
};




void LinearAnalytic::resize(const uint1 newsize){
    const uint1 oldsize = this->internal.size();
    if (!newsize) throw std::invalid_argument("Received size = 0 inside resize, at least 1 required");
    if (newsize > MAXSIZE) throw std::invalid_argument("Received size > MAXSIZE");
    this->internal.resize(newsize);
    if (oldsize < newsize)
        for(uint1 i = oldsize; i < newsize; i++)
            this->internal[i] = 0;
};

void LinearAnalytic::clean(){
    const uint1 degree = this->degree();
    if (degree + 1 != this->internal.size())
        this->resize(degree + 1);
};


uint1 LinearAnalytic::size() const{
    return this->internal.size();
};

uint1 LinearAnalytic::degree() const{
    uint1 degree = this->internal.size() - 1;
    while (degree && !this->internal[degree])
        degree--;
    return degree;
};


template<typename Scalar>
bool LinearAnalytic::operator==(const Scalar other) const{
    return this->internal.size() == 1 && this->internal[0] == other;
};

template<typename Scalar>
bool LinearAnalytic::operator!=(const Scalar other) const{
    return this->internal.size() != 1 || this->internal[0] != other;
};




template<typename Scalar>
LinearAnalytic &LinearAnalytic::operator=(const Scalar other){
    this->resize(1);
    this->internal[0] = other;
    return *this;
};

template<typename Scalar>
LinearAnalytic &LinearAnalytic::operator=(const std::initializer_list<Scalar> &coefs){
    const uint1 size = coefs.size() > 0 ? coefs.size() : 1;
    uint1 i = 0;
    this->resize(size);
    for (const Scalar& coef : coefs){
        this->internal[i] = coef;
        i++;
    }
    this->clean();
    return *this;
};

template<typename Scalar>
LinearAnalytic &LinearAnalytic::operator+=(const Scalar other){
    this->internal[0] += other;
    return *this;
};

template<typename Scalar>
LinearAnalytic &LinearAnalytic::operator-=(const Scalar other){
    this->internal[0] -= other;
    return *this;
};

template<typename Scalar>
LinearAnalytic &LinearAnalytic::operator*=(const Scalar other){
    for(uint1 i = 0; i < this->internal.size(); i++)
        this->internal[i] *= other;
    return *this;
};

template<typename Scalar>
LinearAnalytic &LinearAnalytic::operator/=(const Scalar other){
    if (other == 0)
        throw std::invalid_argument("Math error: Attempted to divide by zero");
    for(uint1 i = 0; i < this->internal.size(); i++)
        this->internal[i] /= other;
    return *this;
};



template<typename Scalar>
LinearAnalytic &LinearAnalytic::operator%=(const Scalar other){
    if (other == 0)
        throw std::invalid_argument("Math error: Attempted to divide by zero");
    this->resize(1);
    this->internal[0] = 0;
    return *this;
};



template<typename Scalar>
LinearAnalytic LinearAnalytic::operator+(const Scalar other) const{
    LinearAnalytic newfunc = LinearAnalytic(this->internal);
    newfunc.internal[0] += other;
    return newfunc;
};


template<typename Scalar>
LinearAnalytic LinearAnalytic::operator-(const Scalar other) const{
    LinearAnalytic newfunc = LinearAnalytic(this->internal);
    newfunc.internal[0] -= other;
    return newfunc;
};

template<typename Scalar>
LinearAnalytic LinearAnalytic::operator*(const Scalar other) const{
    LinearAnalytic newfunc = LinearAnalytic(this->internal);
    newfunc *= other;
    return newfunc;
};

template<typename Scalar>
LinearAnalytic LinearAnalytic::operator/(const Scalar other) const{
    LinearAnalytic newfunc = LinearAnalytic(this->internal);
    newfunc /= other;
    return newfunc;
};

template<typename Scalar>
LinearAnalytic LinearAnalytic::operator%(const Scalar other) const{
    if (other == 0)
        throw std::invalid_argument("Math error: Attempted to divide by zero");
    return LinearAnalytic(0);
};


Coordinate &LinearAnalytic::operator[](const uint1 index){
    if (this->internal.size() <= index) this->resize(index + 1);
    return this->internal[index];
};

const Coordinate LinearAnalytic::operator[](const uint1 index) const
{
    return (index < this->internal.size()) ? (this->internal[index]) : Coordinate(0);
};






template LinearAnalytic::LinearAnalytic(const int constant);
template LinearAnalytic::LinearAnalytic(const std::vector<int> &coefs);
template LinearAnalytic::LinearAnalytic(const std::initializer_list<int> &coefs);
template bool LinearAnalytic::operator==(int const) const;
template bool LinearAnalytic::operator!=(int const) const;
template LinearAnalytic &LinearAnalytic::operator=(int const);
template LinearAnalytic &LinearAnalytic::operator=(const std::initializer_list<int> &coefs);
template LinearAnalytic &LinearAnalytic::operator+=(int const);
template LinearAnalytic &LinearAnalytic::operator-=(int const);
template LinearAnalytic &LinearAnalytic::operator*=(int const);
template LinearAnalytic &LinearAnalytic::operator/=(int const);
template LinearAnalytic &LinearAnalytic::operator%=(int const);
template LinearAnalytic LinearAnalytic::operator+(int const) const;
template LinearAnalytic LinearAnalytic::operator-(int const) const;
template LinearAnalytic LinearAnalytic::operator*(int const) const;
template LinearAnalytic LinearAnalytic::operator/(int const) const;
template LinearAnalytic LinearAnalytic::operator%(int const) const;



template LinearAnalytic::LinearAnalytic(const double constant);
template LinearAnalytic::LinearAnalytic(const std::vector<double> &coefs);
template LinearAnalytic::LinearAnalytic(const std::initializer_list<double> &coefs);
template bool LinearAnalytic::operator==(double const) const;
template bool LinearAnalytic::operator!=(double const) const;
template LinearAnalytic &LinearAnalytic::operator=(double const);
template LinearAnalytic &LinearAnalytic::operator=(const std::initializer_list<double> &coefs);
template LinearAnalytic &LinearAnalytic::operator+=(double const);
template LinearAnalytic &LinearAnalytic::operator-=(double const);
template LinearAnalytic &LinearAnalytic::operator*=(double const);
template LinearAnalytic &LinearAnalytic::operator/=(double const);
template LinearAnalytic &LinearAnalytic::operator%=(double const);
template LinearAnalytic LinearAnalytic::operator+(double const) const;
template LinearAnalytic LinearAnalytic::operator-(double const) const;
template LinearAnalytic LinearAnalytic::operator*(double const) const;
template LinearAnalytic LinearAnalytic::operator/(double const) const;
template LinearAnalytic LinearAnalytic::operator%(double const) const;


template LinearAnalytic::LinearAnalytic(const Coordinate constant);
template LinearAnalytic::LinearAnalytic(const std::vector<Coordinate> &coefs);
template LinearAnalytic::LinearAnalytic(const std::initializer_list<Coordinate> &coefs);
template bool LinearAnalytic::operator==(Coordinate const) const;
template bool LinearAnalytic::operator!=(Coordinate const) const;
template LinearAnalytic &LinearAnalytic::operator=(Coordinate const);
template LinearAnalytic &LinearAnalytic::operator=(const std::initializer_list<Coordinate> &coefs);
template LinearAnalytic &LinearAnalytic::operator+=(Coordinate const);
template LinearAnalytic &LinearAnalytic::operator-=(Coordinate const);
template LinearAnalytic &LinearAnalytic::operator*=(Coordinate const);
template LinearAnalytic &LinearAnalytic::operator%=(Coordinate const);
template LinearAnalytic &LinearAnalytic::operator/=(Coordinate const);
template LinearAnalytic LinearAnalytic::operator+(Coordinate const) const;
template LinearAnalytic LinearAnalytic::operator-(Coordinate const) const;
template LinearAnalytic LinearAnalytic::operator*(Coordinate const) const;
template LinearAnalytic LinearAnalytic::operator/(Coordinate const) const;
template LinearAnalytic LinearAnalytic::operator%(Coordinate const) const;


