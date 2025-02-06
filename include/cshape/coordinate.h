#pragma once

#ifndef COORDINATE_H
#define COORDINATE_H

#include <iostream>
#include <limits>

class Coordinate {
private:
    double internal;
public:
    Coordinate() : internal(0) {};

    template<typename T>
    Coordinate(const T val);
    
    operator double() const { return internal; }
    
    bool operator==(const Coordinate &other) const;
    bool operator!=(const Coordinate &other) const;
    bool operator<(const Coordinate &other) const;
    bool operator>(const Coordinate &other) const;
    bool operator<=(const Coordinate &other) const;
    bool operator>=(const Coordinate &other) const;
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
    Coordinate &operator=(const T val);
    Coordinate &operator=(const Coordinate& val);
    Coordinate &operator+=(const Coordinate& rhs);
    Coordinate &operator-=(const Coordinate& rhs);
    Coordinate &operator*=(const Coordinate& rhs);
    Coordinate &operator/=(const Coordinate& rhs);
    Coordinate operator+(const Coordinate& rhs) const;
    Coordinate operator-(const Coordinate& rhs) const;
    Coordinate operator*(const Coordinate& rhs) const;
    Coordinate operator/(const Coordinate& rhs) const;

    static const Coordinate NEGINF;
    static const Coordinate POSINF;
    
    friend std::ostream &operator<<(std::ostream &os, const Coordinate &coord);
};



#endif