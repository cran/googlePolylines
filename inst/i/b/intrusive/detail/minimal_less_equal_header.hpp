/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2015
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTRUSIVE_DETAIL_MINIMAL_LESS_EQUAL_HEADER_HPP
#define BOOST_INTRUSIVE_DETAIL_MINIMAL_LESS_EQUAL_HEADER_HPP
#
#ifndef BOOST_CONFIG_HPP
#  include <b/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif
#
#//Try to avoid including <functional>, as it's quite big in C++11
#if defined(BOOST_GNU_STDLIB)
#  include <bits/stl_function.h>
#else
#  include <functional>    //Fallback
#endif
#
#endif //BOOST_INTRUSIVE_DETAIL_MINIMAL_LESS_EQUAL_HEADER_HPP
