// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2023 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2024.
// Modifications copyright (c) 2014-2024 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPS_OR_SPIKES_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPS_OR_SPIKES_HPP


#include <type_traits>

#include <b/range/begin.hpp>
#include <b/range/end.hpp>
#include <b/range/size.hpp>
#include <b/static_assert.hpp>

#include <b/geometry/algorithms/append.hpp>
#include <b/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <b/geometry/algorithms/detail/point_is_spike_or_equal.hpp>
#include <b/geometry/algorithms/detail/equals/point_point.hpp>

#include <b/geometry/core/closure.hpp>

#include <b/geometry/util/constexpr.hpp>
#include <b/geometry/util/range.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace overlay
{

// TODO: move this / rename this
template <typename Point1, typename Point2, typename Strategy>
inline bool points_equal_or_close(Point1 const& point1,
                                  Point2 const& point2,
                                  Strategy const& strategy)
{
    if (detail::equals::equals_point_point(point1, point2, strategy))
    {
        return true;
    }
    return false;
}


template <typename Range, typename Point, typename Strategy>
inline void append_no_dups_or_spikes(Range& range, Point const& point,
                                     Strategy const& strategy)
{
#ifdef BOOST_GEOMETRY_DEBUG_INTERSECTION
    std::cout << "  add: ("
        << geometry::get<0>(point) << ", " << geometry::get<1>(point) << ")"
        << std::endl;
#endif
    // The code below this condition checks all spikes/dups
    // for geometries >= 3 points.
    // So we have to check the first potential duplicate differently
    if ( boost::size(range) == 1
      && points_equal_or_close(*(boost::begin(range)), point, strategy) )
    {
        return;
    }

    auto append = [](auto& r, auto const& p)
    {
        using point_t = typename boost::range_value<Range>::type;
        point_t rp;
        geometry::detail::conversion::convert_point_to_point(p, rp);
        traits::push_back<Range>::apply(r, std::move(rp));
    };

    append(range, point);


    // If a point is equal, or forming a spike, remove the pen-ultimate point
    // because this one caused the spike.
    // If so, the now-new-pen-ultimate point can again cause a spike
    // (possibly at a corner). So keep doing this.
    // Besides spikes it will also avoid adding duplicates.
    while(boost::size(range) >= 3
            && point_is_spike_or_equal(point,
                *(boost::end(range) - 3),
                *(boost::end(range) - 2),
                strategy.side() // TODO: Pass strategy?
                ))
    {
        // Use the Concept/traits, so resize and append again
        traits::resize<Range>::apply(range, boost::size(range) - 2);
        append(range, point);
    }
}

template <typename Range, typename Point, typename Strategy>
inline void append_no_collinear(Range& range, Point const& point,
                                Strategy const& strategy)
{
    // Stricter version, not allowing any point in a linear row
    // (spike, continuation or same point)

    // The code below this condition checks all spikes/dups
    // for geometries >= 3 points.
    // So we have to check the first potential duplicate differently
    if ( boost::size(range) == 1
      && points_equal_or_close(*(boost::begin(range)), point,
                               strategy) )
    {
        return;
    }

    traits::push_back<Range>::apply(range, point);

    // If a point is equal, or forming a spike, remove the pen-ultimate point
    // because this one caused the spike.
    // If so, the now-new-pen-ultimate point can again cause a spike
    // (possibly at a corner). So keep doing this.
    // Besides spikes it will also avoid adding duplicates.
    while(boost::size(range) >= 3
            && point_is_collinear(point,
                *(boost::end(range) - 3),
                *(boost::end(range) - 2),
                strategy.side() // TODO: Pass strategy?
                ))
    {
        // Use the Concept/traits, so resize and append again
        traits::resize<Range>::apply(range, boost::size(range) - 2);
        traits::push_back<Range>::apply(range, point);
    }
}

// Should only be called internally, from traverse.
template <typename Ring, typename Strategy>
inline void remove_spikes_at_closure(Ring& ring, Strategy const& strategy)
{
    // It assumes a closed ring (whatever the closure value)
    constexpr std::size_t min_size
            = core_detail::closure::minimum_ring_size
                    <
                        geometry::closed
                    >::value;

    if (boost::size(ring) < min_size)
    {
        // Don't act on too small rings.
        return;
    }

    bool found = false;
    do
    {
        found = false;
        auto const first = boost::begin(ring);
        auto const second = first + 1;
        auto const penultimate = boost::end(ring) - 2;

        // Check if closing point is a spike (this is so if the second point is
        // considered as collinear w.r.t. the last segment)
        if (point_is_collinear(*second, *penultimate, *first,
                               strategy.side() // TODO: Pass strategy?
                               ))
        {
            // Remove first point and last point
            range::erase(ring, first);
            range::resize(ring, boost::size(ring) - 1);
            // Close the ring again
            range::push_back(ring, range::front(ring));

            found = true;
        }
    } while (found && boost::size(ring) >= min_size);
}

template <typename Ring, typename Strategy>
inline void fix_closure(Ring& ring, Strategy const& strategy)
{
    if BOOST_GEOMETRY_CONSTEXPR (geometry::closure<Ring>::value == geometry::open)
    {
        if (! boost::empty(ring)
            && detail::equals::equals_point_point(range::front(ring), range::back(ring), strategy))
        {
            // Correct closure: traversal automatically closes rings.
            // Depending on the geometric configuration,
            // remove_spikes_at_closure can remove the closing point.
            // But it does not always do that. Therefore it is corrected here explicitly.
            range::resize(ring, boost::size(ring) - 1);
        }
    }
}


}} // namespace detail::overlay
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_OVERLAY_APPEND_NO_DUPS_OR_SPIKES_HPP
