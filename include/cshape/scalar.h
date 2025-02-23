#ifndef SCALAR_H
#define SCALAR_H
#include <iostream>


typedef double basetype;


class NegativeInfinity;
class PositiveInfinity;


basetype string_to_basetype(const std::string &str){
    return basetype(atof(str.c_str()));
}

    
class NegativeInfinity {
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
    
    virtual bool operator==(const basetype &other) const final;
    virtual bool operator!=(const basetype &other) const final;
    virtual bool operator<(const basetype &other) const final;
    virtual bool operator<=(const basetype &other) const final;
    virtual bool operator>=(const basetype &other) const final;
    virtual bool operator>(const basetype &other) const final;

    virtual bool operator==(const NegativeInfinity &other) const final;
    virtual bool operator!=(const NegativeInfinity &other) const final;
    virtual bool operator<(const NegativeInfinity &other) const final;
    virtual bool operator<=(const NegativeInfinity &other) const final;
    virtual bool operator>=(const NegativeInfinity &other) const final;
    virtual bool operator>(const NegativeInfinity &other) const final;

    virtual bool operator==(const PositiveInfinity &other) const final;
    virtual bool operator!=(const PositiveInfinity &other) const final;
    virtual bool operator<(const PositiveInfinity &other) const final;
    virtual bool operator<=(const PositiveInfinity &other) const final;
    virtual bool operator>=(const PositiveInfinity &other) const final;
    virtual bool operator>(const PositiveInfinity &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const NegativeInfinity &value);
};
    
class PositiveInfinity {
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

    virtual bool operator==(const basetype &other) const final;
    virtual bool operator!=(const basetype &other) const final;
    virtual bool operator<(const basetype &other) const final;
    virtual bool operator<=(const basetype &other) const final;
    virtual bool operator>=(const basetype &other) const final;
    virtual bool operator>(const basetype &other) const final;

    virtual bool operator==(const NegativeInfinity &other) const final;
    virtual bool operator!=(const NegativeInfinity &other) const final;
    virtual bool operator<(const NegativeInfinity &other) const final;
    virtual bool operator<=(const NegativeInfinity &other) const final;
    virtual bool operator>=(const NegativeInfinity &other) const final;
    virtual bool operator>(const NegativeInfinity &other) const final;

    virtual bool operator==(const PositiveInfinity &other) const final;
    virtual bool operator!=(const PositiveInfinity &other) const final;
    virtual bool operator<(const PositiveInfinity &other) const final;
    virtual bool operator<=(const PositiveInfinity &other) const final;
    virtual bool operator>=(const PositiveInfinity &other) const final;
    virtual bool operator>(const PositiveInfinity &other) const final;

    friend std::ostream &operator<< (std::ostream &os, const PositiveInfinity &value);
};



bool NegativeInfinity::operator==(const NegativeInfinity &other) const {
    return true;
};
bool NegativeInfinity::operator!=(const NegativeInfinity &other) const {
    return false;
};
bool NegativeInfinity::operator<(const NegativeInfinity &other) const {
    return false;
};
bool NegativeInfinity::operator<=(const NegativeInfinity &other) const {
    return true;
};
bool NegativeInfinity::operator>=(const NegativeInfinity &other) const {
    return true;
};
bool NegativeInfinity::operator>(const NegativeInfinity &other) const {
    return false;
};

bool NegativeInfinity::operator==(const PositiveInfinity &other) const {
    return false;
};
bool NegativeInfinity::operator!=(const PositiveInfinity &other) const {
    return true;
};
bool NegativeInfinity::operator<(const PositiveInfinity &other) const {
    return true;
};
bool NegativeInfinity::operator<=(const PositiveInfinity &other) const {
    return true;
};
bool NegativeInfinity::operator>=(const PositiveInfinity &other) const {
    return false;
};
bool NegativeInfinity::operator>(const PositiveInfinity &other) const {
    return false;
};


bool PositiveInfinity::operator==(const NegativeInfinity &other) const {
    return false;
};
bool PositiveInfinity::operator!=(const NegativeInfinity &other) const {
    return true;
};
bool PositiveInfinity::operator<(const NegativeInfinity &other) const {
    return false;
};
bool PositiveInfinity::operator<=(const NegativeInfinity &other) const {
    return false;
};
bool PositiveInfinity::operator>=(const NegativeInfinity &other) const {
    return true;
};
bool PositiveInfinity::operator>(const NegativeInfinity &other) const {
    return true;
};

bool PositiveInfinity::operator==(const PositiveInfinity &other) const {
    return true;
};
bool PositiveInfinity::operator!=(const PositiveInfinity &other) const {
    return false;
};
bool PositiveInfinity::operator<(const PositiveInfinity &other) const {
    return false;
};
bool PositiveInfinity::operator<=(const PositiveInfinity &other) const {
    return true;
};
bool PositiveInfinity::operator>=(const PositiveInfinity &other) const {
    return true;
};
bool PositiveInfinity::operator>(const PositiveInfinity &other) const {
    return false;
};



bool NegativeInfinity::operator==(const basetype &other) const {
    return false;
};
bool NegativeInfinity::operator!=(const basetype &other) const {
    return true;
};
bool NegativeInfinity::operator<(const basetype &other) const {
    return true;
};
bool NegativeInfinity::operator<=(const basetype &other) const {
    return true;
};
bool NegativeInfinity::operator>=(const basetype &other) const {
    return false;
};
bool NegativeInfinity::operator>(const basetype &other) const {
    return false;
};

bool PositiveInfinity::operator==(const basetype &other) const {
    return false;
};
bool PositiveInfinity::operator!=(const basetype &other) const {
    return true;
};
bool PositiveInfinity::operator<(const basetype &other) const {
    return false;
};
bool PositiveInfinity::operator<=(const basetype &other) const {
    return false;
};
bool PositiveInfinity::operator>=(const basetype &other) const {
    return true;
};
bool PositiveInfinity::operator>(const basetype &other) const {
    return true;
};




bool operator<(const basetype &lhs, const NegativeInfinity &rhs) {
    return false;
};
bool operator<=(const basetype &lhs, const NegativeInfinity &rhs) {
    return false;
};
bool operator==(const basetype &lhs, const NegativeInfinity &rhs) {
    return false;
}
bool operator!=(const basetype &lhs, const NegativeInfinity &rhs) {
    return true;
}
bool operator>=(const basetype &lhs, const NegativeInfinity &rhs) {
    return true;
}
bool operator>(const basetype &lhs, const NegativeInfinity &rhs) {
    return true;
}

bool operator<(const basetype &lhs, const PositiveInfinity &rhs) {
    return true;
};
bool operator<=(const basetype &lhs, const PositiveInfinity &rhs) {
    return true;
};
bool operator==(const basetype &lhs, const PositiveInfinity &rhs) {
    return false;
}
bool operator!=(const basetype &lhs, const PositiveInfinity &rhs) {
    return true;
}
bool operator>=(const basetype &lhs, const PositiveInfinity &rhs) {
    return false;
}
bool operator>(const basetype &lhs, const PositiveInfinity &rhs) {
    return false;
}








std::ostream &operator<< (std::ostream &os, const NegativeInfinity &value){    
    os << "-inf";
    return os;
}

std::ostream &operator<< (std::ostream &os, const PositiveInfinity &value){    
    os << "+inf";
    return os;
}


static const NegativeInfinity& NEGINF = NegativeInfinity::getInstance();
static const PositiveInfinity& POSINF = PositiveInfinity::getInstance();

#endif
