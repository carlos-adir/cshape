#ifndef BOOLALG_SIMPLIFY_H
#define BOOLALG_SIMPLIFY_H

#include "types.h"
#include "booltree.h"

template<typename T>
std::shared_ptr<BoolTree<T>> false_true_tree_simpifier(const std::shared_ptr<BoolTree<T>> &tree);

template<typename T>
std::shared_ptr<BoolTree<T>> flatten_tree_simpifier(const std::shared_ptr<BoolTree<T>> &tree);

template<typename T>
std::shared_ptr<BoolTree<T>> equal_reference_tree_simplifier(const std::shared_ptr<BoolTree<T>> &tree);

template<typename T>
std::shared_ptr<BoolTree<T>> single_item_simplifier(const std::shared_ptr<BoolTree<T>> &tree);

template<typename T>
std::shared_ptr<BoolTree<T>> implicants_tree_simplifier(const std::shared_ptr<BoolTree<T>> &tree);

template<typename T>
std::shared_ptr<BoolTree<T>> composition_tree_simplifier(const std::shared_ptr<BoolTree<T>> &tree);

// include impl
#include "simplifiers_impl.tpp"

#endif
