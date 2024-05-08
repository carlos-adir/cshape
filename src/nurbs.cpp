#include <vector>
#include <iostream>
#include "nurbs.hpp"


ushort Math::binom(const ushort n, const ushort i){
    // Functions computes correctly up to n = 17
    unsigned result = 1;
    if(n < 2*i)
        return binom(n, n - i);
    for(ushort j = 0; j < i; j++)
        result *= n - j;
    for(ushort j = 0; j < i; j++)
        result /= i - j;
    return result;
};


template<typename parameter>
parameter Math::bezier(const parameter u, const ushort p, const ushort i){
    // Computes bezier B_{i, p} = binom(p, i) * (1-u)^(p-i) * u^i
    const parameter v = 1 - u;
    parameter result = binom(p, i);
    for(ushort j=0; j<i; j++)
        result *= u;
    for(ushort j=i; j<p; j++)
        result *= v;
    return result;
}


template<typename parameter>
ushort find_degree(const std::vector<parameter> &init_vector){
    ushort degree = 0;
    for(ushort i=1; i<init_vector.size(); i++)
        if(init_vector[i] == init_vector[0])
            degree += 1;
    return degree;
};


template<typename parameter>
ushort find_npts(const std::vector<parameter> &init_vector){
    ushort degree = find_degree(init_vector);
    return init_vector.size() - degree - 1;
};


template<typename parameter>
const parameter& KnotVector<parameter>::operator[](const ushort index) const{
    return this->internal[index];
};


template<typename parameter>
KnotVector<parameter>::KnotVector(const std::vector<parameter> &init_vector) :
    internal(init_vector),
    degree(find_degree(init_vector)),
    npts(find_npts(init_vector)){}


template<typename parameter>
ushort KnotVector<parameter>::span(const parameter node){
    ushort low, mid, high;
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
ushort KnotVector<parameter>::mult(const parameter node){
    ushort i, sum = 0;
    for(i=0; i <= degree + npts; i++)
        if(internal[i] == node)
            sum += 1;
    return sum;
};


template<typename parameter>
KnotVector<parameter> GeneratorKnotVector::bezier(const ushort degree){
    const ushort size = 2 * degree + 2;
    std::vector<parameter> vect(size);
    for(ushort i=0; i<=degree; i++)
        vect[i] = 0;
    for(ushort i=degree+1; i<size; i++)
        vect[i] = 1;
    return KnotVector<parameter>(vect);
};


template<typename parameter>
KnotVector<parameter> GeneratorKnotVector::uniform(const ushort degree, const ushort npts){
    const ushort size = degree + npts + 1;
    const ushort maxi = npts - degree;
    std::vector<parameter> vect(size);
    for(ushort i=0; i<degree; i++)
        vect[i] = 0;
    for(ushort i=0; i<maxi; i++)
        vect[degree + i] = (static_cast<parameter>(i))/maxi;
    for(ushort i=npts; i<size; i++)
        vect[i] = 1;
    return KnotVector<parameter>(vect);
};


template class KnotVector<double>;
template int Math::bezier<int>(int, ushort, ushort);
template float Math::bezier<float>(float, ushort, ushort);
template double Math::bezier<double>(double, ushort, ushort);
template KnotVector<double> GeneratorKnotVector::bezier<double>(const ushort);
template KnotVector<double> GeneratorKnotVector::uniform<double>(const ushort, const ushort);


std::ostream& operator<<(std::ostream &os, const KnotVector<double>& knotvector){
    const ushort size = knotvector.degree + knotvector.npts;
    for(ushort i=0; i < size; i++)
        os << knotvector[i] << " ";
    os << knotvector[size];
    return os;
};
