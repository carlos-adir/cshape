
#include "cshape/rbool.h"
#include "cshape/loggers.h"

const static Logger& logger = Logger::getInstance("cshape.rbool");


template<typename T>
constexpr T SubSetR1<T>::NEGINF;
template<typename T>
constexpr T SubSetR1<T>::POSINF;

//
//
//
// Compare
//
//
//

template<typename T>
bool IntervalR1<T>::operator== (const IntervalR1<T> &other) const
{
    return this->start == other.start
        && this->end == other.end
        && this->closed_left == other.closed_left
        && this->closed_right == other.closed_right;
}

template<typename T>
bool SubSetR1<T>::operator==(const SubSetR1<T> &other) const
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


template<typename T>
SubSetR1<T> string_to_subset(const std::string &str);
template<typename T>
SubSetR1Typo find_typo(const std::vector<T> &finites,
                       const std::vector<IntervalR1<T>> &intervals);

// Clone
template<typename T>
SubSetR1<T>::SubSetR1(const SubSetR1<T> &other): finites(other.finites), intervals(other.intervals), typo(other.typo){};

template<typename T>
SubSetR1<T>::SubSetR1(const std::string &str):SubSetR1<T>(
    string_to_subset<T>(str).finites,
    string_to_subset<T>(str).intervals) {} ;

template<typename T>
SubSetR1<T>::SubSetR1(const std::vector<T> &finites,
                   const std::vector<IntervalR1<T>> &intervals):
    finites(finites), intervals(intervals), typo(find_typo(finites, intervals))
    {
        logger << "Inside SubSetR1<T> constructor" << ENDL;
        logger << "Finites = {";
        for (auto finite : finites)
        {
            logger << finite << ", ";
        }
        logger << "}" << ENDL;
        logger << "Intervals = ";
        for (auto interval : intervals)
        {
            logger << interval << " U ";
        }
        logger << "}" << ENDL;
        const size_t fsize = finites.size();
        const size_t isize = intervals.size();
        for (size_t i = 0; i + 1 < fsize; ++i)
            if (finites[i] >= finites[i+1])
                throw std::invalid_argument("Not ordered vector!");
        for (size_t i = 0; i + 1 < isize; ++i){
            if (intervals[i].end ==  SubSetR1<T>::POSINF)
                throw std::invalid_argument("Only last interval can end with POSINF");         
            if (intervals[i+1].start == SubSetR1<T>::NEGINF)
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

template<typename T>
const SubSetR1<T> SubSetR1<T>::Empty()
{
    return SubSetR1<T>({}, {});
}

template<typename T>
const SubSetR1<T> SubSetR1<T>::Whole()
{
    IntervalR1<T> interval = {SubSetR1<T>::NEGINF,  SubSetR1<T>::POSINF, CLOSED_INF, CLOSED_INF};
    return SubSetR1<T>({}, {interval});
}

template<typename T>
const SubSetR1<T> SubSetR1<T>::Point(const T &value)
{
    return SubSetR1<T>({value}, {});
}

template<typename T>
const SubSetR1<T> SubSetR1<T>::Lower(const T &value, const bool closed){
    IntervalR1<T> interval {SubSetR1<T>::NEGINF, value, CLOSED_INF, closed};
    return SubSetR1<T>({}, {interval});
}

template<typename T>
const SubSetR1<T> SubSetR1<T>::Bigger(const T &value, const bool closed)
{
    IntervalR1<T> interval {value, SubSetR1<T>::POSINF, closed, CLOSED_INF};
    return SubSetR1<T>({}, {interval});
}

template<typename T>
const SubSetR1<T> SubSetR1<T>::Between(const T &sta,
                                       const T &end,
                                       const bool closed_left,
                                       const bool closed_right)
{
    IntervalR1<T> interval {sta, end, closed_left, closed_right};
    return SubSetR1<T>({}, {interval});
}

//
//
//
//  Boolean operations
//
//
//

template<typename T>
void compute_middle(const std::vector<T> &knots,
                    const std::vector<bool> &inside,
                    std::vector<T> &finites,
                    std::vector<IntervalR1<T>> &intervals);

template<typename T>
SubSetR1<T> SubSetR1<T>::operator~() const
{
    logger << "Begin SubSetR1<T>::operator~" << ENDL;
    logger << *this << ENDL;
    switch (typo)
    {
        case SubSetR1Typo::Empty:
            logger << "Return Whole" << ENDL;
            return SubSetR1<T>::Whole();
        case SubSetR1Typo::Whole:
            logger << "Return Empty" << ENDL;
            return SubSetR1<T>::Empty();
        case SubSetR1Typo::Point:
        {
            IntervalR1<T> left = {NEGINF, this->finites[0], CLOSED_INF, false};
            IntervalR1<T> right = {this->finites[0],  SubSetR1<T>::POSINF, false, CLOSED_INF};
            SubSetR1<T> inverted = SubSetR1<T>({}, {left, right});
            logger << "Return " << inverted << ENDL;
            return inverted;
        }
        case SubSetR1Typo::Interval:
        {
            const IntervalR1<T> interval = this->intervals[0];
            if (interval.start == SubSetR1<T>::NEGINF)
            {
                SubSetR1<T> inverted = SubSetR1<T>::Bigger(interval.end, !interval.closed_right);
                logger << "Return " << inverted << ENDL;
                return inverted;
            }
            else if (interval.end ==  SubSetR1<T>::POSINF)
            {
                SubSetR1<T> inverted = SubSetR1<T>::Lower(interval.start, !interval.closed_left);
                logger << "Return " << inverted << ENDL;
                return inverted;
            }
            IntervalR1<T> left = {NEGINF, this->intervals[0].start, CLOSED_INF, !this->intervals[0].closed_left};
            IntervalR1<T> right = {this->intervals[0].end,  SubSetR1<T>::POSINF, !this->intervals[0].closed_right, CLOSED_INF};
            SubSetR1<T> inverted = SubSetR1<T>({}, {left, right});
            logger << "Return " << inverted << ENDL;
            return inverted;
        }
        case SubSetR1Typo::Disjoint:
        {
            std::set<T> setknots = {NEGINF,  SubSetR1<T>::POSINF};
            for (const T point : this->finites)
                setknots.insert(point);
            for (const IntervalR1<T> interval : this->intervals)
            {
                setknots.insert(interval.start);
                setknots.insert(interval.end);
            }
            setknots.erase(NEGINF);
            setknots.erase(POSINF);
            std::vector<bool> inside(2 * setknots.size() + 1, false);
            const std::vector<T> knots(setknots.begin(), setknots.end());

            inside[0] = !this->contains(knots[0] - 1);
            for (size_t i = 0; i < knots.size(); ++i)
                inside[2*i + 1] = !this->contains(knots[i]);
            for (size_t i = 1; i < knots.size(); ++i){
                const T middle = (knots[i-1] + knots[i]) / 2;
                inside[2 * i] = !this->contains(middle);
            }
            const T last = knots[knots.size() - 1] + 1;
            inside[2 * knots.size()] = !this->contains(last);

            std::vector<T> finites;
            std::vector<IntervalR1<T>> intervals;
            compute_middle(knots, inside, finites, intervals);
            SubSetR1<T> inverted = SubSetR1<T>(finites, intervals);
            logger << "Return " << inverted << ENDL;
            return inverted;
        }
        default:
            throw std::invalid_argument("Wrong typo");
    }
};


template<typename T>
SubSetR1<T> SubSetR1<T>::operator|(const SubSetR1<T> &other) const
{
    logger << "Begin SubSetR1<T>::operator|" << ENDL;
    logger << *this << " | " << other << ENDL;
    if (this->contains(other))  // Take cares of whole |= other or *this |= empty
        return *this;
    if (other.contains(*this))  // Take cares of empty |= other or *this |= whole
        return other;

    std::set<T> setknots = {NEGINF,  SubSetR1<T>::POSINF};
    for (const T point : this->finites)
        setknots.insert(point);
    for (const T point : other.finites)
        setknots.insert(point);
    for (const IntervalR1<T> interval : this->intervals)
    {
        setknots.insert(interval.start);
        setknots.insert(interval.end);
    }
    for (const IntervalR1<T> interval : other.intervals)
    {
        setknots.insert(interval.start);
        setknots.insert(interval.end);
    }
    setknots.erase(NEGINF);
    setknots.erase(POSINF);
    
    const std::vector<T> knots(setknots.begin(), setknots.end());
    std::vector<bool> inside(2 * knots.size() + 1, false);

    inside[0] = this->contains(knots[0] - 1) || other.contains(knots[0] - 1);
    for (size_t i = 0; i < knots.size(); ++i)
        inside[2*i + 1] = this->contains(knots[i]) || other.contains(knots[i]);
    for (size_t i = 1; i < knots.size(); ++i){
        const T midknot = (knots[i - 1] + knots[i]) / 2;
        inside[2 * i] = this->contains(midknot) || other.contains(midknot);
    }
    const T last = knots[knots.size() - 1] + 1;
    inside[2 * knots.size()] = this->contains(last) || other.contains(last);
    
    std::vector<T> finites;
    std::vector<IntervalR1<T>> intervals;
    compute_middle(knots, inside, finites, intervals);
    return SubSetR1<T>(finites, intervals);
};


template<typename T>
SubSetR1<T> SubSetR1<T>::operator&(const SubSetR1<T> &other) const
{
    logger << "Begin SubSetR1<T>::operator&" << ENDL;
    logger << *this << " & " << other << ENDL;
    if (this->contains(other))  // Take cares of whole |= other or *this |= empty
        return other;
    if (other.contains(*this))  // Take cares of empty |= other or *this |= whole
        return *this;

    std::set<T> setknots = {NEGINF,  SubSetR1<T>::POSINF};
    for (const T point : this->finites)
        setknots.insert(point);
    for (const T point : other.finites)
        setknots.insert(point);
    for (const IntervalR1<T> interval : this->intervals)
    {
        setknots.insert(interval.start);
        setknots.insert(interval.end);
    }
    for (const IntervalR1<T> interval : other.intervals)
    {
        setknots.insert(interval.start);
        setknots.insert(interval.end);
    }
    setknots.erase(NEGINF);
    setknots.erase(POSINF);

    const std::vector<T> knots(setknots.begin(), setknots.end());
    std::vector<bool> inside(2 * knots.size() + 1, false);

    inside[0] = this->contains(knots[0] - 1) && other.contains(knots[0] - 1);
    for (size_t i = 0; i < knots.size(); ++i)
        inside[2*i + 1] = this->contains(knots[i]) && other.contains(knots[i]);
    for (size_t i = 1; i < knots.size(); ++i){
        const T midknot = (knots[i-1] + knots[i]) / 2;
        inside[2*i] = this->contains(midknot) && other.contains(midknot);
    }
    const T last = knots[knots.size() - 1] + 1;
    inside[2 * knots.size()] = this->contains(last) && other.contains(last);

    std::vector<T> finites;
    std::vector<IntervalR1<T>> intervals;
    compute_middle(knots, inside, finites, intervals);
    return SubSetR1<T>(finites, intervals);
};

template<typename T>
void compute_middle(const std::vector<T> &knots,
                    const std::vector<bool> &inside,
                    std::vector<T> &finites,
                    std::vector<IntervalR1<T>> &intervals)
{
    logger << "Inside 'compute_middle'" << ENDL;
    logger << "Received knots: {" << knots[0];
    for (size_t i = 1; i < knots.size(); ++i)
        logger << ", " << knots[i];
    logger << "}" << ENDL;
    logger << "Received inside: {" << inside[0];
    for (size_t i = 1; i < inside.size(); ++i)
        logger << ", " << inside[i];
    logger << "}" << ENDL;
    T start = SubSetR1<T>::NEGINF;
    bool closed = false;
    for(size_t i = 0; i < knots.size(); ++i){
        const T &knot = knots[i];
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
    if (inside.back())
    {
        intervals.push_back({start, SubSetR1<T>::POSINF, closed, CLOSED_INF});
    }
}


// 
//
//
//  Printing implementations
// 
//
//

template<typename T>
std::ostream &operator<<(std::ostream &os, const IntervalR1<T> &obj){
    os << ((obj.start == SubSetR1<T>::NEGINF || !obj.closed_left) ? "(" : "[");
    os << obj.start << ", " << obj.end;
    os << ((obj.end ==  SubSetR1<T>::POSINF || !obj.closed_right) ? ")" : "]");
    return os;
}

template<typename T>
SubSetR1<T>::operator std::string() const{
    std::ostringstream stream;
    stream << *this;
    return stream.str();
}


template<typename T>
std::ostream &operator<<(std::ostream &os, const SubSetR1<T> &obj){
    switch (obj.typo)
    {
        case SubSetR1Typo::Empty:
            return os << "{}";
        case SubSetR1Typo::Whole:
            return os << "(" << SubSetR1<T>::NEGINF << ", " <<  SubSetR1<T>::POSINF << ")";        
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
    std::vector<T> finis;
    bool first = true;
    bool flag = false;
    size_t i = 0, f = 0;
    
    if (obj.intervals[0].start == SubSetR1<T>::NEGINF){
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

template<typename T>
bool IntervalR1<T>::contains(const T &other) const
{
    return (this->start < other || (this->closed_left && this->start == other))
        && (other < this->end || (this->closed_right && this->end == other));
}


template<typename T>
bool IntervalR1<T>::contains(const IntervalR1<T> &other) const
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

template<typename T>
bool SubSetR1<T>::contains(const T &other) const{
    for(const IntervalR1<T> interval : this->intervals)
        if(interval.contains(other))
            return true;
    for(const T point : this->finites)
        if(point == other)
            return true;
    return false;
}

template<typename T>
bool SubSetR1<T>::contains(const IntervalR1<T> &other) const{
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
            for (const IntervalR1<T> interval : this->intervals)
                if (interval.contains(other))
                    return true;
            return false;
        default:
            throw std::invalid_argument("Received wrong type");
    }
}

template<typename T>
bool SubSetR1<T>::contains(const SubSetR1<T> &other) const{
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
            for (const T point : other.finites)
                if (!this->contains(point))
                    return false;
            for (const IntervalR1<T> interval : other.intervals)
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



template<typename T>
IntervalR1<T> string_to_interval(const std::string &str) {
    const size_t size = str.size();
    bool closed_left = (str[0] == '[');
    bool closed_right = (str[size - 1] == ']');
    size_t virg = 1;
    while (virg < size && str[virg] != ',')
        ++virg;
    if (virg == size)
        throw std::invalid_argument("Invalid string to convert to interval");
    const T first = string_to_scalar(str.substr(1, virg - 1));
    const T second = string_to_scalar(str.substr(virg + 1, size - virg - 2));
    if (first == SubSetR1<T>::NEGINF)
        closed_left = true;
    if (second ==  SubSetR1<T>::POSINF)
        closed_right = true;
    return {first, second, closed_left, closed_right};
};




template<typename T>
SubSetR1Typo find_typo(const std::vector<T> &finites,
                       const std::vector<IntervalR1<T>> &intervals)
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
    if (intervals[0].start == SubSetR1<T>::NEGINF && intervals[0].end ==  SubSetR1<T>::POSINF)
    {
        return SubSetR1Typo::Whole;
    }
    return SubSetR1Typo::Interval;
}


const static std::string EMPTYSTR = std::string(SubSetR1<Scalar>::Empty());
const static std::string WHOLESTR = std::string(SubSetR1<Scalar>::Whole());


template<typename T>
SubSetR1<T> string_to_subset(const std::string &str)
{
    if (str == EMPTYSTR)
        return SubSetR1<T>::Empty();
    if (str == WHOLESTR)
        return SubSetR1<T>::Whole();
    const size_t size = str.size();
    std::vector<T> finites;
    std::vector<IntervalR1<T>> intervals;
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
                const T new_value = string_to_scalar(sub.substr(i, j - i));
                finites.push_back(new_value);
                i = j + 1;
            }
            continue;
        }else{
            intervals.push_back(string_to_interval<T>(sub));
        }
        sta = end+1;
    }
    return SubSetR1<T>(finites, intervals);
}
