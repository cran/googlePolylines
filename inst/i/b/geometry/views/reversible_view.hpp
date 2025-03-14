// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020-2023.
// Modifications copyright (c) 2020-2023 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_REVERSIBLE_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_REVERSIBLE_VIEW_HPP


#include <b/version.hpp>
#include <b/range/adaptor/reversed.hpp>

#include <b/geometry/core/closure.hpp>
#include <b/geometry/core/point_order.hpp>
#include <b/geometry/core/ring_type.hpp>
#include <b/geometry/core/tag.hpp>
#include <b/geometry/core/tags.hpp>

#include <b/geometry/util/order_as_direction.hpp>

#include <b/geometry/views/identity_view.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template
<
    typename Range,
    order_selector Order = geometry::point_order<Range>::value
>
struct clockwise_view
    : identity_view<Range>
{
    explicit inline clockwise_view(Range& r)
        : identity_view<Range>(r)
    {}
};

template <typename Range>
struct clockwise_view<Range, counterclockwise>
    : boost::reversed_range<Range>
{
    explicit inline clockwise_view(Range& r)
        : boost::reversed_range<Range>(r)
    {}
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
\brief View on a range, reversing direction if necessary
\tparam Range original range
\tparam Direction direction of iteration
\ingroup views
*/
template <typename Range, iterate_direction Direction>
struct reversible_view {};


#ifndef DOXYGEN_NO_SPECIALIZATIONS

template <typename Range>
struct reversible_view<Range, iterate_forward>
{
    using type = identity_view<Range>;
};


template <typename Range>
struct reversible_view<Range, iterate_reverse>
{
    using type = boost::reversed_range<Range>;
};

#endif // DOXYGEN_NO_SPECIALIZATIONS


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{


template <typename Range, order_selector Order>
struct tag<geometry::detail::clockwise_view<Range, Order> >
    : geometry::tag<Range>
{};

template <typename Range, order_selector Order>
struct point_order<geometry::detail::clockwise_view<Range, Order> >
{
    static const order_selector value = clockwise;
};

template <typename Range, order_selector Order>
struct closure<geometry::detail::clockwise_view<Range, Order> >
    : geometry::closure<Range>
{};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_REVERSIBLE_VIEW_HPP
