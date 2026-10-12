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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_CONST_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_CONST_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__remove_const)
#define CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_CONST(...) __remove_const(__VA_ARGS__)
#endif  // CANN_ASC_STL_DETAIL_HAS_BUILTIN(__remove_const)

CANN_ASC_STL_BEGIN_NAMESPACE

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_CONST) && !defined(CANN_ASC_STL_DETAIL_USE_REMOVE_CONST_FALLBACK)
template <class _Tp>
struct remove_const {
    using type = CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_CONST(_Tp);
};

template <class _Tp>
using remove_const_t = CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_CONST(_Tp);

#else

template <class _Tp>
struct remove_const {
    using type = _Tp;
};
template <class _Tp>
struct remove_const<const _Tp> {
    using type = _Tp;
};

template <class _Tp>
using remove_const_t = typename remove_const<_Tp>::type;

#endif  // defined(CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_CONST) &&
        // !defined(CANN_ASC_STL_DETAIL_USE_REMOVE_CONST_FALLBACK)

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_CONST_H
