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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_DISJUNCTION_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_DISJUNCTION_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/integral_constant.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <bool>
struct __or_impl;
template <>
struct __or_impl<true> {
    template <class Result, class First, class... Rest>
    using type =
        typename __or_impl<!static_cast<bool>(First::value) && sizeof...(Rest) != 0>::template type<First, Rest...>;
};
template <>
struct __or_impl<false> {
    template <class Result, class...>
    using type = Result;
};
template <class... Predicates>
using _Or = typename __or_impl<sizeof...(Predicates) != 0>::template type<false_type, Predicates...>;
template <class...>
struct disjunction;
template <class... Predicates>
struct disjunction : _Or<Predicates...> {};
template <class... Predicates>
inline constexpr bool disjunction_v = _Or<Predicates...>::value;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_DISJUNCTION_H
