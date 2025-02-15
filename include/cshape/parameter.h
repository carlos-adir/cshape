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
class UnionSubsets;
template <typename T>
class FiniteSingleValue;
class NegativeInfinity;
class PositiveInfinity;

class SubSetRealLine{
public:
    virtual bool operator==(const SubSetRealLine &other) const = 0;
    virtual bool operator!=(const SubSetRealLine &other) const = 0;
    virtual bool contains(const SubSetRealLine &other) const = 0;

    // virtual SubSetRealLine &operator~() const = 0;
    // virtual SubSetRealLine &operator|(const SubSetRealLine &other) const = 0;
    // virtual SubSetRealLine &operator&(const SubSetRealLine &other) const = 0;
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

    bool operator==(const SubSetRealLine &other) const final {
        return dynamic_cast<const EmptyParam*>(&other);
    };
    bool operator!=(const SubSetRealLine &other) const final {
        return !dynamic_cast<const EmptyParam*>(&other);
    };

    bool contains(const SubSetRealLine &other) const final {
        return dynamic_cast<const EmptyParam*>(&other);
    };

    // SubSetRealLine &operator~() const final;

    friend std::ostream &operator<< (std::ostream &os, const EmptyParam &value){
        os << "{}";
        return os;
    };
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

    bool operator==(const SubSetRealLine &other) const final {
        return dynamic_cast<const WholeParam*>(&other);
    };
    bool operator!=(const SubSetRealLine &other) const final {
        return !dynamic_cast<const WholeParam*>(&other);
    };

    bool contains(const SubSetRealLine &other) const final {
        return true;
    };

    friend std::ostream &operator<< (std::ostream &os, const WholeParam &value){
        os << "(-inf, +inf)";
        return os;
    };
};


class SingleValue : public SubSetRealLine{
   

public:
    bool operator==(const SubSetRealLine &other) const final {
        const SingleValue *single = dynamic_cast<const SingleValue*>(&other);
        return single && this->operator==(*single);
    };
    bool operator!=(const SubSetRealLine &other) const final {
        const SingleValue *single = dynamic_cast<const SingleValue*>(&other);
        return !single || this->operator!=(*single);
    };

    virtual bool operator<(const SingleValue &other) const = 0;
    virtual bool operator>(const SingleValue &other) const = 0;
    virtual bool operator<=(const SingleValue &other) const = 0;
    virtual bool operator>=(const SingleValue &other) const = 0;
    virtual bool operator==(const SingleValue &other) const = 0;
    virtual bool operator!=(const SingleValue &other) const = 0;

    bool contains(const SubSetRealLine &other) const final {
        const SingleValue *single = dynamic_cast<const SingleValue*>(&other);
        if (!single)
            return dynamic_cast<const EmptyParam*>(&other);
        return *this == *single;
    };

    friend std::ostream &operator<< (std::ostream &os, const SingleValue &value){
        os << "SingleValue(X)";
        return os;
    }
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

    
    bool operator==(const SingleValue &other) const final {
        return dynamic_cast<const NegativeInfinity*>(&other);
    };
    bool operator!=(const SingleValue &other) const final {
        return !dynamic_cast<const NegativeInfinity*>(&other);
    };
    bool operator<(const SingleValue &other) const final {
        return !dynamic_cast<const NegativeInfinity*>(&other);
    };
    bool operator<=(const SingleValue &other) const final {return true;};
    bool operator>=(const SingleValue &other) const final {
        return dynamic_cast<const NegativeInfinity*>(&other);
    };
    bool operator>(const SingleValue &other) const final {return false;};

    friend std::ostream &operator<< (std::ostream &os, const NegativeInfinity &value){
        os << "-inf";
        return os;
    }
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

    bool operator==(const SingleValue &other) const final {
        return dynamic_cast<const PositiveInfinity*>(&other);
    };
    bool operator!=(const SingleValue &other) const final {
        return !dynamic_cast<const PositiveInfinity*>(&other);
    };
    bool operator<(const SingleValue &other) const final {return false;};
    bool operator<=(const SingleValue &other) const final {    
        return dynamic_cast<const PositiveInfinity*>(&other);
    };
    bool operator>=(const SingleValue &other) const final {return true;};
    bool operator>(const SingleValue &other) const final {
        return !dynamic_cast<const PositiveInfinity*>(&other);
    };
    
    friend std::ostream &operator<< (std::ostream &os, const PositiveInfinity &value){
        os << "+inf";
        return os;
    }
};


template <typename T>
class FiniteSingleValue : public SingleValue {
private:
    const T *internal;

public:
    FiniteSingleValue(const T *value) : internal(value) {};
    
    using SingleValue::operator==;
    using SingleValue::operator!=;

    bool operator<(const SingleValue &other) const final {
        if (dynamic_cast<const NegativeInfinity*>(&other))
            return false;
        if (dynamic_cast<const PositiveInfinity*>(&other))
            return true;
        
        const FiniteSingleValue *finite = dynamic_cast<const FiniteSingleValue*>(&other);
        return *internal < *finite->internal;
    };
    bool operator<=(const SingleValue &other) const final {
        if (dynamic_cast<const NegativeInfinity*>(&other))
            return false;
        if (dynamic_cast<const PositiveInfinity*>(&other))
            return true;

        const FiniteSingleValue *finite = dynamic_cast<const FiniteSingleValue*>(&other);
        return *internal <= *finite->internal;
    };
    bool operator>=(const SingleValue &other) const final {
        if (dynamic_cast<const NegativeInfinity*>(&other))
            return true;
        if (dynamic_cast<const PositiveInfinity*>(&other))
            return false;
        const FiniteSingleValue *finite = dynamic_cast<const FiniteSingleValue*>(&other);
        return *internal >= *finite->internal;
    };
    bool operator>(const SingleValue &other) const final {
        if (dynamic_cast<const NegativeInfinity*>(&other))
            return true;
        if (dynamic_cast<const PositiveInfinity*>(&other))
            return false;
        const FiniteSingleValue *finite = dynamic_cast<const FiniteSingleValue*>(&other);
        return *internal > *finite->internal;
    };
    bool operator==(const SingleValue &other) const final {
        if (dynamic_cast<const NegativeInfinity*>(&other))
            return false;
        if (dynamic_cast<const PositiveInfinity*>(&other))
            return false;
        const FiniteSingleValue *finite = dynamic_cast<const FiniteSingleValue*>(&other);
        return *internal == *finite->internal;
    };
    bool operator!=(const SingleValue &other) const final {
        if (dynamic_cast<const NegativeInfinity*>(&other))
            return true;
        if (dynamic_cast<const PositiveInfinity*>(&other))
            return true;
        const FiniteSingleValue *finite = dynamic_cast<const FiniteSingleValue*>(&other);
        return *internal != *finite->internal;
    };
};

class Interval : public SubSetRealLine {
private:
    const SingleValue *start, *end;

public:
    Interval(const SingleValue *start, const SingleValue *end) : start(start), end(end){};

    bool operator==(const SubSetRealLine &other) const final {
        const Interval *interval = dynamic_cast<const Interval*>(&other);
        return interval && this->operator==(*interval);
    };
    bool operator!=(const SubSetRealLine &other) const final {
        const Interval *interval = dynamic_cast<const Interval*>(&other);
        return !interval || this->operator!=(*interval);
    };
    virtual bool operator==(const Interval &other) const final {
        return *start == *other.start && *end == *other.end;
    };
    virtual bool operator!=(const Interval &other) const final {
        return *start != *other.start || *end != *other.end;
    };


    bool contains(const SubSetRealLine &other) const final {
        const SingleValue *single = dynamic_cast<const SingleValue*>(&other);
        if (single)
            return *start <= *single && *single <= *end;
        const Interval *interval = dynamic_cast<const Interval*>(&other);
        if (interval)
            return *start <= *interval->start && *interval->end <= *end;
        const UnionSubsets *unionsets = dynamic_cast<const UnionSubsets*>(&other);
        if (unionsets){
            // for(uint1 i = 0; i < unionsets->singles.size(); i++){
            //     const SingleValue *single = unionsets->singles[i];
            //     if (*single < *this->start || *this->end < *single)
            //         return false;
            // }
            // for(uint1 i = 0; i < unionsets->intervals.size(); i++){
            //     const Interval *interval = unionsets->intervals[i];
            //     if (*interval->start < *this->start || *this->end < *interval->end)
            //         return false;
            // }
            return true;
        }
        return dynamic_cast<const EmptyParam*>(&other);
    };
};


class UnionSubsets : public SubSetRealLine {
public:
    std::vector<SingleValue*> singles;
    std::vector<Interval*> intervals;
    
    bool operator==(const SubSetRealLine &other) const final {
        const UnionSubsets *unionsubsets = dynamic_cast<const UnionSubsets*>(&other);
        return unionsubsets && this->operator==(*unionsubsets);
    };
    bool operator!=(const SubSetRealLine &other) const final {
        const UnionSubsets *unionsubsets = dynamic_cast<const UnionSubsets*>(&other);
        return !unionsubsets || this->operator!=(*unionsubsets);
    };
    virtual bool operator==(const UnionSubsets &other) const final {
        return false;
    };
    virtual bool operator!=(const UnionSubsets &other) const final {
        return false;
    };
    bool contains(const SubSetRealLine &other) const final {
        return false;
    }
};

static const NegativeInfinity& BOTINF = NegativeInfinity::getInstance();
static const PositiveInfinity& TOPINF = PositiveInfinity::getInstance();
static const EmptyParam& EMPTY = EmptyParam::getInstance();
static const WholeParam& WHOLE = WholeParam::getInstance();


// SubSetRealLine &EmptyParam::operator~() const{
//     return WHOLE;
// }
// SubSetRealLine &WholeParam::operator~() const{
//     return EMPTY;
// }



template class FiniteSingleValue<int>;






#endif
