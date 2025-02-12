#ifndef ANALYTIC_H
#define ANALYTIC_H

#include <iostream>
#include <vector>

typedef unsigned long uint8;
typedef unsigned int uint4;
typedef unsigned short uint2;
typedef unsigned short uint1;

const uint1 MAXSIZE = 100;

template <typename I, typename O>
class IAnalytic {
   public:
    O eval(const I node, const uint1 deriv = 0) const;
};

template <typename I, typename O>
class LinearAnalytic : public IAnalytic<I, O> {
   protected:
    std::vector<O> internal;
    void resize(const uint1 newsize);
    void clean();

   public:
    explicit LinearAnalytic(const O constant = 0);
    LinearAnalytic(const std::vector<O> &coefs);
    LinearAnalytic(const std::initializer_list<O> &coefs);
    LinearAnalytic(const LinearAnalytic<I, O> &other);

    virtual const O operator[](const uint1 index) const final;  // getter
    virtual O &operator[](const uint1 index) final;             // setter

    virtual bool operator==(const O other) const final;
    virtual bool operator!=(const O other) const final;
    virtual bool operator==(const LinearAnalytic<I, O> &other) const final;
    virtual bool operator!=(const LinearAnalytic<I, O> &other) const final;

    virtual LinearAnalytic<I, O> &operator=(const O other) final;
    virtual LinearAnalytic<I, O> &operator=(const std::vector<O> &coefs) final;
    virtual LinearAnalytic<I, O> &operator=(
        const std::initializer_list<O> &coefs) final;

    virtual LinearAnalytic<I, O> &operator+=(const O other) final;
    virtual LinearAnalytic<I, O> &operator-=(const O other) final;
    virtual LinearAnalytic<I, O> &operator*=(const O other) final;
    virtual LinearAnalytic<I, O> &operator/=(const O other) final;
    virtual LinearAnalytic<I, O> &operator%=(const O other) final;

    virtual LinearAnalytic<I, O> &operator=(
        const LinearAnalytic<I, O> &other) final;
    virtual LinearAnalytic<I, O> &operator+=(
        const LinearAnalytic<I, O> &other) final;
    virtual LinearAnalytic<I, O> &operator-=(
        const LinearAnalytic<I, O> &other) final;

    uint1 degree() const;
};

template <typename I, typename O>
std::ostream &operator<<(std::ostream &os, const LinearAnalytic<I, O> &poly);

template class IAnalytic<int, int>;
template class LinearAnalytic<int, int>;

#endif