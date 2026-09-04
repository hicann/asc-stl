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

#ifndef CANN_ASC_STL_ASC_STD___FLOATING_POINT_NATIVE_TYPE_H
#define CANN_ASC_STL_ASC_STD___FLOATING_POINT_NATIVE_TYPE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__floating_point/format.h>
#include <asc/std/__floating_point/traits.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/cfloat>

CANN_ASC_STL_BEGIN_NAMESPACE

template <__fp_format Fmt>
CANN_ASC_STL_API constexpr auto __fp_native_type_impl() noexcept
{
    if constexpr (Fmt == __fp_format::__binary32) {
        return float{};
    } else if constexpr (Fmt == __fp_format::__binary64) {
        return double{};
    } else if constexpr (Fmt == __long_double_format) {
        return static_cast<long double>(0);
    } else {
        return;
    }
}

template <__fp_format Fmt>
using __fp_native_type_t = decltype(__fp_native_type_impl<Fmt>());
template <__fp_format Fmt>
inline constexpr bool __fp_has_native_type_v = !is_void_v<__fp_native_type_t<Fmt>>;
template <class T>
inline constexpr bool __fp_is_native_type_v = __is_std_fp_v<T>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FLOATING_POINT_NATIVE_TYPE_H
