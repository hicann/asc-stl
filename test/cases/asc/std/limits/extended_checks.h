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

#ifndef ASC_STL_TEST_LIMITS_EXTENDED_CHECKS_H
#define ASC_STL_TEST_LIMITS_EXTENDED_CHECKS_H

#include <asc/std/__floating_point/storage.h>
#include <asc/std/limits>
#include <asc/std/type_traits>

namespace asc_stl_test_limits {

// The exponents are those of the smallest and largest representable powers of two.
// numeric_limits counts one past that exponent for its radix-two bounds.
template <class T, class Bits, unsigned Fraction, int LeastPower, int GreatestPower, int MinDecimal, int MaxDecimal,
    bool Signed, bool Infinity, bool Iec>
CANN_ASC_STL_API bool check_format(int seed, unsigned min_bits, unsigned max_bits, unsigned epsilon_bits,
    unsigned round_bits, unsigned infinity_bits, unsigned quiet_bits, unsigned signaling_bits)
{
    namespace s = ::asc::std;
    using l = s::numeric_limits<T>;
    static_assert(s::is_same_v<typename l::type, T>);
    static_assert(l::is_specialized && l::is_bounded && !l::is_integer && !l::is_exact && !l::is_modulo);
    static_assert(l::radix == 2 && l::digits == Fraction + 1 && l::is_signed == Signed);
    static_assert(l::min_exponent == LeastPower + 1 && l::max_exponent == GreatestPower + 1);
    static_assert(l::min_exponent10 == MinDecimal && l::max_exponent10 == MaxDecimal);
    static_assert(
        l::digits10 == (Fraction * 30103 / 100000) && l::max_digits10 == 2 + ((Fraction + 1) * 30103 / 100000));
    static_assert(l::has_infinity == Infinity && l::has_quiet_NaN && l::has_signaling_NaN == Infinity);
    static_assert(l::is_iec559 == Iec && !l::traps && !l::has_denorm_loss && !l::tinyness_before);
    static_assert(l::has_denorm == (Signed ? s::denorm_present : s::denorm_absent));
    static_assert(l::round_style == (Signed ? s::round_to_nearest : s::round_toward_zero));
    const auto raw = [](T x) -> unsigned { return s::__fp_get_storage(x); };
    const unsigned sign = 1U << (8 * sizeof(Bits) - 1);
    return raw(l::min()) == min_bits + static_cast<unsigned>(seed - 7) && raw(l::max()) == max_bits &&
        raw(l::lowest()) == (Signed ? max_bits | sign : min_bits) && raw(l::epsilon()) == epsilon_bits &&
        raw(l::round_error()) == round_bits && raw(l::denorm_min()) == (Signed ? 1U : min_bits) &&
        raw(l::infinity()) == infinity_bits && raw(l::quiet_NaN()) == quiet_bits &&
        raw(l::signaling_NaN()) == signaling_bits;
}

CANN_ASC_STL_API int extended_limits(int seed)
{
#if CANN_ASC_STL_DETAIL_HAS_HALF()
    if (!check_format<half, unsigned short, 10, -14, 15, -4, 4, true, true, true>(
            seed, 0x0400U, 0x7bffU, 0x1400U, 0x3800U, 0x7c00U, 0x7e00U, 0x7d00U))
        return 2;
#endif
#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
    if (!check_format<bfloat16_t, unsigned short, 7, -126, 127, -37, 38, true, true, true>(
            seed, 0x0080U, 0x7f7fU, 0x3c00U, 0x3f00U, 0x7f80U, 0x7fc0U, 0x7fa0U))
        return 3;
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
    if (!check_format<float8_e4m3_t, unsigned char, 3, -6, 8, -1, 2, true, false, false>(
            seed, 0x08U, 0x7eU, 0x20U, 0x30U, 0U, 0x7fU, 0U))
        return 4;
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
    if (!check_format<float8_e5m2_t, unsigned char, 2, -14, 15, -4, 4, true, true, false>(
            seed, 0x04U, 0x7bU, 0x34U, 0x38U, 0x7cU, 0x7eU, 0x7dU))
        return 5;
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
    if (!check_format<float8_e8m0_t, unsigned char, 0, -127, 127, -38, 38, false, false, false>(
            seed, 0, 0xfeU, 0x7fU, 0x7fU, 0, 0xffU, 0))
        return 6;
#endif
    return static_cast<int>(seed != 7);
}
}  // namespace asc_stl_test_limits

#endif  // ASC_STL_TEST_LIMITS_EXTENDED_CHECKS_H
