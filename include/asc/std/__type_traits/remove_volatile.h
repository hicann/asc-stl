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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_VOLATILE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_VOLATILE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__remove_volatile)
#define CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_VOLATILE(...) __remove_volatile(__VA_ARGS__)
#endif  // CANN_ASC_STL_DETAIL_HAS_BUILTIN(__remove_volatile)

CANN_ASC_STL_BEGIN_NAMESPACE

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_VOLATILE) && !defined(CANN_ASC_STL_DETAIL_USE_REMOVE_VOLATILE_FALLBACK)
template <class _Tp>
struct remove_volatile {
    using type = CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_VOLATILE(_Tp);
};

template <class _Tp>
using remove_volatile_t = CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_VOLATILE(_Tp);

#else

template <class _Tp>
struct remove_volatile {
    using type = _Tp;
};
template <class _Tp>
struct remove_volatile<volatile _Tp> {
    using type = _Tp;
};

template <class _Tp>
using remove_volatile_t = typename remove_volatile<_Tp>::type;

#endif  // defined(CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_VOLATILE) &&
        // !defined(CANN_ASC_STL_DETAIL_USE_REMOVE_VOLATILE_FALLBACK)

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_VOLATILE_H
