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

#ifndef CANN_ASC_STL_DETAIL_TYPE_TRAITS_IS_BITWISE_COMPARABLE_H
#define CANN_ASC_STL_DETAIL_TYPE_TRAITS_IS_BITWISE_COMPARABLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__fwd/complex.h>
#include <asc/__type_traits/is_vector_type.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__fwd/array.h>
#include <asc/std/__fwd/complex.h>
#include <asc/std/__tuple_dir/tuple.h>  // required for sizeof
#include <asc/std/__type_traits/aggregate_members_all_of.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/has_unique_object_representation.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_aggregate.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__utility/pair.h>  // required for sizeof

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

template <typename _Tp, typename = void>
inline constexpr bool __is_aggregate_bitwise_comparable_v = true;

template <typename _Tp>
inline constexpr bool __is_bitwise_comparable_v =
    ::asc::std::has_unique_object_representations_v<_Tp>  // no padding, no float/double
#if 0   // extended-fp branches of the reference toolkit do not apply here
  && !::asc::std::__is_extended_floating_point_v<_Tp>   // scalar extended floating-point types
  && !is_extended_fp_vector_type_v<_Tp>   // vector extended floating-point types
#endif  // CANN_ASC_STL_DETAIL_TYPE_TRAITS_IS_BITWISE_COMPARABLE_H
    && __is_aggregate_bitwise_comparable_v<_Tp>;

template <typename _Tp>
inline constexpr bool __is_bitwise_comparable_v<_Tp[]> = __is_bitwise_comparable_v<_Tp>;

template <typename _Tp, ::asc::std::size_t _Size>
inline constexpr bool __is_bitwise_comparable_v<_Tp[_Size]> = __is_bitwise_comparable_v<_Tp>;

template <typename _Tp, ::asc::std::size_t _Size>
inline constexpr bool __is_bitwise_comparable_v<::asc::std::array<_Tp, _Size>> = __is_bitwise_comparable_v<_Tp>;

template <typename _T1, typename _T2>
inline constexpr bool __is_bitwise_comparable_v<::asc::std::pair<_T1, _T2>> =
    (sizeof(::asc::std::pair<_T1, _T2>) == sizeof(_T1) + sizeof(_T2)) && __is_bitwise_comparable_v<_T1> &&
    __is_bitwise_comparable_v<_T2>;

template <typename... _Ts>
inline constexpr bool __is_bitwise_comparable_v<::asc::std::tuple<_Ts...>> =
    (sizeof...(_Ts) == 0 || sizeof(::asc::std::tuple<_Ts...>) == (sizeof(_Ts) + ... + 0)) &&
    (__is_bitwise_comparable_v<_Ts> && ...);

template <typename _Tp>
inline constexpr bool __is_bitwise_comparable_v<::asc::std::complex<_Tp>> = false;

template <typename _Tp>
inline constexpr bool __is_bitwise_comparable_v<complex<_Tp>> = false;

// if all the previous conditions fail, check if the type is an aggregate and all its members are bitwise comparable
template <typename _Tp>
using __is_bitwise_comparable_callable = ::asc::std::bool_constant<__is_bitwise_comparable_v<_Tp>>;

// __aggregate_all_of_v returns true if the type is not an aggregate (or empty)
template <typename _Tp>
inline constexpr bool
    __is_aggregate_bitwise_comparable_v<_Tp, ::asc::std::enable_if_t<::asc::std::is_aggregate_v<_Tp>>> =
        ::asc::std::__aggregate_all_of_v<__is_bitwise_comparable_callable, _Tp>;

//----------------------------------------------------------------------------------------------------------------------
// public variable template and alias

// Users are allowed to specialize this variable template for their own types
template <typename _Tp>
inline constexpr bool is_bitwise_comparable_v = __is_bitwise_comparable_v<_Tp>;

template <typename _Tp>
inline constexpr bool is_bitwise_comparable_v<const _Tp> = is_bitwise_comparable_v<_Tp>;

template <typename _Tp>
inline constexpr bool is_bitwise_comparable_v<volatile _Tp> = is_bitwise_comparable_v<_Tp>;

template <typename _Tp>
inline constexpr bool is_bitwise_comparable_v<const volatile _Tp> = is_bitwise_comparable_v<_Tp>;

// defined as alias so users cannot specialize it (they should specialize the variable template instead)
template <typename _Tp>
using is_bitwise_comparable = ::asc::std::bool_constant<is_bitwise_comparable_v<_Tp>>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_TYPE_TRAITS_IS_BITWISE_COMPARABLE_H
