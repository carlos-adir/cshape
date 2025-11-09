#ifndef SCALAR_H
#define SCALAR_H
#include <iostream>
#include <limits>

typedef double scalar;

static const scalar NEGINF = -std::numeric_limits<scalar>::infinity();

static const scalar POSINF = std::numeric_limits<scalar>::infinity();


scalar string_to_scalar(const std::string &str);

#endif
