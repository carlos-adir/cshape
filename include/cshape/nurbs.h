#pragma once

#ifndef NURBS_H
#define NURBS_H

#include <iostream>
#include <vector>

typedef double parameter;
typedef double coordinate;
typedef unsigned short ushort;

template <typename T>
class Array
{
private:
    std::vector<T> data;

public:
    Array(const std::vector<ushort> inshape);
    ~Array() = default;
    const T &operator[](const std::vector<ushort> indexs) const;
    T &operator[](const std::vector<ushort> indexs);
    const ushort ndim;
    const std::vector<ushort> shape;
};

class Point
{
public:
    const coordinate x, y;
    Point(const coordinate &x, const coordinate &y);
    ~Point() = default;
    coordinate inner(const Point &other) const;
    coordinate cross(const Point &other) const;
    void move(const coordinate &dx, const coordinate &dy);
    void move(const Point &other);
    const coordinate &operator[](const ushort &index) const;
};

class KnotVector
{
private:
    const std::vector<parameter> internal;

public:
    KnotVector(const std::vector<parameter> &init_vector);
    ~KnotVector() = default;
    const parameter &operator[](const ushort index) const;
    const ushort degree;
    const ushort npts;
    const std::vector<parameter> knots;
    const std::vector<parameter> spans;
    ushort span(const parameter &node) const;
    ushort mult(const parameter &node) const;
};

std::ostream &operator<<(std::ostream &os, const KnotVector &knotvector);

namespace GeneratorKnotVector
{
    KnotVector bezier(const ushort degree);
    KnotVector uniform(const ushort degree, const ushort npts);
};

class Basis
{
private:
    const KnotVector knotvector;
    const Array<parameter> spectre;

public:
    Basis(const KnotVector &knotvector);
    ~Basis() = default;
    parameter operator()(parameter node, const ushort index) const;
    void evaluate(parameter node, std::vector<parameter> &output) const;
};

#endif