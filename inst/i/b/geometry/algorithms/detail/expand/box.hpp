// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015-2020.
// Modifications copyright (c) 2015-2020, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_BOX_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_BOX_HPP


#include <b/geometry/algorithms/dispatch/expand.hpp>

#include <b/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// Box + box -> new box containing two input boxes
template
<
    typename BoxOut, typename BoxIn
>
struct expand
    <
        BoxOut, BoxIn,
        box_tag, box_tag
    >
{
    template <typename Strategy>
    static inline void apply(BoxOut& box_out,
                             BoxIn const& box_in,
                             Strategy const& strategy)
    {
        // strategy.expand(box_out, box_in).apply(box_out, box_in);
        using strategy_t = decltype(strategy.expand(box_out, box_in));
        strategy_t::apply(box_out, box_in);
    }
};



} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_INDEXED_HPP
