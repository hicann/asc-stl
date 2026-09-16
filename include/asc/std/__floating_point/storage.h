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
#ifndef CANN_ASC_STL_STD_DETAIL_FLOATING_POINT_STORAGE_H
#define CANN_ASC_STL_STD_DETAIL_FLOATING_POINT_STORAGE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__bit/bit_cast.h>
#include <asc/std/__floating_point/format.h>
#include <asc/std/__floating_point/traits.h>
#include <asc/std/__type_traits/always_false.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

template <bool, class T = void>
struct __fp_storage_enable_if {};

template <class T>
struct __fp_storage_enable_if<true, T> {
    using type = T;
};

// The ASC __fp_format vocabulary has no 8/6/4-bit vendor formats, and
// __int128 is not a delivered contract, so the wider-than-binary64 formats
// fall into the unsupported static_assert branch.
template <__fp_format Fmt>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr auto __fp_storage_type_impl() noexcept
{
    if constexpr (Fmt == __fp_format::__binary16 || Fmt == __fp_format::__bfloat16) {
        return uint16_t{};
    } else if constexpr (Fmt == __fp_format::__binary32) {
        return uint32_t{};
    } else if constexpr (Fmt == __fp_format::__binary64) {
        return uint64_t{};
    } else {
        static_assert(__always_false_v<decltype(Fmt)>, "Unsupported floating point format");
    }
}

template <__fp_format Fmt>
using __fp_storage_t = decltype(__fp_storage_type_impl<Fmt>());

template <class Tp>
using __fp_storage_of_t = __fp_storage_t<__fp_format_of_v<Tp>>;

template <class Tp>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr Tp __fp_from_storage(__fp_storage_of_t<Tp> v) noexcept
{
    if constexpr (__is_std_fp_v<Tp>) {
        return asc::std::bit_cast<Tp>(v);
    } else if constexpr (__is_ext_asc_fp_v<Tp>) {
        Tp ret{};
        ret.__storage_ = v;
        return ret;
    } else {
        static_assert(__always_false_v<Tp>, "Unsupported floating point format");
    }
}

template <class Tp, class Up>
CANN_ASC_STL_API constexpr auto __fp_from_storage(const Up&) noexcept ->
    typename __fp_storage_enable_if<!is_same_v<Up, __fp_storage_of_t<Tp>>, Tp>::type = delete;

template <class Tp>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr __fp_storage_of_t<Tp> __fp_get_storage(Tp v) noexcept
{
    if constexpr (__is_std_fp_v<Tp>) {
        return asc::std::bit_cast<__fp_storage_of_t<Tp>>(v);
    } else if constexpr (__is_ext_asc_fp_v<Tp>) {
        return v.__storage_;
    } else {
        static_assert(__always_false_v<Tp>, "Unsupported floating point format");
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_FLOATING_POINT_STORAGE_H
