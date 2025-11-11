#ifndef SCALAR_H
#define SCALAR_H
#include <iostream>
#include <limits>
#include <cmath>

typedef double Scalar;

static const Scalar NEGINF = -std::numeric_limits<Scalar>::infinity();

static const Scalar POSINF = std::numeric_limits<Scalar>::infinity();

const static Scalar TAU = 2 * M_PIf64;

enum class DIRECTION { XP, YP, XN, YN};

class Angle
{
    private:
        const DIRECTION direction;  // store 0, 1, 2 or 3
        const Scalar amount;  // value between [-0.125, 0.125]
        Angle(const DIRECTION direction, const Scalar &turns): direction(direction), amount(turns) {};
    public:
        static Angle turns(const Scalar& value);
        static Angle degrees(const Scalar& value);
        static Angle degrees(const int value);
        static Angle radians(const Scalar& value);
        Scalar cos() const;
        Scalar sin() const;
        Scalar turns() const;
        Scalar degrees() const;
        Scalar radians() const;

        bool operator==(const Angle& other) const {return this->direction == other.direction && this->amount == other.amount;};
        bool operator!=(const Angle& other) const {return !this->operator==(other);};

        operator std::string() const;
        friend std::ostream &operator<<(std::ostream &os, const Angle &obj);
};


Scalar string_to_scalar(const std::string &str);

#endif
