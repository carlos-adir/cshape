#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include <vector>
#include "rbool.h"
#include "analytic.h"


template<typename O>
struct GeometricPoint
{
    public:
        const O xcoord;
        const O ycoord;
};


template<typename O>
struct GeometricBox
{
    public:
        const O xmin;
        const O xmax;
        const O ymin;
        const O ymax;
};

template<typename O>
bool contains(const GeometricBox<O> &box, GeometricPoint<O> &point);


template<typename O>
class IGeometricCurve {};

template<typename I, typename O>
class IParametricCurve : public IGeometricCurve<O>
{
    public:
        const SubSetR1<I> domain;
        virtual GeometricPoint<O> eval(const I& node, const uint1 deriv = 0) const = 0;
};

template<typename I, typename O>
class ParametricSegment : public IParametricCurve<I, O>
{
    public:
        const std::unique_ptr<const IAnalytic<I, O>> xfunc;
        const std::unique_ptr<const IAnalytic<I, O>> yfunc;
        ParametricSegment(const IAnalytic<I, O>& xfunc, const IAnalytic<I, O>& yfunc);
        ~ParametricSegment();

        virtual GeometricPoint<O> eval(const I& node, const uint1 deriv = 0) const override;
};


#endif
