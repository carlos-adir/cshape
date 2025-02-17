#ifndef PARAMETER_H
#define PARAMETER_H

#include <vector>
#include <iostream>
#include <unistd.h>


typedef unsigned long uint8;
typedef unsigned int uint4;
typedef unsigned short uint2;
typedef unsigned short uint1;

typedef double basetype;

class SubSetR1;
class EmptyR1;
class SingleValue;
class WholeR1;
class IntervalR1;
class DisjointR1;
class FiniteSingleValue;
class NegativeInfinity;
class PositiveInfinity;

class SubSetR1{
public:
    virtual bool operator==(const SubSetR1 &other) const = 0;
    virtual bool operator!=(const SubSetR1 &other) const = 0;
    virtual bool contains(const SubSetR1 &other) const = 0;
};


class EmptyR1 : public SubSetR1 {
private:
    constexpr EmptyR1() noexcept = default;
    
    EmptyR1(const EmptyR1&) = delete;
    EmptyR1& operator=(const EmptyR1&) = delete;
    
    EmptyR1(EmptyR1&&) = delete;
    EmptyR1& operator=(EmptyR1&&) = delete;

public:
    static const EmptyR1& getInstance() noexcept {
        static const EmptyR1 instance;
        return instance;
    }

    bool operator==(const SubSetR1 &other) const final;
    bool operator!=(const SubSetR1 &other) const final;
    bool contains(const SubSetR1 &other) const final;

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
    static const WholeR1& getInstance() noexcept {
        static const WholeR1 instance;
        return instance;
    }

    bool operator==(const SubSetR1 &other) const final;
    bool operator!=(const SubSetR1 &other) const final;
    bool contains(const SubSetR1 &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const WholeR1 &value);
};


class SingleValue : public SubSetR1{
   

public:
    bool operator==(const SubSetR1 &other) const final;
    bool operator!=(const SubSetR1 &other) const final;

    virtual bool operator<(const SingleValue &other) const = 0;
    virtual bool operator>(const SingleValue &other) const = 0;
    virtual bool operator<=(const SingleValue &other) const = 0;
    virtual bool operator>=(const SingleValue &other) const = 0;
    virtual bool operator==(const SingleValue &other) const = 0;
    virtual bool operator!=(const SingleValue &other) const = 0;

    bool contains(const SubSetR1 &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const SingleValue &value);
};

    
class NegativeInfinity : public SingleValue {
private:
    constexpr NegativeInfinity() noexcept = default;
    
    NegativeInfinity(const NegativeInfinity&) = delete;
    NegativeInfinity& operator=(const NegativeInfinity&) = delete;
    
    NegativeInfinity(NegativeInfinity&&) = delete;
    NegativeInfinity& operator=(NegativeInfinity&&) = delete;

public:
    static const NegativeInfinity& getInstance() noexcept {
        static const NegativeInfinity instance;
        return instance;
    }
    
    using SingleValue::operator==;
    using SingleValue::operator!=;
    
    bool operator==(const SingleValue &other) const final;
    bool operator!=(const SingleValue &other) const final;
    bool operator<(const SingleValue &other) const final;
    bool operator<=(const SingleValue &other) const final;
    bool operator>=(const SingleValue &other) const final;
    bool operator>(const SingleValue &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const NegativeInfinity &value);
};

class PositiveInfinity : public SingleValue {
private:
    constexpr PositiveInfinity() noexcept = default;
    
    PositiveInfinity(const PositiveInfinity&) = delete;
    PositiveInfinity& operator=(const PositiveInfinity&) = delete;
    
    PositiveInfinity(PositiveInfinity&&) = delete;
    PositiveInfinity& operator=(PositiveInfinity&&) = delete;

public:
    static const PositiveInfinity& getInstance() noexcept {
        static const PositiveInfinity instance;
        return instance;
    }

    using SingleValue::operator==;
    using SingleValue::operator!=;

    bool operator==(const SingleValue &other) const final;
    bool operator!=(const SingleValue &other) const final;
    bool operator<(const SingleValue &other) const final;
    bool operator<=(const SingleValue &other) const final;
    bool operator>=(const SingleValue &other) const final;
    bool operator>(const SingleValue &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const PositiveInfinity &value);
};


class FiniteSingleValue : public SingleValue {
private:
    const basetype internal;

public:
    FiniteSingleValue(const basetype &value);
    FiniteSingleValue(const FiniteSingleValue &other); // Copy Finite Single Value
    ~FiniteSingleValue();
    
    using SingleValue::operator==;
    using SingleValue::operator!=;

    bool operator<(const SingleValue &other) const final;
    bool operator<=(const SingleValue &other) const final;
    bool operator>=(const SingleValue &other) const final;
    bool operator>(const SingleValue &other) const final;
    bool operator==(const SingleValue &other) const final;
    bool operator!=(const SingleValue &other) const final;

    virtual bool operator<(const FiniteSingleValue &other) const final;
    virtual bool operator<=(const FiniteSingleValue &other) const final;
    virtual bool operator>=(const FiniteSingleValue &other) const final;
    virtual bool operator>(const FiniteSingleValue &other) const final;
    virtual bool operator==(const FiniteSingleValue &other) const final;
    virtual bool operator!=(const FiniteSingleValue &other) const final;

    virtual const FiniteSingleValue operator+(const FiniteSingleValue &other) const final;
    virtual const FiniteSingleValue operator-(const FiniteSingleValue &other) const final;
    virtual const FiniteSingleValue operator*(const FiniteSingleValue &other) const final;
    virtual const FiniteSingleValue operator/(const FiniteSingleValue &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const FiniteSingleValue &other);
};

class IntervalR1 : public SubSetR1 {
private:
    const FiniteSingleValue *start, *end;
public:
    IntervalR1(const FiniteSingleValue &start, const FiniteSingleValue &end);
    IntervalR1(const NegativeInfinity &start, const FiniteSingleValue &end);
    IntervalR1(const FiniteSingleValue &start, const PositiveInfinity &end);
    static IntervalR1 lower(const FiniteSingleValue &endval);
    static IntervalR1 bigger(const FiniteSingleValue &startval);

    bool operator==(const SubSetR1 &other) const final;
    bool operator!=(const SubSetR1 &other) const final;
    virtual bool operator==(const IntervalR1 &other) const final;
    virtual bool operator!=(const IntervalR1 &other) const final;

    bool contains(const SubSetR1 &other) const final;
    virtual bool contains(const FiniteSingleValue &other) const final;
    virtual bool contains(const IntervalR1 &other) const final;
    virtual bool contains(const DisjointR1 &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const IntervalR1 &value);
};

class DisjointR1 : public SubSetR1 {
public:
    const std::vector<FiniteSingleValue*> finites;
    const std::vector<IntervalR1*> intervals;

    DisjointR1(const std::vector<FiniteSingleValue*> &finites);
    DisjointR1(const std::vector<IntervalR1*> &intervals);
    DisjointR1(const std::vector<FiniteSingleValue*> &finites, const std::vector<IntervalR1*> &intervals);
    
    bool operator==(const SubSetR1 &other) const final;
    bool operator!=(const SubSetR1 &other) const final;
    virtual bool operator==(const DisjointR1 &other) const final;
    virtual bool operator!=(const DisjointR1 &other) const final;
    bool contains(const SubSetR1 &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const DisjointR1 &value);
};

static const NegativeInfinity& NEGINF = NegativeInfinity::getInstance();
static const PositiveInfinity& POSINF = PositiveInfinity::getInstance();
static const EmptyR1& EMPTYR1 = EmptyR1::getInstance();
static const WholeR1& WHOLER1 = WholeR1::getInstance();


//
//
//
//   CONSTRUCTOR IMPLEMENTATIONS
//
//
//

FiniteSingleValue::FiniteSingleValue(const basetype &value):
    internal(basetype(value)) {
        std::cout << "Creating FiniteSingleValue: " << value << std::endl;
};
FiniteSingleValue::FiniteSingleValue(const FiniteSingleValue &other):
    FiniteSingleValue(other.internal) {};
FiniteSingleValue::~FiniteSingleValue(){
    std::cout << "Deleting FiniteSingleValue: " << internal << std::endl;
};

IntervalR1::IntervalR1(const FiniteSingleValue &start, const FiniteSingleValue &end):
    start(&start), end(&end) {
        if(end <= start)
            throw std::invalid_argument("In interval [start, end], must have 'start < end'");
    };
IntervalR1::IntervalR1(const NegativeInfinity &start, const FiniteSingleValue &end):
    start(NULL), end(&end) {};
IntervalR1::IntervalR1(const FiniteSingleValue &start, const PositiveInfinity &end):
    start(&start), end(NULL) {};


DisjointR1::DisjointR1(const std::vector<FiniteSingleValue*> &finites):
    finites(finites) {};
DisjointR1::DisjointR1(const std::vector<IntervalR1*> &intervals):
    intervals(intervals) {};
DisjointR1::DisjointR1(const std::vector<FiniteSingleValue*> &finites, const std::vector<IntervalR1*> &intervals):
    finites(finites), intervals(intervals) {};


// 
//
//
//  Printing implementations
// 
//
//


std::ostream &operator<< (std::ostream &os, const EmptyR1 &value){    
    os << "{}";
    return os;
}

std::ostream &operator<< (std::ostream &os, const WholeR1 &value){    
    os << "(-inf, +inf)";
    return os;
}

std::ostream &operator<< (std::ostream &os, const NegativeInfinity &value){    
    os << "-inf";
    return os;
}

std::ostream &operator<< (std::ostream &os, const PositiveInfinity &value){    
    os << "+inf";
    return os;
}

std::ostream &operator<< (std::ostream &os, const FiniteSingleValue &value){    
    os << value.internal;
    return os;
}

std::ostream &operator<< (std::ostream &os, const IntervalR1 &value){
    if (value.start)
        os << "[" << *value.start;
    else
        os << "(-inf";
    os << ", ";
    if (value.end)
        os << *value.end << "]";
    else
        os << "+inf)";
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
    return dynamic_cast<const EmptyR1*>(&other);
};
bool EmptyR1::operator!=(const SubSetR1 &other) const {
    return !dynamic_cast<const EmptyR1*>(&other);
};
bool WholeR1::operator==(const SubSetR1 &other) const {
    return dynamic_cast<const WholeR1*>(&other);
};
bool WholeR1::operator!=(const SubSetR1 &other) const {
    return !dynamic_cast<const WholeR1*>(&other);
};

bool SingleValue::operator==(const SubSetR1 &other) const {
    const SingleValue *single = dynamic_cast<const SingleValue*>(&other);
    return single && this->operator==(*single);
};
bool SingleValue::operator!=(const SubSetR1 &other) const {
    const SingleValue *single = dynamic_cast<const SingleValue*>(&other);
    return !single || this->operator!=(*single);
};

bool NegativeInfinity::operator==(const SingleValue &other) const {
    return dynamic_cast<const NegativeInfinity*>(&other);
};
bool NegativeInfinity::operator!=(const SingleValue &other) const {
    return !dynamic_cast<const NegativeInfinity*>(&other);
};
bool PositiveInfinity::operator==(const SingleValue &other) const {
    return dynamic_cast<const PositiveInfinity*>(&other);
};
bool PositiveInfinity::operator!=(const SingleValue &other) const {
    return !dynamic_cast<const PositiveInfinity*>(&other);
};
bool FiniteSingleValue::operator==(const SingleValue &other) const {
    const FiniteSingleValue *finite = dynamic_cast<const FiniteSingleValue*>(&other);
    return finite && this->operator==(*finite);
};
bool FiniteSingleValue::operator!=(const SingleValue &other) const {
    const FiniteSingleValue *finite = dynamic_cast<const FiniteSingleValue*>(&other);
    return !finite || this->operator!=(*finite);
};

bool IntervalR1::operator==(const SubSetR1 &other) const {
    const IntervalR1 *interval = dynamic_cast<const IntervalR1*>(&other);
    return interval && this->operator==(*interval);
};
bool IntervalR1::operator!=(const SubSetR1 &other) const {
    const IntervalR1 *interval = dynamic_cast<const IntervalR1*>(&other);
    return !interval || this->operator!=(*interval);
};
bool IntervalR1::operator==(const IntervalR1 &other) const {
    return *start == *other.start && *end == *other.end;
};
bool IntervalR1::operator!=(const IntervalR1 &other) const {
    return *start != *other.start || *end != *other.end;
};

bool DisjointR1::operator==(const SubSetR1 &other) const {
    const DisjointR1 *unionsubsets = dynamic_cast<const DisjointR1*>(&other);
    return unionsubsets && this->operator==(*unionsubsets);
};
bool DisjointR1::operator!=(const SubSetR1 &other) const {
    const DisjointR1 *unionsubsets = dynamic_cast<const DisjointR1*>(&other);
    return !unionsubsets || this->operator!=(*unionsubsets);
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
//   RELATIVE POSITION
//
//
//


bool NegativeInfinity::operator<(const SingleValue &other) const {
    return !dynamic_cast<const NegativeInfinity*>(&other);
};
bool NegativeInfinity::operator<=(const SingleValue &other) const {
    return true;
};
bool NegativeInfinity::operator>=(const SingleValue &other) const {
    return dynamic_cast<const NegativeInfinity*>(&other);
};
bool NegativeInfinity::operator>(const SingleValue &other) const {
    return false;
};


bool PositiveInfinity::operator<(const SingleValue &other) const {
    return false;
};
bool PositiveInfinity::operator<=(const SingleValue &other) const {    
    return dynamic_cast<const PositiveInfinity*>(&other);
};
bool PositiveInfinity::operator>=(const SingleValue &other) const {
    return true;
};
bool PositiveInfinity::operator>(const SingleValue &other) const {
    return !dynamic_cast<const PositiveInfinity*>(&other);
};


bool FiniteSingleValue::operator<(const SingleValue &other) const {
    if (typeid(other) == typeid(FiniteSingleValue))
        return this->operator<(*dynamic_cast<const FiniteSingleValue*>(&other));
    return typeid(other) == typeid(PositiveInfinity);
};
bool FiniteSingleValue::operator<=(const SingleValue &other) const {
    if (typeid(other) == typeid(FiniteSingleValue))
        return this->operator<=(*dynamic_cast<const FiniteSingleValue*>(&other));
    return typeid(other) == typeid(PositiveInfinity);
};
bool FiniteSingleValue::operator>=(const SingleValue &other) const {
    if (typeid(other) == typeid(FiniteSingleValue))
        return this->operator>=(*dynamic_cast<const FiniteSingleValue*>(&other));
    return typeid(other) == typeid(NegativeInfinity);
};
bool FiniteSingleValue::operator>(const SingleValue &other) const {
    if (typeid(other) == typeid(FiniteSingleValue))
        return this->operator>(*dynamic_cast<const FiniteSingleValue*>(&other));
    return typeid(other) == typeid(NegativeInfinity);
};




//
//
//
//  STANDARD FINITE VALUE OPERATIONS
//
//
//

bool FiniteSingleValue::operator==(const FiniteSingleValue &other) const {
    return this->internal == other.internal;
};
bool FiniteSingleValue::operator!=(const FiniteSingleValue &other) const {
    return this->internal != other.internal;
};
bool FiniteSingleValue::operator<(const FiniteSingleValue &other) const {
    return internal < other.internal;
};
bool FiniteSingleValue::operator<=(const FiniteSingleValue &other) const {
    return internal <= other.internal;
};
bool FiniteSingleValue::operator>=(const FiniteSingleValue &other) const {
    return internal >= other.internal;
};
bool FiniteSingleValue::operator>(const FiniteSingleValue &other) const {
    return internal > other.internal;
};

const FiniteSingleValue FiniteSingleValue::operator+(const FiniteSingleValue &other) const{
    return FiniteSingleValue(this->internal + other.internal);
}
const FiniteSingleValue FiniteSingleValue::operator-(const FiniteSingleValue &other) const{
    return FiniteSingleValue(this->internal - other.internal);
}
const FiniteSingleValue FiniteSingleValue::operator*(const FiniteSingleValue &other) const{
    return FiniteSingleValue(this->internal * other.internal);
}
const FiniteSingleValue FiniteSingleValue::operator/(const FiniteSingleValue &other) const{
    return FiniteSingleValue(this->internal / other.internal);
}


// 
//
//
//  Contains implementations
// 
//
//


bool EmptyR1::contains(const SubSetR1 &other) const {
    return dynamic_cast<const EmptyR1*>(&other);
}

bool WholeR1::contains(const SubSetR1 &other) const {
    return true;
}

bool SingleValue::contains(const SubSetR1 &other) const {
    if (typeid(other) != typeid(*this))
        return typeid(other) == typeid(EmptyR1);
    if (typeid(other) != typeid(FiniteSingleValue))
        return true;
    return this->operator==(*dynamic_cast<const FiniteSingleValue*>(&other));
};



bool IntervalR1::contains(const SubSetR1 &other) const {
    if (typeid(other) == typeid(FiniteSingleValue))
        return this->contains(*dynamic_cast<const FiniteSingleValue*>(&other));
    if (typeid(other) == typeid(NegativeInfinity))
        return !this->start;
    if (typeid(other) == typeid(PositiveInfinity))
        return !this->end;
    if (typeid(other) == typeid(IntervalR1))
        return this->contains(*dynamic_cast<const IntervalR1*>(&other));
    if (typeid(other) == typeid(DisjointR1))
        return this->contains(*dynamic_cast<const DisjointR1*>(&other));
    return typeid(other) == typeid(EmptyR1);
};


bool IntervalR1::contains(const FiniteSingleValue &other) const {
    if (this->start && other < *this->start)
        return false;
    if (this->end && *this->end < other)
        return false;
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
        if (!this->contains(*other.finites[i]))
            return false;
    for (uint1 i = 0; i < other.intervals.size(); i++)
        if (!this->contains(*other.intervals[i]))
            return false;
    return true;
};


bool DisjointR1::contains(const SubSetR1 &other) const {
    for (uint1 i = 0; i < this->intervals.size(); i++)
        if (this->intervals[i]->contains(other))
            return true;
    for (uint1 i = 0; i < this->finites.size(); i++)
        if (this->finites[i]->contains(other))
            return true;
    return false;
};






#endif
