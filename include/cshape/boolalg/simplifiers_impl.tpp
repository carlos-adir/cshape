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
    switch (tree->operation)
    {
        case Operations::True:
        case Operations::False:
        case Operations::Variable:
            return tree;
        case Operations::Not:
        case Operations::Or:
        case Operations::And:
        case Operations::Xor:
            break;
        default:
            throw std::is_error_condition_enum<Operations>();
    }
    const static std::vector<ISimplifier<BoolTree<T>>> simplifiers = {
        false_true_tree_simpifier<T>,
        flatten_tree_simpifier<T>,
        equal_reference_tree_simplifier<T>,
        single_item_simplifier<T>,
        implicants_tree_simplifier<T>,
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

template<typename T>
const std::vector<std::shared_ptr<BoolTree<T>>> find_variables(const std::shared_ptr<BoolTree<T>> &tree)
{
    switch (tree->operation)
    {
        case Operations::True:
        case Operations::False:
            return {};
        case Operations::Variable:
            return {tree};
        case Operations::Not:
            return find_variables(tree->nodes[0]);
        case Operations::Or:
        case Operations::And:
        case Operations::Xor:
        {
            std::vector<std::shared_ptr<BoolTree<T>>> variables;
            for (const auto& node : tree->nodes)
            {
                for (const auto& candidate : find_variables(node))
                {
                    bool contained = false;
                    for (const auto& var : variables)
                    {
                        if (candidate == var)
                        {
                            contained = true;
                            break;
                        }
                    }
                    if (!contained)
                    {
                        variables.push_back(candidate);
                    }
                }
            }
            return variables;
        }
        default:
            throw std::is_error_condition_enum<Operations>();
    }
}


enum class ImpBit { False = 0, True = 1, NotCare = 2, };


const std::vector<ImpBit> number2implicant(unsigned long number, const unsigned char size)
{
    std::vector<ImpBit> bits;
    bits.reserve(size);
    for (unsigned char i = 0; i < size; i++)
    {
        bits.push_back(number % 2 ? ImpBit::True : ImpBit::False);
        number /= 2;
    }
    return bits;
}


struct Implicant
{
    Implicant(const unsigned long number, const unsigned char size) : bits(number2implicant(number, size)) {};
    const std::vector<ImpBit> bits;
};


template<typename T>
bool evaluate_tree(const std::shared_ptr<BoolTree<T>>& tree, const std::vector<std::shared_ptr<BoolTree<T>>> variables, const unsigned long number)
{
    switch (tree->operation)
    {
        case Operations::False:
            return false;
        case Operations::True:
            return true;
        case Operations::Variable:
            unsigned char index = 0;
            while (tree != variables[index])
                index++;
            return number & (1u << index);
        case Operations::Not:
            return !evaluate_tree<T>(tree->nodes[0], variables, number);
        case Operations::Or:
            for (const auto& node : tree->nodes)
                if (evaluate_tree(node, variables, number))
                    return true;
            return false;
        case Operations::And:
            for (const auto& node : tree->nodes)
                if (!evaluate_tree(node, variables, number))
                    return false;
            return true;
        case Operations::Xor:
            bool result = false;
            for (const auto& node : tree->nodes)
                if (evaluate_tree(node, variables, number))
                    result = !result;
            return result;
        default:
            throw std::is_error_condition_enum<Operations>();
    }
}

template<typename T>
std::shared_ptr<BoolTree<T>> implicants_tree_simplifier(const std::shared_ptr<BoolTree<T>> &tree)
{
    switch (tree->operation)
    {
        case Operations::False:
        case Operations::True:
        case Operations::Variable:
            return tree;
        case Operations::Not:
        case Operations::Or:
        case Operations::And:
        case Operations::Xor:
            break;
        default:
            throw std::is_error_condition_enum<Operations>();
    }
    const auto variables = find_variables(tree);
    const unsigned char size = variables.size();
    const unsigned long maxnumb = 1u << size;
    std::vector<Implicant> implicants;
    for (unsigned long index = 0; index < maxnumb; index++)
        if (evaluate_tree(tree, variables, index))
            implicants.push_back(Implicant(index));
    unsigned long indices;
    std::cout << "vars of " << tree << " = [";
    for (const auto & v : variables)
    {
        std::cout << v << ", ";
    }
    std::cout << "]" << std::endl;
    return tree;
}

