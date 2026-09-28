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

#ifndef CANN_ASC_STL_ASC_STD___TYPE_TRAITS_ALIGNED_UNION_H
#define CANN_ASC_STL_ASC_STD___TYPE_TRAITS_ALIGNED_UNION_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/aligned_storage.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

template <size_t _I0, size_t... _In>
struct __static_max;

template <size_t _I0>
struct __static_max<_I0> {
    static const size_t value = _I0;
};

template <size_t _I0, size_t _I1, size_t... _In>
struct __static_max<_I0, _I1, _In...> {
    static const size_t value = _I0 >= _I1 ? __static_max<_I0, _In...>::value : __static_max<_I1, _In...>::value;
};

template <size_t _Len, class _Type0, class... _Types>
struct aligned_union {
    static const size_t alignment_value = __static_max<alignof(_Type0), alignof(_Types)...>::value;
    static const size_t __len = __static_max<_Len, sizeof(_Type0), sizeof(_Types)...>::value;
    using type = typename aligned_storage<__len, alignment_value>::type;
};

template <size_t _Len, class... _Types>
using aligned_union_t = typename aligned_union<_Len, _Types...>::type;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TYPE_TRAITS_ALIGNED_UNION_H
