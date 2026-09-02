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
#ifndef CANN_ASC_STL_ASC_STDDETAIL__ITERATOR_READABLE_TRAITS_H
#define CANN_ASC_STL_ASC_STDDETAIL__ITERATOR_READABLE_TRAITS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__fwd/iterator.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_const.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_primary_template.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_extent.h>
#include <asc/std/__type_traits/void_t.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _Tp, class = void>
inline constexpr bool __has_member_value_type_v = false;

template <class _Tp>
inline constexpr bool __has_member_value_type_v<_Tp, void_t<typename _Tp::value_type>> = true;

template <class _Tp, class = void>
inline constexpr bool __has_member_element_type_v = false;

template <class _Tp>
inline constexpr bool __has_member_element_type_v<_Tp, void_t<typename _Tp::element_type>> = true;

template <class, class = void>
struct __cond_value_type {};

template <class _Tp>
struct __cond_value_type<_Tp, enable_if_t<is_object_v<_Tp>>> {
    using value_type = remove_cv_t<_Tp>;
};

// [readable.traits]
template <class _Tp>
struct indirectly_readable_traits;

template <class _Tp, class = void>
struct __indirectly_readable_traits_impl {};

template <class _Ip>
struct __indirectly_readable_traits_impl<_Ip, enable_if_t<!is_const_v<_Ip> && is_array_v<_Ip>>> {
    using value_type = remove_cv_t<remove_extent_t<_Ip>>;
};

template <class _Ip>
struct __indirectly_readable_traits_impl<const _Ip> : indirectly_readable_traits<_Ip> {};

template <class _Tp>
struct __indirectly_readable_traits_impl<_Tp*> : __cond_value_type<_Tp> {};

template <class _Tp>
struct __indirectly_readable_traits_impl<_Tp,
    enable_if_t<!is_const_v<_Tp> && __has_member_value_type_v<_Tp> && !__has_member_element_type_v<_Tp>>>
    : __cond_value_type<typename _Tp::value_type> {};

template <class _Tp>
struct __indirectly_readable_traits_impl<_Tp,
    enable_if_t<!is_const_v<_Tp> && !__has_member_value_type_v<_Tp> && __has_member_element_type_v<_Tp>>>
    : __cond_value_type<typename _Tp::element_type> {};

template <class _Tp>
struct __indirectly_readable_traits_impl<_Tp,
    enable_if_t<!is_const_v<_Tp> && __has_member_value_type_v<_Tp> && __has_member_element_type_v<_Tp> &&
        !is_same_v<remove_cv_t<typename _Tp::element_type>, remove_cv_t<typename _Tp::value_type>>>> {};

template <class _Tp>
struct __indirectly_readable_traits_impl<_Tp,
    enable_if_t<!is_const_v<_Tp> && __has_member_value_type_v<_Tp> && __has_member_element_type_v<_Tp> &&
        is_same_v<remove_cv_t<typename _Tp::element_type>, remove_cv_t<typename _Tp::value_type>>>>
    : __cond_value_type<typename _Tp::value_type> {};

template <class _Tp>
struct indirectly_readable_traits : __indirectly_readable_traits_impl<_Tp> {};

// Let `RI` be `remove_cvref_t<I>`. The type `iter_value_t<I>` denotes
// `indirectly_readable_traits<RI>::value_type` if `iterator_traits<RI>` names a specialization
// generated from the primary template, and `iterator_traits<RI>::value_type` otherwise.
template <class T, class OtherTraits, class = void>
struct __readable_select_traits {
    using type = OtherTraits;
};
template <class T, class OtherTraits>
struct __readable_select_traits<T, OtherTraits, void_t<decltype(sizeof(iterator_traits<T>))>> {
    using type = __select_traits<T, OtherTraits>;
};
template <class _Ip>
using iter_value_t = typename __readable_select_traits<remove_cvref_t<_Ip>,
    indirectly_readable_traits<remove_cvref_t<_Ip>>>::type::value_type;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STDDETAIL__ITERATOR_READABLE_TRAITS_H
