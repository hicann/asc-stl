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

#ifndef CANN_ASC_STL_ASC_STD___FLOATING_POINT_CONSTANTS_H
#define CANN_ASC_STL_ASC_STD___FLOATING_POINT_CONSTANTS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__floating_point/arithmetic.h>
#include <asc/std/__floating_point/decompose.h>
#include <asc/std/__floating_point/format.h>
#include <asc/std/__floating_point/mask.h>
#include <asc/std/__floating_point/native_type.h>
#include <asc/std/__floating_point/properties.h>
#include <asc/std/__floating_point/storage.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <__fp_format Fmt>
CANN_ASC_STL_API constexpr __fp_storage_t<Fmt> __fp_inf() noexcept
{
    static_assert(__fp_has_inf_v<Fmt>);
    return static_cast<__fp_storage_t<Fmt>>(__fp_exp_mask_v<Fmt> | __fp_explicit_bit_mask_v<Fmt>);
}
template <class T>
CANN_ASC_STL_API constexpr T __fp_inf() noexcept
{
    if constexpr (__fp_is_native_type_v<T>) {
        return static_cast<T>(__builtin_huge_val());
    } else {
        return __fp_from_storage<T>(__fp_inf<__fp_format_of_v<T>>());
    }
}
template <__fp_format Fmt>
CANN_ASC_STL_API constexpr __fp_storage_t<Fmt> __fp_nan() noexcept
{
    using Storage = __fp_storage_t<Fmt>;
    return static_cast<Storage>(__fp_exp_mask_v<Fmt> | __fp_explicit_bit_mask_v<Fmt> |
        (Storage(1) << (__fp_mant_nbits_v<Fmt> - 1 - !__fp_has_implicit_bit_v<Fmt>)));
}
template <class T>
CANN_ASC_STL_API constexpr T __fp_nan() noexcept
{
    if constexpr (__fp_is_native_type_v<T>) {
        return static_cast<T>(__builtin_nan(""));
    } else {
        return __fp_from_storage<T>(__fp_nan<__fp_format_of_v<T>>());
    }
}
template <__fp_format Fmt>
CANN_ASC_STL_API constexpr __fp_storage_t<Fmt> __fp_nans() noexcept
{
    using Storage = __fp_storage_t<Fmt>;
    return static_cast<Storage>(__fp_exp_mask_v<Fmt> | __fp_explicit_bit_mask_v<Fmt> |
        (Storage(1) << (__fp_mant_nbits_v<Fmt> - 2 - !__fp_has_implicit_bit_v<Fmt>)));
}
template <class T>
CANN_ASC_STL_API constexpr T __fp_nans() noexcept
{
    return __fp_from_storage<T>(__fp_nans<__fp_format_of_v<T>>());
}
template <__fp_format Fmt>
CANN_ASC_STL_API constexpr __fp_storage_t<Fmt> __fp_max() noexcept
{
    return __fp_set_exp<Fmt>(__fp_mant_mask_v<Fmt>, __fp_exp_max_v<Fmt>);
}
template <class T>
CANN_ASC_STL_API constexpr T __fp_max() noexcept
{
    if constexpr (__fp_format_of_v<T> == __fp_format::__binary32)
        return static_cast<T>(0x1.fffffep+127f);
    if constexpr (__fp_format_of_v<T> == __fp_format::__binary64)
        return static_cast<T>(0x1.fffffffffffffp+1023);
    return __fp_from_storage<T>(__fp_max<__fp_format_of_v<T>>());
}
template <__fp_format Fmt>
CANN_ASC_STL_API constexpr __fp_storage_t<Fmt> __fp_min() noexcept
{
    return __fp_set_exp<Fmt>(__fp_storage_t<Fmt>{0}, __fp_exp_min_v<Fmt>);
}
template <class T>
CANN_ASC_STL_API constexpr T __fp_min() noexcept
{
    if constexpr (__fp_format_of_v<T> == __fp_format::__binary32)
        return static_cast<T>(0x1p-126f);
    if constexpr (__fp_format_of_v<T> == __fp_format::__binary64)
        return static_cast<T>(0x1p-1022);
    return __fp_from_storage<T>(__fp_min<__fp_format_of_v<T>>());
}
template <__fp_format Fmt>
CANN_ASC_STL_API constexpr __fp_storage_t<Fmt> __fp_denorm_min() noexcept
{
    return __fp_storage_t<Fmt>{1};
}
template <class T>
CANN_ASC_STL_API constexpr T __fp_denorm_min() noexcept
{
    return __fp_from_storage<T>(__fp_denorm_min<__fp_format_of_v<T>>());
}
template <__fp_format Fmt>
CANN_ASC_STL_API constexpr __fp_storage_t<Fmt> __fp_lowest() noexcept
{
    return __fp_neg<Fmt>(__fp_max<Fmt>());
}
template <class T>
CANN_ASC_STL_API constexpr T __fp_lowest() noexcept
{
    return __fp_neg(__fp_max<T>());
}
template <__fp_format Fmt>
CANN_ASC_STL_API constexpr __fp_storage_t<Fmt> __fp_zero() noexcept
{
    return __fp_storage_t<Fmt>{0};
}
template <class T>
CANN_ASC_STL_API constexpr T __fp_zero() noexcept
{
    return T{};
}
template <__fp_format Fmt>
CANN_ASC_STL_API constexpr __fp_storage_t<Fmt> __fp_one() noexcept
{
    return __fp_set_exp<Fmt>(__fp_storage_t<Fmt>{0}, 0);
}
template <class T>
CANN_ASC_STL_API constexpr T __fp_one() noexcept
{
    return T{1};
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FLOATING_POINT_CONSTANTS_H
