
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_IS_MEMBER_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_IS_MEMBER_FUNCTION_POINTER_HPP_INCLUDED

#include <b/mpl/aux_/lambda_support.hpp>

#include <b/function_types/components.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template< typename T, typename Tag = null_tag > 
    struct is_member_function_pointer
      : function_types::represents
        < function_types::components<T>
        , function_types::tag<Tag ,detail::member_function_pointer_tag> >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,is_member_function_pointer,(T,Tag))
    };
  }
} 
#endif 

