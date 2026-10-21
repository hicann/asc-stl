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

#ifndef ASC_STL_TEST_FLOATING_STORAGE_SEMANTICS_H
#define ASC_STL_TEST_FLOATING_STORAGE_SEMANTICS_H

#include <asc/std/cmath>
#include <asc/std/type_traits>

namespace asc_stl_floating_storage_test {

template <class T>
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned check_format(
    unsigned one, unsigned two, unsigned low_pattern, unsigned other_pattern)
{
    using storage = asc::std::__fp_storage_of_t<T>;
    // Numeric values and bit patterns are independent goldens. The remaining
    // patterns pass through volatile storage so the native union path must
    // materialize their representation rather than fold an immediate cast.
    volatile storage one_bits = static_cast<storage>(one);
    const T encoded_one = asc::std::__fp_from_storage<T>(static_cast<storage>(one_bits));
    unsigned failures = asc::std::__fp_cast<float>(encoded_one) != 1.0F ||
            asc::std::__fp_get_storage(asc::std::__fp_cast<T>(1.0F)) != one ?
        1U :
        0U;
    volatile storage materialized = static_cast<storage>(two);
    const T decoded = asc::std::__fp_from_storage<T>(static_cast<storage>(materialized));
    failures |= asc::std::__fp_cast<float>(decoded) != 2.0F ? 2U : 0U;
    materialized = static_cast<storage>(low_pattern);
    const T low = asc::std::__fp_from_storage<T>(static_cast<storage>(materialized));
    failures |= asc::std::__fp_get_storage(low) != low_pattern ? 4U : 0U;
    materialized = static_cast<storage>(other_pattern);
    const T other = asc::std::__fp_from_storage<T>(static_cast<storage>(materialized));
    failures |= asc::std::__fp_get_storage(other) != other_pattern ? 8U : 0U;
    return failures;
}

template <class T>
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned signed_bits(unsigned one, unsigned sign, unsigned nan)
{
    using storage = asc::std::__fp_storage_of_t<T>;
    const T positive = asc::std::__fp_from_storage<T>(static_cast<storage>(one));
    const T negative_zero = asc::std::__fp_from_storage<T>(static_cast<storage>(sign));
    const T positive_nan = asc::std::__fp_from_storage<T>(static_cast<storage>(nan));
    const T negative_nan = asc::std::__fp_from_storage<T>(static_cast<storage>(nan | sign));
    static_assert(asc::std::is_same_v<decltype(asc::std::fabs(positive)), T>);
    static_assert(asc::std::is_same_v<decltype(asc::std::copysign(positive, negative_zero)), T>);
    unsigned failures = asc::std::__fp_get_storage(asc::std::fabs(negative_zero)) != 0 ? 1U : 0U;
    failures |= asc::std::__fp_get_storage(asc::std::copysign(positive, negative_zero)) != (one | sign) ? 2U : 0U;
    failures |= asc::std::__fp_get_storage(asc::std::fabs(negative_nan)) != nan ? 4U : 0U;
    failures |= asc::std::__fp_get_storage(asc::std::copysign(positive_nan, negative_zero)) != (nan | sign) ? 8U : 0U;
    failures |= !asc::std::signbit(negative_zero) || asc::std::signbit(positive) ? 16U : 0U;
    failures |= !asc::std::isnan(positive_nan) || asc::std::isfinite(negative_nan) || asc::std::isinf(positive_nan) ||
            asc::std::fpclassify(negative_nan) != 0 ?
        32U :
        0U;
    return failures;
}

template <class T>
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned format_constants(
    unsigned minimum, unsigned maximum, unsigned lowest, unsigned one)
{
    unsigned failures = asc::std::__fp_get_storage(asc::std::__fp_min<T>()) != minimum;
    failures += asc::std::__fp_get_storage(asc::std::__fp_max<T>()) != maximum;
    failures += asc::std::__fp_get_storage(asc::std::__fp_lowest<T>()) != lowest;
    failures += asc::std::__fp_get_storage(asc::std::__fp_one<T>()) != one;
    return failures;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned e8m0_codec_boundaries()
{
    using asc::std::__fp_get_storage;
    using asc::std::__detail::__e8m0_decode;
    using asc::std::__detail::__e8m0_encode;
    unsigned failures = __fp_get_storage(__e8m0_decode(0x00u)) != 0x00400000U;
    failures += __fp_get_storage(__e8m0_decode(0x01u)) != 0x00800000U;
    failures += __fp_get_storage(__e8m0_decode(0x7eu)) != 0x3f000000U;
    failures += __fp_get_storage(__e8m0_decode(0x7fu)) != 0x3f800000U;
    failures += __fp_get_storage(__e8m0_decode(0x80u)) != 0x40000000U;
    failures += __fp_get_storage(__e8m0_decode(0xfeu)) != 0x7f000000U;
    failures += (__fp_get_storage(__e8m0_decode(0xffu)) & 0x7fffffffU) <= 0x7f800000U;
    failures += __e8m0_encode(asc::std::bit_cast<float>(0x00400000U)) != 0x00u;
    failures += __e8m0_encode(asc::std::bit_cast<float>(0x00800000U)) != 0x01u;
    failures += __e8m0_encode(1.0F) != 0x7fu || __e8m0_encode(2.0F) != 0x80u;
    failures += __e8m0_encode(asc::std::bit_cast<float>(0x7f000000U)) != 0xfeu;
    return failures;
}

#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned e8m0_storage_boundaries()
{
    using T = float8_e8m0_t;
    const T minimum = asc::std::__fp_from_storage<T>(asc::std::uint8_t{0x00u});
    const T next = asc::std::__fp_from_storage<T>(asc::std::uint8_t{0x01u});
    const T nan = asc::std::__fp_from_storage<T>(asc::std::uint8_t{0xffu});
    static_assert(asc::std::is_same_v<decltype(asc::std::fabs(minimum)), T>);
    static_assert(asc::std::is_same_v<decltype(asc::std::copysign(minimum, nan)), T>);
    unsigned failures = asc::std::fpclassify(minimum) != 4 || !asc::std::isnormal(minimum) ||
        !asc::std::isfinite(minimum) || asc::std::isnan(minimum) || asc::std::isinf(minimum);
    failures += asc::std::__fp_get_storage(asc::std::__fp_cast<float>(minimum)) != 0x00400000U;
    failures += asc::std::__fp_get_storage(asc::std::__fp_cast<float>(next)) != 0x00800000U;
    failures += asc::std::fpclassify(nan) != 0 || !asc::std::isnan(nan) || asc::std::isfinite(nan) ||
        asc::std::isnormal(nan) || asc::std::isinf(nan);
    failures += asc::std::__fp_get_storage(asc::std::__fp_nan<T>()) != 0xffu;
    failures += asc::std::__fp_get_storage(asc::std::fabs(minimum)) != 0x00u;
    failures += asc::std::__fp_get_storage(asc::std::copysign(minimum, nan)) != 0x00u;
    failures += asc::std::signbit(minimum) || asc::std::signbit(nan);
    return failures;
}
#endif

CANN_ASC_STL_DEVICE_API CANN_ASC_STL_DETAIL_NO_INLINE unsigned evaluate()
{
    static_assert(asc::std::__fp_has_nan_v<asc::std::__fp_format::__fp8_e4m3>);
    static_assert(asc::std::__fp_has_nan_v<asc::std::__fp_format::__fp8_e8m0>);
    static_assert(!asc::std::__fp_has_nans_v<asc::std::__fp_format::__fp8_e4m3>);
    static_assert(!asc::std::__fp_has_nans_v<asc::std::__fp_format::__fp8_e8m0>);
    static_assert(asc::std::__fp_max<asc::std::__fp_format::__fp8_e4m3>() == 0x7eu);
    static_assert(asc::std::__fp_lowest<asc::std::__fp_format::__fp8_e4m3>() == 0xfeu);
    static_assert(asc::std::__fp_min<asc::std::__fp_format::__fp8_e8m0>() == 0x00u);
    static_assert(asc::std::__fp_max<asc::std::__fp_format::__fp8_e8m0>() == 0xfeu);
    static_assert(asc::std::__fp_lowest<asc::std::__fp_format::__fp8_e8m0>() == 0x00u);
    static_assert(asc::std::__fp_nan<asc::std::__fp_format::__fp8_e4m3>() == 0x7fu);
    static_assert(asc::std::__fp_nan<asc::std::__fp_format::__fp8_e8m0>() == 0xffu);
    unsigned failures = check_format<float>(0x3f800000U, 0x40000000U, 0x1U, 0x80000000U);
    failures |= signed_bits<float>(0x3f800000U, 0x80000000U, 0x7fc12345U) ? (1U << 24) : 0U;
    failures |= e8m0_codec_boundaries() ? (1U << 25) : 0U;
#if CANN_ASC_STL_DETAIL_HAS_HALF()
    failures |= check_format<half>(0x3c00U, 0x4000U, 0x1U, 0x8000U) << 4;
    failures |= format_constants<half>(0x0400U, 0x7bffU, 0xfbffU, 0x3c00U) ? (1U << 28) : 0U;
    failures |= signed_bits<half>(0x3c00U, 0x8000U, 0x7e15U) ? (1U << 26) : 0U;
#endif
#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
    failures |= check_format<bfloat16_t>(0x3f80U, 0x4000U, 0x1U, 0x8000U) << 8;
    failures |= format_constants<bfloat16_t>(0x0080U, 0x7f7fU, 0xff7fU, 0x3f80U) ? (1U << 28) : 0U;
    failures |= signed_bits<bfloat16_t>(0x3f80U, 0x8000U, 0x7fc5U) ? (1U << 26) : 0U;
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
    failures |= check_format<float8_e4m3_t>(0x38U, 0x40U, 0x1U, 0x80U) << 12;
    failures |= format_constants<float8_e4m3_t>(0x08U, 0x7eU, 0xfeU, 0x38U) ? (1U << 28) : 0U;
    failures |= signed_bits<float8_e4m3_t>(0x38U, 0x80U, 0x7fU) ? (1U << 26) : 0U;
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
    failures |= check_format<float8_e5m2_t>(0x3cU, 0x40U, 0x1U, 0x80U) << 16;
    failures |= format_constants<float8_e5m2_t>(0x04U, 0x7bU, 0xfbU, 0x3cU) ? (1U << 28) : 0U;
    failures |= signed_bits<float8_e5m2_t>(0x3cU, 0x80U, 0x7fU) ? (1U << 26) : 0U;
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
    // E8M0 has no signed zero: use a large finite exponent as its fourth case.
    failures |= check_format<float8_e8m0_t>(0x7fU, 0x80U, 0x1U, 0xfeU) << 20;
    failures |= format_constants<float8_e8m0_t>(0x00U, 0xfeU, 0x00U, 0x7fU) ? (1U << 28) : 0U;
    failures |= e8m0_storage_boundaries() ? (1U << 27) : 0U;
#endif
    return failures;
}

}  // namespace asc_stl_floating_storage_test

#endif  // ASC_STL_TEST_FLOATING_STORAGE_SEMANTICS_H
