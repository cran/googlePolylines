
#ifndef BOOST_MPL_UPPER_BOUND_HPP_INCLUDED
#define BOOST_MPL_UPPER_BOUND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <b/mpl/less.hpp>
#include <b/mpl/lambda.hpp>
#include <b/mpl/aux_/na_spec.hpp>
#include <b/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x610))
#   define BOOST_MPL_CFG_STRIPPED_DOWN_UPPER_BOUND_IMPL
#endif

#if !defined(BOOST_MPL_CFG_STRIPPED_DOWN_UPPER_BOUND_IMPL)
#   include <b/mpl/minus.hpp>
#   include <b/mpl/divides.hpp>
#   include <b/mpl/size.hpp>
#   include <b/mpl/advance.hpp>
#   include <b/mpl/begin_end.hpp>
#   include <b/mpl/long.hpp>
#   include <b/mpl/eval_if.hpp>
#   include <b/mpl/prior.hpp>
#   include <b/mpl/deref.hpp>
#   include <b/mpl/apply.hpp>
#   include <b/mpl/aux_/value_wknd.hpp>
#else
#   include <b/mpl/find.hpp>
#   include <b/mpl/bind.hpp>
#endif

#include <b/config.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_STRIPPED_DOWN_UPPER_BOUND_IMPL)

// agurt 23/oct/02: has a wrong complexity etc., but at least it works;
// feel free to contribute a better implementation!
template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    , typename Predicate = less<>
    , typename pred_ = typename lambda<Predicate>::type
    >
struct upper_bound
    : find_if< Sequence, bind2<pred_,T,_> >
{
};

#else

namespace aux {

template<
      typename Distance
    , typename Predicate
    , typename T
    , typename DeferredIterator
    >
struct upper_bound_step_impl;

template< 
      typename Distance
    , typename Predicate
    , typename T
    , typename DeferredIterator
    >
struct upper_bound_step
{
    typedef typename eval_if<
          Distance
        , upper_bound_step_impl<Distance,Predicate,T,DeferredIterator>
        , DeferredIterator
        >::type type;
};
    
template<
      typename Distance
    , typename Predicate
    , typename T
    , typename DeferredIterator
    >
struct upper_bound_step_impl
{
    typedef typename divides< Distance, long_<2> >::type offset_;
    typedef typename DeferredIterator::type iter_;
    typedef typename advance< iter_,offset_ >::type middle_;
    typedef typename apply2<
              Predicate
            , T
            , typename deref<middle_>::type
            >::type cond_;

    typedef typename prior< minus< Distance, offset_ > >::type step_;
    typedef upper_bound_step< offset_,Predicate,T,DeferredIterator > step_forward_;
    typedef upper_bound_step< step_,Predicate,T,next<middle_> > step_backward_;
    typedef typename eval_if<
          cond_
        , step_forward_
        , step_backward_
        >::type type;
};

} // namespace aux

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    , typename Predicate = less<>
    >
struct upper_bound
{
 private:
    typedef typename lambda<Predicate>::type pred_;
    typedef typename size<Sequence>::type size_;

 public:
    typedef typename aux::upper_bound_step<
        size_,pred_,T,begin<Sequence>
        >::type type;
};

#endif // BOOST_MPL_CFG_STRIPPED_DOWN_UPPER_BOUND_IMPL

BOOST_MPL_AUX_NA_SPEC(2, upper_bound)

}}

#endif // BOOST_MPL_UPPER_BOUND_HPP_INCLUDED
