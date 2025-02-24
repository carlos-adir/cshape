#ifndef UNIDIMBOOL_H
#define UNIDIMBOOL_H

#include <vector>
#include <iostream>
#include <unistd.h>
#include <memory>

#include "scalar.h"

typedef unsigned long uint8;
typedef unsigned int uint4;
typedef unsigned short uint2;
typedef unsigned short uint1;

class SubSetR1;
class EmptyR1;
class WholeR1;
class IntervalR1;
class DisjointR1;
class SingleValue;


class SubSetR1{
public:
    virtual bool operator==(const SubSetR1 &other) const = 0;
    virtual bool operator!=(const SubSetR1 &other) const = 0;

    virtual bool contains(const SubSetR1 &other) const = 0;
    virtual bool contains(const basetype &other) const = 0;
};


class EmptyR1 : public SubSetR1 {
private:
    constexpr EmptyR1() noexcept = default;
    
    EmptyR1(const EmptyR1&) = delete;
    EmptyR1& operator=(const EmptyR1&) = delete;
    
    EmptyR1(EmptyR1&&) = delete;
    EmptyR1& operator=(EmptyR1&&) = delete;

public:
    static const std::string STR;

    static const EmptyR1& getInstance() noexcept {
        static const EmptyR1 instance;
        return instance;
    }

    bool operator==(const SubSetR1 &other) const final;
    bool operator!=(const SubSetR1 &other) const final;

    bool contains(const SubSetR1 &other) const final;
    bool contains(const basetype &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const EmptyR1 &value);
};


class WholeR1 : public SubSetR1{
private:
    constexpr WholeR1() noexcept = default;
    
    WholeR1(const WholeR1&) = delete;
    WholeR1& operator=(const WholeR1&) = delete;
    
    WholeR1(WholeR1&&) = delete;
    WholeR1& operator=(WholeR1&&) = delete;

public:
    static const std::string STR;

    static const WholeR1& getInstance() noexcept {
        static const WholeR1 instance;
        return instance;
    }

    bool operator==(const SubSetR1 &other) const final;
    bool operator!=(const SubSetR1 &other) const final;

    bool contains(const basetype &other) const final;
    bool contains(const SubSetR1 &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const WholeR1 &value);
};


class SingleValue : public SubSetR1{
public:

    const basetype internal;
    
    SingleValue();
    SingleValue(const basetype &value);
    SingleValue(const SingleValue &other); // Copy Finite Single Value
    ~SingleValue();

    bool operator==(const SubSetR1 &other) const final;
    bool operator!=(const SubSetR1 &other) const final;
    virtual bool operator==(const SingleValue &other) const final;
    virtual bool operator!=(const SingleValue &other) const final;

    bool contains(const basetype &other) const final;
    bool contains(const SubSetR1 &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const SingleValue &value);
};



class IntervalR1 : public SubSetR1 {
private:
    const std::unique_ptr<basetype> start, end;
    const bool closed_left, closed_right;
public:
    IntervalR1(std::unique_ptr<basetype> start,
               std::unique_ptr<basetype> end,
               const bool closed_left = true,
               const bool closed_right = true);
    IntervalR1(const basetype &start,
               const basetype &end,
               const bool closed_left = true,
               const bool closed_right = true);
    IntervalR1(const NegativeInfinity &start,
               const basetype &end,
               const bool closed_left = true,
               const bool closed_right = true);
    IntervalR1(const basetype &start,
               const PositiveInfinity &end,
               const bool closed_left = true,
               const bool closed_right = true);
    IntervalR1(const IntervalR1 &other);

    static IntervalR1 lower(const basetype &endval,
                            const bool closed = true);
    static IntervalR1 bigger(const basetype &startval,
                             const bool closed = true);

    bool operator==(const SubSetR1 &other) const final;
    bool operator!=(const SubSetR1 &other) const final;
    virtual bool operator==(const IntervalR1 &other) const final;
    virtual bool operator!=(const IntervalR1 &other) const final;

    bool contains(const basetype &other) const final;
    bool contains(const SubSetR1 &other) const final;
    virtual bool contains(const SingleValue &other) const final;
    virtual bool contains(const IntervalR1 &other) const final;
    virtual bool contains(const DisjointR1 &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const IntervalR1 &value);
};

class DisjointR1 : public SubSetR1 {
public:
    const std::vector<basetype> finites;
    const std::vector<IntervalR1> intervals;

    DisjointR1(const std::vector<basetype> &finites);
    DisjointR1(const std::vector<IntervalR1> &intervals);
    DisjointR1(const std::vector<basetype> &finites, const std::vector<IntervalR1> &intervals);
    
    bool operator==(const SubSetR1 &other) const final;
    bool operator!=(const SubSetR1 &other) const final;
    virtual bool operator==(const DisjointR1 &other) const final;
    virtual bool operator!=(const DisjointR1 &other) const final;
    
    bool contains(const basetype &other) const final;
    bool contains(const SubSetR1 &other) const final;
    virtual bool contains(const SingleValue &other) const final;
    virtual bool contains(const IntervalR1 &other) const final;
    virtual bool contains(const DisjointR1 &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const DisjointR1 &value);
};

static const EmptyR1& EMPTYR1 = EmptyR1::getInstance();
static const WholeR1& WHOLER1 = WholeR1::getInstance();


//
//
//
//   CONSTRUCTOR IMPLEMENTATIONS
//
//
//

SingleValue::SingleValue():
    internal(basetype(0)) {};
SingleValue::SingleValue(const basetype &value):
    internal(basetype(value)) {};
SingleValue::SingleValue(const SingleValue &other):
    SingleValue(other.internal) {};
SingleValue::~SingleValue(){};


IntervalR1::IntervalR1(std::unique_ptr<basetype> start,
                       std::unique_ptr<basetype> end,
                       const bool closed_left,
                       const bool closed_right):
    start(std::move(start)),
    end(std::move(end)),
    closed_left(closed_left),
    closed_right(closed_right) {
};

IntervalR1::IntervalR1(const basetype &start,
                       const basetype &end,
                       const bool closed_left,
                       const bool closed_right):
    IntervalR1(std::make_unique<basetype>(start),
               std::make_unique<basetype>(end),
               closed_left,
               closed_right) {
    if(end <= start)
        throw std::invalid_argument("In interval [start, end], must have 'start < end'");
};

IntervalR1::IntervalR1(const NegativeInfinity &start,
                       const basetype &end,
                       const bool closed_left,
                       const bool closed_right):
    IntervalR1(nullptr,
               std::make_unique<basetype>(end),
               false,
               closed_right) {};

IntervalR1::IntervalR1(const basetype &start,
                       const PositiveInfinity &end,
                       const bool closed_left,
                       const bool closed_right):
    IntervalR1(std::make_unique<basetype>(start),
               nullptr,
               closed_left,
               false) {};

IntervalR1::IntervalR1(const IntervalR1 &other): // Copy constructor
    IntervalR1(other.start == nullptr ? nullptr : std::make_unique<basetype>(*other.start),
               other.end == nullptr ? nullptr : std::make_unique<basetype>(*other.end),
               other.closed_left,
               other.closed_right){};


IntervalR1 IntervalR1::lower(const basetype &endval,
                             const bool closed){
    return IntervalR1(NEGINF, endval, false, closed);
};
IntervalR1 IntervalR1::bigger(const basetype &startval,
                              const bool closed){
return IntervalR1(startval, POSINF, closed, false);
};


DisjointR1::DisjointR1(const std::vector<basetype> &finites):
    finites(finites) {};
DisjointR1::DisjointR1(const std::vector<IntervalR1> &intervals):
    intervals(intervals) {};
DisjointR1::DisjointR1(const std::vector<basetype> &finites, const std::vector<IntervalR1> &intervals):
    finites(finites), intervals(intervals) {};


// 
//
//
//  Printing implementations
// 
//
//


std::ostream &operator<< (std::ostream &os, const EmptyR1 &value){    
    os << EmptyR1::STR;
    return os;
}

std::ostream &operator<< (std::ostream &os, const WholeR1 &value){    
    os << WholeR1::STR;
    return os;
}

std::ostream &operator<< (std::ostream &os, const SingleValue &value){    
    os << value.internal;
    return os;
}

std::ostream &operator<< (std::ostream &os, const IntervalR1 &value){
    os << (value.closed_left ? "[" : "(");
    if (value.start != NULL)
        os << *value.start;
    else
        os << NEGINF.STR;
    os << ", ";
    if (value.end != NULL)
        os << *value.end;
    else
        os << POSINF.STR;
    os << (value.closed_right ? "]" : ")");
    return os;
}


//
//
//
//  EQUALITY COMPARATION
//
//
//


bool EmptyR1::operator==(const SubSetR1 &other) const {
    return typeid(other) == typeid(EmptyR1);
};
bool EmptyR1::operator!=(const SubSetR1 &other) const {
    return typeid(other) != typeid(EmptyR1);
};
bool WholeR1::operator==(const SubSetR1 &other) const {
    return typeid(other) == typeid(WholeR1);
};
bool WholeR1::operator!=(const SubSetR1 &other) const {
    return typeid(other) != typeid(WholeR1);
};



bool SingleValue::operator==(const SubSetR1 &other) const {
    if (typeid(other) != typeid(SingleValue))
        return false;
    return this->operator==(*dynamic_cast<const SingleValue*>(&other));
};
bool SingleValue::operator!=(const SubSetR1 &other) const {
    if (typeid(other) != typeid(SingleValue))
        return true;
    return this->operator!=(*dynamic_cast<const SingleValue*>(&other));
};
bool SingleValue::operator==(const SingleValue &other) const {
    return this->internal == other.internal;
};
bool SingleValue::operator!=(const SingleValue &other) const {
    return this->internal != other.internal;
};



bool IntervalR1::operator==(const SubSetR1 &other) const {
    if (typeid(other) != typeid(IntervalR1))
        return false;
    return this->operator==(*dynamic_cast<const IntervalR1*>(&other));
};
bool IntervalR1::operator!=(const SubSetR1 &other) const {
    if (typeid(other) != typeid(IntervalR1))
        return true;
    return this->operator!=(*dynamic_cast<const IntervalR1*>(&other));
};
bool IntervalR1::operator==(const IntervalR1 &other) const {
    return *start == *other.start && *end == *other.end;
};
bool IntervalR1::operator!=(const IntervalR1 &other) const {
    return *start != *other.start || *end != *other.end;
};

bool DisjointR1::operator==(const SubSetR1 &other) const {
    if (typeid(other) != typeid(IntervalR1))
        return false;
    return this->operator==(*dynamic_cast<const DisjointR1*>(&other));
};
bool DisjointR1::operator!=(const SubSetR1 &other) const {
    if (typeid(other) != typeid(IntervalR1))
        return true;
    return this->operator!=(*dynamic_cast<const DisjointR1*>(&other));
};
bool DisjointR1::operator==(const DisjointR1 &other) const {
    throw std::runtime_error("Not yet implemented");
    return false;
};
bool DisjointR1::operator!=(const DisjointR1 &other) const {
    throw std::runtime_error("Not yet implemented");
    return false;
};



// 
//
//
//  Contains implementations
// 
//
//



bool EmptyR1::contains(const basetype &other) const {
    return false;
}

bool WholeR1::contains(const basetype &other) const {
    return true;
}

bool SingleValue::contains(const basetype &other) const {
    return this->internal == other;
}

bool IntervalR1::contains(const basetype &other) const {
    return this->contains(SingleValue(other));
}

bool DisjointR1::contains(const basetype &other) const {
    return this->contains(SingleValue(other));
}







bool EmptyR1::contains(const SubSetR1 &other) const {
    return typeid(other) == typeid(EmptyR1);
}

bool WholeR1::contains(const SubSetR1 &other) const {
    return true;
}

bool SingleValue::contains(const SubSetR1 &other) const {
    if (typeid(other) == typeid(SingleValue))
        return this->operator==(*dynamic_cast<const SingleValue*>(&other));
    return typeid(other) == typeid(EmptyR1);
};


bool IntervalR1::contains(const SubSetR1 &other) const {
    if (typeid(other) == typeid(SingleValue))
        return this->contains(*dynamic_cast<const SingleValue*>(&other));
    if (typeid(other) == typeid(IntervalR1))
        return this->contains(*dynamic_cast<const IntervalR1*>(&other));
    if (typeid(other) == typeid(DisjointR1))
        return this->contains(*dynamic_cast<const DisjointR1*>(&other));
    return typeid(other) == typeid(EmptyR1);
};


bool DisjointR1::contains(const SubSetR1 &other) const {
    if (typeid(other) == typeid(DisjointR1))
        return this->contains(*dynamic_cast<const DisjointR1*>(&other));
    if (typeid(other) == typeid(IntervalR1))
        return this->contains(*dynamic_cast<const IntervalR1*>(&other));
    if (typeid(other) == typeid(SingleValue))
        return this->contains(*dynamic_cast<const SingleValue*>(&other));
    return typeid(other) == typeid(EmptyR1());
};












bool IntervalR1::contains(const SingleValue &other) const {
    if (this->start != NULL){
        if (other.internal < *this->start)
            return false;
        if (!this->closed_left && other.internal == *this->start)
            return false;
    }
    if (this->end != NULL){
        if (*this->end < other.internal)
            return false;
        if (!this->closed_right && other.internal == *this->start)
            return false;
    }
    return true;
};

bool IntervalR1::contains(const IntervalR1 &other) const {
    if (other.start == NULL && this->start != NULL)
        return false;
    if (other.end == NULL && this->end != NULL)
        return false;
    if (this->start && *other.start < *this->start)
        return false;
    if (this->end && *this->end < *other.end)
        return false;
    return true;
};

bool IntervalR1::contains(const DisjointR1 &other) const {
    for (uint1 i = 0; i < other.finites.size(); i++)
        if (!this->contains(other.finites[i]))
            return false;
    for (uint1 i = 0; i < other.intervals.size(); i++)
        if (!this->contains(other.intervals[i]))
            return false;
    return true;
};




bool DisjointR1::contains(const SingleValue &other) const {
    for (uint1 i = 0; i < this->intervals.size(); i++)
        if ((this->intervals[i]).contains(other))
            return true;
    for (uint1 i = 0; i < this->finites.size(); i++)
        if (this->finites[i] == other.internal)
            return true;
    return false;
};

bool DisjointR1::contains(const IntervalR1 &other) const {
    for (uint1 i = 0; i < this->intervals.size(); i++)
        if ((this->intervals[i]).contains(other))
            return true;
    return false;
};

bool DisjointR1::contains(const DisjointR1 &other) const {
    for (uint i = 0; i < other.intervals.size(); i++)
        if (!this->contains(other.intervals[i]))
            return false;
    for (uint i = 0; i < other.finites.size(); i++)
        if (!this->contains(other.finites[i]))
            return false;
    return true;
};




bool operator==(const basetype &lhs, const SubSetR1 &rhs) {
    if (typeid(rhs) != typeid(SingleValue))
        return false;
    return dynamic_cast<const SingleValue*>(&rhs)->internal == lhs;
};
bool operator!=(const basetype &lhs, const SubSetR1 &rhs) {
    if (typeid(rhs) != typeid(SingleValue))
        return true;
    return dynamic_cast<const SingleValue*>(&rhs)->internal == lhs;
};



std::vector<basetype> finite_set_from_str(const std::string &str){
    std::vector<basetype> finites;
    for (size_t i = 0; i < str.size(); ++i){
        size_t j = i + 1;
        while (j < str.size() && str[j] != ',' && str[j] != '}')
            ++j;
        const std::string sub = str.substr(i+1, j-i-1);
        const basetype finite = string_to_basetype(sub);
        finites.push_back(finite);
        i = j+1;
    }
    return finites;
}

IntervalR1 interval_from_str(const std::string &str){
    const size_t size = str.size();
    const bool closed_left = (str[0] == '[');
    const bool closed_right = (str[size-1] == ']');

    size_t comma = 0;
    while (comma < size && str[comma] != ',')
        ++comma;
    const std::string left = str.substr(1, comma - 1);
    const std::string righ = str.substr(comma+1, size - comma - 2);
    // Check for infinity
    if (left.find(NEGINF.STR) != std::string::npos){
        const basetype end = string_to_basetype(righ); 
        return IntervalR1::bigger(end, closed_right);
    }
    if (righ.find(POSINF.STR) != std::string::npos){
        const basetype sta = string_to_basetype(left); 
        return IntervalR1::lower(sta, closed_left);
    }
    const basetype sta = string_to_basetype(left); 
    const basetype end = string_to_basetype(righ); 
    const IntervalR1 interval(sta, end, closed_left, closed_right);
    return interval;
}



bool valid_string_to_convert_to_subset(const std::string &str){
    bool braces = false, brackets = false;
    for (size_t i = 0; i < str.size(); i++){
        switch (str[i])
        {
            case ' ':
                break;
            case 'U':
                if (braces || brackets)
                    return false;
                break;
            case ',':
                if (!(braces || brackets))
                    return false;
                break;
            case '{':
                if (braces)
                    return false;
                braces = true;
                break;
            case '}':
                if (!braces)
                    return false;
                braces = false;
                break;
            case '(':
            case '[':
                if (brackets)
                    return false;
                brackets = true;
                break;
            case ')':
            case ']':
                if (!brackets)
                    return false;
                brackets = false;
                break;
            default:
                break;
        }
    }
    return true;
}



SubSetR1 const *string_to_subset(const std::string &str){
    if (!valid_string_to_convert_to_subset(str))
        throw std::invalid_argument("Invalid string to convert to subset");

    if (str == EmptyR1::STR)
        return &EMPTYR1;
    if (str == WholeR1::STR)
        return &WHOLER1;
    std::vector<basetype> finites;
    std::vector<IntervalR1> intervs;
    
    const size_t size = str.size();
    for (size_t sta = 0; sta < size; ++sta){
        if (str[sta] != '{' && str[sta] == '[' && str[sta] == '(')
            continue;
        size_t end = sta + 1;
        while (end < size && str[end] != '}' && str[end] != ')' && str[end] != ']')
            ++end;
        const std::string sub = str.substr(sta, end-sta + 1);
        if (sub[0] != '{'){
            const IntervalR1 interval = interval_from_str(sub);
            intervs.push_back(interval);
        }else{
            const std::vector<basetype> new_finites = finite_set_from_str(sub);
            finites.insert(finites.end(),new_finites.begin(), new_finites.end());
        }
        sta = end + 1;
    }
    if (finites.size() == 1 && intervs.size() == 0)
        return new SingleValue(finites[0]);
    if (finites.size() == 0 && intervs.size() == 1)
        return new IntervalR1(intervs[0]);
    return new DisjointR1(finites, intervs);
}

const std::string EmptyR1::STR = "{}";
const std::string WholeR1::STR = "(" + NegativeInfinity::STR + ", " + PositiveInfinity::STR + ")";




#endif
