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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_CV_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_CV_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__type_traits/remove_volatile.h>

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__remove_cv)
#define CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_CV(...) __remove_cv(__VA_ARGS__)
#endif  // CANN_ASC_STL_DETAIL_HAS_BUILTIN(__remove_cv)

CANN_ASC_STL_BEGIN_NAMESPACE

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_CV) && !defined(CANN_ASC_STL_DETAIL_USE_REMOVE_CV_FALLBACK)
template <class _Tp>
struct remove_cv {
    using type = CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_CV(_Tp);
};

template <class _Tp>
using remove_cv_t = typename remove_cv<_Tp>::type;

#else

template <class _Tp>
struct remove_cv {
    using type = remove_volatile_t<remove_const_t<_Tp> >;
};

template <class _Tp>
using remove_cv_t = remove_volatile_t<remove_const_t<_Tp> >;

#endif  // defined(CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_CV) && !defined(CANN_ASC_STL_DETAIL_USE_REMOVE_CV_FALLBACK)

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_CV_H
