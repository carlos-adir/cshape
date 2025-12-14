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
        static const std::vector<std::unique_ptr<ISimplifier<std::shared_ptr<BoolTree<T>>>>> simplifiers;
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
            auto result = p->factory->Build(Operations::Not, {p});
            for (const auto& simp : p->simplifiers)
                result = simp->simplify(result);
            return result;
    }
}
template<typename T>
std::shared_ptr<BoolTree<T>> operator|(const std::shared_ptr<BoolTree<T>> &a, const std::shared_ptr<BoolTree<T>> &b)
{
    auto result = a->factory->Build(Operations::Or, {a, b});
    for (const auto& simp : a->simplifiers)
        result = simp->simplify(result);
    return result;
}
template<typename T>
std::shared_ptr<BoolTree<T>> operator&(const std::shared_ptr<BoolTree<T>> &a, const std::shared_ptr<BoolTree<T>> &b)
{
    auto result = a->factory->Build(Operations::And, {a, b});
    for (const auto& simp : a->simplifiers)
        result = simp->simplify(result);
    return result;
}
template<typename T>
std::shared_ptr<BoolTree<T>> operator^(const std::shared_ptr<BoolTree<T>> &a, const std::shared_ptr<BoolTree<T>> &b)
{
    auto result = a->factory->Build(Operations::Xor, {a, b});
    for (const auto& simp : a->simplifiers)
        result = simp->simplify(result);
    return result;
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
class FalseTrueTreeSimpifier : public ISimplifier<std::shared_ptr<BoolTree<T>>>
{
    public:
        FalseTrueTreeSimpifier(){};
        ~FalseTrueTreeSimpifier(){};
        std::shared_ptr<BoolTree<T>> simplify(const std::shared_ptr<BoolTree<T>> &obj) const override;
};

template<typename T>
class FlattenTreeSimpifier : public ISimplifier<std::shared_ptr<BoolTree<T>>>
{
    public:
        FlattenTreeSimpifier(){};
        ~FlattenTreeSimpifier(){};
        std::shared_ptr<BoolTree<T>> simplify(const std::shared_ptr<BoolTree<T>> &obj) const override;
};

template<typename T>
class RemoveEqualSimpifier : public ISimplifier<std::shared_ptr<BoolTree<T>>>
{
    public:
        RemoveEqualSimpifier(){};
        ~RemoveEqualSimpifier(){};
        std::shared_ptr<BoolTree<T>> simplify(const std::shared_ptr<BoolTree<T>> &obj) const override;
};

template<typename T>
class SingleItemSimpifier : public ISimplifier<std::shared_ptr<BoolTree<T>>>
{
    public:
        SingleItemSimpifier(){};
        ~SingleItemSimpifier(){};
        std::shared_ptr<BoolTree<T>> simplify(const std::shared_ptr<BoolTree<T>> &obj) const override;
};

std::vector<std::unique_ptr<ISimplifier<std::shared_ptr<BoolTree<char>>>>> create_simplifiers()
{
    std::vector<std::unique_ptr<ISimplifier<std::shared_ptr<BoolTree<char>>>>> v;
    v.reserve(4);
    v.push_back(std::make_unique<FalseTrueTreeSimpifier<char>>());
    v.push_back(std::make_unique<FlattenTreeSimpifier<char>>());
    v.push_back(std::make_unique<RemoveEqualSimpifier<char>>());
    v.push_back(std::make_unique<SingleItemSimpifier<char>>());
    return v; // moved, not copied
}

template<>
const std::vector<std::unique_ptr<ISimplifier<std::shared_ptr<BoolTree<char>>>>> BoolTree<char>::simplifiers = create_simplifiers();

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
std::shared_ptr<BoolTree<T>> FalseTrueTreeSimpifier<T>::simplify(const std::shared_ptr<BoolTree<T>> &obj) const
{
    switch (obj->operation)
    {
        case Operations::False:
        case Operations::True:
        case Operations::Variable:
            return obj;
        case Operations::Not:
        {
            std::shared_ptr<BoolTree<T>> item = this->simplify(obj->nodes[0]);
            if (item->operation == Operations::False)
                return obj->factory->True();
            if (item->operation == Operations::True)
                return obj->factory->False();
            return obj;
        }
        case Operations::Or:
        {
            std::vector<std::shared_ptr<BoolTree<T>>> newnodes;
            for (const auto& node : obj->nodes)
            {
                if (node->operation == Operations::True)
                    return node;
                else if (node->operation != Operations::False)
                    newnodes.push_back(node);
            }
            return obj->factory->Build(Operations::Or, newnodes);
        }
        case Operations::And:
        {
            std::vector<std::shared_ptr<BoolTree<T>>> newnodes;
            for (const auto& node : obj->nodes)
            {
                if (node->operation == Operations::False)
                    return node;
                else if (node->operation != Operations::True)
                    newnodes.push_back(node);
            }
            return obj->factory->Build(Operations::And, newnodes);
        }
        case Operations::Xor:
        {
            bool shift = false;
            std::vector<std::shared_ptr<BoolTree<T>>> newnodes;
            for (const auto& node : obj->nodes)
            {
                if (node->operation == Operations::True)
                    shift = !shift;
                else if (node->operation != Operations::False)
                    newnodes.push_back(node);
            }
            auto result = obj->factory->Build(Operations::Xor, newnodes);
            if (shift)
                result = this->simplify(obj->factory->Build(Operations::Not, {result}));
            return result;
        }
    }
    throw std::is_error_condition_enum<Operations>();
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
        case Operations::Or:
        case Operations::And:
        case Operations::Xor:
            std::vector<std::shared_ptr<BoolTree<T>>> newnodes;
            recursive_flatten(newnodes, obj);
            return obj->factory->Build(obj->operation, newnodes);
    }
    throw std::is_error_condition_enum<Operations>();
}


template<typename T>
std::shared_ptr<BoolTree<T>> RemoveEqualSimpifier<T>::simplify(const std::shared_ptr<BoolTree<T>> &obj) const
{
    switch (obj->operation)
    {
        case Operations::False:
        case Operations::True:
        case Operations::Variable:
            return obj;
        case Operations::Not:
            return obj->factory->Build(Operations::Not, {this->simplify(obj->nodes[0])});
        case Operations::Or:
        case Operations::And:
        case Operations::Xor:
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
            return obj->factory->Build(obj->operation, newnodes);
    }
    throw std::is_error_condition_enum<Operations>();
}


template<typename T>
std::shared_ptr<BoolTree<T>> SingleItemSimpifier<T>::simplify(const std::shared_ptr<BoolTree<T>> &obj) const
{
    switch (obj->operation)
    {
        case Operations::False:
        case Operations::True:
        case Operations::Not:
        case Operations::Variable:
            return obj;
        case Operations::And:
        case Operations::Or:
        case Operations::Xor:
            switch (obj->nodes.size())
            {
                case 0:
                    return obj->operation == Operations::And ? obj->factory->True() : obj->factory->False();
                case 1:
                    return obj->nodes[0];
                default:
                    return obj;
            }
    }
    throw std::is_error_condition_enum<Operations>();
}



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