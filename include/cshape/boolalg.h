#ifndef BOOLALG_H
#define BOOLALG_H

#include <iostream>
#include <vector>
#include <memory>
#include <cstddef>
#include <array>

enum class Operations
{
    False = 0,
    True,
    Variable,
    Not,
    And,
    Or,
    Xor,
};

template <typename T>
class ISimplifier {
    public:
        virtual T simplify(const T &obj) const = 0;
};

template <typename T>
class BoolTreeFactory
{
public:
    virtual std::shared_ptr<T> Build(const Operations operation, const std::vector<std::shared_ptr<T>> nodes) const = 0;
    std::shared_ptr<T> Build(const Operations operation, const std::initializer_list<std::shared_ptr<T>> nodes) const {
        std::vector<std::shared_ptr<T>> items = nodes;
        return this->Build(operation, items);
    };
    std::shared_ptr<T> True() const { return this->Build(Operations::True, {});};
    std::shared_ptr<T> False() const { return this->Build(Operations::False, {});};
    
};

template <typename T>
class BoolTree {
    public:
        BoolTree(const Operations operation, const std::vector<std::shared_ptr<BoolTree<T>>> nodes);
        
    public:
        const Operations operation;
        const std::vector<std::shared_ptr<BoolTree<T>>> nodes;

        static const std::unique_ptr<BoolTreeFactory<BoolTree<T>>> factory;
        static std::vector<std::unique_ptr<ISimplifier<std::shared_ptr<BoolTree<T>>>>> simplifiers;
};


template <typename T>
BoolTree<T>::BoolTree (const Operations operation, const std::vector<std::shared_ptr<BoolTree<T>>> nodes) : operation(operation), nodes(nodes)
{
    switch (operation)
    {
        case Operations::True:
        case Operations::False:
        case Operations::Variable:
            if (nodes.size() > 0)
                throw std::invalid_argument("Must have no node");
            break;
        case Operations::Not:
            if (nodes.size() != 1)
                throw std::invalid_argument("Must have only one node");
            break;
        default:
            break;
    }
};


template<typename T>
std::shared_ptr<BoolTree<T>> operator~(const std::shared_ptr<BoolTree<T>> &p)
{
    switch (p->operation)
    {
        case Operations::False:
            return p->factory->True();
        case Operations::True:
            return p->factory->False();
        case Operations::Not:
            return p->nodes[0];
        default:
            return p->factory->Build(Operations::Not, {p});
    }
}
template<typename T>
std::shared_ptr<BoolTree<T>> operator|(const std::shared_ptr<BoolTree<T>> &a, const std::shared_ptr<BoolTree<T>> &b)
{
    switch (a->operation)
    {
        case Operations::True:
            return a;
        case Operations::False:
            return b;
        default:
            break;
    }
    switch (b->operation)
    {
        case Operations::True:
            return b;
        case Operations::False:
            return a;
        default:
            break;
    }
    return a->factory->Build(Operations::Or, {a, b});
}
template<typename T>
std::shared_ptr<BoolTree<T>> operator&(const std::shared_ptr<BoolTree<T>> &a, const std::shared_ptr<BoolTree<T>> &b)
{
    switch (a->operation)
    {
        case Operations::True:
            return b;
        case Operations::False:
            return a;
        default:
            break;
    }
    switch (b->operation)
    {
        case Operations::True:
            return a;
        case Operations::False:
            return b;
        default:
            break;
    }
    return a->factory->Build(Operations::And, {a, b});
}
template<typename T>
std::shared_ptr<BoolTree<T>> operator^(const std::shared_ptr<BoolTree<T>> &a, const std::shared_ptr<BoolTree<T>> &b)
{
    switch (a->operation)
    {
        case Operations::True:
            return ~b;
        case Operations::False:
            return b;
        default:
            break;
    }
    switch (b->operation)
    {
        case Operations::True:
            return ~a;
        case Operations::False:
            return a;
        default:
            break;
    }
    return a->factory->Build(Operations::Xor, {a, b});
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




class StringBoolTree : public BoolTree<char>
{
    public:
        StringBoolTree(const Operations operation, const std::vector<std::shared_ptr<BoolTree<char>>> nodes) : BoolTree<char>(operation, nodes) {};
        StringBoolTree(const Operations operation, const std::initializer_list<std::shared_ptr<BoolTree<char>>> nodes) : BoolTree<char>(operation, nodes) {};
};


class StringBoolVariable : public StringBoolTree
{
    private:
        const std::string name;
    public:
        StringBoolVariable(const std::string &name) : StringBoolTree(Operations::Variable, {}), name(name){};
        static std::shared_ptr<BoolTree<char>> build(const std::string &name) {return std::make_shared<StringBoolVariable>(name);};
};




class StringBoolTreeFactory : public BoolTreeFactory<BoolTree<char>>
{
    public:
        StringBoolTreeFactory() {};
        std::shared_ptr<BoolTree<char>> Build(const Operations operation, const std::vector<std::shared_ptr<BoolTree<char>>> nodes) const override;
    
};


template<>
const std::unique_ptr<BoolTreeFactory<BoolTree<char>>> BoolTree<char>::factory = std::make_unique<StringBoolTreeFactory>();


std::shared_ptr<BoolTree<char>> StringBoolTreeFactory::Build(const Operations operation, const std::vector<std::shared_ptr<BoolTree<char>>> nodes) const
{
    return std::make_shared<StringBoolTree>(operation, nodes);
}

template<typename T>
class FlattenTreeSimpifier : ISimplifier<std::shared_ptr<BoolTree<T>>>
{
    public:
        FlattenTreeSimpifier(){};
        std::shared_ptr<BoolTree<T>> simplify(const std::shared_ptr<BoolTree<T>> &obj) const override;
};

template<typename T>
class RemoveEqualSimpifier : ISimplifier<std::shared_ptr<BoolTree<T>>>
{
    public:
        RemoveEqualSimpifier(){};
        std::shared_ptr<BoolTree<T>> simplify(const std::shared_ptr<BoolTree<T>> &obj) const override;
};


/*
std::vector<std::unique_ptr<ISimplifier<std::shared_ptr<BoolTree<char>>>>> create_simplifiers()
{
    std::vector<std::unique_ptr<ISimplifier<std::shared_ptr<BoolTree<char>>>>> v;
    v.reserve(2);
    v.emplace_back(std::make_unique<FlattenTreeSimpifier<char>>());
    v.emplace_back(std::make_unique<RemoveEqualSimpifier<char>>());
    return v; // moved, not copied
}

template<>
std::vector<std::unique_ptr<ISimplifier<std::shared_ptr<BoolTree<char>>>>> BoolTree<char>::simplifiers = create_simplifiers();
*/
// 

template<typename T>
void recursive_flatten(std::vector<std::shared_ptr<BoolTree<T>>> &vec, const std::shared_ptr<BoolTree<T>> &obj)
{
    for (const auto &node : obj->nodes)
    {
        if (node->operation != obj->operation)
        {
            vec.push_back(node);
        }
        else
        {
            recursive_flatten(vec, node);
        }
    }
}


template<typename T>
std::shared_ptr<BoolTree<T>> FlattenTreeSimpifier<T>::simplify(const std::shared_ptr<BoolTree<T>> &obj) const
{
    switch (obj->operation)
    {
        case Operations::False:
        case Operations::True:
        case Operations::Not:
        case Operations::Variable:
            return obj;
        default:
            std::vector<std::shared_ptr<BoolTree<T>>> newnodes;
            recursive_flatten(newnodes, obj);
            return obj->factory->Build(obj.ope, newnodes);
    }
}

template<typename T>
std::shared_ptr<BoolTree<T>> RemoveEqualSimpifier<T>::simplify(const std::shared_ptr<BoolTree<T>> &obj) const
{
    switch (obj->operation)
    {
        case Operations::False:
        case Operations::True:
        case Operations::Not:
        case Operations::Variable:
            return obj;
        default:
            std::vector<std::shared_ptr<BoolTree<T>>> newnodes;
            for (const auto& node : obj->nodes)
            {
                bool equal = false;
                for (const auto &n : newnodes)
                {
                    if (node == n)
                    {
                        equal = true;
                        break;
                    }
                }
                if (!equal)
                    newnodes.push_back(node);
            }
            recursive_flatten(newnodes, obj);
            return obj->factory->Build(obj.ope, newnodes);
    }
}


template <typename T>
std::ostream &
operator<< (std::ostream &os, const BoolTree<T> &tree)
{
    return os;
};


template <typename T>
std::ostream &
operator<< (std::ostream &os, const std::shared_ptr<BoolTree<T>> &tree)
{
    return os << *tree;
};


#endif