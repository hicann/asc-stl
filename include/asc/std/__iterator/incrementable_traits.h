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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_INCREMENTABLE_TRAITS_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_INCREMENTABLE_TRAITS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/arithmetic.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__fwd/iterator.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_const.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_primary_template.h>
#include <asc/std/__type_traits/make_signed.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Tp>
concept __has_member_difference_type = requires { typename _Tp::difference_type; };

#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv

template <class _Tp, class = void>
inline constexpr bool __has_member_difference_type = false;
template <class _Tp>
inline constexpr bool __has_member_difference_type<_Tp, void_t<typename _Tp::difference_type>> = true;

#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

template <class _Tp, class = void, class = void>
inline constexpr bool __has_integral_minus_impl = false;

// In C++17 we get issues trying to bind void* to a const& so special case it here
template <class _Tp>
inline constexpr bool __has_integral_minus_impl<_Tp, enable_if_t<!same_as<_Tp, void*>>,
    void_t<decltype(::asc::std::declval<const _Tp&>() - ::asc::std::declval<const _Tp&>())>> =
    integral<decltype(::asc::std::declval<const _Tp&>() - ::asc::std::declval<const _Tp&>())>;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Tp>
concept __has_integral_minus = __has_integral_minus_impl<_Tp>;

#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv

template <class _Tp>
inline constexpr bool __has_integral_minus = __has_integral_minus_impl<_Tp>;

#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

// [incrementable.traits]
template <class>
struct incrementable_traits {};

template <class _Tp>
    requires is_object_v<_Tp>
struct incrementable_traits<_Tp*> {
    using difference_type = ptrdiff_t;
};

template <class _Ip>
struct incrementable_traits<const _Ip> : incrementable_traits<_Ip> {};

template <__has_member_difference_type _Tp>
struct incrementable_traits<_Tp> {
    using difference_type = typename _Tp::difference_type;
};

template <__has_integral_minus _Tp>
    requires(!__has_member_difference_type<_Tp>)
struct incrementable_traits<_Tp> {
    using difference_type = make_signed_t<decltype(::asc::std::declval<_Tp>() - ::asc::std::declval<_Tp>())>;
};

// Let `RI` be `remove_cvref_t<I>`. The type `iter_difference_t<I>` denotes
// `incrementable_traits<RI>::difference_type` if `iterator_traits<RI>` names a specialization
// generated from the primary template, and `iterator_traits<RI>::difference_type` otherwise.
template <class _Ip>
using iter_difference_t =
    typename __select_traits<remove_cvref_t<_Ip>, incrementable_traits<remove_cvref_t<_Ip>>>::difference_type;

#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv

// [incrementable.traits]
template <class, class = void>
struct incrementable_traits {};

template <class _Tp>
struct incrementable_traits<_Tp*, enable_if_t<is_object_v<_Tp>>> {
    using difference_type = ptrdiff_t;
};

template <class _Ip>
struct incrementable_traits<const _Ip> : incrementable_traits<_Ip> {};

template <class _Tp>
struct incrementable_traits<_Tp,
    enable_if_t<!is_pointer_v<_Tp> && !is_const_v<_Tp> && __has_member_difference_type<_Tp>>> {
    using difference_type = typename _Tp::difference_type;
};

template <class _Tp>
struct incrementable_traits<_Tp,
    enable_if_t<!is_pointer_v<_Tp> && !is_const_v<_Tp> && !__has_member_difference_type<_Tp> &&
        __has_integral_minus<_Tp>>> {
    using difference_type = make_signed_t<decltype(::asc::std::declval<_Tp>() - ::asc::std::declval<_Tp>())>;
};

// Let `RI` be `remove_cvref_t<I>`. The type `iter_difference_t<I>` denotes
// `incrementable_traits<RI>::difference_type` if `iterator_traits<RI>` names a specialization
// generated from the primary template, and `iterator_traits<RI>::difference_type` otherwise.
template <class _Ip>
using iter_difference_t =
    typename __select_traits<remove_cvref_t<_Ip>, incrementable_traits<remove_cvref_t<_Ip>>>::difference_type;

#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_INCREMENTABLE_TRAITS_H
