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

#ifndef CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_CONSTRAINTS_H
#define CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_CONSTRAINTS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__fwd/variant.h>
#include <asc/std/__tuple/get.h>
#include <asc/std/__tuple/sfinae_helpers.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__variant/variant_match.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T, class... Types>
struct __variant_type_count;
template <class T>
struct __variant_type_count<T> : integral_constant<__SIZE_TYPE__, 0> {};
template <class T, class Head, class... Tail>
struct __variant_type_count<T, Head, Tail...>
    : integral_constant<__SIZE_TYPE__, (is_same_v<T, Head> ? 1 : 0) + __variant_type_count<T, Tail...>::value> {};
template <class T, class... Types>
inline constexpr __SIZE_TYPE__ __variant_type_count_v = __variant_type_count<T, Types...>::value;
template <class T, class... Types>
inline constexpr __SIZE_TYPE__ __variant_index_v = __variant_find_exact<remove_cvref_t<T>, Types...>::value;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_CONSTRAINTS_H
