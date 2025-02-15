/* 
   Copyright (c) Marshall Clow 2008-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  copy_if.hpp
/// \brief Copy a subset of a sequence to a new sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_COPY_IF_HPP
#define BOOST_ALGORITHM_COPY_IF_HPP

#include <utility>    // for std::pair, std::make_pair

#include <b/config.hpp>
#include <b/range/begin.hpp>
#include <b/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn copy_if ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
/// \brief Copies all the elements from the input range that satisfy the
/// predicate to the output range.
/// \return The updated output iterator
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
/// \note           This function is part of the C++2011 standard library.
template<typename InputIterator, typename OutputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR OutputIterator copy_if ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
{
    for ( ; first != last; ++first )
        if (p(*first))
            *result++ = *first;
    return result;
}

/// \fn copy_if ( const Range &r, OutputIterator result, Predicate p )
/// \brief Copies all the elements from the input range that satisfy the
/// predicate to the output range.
/// \return The updated output iterator
/// 
/// \param r        The input range
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
///
template<typename Range, typename OutputIterator, typename Predicate>
BOOST_CXX14_CONSTEXPR OutputIterator copy_if ( const Range &r, OutputIterator result, Predicate p )
{
    return boost::algorithm::copy_if (boost::begin (r), boost::end(r), result, p);
}


/// \fn copy_while ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
/// \brief Copies all the elements at the start of the input range that
///     satisfy the predicate to the output range.
/// \return The updated input and output iterators
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
///
template<typename InputIterator, typename OutputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR std::pair<InputIterator, OutputIterator>
copy_while ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
{
    for ( ; first != last && p(*first); ++first )
        *result++ = *first;
    return std::make_pair(first, result);
}

/// \fn copy_while ( const Range &r, OutputIterator result, Predicate p )
/// \brief Copies all the elements at the start of the input range that
///     satisfy the predicate to the output range.
/// \return The updated input and output iterators
/// 
/// \param r        The input range
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
///
template<typename Range, typename OutputIterator, typename Predicate>
BOOST_CXX14_CONSTEXPR std::pair<typename boost::range_iterator<const Range>::type, OutputIterator> 
copy_while ( const Range &r, OutputIterator result, Predicate p )
{
    return boost::algorithm::copy_while (boost::begin (r), boost::end(r), result, p);
}


/// \fn copy_until ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
/// \brief Copies all the elements at the start of the input range that do not
///     satisfy the predicate to the output range.
/// \return The updated output iterator
/// 
/// \param first    The start of the input sequence
/// \param last     One past the end of the input sequence
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
///
template<typename InputIterator, typename OutputIterator, typename Predicate> 
BOOST_CXX14_CONSTEXPR std::pair<InputIterator, OutputIterator>
copy_until ( InputIterator first, InputIterator last, OutputIterator result, Predicate p )
{
    for ( ; first != last && !p(*first); ++first )
        *result++ = *first;
    return std::make_pair(first, result);
}

/// \fn copy_until ( const Range &r, OutputIterator result, Predicate p )
/// \brief Copies all the elements at the start of the input range that do not
///     satisfy the predicate to the output range.
/// \return The updated output iterator
/// 
/// \param r        The input range
/// \param result   An output iterator to write the results into
/// \param p        A predicate for testing the elements of the range
///
template<typename Range, typename OutputIterator, typename Predicate>
BOOST_CXX14_CONSTEXPR std::pair<typename boost::range_iterator<const Range>::type, OutputIterator> 
copy_until ( const Range &r, OutputIterator result, Predicate p )
{
    return boost::algorithm::copy_until (boost::begin (r), boost::end(r), result, p);
}

/// \fn copy_if_while ( InputIterator first, InputIterator last, OutputIterator result, CopyPredicate copy_pred, TerminatePred term_pred )
/// \brief Copies all the elements from the input range that satisfy the
/// copy predicate to the output range while the termination predicate is
/// satisfied.
/// \return The updated output iterator
///
/// \param first     The start of the input sequence
/// \param last      One past the end of the input sequence
/// \param result    An output iterator to write the results into
/// \param copy_pred A predicate for testing whether to the current element
/// \param term_pred A predicate for testing whether to end the copy operation
template<typename InputIterator, typename OutputIterator, typename CopyPredicate, typename TerminatePred>
BOOST_CXX14_CONSTEXPR std::pair<InputIterator, OutputIterator>
copy_if_while ( InputIterator first, InputIterator last, OutputIterator result, CopyPredicate copy_pred, TerminatePred term_pred)
{
    for ( ; first != last && term_pred(*first); ++first ) {
        if (copy_pred(*first)) {
            *result++ = *first;
        }
    }
    return std::make_pair(first, result);
}

/// \fn copy_if_while ( const Range& r, OutputIterator result, CopyPredicate copy_pred, TerminatePred term_pred )
/// \brief Copies all the elements from the input range that satisfy the
/// copy predicate to the output range while the termination predicate is
/// satisfied.
/// \return The updated output iterator
///
/// \param r         The input range
/// \param result    An output iterator to write the results into
/// \param copy_pred A predicate for testing whether to the current element
/// \param term_pred A predicate for testing whether to end the copy operation
template<typename Range, typename OutputIterator, typename CopyPredicate, typename TerminatePred>
BOOST_CXX14_CONSTEXPR std::pair<typename boost::range_iterator<const Range>::type, OutputIterator>
copy_if_while ( const Range& r, OutputIterator result, CopyPredicate copy_pred, TerminatePred term_pred)
{
    return boost::algorithm::copy_if_while(boost::begin(r), boost::end(r), result, copy_pred, term_pred);
}

/// \fn copy_if_until ( InputIterator first, InputIterator last, OutputIterator result, CopyPredicate copy_pred, TerminatePred term_pred )
/// \brief Copies all the elements from the input range that satisfy the
/// copy predicate to the output range until the termination predicate is
/// satisfied.
/// \return The updated output iterator
///
/// \param first     The start of the input sequence
/// \param last      One past the end of the input sequence
/// \param result    An output iterator to write the results into
/// \param copy_pred A predicate for testing whether to the current element
/// \param term_pred A predicate for testing whether to end the copy operation
template<typename InputIterator, typename OutputIterator, typename CopyPredicate, typename TerminatePred>
BOOST_CXX14_CONSTEXPR std::pair<InputIterator, OutputIterator>
copy_if_until ( InputIterator first, InputIterator last, OutputIterator result, CopyPredicate copy_pred, TerminatePred term_pred)
{
    for ( ; first != last && !term_pred(*first); ++first ) {
        if (copy_pred(*first)) {
            *result++ = *first;
        }
    }
    return std::make_pair(first, result);
}

/// \fn copy_if_until ( const Range& r, OutputIterator result, CopyPredicate copy_pred, TerminatePred term_pred )
/// \brief Copies all the elements from the input range that satisfy the
/// copy predicate to the output range until the termination predicate is
/// satisfied.
/// \return The updated output iterator
///
/// \param r         The input range
/// \param result    An output iterator to write the results into
/// \param copy_pred A predicate for testing whether to the current element
/// \param term_pred A predicate for testing whether to end the copy operation
template<typename Range, typename OutputIterator, typename CopyPredicate, typename TerminatePred>
BOOST_CXX14_CONSTEXPR std::pair<typename boost::range_iterator<const Range>::type, OutputIterator>
copy_if_until ( const Range& r, OutputIterator result, CopyPredicate copy_pred, TerminatePred term_pred)
{
    return boost::algorithm::copy_if_until(boost::begin(r), boost::end(r), result, copy_pred, term_pred);
}

}} // namespace boost and algorithm

#endif  // BOOST_ALGORITHM_COPY_IF_HPP
