#ifndef PARAMETER_H
#define PARAMETER_H

#include <vector>
#include <iostream>
#include <unistd.h>


typedef unsigned long uint8;
typedef unsigned int uint4;
typedef unsigned short uint2;
typedef unsigned short uint1;

class SubSetRealLine;
class EmptyParam;
class SingleValue;
class WholeParam;
class Interval;
class UnionSubSets;
class FiniteSingleValue;
class NegativeInfinity;
class PositiveInfinity;

class SubSetRealLine{
public:
    virtual bool operator==(const SubSetRealLine &other) const = 0;
    virtual bool operator!=(const SubSetRealLine &other) const = 0;
    virtual bool contains(const SubSetRealLine &other) const = 0;
};




class EmptyParam : public SubSetRealLine {
private:
    constexpr EmptyParam() noexcept = default;
    
    EmptyParam(const EmptyParam&) = delete;
    EmptyParam& operator=(const EmptyParam&) = delete;
    
    EmptyParam(EmptyParam&&) = delete;
    EmptyParam& operator=(EmptyParam&&) = delete;

public:
    static const EmptyParam& getInstance() noexcept {
        static const EmptyParam instance;
        return instance;
    }

    bool operator==(const SubSetRealLine &other) const final;
    bool operator!=(const SubSetRealLine &other) const final;
    bool contains(const SubSetRealLine &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const EmptyParam &value);
};


class WholeParam : public SubSetRealLine{
private:
    constexpr WholeParam() noexcept = default;
    
    WholeParam(const WholeParam&) = delete;
    WholeParam& operator=(const WholeParam&) = delete;
    
    WholeParam(WholeParam&&) = delete;
    WholeParam& operator=(WholeParam&&) = delete;

public:
    static const WholeParam& getInstance() noexcept {
        static const WholeParam instance;
        return instance;
    }

    bool operator==(const SubSetRealLine &other) const final;
    bool operator!=(const SubSetRealLine &other) const final;
    bool contains(const SubSetRealLine &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const WholeParam &value);
};


class SingleValue : public SubSetRealLine{
   

public:
    bool operator==(const SubSetRealLine &other) const final;
    bool operator!=(const SubSetRealLine &other) const final;

    virtual bool operator<(const SingleValue &other) const = 0;
    virtual bool operator>(const SingleValue &other) const = 0;
    virtual bool operator<=(const SingleValue &other) const = 0;
    virtual bool operator>=(const SingleValue &other) const = 0;
    virtual bool operator==(const SingleValue &other) const = 0;
    virtual bool operator!=(const SingleValue &other) const = 0;

    bool contains(const SubSetRealLine &other) const final;

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
    const double *internal;

public:
    FiniteSingleValue(const double *value);
    FiniteSingleValue(const double &value);
    
    using SingleValue::operator==;
    using SingleValue::operator!=;

    bool operator<(const SingleValue &other) const final;
    bool operator<=(const SingleValue &other) const final;
    bool operator>=(const SingleValue &other) const final;
    bool operator>(const SingleValue &other) const final;
    bool operator==(const SingleValue &other) const final;
    bool operator!=(const SingleValue &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const FiniteSingleValue &other);
};

class Interval : public SubSetRealLine {
public:
    const SingleValue *start, *end;

    Interval(const SingleValue *start, const SingleValue *end);
    Interval(const SingleValue &start, const SingleValue &end);

    bool operator==(const SubSetRealLine &other) const final;
    bool operator!=(const SubSetRealLine &other) const final;
    virtual bool operator==(const Interval &other) const final;
    virtual bool operator!=(const Interval &other) const final;


    bool contains(const SubSetRealLine &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const Interval &value);
};

class UnionSubSets : public SubSetRealLine {
public:
    const std::vector<FiniteSingleValue*> singles;
    const std::vector<Interval*> intervals;

    UnionSubSets(const std::vector<FiniteSingleValue*> &singles);
    UnionSubSets(const std::vector<Interval*> &intervals);
    UnionSubSets(const std::vector<FiniteSingleValue*> &singles, const std::vector<Interval*> &intervals);
    
    bool operator==(const SubSetRealLine &other) const final;
    bool operator!=(const SubSetRealLine &other) const final;
    virtual bool operator==(const UnionSubSets &other) const final;
    virtual bool operator!=(const UnionSubSets &other) const final;
    bool contains(const SubSetRealLine &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const UnionSubSets &value);
};

static const NegativeInfinity& BOTINF = NegativeInfinity::getInstance();
static const PositiveInfinity& TOPINF = PositiveInfinity::getInstance();
static const EmptyParam& EMPTY = EmptyParam::getInstance();
static const WholeParam& WHOLE = WholeParam::getInstance();


//
//
//
//   CONSTRUCTOR IMPLEMENTATIONS
//
//
//

FiniteSingleValue::FiniteSingleValue(const double *value)
    : internal(value) {};
FiniteSingleValue::FiniteSingleValue(const double &value)
    : FiniteSingleValue(&value) {};


Interval::Interval(const SingleValue *start, const SingleValue *end):
    start(start), end(end) {
        if(*end <= *start)
            throw std::invalid_argument("In interval [start, end], must have 'start < end'");
        if(*start == BOTINF && *end == TOPINF)
            throw std::invalid_argument("Cannot make interval (-inf, +inf), use Whole instead");
    };

Interval::Interval(const SingleValue &start, const SingleValue &end):
    Interval(&start, &end) {};


UnionSubSets::UnionSubSets(const std::vector<FiniteSingleValue*> &singles):
    singles(singles) {};
UnionSubSets::UnionSubSets(const std::vector<Interval*> &intervals):
    intervals(intervals) {};
UnionSubSets::UnionSubSets(const std::vector<FiniteSingleValue*> &singles, const std::vector<Interval*> &intervals):
    singles(singles), intervals(intervals) {};


// 
//
//
//  Printing implementations
// 
//
//


std::ostream &operator<< (std::ostream &os, const EmptyParam &value){    
    os << "{}";
    return os;
}

std::ostream &operator<< (std::ostream &os, const WholeParam &value){    
    os << "(-inf, +inf)";
    return os;
}

std::ostream &operator<< (std::ostream &os, const SingleValue &value){    
    const NegativeInfinity *neg = dynamic_cast<const NegativeInfinity*>(&value);
    if(neg){
        os << *neg;
        return os;
    }
    const PositiveInfinity *pos = dynamic_cast<const PositiveInfinity*>(&value);
    if(pos){
        os << *pos;
        return os;
    }
    const FiniteSingleValue *finite = dynamic_cast<const FiniteSingleValue*>(&value);
    if(finite){
        os << *finite;
        return os;
    }
    throw std::runtime_error("Not expected to get here!");
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
    os << *value.internal;
    return os;
}

std::ostream &operator<< (std::ostream &os, const Interval &value){    
    os << "[" << *value.start << ", " << *value.end << "]";
    return os;
}


//
//
//
//  EQUALITY COMPARATION
//
//
//


bool EmptyParam::operator==(const SubSetRealLine &other) const {
    return dynamic_cast<const EmptyParam*>(&other);
};
bool EmptyParam::operator!=(const SubSetRealLine &other) const {
    return !dynamic_cast<const EmptyParam*>(&other);
};
bool WholeParam::operator==(const SubSetRealLine &other) const {
    return dynamic_cast<const WholeParam*>(&other);
};
bool WholeParam::operator!=(const SubSetRealLine &other) const {
    return !dynamic_cast<const WholeParam*>(&other);
};

bool SingleValue::operator==(const SubSetRealLine &other) const {
    const SingleValue *single = dynamic_cast<const SingleValue*>(&other);
    return single && this->operator==(*single);
};
bool SingleValue::operator!=(const SubSetRealLine &other) const {
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
    return finite && *internal == *finite->internal;
};
bool FiniteSingleValue::operator!=(const SingleValue &other) const {
    const FiniteSingleValue *finite = dynamic_cast<const FiniteSingleValue*>(&other);
    return !finite || *internal != *finite->internal;
};

bool Interval::operator==(const SubSetRealLine &other) const {
    const Interval *interval = dynamic_cast<const Interval*>(&other);
    return interval && this->operator==(*interval);
};
bool Interval::operator!=(const SubSetRealLine &other) const {
    const Interval *interval = dynamic_cast<const Interval*>(&other);
    return !interval || this->operator!=(*interval);
};
bool Interval::operator==(const Interval &other) const {
    return *start == *other.start && *end == *other.end;
};
bool Interval::operator!=(const Interval &other) const {
    return *start != *other.start || *end != *other.end;
};

bool UnionSubSets::operator==(const SubSetRealLine &other) const {
    const UnionSubSets *unionsubsets = dynamic_cast<const UnionSubSets*>(&other);
    return unionsubsets && this->operator==(*unionsubsets);
};
bool UnionSubSets::operator!=(const SubSetRealLine &other) const {
    const UnionSubSets *unionsubsets = dynamic_cast<const UnionSubSets*>(&other);
    return !unionsubsets || this->operator!=(*unionsubsets);
};
bool UnionSubSets::operator==(const UnionSubSets &other) const {
    throw std::runtime_error("Not yet implemented");
    return false;
};
bool UnionSubSets::operator!=(const UnionSubSets &other) const {
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
    if (dynamic_cast<const NegativeInfinity*>(&other))
        return false;
    if (dynamic_cast<const PositiveInfinity*>(&other))
        return true;
    
    const FiniteSingleValue *finite = dynamic_cast<const FiniteSingleValue*>(&other);
    return *internal < *finite->internal;
};
bool FiniteSingleValue::operator<=(const SingleValue &other) const {
    if (dynamic_cast<const NegativeInfinity*>(&other))
        return false;
    if (dynamic_cast<const PositiveInfinity*>(&other))
        return true;

    const FiniteSingleValue *finite = dynamic_cast<const FiniteSingleValue*>(&other);
    return *internal <= *finite->internal;
};
bool FiniteSingleValue::operator>=(const SingleValue &other) const {
    if (dynamic_cast<const NegativeInfinity*>(&other))
        return true;
    if (dynamic_cast<const PositiveInfinity*>(&other))
        return false;
    const FiniteSingleValue *finite = dynamic_cast<const FiniteSingleValue*>(&other);
    return *internal >= *finite->internal;
};
bool FiniteSingleValue::operator>(const SingleValue &other) const {
    if (dynamic_cast<const NegativeInfinity*>(&other))
        return true;
    if (dynamic_cast<const PositiveInfinity*>(&other))
        return false;
    const FiniteSingleValue *finite = dynamic_cast<const FiniteSingleValue*>(&other);
    return *internal > *finite->internal;
};


// 
//
//
//  Contains implementations
// 
//
//


bool EmptyParam::contains(const SubSetRealLine &other) const {
    return dynamic_cast<const EmptyParam*>(&other);
}

bool WholeParam::contains(const SubSetRealLine &other) const {
    return true;
}

bool SingleValue::contains(const SubSetRealLine &other) const {
    const SingleValue *single = dynamic_cast<const SingleValue*>(&other);
    if (!single)
        return dynamic_cast<const EmptyParam*>(&other);
    return *this == *single;
};



bool Interval::contains(const SubSetRealLine &other) const {
    const SingleValue *single = dynamic_cast<const SingleValue*>(&other);
    if (single)
        return *start <= *single && *single <= *end;
    const Interval *interval = dynamic_cast<const Interval*>(&other);
    if (interval)
        return *start <= *interval->start && *interval->end <= *end;
    const UnionSubSets *subsets = dynamic_cast<const UnionSubSets*>(&other);
    if (subsets){
        for(uint1 i = 0; i < subsets->singles.size(); i++){
            const SingleValue *single = subsets->singles[i];
            if (*single < *this->start || *this->end < *single)
                return false;
        }
        for(uint1 i = 0; i < subsets->intervals.size(); i++){
            const Interval *interval = subsets->intervals[i];
            if (*interval->start < *this->start || *this->end < *interval->end)
                return false;
        }
        return true;
    }
    return dynamic_cast<const EmptyParam*>(&other);
};


bool UnionSubSets::contains(const SubSetRealLine &other) const {
    const SingleValue *single = dynamic_cast<const SingleValue*>(&other);
    if (single){
        for(uint1 i = 0; i < this->singles.size(); i++)
            if(*single == *this->singles[i])
                return true;
        for(uint1 i = 0; i < this->intervals.size(); i++){
            const Interval *interv = this->intervals[i];
            if((*(interv->start) <= *single) && (*single <= *(interv->end)))
                return true;
        }
    }
    const Interval *interval = dynamic_cast<const Interval*>(&other);
    if (interval)
        for(uint1 i = 0; i < this->intervals.size(); i++){
            const Interval *interv = this->intervals[i];
            if(*interv->start <= *interval->start && *interval->end <= *interv->end)
                return true;
        }
    const UnionSubSets *subsets = dynamic_cast<const UnionSubSets*>(&other);
    if (subsets){
        return true;
    }
    return dynamic_cast<const EmptyParam*>(&other);
};






#endif
