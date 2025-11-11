
#include "cshape/scalar.h"

Scalar string_to_scalar(const std::string &str){
    return atof(str.c_str());
}

Angle Angle::turns(const Scalar& value)
{
    const Scalar temp = fmod(value, 1);
    const Scalar newv = (temp <= 0.5) ? temp : (temp - 1);
    if (newv > 0.375)
        return Angle(DIRECTION::XN, newv - 0.5);
    if (newv < -0.375)
        return Angle(DIRECTION::XN, newv + 0.5);
    if (newv > 0.125)
        return Angle(DIRECTION::YP, newv - 0.25);
    if (newv < -0.125)
        return Angle(DIRECTION::YN, newv + 0.25);
    return Angle(DIRECTION::XP, newv);
}
Angle Angle::degrees(const int value)
{
    const short int temp = value % 360;
    return Angle::turns(Scalar((temp <= 180) ? temp : (temp - 360)) / 360);
}
Angle Angle::degrees(const Scalar& value)
{
    const Scalar temp = fmod(value, 360);
    return Angle::turns(((temp <= 180) ? temp : (temp - 360)) / 360);
}
Angle Angle::radians(const Scalar& value)
{
    const Scalar temp = fmod(value, TAU);
    return Angle::turns(((temp <= TAU / 2) ? temp : (temp - TAU)) / TAU);
}
Scalar Angle::cos() const
{
    switch (direction)
    {
        case DIRECTION::XP:
            return cosf64(TAU * amount);
        case DIRECTION::XN:
            return -cosf64(TAU * amount);
        case DIRECTION::YN:
            return sinf64(TAU * amount);
        case DIRECTION::YP:
            return -sinf64(TAU * amount);
        default:
            throw std::invalid_argument("Not expected");
    }
}
Scalar Angle::sin() const
{
    switch (direction)
    {
        case DIRECTION::XP:
            return sinf64(TAU * amount);
        case DIRECTION::XN:
            return -sinf64(TAU * amount);
        case DIRECTION::YN:
            return -cosf64(TAU * amount);
        case DIRECTION::YP:
            return cosf64(TAU * amount);
        default:
            throw std::invalid_argument("Not expected");
    }
}

Scalar Angle::turns() const
{
    switch (direction)
    {
        case DIRECTION::XP:
            return this->amount;
        case DIRECTION::YP:
            return this->amount + 0.25;
        case DIRECTION::YN:
            return this->amount - 0.25;
        case DIRECTION::XN:
            return amount + (amount <= 0 ? 0.5 : -0.5);
        default:
            throw std::invalid_argument("Not expected");
    }
}


Scalar Angle::degrees() const
{
    return 360 * turns();
}


Scalar Angle::radians() const
{
    return TAU * turns();
}


std::ostream &operator<<(std::ostream &os, const Angle &obj)
{
    const Scalar degrees = obj.degrees();
    os << (degrees >= 0 ? degrees : (360 + degrees));
    return os;
}

