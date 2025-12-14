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
class BoolTree : public std::enable_shared_from_this<BoolTree<T>> {
    private:
        BoolTree(const Operations operation, const std::vector<std::shared_ptr<BoolTree<T>>> &nodes);
    protected:
        virtual std::shared_ptr<BoolTree<T>> build(const Operations operation, const std::vector<std::shared_ptr<BoolTree<T>>> &nodes);
    public:
        const Operations operation;
        const std::vector<std::shared_ptr<BoolTree<T>>> nodes;
        
        static std::vector<ISimplifier<BoolTree<T>>> simplifiers;

        static const std::shared_ptr<BoolTree<T>> False();
        static const std::shared_ptr<BoolTree<T>> True();
        std::shared_ptr<BoolTree<T>> operator~();
        std::shared_ptr<BoolTree<T>> operator|(const BoolTree<T> &other);
        std::shared_ptr<BoolTree<T>> operator&(const BoolTree<T> &other);
        std::shared_ptr<BoolTree<T>> operator^(const BoolTree<T> &other);
};

template <typename T>
BoolTree<T>::BoolTree (const Operations operation, const std::vector<std::shared_ptr<BoolTree<T>>> &nodes) : operation(operation), nodes (nodes){};

template <typename T>
std::shared_ptr<BoolTree<T>> BoolTree<T>::build(const Operations operation, const std::vector<std::shared_ptr<BoolTree<T>>> &nodes)
{
    return BoolTree<T>(operation, nodes).shared_from_this();
};

template <typename T>
std::ostream &
operator<< (std::ostream &os, const BoolTree<T> &tree)
{
    return os;
};

template<typename T>
const std::shared_ptr<BoolTree<T>> BoolTree<T>::False()
{
    return BoolTree<T>(Operations::False, {}).shared_from_this();
}

template<typename T>
const std::shared_ptr<BoolTree<T>> BoolTree<T>::True()
{
    return BoolTree<T>(Operations::True, {}).shared_from_this();
}

template<typename T>
std::shared_ptr<BoolTree<T>> BoolTree<T>::operator~()
{
    std::vector<std::shared_ptr<BoolTree<T>>> items;
    items.reserve(1);
    items.push_back(this->shared_from_this());
    return this->build(Operations::Not, items);
}

template<typename T>
std::shared_ptr<BoolTree<T>> BoolTree<T>::operator|(const BoolTree<T> &other)
{
    std::array<std::shared_ptr<BoolTree<T>>, 2> items;
    items.reserve(2);
    items.push_back(this->shared_from_this());
    items.push_back(other.shared_from_this());
    return this->build(Operations::Or, items);
}

template<typename T>
std::shared_ptr<BoolTree<T>> BoolTree<T>::operator&(const BoolTree<T> &other)
{
    std::vector<std::shared_ptr<BoolTree<T>>> items;
    items.reserve(2);
    items.push_back(this->shared_from_this());
    items.push_back(other.shared_from_this());
    return this->build(Operations::And, items);
}

template<typename T>
std::shared_ptr<BoolTree<T>> BoolTree<T>::operator^(const BoolTree<T> &other)
{
    std::vector<std::shared_ptr<BoolTree<T>>> items;
    items.reserve(2);
    items.push_back(this->shared_from_this());
    items.push_back(other.shared_from_this());
    return this->build(Operations::Xor, items);
}

template<typename T>
class FlattenTreeSimpifier : ISimplifier<BoolTree<T>>
{
    public:
        std::shared_ptr<BoolTree<T>> simplify(const std::shared_ptr<BoolTree<T>> &obj) const override;
};



template<typename T>
void recursive_flatten(std::vector<std::shared_ptr<BoolTree<T>>> &vec, const BoolTree<T> &obj)
{
    // for (const std::shared_ptr<BoolTree<T>>&n : obj.nodes)
    // {
    //  
    // }
}


template<typename T>
std::shared_ptr<BoolTree<T>> FlattenTreeSimpifier<T>::simplify(const std::shared_ptr<BoolTree<T>> &obj) const
{
    std::vector<std::shared_ptr<BoolTree<T>>> newnodes = {};
    return obj.build(obj.ope, newnodes);
}



template class BoolTree<char>;

#endif