#pragma once


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
                return tree->build(Operations::True, {});
            if (item->operation == Operations::True)
                return tree->build(Operations::False, {});
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
            return tree->build(Operations::Or, newnodes);
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
            return tree->build(Operations::And, newnodes);
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
            auto result = tree->build(Operations::Xor, newnodes);
            if (nbtrues % 2)
                result = tree->build(Operations::Not, {result});
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
            return tree->build(tree->operation, newnodes);
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
            return tree->build(tree->operation, newnodes);
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
            return tree->build(Operations::Not, {item});
        }
        case Operations::And:
        case Operations::Or:
        case Operations::Xor:
            switch (tree->nodes.size())
            {
                case 0:
                    return tree->operation == Operations::And ? tree->build(Operations::True, {}) : tree->build(Operations::False, {});
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
