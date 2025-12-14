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
class Factory
{
public:
    virtual std::shared_ptr<T> Build(const Operations operation, const std::vector<std::shared_ptr<T>> nodes) const = 0;
};


template <typename T>
class BoolTree : private std::enable_shared_from_this<BoolTree<T>> {
    public:
        BoolTree(const Operations operation, const std::vector<std::shared_ptr<BoolTree<T>>> nodes) : operation(operation), nodes(nodes) {};
        const Operations operation;
        const std::vector<std::shared_ptr<BoolTree<T>>> nodes;
        
        std::shared_ptr<BoolTree<T>> operator~();
        std::shared_ptr<BoolTree<T>> operator|(const std::shared_ptr<BoolTree<T>> &other);
        std::shared_ptr<BoolTree<T>> operator&(const std::shared_ptr<BoolTree<T>> &other);
        std::shared_ptr<BoolTree<T>> operator^(const std::shared_ptr<BoolTree<T>> &other);

        static const std::unique_ptr<Factory<BoolTree<T>>> factory;
        static std::vector<ISimplifier<std::shared_ptr<BoolTree<T>>>> simplifiers;

};

class StringBoolTree : public BoolTree<char>
{
    public:
        StringBoolTree(const Operations operation, const std::vector<std::shared_ptr<BoolTree<char>>> nodes) : BoolTree<char>(operation, nodes) {};
};


class StringBoolTreeFactory : public Factory<BoolTree<char>>
{
    public:
        StringBoolTreeFactory() {};
        std::shared_ptr<BoolTree<char>> Build(const Operations operation, const std::vector<std::shared_ptr<BoolTree<char>>> nodes) const override;
    
};

template class BoolTree<char>;

template<>
const std::unique_ptr<Factory<BoolTree<char>>> BoolTree<char>::factory = std::make_unique<StringBoolTreeFactory>();

std::shared_ptr<BoolTree<char>> StringBoolTreeFactory::Build(const Operations operation, const std::vector<std::shared_ptr<BoolTree<char>>> nodes) const
{
    return std::make_shared<StringBoolTree>(operation, nodes);
}



template<typename T>
std::shared_ptr<BoolTree<T>> BoolTree<T>::operator~()
{
    std::vector<std::shared_ptr<BoolTree<T>>> items;
    items.reserve(1);
    items.push_back(this->shared_from_this());
    return this->factory->Build(Operations::Not, items);
}

template<typename T>
std::shared_ptr<BoolTree<T>> BoolTree<T>::operator|(const std::shared_ptr<BoolTree<T>> &other)
{
    std::vector<std::shared_ptr<BoolTree<T>>> items;
    items.reserve(2);
    items.push_back(this->shared_from_this());
    items.push_back(other);
    return this->factory->Build(Operations::Or, items);
}

template<typename T>
std::shared_ptr<BoolTree<T>> BoolTree<T>::operator&(const std::shared_ptr<BoolTree<T>> &other)
{
    std::vector<std::shared_ptr<BoolTree<T>>> items;
    items.reserve(2);
    items.push_back(this->shared_from_this());
    items.push_back(other);
    return this->factory->Build(Operations::And, items);
}

template<typename T>
std::shared_ptr<BoolTree<T>> BoolTree<T>::operator^(const std::shared_ptr<BoolTree<T>> &other)
{
    std::vector<std::shared_ptr<BoolTree<T>>> items;
    items.reserve(2);
    items.push_back(this->shared_from_this());
    items.push_back(other);
    return this->factory->Build(Operations::Xor, items);
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
    return obj->factory->Build(obj.ope, newnodes);
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