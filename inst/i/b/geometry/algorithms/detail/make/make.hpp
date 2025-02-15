// Boost.Geometry

// Copyright (c) 2019 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_MAKE_MAKE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_MAKE_MAKE_HPP

#include <b/geometry/geometries/infinite_line.hpp>
#include <b/geometry/core/access.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace make
{

template <typename Type, typename Coordinate1, typename Coordinate2>
inline
model::infinite_line<Type> make_infinite_line(Coordinate1 const& x1,
    Coordinate1 const& y1, Coordinate2 const& x2, Coordinate2 const& y2)
{
    model::infinite_line<Type> result;
    result.a = y1 - y2;
    result.b = x2 - x1;
    result.c = -result.a * x1 - result.b * y1;
    return result;
}

template <typename Type, typename PointA, typename PointB>
inline
model::infinite_line<Type> make_infinite_line(PointA const& a, PointB const& b)
{
    return make_infinite_line<Type>(geometry::get<0>(a), geometry::get<1>(a),
        geometry::get<0>(b), geometry::get<1>(b));
}

template <typename Type, typename Segment>
inline
model::infinite_line<Type> make_infinite_line(Segment const& segment)
{
    return make_infinite_line<Type>(geometry::get<0, 0>(segment),
        geometry::get<0, 1>(segment),
        geometry::get<1, 0>(segment),
        geometry::get<1, 1>(segment));
}

template <typename Type, typename PointA, typename PointB, typename PointC>
inline
model::infinite_line<Type> make_perpendicular_line(PointA const& a, PointB const& b, PointC const& c)
{
    // https://www.math-only-math.com/equation-of-a-line-perpendicular-to-a-line.html
    model::infinite_line<Type> const line = make_infinite_line<Type>(a, b);
    model::infinite_line<Type> result;
    result.a = line.b;
    result.b = -line.a;
    // Lines with any result.c are perpendicular to a->b
    // Calculate this result such that it goes through point c
    result.c = -result.a * geometry::get<0>(c) - result.b * geometry::get<1>(c);
    return result;
}

}} // namespace detail::make
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_MAKE_MAKE_HPP
