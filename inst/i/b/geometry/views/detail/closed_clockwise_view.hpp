// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2023 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_DETAIL_CLOSED_CLOCKWISE_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_DETAIL_CLOSED_CLOCKWISE_VIEW_HPP

#include <type_traits>

#include <b/range/begin.hpp>
#include <b/range/end.hpp>
#include <b/range/iterator.hpp>

#include <b/geometry/views/closeable_view.hpp>
#include <b/geometry/views/reversible_view.hpp>
#include <b/geometry/util/order_as_direction.hpp>
#include <b/geometry/util/type_traits_std.hpp>

namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template
<
    typename Range,
    closure_selector Closure = geometry::closure<Range>::value,
    order_selector Order = geometry::point_order<Range>::value
>
struct closed_clockwise_view
{
    using closed_view = detail::closed_view<Range const, Closure>;
    using view = detail::clockwise_view<closed_view const, Order>;

    explicit inline closed_clockwise_view(Range const& r)
        : m_view(closed_view(r))
    {}

    using iterator = typename boost::range_iterator<view const>::type;
    using const_iterator = typename boost::range_iterator<view const>::type;

    inline const_iterator begin() const { return boost::begin(m_view); }
    inline const_iterator end() const { return boost::end(m_view); }

private:
    view m_view;
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename Range, closure_selector Closure, order_selector Order>
struct tag<geometry::detail::closed_clockwise_view<Range, Closure, Order> >
    : geometry::tag<Range>
{};

template <typename Range, closure_selector Closure, order_selector Order>
struct point_order<geometry::detail::closed_clockwise_view<Range, Closure, Order> >
{
    static const order_selector value = clockwise;
};

template <typename Range, closure_selector Closure, order_selector Order>
struct closure<geometry::detail::closed_clockwise_view<Range, Closure, Order> >
{
    static const closure_selector value = closed;
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_DETAIL_CLOSED_CLOCKWISE_VIEW_HPP
