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
#ifndef CANN_ASC_STL_ASC_STDDETAIL__ITERATOR_INCREMENTABLE_TRAITS_H
#define CANN_ASC_STL_ASC_STDDETAIL__ITERATOR_INCREMENTABLE_TRAITS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
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

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _Tp, class = void>
inline constexpr bool __has_member_difference_type_v = false;

template <class _Tp>
inline constexpr bool __has_member_difference_type_v<_Tp, void_t<typename _Tp::difference_type>> = true;

template <class _Tp, class = void, class = void>
inline constexpr bool __has_integral_minus_impl = false;

// In C++17 we get issues trying to bind void* to a const& so special case it here
template <class _Tp>
inline constexpr bool __has_integral_minus_impl<_Tp, enable_if_t<!is_same_v<_Tp, void*>>,
    void_t<decltype(::asc::std::declval<const _Tp&>() - ::asc::std::declval<const _Tp&>())>> =
    is_integral_v<decltype(::asc::std::declval<const _Tp&>() - ::asc::std::declval<const _Tp&>())>;

// [incrementable.traits]
template <class _Tp>
struct incrementable_traits;

template <class _Tp, class = void>
struct __incrementable_traits_impl {};

template <class _Tp>
struct __incrementable_traits_impl<_Tp*, enable_if_t<is_object_v<_Tp>>> {
    using difference_type = ptrdiff_t;
};

template <class _Ip>
struct __incrementable_traits_impl<const _Ip> : incrementable_traits<_Ip> {};

template <class _Tp>
struct __incrementable_traits_impl<_Tp,
    enable_if_t<!is_pointer_v<_Tp> && !is_const_v<_Tp> && __has_member_difference_type_v<_Tp>>> {
    using difference_type = typename _Tp::difference_type;
};

template <class _Tp>
struct __incrementable_traits_impl<_Tp,
    enable_if_t<!is_pointer_v<_Tp> && !is_const_v<_Tp> && !__has_member_difference_type_v<_Tp> &&
        __has_integral_minus_impl<_Tp>>> {
    using difference_type = make_signed_t<decltype(::asc::std::declval<_Tp>() - ::asc::std::declval<_Tp>())>;
};

template <class _Tp>
struct incrementable_traits : __incrementable_traits_impl<_Tp> {};

// Let `RI` be `remove_cvref_t<I>`. The type `iter_difference_t<I>` denotes
// `incrementable_traits<RI>::difference_type` if `iterator_traits<RI>` names a specialization
// generated from the primary template, and `iterator_traits<RI>::difference_type` otherwise.
template <class T, class OtherTraits, class = void>
struct __incrementable_select_traits {
    using type = OtherTraits;
};
template <class T, class OtherTraits>
struct __incrementable_select_traits<T, OtherTraits, void_t<decltype(sizeof(iterator_traits<T>))>> {
    using type = __select_traits<T, OtherTraits>;
};
template <class _Ip>
using iter_difference_t = typename __incrementable_select_traits<remove_cvref_t<_Ip>,
    incrementable_traits<remove_cvref_t<_Ip>>>::type::difference_type;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STDDETAIL__ITERATOR_INCREMENTABLE_TRAITS_H
