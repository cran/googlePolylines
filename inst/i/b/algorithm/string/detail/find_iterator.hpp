//  Boost string_algo library find_iterator.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_FIND_ITERATOR_DETAIL_HPP
#define BOOST_STRING_FIND_ITERATOR_DETAIL_HPP

#include <b/algorithm/string/config.hpp>
#include <b/range/iterator_range_core.hpp>
#include <b/iterator/iterator_facade.hpp>
#include <b/iterator/iterator_categories.hpp>
#include <b/function.hpp>

namespace boost {
    namespace algorithm { 
        namespace detail {

//  find_iterator base -----------------------------------------------//

            // Find iterator base
            template<typename IteratorT>
            class find_iterator_base
            {
            protected:
                // typedefs
                typedef IteratorT input_iterator_type;
                typedef iterator_range<IteratorT> match_type;
                typedef function2<
                    match_type, 
                    input_iterator_type, 
                    input_iterator_type> finder_type;
                
            protected:
            // Protected construction/destruction

                // Default constructor
                BOOST_DEFAULTED_FUNCTION(find_iterator_base(), {})

                // Copy construction
                BOOST_DEFAULTED_FUNCTION(find_iterator_base( const find_iterator_base& Other ), :
                    m_Finder(Other.m_Finder) {}
                )

                // Assignment
                BOOST_DEFAULTED_FUNCTION(find_iterator_base& operator=( const find_iterator_base& Other ), {
                    m_Finder = Other.m_Finder;
                    return *this;
                })
                
                // Constructor
                template<typename FinderT>
                find_iterator_base( FinderT Finder, int ) :
                    m_Finder(Finder) {}

                // Destructor
                BOOST_DEFAULTED_FUNCTION(~find_iterator_base(), {})

                // Find operation
                match_type do_find( 
                    input_iterator_type Begin,
                    input_iterator_type End ) const
                {
                    if (!m_Finder.empty())
                    {
                        return m_Finder(Begin,End);
                    }
                    else
                    {
                        return match_type(End,End);
                    }
                }

                // Check
                bool is_null() const
                {
                    return m_Finder.empty();
                }

            private:
                // Finder
                finder_type m_Finder;
            };

       } // namespace detail
    } // namespace algorithm
} // namespace boost


#endif  // BOOST_STRING_FIND_ITERATOR_DETAIL_HPP
