/*
Copyright Rene Rivera 2008-2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_OS_BEOS_H
#define BOOST_PREDEF_OS_BEOS_H

#include <b/predef/version_number.h>
#include <b/predef/make.h>

/* tag::reference[]
= `BOOST_OS_BEOS`

http://en.wikipedia.org/wiki/BeOS[BeOS] operating system.

[options="header"]
|===
| {predef_symbol} | {predef_version}

| `+__BEOS__+` | {predef_detection}
|===
*/ // end::reference[]

#define BOOST_OS_BEOS BOOST_VERSION_NUMBER_NOT_AVAILABLE

#if !defined(BOOST_PREDEF_DETAIL_OS_DETECTED) && ( \
    defined(__BEOS__) \
    )
#   undef BOOST_OS_BEOS
#   define BOOST_OS_BEOS BOOST_VERSION_NUMBER_AVAILABLE
#endif

#if BOOST_OS_BEOS
#   define BOOST_OS_BEOS_AVAILABLE
#   include <b/predef/detail/os_detected.h>
#endif

#define BOOST_OS_BEOS_NAME "BeOS"

#endif

#include <b/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_OS_BEOS,BOOST_OS_BEOS_NAME)
