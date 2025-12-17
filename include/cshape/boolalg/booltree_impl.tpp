#pragma once
#include "types.h"
#include "booltree.h"
#include <utility>

template <typename T>
BoolTree<T>::BoolTree(const Operations operation, const std::vector<std::shared_ptr<BoolTree<T>>> &nodes)
    : operation(operation), nodes(nodes)
{
    switch (operation) {
        case Operations::True:
        case Operations::False:
        case Operations::Variable:
            if (!nodes.empty()) throw std::invalid_argument("Must have no node");
            break;
        case Operations::Not:
            if (nodes.size() != 1) throw std::invalid_argument("Must have only one node");
            break;
        default: break;
    }
}


template<typename T>
std::shared_ptr<BoolTree<T>> operator~(const std::shared_ptr<BoolTree<T>> &p)
{
    auto result = p->build(Operations::Not, {p});
    return p->simplify == nullptr ? result : p->simplify(result);
}
template<typename T>
std::shared_ptr<BoolTree<T>> operator|(const std::shared_ptr<BoolTree<T>> &a, const std::shared_ptr<BoolTree<T>> &b)
{
    auto result = a->build(Operations::Or, {a, b});
    return a->simplify == nullptr ? result : a->simplify(result);
}
template<typename T>
std::shared_ptr<BoolTree<T>> operator&(const std::shared_ptr<BoolTree<T>> &a, const std::shared_ptr<BoolTree<T>> &b)
{
    auto result = a->build(Operations::And, {a, b});
    return a->simplify == nullptr ? result : a->simplify(result);
}
template<typename T>
std::shared_ptr<BoolTree<T>> operator^(const std::shared_ptr<BoolTree<T>> &a, const std::shared_ptr<BoolTree<T>> &b)
{
    auto result = a->build(Operations::Xor, {a, b});
    return a->simplify == nullptr ? result : a->simplify(result);
}


template<typename T>
bool operator==(const std::shared_ptr<BoolTree<T>> &a, const std::shared_ptr<BoolTree<T>> &b)
{
    if (a->operation != b->operation)
        return false;
    if (a->nodes.size() != b->nodes.size())
        return false;
    for (unsigned i = 0; i < a->nodes.size(); i++)
        if (a->nodes[i] != b->nodes[i])
            return false;
    return true;
}
template<typename T>
bool operator!=(const std::shared_ptr<BoolTree<T>> &a, const std::shared_ptr<BoolTree<T>> &b)
{
    return !(a == b);
}
