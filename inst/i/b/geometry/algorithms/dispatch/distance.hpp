// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISTANCE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISTANCE_HPP


#include <b/geometry/algorithms/not_implemented.hpp>

#include <b/geometry/core/reverse_dispatch.hpp>
#include <b/geometry/core/tag.hpp>
#include <b/geometry/core/tag_cast.hpp>
#include <b/geometry/core/tags.hpp>

#include <b/geometry/strategies/detail.hpp>
#include <b/geometry/strategies/distance.hpp>
#include <b/geometry/strategies/distance/services.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry1, typename Geometry2, typename Strategies,
    bool IsUmbrella = strategies::detail::is_umbrella_strategy<Strategies>::value,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::value
>
struct distance_strategy_type
{
    typedef decltype(std::declval<Strategies>().distance(std::declval<Geometry1>(), std::declval<Geometry2>())) type;
};

// TODO: right now legacy single strategy can be passed here in some cases
//       so for now dispatch also by IsUmbrella. Later this could be removed.
template <typename Geometry1, typename Geometry2, typename Strategy, bool Reverse>
struct distance_strategy_type<Geometry1, Geometry2, Strategy, false, Reverse>
{
    typedef Strategy type;
};

template <typename Geometry1, typename Geometry2, typename Strategies>
struct distance_strategy_type<Geometry1, Geometry2, Strategies, true, true>
    : distance_strategy_type<Geometry2, Geometry1, Strategies, true, false>
{};


template
<
    typename Geometry1, typename Geometry2, typename Strategies,
    bool IsDynamicOrGC = util::is_dynamic_geometry<Geometry1>::value
                      || util::is_dynamic_geometry<Geometry2>::value
                      || util::is_geometry_collection<Geometry1>::value
                      || util::is_geometry_collection<Geometry2>::value
>
struct distance_strategy_tag
{
    using type = void;
};

template <typename Geometry1, typename Geometry2, typename Strategies>
struct distance_strategy_tag<Geometry1, Geometry2, Strategies, false>
{
    using type = typename strategy::distance::services::tag
        <
            typename distance_strategy_type<Geometry1, Geometry2, Strategies>::type
        >::type;
};


template
<
    typename Geometry1, typename Geometry2,
    typename Strategy = typename strategies::distance::services::default_strategy
        <
            Geometry1, Geometry2
        >::type,
    typename Tag1 = tag_cast_t
        <
            tag_t<Geometry1>,
            segment_tag,
            box_tag,
            linear_tag,
            areal_tag
        >,
    typename Tag2 = tag_cast_t
        <
            tag_t<Geometry2>,
            segment_tag,
            box_tag,
            linear_tag,
            areal_tag
        >,
    typename StrategyTag = typename distance_strategy_tag
        <
            Geometry1, Geometry2, Strategy
        >::type,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::value
>
struct distance : not_implemented<Tag1, Tag2>
{};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISTANCE_HPP
