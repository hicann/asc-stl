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

#ifndef CANN_ASC_STL_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_H
#define CANN_ASC_STL_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__fwd/complex.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__fwd/array.h>
#include <asc/std/__fwd/complex.h>
#include <asc/std/__fwd/pair.h>
#include <asc/std/__fwd/tuple.h>
#include <asc/std/__type_traits/aggregate_members_all_of.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_aggregate.h>
#include <asc/std/__type_traits/is_trivially_copyable.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

template <typename _Tp, typename = void>
inline constexpr bool __is_aggregate_trivially_copyable_v = false;

template <typename _Tp>
inline constexpr bool __is_trivially_copyable_v =
    ::asc::std::is_trivially_copyable_v<_Tp> || __is_aggregate_trivially_copyable_v<_Tp>;

#if CANN_ASC_STL_DETAIL_HAS_HALF()

template <>
inline constexpr bool __is_trivially_copyable_v<::half> = true;

#endif  // CANN_ASC_STL_DETAIL_HAS_HALF()

#if CANN_ASC_STL_DETAIL_HAS_HALF2()

template <>
inline constexpr bool __is_trivially_copyable_v<::half2> = true;

#endif  // CANN_ASC_STL_DETAIL_HAS_HALF2()

#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16()

template <>
inline constexpr bool __is_trivially_copyable_v<::bfloat16_t> = true;

#endif  // CANN_ASC_STL_DETAIL_HAS_BFLOAT16()

#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2()

template <>
inline constexpr bool __is_trivially_copyable_v<::bfloat16x2_t> = true;

#endif  // CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2()

template <typename _Tp>
inline constexpr bool __is_trivially_copyable_v<_Tp[]> = __is_trivially_copyable_v<_Tp>;

template <typename _Tp, ::asc::std::size_t _Size>
inline constexpr bool __is_trivially_copyable_v<_Tp[_Size]> = __is_trivially_copyable_v<_Tp>;

template <typename _Tp, ::asc::std::size_t _Size>
inline constexpr bool __is_trivially_copyable_v<::asc::std::array<_Tp, _Size>> = __is_trivially_copyable_v<_Tp>;

template <typename _T1, typename _T2>
inline constexpr bool __is_trivially_copyable_v<::asc::std::pair<_T1, _T2>> =
    __is_trivially_copyable_v<_T1> && __is_trivially_copyable_v<_T2>;

template <typename... _Ts>
inline constexpr bool __is_trivially_copyable_v<::asc::std::tuple<_Ts...>> = (__is_trivially_copyable_v<_Ts> && ...);

template <typename _Tp>
inline constexpr bool __is_trivially_copyable_v<complex<_Tp>> = true;

template <typename _Tp>
inline constexpr bool __is_trivially_copyable_v<::asc::std::complex<_Tp>> = true;

// If the compiler trait rejects a composite aggregate, recursively check its
// members against the ASC extension trait.
template <typename _Tp>
using __is_trivially_copyable_callable = ::asc::std::bool_constant<__is_trivially_copyable_v<_Tp>>;

template <typename _Tp>
inline constexpr bool __is_aggregate_trivially_copyable_v<_Tp,
    ::asc::std::enable_if_t<::asc::std::is_aggregate_v<_Tp> && !::asc::std::is_trivially_copyable_v<_Tp>>> =
    ::asc::std::__aggregate_all_of_v<__is_trivially_copyable_callable, _Tp>;

// Public traits

template <typename _Tp>
inline constexpr bool is_trivially_copyable_v = __is_trivially_copyable_v<_Tp>;

template <typename _Tp>
inline constexpr bool is_trivially_copyable_v<const _Tp> = is_trivially_copyable_v<_Tp>;

// Defined as an alias so users cannot specialize it; specialize the variable
// template above when extending the trait for a user-defined type.
template <typename _Tp>
using is_trivially_copyable = ::asc::std::bool_constant<is_trivially_copyable_v<_Tp>>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_TYPE_TRAITS_IS_TRIVIALLY_COPYABLE_H
