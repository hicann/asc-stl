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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPTS_TOTALLY_ORDERED_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPTS_TOTALLY_ORDERED_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/boolean_testable.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__type_traits/common_reference.h>
#include <asc/std/__type_traits/make_const_lvalue_ref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Tp, class _Up>
concept __partially_ordered_with = requires(__make_const_lvalue_ref<_Tp> __t, __make_const_lvalue_ref<_Up> __u) {
    { __t < __u } -> __boolean_testable;
    { __t > __u } -> __boolean_testable;
    { __t <= __u } -> __boolean_testable;
    { __t >= __u } -> __boolean_testable;
    { __u < __t } -> __boolean_testable;
    { __u > __t } -> __boolean_testable;
    { __u <= __t } -> __boolean_testable;
    { __u >= __t } -> __boolean_testable;
};

#else

template <class _Tp, class _Up, class = void>
inline constexpr bool __partially_ordered_with_impl = false;

template <class _Tp, class _Up>
inline constexpr bool __partially_ordered_with_impl<_Tp, _Up,
    void_t<decltype(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() <
               ::asc::std::declval<__make_const_lvalue_ref<_Up>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() >
            ::asc::std::declval<__make_const_lvalue_ref<_Up>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() <=
            ::asc::std::declval<__make_const_lvalue_ref<_Up>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() >=
            ::asc::std::declval<__make_const_lvalue_ref<_Up>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<_Up>>() <
            ::asc::std::declval<__make_const_lvalue_ref<_Tp>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<_Up>>() >
            ::asc::std::declval<__make_const_lvalue_ref<_Tp>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<_Up>>() <=
            ::asc::std::declval<__make_const_lvalue_ref<_Tp>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<_Up>>() >=
            ::asc::std::declval<__make_const_lvalue_ref<_Tp>>())>> =
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() <
        ::asc::std::declval<__make_const_lvalue_ref<_Up>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() >
        ::asc::std::declval<__make_const_lvalue_ref<_Up>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() <=
        ::asc::std::declval<__make_const_lvalue_ref<_Up>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() >=
        ::asc::std::declval<__make_const_lvalue_ref<_Up>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<_Up>>() <
        ::asc::std::declval<__make_const_lvalue_ref<_Tp>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<_Up>>() >
        ::asc::std::declval<__make_const_lvalue_ref<_Tp>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<_Up>>() <=
        ::asc::std::declval<__make_const_lvalue_ref<_Tp>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<_Up>>() >=
        ::asc::std::declval<__make_const_lvalue_ref<_Tp>>())>;

template <class _Tp, class _Up>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __partially_ordered_with = __partially_ordered_with_impl<_Tp, _Up>;

#endif

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT totally_ordered = equality_comparable<_Tp> && __partially_ordered_with<_Tp, _Tp>;

template <class _Tp, class _Up, class = void>
inline constexpr bool __totally_ordered_with_impl = false;

template <class _Tp, class _Up>
inline constexpr bool __totally_ordered_with_impl<_Tp, _Up,
    void_t<common_reference_t<__make_const_lvalue_ref<_Tp>, __make_const_lvalue_ref<_Up>>>> =
    totally_ordered<_Tp> && totally_ordered<_Up> && equality_comparable_with<_Tp, _Up> &&
    totally_ordered<common_reference_t<__make_const_lvalue_ref<_Tp>, __make_const_lvalue_ref<_Up>>> &&
    __partially_ordered_with<_Tp, _Up>;

template <class _Tp, class _Up>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT totally_ordered_with = __totally_ordered_with_impl<_Tp, _Up>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CONCEPTS_TOTALLY_ORDERED_H
