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

#ifndef CANN_ASC_STL_ASC_STD___FLOATING_POINT_DECOMPOSE_H
#define CANN_ASC_STL_ASC_STD___FLOATING_POINT_DECOMPOSE_H

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
#include <asc/std/__floating_point/mask.h>
#include <asc/std/__floating_point/properties.h>
#include <asc/std/__floating_point/storage.h>
#include <asc/std/climits>

CANN_ASC_STL_BEGIN_NAMESPACE

template <__fp_format Fmt>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr int __fp_get_exp_biased(__fp_storage_t<Fmt> value) noexcept
{
    static_assert(__fp_exp_nbits_v<Fmt> < static_cast<int>(sizeof(int) * CHAR_BIT));
    return static_cast<int>((value & __fp_exp_mask_v<Fmt>) >> __fp_mant_nbits_v<Fmt>);
}
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr int __fp_get_exp_biased(T value) noexcept
{
    return __fp_get_exp_biased<__fp_format_of_v<T>>(__fp_get_storage(value));
}
template <__fp_format Fmt>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr int __fp_get_exp(__fp_storage_t<Fmt> value) noexcept
{
    return __fp_get_exp_biased<Fmt>(value) - __fp_exp_bias_v<Fmt>;
}
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr int __fp_get_exp(T value) noexcept
{
    return __fp_get_exp<__fp_format_of_v<T>>(__fp_get_storage(value));
}
template <__fp_format Fmt>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr __fp_storage_t<Fmt> __fp_set_exp_biased(
    __fp_storage_t<Fmt> value, int exponent) noexcept
{
    using Storage = __fp_storage_t<Fmt>;
    auto result = static_cast<Storage>((value & __fp_inv_exp_mask_v<Fmt>) |
        ((static_cast<Storage>(exponent) << __fp_mant_nbits_v<Fmt>)&__fp_exp_mask_v<Fmt>));
    if constexpr (!__fp_has_implicit_bit_v<Fmt>) {
        result = exponent == 0 ? static_cast<Storage>(result & ~__fp_explicit_bit_mask_v<Fmt>) :
                                 static_cast<Storage>(result | __fp_explicit_bit_mask_v<Fmt>);
    }
    return result;
}
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr T __fp_set_exp_biased(T value, int exponent) noexcept
{
    return __fp_from_storage<T>(__fp_set_exp_biased<__fp_format_of_v<T>>(__fp_get_storage(value), exponent));
}
template <__fp_format Fmt>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr __fp_storage_t<Fmt> __fp_set_exp(
    __fp_storage_t<Fmt> value, int exponent) noexcept
{
    return __fp_set_exp_biased<Fmt>(value, exponent + __fp_exp_bias_v<Fmt>);
}
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr T __fp_set_exp(T value, int exponent) noexcept
{
    return __fp_from_storage<T>(__fp_set_exp<__fp_format_of_v<T>>(__fp_get_storage(value), exponent));
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FLOATING_POINT_DECOMPOSE_H
