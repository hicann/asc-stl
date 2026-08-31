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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_NUM_BITS_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_NUM_BITS_H

#include <asc/std/detail/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__fwd/complex.h>
#include <asc/std/__type_traits/always_false.h>
#include <asc/std/__type_traits/has_unique_object_representation.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/climits>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// 基础类型与指针：按字节数计位。
template <typename _RawTp>
[[nodiscard]] CANN_ASC_STL_API constexpr int __num_bits_of_basic() noexcept
{
    return sizeof(_RawTp) * CHAR_BIT;
}

// 16 位扩展标量：half / bfloat16 家族。
template <typename _RawTp>
[[nodiscard]] CANN_ASC_STL_API constexpr int __num_bits_of_16bit() noexcept
{
#if CANN_ASC_STL_DETAIL_HAS_HALF()
    if constexpr (is_same_v<_RawTp, half>) {
        return sizeof(_RawTp) * CHAR_BIT;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_HALF2()
        if constexpr (is_same_v<_RawTp, half2>) {
        return sizeof(_RawTp) * CHAR_BIT;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
        if constexpr (is_same_v<_RawTp, bfloat16_t>) {
        return sizeof(_RawTp) * CHAR_BIT;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2()
        if constexpr (is_same_v<_RawTp, bfloat16x2_t>) {
        return sizeof(_RawTp) * CHAR_BIT;
    } else  // NOLINT(readability/braces)
#endif
    {
        return -1;
    }
}

// FP8 家族与 __float128：固定宽度或按字节数计位。
template <typename _RawTp>
[[nodiscard]] CANN_ASC_STL_API constexpr int __num_bits_of_fp8_and_qlike() noexcept
{
#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
    if constexpr (is_same_v<_RawTp, float8_e4m3_t>) {
        return 8;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
        if constexpr (is_same_v<_RawTp, float8_e5m2_t>) {
        return 8;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
        if constexpr (is_same_v<_RawTp, float8_e8m0_t>) {
        return 8;
    } else  // NOLINT(readability/braces)
#endif
#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
        if constexpr (is_same_v<_RawTp, __float128>) {
        return sizeof(_RawTp) * CHAR_BIT;
    } else  // NOLINT(readability/braces)
#endif
    {
        return -1;
    }
}

template <typename _Tp, typename _RawTp = remove_cvref_t<_Tp>>
[[nodiscard]] CANN_ASC_STL_API constexpr int __num_bits_impl() noexcept
{
    if constexpr (is_arithmetic_v<_RawTp> || is_pointer_v<_RawTp>) {
        return __num_bits_of_basic<_RawTp>();
    } else if constexpr (has_unique_object_representations_v<_RawTp>) {
        const int __narrow = __num_bits_of_fp8_and_qlike<_RawTp>();
        if (__narrow > 0) {
            return __narrow;
        }
        const int __half_width = __num_bits_of_16bit<_RawTp>();
        if (__half_width > 0) {
            return __half_width;
        }
        return sizeof(_RawTp) * CHAR_BIT;
    } else {
        static_assert(__always_false_v<_Tp>, "unsupported type");
        return 0;
    }
}

template <typename _Tp>
inline constexpr int __num_bits_helper_v = __num_bits_impl<_Tp>();

template <typename _Tp>
inline constexpr int __num_bits_helper_v<complex<_Tp>> = __num_bits_impl<_Tp>() * 2;

template <typename _Tp>
inline constexpr int __num_bits_v = __num_bits_helper_v<remove_cvref_t<_Tp>>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_NUM_BITS_H
