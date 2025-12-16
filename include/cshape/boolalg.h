#ifndef BOOLALG_H
#define BOOLALG_H

#include <iostream>
#include <vector>
#include <memory>
#include <cstddef>
#include <array>



template <typename T>
using ISimplifier = std::shared_ptr<T> (*)(const std::shared_ptr<T> &);


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
class BoolTreeFactory
{
public:
    virtual std::shared_ptr<T> build(const Operations operation, const std::vector<std::shared_ptr<T>> nodes) const = 0;
    std::shared_ptr<T> build(const Operations operation, const std::initializer_list<std::shared_ptr<T>> nodes) const {
        std::vector<std::shared_ptr<T>> items = nodes;
        return this->build(operation, items);
    };
    std::shared_ptr<T> True() const { return this->build(Operations::True, {});};
    std::shared_ptr<T> False() const { return this->build(Operations::False, {});};
};


template <typename T>
class BoolTree;


template <typename T>
class BoolTree {
    public:
        BoolTree(const Operations operation, const std::vector<std::shared_ptr<BoolTree<T>>> nodes);
        
    public:
        const Operations operation;
        const std::vector<std::shared_ptr<BoolTree<T>>> nodes;

        static const std::unique_ptr<BoolTreeFactory<BoolTree<T>>> factory;
        static const ISimplifier<BoolTree<T>> simplifier;
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
    auto result = p->factory->build(Operations::Not, {p});
    return p->simplifier == nullptr ? result : p->simplifier(result);
}
template<typename T>
std::shared_ptr<BoolTree<T>> operator|(const std::shared_ptr<BoolTree<T>> &a, const std::shared_ptr<BoolTree<T>> &b)
{
    auto result = a->factory->build(Operations::Or, {a, b});
    return a->simplifier == nullptr ? result : a->simplifier(result);
}
template<typename T>
std::shared_ptr<BoolTree<T>> operator&(const std::shared_ptr<BoolTree<T>> &a, const std::shared_ptr<BoolTree<T>> &b)
{
    auto result = a->factory->build(Operations::And, {a, b});
    return a->simplifier == nullptr ? result : a->simplifier(result);
}
template<typename T>
std::shared_ptr<BoolTree<T>> operator^(const std::shared_ptr<BoolTree<T>> &a, const std::shared_ptr<BoolTree<T>> &b)
{
    auto result = a->factory->build(Operations::Xor, {a, b});
    return a->simplifier == nullptr ? result : a->simplifier(result);
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
        std::shared_ptr<BoolTree<char>> build(const Operations operation, const std::vector<std::shared_ptr<BoolTree<char>>> nodes) const override;
    
};


template<>
const std::unique_ptr<BoolTreeFactory<BoolTree<char>>> BoolTree<char>::factory = std::make_unique<StringBoolTreeFactory>();


std::shared_ptr<BoolTree<char>> StringBoolTreeFactory::build(const Operations operation, const std::vector<std::shared_ptr<BoolTree<char>>> nodes) const
{
    return std::make_shared<StringBoolTree>(operation, nodes);
}


template<typename T>
std::shared_ptr<BoolTree<T>> false_true_tree_simpifier(const std::shared_ptr<BoolTree<T>> &tree)
{
    switch (tree->operation)
    {
        case Operations::False:
        case Operations::True:
        case Operations::Variable:
            return tree;
        case Operations::Not:
        {
            const auto& item = false_true_tree_simpifier(tree->nodes[0]);
            if (item->operation == Operations::False)
                return tree->factory->True();
            if (item->operation == Operations::True)
                return tree->factory->False();
            return tree;
        }
        case Operations::Or:
        {
            bool contains_false = false;
            for (const auto& node : tree->nodes)
            {
                if (node->operation == Operations::True)
                    return node;
                else if (node->operation == Operations::False)
                    contains_false = true;
            }
            if (!contains_false)
                return tree;
            std::vector<std::shared_ptr<BoolTree<T>>> newnodes;
            for (const auto& node : tree->nodes)
                if (node->operation != Operations::False)
                    newnodes.push_back(node);
            return tree->factory->build(Operations::Or, newnodes);
        }
        case Operations::And:
        {
            bool contains_true = false;
            for (const auto& node : tree->nodes)
            {
                if (node->operation == Operations::False)
                    return node;
                else if (node->operation == Operations::True)
                    contains_true = true;
            }
            if (!contains_true)
                return tree;
            std::vector<std::shared_ptr<BoolTree<T>>> newnodes;
            for (const auto& node : tree->nodes)
                if (node->operation != Operations::True)
                    newnodes.push_back(node);
            return tree->factory->build(Operations::And, newnodes);
        }
        case Operations::Xor:
        {
            bool contains_false = false;
            unsigned char nbtrues = 0;
            for (const auto& node : tree->nodes)
            {
                if (node->operation == Operations::True)
                    nbtrues++;
                else if (node->operation == Operations::False)
                    contains_false = true;
            }
            if (!contains_false && nbtrues == 0)
            {
                return tree;
            }
            std::vector<std::shared_ptr<BoolTree<T>>> newnodes;
            for (const auto& node : tree->nodes)
                if (node->operation != Operations::True && node->operation != Operations::False)
                    newnodes.push_back(node);
            auto result = tree->factory->build(Operations::Xor, newnodes);
            if (nbtrues % 2)
                result = tree->factory->build(Operations::Not, {result});
            return result;
        }
        default:
            throw std::is_error_condition_enum<Operations>();
    }
    
};






template<typename T>
void recursive_flatten(std::vector<std::shared_ptr<BoolTree<T>>> &vec, const std::shared_ptr<BoolTree<T>> &tree)
{
    for (const auto &node : tree->nodes)
    {
        if (node->operation != tree->operation)
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
std::shared_ptr<BoolTree<T>> flatten_tree_simpifier(const std::shared_ptr<BoolTree<T>> &tree)
{
    switch (tree->operation)
    {
        case Operations::False:
        case Operations::True:
        case Operations::Variable:
            return tree;
        case Operations::Not:
        {
            auto& item = tree->nodes[0];
            return item->operation != Operations::Not ? tree : flatten_tree_simpifier(item->nodes[0]);
        }
        case Operations::Or:
        case Operations::And:
        case Operations::Xor:
        {
            bool needs_flat = false;
            for (const auto &node : tree->nodes)
            {
                if (node->operation == tree->operation)
                {
                    needs_flat = true;
                    break;
                }
            }
            if (!needs_flat)
                return tree;
            std::vector<std::shared_ptr<BoolTree<T>>> newnodes;
            recursive_flatten(newnodes, tree);
            return tree->factory->build(tree->operation, newnodes);
        }
        default:
            throw std::is_error_condition_enum<Operations>();
    }   
}


template<typename T>
std::shared_ptr<BoolTree<T>> equal_reference_tree_simplifier(const std::shared_ptr<BoolTree<T>> &tree)
{
    switch (tree->operation)
    {
        case Operations::False:
        case Operations::True:
        case Operations::Variable:
        case Operations::Not:
            return tree;
        case Operations::Or:
        case Operations::And:
        case Operations::Xor:
        {
            std::vector<unsigned char> bases;
            std::vector<unsigned char> equals;
            bases.reserve(tree->nodes.size());
            equals.reserve(tree->nodes.size());
            unsigned char index = 0;
            
            for (const auto& node : tree->nodes)
            {
                bool equal = false;
                for (const auto &i : bases)
                {
                    if (node == tree->nodes[i])
                    {
                        equals.push_back(i);
                        equal = true;
                        break;
                    }
                }
                if (!equal)
                {
                    bases.push_back(index);
                    equals.push_back(index);
                }
                index++;
            }
            if (bases.size() == equals.size())
                return tree;
            std::vector<std::shared_ptr<BoolTree<T>>> newnodes;
            newnodes.reserve(bases.size());
            for (const auto &i : bases)
            {
                newnodes.push_back(tree->nodes[i]);
            }
            return tree->factory->build(tree->operation, newnodes);
        }
    }
    throw std::is_error_condition_enum<Operations>();
}


template<typename T>
std::shared_ptr<BoolTree<T>> single_item_simplifier(const std::shared_ptr<BoolTree<T>> &tree)
{
    switch (tree->operation)
    {
        case Operations::False:
        case Operations::True:
        case Operations::Variable:
            return tree;
        case Operations::Not:
        {
            const auto& item = single_item_simplifier(tree->nodes[0]);
            return tree->factory->build(Operations::Not, {item});
        }
        case Operations::And:
        case Operations::Or:
        case Operations::Xor:
            switch (tree->nodes.size())
            {
                case 0:
                    return tree->operation == Operations::And ? tree->factory->True() : tree->factory->False();
                case 1:
                    return tree->nodes[0];
                default:
                    return tree;
            }
    }
    throw std::is_error_condition_enum<Operations>();
}


template<typename T>
std::shared_ptr<BoolTree<T>> composition_tree_simplifier(const std::shared_ptr<BoolTree<T>> &tree)
{
    const static std::vector<ISimplifier<BoolTree<T>>> simplifiers = {
        false_true_tree_simpifier<T>,
        flatten_tree_simpifier<T>,
        equal_reference_tree_simplifier<T>,
        single_item_simplifier<T>,
    };
    std::shared_ptr<BoolTree<T>> actual = tree;
    bool cont = true;
    while (cont)
    {
        cont = false;
        for (const ISimplifier<BoolTree<T>> &simplifier : simplifiers)
        {
            std::shared_ptr<BoolTree<T>> newpt = simplifier(actual);
            if (newpt != actual)
            {
                cont = true;
                actual = newpt;
                break;
            }
        }
    };
    return actual;
    
}



template<>
const ISimplifier<BoolTree<char>> BoolTree<char>::simplifier = composition_tree_simplifier<char>;




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