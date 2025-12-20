#include "cshape/boolalg/strvar.h"

#include "cshape/boolalg/simplifiers.h"

std::shared_ptr<BoolTree<char>> StringBoolTree::build(const Operations operation, const std::vector<std::shared_ptr<BoolTree<char>>> &nodes)
{
    return std::shared_ptr<StringBoolTree>(new StringBoolTree(operation, nodes));
}


std::shared_ptr<BoolTree<char>> StringBoolVariable::build(const std::string &name)
{
    return std::shared_ptr<StringBoolVariable>(new StringBoolVariable(name));
}


template<>
const IBoolTreeBuilder<BoolTree<char>> BoolTree<char>::build = StringBoolTree::build;

template<>
const ISimplifier<BoolTree<char>> BoolTree<char>::simplify = composition_tree_simplifier<char>;

