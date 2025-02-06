#include "cshape/parameter.h"


template<typename T>
Parameter::Parameter(const T val) : internal(val) {}


bool Parameter::operator==(const Parameter &other) const{
    return internal == other.internal;
};

bool Parameter::operator!=(const Parameter &other) const{
    return internal != other.internal;
};

bool Parameter::operator<(const Parameter &other) const{
    return internal < other.internal;
};

bool Parameter::operator>(const Parameter &other) const{
    return internal > other.internal;
};

bool Parameter::operator<=(const Parameter &other) const{
    return internal <= other.internal;
};

bool Parameter::operator>=(const Parameter &other) const{
    return internal >= other.internal;
};


template<typename T>
bool Parameter::operator==(const T &other) const{
    return internal == other;
};

template<typename T>
bool Parameter::operator!=(const T &other) const{
    return internal != other;
};

template<typename T>
bool Parameter::operator<(const T &other) const{
    return internal < other;
};

template<typename T>
bool Parameter::operator>(const T &other) const{
    return internal > other;
};

template<typename T>
bool Parameter::operator<=(const T &other) const{
    return internal <= other;
};

template<typename T>
bool Parameter::operator>=(const T &other) const{
    return internal >= other;
};


template<typename T>
Parameter &Parameter::operator=(const T& value){ 
    this->internal = value;
    return *this;
};


Parameter &Parameter::operator=(const Parameter& value){ 
    this->internal = value.internal;
    return *this;
};
Parameter &Parameter::operator+=(const Parameter& rhs){ 
    this->internal += rhs.internal;
    return *this;
};
Parameter &Parameter::operator-=(const Parameter& rhs) {
    this->internal -= rhs.internal;
    return *this;
    
};
Parameter &Parameter::operator*=(const Parameter& rhs) {
    this->internal *= rhs.internal;
    return *this;

};
Parameter &Parameter::operator/=(const Parameter& rhs) {
    this->internal /= rhs.internal;
    return *this;
};

Parameter Parameter::operator+(const Parameter& rhs) const{
    return Parameter(internal + rhs.internal);
};
Parameter Parameter::operator-(const Parameter& rhs) const{
    return Parameter(internal - rhs.internal);
    
};
Parameter Parameter::operator*(const Parameter& rhs) const{
    return Parameter(internal * rhs.internal);

};
Parameter Parameter::operator/(const Parameter& rhs) const{
    return Parameter(internal / rhs.internal);
};


std::ostream &operator<<(std::ostream &os, const Parameter &param)
{
    os << param.internal;
    return os;
};



template Parameter::Parameter(const int);
template Parameter& Parameter::operator=<int>(int const&);
template bool Parameter::operator==<int>(int const&) const;
template bool Parameter::operator!=<int>(int const&) const;
template bool Parameter::operator< <int>(int const&) const;
template bool Parameter::operator<= <int>(int const&) const;
template bool Parameter::operator> <int>(int const&) const;
template bool Parameter::operator>= <int>(int const&) const;

template Parameter::Parameter(const double);
template Parameter& Parameter::operator=<double>(double const&);
template bool Parameter::operator==<double>(double const&) const;
template bool Parameter::operator!=<double>(double const&) const;
template bool Parameter::operator< <double>(double const&) const;
template bool Parameter::operator<= <double>(double const&) const;
template bool Parameter::operator> <double>(double const&) const;
template bool Parameter::operator>= <double>(double const&) const;




static const Parameter NEGINF = -std::numeric_limits<double>::max();
static const Parameter POSINF = std::numeric_limits<double>::max();

