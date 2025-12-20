#ifndef BOOLALG_H
#define BOOLALG_H

#include <iostream>
#include <vector>
#include <memory>
#include <cstddef>
#include <array>



#include "boolalg/binary.h"
#include "boolalg/types.h"
#include "boolalg/booltree.h"
#include "boolalg/implicants.h"
#include "boolalg/simplifiers.h"
#include "boolalg/printer.h"






class StringBoolTree : public BoolTree<char> 
{
protected:
    StringBoolTree(const Operations operation, const std::vector<std::shared_ptr<BoolTree<char>>> &nodes) : BoolTree<char>(operation, nodes) {};
public:
    static std::shared_ptr<BoolTree<char>> build(const Operations operation, const std::vector<std::shared_ptr<BoolTree<char>>> &items);
};


class StringBoolVariable : public StringBoolTree
{
    protected:
        const std::string name;
        StringBoolVariable(const std::string &name) : StringBoolTree(Operations::Variable, {}), name(name){};
    public:
        static std::shared_ptr<BoolTree<char>> build(const std::string &name);
};


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





#endif