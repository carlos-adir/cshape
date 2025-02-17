#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>


typedef double basetype;

class Scalar{
private:
    const basetype internal;
public:
    Scalar(const basetype &value = 0): internal(value) {};
    Scalar(const Scalar &other): Scalar(other.internal) {};

    virtual bool operator==(const Scalar &other) const final;
    virtual bool operator!=(const Scalar &other) const final;
    virtual bool operator<(const Scalar &other) const final;
    virtual bool operator<=(const Scalar &other) const final;
    virtual bool operator>=(const Scalar &other) const final;
    virtual bool operator>(const Scalar &other) const final;

    virtual bool operator+(const Scalar &other) const final;
    virtual bool operator-(const Scalar &other) const final;
    virtual bool operator*(const Scalar &other) const final;
    virtual bool operator/(const Scalar &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const Scalar &value);
};


bool Scalar::operator==(const Scalar &other) const{
    return this->internal == other.internal;
};

bool Scalar::operator!=(const Scalar &other) const{
    return this->internal != other.internal;
};

bool Scalar::operator>(const Scalar &other) const{
    return this->internal > other.internal;
};

bool Scalar::operator>=(const Scalar &other) const{
    return this->internal >= other.internal;
};

bool Scalar::operator<=(const Scalar &other) const{
    return this->internal <= other.internal;
};

bool Scalar::operator<(const Scalar &other) const{
    return this->internal < other.internal;
};




bool Scalar::operator+(const Scalar &other) const{
    return this->internal + other.internal;
};
bool Scalar::operator-(const Scalar &other) const{
    return this->internal - other.internal;
};
bool Scalar::operator*(const Scalar &other) const{
    return this->internal * other.internal;
};
bool Scalar::operator/(const Scalar &other) const{
    return this->internal / other.internal;
};


std::ostream &operator<< (std::ostream &os, const Scalar &value){    
    os << value.internal;
    return os;
}



#endif
