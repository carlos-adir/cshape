#pragma once

#ifndef PARAMETER_H
#define PARAMETER_H

#include <iostream>
#include <limits>

class Parameter {
private:
    double internal;
public:
    Parameter() : internal(0) {};

    template<typename T>
    Parameter(const T val);
    
    operator double() const { return internal; }
    
    bool operator==(const Parameter &other) const;
    bool operator!=(const Parameter &other) const;
    bool operator<(const Parameter &other) const;
    bool operator>(const Parameter &other) const;
    bool operator<=(const Parameter &other) const;
    bool operator>=(const Parameter &other) const;
    template<typename T>
    bool operator==(const T &other) const;
    template<typename T>
    bool operator!=(const T &other) const;
    template<typename T>
    bool operator<(const T &other) const;
    template<typename T>
    bool operator>(const T &other) const;
    template<typename T>
    bool operator<=(const T &other) const;
    template<typename T>
    bool operator>=(const T &other) const;
    
    template<typename T>
    Parameter &operator=(const T& val);
    Parameter &operator=(const Parameter& val);
    Parameter &operator+=(const Parameter& rhs);
    Parameter &operator-=(const Parameter& rhs);
    Parameter &operator*=(const Parameter& rhs);
    Parameter &operator/=(const Parameter& rhs);
    Parameter operator+(const Parameter& rhs) const;
    Parameter operator-(const Parameter& rhs) const;
    Parameter operator*(const Parameter& rhs) const;
    Parameter operator/(const Parameter& rhs) const;

    static const Parameter NEGINF;
    static const Parameter POSINF;
    
    friend std::ostream &operator<<(std::ostream &os, const Parameter &param);
};







#endif