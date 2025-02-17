#ifndef BIDIMBOOL_H
#define BIDIMBOOL_H

#include <vector>
#include <iostream>
#include <unistd.h>


typedef unsigned long uint8;
typedef unsigned int uint4;
typedef unsigned short uint2;
typedef unsigned short uint1;

typedef double basetype;

class SubSetR2;
class EmptyR2;
class WholeR2;

class IPoint;
class ICurve;
class IShape;
class BoolNot;
class BoolAnd;
class BoolOr;


enum SubSetR2Typo {
    EMPTY,
    POINT,
    CURVE,
    SHAPE,
    WHOLE,
    BOOL,
};


class SubSetR2{
public:
    virtual bool operator==(const SubSetR2 &other) const = 0;
    virtual bool operator!=(const SubSetR2 &other) const = 0;
    virtual bool contains(const SubSetR2 &other) const = 0;

    virtual const SubSetR2 &operator~() const = 0; // Inversion
    virtual const SubSetR2 &operator|(const SubSetR2 &other) const = 0; // Union
    virtual const SubSetR2 &operator&(const SubSetR2 &other) const = 0; // Intersect
    virtual const SubSetR2 &operator-(const SubSetR2 &other) const = 0; // Subtraction
    virtual const SubSetR2 &operator^(const SubSetR2 &other) const = 0; // XOR

    virtual SubSetR2Typo tipo() const = 0; 
};


class EmptyR2 : public SubSetR2 {
private:
    constexpr EmptyR2() noexcept = default;
    
    EmptyR2(const EmptyR2&) = delete;
    EmptyR2& operator=(const EmptyR2&) = delete;
    
    EmptyR2(EmptyR2&&) = delete;
    EmptyR2& operator=(EmptyR2&&) = delete;

public:
    static const EmptyR2& getInstance() noexcept {
        static const EmptyR2 instance;
        return instance;
    }

    SubSetR2Typo tipo() const final {return SubSetR2Typo::EMPTY;};

    bool operator==(const SubSetR2 &other) const final;
    bool operator!=(const SubSetR2 &other) const final;
    bool contains(const SubSetR2 &other) const final;

    const SubSetR2 &operator~() const final;
    const SubSetR2 &operator|(const SubSetR2 &other) const final;
    const SubSetR2 &operator&(const SubSetR2 &other) const final;
    const SubSetR2 &operator-(const SubSetR2 &other) const final;
    const SubSetR2 &operator^(const SubSetR2 &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const EmptyR2 &value);
};


class WholeR2 : public SubSetR2{
private:
    constexpr WholeR2() noexcept = default;
    
    WholeR2(const WholeR2&) = delete;
    WholeR2& operator=(const WholeR2&) = delete;
    
    WholeR2(WholeR2&&) = delete;
    WholeR2& operator=(WholeR2&&) = delete;

public:
    static const WholeR2& getInstance() noexcept {
        static const WholeR2 instance;
        return instance;
    }
    
    SubSetR2Typo tipo() const final {return SubSetR2Typo::WHOLE;};

    bool operator==(const SubSetR2 &other) const final;
    bool operator!=(const SubSetR2 &other) const final;
    bool contains(const SubSetR2 &other) const final;

    const SubSetR2 &operator~() const final;
    const SubSetR2 &operator|(const SubSetR2 &other) const final;
    const SubSetR2 &operator&(const SubSetR2 &other) const final;
    const SubSetR2 &operator-(const SubSetR2 &other) const final;
    const SubSetR2 &operator^(const SubSetR2 &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const WholeR2 &value);
};



// class IPoint : public SubSetR2{

// public:
//     SubSetR2Typo tipo() const final {return SubSetR2Typo::POINT;};

// };

// class ICurve : public SubSetR2{

// public:
//     SubSetR2Typo tipo() const final {return SubSetR2Typo::CURVE;};

// };

// class IShape : public SubSetR2{

// public:
//     SubSetR2Typo tipo() const final {return SubSetR2Typo::SHAPE;};
// };


// class BoolNot : public SubSetR2{
// private:
//     const SubSetR2 *internal;
// public:
//     BoolNot(const SubSetR2 &other);

//     SubSetR2Typo tipo() const final {return SubSetR2Typo::BOOL;};

//     friend std::ostream &operator<< (std::ostream &os, const BoolNot &value);
// };


// class BoolAnd : public SubSetR2{
// private:
//     const std::vector<SubSetR2*> other;
// public:
//     BoolAnd(const std::vector<SubSetR2*> &instance);

//     SubSetR2Typo tipo() const final {return SubSetR2Typo::BOOL;};

//     friend std::ostream &operator<< (std::ostream &os, const BoolAnd &value);

// };

// class BoolOr : public SubSetR2{
// private:
//     const std::vector<SubSetR2*> other;
// public:
//     BoolOr(const std::vector<SubSetR2*> &instance);

//     SubSetR2Typo tipo() const final {return SubSetR2Typo::BOOL;};

//     friend std::ostream &operator<< (std::ostream &os, const BoolOr &value);
    
// };


static const EmptyR2& EMPTYR2 = EmptyR2::getInstance();
static const WholeR2& WHOLER2 = WholeR2::getInstance();




// BoolNot::BoolNot(const SubSetR2 &other): internal(&other){
//     if (typeid(other) == typeid(EmptyR2))
//         throw std::runtime_error("Cannot receive EmptyR2!");
//     if (typeid(other) == typeid(WholeR2))
//         throw std::runtime_error("Cannot receive WholeR2!");
// };
// BoolAnd::BoolAnd(const std::vector<SubSetR2*> &instance): other(instance){};
// BoolOr::BoolOr(const std::vector<SubSetR2*> &instance): other(instance){};








std::ostream &operator<< (std::ostream &os, const EmptyR2 &value){    
    os << "Empty";
    return os;
}

std::ostream &operator<< (std::ostream &os, const WholeR2 &value){    
    os << "Whole";
    return os;
}
// std::ostream &operator<< (std::ostream &os, const BoolNot &value){    
//     os << "NOT[" << value.internal << "]";
//     return os;
// }
// std::ostream &operator<< (std::ostream &os, const BoolAnd &value){    
//     os << "AND[";
//     return os;
// }
// std::ostream &operator<< (std::ostream &os, const BoolOr &value){    
//     os << "OR[";
//     return os;
// }




bool EmptyR2::operator==(const SubSetR2 &other) const {
    return typeid(other) == typeid(EmptyR2);
};
bool EmptyR2::operator!=(const SubSetR2 &other) const {
    return typeid(other) != typeid(EmptyR2);
};
bool WholeR2::operator==(const SubSetR2 &other) const {
    return typeid(other) == typeid(WholeR2);
};
bool WholeR2::operator!=(const SubSetR2 &other) const {
    return typeid(other) != typeid(WholeR2);
};







const SubSetR2 &EmptyR2::operator~() const {
    return WHOLER2;
};
const SubSetR2 &EmptyR2::operator|(const SubSetR2 &other) const{
    return other;
}
const SubSetR2 &EmptyR2::operator&(const SubSetR2 &other) const{
    return *this;
}
const SubSetR2 &EmptyR2::operator-(const SubSetR2 &other) const{
    return *this;
}
const SubSetR2 &EmptyR2::operator^(const SubSetR2 &other) const{
    return other;
}



const SubSetR2 &WholeR2::operator~() const {
    return EMPTYR2;
};
const SubSetR2 &WholeR2::operator|(const SubSetR2 &other) const{
    return *this;
}
const SubSetR2 &WholeR2::operator&(const SubSetR2 &other) const{
    return other;
}
const SubSetR2 &WholeR2::operator-(const SubSetR2 &other) const{
    return other.operator~();
}
const SubSetR2 &WholeR2::operator^(const SubSetR2 &other) const{
    return other.operator~();
}



bool EmptyR2::contains(const SubSetR2 &other) const {
    return typeid(other) == typeid(EmptyR2);
};
bool WholeR2::contains(const SubSetR2 &other) const {
    return true;
};





#endif
