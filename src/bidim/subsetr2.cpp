

#include "cshape/bidim/subsetr2.h"
#include <iostream>


SubSetR2::SubSetR2(const std::shared_ptr<BoolTree<SubSetR2>> pointer) : pointer(pointer){};


template<>
const IBoolTreeBuilder<BoolTree<SubSetR2>> BoolTree<SubSetR2>::build = BoolTree<SubSetR2>::Build;

template<>
const ISimplifier<BoolTree<SubSetR2>> BoolTree<SubSetR2>::simplify = nullptr;


std::shared_ptr<SubSetR2> SubSetR2::empty()
{
    std::shared_ptr<BoolTree<SubSetR2>> pointer = BoolTree<SubSetR2>::build(Operations::False, {});
    return std::shared_ptr<SubSetR2>(new SubSetR2(pointer));
}

std::shared_ptr<SubSetR2> SubSetR2::whole()
{
    std::shared_ptr<BoolTree<SubSetR2>> pointer = BoolTree<SubSetR2>::build(Operations::True, {});
    return std::shared_ptr<SubSetR2>(new SubSetR2(pointer));
}

std::shared_ptr<SubSetR2> operator~(const std::shared_ptr<SubSetR2> &p)
{
    return std::shared_ptr<SubSetR2>(new SubSetR2(~p->pointer));
}

std::shared_ptr<SubSetR2> operator|(const std::shared_ptr<SubSetR2> &a, const std::shared_ptr<SubSetR2> &b)
{
    return std::shared_ptr<SubSetR2>(new SubSetR2(a->pointer | b->pointer));
}

std::shared_ptr<SubSetR2> operator&(const std::shared_ptr<SubSetR2> &a, const std::shared_ptr<SubSetR2> &b)
{
    return std::shared_ptr<SubSetR2>(new SubSetR2(a->pointer & b->pointer));
}

std::shared_ptr<SubSetR2> operator^(const std::shared_ptr<SubSetR2> &a, const std::shared_ptr<SubSetR2> &b)
{
    return std::shared_ptr<SubSetR2>(new SubSetR2(a->pointer ^ b->pointer));
}

bool operator==(const std::shared_ptr<SubSetR2> &a, const std::shared_ptr<SubSetR2> &b)
{
    return a->pointer == b->pointer;
}






