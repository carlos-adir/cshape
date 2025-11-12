#include <iostream>
#include <stdexcept>
#include <vector>

#include "cshape/loggers.h"
#include "cshape/analytic.h"

const static Logger& logger = Logger::getInstance("cshape.analytic");

template <typename O>
uint1 find_degree(const std::vector<O> &coefs)
{
    logger << "Find degree of vector of size: " << coefs.size() << ENDL;
    if (coefs.size() == 0)
        return 0;
    for (const O& coef : coefs)
        logger << coef << ENDL;
    for (uint1 i = coefs.size()-1; i>0; --i)
        if (coefs[i])
        {
            logger << "    found " << i << ENDL;
            return i;
        }
    logger << "    found #0" << ENDL;
    return 0;
}

template <typename O>
const std::vector<O> clean_polynomial(const std::vector<O> &coefs)
{
    if (coefs.size() == 0)
        return {O(0)};
    return std::vector<O>(coefs.begin(), coefs.begin() + find_degree<O>(coefs) + 1);
}

//
//
//
//  CONSTRUCTORS
//
//
//

template <typename I, typename O>
Polynomial<I, O>::Polynomial (const O constant) : degree(0), coefficients ({constant}){};

template <typename I, typename O>
Polynomial<I, O>::Polynomial (const std::vector<O> &coefs) : degree(find_degree<O>(coefs)), coefficients(clean_polynomial<O>(coefs)) {};

template <typename I, typename O>
Polynomial<I, O>::Polynomial (const std::initializer_list<O> &coefs) : degree(find_degree<O>(coefs)), coefficients(clean_polynomial<O>(coefs)) {};

template <typename I, typename O>
Polynomial<I, O>::Polynomial (const Polynomial &other) : degree(other.degree), coefficients(other.coefficients) {};

template <typename I, typename O>
std::unique_ptr<IAnalytic<I, O>> Polynomial<I, O>::clone () const
{
    return std::unique_ptr<IAnalytic<I, O>>(new Polynomial<I, O>(*this));
}

//
//
//
//   OPERATORS
//
//
//

template <typename I, typename O>
bool Polynomial<I, O>::operator== (const O& other) const
{
    return degree == 0 && coefficients[0] == other;
};

template <typename I, typename O>
bool Polynomial<I, O>::operator== (const Polynomial<I, O>& other) const
{
    if (degree != other.degree)
        return false;
    for (uint1 i = 0; i <= degree; ++i)
        if (coefficients[i] != other.coefficients[i])
            return false;
    return true;
};


template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator- () const
{
    std::vector<O> newvec (this->coefficients);
    for (size_t i = 0; i < newvec.size(); ++i)
        newvec[i] = -newvec[i];
    return Polynomial<I, O>(newvec);
};


template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator+ (const O& other) const
{
    std::vector<O> newvec (this->coefficients);
    newvec[0] += other;
    return Polynomial<I, O>(newvec);
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator- (const O& other) const
{
    std::vector<O> newvec (this->coefficients);
    newvec[0] -= other;
    return Polynomial<I, O>(newvec);
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator* (const O& other) const
{
    std::vector<O> newvec (this->coefficients);
    for (size_t i = 0; i < newvec.size(); ++i)
        newvec[i] *= other;
    return Polynomial<I, O>(newvec);
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator/ (const O& other) const
{
    if (other == 0)
        throw std::invalid_argument ("Math error: Attempted to divide by zero");
    std::vector<O> newvec (this->coefficients);
    for (size_t i = 0; i < newvec.size(); ++i)
        newvec[i] /= other;
    return Polynomial<I, O>(newvec);
};
template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator% (const O& other) const
{
    if (other == 0)
        throw std::invalid_argument ("Math error: Attempted to divide by zero");
    return Polynomial<I, O> (0);
};


template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator+ (const Polynomial<I, O> &other) const
{
    std::vector<O> newcoefs ((this->degree > other.degree ? this->degree : other.degree) + 1);
    for (uint1 i = 0; i <= this->degree; i++)
        newcoefs[i] += this->coefficients[i];
    for (uint1 i = 0; i <= other.degree; i++)
        newcoefs[i] += other.coefficients[i];
    return Polynomial<I, O>(newcoefs);
};
template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator- (const Polynomial<I, O> &other) const
{
    std::vector<O> newcoefs ((this->degree > other.degree ? this->degree : other.degree) + 1);
    for (uint1 i = 0; i <= this->degree; i++)
        newcoefs[i] += this->coefficients[i];
    for (uint1 i = 0; i <= other.degree; i++)
        newcoefs[i] -= other.coefficients[i];
    return Polynomial<I, O>(newcoefs);
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator* (const Polynomial<I, O> &other) const
{
    std::vector<O> newcoefs (this->degree + other.degree + 1);
    for (uint1 i = 0; i <= this->degree; i++)
        for (uint1 j = 0; j <= other.degree; j++)
            newcoefs[i + j] += this->coefficients[i] * other.coefficients[j];
    return Polynomial<I, O>(newcoefs);
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator/ (const Polynomial<I, O> &other) const
{
    if (other.degree == 0)
        return *this / other.coefficients[0];
    if (this->degree < other.degree)
        return Polynomial<I, O>(O(0));
    std::vector<O> residual (this->coefficients);
    std::vector<O> quotpoly (1 + this->degree - other.degree);
    for (uint1 i = 0; i < quotpoly.size(); i++)
        quotpoly[i] = 0;
    for (uint1 r = this->degree; r >= other.degree; r--)
    {
        const O ratio = residual[r] / other.coefficients[other.degree];
        quotpoly[r - other.degree] = ratio;
        residual[r] = 0;
        for (uint1 i = 0; i < other.degree; i++)
            residual[i + r - other.degree] -= ratio * other.coefficients[i];
    }
    return quotpoly;
};

template <typename I, typename O>
Polynomial<I, O>
Polynomial<I, O>::operator% (const Polynomial<I, O> &other) const
{
    if (other.degree == 0)
        return Polynomial<I, O>(O(0));
    if (this->degree < other.degree)
        return *this;
    std::vector<O> residual (this->coefficients); // copy coefs
    for (uint1 r = residual.size()-1; r >= other.degree; r--)
    {
        const O ratio = residual[r] / other.coefficients[other.degree];
        residual[r] = 0;
        for (uint1 i = 0; i < other.degree; i++)
            residual[i + r - other.degree] -= ratio * other.coefficients[i];
    }
    return residual;
};


//
//
//
//   EVALUATE FUNCTION
//
//
//

template <typename I, typename O>
O Polynomial<I, O>::eval(const I node, const uint1 deriv) const
{
    if (deriv > degree)
        return 0;
    O result = 0;
    uint4 deriv_coef;
    for (uint1 i = degree; i > deriv; i--)
        {
            result *= node;
            deriv_coef = 1;
            for (uint1 j = 0; j < deriv; j++)
                deriv_coef *= i - j;
            result += deriv_coef * coefficients[i];
        }
    result *= node;
    deriv_coef = 1;
    for (uint1 j = 0; j < deriv; j++)
        deriv_coef *= deriv - j;
    result += deriv_coef * coefficients[deriv];
    return result;
};



//
//
//
//   INVERTED OPERATIONS
//
//
//

/*
template <typename I, typename O>
inline Polynomial<I, O>
operator+ (const O& scalar, const Polynomial<I, O> &poly)
{
    return poly + scalar;
};
template <typename I, typename O>
inline Polynomial<I, O>
operator- (const O& scalar, const Polynomial<I, O> &poly)
{
    return (-poly) + scalar;
};
template <typename I, typename O>
inline Polynomial<I, O>
operator* (const O& scalar, const Polynomial<I, O> &poly)
{
    return poly * scalar;
};

*/