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

#ifndef CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_LIKE_H
#define CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_LIKE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__fwd/array.h>
#include <asc/std/__fwd/complex.h>
#include <asc/std/__fwd/pair.h>
#include <asc/std/__fwd/subrange.h>
#include <asc/std/__fwd/tuple.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__tuple/tuple_types.h>
#include <asc/std/cstddef>
#include <asc/std/__type_traits/remove_cvref.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// Extended tuple-like detection: true for every type that participates in
// the tuple protocol (tuple_size / tuple_element / get). This variable
// template form is SFINAE-friendly and works without concepts.
template <class T>
inline constexpr bool __tuple_like_ext = false;
template <class T>
inline constexpr bool __tuple_like_ext<const T> = __tuple_like_ext<T>;
template <class T>
inline constexpr bool __tuple_like_ext<volatile T> = __tuple_like_ext<T>;
template <class T>
inline constexpr bool __tuple_like_ext<const volatile T> = __tuple_like_ext<T>;
template <class... Types>
inline constexpr bool __tuple_like_ext<tuple<Types...>> = true;  // NOLINT(build/include_what_you_use)
template <class T1, class T2>
inline constexpr bool __tuple_like_ext<pair<T1, T2>> = true;  // NOLINT(build/include_what_you_use)
template <class T, size_t Size>
inline constexpr bool __tuple_like_ext<array<T, Size>> = true;
template <class T>
inline constexpr bool __tuple_like_ext<complex<T>> = true;
template <class Iter, class Sent, ranges::subrange_kind Kind>
inline constexpr bool __tuple_like_ext<ranges::subrange<Iter, Sent, Kind>> = true;
template <class... Types>
inline constexpr bool __tuple_like_ext<__tuple_types<Types...>> = true;

// pair-like（二元 tuple 协议类型）判定：供 ranges::subrange 的 pair 构造约束
// 使用。变量模板形式与 __tuple_like_ext 一致，无 concepts 环境也可用。
template <class T>
inline constexpr bool __pair_like = __tuple_like_ext<remove_cvref_t<T>> && tuple_size<remove_cvref_t<T>>::value == 2;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_LIKE_H
