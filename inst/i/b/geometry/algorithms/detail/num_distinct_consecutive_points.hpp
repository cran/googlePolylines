// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2023, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_NUM_DISTINCT_CONSECUTIVE_POINTS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_NUM_DISTINCT_CONSECUTIVE_POINTS_HPP


#include <algorithm>
#include <cstddef>

#include <b/range/begin.hpp>
#include <b/range/end.hpp>
#include <b/range/size.hpp>

#include <b/geometry/algorithms/detail/equals/point_point.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


// returns the number of distinct values in the range;
// return values are 0u through MaximumNumber, where MaximumNumber
// corresponds to MaximumNumber or more distinct values
//
// FUTURE: take into account topologically closed ranges;
//         add appropriate template parameter(s) to control whether
//         the closing point for topologically closed ranges is to be
//         accounted for separately or not
template
<
    typename Range,
    std::size_t MaximumNumber,
    bool AllowDuplicates /* true */
>
struct num_distinct_consecutive_points
{
    template <typename Strategy>
    static inline std::size_t apply(Range const& range, Strategy const& strategy)
    {
        std::size_t const size = boost::size(range);

        if ( size < 2u )
        {
            return (size < MaximumNumber) ? size : MaximumNumber;
        }

        auto current = boost::begin(range);
        auto const end = boost::end(range);
        std::size_t counter(0);
        do
        {
            ++counter;
            auto next = std::find_if(current, end, [&](auto const& pt) {
                    return ! equals::equals_point_point(pt, *current, strategy);
                });
            current = next;
        }
        while ( current != end && counter <= MaximumNumber );

        return counter;
    }
};


template <typename Range, std::size_t MaximumNumber>
struct num_distinct_consecutive_points<Range, MaximumNumber, false>
{
    template <typename Strategy>
    static inline std::size_t apply(Range const& range, Strategy const&)
    {
        std::size_t const size = boost::size(range);
        return (size < MaximumNumber) ? size : MaximumNumber;
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_NUM_DISTINCT_CONSECUTIVE_POINTS_HPP
