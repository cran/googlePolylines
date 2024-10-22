//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/move for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_MOVE_ALGO_PREDICATE_HPP
#define BOOST_MOVE_ALGO_PREDICATE_HPP

#include <b/move/algo/move.hpp>
#include <b/move/adl_move_swap.hpp>
#include <b/move/algo/detail/basic_op.hpp>
#include <b/move/detail/iterator_traits.hpp>
#include <b/move/detail/destruct_n.hpp>
#include <cassert>

namespace boost {
namespace movelib {

template<class Comp>
struct antistable
{
   BOOST_MOVE_FORCEINLINE explicit antistable(Comp &comp)
      : m_comp(comp)
   {}

   BOOST_MOVE_FORCEINLINE antistable(const antistable & other)
      : m_comp(other.m_comp)
   {}

   template<class U, class V>
   BOOST_MOVE_FORCEINLINE bool operator()(const U &u, const V & v)
   {  return !m_comp(v, u);  }

   BOOST_MOVE_FORCEINLINE const Comp &get() const
   {  return m_comp; }

   private:
   antistable & operator=(const antistable &);
   Comp &m_comp;
};

template<class Comp>
Comp unantistable(Comp comp)
{   return comp;  }

template<class Comp>
Comp unantistable(antistable<Comp> comp)
{   return comp.get();  }

template <class Comp>
class negate
{
   public:
   BOOST_MOVE_FORCEINLINE negate()
   {}

   BOOST_MOVE_FORCEINLINE explicit negate(Comp comp)
      : m_comp(comp)
   {}

   template <class T1, class T2>
   BOOST_MOVE_FORCEINLINE bool operator()(const T1& l, const T2& r)
   {
      return !m_comp(l, r);
   }

   private:
   Comp m_comp;
};


template <class Comp>
class inverse
{
   public:
   BOOST_MOVE_FORCEINLINE inverse()
   {}

   BOOST_MOVE_FORCEINLINE explicit inverse(Comp comp)
      : m_comp(comp)
   {}

   template <class T1, class T2>
   BOOST_MOVE_FORCEINLINE bool operator()(const T1& l, const T2& r)
   {
      return m_comp(r, l);
   }

   private:
   Comp m_comp;
};

}  //namespace movelib {
}  //namespace boost {

#endif   //#define BOOST_MOVE_ALGO_PREDICATE_HPP
