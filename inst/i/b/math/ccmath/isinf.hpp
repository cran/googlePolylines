//  (C) Copyright Matt Borland 2021.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_CCMATH_ISINF
#define BOOST_MATH_CCMATH_ISINF

#include <b/math/special_functions/fpclassify.hpp>
#include <b/math/ccmath/detail/config.hpp>

#ifdef BOOST_MATH_NO_CCMATH
#error "The header <b/math/isinf.hpp> can only be used in C++17 and later."
#endif

namespace boost::math::ccmath {

template <typename T>
constexpr bool isinf BOOST_MATH_PREVENT_MACRO_SUBSTITUTION(T x) noexcept
{
    if(BOOST_MATH_IS_CONSTANT_EVALUATED(x))
    {
        if constexpr (std::numeric_limits<T>::is_signed)
        {
#if defined(__clang_major__) && __clang_major__ >= 6
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wtautological-constant-compare"
#endif
            return x == std::numeric_limits<T>::infinity() || -x == std::numeric_limits<T>::infinity();
#if defined(__clang_major__) && __clang_major__ >= 6
#pragma clang diagnostic pop
#endif
        }
        else
        {
            return x == std::numeric_limits<T>::infinity();
        }
    }
    else
    {
        using boost::math::isinf;

        if constexpr (!std::is_integral_v<T>)
        {
            return (isinf)(x);
        }
        else
        {
            return (isinf)(static_cast<double>(x));
        }
    }
}

}

#endif // BOOST_MATH_CCMATH_ISINF
