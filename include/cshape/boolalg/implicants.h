#ifndef BOOLALG_IMPLICANT_H
#define BOOLALG_IMPLICANT_H

#include "binary.h"
#include "types.h"
#include <stdexcept>
#include <ostream>
#include <cstdint>
#include <array>
#include <memory>
#include <cstring>

struct Implicant
{
    const Binary number;
    const Binary notcare;
    
    Implicant(const Binary number) : number(number), notcare(Binary(false, number.nbits)) {};
    Implicant(const Binary number, const Binary notcare) : number(number), notcare(notcare) {};
};

std::ostream &operator<<(std::ostream &os, const Implicant &obj);
void merge(std::vector<Implicant>& implicants);



template<typename V>
struct Implicants
{
    const std::vector<std::shared_ptr<V>> variables;
    std::vector<Implicant> implicants;

    Implicants<V> operator|(const Implicants<V>& other) const;
    Implicants<V> operator&(const Implicants<V>& other) const;
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const Implicants<T> &obj);

#endif
