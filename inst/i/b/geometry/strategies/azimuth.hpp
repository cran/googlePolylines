// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AZIMUTH_HPP
#define BOOST_GEOMETRY_STRATEGIES_AZIMUTH_HPP

#include <b/geometry/core/static_assert.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace azimuth { namespace services
{

/*!
\brief Traits class binding a default azimuth strategy to a coordinate system
\ingroup util
\tparam CSTag tag of coordinate system
\tparam CalculationType \tparam_calculation
*/
template <typename CSTag>
struct default_strategy
{
    BOOST_GEOMETRY_STATIC_ASSERT_FALSE(
        "Not implemented for this type.",
        CSTag);
};

}}} // namespace strategy::azimuth::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_AZIMUTH_HPP
