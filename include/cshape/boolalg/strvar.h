#ifndef BOOLALG_STRVAR_H
#define BOOLALG_STRVAR_H

#include "booltree.h"


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





#endif