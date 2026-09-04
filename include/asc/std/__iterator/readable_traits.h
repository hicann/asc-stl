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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_READABLE_TRAITS_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_READABLE_TRAITS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__fwd/iterator.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_const.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_extent.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __has_member_value_type =
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Tp))(typename(typename _Tp::value_type));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __has_member_element_type =
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_Tp))(typename(typename _Tp::element_type));

template <class, class = void>
struct __cond_value_type {};

template <class _Tp>
struct __cond_value_type<_Tp, enable_if_t<is_object_v<_Tp>>> {
    using value_type = remove_cv_t<_Tp>;
};

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class>
struct indirectly_readable_traits {};

template <class _Ip>
    requires is_array_v<_Ip>
struct indirectly_readable_traits<_Ip> {
    using value_type = remove_cv_t<remove_extent_t<_Ip>>;
};

template <class _Ip>
struct indirectly_readable_traits<const _Ip> : indirectly_readable_traits<_Ip> {};

template <class _Tp>
struct indirectly_readable_traits<_Tp*> : __cond_value_type<_Tp> {};

template <__has_member_value_type _Tp>
struct indirectly_readable_traits<_Tp> : __cond_value_type<typename _Tp::value_type> {};

template <__has_member_element_type _Tp>
struct indirectly_readable_traits<_Tp> : __cond_value_type<typename _Tp::element_type> {};

template <__has_member_value_type _Tp>
    requires __has_member_element_type<_Tp>
struct indirectly_readable_traits<_Tp> {};

template <__has_member_value_type _Tp>
    requires __has_member_element_type<_Tp> &&
    same_as<remove_cv_t<typename _Tp::element_type>, remove_cv_t<typename _Tp::value_type>>
struct indirectly_readable_traits<_Tp> : __cond_value_type<typename _Tp::value_type> {};

#else

template <class, class = void>
struct indirectly_readable_traits {};

template <class _Ip>
struct indirectly_readable_traits<_Ip, enable_if_t<!is_const_v<_Ip> && is_array_v<_Ip>>> {
    using value_type = remove_cv_t<remove_extent_t<_Ip>>;
};

template <class _Ip>
struct indirectly_readable_traits<const _Ip> : indirectly_readable_traits<_Ip> {};

template <class _Tp>
struct indirectly_readable_traits<_Tp*> : __cond_value_type<_Tp> {};

template <class _Tp>
struct indirectly_readable_traits<_Tp,
    enable_if_t<!is_const_v<_Tp> && __has_member_value_type<_Tp> && !__has_member_element_type<_Tp>>>
    : __cond_value_type<typename _Tp::value_type> {};

template <class _Tp>
struct indirectly_readable_traits<_Tp,
    enable_if_t<!is_const_v<_Tp> && !__has_member_value_type<_Tp> && __has_member_element_type<_Tp>>>
    : __cond_value_type<typename _Tp::element_type> {};

template <class _Tp>
struct indirectly_readable_traits<_Tp,
    enable_if_t<!is_const_v<_Tp> && __has_member_value_type<_Tp> && __has_member_element_type<_Tp> &&
        same_as<remove_cv_t<typename _Tp::element_type>, remove_cv_t<typename _Tp::value_type>>>>
    : __cond_value_type<typename _Tp::value_type> {};

#endif

template <class _Ip>
using iter_value_t =
    typename __select_traits<remove_cvref_t<_Ip>, indirectly_readable_traits<remove_cvref_t<_Ip>>>::value_type;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_READABLE_TRAITS_H
