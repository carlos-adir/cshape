
#include "cshape/rbool.h"
#include "cshape/loggers.h"

const static Logger& logger = Logger::getInstance("cshape.rbool");

//
//
//
// Compare
//
//
//

bool IntervalR1::operator== (const IntervalR1 &other) const
{
    return this->start == other.start
        && this->end == other.end
        && this->closed_left == other.closed_left
        && this->closed_right == other.closed_right;
}

bool SubSetR1::operator==(const SubSetR1 &other) const
{
    if (this->typo != other.typo 
        || this->finites.size() != other.finites.size()
        || this->intervals.size() != other.intervals.size())
        return false;
    for (size_t i = 0; i < this->intervals.size(); ++i)
        if (this->intervals[i] != other.intervals[i])
            return false;
    for (size_t i = 0; i < this->finites.size(); ++i)
        if (this->finites[i] != other.finites[i])
            return false;
    return true;
}


//
// CONSTRUCTOR
//


SubSetR1 string_to_subset(const std::string &str);
SubSetR1Typo find_typo(const std::vector<scalar> &finites,
                       const std::vector<IntervalR1> &intervals);

// Clone
SubSetR1::SubSetR1(const SubSetR1 &other): finites(other.finites), intervals(other.intervals), typo(other.typo){};


SubSetR1::SubSetR1(const std::string &str):SubSetR1(
    string_to_subset(str).finites,
    string_to_subset(str).intervals) {} ;


SubSetR1::SubSetR1(const std::vector<scalar> &finites,
                   const std::vector<IntervalR1> &intervals):
    finites(finites), intervals(intervals), typo(find_typo(finites, intervals))
    {
        const size_t fsize = finites.size();
        const size_t isize = intervals.size();
        for (size_t i = 0; i + 1 < fsize; ++i)
            if (finites[i] >= finites[i+1])
                throw std::invalid_argument("Not ordered vector!");
        for (size_t i = 0; i + 1 < isize; ++i){
            if (intervals[i].end == POSINF)
                throw std::invalid_argument("Only last interval can end with POSINF");         
            if (intervals[i+1].start == NEGINF)
                throw std::invalid_argument("Only first interval can start with NEGINF");
            if (intervals[i].end >= intervals[i+1].start)
                throw std::invalid_argument("Intervals are not ordered!");
        }
    };


//
//
//
// STATIC BUILDERS
//
//
//
//


const static bool CLOSED_INF = true;


const SubSetR1 SubSetR1::Empty()
{
    return SubSetR1({}, {});
}

const SubSetR1 SubSetR1::Whole()
{
    IntervalR1 interval = {NEGINF, POSINF, CLOSED_INF, CLOSED_INF};
    return SubSetR1({}, {interval});
}

const SubSetR1 SubSetR1::Point(const scalar &value)
{
    return SubSetR1({value}, {});
}

const SubSetR1 SubSetR1::Lower(const scalar &value, const bool closed){
    IntervalR1 interval {NEGINF, value, CLOSED_INF, closed};
    return SubSetR1({}, {interval});
}


const SubSetR1 SubSetR1::Bigger(const scalar &value, const bool closed)
{
    IntervalR1 interval {value, POSINF, closed, CLOSED_INF};
    return SubSetR1({}, {interval});
}

const SubSetR1 SubSetR1::Between(const scalar &sta,
                                 const scalar &end,
                                 const bool closed_left,
                                 const bool closed_right)
{
    IntervalR1 interval {sta, end, closed_left, closed_right};
    return SubSetR1({}, {interval});
}

//
//
//
//  Boolean operations
//
//
//

void compute_middle(const std::vector<scalar> &knots,
                    const std::vector<bool> &inside,
                    std::vector<scalar> &finites,
                    std::vector<IntervalR1> &intervals);

SubSetR1 SubSetR1::operator~() const
{
    logger << "Begin SubSetR1::operator~";
    logger << *this;
    switch (typo)
    {
        case SubSetR1Typo::Empty:
            return SubSetR1::Whole();
        case SubSetR1Typo::Whole:
            return SubSetR1::Empty();
        case SubSetR1Typo::Point:
        {
            IntervalR1 left = {NEGINF, this->finites[0], CLOSED_INF, false};
            IntervalR1 right = {this->finites[0], POSINF, false, CLOSED_INF};
            return SubSetR1({}, {left, right});
        }
        case SubSetR1Typo::Interval:
        {
            const IntervalR1 interval = this->intervals[0];
            if (interval.start == NEGINF)
                return SubSetR1::Bigger(interval.end, !interval.closed_right);
            else if (interval.end == POSINF)
                return SubSetR1::Lower(interval.start, !interval.closed_left);
            IntervalR1 left = {NEGINF, this->intervals[0].start, CLOSED_INF, !this->intervals[0].closed_left};
            IntervalR1 right = {this->intervals[0].end, POSINF, !this->intervals[0].closed_right, CLOSED_INF};
            return SubSetR1({}, {left, right});
        }
        case SubSetR1Typo::Disjoint:
        {
            std::set<scalar> setknots = {NEGINF, POSINF};
            for (const scalar point : this->finites)
                setknots.insert(point);
            for (const IntervalR1 interval : this->intervals)
            {
                setknots.insert(interval.start);
                setknots.insert(interval.end);
            }
            setknots.erase(NEGINF);
            setknots.erase(POSINF);
            std::vector<bool> inside(2 * setknots.size() + 1, false);
            const std::vector<scalar> knots(setknots.begin(), setknots.end());

            inside[0] = !this->contains(knots[0] - 1);
            for (size_t i = 0; i < knots.size(); ++i)
                inside[2*i + 1] = !this->contains(knots[i]);
            for (size_t i = 1; i < knots.size(); ++i){
                const scalar middle = (knots[i-1] + knots[i]) / 2;
                inside[2 * i] = !this->contains(middle);
            }
            const scalar last = knots[knots.size() - 1] + 1;
            inside[2 * knots.size()] = !this->contains(last);

            std::vector<scalar> finites;
            std::vector<IntervalR1> intervals;
            compute_middle(knots, inside, finites, intervals);
            return SubSetR1(finites, intervals);
        }
        default:
            throw std::invalid_argument("Wrong typo");
    }
};


SubSetR1 SubSetR1::operator|(const SubSetR1 &other) const
{
    logger << "Begin SubSetR1::operator|";
    logger << *this;
    logger << other;
    if (this->contains(other))  // Take cares of whole |= other or *this |= empty
        return *this;
    if (other.contains(*this))  // Take cares of empty |= other or *this |= whole
        return other;

    std::set<scalar> setknots = {NEGINF, POSINF};
    for (const scalar point : this->finites)
        setknots.insert(point);
    for (const scalar point : other.finites)
        setknots.insert(point);
    for (const IntervalR1 interval : this->intervals)
    {
        setknots.insert(interval.start);
        setknots.insert(interval.end);
    }
    for (const IntervalR1 interval : other.intervals)
    {
        setknots.insert(interval.start);
        setknots.insert(interval.end);
    }
    setknots.erase(NEGINF);
    setknots.erase(POSINF);
    
    const std::vector<scalar> knots(setknots.begin(), setknots.end());
    std::vector<bool> inside(2 * knots.size() + 1, false);

    inside[0] = this->contains(knots[0] - 1) || other.contains(knots[0] - 1);
    for (size_t i = 0; i < knots.size(); ++i)
        inside[2*i + 1] = this->contains(knots[i]) || other.contains(knots[i]);
    for (size_t i = 1; i < knots.size(); ++i){
        const scalar midknot = (knots[i - 1] + knots[i]) / 2;
        inside[2 * i] = this->contains(midknot) || other.contains(midknot);
    }
    const scalar last = knots[knots.size() - 1] + 1;
    inside[2 * knots.size()] = this->contains(last) || other.contains(last);
    
    std::vector<scalar> finites;
    std::vector<IntervalR1> intervals;
    compute_middle(knots, inside, finites, intervals);
    return SubSetR1(finites, intervals);
};


SubSetR1 SubSetR1::operator&(const SubSetR1 &other) const
{
    logger << "Begin SubSetR1::operator&";
    logger << *this;
    logger << other;
    if (this->contains(other))  // Take cares of whole |= other or *this |= empty
        return other;
    if (other.contains(*this))  // Take cares of empty |= other or *this |= whole
        return *this;

    std::set<scalar> setknots = {NEGINF, POSINF};
    for (const scalar point : this->finites)
        setknots.insert(point);
    for (const scalar point : other.finites)
        setknots.insert(point);
    for (const IntervalR1 interval : this->intervals)
    {
        setknots.insert(interval.start);
        setknots.insert(interval.end);
    }
    for (const IntervalR1 interval : other.intervals)
    {
        setknots.insert(interval.start);
        setknots.insert(interval.end);
    }
    setknots.erase(NEGINF);
    setknots.erase(POSINF);

    const std::vector<scalar> knots(setknots.begin(), setknots.end());
    std::vector<bool> inside(2 * knots.size() + 1, false);

    inside[0] = this->contains(knots[0] - 1) && other.contains(knots[0] - 1);
    for (size_t i = 0; i < knots.size(); ++i)
        inside[2*i + 1] = this->contains(knots[i]) && other.contains(knots[i]);
    for (size_t i = 1; i < knots.size(); ++i){
        const scalar midknot = (knots[i-1] + knots[i]) / 2;
        inside[2*i] = this->contains(midknot) && other.contains(midknot);
    }
    const scalar last = knots[knots.size() - 1] + 1;
    inside[2 * knots.size()] = this->contains(last) && other.contains(last);

    std::vector<scalar> finites;
    std::vector<IntervalR1> intervals;
    compute_middle(knots, inside, finites, intervals);
    return SubSetR1(finites, intervals);
};



void compute_middle(const std::vector<scalar> &knots,
                    const std::vector<bool> &inside,
                    std::vector<scalar> &finites,
                    std::vector<IntervalR1> &intervals)
{
    scalar start = NEGINF;
    bool closed = false;
    for(size_t i = 0; i < knots.size(); ++i){
        const scalar &knot = knots[i];
        const bool left = inside[2*i];
        const bool midd = inside[2*i+1];
        const bool righ = inside[2*i+2];
        if (left == midd && midd == righ)
            continue;  // Take care of two of 8 cases
        if (!left && !righ){ // single finite value
            finites.push_back(knot);
            continue;
        }
        if (left) // finish interval
            intervals.push_back({start, knot, closed, midd});
        if (righ){ // start new interval
            start = knot;
            closed = midd;
        }
    }
    if (start != NEGINF)
    {
        intervals.push_back({start, POSINF, closed, CLOSED_INF});
    }
}


// 
//
//
//  Printing implementations
// 
//
//

std::ostream &operator<<(std::ostream &os, const IntervalR1 &obj){
    os << ((obj.start == NEGINF || !obj.closed_left) ? "(" : "[");
    os << obj.start << ", " << obj.end;
    os << ((obj.end == POSINF || !obj.closed_right) ? ")" : "]");
    return os;
}

SubSetR1::operator std::string() const{
    std::ostringstream stream;
    stream << *this;
    return stream.str();
}


std::ostream &operator<<(std::ostream &os, const SubSetR1 &obj){
    switch (obj.typo)
    {
        case SubSetR1Typo::Empty:
            return os << "{}";
        case SubSetR1Typo::Whole:
            return os << "(" << NEGINF << ", " << POSINF << ")";        
        case SubSetR1Typo::Point:
            return os << "{" << obj.finites[0] << "}";        
        case SubSetR1Typo::Interval:
            return os << obj.intervals[0];
        case SubSetR1Typo::Disjoint:
            break;
        default:
            throw std::invalid_argument("Not expected");        
    }
    // Disjoint

    const size_t fsize = obj.finites.size();
    const size_t isize = obj.intervals.size();

    std::vector<std::string> msgs;
    std::vector<scalar> finis;
    bool first = true;
    bool flag = false;
    size_t i = 0, f = 0;
    
    if (obj.intervals[0].start == NEGINF){
        os << obj.intervals[0];
        ++i;
        first = false;
    }
    while (i < isize && f < fsize){
        if (obj.finites[f] < obj.intervals[i].end){
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


//
//
//
//  Contains
//
//
//


bool IntervalR1::contains(const scalar &other) const
{
    return (this->start < other || (this->closed_left && this->start == other))
        && (other < this->end || (this->closed_right && this->end == other));
}


bool IntervalR1::contains(const IntervalR1 &other) const
{
    if (other.start < this->start || this->end < other.end)
        return false;
    if (this->start < other.start && other.end < this->end)
        return true;
    if (!this->closed_left && other.closed_left && this->start == other.start)
        return false;
    if (!this->closed_right && other.closed_right && this->end == other.end)
        return false;
    return true;    
}

bool SubSetR1::contains(const scalar &other) const{
    for(const IntervalR1 interval : this->intervals)
        if(interval.contains(other))
            return true;
    for(const scalar point : this->finites)
        if(point == other)
            return true;
    return false;
}

bool SubSetR1::contains(const IntervalR1 &other) const{
    switch (this->typo)
    {
        case SubSetR1Typo::Whole:
            return true;
        case SubSetR1Typo::Empty:
            return false;
        case SubSetR1Typo::Point:
            return false;
        case SubSetR1Typo::Interval:
            return intervals[0].contains(other);
        case SubSetR1Typo::Disjoint:
            for (const IntervalR1 interval : this->intervals)
                if (interval.contains(other))
                    return true;
            return false;
        default:
            throw std::invalid_argument("Received wrong type");
    }
}

bool SubSetR1::contains(const SubSetR1 &other) const{
    switch (other.typo)
    {
        case SubSetR1Typo::Whole:
            return this->typo == SubSetR1Typo::Whole;
        case SubSetR1Typo::Empty:
            return this->typo != SubSetR1Typo::Empty;
        case SubSetR1Typo::Point:
            return this->contains(other.finites[0]);
        case SubSetR1Typo::Interval:
            return this->contains(other.intervals[0]);
        case SubSetR1Typo::Disjoint:
            for (const scalar point : other.finites)
                if (!this->contains(point))
                    return false;
            for (const IntervalR1 interval : other.intervals)
                if (!this->contains(interval))
                    return false;
            return true;
        default:
            throw std::invalid_argument("Received wrong type");
    }
}


//
//  STRING OPERATIONS
//  
//






IntervalR1 string_to_interval(const std::string &str) {
    const size_t size = str.size();
    bool closed_left = (str[0] == '[');
    bool closed_right = (str[size - 1] == ']');
    size_t virg = 1;
    while (virg < size && str[virg] != ',')
        ++virg;
    if (virg == size)
        throw std::invalid_argument("Invalid string to convert to interval");
    const scalar first = string_to_scalar(str.substr(1, virg - 1));
    const scalar second = string_to_scalar(str.substr(virg + 1, size - virg - 2));
    if (first == NEGINF)
        closed_left = true;
    if (second == POSINF)
        closed_right = true;
    return {first, second, closed_left, closed_right};
};




SubSetR1Typo find_typo(const std::vector<scalar> &finites,
                       const std::vector<IntervalR1> &intervals)
{
    const size_t fsize = finites.size();
    const size_t isize = intervals.size();
    if (isize == 0 && fsize == 0)
    {
        return SubSetR1Typo::Empty;
    }
    else if (isize == 0)
    {
        return fsize == 1 ? SubSetR1Typo::Point : SubSetR1Typo::Disjoint;
    }
    else if (fsize != 0 || isize > 1)
    {
        return SubSetR1Typo::Disjoint;
    }
    if (intervals[0].start == NEGINF && intervals[0].end == POSINF)
    {
        return SubSetR1Typo::Whole;
    }
    return SubSetR1Typo::Interval;
}


const static std::string EMPTYSTR = std::string(SubSetR1::Empty());
const static std::string WHOLESTR = std::string(SubSetR1::Whole());


SubSetR1 string_to_subset(const std::string &str)
{
    if (str == EMPTYSTR)
        return SubSetR1::Empty();
    if (str == WHOLESTR)
        return SubSetR1::Whole();
    const size_t size = str.size();
    std::vector<scalar> finites;
    std::vector<IntervalR1> intervals;
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
                const scalar new_value = string_to_scalar(sub.substr(i, j - i));
                finites.push_back(new_value);
                i = j + 1;
            }
            continue;
        }else{
            intervals.push_back(string_to_interval(sub));
        }
        sta = end+1;
    }
    return SubSetR1(finites, intervals);
}
