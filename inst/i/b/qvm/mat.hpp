#ifndef BOOST_QVM_MAT_HPP_INCLUDED
#define BOOST_QVM_MAT_HPP_INCLUDED

// Copyright 2008-2024 Emil Dotchevski and Reverge Studios, Inc.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <b/qvm/detail/mat_assign.hpp>
#include <b/qvm/assert.hpp>
#include <b/qvm/static_assert.hpp>

namespace boost { namespace qvm {

template <class T,int Rows,int Cols>
struct
mat
    {
    T a[Rows][Cols];
    template <class R
#if __cplusplus >= 201103L
        , class = typename enable_if<is_mat<R> >::type
#endif
    >
    operator R() const
        {
        R r;
        assign(r,*this);
        return r;
        }
    };

template <class M>
struct mat_traits;

template <class T,int Rows,int Cols>
struct
mat_traits< mat<T,Rows,Cols> >
    {
    typedef mat<T,Rows,Cols> this_matrix;
    typedef T scalar_type;
    static int const rows=Rows;
    static int const cols=Cols;

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element( this_matrix const & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<rows);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Col<cols);
        return x.a[Row][Col];
        }

    template <int Row,int Col>
    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element( this_matrix & x )
        {
        BOOST_QVM_STATIC_ASSERT(Row>=0);
        BOOST_QVM_STATIC_ASSERT(Row<rows);
        BOOST_QVM_STATIC_ASSERT(Col>=0);
        BOOST_QVM_STATIC_ASSERT(Col<cols);
        return x.a[Row][Col];
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type
    read_element_idx( int row, int col, this_matrix const & x )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(row<Rows);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(col<Cols);
        return x.a[row][col];
        }

    static
    BOOST_QVM_CONSTEXPR BOOST_QVM_INLINE_CRITICAL
    scalar_type &
    write_element_idx( int row, int col, this_matrix & x )
        {
        BOOST_QVM_ASSERT(row>=0);
        BOOST_QVM_ASSERT(row<Rows);
        BOOST_QVM_ASSERT(col>=0);
        BOOST_QVM_ASSERT(col<Cols);
        return x.a[row][col];
        }
    };

} }

#endif
