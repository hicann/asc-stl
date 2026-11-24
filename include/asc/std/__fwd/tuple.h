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
#ifndef CANN_ASC_STL_STD_DETAIL_FWD_TUPLE_H
#define CANN_ASC_STL_STD_DETAIL_FWD_TUPLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>

// Hosted ::std interoperation gate: a host standard library has been pulled in.
#ifndef CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB
#if defined(__GLIBCXX__) || defined(_LIBCPP_VERSION) || defined(_MSVC_STL_VERSION)
#define CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB

// std:: forward declarations

// The language's tuple binding protocol names ::std even in a freestanding
// Device translation unit. Keep its primary declarations in this one owner;
// extension proxies provide only their own specializations.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
namespace std {
template <class>
struct tuple_size;
template <__SIZE_TYPE__, class>
struct tuple_element;
}  // namespace std
#endif

#if CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()
namespace std {
template <class...>
class tuple;
}  // namespace std
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()

// asc::std:: forward declarations

CANN_ASC_STL_BEGIN_NAMESPACE

template <class... Types>
class tuple;

template <class T>
inline constexpr bool __is_tuple_of_iterator_references_v = false;

template <class T>
inline constexpr bool __is_asc_std_tuple = false;

template <class... Types>
inline constexpr bool __is_asc_std_tuple<tuple<Types...>> = true;  // NOLINT(build/include_what_you_use)

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_FWD_TUPLE_H
