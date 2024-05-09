#include "math.hpp"

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