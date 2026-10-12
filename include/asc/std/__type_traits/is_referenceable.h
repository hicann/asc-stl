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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_REFERENCEABLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_REFERENCEABLE_H

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
#include <asc/std/__type_traits/is_same.h>

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_referenceable)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_REFERENCEABLE(...) __is_referenceable(__VA_ARGS__)
#endif  // CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_referenceable)

CANN_ASC_STL_BEGIN_NAMESPACE

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_REFERENCEABLE) && !defined(CANN_ASC_STL_DETAIL_USE_IS_REFERENCEABLE_FALLBACK)

template <class _Tp>
struct __asc_is_referenceable : public integral_constant<bool, CANN_ASC_STL_DETAIL_BUILTIN_IS_REFERENCEABLE(_Tp)> {};

#else
struct __asc_is_referenceable_impl {
    template <class _Tp>
    CANN_ASC_STL_HOST_DEVICE static _Tp& __test(int);
    template <class _Tp>
    static false_type __test(long);
};

template <class _Tp>
struct __asc_is_referenceable
    : integral_constant<bool, _IsNotSame<decltype(__asc_is_referenceable_impl::__test<_Tp>(0)), false_type>::value> {};
#endif  // defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_REFERENCEABLE) &&
        // !defined(CANN_ASC_STL_DETAIL_USE_IS_REFERENCEABLE_FALLBACK)

// 兼容 master 侧既有消费方的旧名
template <class _Tp>
using __is_referenceable = __asc_is_referenceable<_Tp>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_REFERENCEABLE_H
