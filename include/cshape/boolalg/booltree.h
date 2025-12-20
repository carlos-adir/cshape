#ifndef BOOLALG_BOOLTREE_H
#define BOOLALG_BOOLTREE_H

#include "types.h"
#include <stdexcept>
#include <ostream>


template <typename T>
class BoolTree {
protected:
    BoolTree(const Operations operation, const std::vector<std::shared_ptr<BoolTree<T>>> &nodes);
public:
    const Operations operation;
    const std::vector<std::shared_ptr<BoolTree<T>>> nodes;

    static const IBoolTreeBuilder<BoolTree<T>> build;
    static const ISimplifier<BoolTree<T>> simplify;
};

// include template implementations
#include "booltree_impl.tpp"

#endif