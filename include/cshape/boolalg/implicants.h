#pragma once
#include "types.h"
#include <stdexcept>
#include <ostream>

typedef unsigned char binary;

const unsigned char nbits = 8 * sizeof(binary);

struct Implicant
{
    const binary number;
    const binary notcare;
    Implicant(const binary number) : number(number), notcare(0) {};
    Implicant(const binary number, const binary notcare) : number(number), notcare(notcare) {};
};



std::ostream &operator<<(std::ostream &os, const Implicant &obj)
{
    binary bit = 1u;
    for (unsigned char i = 0; i < nbits; i++)
    {
        if (bit & obj.notcare)
            os << "-";
        else if (bit & obj.number)
            os << "1";
        else
            os << "0";
        bit <<= 1;
    }
    return os;
}




bool can_merge(const Implicant &a, const Implicant& b)
{
    if (a.notcare ^ b.notcare)
        return false;
    binary res = a.number ^ b.number;
    return res != 0 && (res & (res - 1)) == 0;
}

Implicant merge(const Implicant &a, const Implicant& b)
{
    return Implicant(a.number & b.number, a.notcare | (a.number ^ b.number));
}

void merge(std::vector<Implicant>& implicants)
{
    unsigned long size = implicants.size();
    std::vector<bool> mergedvec(size, false);
    std::vector<Implicant> outvec;
    std::vector<Implicant> avec(implicants);
    std::vector<Implicant> bvec;
    auto direct = &avec;
    auto auxiliar = &bvec;
    std::cout << "Got here !" << std::endl;
    std::cout << "Implicants = [";
    for (const auto& imp : implicants)
    {
        std::cout << imp << ", ";
    }
    std::cout << "]" << std::endl;
    while (!direct->empty())
    {
        for (unsigned long i = 0; i < size; i++)
        {
            for (unsigned long j = i+1; j < size; j++)
            {
                if (can_merge((*direct)[i], (*direct)[j]))
                {
                    mergedvec[i] = true;
                    mergedvec[j] = true;
                    auto merged = merge((*direct)[i], (*direct)[j]);
                    std::cout << "Merge(" << (*direct)[i] << ", " << (*direct)[j] << ") = " << merged << std::endl;
                    bool contained = false;
                    for (const auto& imp : *auxiliar)
                    {
                        if (merged.notcare == imp.notcare && merged.number == imp.number)
                        {
                            contained = true;
                            break;
                        }
                    }
                    if (!contained)
                    {
                        auxiliar->push_back(merged);
                    }
                }
            }
            if (!mergedvec[i])
            {
                outvec.push_back((*direct)[i]);
            }
        }
        std::swap(direct, auxiliar);
        auxiliar->clear();
        size = direct->size();
        mergedvec.assign(size, false);
    }
    std::cout << "At last:" << std::endl;
    std::cout << "Implicants = [";
    for (const auto& imp : outvec)
    {
        std::cout << imp << ", ";
    }
    std::cout << "]" << std::endl;
    implicants = std::move(outvec);
}