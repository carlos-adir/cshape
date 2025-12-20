#ifndef BIDIM_SUBSETR2_H
#define BIDIM_SUBSETR2_H

#include "boolalg.h"

class ISubSetR2{};

class SubSetR2 : public ISubSetR2
{
private:
    const std::shared_ptr<BoolTree<SubSetR2>> pointer;
protected:
    SubSetR2(const std::shared_ptr<BoolTree<SubSetR2>> pointer);
public:
    static std::shared_ptr<SubSetR2> empty();
    static std::shared_ptr<SubSetR2> whole();

    friend std::shared_ptr<SubSetR2> operator~(const std::shared_ptr<SubSetR2> &p);
    friend std::shared_ptr<SubSetR2> operator|(const std::shared_ptr<SubSetR2> &a, const std::shared_ptr<SubSetR2> &b);
    friend std::shared_ptr<SubSetR2> operator&(const std::shared_ptr<SubSetR2> &a, const std::shared_ptr<SubSetR2> &b);
    friend std::shared_ptr<SubSetR2> operator^(const std::shared_ptr<SubSetR2> &a, const std::shared_ptr<SubSetR2> &b);
    friend bool operator==(const std::shared_ptr<SubSetR2> &a, const std::shared_ptr<SubSetR2> &b);
};







#endif
