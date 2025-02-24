#ifndef UNIDIMBOOL_H
#define UNIDIMBOOL_H

#include <vector>
#include <iostream>
#include <unistd.h>
#include <sstream>
#include <string>
#include <memory>

#include "scalar.h"

typedef unsigned long uint8;
typedef unsigned int uint4;
typedef unsigned short uint2;
typedef unsigned short uint1;

class SubSetR1;
class IntervalR1;



class IntervalR1{
private:
    std::unique_ptr<basetype> sta, end;
    bool left, right;

    IntervalR1(std::unique_ptr<basetype> sta,
               std::unique_ptr<basetype> end,
               const bool closed_left,
               const bool closed_right);
public:
    IntervalR1(const IntervalR1 &other); // Copy constructor
    IntervalR1(const std::string &str);  // From string to interval

    operator std::string() const;
    friend std::ostream &operator<< (std::ostream &os, const IntervalR1 &value);
    friend std::ostream &operator<< (std::ostream &os, const SubSetR1 &obj);

    IntervalR1 &operator=(const std::string &str);

    bool contains(const basetype &other) const;
    bool contains(const IntervalR1 &other) const;

    bool operator==(const IntervalR1 &other) const;
    bool operator!=(const IntervalR1 &other) const;

    friend class SubSetR1;
};
    



class SubSetR1{
private:
    std::vector<basetype> finites;
    std::vector<IntervalR1> intervals;
    
    SubSetR1(const std::vector<basetype> &finites,
             const std::vector<IntervalR1> &intervals); // Empty

public:
    SubSetR1();
    SubSetR1(const SubSetR1 &other); // Copy constructor
    SubSetR1(const std::string &str); // Transform string to SubSetR1

    // virtual bool operator==(const SubSetR1 &other) const;
    // virtual bool operator!=(const SubSetR1 &other) const;

    virtual bool contains(const SubSetR1 &other) const;
    virtual bool contains(const basetype &other) const;

    // virtual SubSetR1 operator~() const;
    // virtual SubSetR1 operator|(const SubSetR1 &other) const;
    // virtual SubSetR1 operator&(const SubSetR1 &other) const;

    static SubSetR1 empty();
    static SubSetR1 whole();
    static SubSetR1 single(const basetype &value);
    static SubSetR1 lower(const basetype &value, const bool closed = true);
    static SubSetR1 bigger(const basetype &value, const bool closed = true);
    static SubSetR1 interval(const basetype &sta,
                             const basetype &end,
                             const bool closed_left = true,
                             const bool closed_right = true);
    static SubSetR1 interval(const NegativeInfinity &sta,
                             const basetype &end,
                             const bool closed_left = false,
                             const bool closed_right = true);
    static SubSetR1 interval(const basetype &sta,
                             const PositiveInfinity &end,
                             const bool closed_left = true,
                             const bool closed_right = false);

    SubSetR1 &operator=(const SubSetR1 &other);
    SubSetR1 &operator=(const std::string &other);

    bool operator==(const SubSetR1 &other) const;
    bool operator!=(const SubSetR1 &other) const;

    operator std::string() const;
    friend std::ostream &operator<<(std::ostream &os, const SubSetR1 &obj);

};


IntervalR1::IntervalR1(std::unique_ptr<basetype> sta,
                       std::unique_ptr<basetype> end,
                       const bool closed_left,
                       const bool closed_right):
    sta(std::move(sta)),
    end(std::move(end)),
    left(closed_left),
    right(closed_right){
    if (sta != nullptr && end != nullptr && *end <= *sta)   
        throw std::invalid_argument("In interval [start, end], must have 'start < end'");
}

IntervalR1::IntervalR1(const IntervalR1 &other):
    sta((other.sta == nullptr) ? nullptr : (std::make_unique<basetype>(*other.sta))),
    end((other.end == nullptr) ? nullptr : (std::make_unique<basetype>(*other.end))),
    left(other.left),
    right(other.right){};


IntervalR1::IntervalR1(const std::string &str){
    *this = str;
};



SubSetR1::SubSetR1(){};
SubSetR1::SubSetR1(const std::vector<basetype> &finites,
                   const std::vector<IntervalR1> &intervals):
    finites(finites), intervals(intervals){
        const size_t fsize = finites.size();
        const size_t isize = intervals.size();
        for (size_t i = 0; i + 1 < fsize; ++i)
            if (finites[i] >= finites[i+1])
                throw std::invalid_argument("Not ordered vector!");
        for (size_t i = 0; i + 1 < isize; ++i){
            if (intervals[i].end == nullptr)
                throw std::invalid_argument("Only last interval can end with POSINF");         
            if (intervals[i+1].sta == nullptr)
                throw std::invalid_argument("Only first interval can start with NEGINF");
            if (*intervals[i].end >= *intervals[i+1].sta)
                throw std::invalid_argument("Intervals are not ordered!");
        }
    };

SubSetR1::SubSetR1(const SubSetR1 &other):SubSetR1(other.finites, other.intervals){};

SubSetR1::SubSetR1(const std::string &str){
    *this = str;
};


SubSetR1 SubSetR1::empty(){
    std::vector<basetype> finites;
    std::vector<IntervalR1> intervals;
    return SubSetR1(finites, intervals);
}

SubSetR1 SubSetR1::whole(){
    std::vector<basetype> finites;
    std::vector<IntervalR1> intervals;
    const IntervalR1 interval(nullptr, nullptr, false, false);
    intervals.push_back(interval);
    return SubSetR1(finites, intervals);
}


SubSetR1 SubSetR1::single(const basetype &value){
    std::vector<basetype> finites;
    std::vector<IntervalR1> intervals;
    finites.push_back(value);
    return SubSetR1(finites, intervals);
}

SubSetR1 SubSetR1::lower(const basetype &value, const bool closed){
    std::vector<basetype> finites;
    std::vector<IntervalR1> intervals;
    const IntervalR1 interval(nullptr, std::make_unique<basetype>(value), false, closed);
    intervals.push_back(interval);
    return SubSetR1(finites, intervals);
}

SubSetR1 SubSetR1::bigger(const basetype &value, const bool closed){
    std::vector<basetype> finites;
    std::vector<IntervalR1> intervals;
    const IntervalR1 interval(std::make_unique<basetype>(value), nullptr, closed, false);
    intervals.push_back(interval);
    return SubSetR1(finites, intervals);
}


SubSetR1 SubSetR1::interval(const basetype &sta,
                        const basetype &end,
                        const bool closed_left,
                        const bool closed_right){
    std::vector<basetype> finites;
    std::vector<IntervalR1> intervals;
    const IntervalR1 interval(std::make_unique<basetype>(sta),
                              std::make_unique<basetype>(end),
                              closed_left, closed_right);
    intervals.push_back(interval);
    return SubSetR1(finites, intervals);
}


SubSetR1 SubSetR1::interval(const NegativeInfinity &sta,
                        const basetype &end,
                        const bool closed_left,
                        const bool closed_right){
    return SubSetR1::lower(end, closed_right);
}


SubSetR1 SubSetR1::interval(const basetype &sta,
                            const PositiveInfinity &end,
                            const bool closed_left,
                            const bool closed_right){
    return SubSetR1::bigger(sta, closed_left);
}




//
//
//
// Comparate
//
//
//

bool IntervalR1::operator==(const IntervalR1 &other) const{
    if ((this->sta == nullptr) ^ (other.sta == nullptr))
        return false;
    if ((this->sta == nullptr) ^ (other.sta == nullptr))
        return false;
    if (this->sta != nullptr && (this->left ^ other.left || *this->sta != *other.sta))
        return false;
    if (this->sta != nullptr && (this->left ^ other.left || *this->sta != *other.sta))
        return false;
    return true;
}

bool IntervalR1::operator!=(const IntervalR1 &other) const{
    return !(this->operator==(other));
}

bool SubSetR1::operator==(const SubSetR1 &other) const{
    if (this->finites.size() != other.finites.size())
        return false;
    if (this->intervals.size() != other.intervals.size())
        return false;
    for (size_t i = 0; i < this->intervals.size(); ++i)
        if (this->intervals[i] != other.intervals[i])
            return false;
    for (size_t i = 0; i < this->finites.size(); ++i)
        if (this->finites[i] != other.finites[i])
            return false;
    return true;
}

bool SubSetR1::operator!=(const SubSetR1 &other) const{
    return !(this->operator==(other));
}




IntervalR1 &IntervalR1::operator=(const std::string &str) {
    const size_t size = str.size();
    this->left = (str[0] == '[');
    this->right = (str[size - 1] == ']');
    size_t virg = 1;
    while (virg < size && str[virg] != ',')
        ++virg;
    if (virg == size)
        throw std::invalid_argument("Invalid string to convert to interval");
    const std::string first = str.substr(1, virg - 1);
    const std::string secon = str.substr(virg + 1, size - virg - 2);
    std::unique_ptr<basetype> sta, end;
    if (first.find(NegativeInfinity::STR) != std::string::npos)
        this->sta.reset();
    else
        this->sta = std::make_unique<basetype>(string_to_basetype(first));
    if (secon.find(PositiveInfinity::STR) != std::string::npos)
        this->end.reset();
    else
        this->end = std::make_unique<basetype>(string_to_basetype(secon));
    return *this;
};






SubSetR1 &SubSetR1::operator=(const SubSetR1 &other) {
    this->finites.clear();
    this->intervals.clear();
    for (size_t i = 0; i < other.finites.size(); i++)
        this->finites.push_back(basetype(other.finites[i]));
    for (size_t i = 0; i < other.intervals.size(); i++)
        this->intervals.push_back(IntervalR1(other.intervals[i]));
    return *this;
};

SubSetR1 &SubSetR1::operator=(const std::string &str) {
    const size_t size = str.size();
    const size_t sta = 0, end = 0;
    this->finites.clear();
    this->intervals.clear();
    if (str == "{}") return *this;
    for (size_t sta = 0; sta < size; ++sta){
        if (str[sta] != '(' && str[sta] != '[' && str[sta] != '{')
            continue;
        size_t end = sta + 1;
        while(end < size && str[end] != ')' && str[end] != ']' && str[end] != '}')
            ++end;
        const std::string sub = str.substr(sta, end + 1 - sta);
        const size_t subsize = sub.size();
        if (sub[0] == '{' && sub[subsize-1] == '}'){
            for (size_t i = 1; i + 1 < subsize; ++i){
                size_t j = i + 1;
                while (j < subsize && sub[j] != ',' && sub[j] != '}')
                    ++j;
                const basetype new_value = string_to_basetype(sub.substr(i, j - i));
                this->finites.push_back(new_value);
                i = j + 1;
            }
            continue;
        }else{
            const IntervalR1 new_interv = IntervalR1(sub);
            this->intervals.push_back(new_interv);
        }
        sta = end+1;
    }
    return *this;
};






// 
//
//
//  Printing implementations
// 
//
//

IntervalR1::operator std::string() const{
    std::ostringstream stream;
    stream << *this;
    return stream.str();
}


std::ostream &operator<<(std::ostream &os, const IntervalR1 &obj){
    os << (obj.left ? "[" : "(");
    if (obj.sta)
        os << *obj.sta;
    else
        os << NegativeInfinity::STR;
    os << ", ";
    if (obj.end)
        os << *obj.end;
    else
        os << PositiveInfinity::STR;
    os << (obj.right ? "]" : ")");
    return os;
}

SubSetR1::operator std::string() const{
    std::ostringstream stream;
    stream << *this;
    return stream.str();
}


std::ostream &operator<<(std::ostream &os, const SubSetR1 &obj){
    const size_t fsize = obj.finites.size();
    const size_t isize = obj.intervals.size();
    if (fsize == 0 && isize == 0){
        os << "{}";
        return os;
    } else if (fsize == 0){
        os << obj.intervals[0];
        for (size_t i = 1; i < isize; ++i)
            os << " U " << obj.intervals[i];
        return os;
    } else if (isize == 0){
        os << "{" << obj.finites[0];
        for (size_t f = 1; f < isize; ++f)
            os << ", " << obj.finites[f];
        os << "}";
        return os;
    }

    std::vector<std::string> msgs;
    std::vector<basetype> finis;
    bool first = true;
    bool flag = false;
    size_t i = 0, f = 0;
    
    if (obj.intervals[0].sta == nullptr){
        os << obj.intervals[0];
        ++i;
        first = false;
    }
    while (i < isize && f < fsize){
        if (obj.finites[f] < *obj.intervals[i].sta){
            if (!flag){
                if (!first){
                    os << " U ";
                }
                os << "{";
                first = false;
                flag = true;
            }else
                os << ", ";
            os << obj.finites[f];
            ++f;
            continue;
        }
        if (flag){
            os << "}";
            flag = false;
        }
        if (!first)
            os << " U ";
        first = false;
        os << obj.intervals[i];
        ++i;
    }
    if (f < fsize){
        if (!flag){
            if (!first)
                os << " U ";
            os << "{";
            first = false;
            flag = true;
        }else{
            os << ", ";
        }
        os << obj.finites[f];
        ++f;
        for (; f < fsize; ++f)
            os << ", " << obj.finites[f];
    }
    if (flag)
        os << "}";
    for (; i < isize; ++i)
        os << " U " << obj.intervals[i];
    return os;
}



bool IntervalR1::contains(const basetype &other) const{
    if (this->sta != nullptr)
        if (other < *this->sta || (!this->left && other == *this->sta))
            return false;
    if (this->end != nullptr)
        if (*this->end < other || (!this->right && other == *this->end))
            return false;
    return true;
}

bool IntervalR1::contains(const IntervalR1 &other) const{
    if ((other.sta == nullptr && this->sta != nullptr) || (other.end == nullptr && this->end != nullptr))
        return false;
    if (this->sta){
        if (*other.sta < *this->sta)
            return false;
        if (other.left && !this->left && *other.sta == *this->sta)
            return false;
    }
    if (this->end){
        if (*this->end < *other.end)
            return false;
        if (other.right && !this->right && *other.end == *this->end)
            return false;
    }
    return true;
}


bool SubSetR1::contains(const basetype &other) const{
    for(size_t j = 0; j < this->intervals.size(); ++j)
        if(this->intervals[j].contains(other))
            return true;
    for(size_t j = 0; j < this->finites.size(); ++j)
        if(this->finites[j] == other)
            return true;
    return false;
}



bool SubSetR1::contains(const SubSetR1 &other) const{
    bool exit;
    for (size_t i = 0; i < other.intervals.size(); ++i){
        exit = true;
        for(size_t j = 0; j < this->intervals.size(); ++j)
            if(this->intervals[j].contains(other.intervals[i])){
                exit = false;
                break;
            }
        if (exit) return false;
    }
    for (size_t i = 0; i < other.finites.size(); ++i){
        const basetype finite = other.finites[i];
        exit = true;
        for(size_t j = 0; j < this->intervals.size(); ++j)
            if(this->intervals[j].contains(finite)){
                exit = false;
                break;
            }
        if (!exit) continue;
        for(size_t j = 0; j < this->finites.size(); ++j)
            if(this->finites[j] == finite){
                exit = false;
                break;
            }
        if (exit) return false;
    }
    return true;
}




#endif
