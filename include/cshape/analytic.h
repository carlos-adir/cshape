#ifndef ANALYTIC_H
#define ANALYTIC_H

#include <vector>
#include <iostream>

typedef unsigned long uint8;
typedef unsigned int uint4;
typedef unsigned short uint2;
typedef unsigned short uint1;

const uint1 MAXSIZE = 100;


template<typename I, typename O>
class IAnalytic{

public:
    // O eval(const I node, const uint1 deriv = 0) const;
    // O operator()(const I node) const {return this->eval(node);};
};

template<typename I, typename O>
class LinearAnalytic : public IAnalytic<I, O>{
private:
    std::vector<O> internal;
    void resize(const uint1 newsize);
    void clean();

public:
    LinearAnalytic(const O constant = 0);
    LinearAnalytic(const std::vector<O> &coefs);
    LinearAnalytic(const std::initializer_list<O> &coefs);

    const O operator[](const uint1 index) const;  // getter
    O &operator[](const uint1 index); // setter
    
    bool operator==(const O other) const;
    bool operator!=(const O other) const;
    bool operator==(const LinearAnalytic<I, O> &other) const;
    bool operator!=(const LinearAnalytic<I, O> &other) const;
    
    LinearAnalytic<I, O> &operator=(const O other);
    LinearAnalytic<I, O> &operator=(const std::initializer_list<O> &coefs);
    LinearAnalytic<I, O> &operator=(const LinearAnalytic<I, O> &other);

    LinearAnalytic<I, O> &operator+=(const O other);
    LinearAnalytic<I, O> &operator-=(const O other);
    LinearAnalytic<I, O> &operator*=(const O other);
    LinearAnalytic<I, O> &operator/=(const O other);
    LinearAnalytic<I, O> &operator%=(const O other);
    LinearAnalytic<I, O> operator+(const O other) const;
    LinearAnalytic<I, O> operator-(const O other) const;
    LinearAnalytic<I, O> operator*(const O other) const;
    LinearAnalytic<I, O> operator/(const O other) const;
    LinearAnalytic<I, O> operator%(const O other) const;
    LinearAnalytic<I, O> operator-() const;

    
    LinearAnalytic<I, O> &operator+=(const LinearAnalytic<I, O> &other);
    LinearAnalytic<I, O> &operator-=(const LinearAnalytic<I, O> &other);
    LinearAnalytic<I, O> operator+(const LinearAnalytic<I, O> &other) const;
    LinearAnalytic<I, O> operator-(const LinearAnalytic<I, O> &other) const;
    
    uint1 degree() const;

    // template<typename I, typename O>
    // friend std::ostream &operator<<(std::ostream &os, const LinearAnalytic<I, O> &poly);
    friend LinearAnalytic<I, O> operator+(const O constant, const LinearAnalytic<I, O> &other) {return other + constant;};
    friend LinearAnalytic<I, O> operator-(const O constant, const LinearAnalytic<I, O> &other) {return (-other) + constant;};
    friend LinearAnalytic<I, O> operator*(const O constant, const LinearAnalytic<I, O> &other) {return other * constant;};
    // template<typename I, typename O>
    // friend LinearAnalytic<I, O> operator-(const O constant, const LinearAnalytic<I, O> &other);
    // template<typename I, typename O>
    // friend LinearAnalytic<I, O> operator*(const O constant, const LinearAnalytic<I, O> &other);
};


// template<typename I, typename O>
// std::ostream &operator<<(std::ostream &os, const LinearAnalytic<I, O> &poly);
// template<typename I, typename O>
// LinearAnalytic<I, O> operator+(const O constant, const LinearAnalytic<I, O> &other);
// template<typename I, typename O>
// LinearAnalytic<I, O> operator-(const O constant, const LinearAnalytic<I, O> &other);
// template<typename I, typename O>
// LinearAnalytic<I, O> operator*(const O constant, const LinearAnalytic<I, O> &other);


template class IAnalytic<int, int>;
template class IAnalytic<int, float>;
template class IAnalytic<int, double>;
template class IAnalytic<float, float>;
template class IAnalytic<float, double>;
template class IAnalytic<double, float>;
template class IAnalytic<double, double>;
template class LinearAnalytic<int, int>;
template class LinearAnalytic<int, float>;
template class LinearAnalytic<int, double>;
template class LinearAnalytic<float, float>;
template class LinearAnalytic<float, double>;
template class LinearAnalytic<double, float>;
template class LinearAnalytic<double, double>;

// template LinearAnalytic<int, int> operator+(const int constant, const LinearAnalytic<int, int> &other);
// template LinearAnalytic<int, int> operator-(const int constant, const LinearAnalytic<int, int> &other);
// template LinearAnalytic<int, int> operator*(const int constant, const LinearAnalytic<int, int> &other);



#endif