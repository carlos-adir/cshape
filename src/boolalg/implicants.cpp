#include <iostream>
#include "cshape/boolalg/implicants.h"

template<typename T>
inline bool has_one_bit(const T& number)
{
    return (number & (number - 1)) == 0;
}

bool has_one_bit(const Binary& number)
{
    bool one_bit = false;
    for (const byte b : number.bytes)
        if (has_one_bit(b))
        {
            if (one_bit)
                return false;
            one_bit = true;
        }
    return one_bit;
}

bool can_merge(const Implicant &a, const Implicant& b)
{
    if (a.notcare ^ b.notcare)
        return false;
    Binary res = a.number ^ b.number;
    return res != 0 && has_one_bit(res);
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
                std::cout << "Can merge [" << (*direct)[i] << ", " << (*direct)[j] << "]" << std::endl;
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

std::ostream &operator<<(std::ostream &os, const Implicant &obj)
{
    const unsigned char nbits = obj.number.nbits;
    std::cout << "(" << obj.notcare << ", " << obj.number << ")" << std::endl;
    Binary bit(true, nbits);
    bit <<= (nbits-1);
    for (; bool(bit); bit>>=1)
    {
        auto k = bit & obj.notcare;
        os << bit << "&" << obj.notcare << "=" << k << std::endl;
        if (bool(bit & obj.notcare))
            os << '-';
        else if (bool(bit & obj.number))
            os << '1';
        else
            os << '0';
    }
    return os;
}