#include <iostream>
#include <stdexcept>
#include <vector>

#include "cshape/analytic.h"

template <typename I, typename O>
LinearAnalytic<I, O>::LinearAnalytic(const O constant) {
    this->internal.clear();
    this->internal.push_back(constant);
};

template <typename I, typename O>
LinearAnalytic<I, O>::LinearAnalytic(const std::vector<O> &coefs) {
    const uint1 size = coefs.size();
    this->resize(size > 0 ? size : 1);
    for (uint1 i = 0; i < size; i++) this->internal[i] = coefs[i];
    this->clean();
};

template <typename I, typename O>
LinearAnalytic<I, O>::LinearAnalytic(const std::initializer_list<O> &coefs) {
    const uint1 csize = coefs.size();
    uint1 i = 0;
    this->resize(csize > 0 ? csize : 1);
    for (const O &coef : coefs) {
        this->internal[i] = coef;
        i++;
    }
    this->clean();
};

template <typename I, typename O>
LinearAnalytic<I, O>::LinearAnalytic(const LinearAnalytic<I, O> &other) {
    const uint1 osize = other.internal.size();
    this->resize(osize);
    for (uint1 i = 0; i < osize; i++) this->internal[i] = other.internal[i];
    this->clean();
};

template <typename I, typename O>
void LinearAnalytic<I, O>::resize(const uint1 newsize) {
    const uint1 oldsize = this->internal.size();
    if (!newsize)
        throw std::invalid_argument(
            "Received size = 0 inside resize, at least 1 required");
    if (newsize > MAXSIZE)
        throw std::invalid_argument("Received size > MAXSIZE");
    this->internal.resize(newsize);
    if (oldsize < newsize)
        for (uint1 i = oldsize; i < newsize; i++) this->internal[i] = 0;
};

template <typename I, typename O>
void LinearAnalytic<I, O>::clean() {
    const uint1 degree = this->degree();
    if (degree + 1 != this->internal.size()) this->resize(degree + 1);
};

template <typename I, typename O>
uint1 LinearAnalytic<I, O>::degree() const {
    uint1 degree = this->internal.size() - 1;
    while (degree && !this->internal[degree]) degree--;
    return degree;
};

//
//
//
// COMPARING
//
//
//

template <typename I, typename O>
bool LinearAnalytic<I, O>::operator==(const O other) const {
    return this->internal.size() == 1 && this->internal[0] == other;
};

template <typename I, typename O>
bool LinearAnalytic<I, O>::operator!=(const O other) const {
    return this->internal.size() != 1 || this->internal[0] != other;
};

template <typename I, typename O>
bool LinearAnalytic<I, O>::operator==(const LinearAnalytic<I, O> &other) const {
    if (this->degree() != other.degree()) return false;
    for (uint1 i = 0; i <= this->degree(); i++)
        if (this->internal[i] != other.internal[i]) return false;
    return true;
};

template <typename I, typename O>
bool LinearAnalytic<I, O>::operator!=(const LinearAnalytic<I, O> &other) const {
    return !((*this) == other);
};

//
//
//
//   SETTER
//
//
//

template <typename I, typename O>
LinearAnalytic<I, O> &LinearAnalytic<I, O>::operator=(const O other) {
    this->internal.clear();
    this->internal.push_back(other);
    return *this;
};

template <typename I, typename O>
LinearAnalytic<I, O> &LinearAnalytic<I, O>::operator=(
    const std::vector<O> &coefs) {
    const uint1 csize = coefs.size();
    this->resize(csize > 0 ? csize : 1);
    for (uint1 i = 0; i < csize; i++) this->internal[i] = coefs[i];
    this->clean();
    return *this;
};

template <typename I, typename O>
LinearAnalytic<I, O> &LinearAnalytic<I, O>::operator=(
    const std::initializer_list<O> &coefs) {
    const uint1 csize = coefs.size();
    uint1 i = 0;
    this->resize(csize > 0 ? csize : 1);
    for (const O &coef : coefs) this->internal[i++] = coef;
    this->clean();
    return *this;
};

template <typename I, typename O>
LinearAnalytic<I, O> &LinearAnalytic<I, O>::operator=(
    const LinearAnalytic<I, O> &other) {
    const uint1 degree = other.degree();
    this->resize(degree + 1);
    for (uint1 i = 0; i <= degree; i++) this->internal[i] = other.internal[i];
    this->clean();
    return *this;
};

//
//
//   OPERATIONS WITH SCALAR
//   TO CHANGE ACUTAL STATE
//
//

template <typename I, typename O>
LinearAnalytic<I, O> &LinearAnalytic<I, O>::operator+=(const O other) {
    this->internal[0] += other;
    return *this;
};

template <typename I, typename O>
LinearAnalytic<I, O> &LinearAnalytic<I, O>::operator-=(const O other) {
    this->internal[0] -= other;
    return *this;
};

template <typename I, typename O>
LinearAnalytic<I, O> &LinearAnalytic<I, O>::operator*=(const O other) {
    for (uint1 i = 0; i < this->internal.size(); i++)
        this->internal[i] *= other;
    return *this;
};

template <typename I, typename O>
LinearAnalytic<I, O> &LinearAnalytic<I, O>::operator/=(const O other) {
    if (other == 0)
        throw std::invalid_argument("Math error: Attempted to divide by zero");
    for (uint1 i = 0; i < this->internal.size(); i++)
        this->internal[i] /= other;
    return *this;
};

template <typename I, typename O>
LinearAnalytic<I, O> &LinearAnalytic<I, O>::operator%=(const O other) {
    if (other == 0)
        throw std::invalid_argument("Math error: Attempted to divide by zero");
    this->resize(1);
    this->internal[0] = 0;
    return *this;
};

//
//
//   OPERATIONS WITH SCALAR
//   TO CREATE A NEW COPY
//
//

//
//
//
//
//
//

template <typename I, typename O>
LinearAnalytic<I, O> &LinearAnalytic<I, O>::operator+=(
    const LinearAnalytic<I, O> &other) {
    const uint1 tdegree = this->degree();
    const uint1 odegree = other.degree();
    if (odegree > tdegree) this->resize(odegree);
    for (uint1 i = 0; i <= odegree; i++) this->internal[i] += other.internal[i];
    return *this;
};
template <typename I, typename O>
LinearAnalytic<I, O> &LinearAnalytic<I, O>::operator-=(
    const LinearAnalytic<I, O> &other) {
    const uint1 tdegree = this->degree();
    const uint1 odegree = other.degree();
    if (odegree > tdegree) this->resize(odegree);
    for (uint1 i = 0; i <= odegree; i++) this->internal[i] -= other.internal[i];
    return *this;
};

//
//
//
//   GETTER AND SETTER OF INTERNAL VECTOR
//
//
//

template <typename I, typename O>
O &LinearAnalytic<I, O>::operator[](const uint1 index) {
    if (this->internal.size() <= index) this->resize(index + 1);
    return this->internal[index];
};

template <typename I, typename O>
const O LinearAnalytic<I, O>::operator[](const uint1 index) const {
    return (index < this->internal.size()) ? (this->internal[index]) : 0;
};

//
//
//
//
//
//
//

template <typename I, typename O>
std::ostream &operator<<(std::ostream &os, const LinearAnalytic<I, O> &poly) {
    const uint1 degree = poly.degree();
    os << "LinearAnalytic[";
    for (uint1 i = 0; i < degree; i++) os << poly[i] << ", ";
    os << poly[degree] << "]";
    return os;
};
