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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPTS_EQUALITY_COMPARABLE_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPTS_EQUALITY_COMPARABLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/boolean_testable.h>
#include <asc/std/__concepts/common_reference_with.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/common_reference.h>
#include <asc/std/__type_traits/make_const_lvalue_ref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Tp, class _Up>
concept __weakly_equality_comparable_with =
    requires(__make_const_lvalue_ref<_Tp> __t, __make_const_lvalue_ref<_Up> __u) {
        { __t == __u } -> __boolean_testable;
        { __t != __u } -> __boolean_testable;
        { __u == __t } -> __boolean_testable;
        { __u != __t } -> __boolean_testable;
    };

template <class _Tp>
concept equality_comparable = __weakly_equality_comparable_with<_Tp, _Tp>;

template <class _Tp, class _Up>
concept equality_comparable_with = equality_comparable<_Tp> && equality_comparable<_Up> &&
    common_reference_with<__make_const_lvalue_ref<_Tp>, __make_const_lvalue_ref<_Up>> &&
    equality_comparable<common_reference_t<__make_const_lvalue_ref<_Tp>, __make_const_lvalue_ref<_Up>>> &&
    __weakly_equality_comparable_with<_Tp, _Up>;

#else

template <class _Tp, class _Up, class = void>
inline constexpr bool __weakly_equality_comparable_with_impl = false;

template <class _Tp, class _Up>
inline constexpr bool __weakly_equality_comparable_with_impl<_Tp, _Up,
    void_t<__make_const_lvalue_ref<_Tp>, __make_const_lvalue_ref<_Up>,
        decltype(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() ==
            ::asc::std::declval<__make_const_lvalue_ref<_Up>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() !=
            ::asc::std::declval<__make_const_lvalue_ref<_Up>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<_Up>>() ==
            ::asc::std::declval<__make_const_lvalue_ref<_Tp>>()),
        decltype(::asc::std::declval<__make_const_lvalue_ref<_Up>>() !=
            ::asc::std::declval<__make_const_lvalue_ref<_Tp>>())>> =
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() ==
        ::asc::std::declval<__make_const_lvalue_ref<_Up>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<_Tp>>() !=
        ::asc::std::declval<__make_const_lvalue_ref<_Up>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<_Up>>() ==
        ::asc::std::declval<__make_const_lvalue_ref<_Tp>>())> &&
    __boolean_testable<decltype(::asc::std::declval<__make_const_lvalue_ref<_Up>>() !=
        ::asc::std::declval<__make_const_lvalue_ref<_Tp>>())>;

template <class _Tp, class _Up>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __weakly_equality_comparable_with = __weakly_equality_comparable_with_impl<_Tp, _Up>;

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT equality_comparable = __weakly_equality_comparable_with<_Tp, _Tp>;

template <class _Tp, class _Up, class = void>
inline constexpr bool __equality_comparable_with_impl = false;

template <class _Tp, class _Up>
inline constexpr bool __equality_comparable_with_impl<_Tp, _Up,
    void_t<common_reference_t<__make_const_lvalue_ref<_Tp>, __make_const_lvalue_ref<_Up>>>> =
    equality_comparable<_Tp> && equality_comparable<_Up> &&
    common_reference_with<__make_const_lvalue_ref<_Tp>, __make_const_lvalue_ref<_Up>> &&
    equality_comparable<common_reference_t<__make_const_lvalue_ref<_Tp>, __make_const_lvalue_ref<_Up>>> &&
    __weakly_equality_comparable_with<_Tp, _Up>;

template <class _Tp, class _Up>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT equality_comparable_with = __equality_comparable_with_impl<_Tp, _Up>;

#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CONCEPTS_EQUALITY_COMPARABLE_H
