// Boost.Geometry

// Copyright (c) 2024 Adam Wulkiewicz, Lodz, Poland.

// Copyright (c) 2020-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_UTIL_TYPE_TRAITS_HPP
#define BOOST_GEOMETRY_UTIL_TYPE_TRAITS_HPP


#include <b/geometry/core/tag.hpp>
#include <b/geometry/core/tags.hpp>
#include <b/geometry/util/type_traits_std.hpp>


namespace boost { namespace geometry
{


namespace util
{


template <typename T>
struct is_geometry
    : bool_constant<! std::is_void<tag_t<T>>::value>
{};

template <typename T>
struct is_not_geometry
    : std::is_void<tag_t<T>>
{};

#ifndef BOOST_NO_CXX17_INLINE_VARIABLES
template <typename T>
inline constexpr bool is_geometry_v = is_geometry<T>::value;
template <typename T>
inline constexpr bool is_not_geometry_v = is_not_geometry<T>::value;
#endif

template <typename T>
struct is_point
    : std::is_same<point_tag, tag_t<T>>
{};

template <typename T>
struct is_multi_point
    : std::is_same<multi_point_tag, tag_t<T>>
{};

template <typename T>
struct is_pointlike
    : std::is_base_of<pointlike_tag, tag_t<T>>
{};

#ifndef BOOST_NO_CXX17_INLINE_VARIABLES
template <typename T>
inline constexpr bool is_point_v = is_point<T>::value;
template <typename T>
inline constexpr bool is_multi_point_v = is_multi_point<T>::value;
template <typename T>
inline constexpr bool is_pointlike_v = is_pointlike<T>::value;
#endif


template <typename T>
struct is_segment
    : std::is_same<segment_tag, tag_t<T>>
{};

template <typename T>
struct is_linestring
    : std::is_same<linestring_tag, tag_t<T>>
{};

template <typename T>
struct is_multi_linestring
    : std::is_same<multi_linestring_tag, tag_t<T>>
{};

template <typename T>
struct is_polylinear
    : std::is_base_of<polylinear_tag, tag_t<T>>
{};

template <typename T>
struct is_linear
    : std::is_base_of<linear_tag, tag_t<T>>
{};

#ifndef BOOST_NO_CXX17_INLINE_VARIABLES
template <typename T>
inline constexpr bool is_segment_v = is_segment<T>::value;
template <typename T>
inline constexpr bool is_linestring_v = is_linestring<T>::value;
template <typename T>
inline constexpr bool is_multi_linestring_v = is_multi_linestring<T>::value;
template <typename T>
inline constexpr bool is_polylinear_v = is_polylinear<T>::value;
template <typename T>
inline constexpr bool is_linear_v = is_linear<T>::value;
#endif


template <typename T>
struct is_box
    : std::is_same<box_tag, tag_t<T>>
{};

template <typename T>
struct is_ring
    : std::is_same<ring_tag, tag_t<T>>
{};

template <typename T>
struct is_polygon
    : std::is_same<polygon_tag, tag_t<T>>
{};

template <typename T>
struct is_multi_polygon
    : std::is_same<multi_polygon_tag, tag_t<T>>
{};

template <typename T>
struct is_polygonal
    : std::is_base_of<polygonal_tag, tag_t<T>>
{};

template <typename T>
struct is_areal
    : std::is_base_of<areal_tag, tag_t<T>>
{};

#ifndef BOOST_NO_CXX17_INLINE_VARIABLES
template <typename T>
inline constexpr bool is_box_v = is_box<T>::value;
template <typename T>
inline constexpr bool is_ring_v = is_ring<T>::value;
template <typename T>
inline constexpr bool is_polygon_v = is_polygon<T>::value;
template <typename T>
inline constexpr bool is_multi_polygon_v = is_multi_polygon<T>::value;
template <typename T>
inline constexpr bool is_polygonal_v = is_polygonal<T>::value;
template <typename T>
inline constexpr bool is_areal_v = is_areal<T>::value;
#endif


template <typename T>
struct is_segmental
    : bool_constant<is_linear<T>::value || is_polygonal<T>::value>
{};

template <typename T>
struct is_polysegmental
    : bool_constant<is_polylinear<T>::value || is_polygonal<T>::value>
{};

template <typename T>
struct is_multi
    : std::is_base_of<multi_tag, tag_t<T>>
{};

template <typename T>
struct is_multi_element
    : bool_constant<is_point<T>::value || is_linestring<T>::value || is_polygon<T>::value>
{};

template <typename T>
struct is_single
    : std::is_base_of<single_tag, tag_t<T>>
{};

template <typename T>
struct is_geometry_collection
    : std::is_same<geometry_collection_tag, tag_t<T>>
{};

template <typename T>
struct is_dynamic_geometry
    : std::is_same<dynamic_geometry_tag, tag_t<T>>
{};

#ifndef BOOST_NO_CXX17_INLINE_VARIABLES
template <typename T>
inline constexpr bool is_segmental_v = is_segmental<T>::value;
template <typename T>
inline constexpr bool is_polysegmental_v = is_polysegmental<T>::value;
template <typename T>
inline constexpr bool is_multi_v = is_multi<T>::value;
template <typename T>
inline constexpr bool is_multi_element_v = is_multi_element<T>::value;
template <typename T>
inline constexpr bool is_single_v = is_single<T>::value;
template <typename T>
inline constexpr bool is_geometry_collection_v = is_geometry_collection<T>::value;
template <typename T>
inline constexpr bool is_dynamic_geometry_v = is_dynamic_geometry<T>::value;
#endif


template <typename Geometry, typename T = void>
struct enable_if_point
    : std::enable_if<is_point<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_point_t = typename enable_if_point<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_multi_point
    : std::enable_if<is_multi_point<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_multi_point_t = typename enable_if_multi_point<Geometry, T>::type;

template <typename Geometry, typename T = void>
struct enable_if_pointlike
    : std::enable_if<is_pointlike<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_pointlike_t = typename enable_if_pointlike<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_segment
    : std::enable_if<is_segment<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_segment_t = typename enable_if_segment<Geometry, T>::type;

template <typename Geometry, typename T = void>
struct enable_if_linestring
    : std::enable_if<is_linestring<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_linestring_t = typename enable_if_linestring<Geometry, T>::type;

template <typename Geometry, typename T = void>
struct enable_if_multi_linestring
    : std::enable_if<is_multi_linestring<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_multi_linestring_t = typename enable_if_multi_linestring<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_polylinear
    : std::enable_if<is_polylinear<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_polylinear_t = typename enable_if_polylinear<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_linear
    : std::enable_if<is_linear<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_linear_t = typename enable_if_linear<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_box
    : std::enable_if<is_box<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_box_t = typename enable_if_box<Geometry, T>::type;

template <typename Geometry, typename T = void>
struct enable_if_ring
    : std::enable_if<is_ring<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_ring_t = typename enable_if_ring<Geometry, T>::type;

template <typename Geometry, typename T = void>
struct enable_if_polygon
    : std::enable_if<is_polygon<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_polygon_t = typename enable_if_polygon<Geometry, T>::type;

template <typename Geometry, typename T = void>
struct enable_if_multi_polygon
    : std::enable_if<is_multi_polygon<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_multi_polygon_t = typename enable_if_multi_polygon<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_polygonal
    : std::enable_if<is_polygonal<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_polygonal_t = typename enable_if_polygonal<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_areal
    : std::enable_if<is_areal<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_areal_t = typename enable_if_areal<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_polysegmental
    : std::enable_if<is_polysegmental<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_polysegmental_t = typename enable_if_polysegmental<Geometry, T>::type;


template <typename Geometry, typename T = void>
struct enable_if_dynamic_geometry
    : std::enable_if<is_dynamic_geometry<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_dynamic_geometry_t = typename enable_if_dynamic_geometry<Geometry, T>::type;

template <typename Geometry, typename T = void>
struct enable_if_geometry_collection
    : std::enable_if<is_geometry_collection<Geometry>::value, T>
{};

template <typename Geometry, typename T = void>
using enable_if_geometry_collection_t = typename enable_if_geometry_collection<Geometry, T>::type;


} // namespace util


// Deprecated utilities, defined for backward compatibility but might be
// removed in the future.


/*!
    \brief Meta-function defining "true" for areal types (box, (multi)polygon, ring),
    \note Used for tag dispatching and meta-function finetuning
    \note Also a "ring" has areal properties within Boost.Geometry
    \ingroup core
*/
template <typename T>
using is_areal [[deprecated("Use util::is_areal<> instead.")]] = util::is_areal<T>;


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_DETAIL_HPP
