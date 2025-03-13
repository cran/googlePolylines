#ifndef DATE_TIME_TIME_HPP___
#define DATE_TIME_TIME_HPP___

/* Copyright (c) 2002,2003,2005,2020 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */


/*! @file time.hpp
  This file contains the interface for the time associated classes.
*/
#include <string>
#include <b/operators.hpp>
#include <b/date_time/time_defs.hpp>
#include <b/date_time/special_defs.hpp>

namespace boost {
namespace date_time {

  //! Representation of a precise moment in time, including the date.
  /*! 
    This class is a skeleton for the interface of a temporal type
    with a resolution that is higher than a day.  It is intended that 
    this class be the base class and that the actual time 
    class be derived using the BN pattern.  In this way, the derived 
    class can make decisions such as 'should there be a default constructor' 
    and what should it set its value to, should there be optional constructors
    say allowing only an time_durations that generate a time from a clock,etc.
    So, in fact multiple time types can be created for a time_system with
    different construction policies, and all of them can perform basic
    operations by only writing a copy constructor.  Finally, compiler 
    errors are also shorter. 
    
    The real behavior of the time class is provided by the time_system
    template parameter.  This class must provide all the logic
    for addition, subtraction, as well as define all the interface
    types.
    
  */

  template <class T, class time_system>
  class base_time : private
      boost::less_than_comparable<T
    , boost::equality_comparable<T
      > >
  {
  public:
    // A tag for type categorization. Can be used to detect Boost.DateTime time points in generic code.
    typedef void _is_boost_date_time_time_point;
    typedef T time_type;
    typedef typename time_system::time_rep_type time_rep_type;
    typedef typename time_system::date_type date_type;
    typedef typename time_system::date_duration_type date_duration_type;
    typedef typename time_system::time_duration_type time_duration_type;
    //typedef typename time_system::hms_type hms_type;
    
    BOOST_CXX14_CONSTEXPR
    base_time(const date_type& day, 
              const time_duration_type& td, 
              dst_flags dst=not_dst) :
      time_(time_system::get_time_rep(day, td, dst))
    {}
    BOOST_CXX14_CONSTEXPR
    base_time(special_values sv) :
      time_(time_system::get_time_rep(sv))
    {}
    BOOST_CXX14_CONSTEXPR
    base_time(const time_rep_type& rhs) :
      time_(rhs)
    {}
    BOOST_CXX14_CONSTEXPR
    date_type date() const
    {
      return time_system::get_date(time_);
    }
    BOOST_CXX14_CONSTEXPR
    time_duration_type time_of_day() const
    {
      return time_system::get_time_of_day(time_);
    }
    /*! Optional bool parameter will return time zone as an offset 
     * (ie "+07:00"). Empty string is returned for classes that do 
     * not use a time_zone */
    std::string zone_name(bool /*as_offset*/=false) const
    {
      return time_system::zone_name(time_);
    }
    /*! Optional bool parameter will return time zone as an offset 
     * (ie "+07:00"). Empty string is returned for classes that do 
     * not use a time_zone */
    std::string zone_abbrev(bool /*as_offset*/=false) const
    {
      return time_system::zone_name(time_);
    }
    //! An empty string is returned for classes that do not use a time_zone
    std::string zone_as_posix_string() const
    {
      return std::string();
    }

    //! check to see if date is not a value
    BOOST_CXX14_CONSTEXPR
    bool is_not_a_date_time()  const
    {
      return time_.is_not_a_date_time();
    }
    //! check to see if date is one of the infinity values
    BOOST_CXX14_CONSTEXPR
    bool is_infinity()  const
    {
      return (is_pos_infinity() || is_neg_infinity()); 
    }
    //! check to see if date is greater than all possible dates
    BOOST_CXX14_CONSTEXPR
    bool is_pos_infinity()  const
    {
      return time_.is_pos_infinity();
    }
    //! check to see if date is greater than all possible dates
    BOOST_CXX14_CONSTEXPR
    bool is_neg_infinity()  const
    {
      return time_.is_neg_infinity();
    }
    //! check to see if time is a special value
    BOOST_CXX14_CONSTEXPR
    bool is_special() const
    {
      return(is_not_a_date_time() || is_infinity());
    }
    //!Equality operator -- others generated by boost::equality_comparable
    BOOST_CXX14_CONSTEXPR
    bool operator==(const time_type& rhs) const
    {
      return time_system::is_equal(time_,rhs.time_);
    }
    //!Equality operator -- others generated by boost::less_than_comparable
    BOOST_CXX14_CONSTEXPR
    bool operator<(const time_type& rhs) const
    {
      return time_system::is_less(time_,rhs.time_);
    }
    //! difference between two times
    BOOST_CXX14_CONSTEXPR
    time_duration_type operator-(const time_type& rhs) const
    {
      return time_system::subtract_times(time_, rhs.time_);
    }
    //! add date durations
    BOOST_CXX14_CONSTEXPR
    time_type operator+(const date_duration_type& dd) const
    {
      return time_system::add_days(time_, dd);
    }
    BOOST_CXX14_CONSTEXPR
    time_type operator+=(const date_duration_type& dd)
    {
      time_ = (time_system::get_time_rep(date() + dd, time_of_day()));
      return time_type(time_);
    }
    //! subtract date durations
    BOOST_CXX14_CONSTEXPR
    time_type operator-(const date_duration_type& dd) const
    {
      return time_system::subtract_days(time_, dd);
    }
    BOOST_CXX14_CONSTEXPR
    time_type operator-=(const date_duration_type& dd)
    {
      time_ = (time_system::get_time_rep(date() - dd, time_of_day()));
      return time_type(time_);
    }
    //! add time durations
    BOOST_CXX14_CONSTEXPR
    time_type operator+(const time_duration_type& td) const
    {
      return time_type(time_system::add_time_duration(time_, td));
    }
    BOOST_CXX14_CONSTEXPR
    time_type operator+=(const time_duration_type& td)
    {
      time_ = time_system::add_time_duration(time_,td);
      return time_type(time_);
    }
    //! subtract time durations
    BOOST_CXX14_CONSTEXPR
    time_type operator-(const time_duration_type& rhs) const
    {
      return time_system::subtract_time_duration(time_, rhs);
    }
    BOOST_CXX14_CONSTEXPR
    time_type operator-=(const time_duration_type& td) 
    {
      time_ = time_system::subtract_time_duration(time_, td);
      return time_type(time_);
    }
    
  protected:
    time_rep_type time_;
  };





} } //namespace date_time::boost


#endif

