/*
 * Copyright 2026 湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_ASC_STD___CONCEPTS_TOTALLY_ORDERED_H
#define CANN_ASC_STL_ASC_STD___CONCEPTS_TOTALLY_ORDERED_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/boolean_testable.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/equality_comparable.h>
#include <asc/std/__type_traits/common_reference.h>
#include <asc/std/__type_traits/make_const_lvalue_ref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class T, class U>
concept __partially_ordered_with = requires(__make_const_lvalue_ref<T> t, __make_const_lvalue_ref<U> u) {
    { t < u } -> __boolean_testable;
    { t > u } -> __boolean_testable;
    { t <= u } -> __boolean_testable;
    { t >= u } -> __boolean_testable;
    { u < t } -> __boolean_testable;
    { u > t } -> __boolean_testable;
    { u <= t } -> __boolean_testable;
    { u >= t } -> __boolean_testable;
};

template <class T>
concept totally_ordered = equality_comparable<T> && __partially_ordered_with<T, T>;

template <class T, class U>
concept totally_ordered_with = totally_ordered<T> && totally_ordered<U> &&
    common_reference_with<__make_const_lvalue_ref<T>, __make_const_lvalue_ref<U>> &&
    totally_ordered<common_reference_t<__make_const_lvalue_ref<T>, __make_const_lvalue_ref<U>>> &&
    equality_comparable_with<T, U> && __partially_ordered_with<T, U>;
#else
template <class T, class U, class = void>
inline constexpr bool __partially_ordered_with_impl = false;

template <class T, class U>
inline constexpr bool __partially_ordered_with_impl<T, U,
    void_t<decltype(::asc::std::declval<__make_const_lvalue_ref<T>>() <
               ::asc::std::declval<__make_const_lvalue_ref<U>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<T>>() > ::asc::std::declval<__make_const_lvalue_ref<U>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<T>>() <=
            ::asc::std::declval<__make_const_lvalue_ref<U>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<T>>() >=
            ::asc::std::declval<__make_const_lvalue_ref<U>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<U>>() < ::asc::std::declval<__make_const_lvalue_ref<T>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<U>>() > ::asc::std::declval<__make_const_lvalue_ref<T>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<U>>() <=
            ::asc::std::declval<__make_const_lvalue_ref<T>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<U>>() >=
            ::asc::std::declval<__make_const_lvalue_ref<T>>())>> =
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<T>>() <
        ::asc::std::declval<__make_const_lvalue_ref<U>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<T>>() >
        ::asc::std::declval<__make_const_lvalue_ref<U>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<T>>() <=
        ::asc::std::declval<__make_const_lvalue_ref<U>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<T>>() >=
        ::asc::std::declval<__make_const_lvalue_ref<U>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<U>>() <
        ::asc::std::declval<__make_const_lvalue_ref<T>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<U>>() >
        ::asc::std::declval<__make_const_lvalue_ref<T>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<U>>() <=
        ::asc::std::declval<__make_const_lvalue_ref<T>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<U>>() >=
        ::asc::std::declval<__make_const_lvalue_ref<T>>())>;

template <class T, class U>
inline constexpr bool __partially_ordered_with = __partially_ordered_with_impl<T, U>;

template <class T, class U, class = void>
inline constexpr bool __totally_ordered_with_impl = false;

template <class T, class U>
inline constexpr bool __totally_ordered_with_impl<T, U,
    void_t<common_reference_t<__make_const_lvalue_ref<T>, __make_const_lvalue_ref<U>>>> =
    __weakly_equality_comparable_with<T, T> && __partially_ordered_with<T, T> &&
    __weakly_equality_comparable_with<U, U> && __partially_ordered_with<U, U> &&
    __equality_comparable_with_impl<T, U> &&
    __common_reference_with_impl<__make_const_lvalue_ref<T>, __make_const_lvalue_ref<U>> &&
    __weakly_equality_comparable_with<common_reference_t<__make_const_lvalue_ref<T>, __make_const_lvalue_ref<U>>,
        common_reference_t<__make_const_lvalue_ref<T>, __make_const_lvalue_ref<U>>> &&
    __partially_ordered_with<common_reference_t<__make_const_lvalue_ref<T>, __make_const_lvalue_ref<U>>,
        common_reference_t<__make_const_lvalue_ref<T>, __make_const_lvalue_ref<U>>> &&
    __partially_ordered_with<T, U>;

template <class T>
inline constexpr bool totally_ordered = __weakly_equality_comparable_with<T, T> && __partially_ordered_with<T, T>;
template <class T, class U>
inline constexpr bool totally_ordered_with = __totally_ordered_with_impl<T, U>;
#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CONCEPTS_TOTALLY_ORDERED_H
