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
    Point();
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

class Curve
{
private:
    const KnotVector knotvector;
    const Array<parameter> spectre;
    const std::vector<coordinate> xcoords;
    const std::vector<coordinate> ycoords;
    const std::vector<coordinate> weights;

public:
    Curve(const KnotVector &knotvector,
          const std::vector<coordinate> xcoords,
          const std::vector<coordinate> ycoords);
    Curve(const KnotVector &knotvector,
          const std::vector<coordinate> xcoords,
          const std::vector<coordinate> ycoords,
          const std::vector<coordinate> weights);
    ~Curve() = default;
    Point operator()(parameter node) const;
};

#endif