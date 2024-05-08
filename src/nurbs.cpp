#include <vector>
#include <iostream>
#include "nurbs.hpp"


unsigned short Math::binom(const unsigned short n, const unsigned short i){
    // Functions computes correctly up to n = 17
    unsigned result = 1;
    if(n < 2*i)
        return binom(n, n - i);
    for(unsigned short j = 0; j < i; j++)
        result *= n - j;
    for(unsigned short j = 0; j < i; j++)
        result /= i - j;
    return result;
};


template<typename parameter>
parameter Math::bezier(const parameter u, const unsigned short p, const unsigned short i){
    // Computes bezier B_{i, p} = binom(p, i) * (1-u)^(p-i) * u^i
    const parameter v = 1 - u;
    parameter result = binom(p, i);
    for(unsigned short j=0; j<i; j++)
        result *= u;
    for(unsigned short j=i; j<p; j++)
        result *= v;
    return result;
}


template<typename parameter>
unsigned short find_degree(const std::vector<parameter> &init_vector){
    unsigned short degree = 0;
    for(unsigned short i=1; i<init_vector.size(); i++)
        if(init_vector[i] == init_vector[0])
            degree += 1;
    return degree;
};


template<typename parameter>
unsigned short find_npts(const std::vector<parameter> &init_vector){
    unsigned short degree = find_degree(init_vector);
    return init_vector.size() - degree - 1;
};


template<typename parameter>
const parameter& KnotVector<parameter>::operator[](const unsigned short index) const{
    return this->internal[index];
};


template<typename parameter>
KnotVector<parameter>::KnotVector(const std::vector<parameter> &init_vector) :
    internal(init_vector),
    degree(find_degree(init_vector)),
    npts(find_npts(init_vector)){}


template<typename parameter>
unsigned short KnotVector<parameter>::span(const parameter node){
    unsigned short low, mid, high;
    if(node == internal[npts])
        return npts - 1;
    low = degree;
    high = npts + 1;
    mid = (low + high) / 2;
    while(true){
        if(node < internal[mid])
            high = mid;
        else
            low = mid;
        mid = (low + high) / 2;
        if ((internal[mid] <= node) && (node <= internal[mid+1]))
            return mid;
    }
}


template<typename parameter>
unsigned short KnotVector<parameter>::mult(const parameter node){
    unsigned short i, sum = 0;
    for(i=0; i <= degree + npts; i++)
        if(internal[i] == node)
            sum += 1;
    return sum;
};


template<typename parameter>
KnotVector<parameter> GeneratorKnotVector::bezier(const unsigned short degree){
    const unsigned short size = 2 * degree + 2;
    std::vector<parameter> vect(size);
    for(unsigned short i=0; i<=degree; i++)
        vect[i] = 0;
    for(unsigned short i=degree+1; i<size; i++)
        vect[i] = 1;
    return KnotVector<parameter>(vect);
};


template<typename parameter>
KnotVector<parameter> GeneratorKnotVector::uniform(const unsigned short degree, const unsigned short npts){
    const unsigned short size = degree + npts + 1;
    const unsigned short maxi = npts - degree;
    std::vector<parameter> vect(size);
    for(unsigned short i=0; i<degree; i++)
        vect[i] = 0;
    for(unsigned short i=0; i<maxi; i++)
        vect[degree + i] = (static_cast<parameter>(i))/maxi;
    for(unsigned short i=npts; i<size; i++)
        vect[i] = 1;
    return KnotVector<parameter>(vect);
};


template class KnotVector<double>;
template int Math::bezier<int>(int, unsigned short, unsigned short);
template float Math::bezier<float>(float, unsigned short, unsigned short);
template double Math::bezier<double>(double, unsigned short, unsigned short);
template KnotVector<double> GeneratorKnotVector::bezier<double>(const unsigned short);
template KnotVector<double> GeneratorKnotVector::uniform<double>(const unsigned short, const unsigned short);


std::ostream& operator<<(std::ostream &os, const KnotVector<double>& knotvector){
    const unsigned short size = knotvector.degree + knotvector.npts;
    for(unsigned short i=0; i < size; i++)
        os << knotvector[i] << " ";
    os << knotvector[size];
    return os;
};
