/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CANN_ASC_STL_STD_DETAIL_MDSPAN_CONCEPTS_H
#define CANN_ASC_STL_STD_DETAIL_MDSPAN_CONCEPTS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__fwd/mdspan.h>
#include <asc/std/__tuple_dir/tuple_element.h>
#include <asc/std/__tuple_dir/tuple_like.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/integral_constant_like.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__type_traits/is_unsigned.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

namespace __mdspan_detail {
// [mdspan.layout.stride.expo]/3

// [mdspan.layout.general]/2
template <class _Layout, class _Mapping>
inline constexpr bool __is_mapping_of =
    is_same_v<typename _Layout::template mapping<typename _Mapping::extents_type>, _Mapping>;

// [mdspan.layout.reqmts]/1
template <class _Mapping>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __layout_mapping_req_type =
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Mapping))(requires(copyable<_Mapping>),
        requires(equality_comparable<_Mapping>), requires(is_nothrow_move_constructible_v<_Mapping>),
        requires(is_move_assignable_v<_Mapping>), requires(is_nothrow_swappable_v<_Mapping>));

// [mdspan.layout.reqmts]/2-4
template <class _Mapping>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __layout_mapping_req_types = CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Mapping))(
    requires(__is_asc_std_extents_v<typename _Mapping::extents_type>),
    requires(same_as<typename _Mapping::index_type, typename _Mapping::extents_type::index_type>),
    requires(same_as<typename _Mapping::rank_type, typename _Mapping::extents_type::rank_type>),
    requires(__is_mapping_of<typename _Mapping::layout_type, _Mapping>));

template <class _Mapping>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __layout_mapping_req_members = CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR(
    (_Mapping), const _Mapping& __map)(_Same_as(const typename _Mapping::extents_type&) __map.extents(),
    _Same_as(typename _Mapping::index_type) __map.required_span_size(),
    _Same_as(bool) __map.is_unique(),                                          // NOLINT(readability/casting)
    _Same_as(bool) __map.is_exhaustive(), _Same_as(bool) __map.is_strided());  // NOLINT(readability/casting)

template <class _Mapping>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __layout_mapping_req =
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Mapping))(requires(__layout_mapping_req_type<_Mapping>),
        requires(__layout_mapping_req_types<_Mapping>), requires(__layout_mapping_req_members<_Mapping>));

// [mdspan.layout.stride.expo]/4
// NOTE: integral_constant<bool, _Mapping::is_always_strided()>::value only checks that this is a constant expression
template <class _Mapping>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __layout_mapping_alike = CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Mapping))(
    requires(__is_mapping_of<typename _Mapping::layout_type, _Mapping>),
    requires(__is_asc_std_extents_v<typename _Mapping::extents_type>),
    requires(same_as<bool, decltype(_Mapping::is_always_strided())>),
    requires(same_as<bool, decltype(_Mapping::is_always_exhaustive())>),
    requires(same_as<bool, decltype(_Mapping::is_always_unique())>),
    (integral_constant<bool, _Mapping::is_always_strided()>::value),
    (integral_constant<bool, _Mapping::is_always_exhaustive()>::value),
    (integral_constant<bool, _Mapping::is_always_unique()>::value));

template <class _IndexType, class... _Indices>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __all_convertible_to_index_type =
    (is_convertible_v<_Indices, _IndexType> && ... && true) &&
    (is_nothrow_constructible_v<_IndexType, _Indices> && ... && true);

template <class _Extent, size_t _Size>
static constexpr bool __matches_dynamic_rank = (_Size == _Extent::rank_dynamic());

template <class _Extent, size_t _Size>
static constexpr bool __matches_static_rank = (_Size == _Extent::rank()) && (_Size != _Extent::rank_dynamic());
}  // namespace __mdspan_detail

// Note: __pair_like_v is SFINAE-safe (it yields false when tuple_size is unavailable
// or the type is incomplete; see __tuple_dir/tuple_like.h), so the reference form
// matches the intended semantics directly.
template <class _Tp, class _IndexType>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __index_pair_like = CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Tp, _IndexType))(
    requires(__pair_like_v<_Tp>), requires(convertible_to<tuple_element_t<0, _Tp>, _IndexType>),
    requires(convertible_to<tuple_element_t<1, _Tp>, _IndexType>));

// [mdspan.submdspan.strided.slice]/3

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __index_like = is_signed_v<_Tp> || is_unsigned_v<_Tp> || __integral_constant_like<_Tp>;

template <class _AccessorPolicy>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __has_detect_invalidity =
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_AccessorPolicy), _AccessorPolicy __ap)(__ap.__detectably_invalid(
        ::asc::std::declval<typename _AccessorPolicy::data_handle_type>(), ::asc::std::declval<::asc::std::size_t>()));

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_MDSPAN_CONCEPTS_H
