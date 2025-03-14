// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_LINEAR_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_LINEAR_HPP

#include <b/geometry/algorithms/detail/distance/range_to_geometry_rtree.hpp>
#include <b/geometry/algorithms/detail/distance/strategy_utils.hpp>
#include <b/geometry/algorithms/dispatch/distance.hpp>
#include <b/geometry/algorithms/num_points.hpp>
#include <b/geometry/algorithms/num_segments.hpp>

#include <b/geometry/core/point_type.hpp>

#include <b/geometry/iterators/point_iterator.hpp>
#include <b/geometry/iterators/segment_iterator.hpp>

#include <b/geometry/strategies/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace distance
{


template <typename Linear1, typename Linear2, typename Strategies>
struct linear_to_linear
{
    typedef distance::return_t<Linear1, Linear2, Strategies> return_type;

    static inline return_type apply(Linear1 const& linear1,
                                    Linear2 const& linear2,
                                    Strategies const& strategies,
                                    bool = false)
    {
        if (geometry::num_points(linear1) == 1)
        {
            return dispatch::distance
                <
                    point_type_t<Linear1>,
                    Linear2,
                    Strategies
                >::apply(*points_begin(linear1), linear2, strategies);
        }

        if (geometry::num_points(linear2) == 1)
        {
            return dispatch::distance
                <
                    point_type_t<Linear2>,
                    Linear1,
                    Strategies
                >::apply(*points_begin(linear2), linear1, strategies);
        }

        if (geometry::num_segments(linear2) < geometry::num_segments(linear1))
        {
            return point_or_segment_range_to_geometry_rtree
                <
                    geometry::segment_iterator<Linear2 const>,
                    Linear1,
                    Strategies
                >::apply(geometry::segments_begin(linear2),
                         geometry::segments_end(linear2),
                         linear1,
                         strategies);

        }

        return point_or_segment_range_to_geometry_rtree
            <
                geometry::segment_iterator<Linear1 const>,
                Linear2,
                Strategies
            >::apply(geometry::segments_begin(linear1),
                     geometry::segments_end(linear1),
                     linear2,
                     strategies);
    }
};


}} // namespace detail::distance
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template <typename Linear1, typename Linear2, typename Strategy, typename StrategyTag>
struct distance
    <
        Linear1, Linear2, Strategy,
        linear_tag, linear_tag,
        StrategyTag, false
    > : detail::distance::linear_to_linear
        <
            Linear1, Linear2, Strategy
        >
{};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISTANCE_LINEAR_TO_LINEAR_HPP
