#ifndef BOOLALG_PRINTER_H
#define BOOLALG_PRINTER_H

#include <iostream>
#include <memory>
#include "booltree.h"


template <typename T>
std::ostream &
operator<< (std::ostream &os, const std::shared_ptr<BoolTree<T>> &tree);


template <typename T>
std::ostream &
operator<< (std::ostream &os, const std::shared_ptr<BoolTree<T>> &tree)
{
    switch (tree->operation)
    {
        case Operations::True:
            return os << "1";
        case Operations::False:
            return os << "0";
        case Operations::Not:
            return os << "NOT[" << tree->nodes[0] << "]";
        case Operations::Variable:
            return os << "var";
        case Operations::Or:
            os << "OR[";
            break;
        case Operations::And:
            os << "AND[";
            break;
        case Operations::Xor:
            os << "XOR[";
            break;
    }
    const unsigned size = tree->nodes.size();
    if (size > 0)
        os << tree->nodes[0];
    for (unsigned i = 1; i < size; i++)
    {
        os << "," << tree->nodes[i];
    }
    return os << "]";
};


#endif
