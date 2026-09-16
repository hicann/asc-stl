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
#ifndef CANN_ASC_STL_STD_DETAIL_FWD_VARIANT_H
#define CANN_ASC_STL_STD_DETAIL_FWD_VARIANT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class... Types>
class variant;

template <class T>
struct variant_size;

template <class T>
inline constexpr __SIZE_TYPE__ variant_size_v = variant_size<T>::value;

template <__SIZE_TYPE__ Ip, class T>
struct variant_alternative;

template <__SIZE_TYPE__ Ip, class T>
using variant_alternative_t = typename variant_alternative<Ip, T>::type;

inline constexpr __SIZE_TYPE__ variant_npos = static_cast<__SIZE_TYPE__>(-1);

template <class T>
inline constexpr T __variant_npos = static_cast<T>(-1);

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_FWD_VARIANT_H
