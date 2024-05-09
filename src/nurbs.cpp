#include <vector>
#include <iostream>
#include <stdexcept>
#include "nurbs.hpp"

typedef double parameter;
typedef unsigned short ushort;




ushort find_degree(const std::vector<parameter> &init_vector){
    ushort degree = 0;
    for(ushort i=1; i<init_vector.size(); i++)
        if(init_vector[i] == init_vector[0])
            degree += 1;
    return degree;
};


ushort find_npts(const std::vector<parameter> &init_vector){
    ushort degree = find_degree(init_vector);
    return init_vector.size() - degree - 1;
};


std::vector<parameter> find_knots(const std::vector<parameter> &init_vector){
    std::vector<parameter> knots;
    const ushort degree = find_degree(init_vector);
    const ushort npts = find_npts(init_vector);
    knots.push_back(init_vector[degree]);
    for(ushort i=degree; i<=npts; i++)
        if(knots[knots.size()-1] != init_vector[i])
            knots.push_back(init_vector[i]);
    return knots;
}


std::vector<parameter> find_spans(const std::vector<parameter> &init_vector){
    std::vector<parameter> spans;
    const ushort degree = find_degree(init_vector);
    const ushort npts = find_npts(init_vector);
    for(ushort i=degree; i<=npts; i++)
        if(init_vector[i] != init_vector[i+1])
            spans.push_back(i);
    return spans;
}


unsigned multiply(const std::vector<ushort> terms){
    unsigned prod = 1;
    for(ushort term : terms)
        prod *= term;
    return prod;
}


template <typename T>
Array<T>::Array(const std::vector<ushort> inshape) :
    data(multiply(inshape)),
    ndim(inshape.size()),
    shape(inshape) {};


template <typename T>
T& Array<T>::operator[](const std::vector<ushort> indexs) {
    unsigned index = 0;
    for(unsigned short i=0; i < this->ndim; i++){
        index *= this->shape[i];
        if(indexs[i] >= this->shape[i]){
            std::cout << "received indexs [";
            for(unsigned j=0; j <indexs.size(); j++)
                std::cout << indexs[j] << " ";
            std::cout << "], but shape is ";
            
            for(unsigned j=0; j <this->shape.size(); j++)
                std::cout << this->shape[j] << " ";
            std::cout << std::endl;
            throw std::invalid_argument("Invalid argument passed to function");
        }
        index += indexs[i] % this->shape[i];
    }
    return this->data[index];
};


template <typename T>
const T& Array<T>::operator[](const std::vector<ushort> indexs) const {
    unsigned index = 0;
    for(unsigned short i=0; i < this->ndim; i++){
        index *= this->shape[i];
        index += indexs[i] % this->shape[i];
    }
    return this->data[index];
};



const parameter& KnotVector::operator[](const ushort index) const{
    return this->internal[index];
};


KnotVector::KnotVector(const std::vector<parameter> &init_vector) :
    internal(init_vector),
    degree(find_degree(init_vector)),
    npts(find_npts(init_vector)),
    knots(find_knots(init_vector)),
    spans(find_spans(init_vector)){};


ushort KnotVector::span(const parameter &node) const{
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


ushort KnotVector::mult(const parameter &node) const{
    ushort i, sum = 0;
    for(i=0; i <= degree + npts; i++)
        if(internal[i] == node)
            sum += 1;
    return sum;
};


KnotVector GeneratorKnotVector::bezier(const ushort degree){
    const ushort size = 2 * degree + 2;
    std::vector<parameter> vect(size);
    for(ushort i=0; i<=degree; i++)
        vect[i] = 0;
    for(ushort i=degree+1; i<size; i++)
        vect[i] = 1;
    return KnotVector(vect);
};


KnotVector GeneratorKnotVector::uniform(const ushort degree, const ushort npts){
    const ushort size = degree + npts + 1;
    const ushort maxi = npts - degree;
    std::vector<parameter> vect(size);
    for(ushort i=0; i<degree; i++)
        vect[i] = 0;
    for(ushort i=0; i<maxi; i++)
        vect[degree + i] = (static_cast<parameter>(i))/maxi;
    for(ushort i=npts; i<size; i++)
        vect[i] = 1;
    return KnotVector(vect);
};


std::ostream& operator<<(std::ostream &os, const KnotVector& knotvector){
    const ushort size = knotvector.degree + knotvector.npts;
    for(ushort i=0; i < size; i++)
        os << knotvector[i] << " ";
    os << knotvector[size];
    return os;
};


Array<parameter> compute_spectre(const KnotVector &knotvector, const ushort reqdegree){
    /*
    Given a knotvector, it has properties like
        - number of points: npts
        - polynomial degree: degree
        - knots: A list of non-repeted knots
        - spans: The span of each knot
    This function returns a matrix of size
        (m) x (j+1) x (j+1)
    which
        - m is the number of segments: len(knots)-1
        - j is the requested degree

    The given matrix is the coefficients to evaluate a spline
    for the given vector.

    More definitions:
    knotvector = [u_0, u_1, ..., u_p, ..., u_n, ..., u_m] with (m = n+p)
    knots = [U_0, U_1, ..., U_m]

    Return
    -------------------
    We want to evaluate all the functions N_{i,j}(w).
    The node (w) is in the interval [U_z, U_{z+1}] -> U_{z} <= w <= U_{z+1}
    We would require a matrix (m, n, j+1) to everything,
        but in the interval [U_z, U_{z+1}], only (j+1) functions are not zero:
        meaning [N_{z-j,j}, ..., N_{z,j}]
    Therefore, we return a matrix of shape (m, j+1, j+1)

    The value M[z, y, k] = h, means,
        the node (w) is in the interval [U_{z}, U_{z+1}]
        the node (w) has span (s), meaning (U_{z} = u_{s}), (U_{z+1} = u_{s+1})
        it's requested the function N_{i,j}(w), with
            y = 0 -> i = 
            y = j -> i =
        the node (w) is transformed to (v = (w - U_{z})/(U_{z+1} - U_{z}))
            w = U_{z} -> v = 0
            w = U_{z+1} -> v = 1
        the value is computed with
            N_{i,j}(w) = M[z, y, j] * v^j + ... + M[z, y, 1] * v + M[z, y, 0]
    
    Example
    -------------------

    Suppose the knots are: [0, 1, 2, 3]
    Therefore there are 3 intervals: [0, 1], [1, 2], [2, 3]
    Then, the matrix3D will have 3 matrix2D of shape (j+1, j+1).
    Therefore, if we want to evaluate the node 2.5, which is
    inside the interval [1, 2], we will only need of the second
    matrix, of index z=1.

    As it's objective to evaluate (npts) functions at node (w),
    we would require a matrix2D of shape (npts, j+1).
    But from these (npts) basis functions, in the interval
    [u_i, u_{i+1}] only (j+1) are not zero, meaning

    */
    const ushort m = knotvector.knots.size() - 1;
    const ushort j = reqdegree;
    const ushort n = reqdegree + 1;
    const std::vector<ushort> shape = {m, n, n};
    Array<parameter> spectre(shape);
    if(n == 1){  // Req degree = 0
        for(ushort k=0; k<m; k++)
            for(ushort i=0; i<n; i++)
                for(ushort j=0; j<n; j++)
                    spectre[{k, i, j}] = 1;
        return spectre;
    }

    Array<parameter> spectre0 = compute_spectre(knotvector, reqdegree - 1);
    for(ushort z=0; z < m; z++){
        const parameter u0 = knotvector.knots[z];
        const parameter u1 = knotvector.knots[z + 1];
        const parameter s0 = knotvector.spans[z];
        for(ushort y=0; y < j; y++){
            const ushort i = y + s0 - j + 1;
            const parameter a0 = u0 - knotvector[i];
            const parameter a1 = u1 - u0;
            const parameter b0 = knotvector[i + j] - u0;
            const parameter b1 = u0 - u1;
            const parameter over_denom = 1/(knotvector[i + j] - knotvector[i]);
            for(ushort k = 0; k < j; k++)
                spectre0[{z, y, k}] *= over_denom;
            for(ushort k = 0; k < j; k++){
                const ushort y1 = y + 1;
                const ushort k1 = k + 1;
                spectre[{z, y, k}] += b0 * spectre0[{z, y, k}];
                spectre[{z, y, k1}] += b1 * spectre0[{z, y, k}];
                spectre[{z, y1, k}] += a0 * spectre0[{z, y, k}];
                spectre[{z, y1, k1}] += a1 * spectre0[{z, y, k}];
            }
        }
    }
    return spectre;
}


Basis::Basis(const KnotVector &knotvector) :
    knotvector(knotvector),
    spectre(compute_spectre(knotvector, knotvector.degree)){};


parameter Basis::operator()(parameter node, const ushort index) const{
    const ushort span = knotvector.span(node);
    const ushort func_index = index + knotvector.degree - span;

    if(knotvector.degree < func_index)
        return 0;

    node -= knotvector[span];
    node /= knotvector[span + 1] - knotvector[span];
    
    ushort span_index = 0; 
    while(knotvector.spans[span_index] != span)
        span_index++;
    
    parameter result = 0;
    for(ushort k=knotvector.degree; k<=knotvector.degree; k--){
        result *= node;
        result += spectre[{span_index, func_index, k}];
    }
    return result;
};


void Basis::evaluate(parameter node, std::vector<parameter> output) const{
    if(output.size() != knotvector.npts)
        throw std::invalid_argument("Given results vector lenght is invalid");
    for(ushort index = 0; index < knotvector.npts; index++)
        output[index] = 0; // Clean output vector
    
    const ushort span = knotvector.span(node);
    node -= knotvector[span];
    node /= knotvector[span + 1] - knotvector[span];

    ushort span_index = 0; 
    while(knotvector.spans[span_index] != span)
        span_index++;
    ushort func_index = 0;
    for(ushort index = span - knotvector.degree; index <= span; index++){
        for(ushort k=knotvector.degree; k<=knotvector.degree; k--){
            output[index] *= node;
            output[index] += spectre[{span_index, func_index, k}];
        }
        func_index++;
    }
};


template class Array<parameter>;
