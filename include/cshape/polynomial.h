
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "parameter.h"
#include "coordinate.h"
#include "analytic.h"
#include <vector>


class Polynomial : public LinearAnalytic{

public:

    Polynomial();
    template<typename Scalar>
    Polynomial(const Scalar value);
    template<typename Scalar>
    Polynomial(const std::vector<Scalar> &coefs);
    template<typename Scalar>
    Polynomial(const std::initializer_list<Scalar> &coefs);


    bool operator==(Polynomial const &other) const;
    bool operator!=(Polynomial const &other) const;
    Polynomial &operator=(Polynomial const &other);
    Polynomial &operator+=(Polynomial const &other);
    Polynomial &operator-=(Polynomial const &other);
    Polynomial &operator*=(Polynomial const &other);
    Polynomial &operator/=(Polynomial const &other);
    Polynomial &operator%=(Polynomial const &other);
    Polynomial operator+(Polynomial const &other) const;
    Polynomial operator-(Polynomial const &other) const;
    Polynomial operator*(Polynomial const &other) const;
    Polynomial operator/(Polynomial const &other) const;
    Polynomial operator%(Polynomial const &other) const;

    friend std::ostream &operator<<(std::ostream &os, const Polynomial &poly);
    template<typename Scalar>
    Coordinate eval(const Scalar node, const uint1 deriv = 0) const;
//     Coordinate defintegral(const Parameter nodea, const Parameter nodeb) const;
//     Polynomial derivate(const uint1 times = 1) const;
//     Polynomial shift(const Parameter amount) const;
//     Polynomial scale(const Parameter amount) const;
};

#endif