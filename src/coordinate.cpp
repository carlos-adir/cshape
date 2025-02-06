#include "cshape/coordinate.h"


template<typename T>
Coordinate::Coordinate(const T val) : internal(val) {}


bool Coordinate::operator==(const Coordinate &other) const{
    return internal == other.internal;
};

bool Coordinate::operator!=(const Coordinate &other) const{
    return internal != other.internal;
};

bool Coordinate::operator<(const Coordinate &other) const{
    return internal < other.internal;
};

bool Coordinate::operator>(const Coordinate &other) const{
    return internal > other.internal;
};

bool Coordinate::operator<=(const Coordinate &other) const{
    return internal <= other.internal;
};

bool Coordinate::operator>=(const Coordinate &other) const{
    return internal >= other.internal;
};


template<typename T>
bool Coordinate::operator==(const T &other) const{
    return internal == other;
};

template<typename T>
bool Coordinate::operator!=(const T &other) const{
    return internal != other;
};

template<typename T>
bool Coordinate::operator<(const T &other) const{
    return internal < other;
};

template<typename T>
bool Coordinate::operator>(const T &other) const{
    return internal > other;
};

template<typename T>
bool Coordinate::operator<=(const T &other) const{
    return internal <= other;
};

template<typename T>
bool Coordinate::operator>=(const T &other) const{
    return internal >= other;
};


template<typename T>
Coordinate &Coordinate::operator=(const T value){ 
    this->internal = value;
    return *this;
};


Coordinate &Coordinate::operator=(const Coordinate& value){ 
    this->internal = value.internal;
    return *this;
};
Coordinate &Coordinate::operator+=(const Coordinate& rhs){ 
    this->internal += rhs.internal;
    return *this;
};
Coordinate &Coordinate::operator-=(const Coordinate& rhs) {
    this->internal -= rhs.internal;
    return *this;
    
};
Coordinate &Coordinate::operator*=(const Coordinate& rhs) {
    this->internal *= rhs.internal;
    return *this;

};
Coordinate &Coordinate::operator/=(const Coordinate& rhs) {
    this->internal /= rhs.internal;
    return *this;
};

Coordinate Coordinate::operator+(const Coordinate& rhs) const{
    return Coordinate(internal + rhs.internal);
};
Coordinate Coordinate::operator-(const Coordinate& rhs) const{
    return Coordinate(internal - rhs.internal);
    
};
Coordinate Coordinate::operator*(const Coordinate& rhs) const{
    return Coordinate(internal * rhs.internal);

};
Coordinate Coordinate::operator/(const Coordinate& rhs) const{
    return Coordinate(internal / rhs.internal);
};


std::ostream &operator<<(std::ostream &os, const Coordinate &param)
{
    os << param.internal;
    return os;
};










template Coordinate::Coordinate(const int);
// template Coordinate& Coordinate::operator=(int const&);
template Coordinate& Coordinate::operator=(int const);
template bool Coordinate::operator==(int const&) const;
template bool Coordinate::operator!=(int const&) const;
template bool Coordinate::operator<(int const&) const;
template bool Coordinate::operator<=(int const&) const;
template bool Coordinate::operator>(int const&) const;
template bool Coordinate::operator>=(int const&) const;


template Coordinate::Coordinate(const double);
// template Coordinate& Coordinate::operator=(double const&);
template Coordinate& Coordinate::operator=(double const);
template bool Coordinate::operator==(double const&) const;
template bool Coordinate::operator!=(double const&) const;
template bool Coordinate::operator<(double const&) const;
template bool Coordinate::operator<=(double const&) const;
template bool Coordinate::operator>(double const&) const;
template bool Coordinate::operator>=(double const&) const;


static const Coordinate NEGINF = -std::numeric_limits<double>::max();
static const Coordinate POSINF = std::numeric_limits<double>::max();

