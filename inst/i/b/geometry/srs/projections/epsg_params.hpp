// Boost.Geometry

// Copyright (c) 2017-2022, Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP


#include <string>

#include <b/geometry/srs/spheroid.hpp>


namespace boost { namespace geometry
{

namespace srs
{


struct epsg
{
    explicit epsg(int c)
        : code(c)
    {}

    int code;
};


template <int Code>
struct static_epsg
{
    static const int code = Code;
};


} // namespace srs


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_EPSG_PARAMS_HPP
