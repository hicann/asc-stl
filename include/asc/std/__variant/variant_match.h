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

#ifndef CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_MATCH_H
#define CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_MATCH_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__tuple/tuple_indices.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/type_identity.h>
#include <asc/std/__utility/integer_sequence.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T, class... Types>
struct __variant_find_exact;
template <class T>
struct __variant_find_exact<T> : integral_constant<__SIZE_TYPE__, static_cast<__SIZE_TYPE__>(-1)> {};
template <class T, class Head, class... Tail>
struct __variant_find_exact<T, Head, Tail...>
    : integral_constant<__SIZE_TYPE__,
          __is_same(T, Head) ? 0 :
                               (__variant_find_exact<T, Tail...>::value == static_cast<__SIZE_TYPE__>(-1) ?
                                       static_cast<__SIZE_TYPE__>(-1) :
                                       1 + __variant_find_exact<T, Tail...>::value)> {};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___VARIANT_VARIANT_MATCH_H
