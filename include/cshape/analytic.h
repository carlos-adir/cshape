#ifndef ANALYTIC_H
#define ANALYTIC_H

#include "parameter.h"
#include "coordinate.h"
#include <vector>

typedef unsigned long uint8;
typedef unsigned int uint4;
typedef unsigned short uint2;
typedef unsigned int uint1;

const uint1 MAXSIZE = 100;

class IAnalytic{

public:
    Coordinate eval(const Parameter node, const uint1 deriv = 0) const;
    Coordinate defintegral(const Parameter nodea, const Parameter nodeb) const;
    IAnalytic derivate(const uint1 times = 1) const;
    IAnalytic shift(const Parameter amount) const; 
    IAnalytic scale(const Parameter amount) const;
};

class LinearAnalytic : public IAnalytic{
public:
    std::vector<Coordinate> internal;
    void resize(const uint1 newsize);
    void clean();

public:
    template<typename Scalar>
    LinearAnalytic(const Scalar value);
    template<typename Scalar>
    LinearAnalytic(const std::vector<Scalar> &coefs);
    template<typename Scalar>
    LinearAnalytic(const std::initializer_list<Scalar> &coefs);

    const Coordinate operator[](const uint1 index) const;  // getter
    Coordinate &operator[](const uint1 index); // setter
    
    template<typename Scalar>
    Coordinate operator()(const Scalar node) const {return eval(node);};

    
    template<typename Scalar>
    bool operator==(const Scalar other) const;
    template<typename Scalar>
    bool operator!=(const Scalar other) const;
    
    
    template<typename Scalar>
    LinearAnalytic &operator=(const Scalar other);
    template<typename Scalar>
    LinearAnalytic &operator=(const std::initializer_list<Scalar> &coefs);
    template<typename Scalar>
    LinearAnalytic &operator+=(const Scalar other);
    template<typename Scalar>
    LinearAnalytic &operator-=(const Scalar other);
    template<typename Scalar>
    LinearAnalytic &operator*=(const Scalar other);
    template<typename Scalar>
    LinearAnalytic &operator/=(const Scalar other);
    template<typename Scalar>
    LinearAnalytic &operator%=(const Scalar other);
    template<typename Scalar>
    LinearAnalytic operator+(const Scalar other) const;
    template<typename Scalar>
    LinearAnalytic operator-(const Scalar other) const;
    template<typename Scalar>
    LinearAnalytic operator*(const Scalar other) const;
    template<typename Scalar>
    LinearAnalytic operator/(const Scalar other) const;
    template<typename Scalar>
    LinearAnalytic operator%(const Scalar other) const;
    
    uint1 degree() const;
    uint1 size() const;
};


#endif