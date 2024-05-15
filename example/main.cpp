#include <iostream>

#include "cshape/nurbs.h"

int main(){
    KnotVector knotvector = GeneratorKnotVector::uniform(2, 7);
    std::cout << knotvector << std::endl;
    return 0;
}