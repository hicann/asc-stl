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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_COMPARABLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_COMPARABLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/boolean_testable.h>
#include <asc/std/__type_traits/make_const_lvalue_ref.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_DIAG_PUSH
CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_MSVC(4389)
CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_MSVC(4018)
CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_MSVC(4244)

template <class _Tp, class _Up, class = void>
inline constexpr bool __is_cpp17_equality_comparable_v = false;

template <class _Tp, class _Up>
inline constexpr bool __is_cpp17_equality_comparable_v<_Tp, _Up,
    void_t<decltype(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() ==
        ::asc::std::declval<__make_const_lvalue_ref<_Up>>())>> =
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() ==
        ::asc::std::declval<__make_const_lvalue_ref<_Up>>())>;

template <class _Tp, class _Up, bool = __is_cpp17_equality_comparable_v<_Tp, _Up>>
inline constexpr bool __is_cpp17_nothrow_equality_comparable_v = false;

template <class _Tp, class _Up>
inline constexpr bool __is_cpp17_nothrow_equality_comparable_v<_Tp, _Up, true> = noexcept(
    ::asc::std::declval<__make_const_lvalue_ref<_Tp>>() == ::asc::std::declval<__make_const_lvalue_ref<_Up>>());

template <class _Tp, class _Up, class = void>
inline constexpr bool __is_cpp17_less_than_comparable_v = false;

template <class _Tp, class _Up>
inline constexpr bool __is_cpp17_less_than_comparable_v<_Tp, _Up,
    void_t<decltype(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() <
        ::asc::std::declval<__make_const_lvalue_ref<_Up>>())>> =
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() <
        ::asc::std::declval<__make_const_lvalue_ref<_Up>>())>;

template <class _Tp, class _Up, bool = __is_cpp17_less_than_comparable_v<_Tp, _Up>>
inline constexpr bool __is_cpp17_nothrow_less_than_comparable_v = false;

template <class _Tp, class _Up>
inline constexpr bool __is_cpp17_nothrow_less_than_comparable_v<_Tp, _Up, true> =
    noexcept(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() < ::asc::std::declval<__make_const_lvalue_ref<_Up>>());

CANN_ASC_STL_DETAIL_DIAG_POP

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_COMPARABLE_H
