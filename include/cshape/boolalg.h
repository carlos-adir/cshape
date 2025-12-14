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
class BoolTree : private std::enable_shared_from_this<BoolTree<T>> {
    protected:
        BoolTree(const Operations operation, const std::vector<std::shared_ptr<BoolTree<T>>> &nodes);
        virtual std::shared_ptr<BoolTree<T>> build(const Operations operation, const std::vector<std::shared_ptr<BoolTree<T>>> &nodes);
    public:
        const Operations operation;
        const std::vector<std::shared_ptr<BoolTree<T>>> nodes;
        
        BoolTree();

        static std::vector<ISimplifier<std::shared_ptr<BoolTree<T>>>> simplifiers;

        std::shared_ptr<BoolTree<T>> operator~();
        std::shared_ptr<BoolTree<T>> operator|(const std::shared_ptr<BoolTree<T>> &other);
        std::shared_ptr<BoolTree<T>> operator&(const std::shared_ptr<BoolTree<T>> &other);
        std::shared_ptr<BoolTree<T>> operator^(const std::shared_ptr<BoolTree<T>> &other);

        virtual std::string FalseStr() = 0;
        virtual std::string TrueStr() = 0; 
};


template <typename T>
BoolTree<T>::BoolTree () : operation(Operations::False), nodes ({}){};

template <typename T>
BoolTree<T>::BoolTree (const Operations operation, const std::vector<std::shared_ptr<BoolTree<T>>> &nodes) : operation(operation), nodes (nodes){};

template <typename T>
std::shared_ptr<BoolTree<T>> BoolTree<T>::build(const Operations operation, const std::vector<std::shared_ptr<BoolTree<T>>> &nodes)
{
    return BoolTree<T>(operation, nodes).shared_from_this();
};


template<typename T>
std::shared_ptr<BoolTree<T>> BoolTree<T>::operator~()
{
    std::vector<std::shared_ptr<BoolTree<T>>> items;
    items.reserve(1);
    items.push_back(this->shared_from_this());
    return this->build(Operations::Not, items);
}

template<typename T>
std::shared_ptr<BoolTree<T>> BoolTree<T>::operator|(const std::shared_ptr<BoolTree<T>> &other)
{
    std::vector<std::shared_ptr<BoolTree<T>>> items;
    items.reserve(2);
    items.push_back(this->shared_from_this());
    items.push_back(other);
    return this->build(Operations::Or, items);
}

template<typename T>
std::shared_ptr<BoolTree<T>> BoolTree<T>::operator&(const std::shared_ptr<BoolTree<T>> &other)
{
    std::vector<std::shared_ptr<BoolTree<T>>> items;
    items.reserve(2);
    items.push_back(this->shared_from_this());
    items.push_back(other);
    return this->build(Operations::And, items);
}

template<typename T>
std::shared_ptr<BoolTree<T>> BoolTree<T>::operator^(const std::shared_ptr<BoolTree<T>> &other)
{
    std::vector<std::shared_ptr<BoolTree<T>>> items;
    items.reserve(2);
    items.push_back(this->shared_from_this());
    items.push_back(other);
    return this->build(Operations::Xor, items);
}

template<typename T>
class FlattenTreeSimpifier : ISimplifier<std::shared_ptr<BoolTree<T>>>
{
    public:
        std::shared_ptr<BoolTree<T>> simplify(const std::shared_ptr<BoolTree<T>> &obj) const override;
};



template<typename T>
void recursive_flatten(std::vector<std::shared_ptr<BoolTree<T>>> &vec, const std::shared_ptr<BoolTree<T>> &obj)
{
    for (const std::shared_ptr<BoolTree<T>> &node : obj->nodes)
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
    std::vector<std::shared_ptr<BoolTree<T>>> newnodes = {};
    recursive_flatten(newnodes, obj);
    return obj.build(obj.ope, newnodes);
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


class StringBoolTree : public BoolTree<std::string>
{
    protected:
        std::shared_ptr<BoolTree<std::string>> build(const Operations operation, const std::vector<std::shared_ptr<BoolTree<std::string>>> &nodes) override;
    public:
        std::string FalseStr() override {return "0";};
        std::string TrueStr() override {return "1";};
};


std::shared_ptr<BoolTree<std::string>> StringBoolTree::build(const Operations operation, const std::vector<std::shared_ptr<BoolTree<std::string>>> &nodes)
{
    std::shared_ptr<StringBoolTree> child = std::make_shared<StringBoolTree>(operation, nodes);
    return child;
};


#endif