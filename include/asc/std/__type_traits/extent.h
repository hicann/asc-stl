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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_EXTENT_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_EXTENT_H

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
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__array_extent)

template <class T, size_t Ip = 0>
struct extent : integral_constant<size_t, __array_extent(T, Ip)> {};

template <class T, unsigned int Ip = 0>
inline constexpr size_t extent_v = __array_extent(T, Ip);

#else

template <class T, unsigned int Ip = 0>
inline constexpr size_t extent_v = 0;
template <class T>
inline constexpr size_t extent_v<T[], 0> = 0;
template <class T, unsigned int Ip>
inline constexpr size_t extent_v<T[], Ip> = extent_v<T, Ip - 1>;
template <class T, size_t N>
inline constexpr size_t extent_v<T[N], 0> = N;
template <class T, size_t N, unsigned int Ip>
inline constexpr size_t extent_v<T[N], Ip> = extent_v<T, Ip - 1>;

template <class T, size_t Ip = 0>
struct extent : integral_constant<size_t, extent_v<T, Ip> > {};

#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_EXTENT_H
