
#include "cshape/geometry.h"

template<typename I, typename O>
ParametricSegment<I, O>::ParametricSegment(const IAnalytic<I, O>& xfunc, const IAnalytic<I, O>& yfunc) : xfunc(std::move(xfunc.clone())), yfunc(std::move(yfunc.clone())) {}


template<typename I, typename O>
ParametricSegment<I, O>::~ParametricSegment()
{
    delete xfunc;
    delete yfunc;
}

template<typename I, typename O>
GeometricPoint<O> ParametricSegment<I, O>::eval(const I& node, const uint1 deriv) const
{
    const O xcoord = xfunc(node, deriv);
    const O ycoord = yfunc(node, deriv);
    return Geometric(xcoord, ycoord);
}


template<typename O>
bool contains(const GeometricBox<O>& box, const GeometricPoint<O>& point)
{
    return box.xmin <= point.xcoord
        && point.xcoord <= box.xmax
        && box.ymin <= point.ycoord
        && point.ycoord <= box.ymax;
}