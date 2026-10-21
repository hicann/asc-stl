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

#ifndef ASC_STL_TEST_NUMERIC_MATH_REVIEW_SEMANTICS_H
#define ASC_STL_TEST_NUMERIC_MATH_REVIEW_SEMANTICS_H

#include <asc/std/cmath>
#include <asc/std/type_traits>

namespace asc_stl_numeric_math_review {

#if !CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
template <class T>
CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_NO_INLINE int neighbors(
    unsigned int one, unsigned int two, unsigned int up, unsigned int down)
{
    using storage = asc::std::__fp_storage_of_t<T>;
    const T a = asc::std::__fp_from_storage<T>(static_cast<storage>(one));
    const T b = asc::std::__fp_from_storage<T>(static_cast<storage>(two));
    const T lower = asc::std::__fp_from_storage<T>(static_cast<storage>(down));
    int failures = asc::std::__fp_get_storage(asc::std::nextafter(a, b)) != up;
    failures += asc::std::__fp_get_storage(asc::std::nextafter(a, lower)) != down;
    failures += asc::std::__fp_get_storage(asc::std::nextafter(a, a)) != one;
    static_assert(asc::std::is_same_v<decltype(asc::std::lrint(a)), long>);
    static_assert(asc::std::is_same_v<decltype(asc::std::lround(a)), long>);
    static_assert(asc::std::is_same_v<decltype(asc::std::llrint(a)), long long>);
    static_assert(asc::std::is_same_v<decltype(asc::std::llround(a)), long long>);
    failures += asc::std::lrint(a) != 1L || asc::std::llrint(a) != 1LL;
    failures += asc::std::lround(b) != 2L || asc::std::llround(b) != 2LL;
    return failures;
}

template <class T>
CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_NO_INLINE int public_functions(
    unsigned one, unsigned two, unsigned four, unsigned sine_one)
{
    using storage = asc::std::__fp_storage_of_t<T>;
    const T a = asc::std::__fp_from_storage<T>(static_cast<storage>(one));
    const T b = asc::std::__fp_from_storage<T>(static_cast<storage>(two));
    const T c = asc::std::__fp_from_storage<T>(static_cast<storage>(four));
    static_assert(asc::std::is_same_v<decltype(asc::std::sqrt(c)), T>);
    static_assert(asc::std::is_same_v<decltype(asc::std::sin(a)), T>);
    static_assert(asc::std::is_same_v<decltype(asc::std::ceil(a)), T>);
    static_assert(asc::std::is_same_v<decltype(asc::std::fmod(b, c)), T>);
    static_assert(asc::std::is_same_v<decltype(asc::std::remainder(b, c)), T>);
    static_assert(asc::std::is_same_v<decltype(asc::std::fma(a, a, a)), T>);
    int failures = asc::std::__fp_get_storage(asc::std::sqrt(c)) != two;
    failures += asc::std::__fp_get_storage(asc::std::sin(a)) != sine_one;
    failures += asc::std::__fp_get_storage(asc::std::ceil(a)) != one;
    failures += asc::std::__fp_get_storage(asc::std::fmod(b, c)) != two;
    failures += asc::std::__fp_get_storage(asc::std::remainder(b, c)) != two;
    failures += asc::std::__fp_get_storage(asc::std::fma(a, a, a)) != two;
    failures += !asc::std::isfinite(a) || !asc::std::isnormal(a) || asc::std::fpclassify(a) != 4;
    return failures;
}

CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_NO_INLINE int evaluate_float_cases()
{
    volatile float large = 3.0e38F;
    const float a = -large, b = large;
    int failures = asc::std::lerp(a, b, 0.5F) != 0.0F;
    failures += asc::std::lerp(a, b, 0.0F) != a || asc::std::lerp(a, b, 1.0F) != b;
    failures += asc::std::lerp(2.0F, 4.0F, 2.0F) != 6.0F;
    // remquo exposes at least three signed quotient bits; the backend may
    // preserve more. Use independent integer quotients and IEEE tie-to-even
    // remainders without assuming an exact backend quotient width.
    const float dividends[] = {90.0F, -90.0F, 9.0F, 11.0F};
    const float remainders[] = {0.0F, 0.0F, 1.0F, -1.0F};
    const unsigned int low_bits[] = {5U, 5U, 4U, 6U};
    for (unsigned int index = 0; index < 4U; ++index) {
        int quotient = 0;
        const float remainder = asc::std::remquo(dividends[index], 2.0F, &quotient);
        const unsigned int magnitude =
            quotient < 0 ? 0U - static_cast<unsigned int>(quotient) : static_cast<unsigned int>(quotient);
        failures += remainder != remainders[index] || (magnitude & 7U) != low_bits[index] ||
            (quotient < 0) != (dividends[index] < 0.0F);
    }
    float previous = a;
    for (int index = 0; index <= 8; ++index) {
        const float current = asc::std::lerp(a, b, static_cast<float>(index) / 8.0F);
        failures += !asc::std::isfinite(current) || current < previous;
        previous = current;
    }
    return failures;
}

#if CANN_ASC_STL_DETAIL_HAS_HALF()
CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_NO_INLINE int evaluate_half_cases()
{
    int failures = 0;
    failures += neighbors<half>(0x3c00U, 0x4000U, 0x3c01U, 0x3bffU);
    failures += public_functions<half>(0x3c00U, 0x4000U, 0x4400U, 0x3abbU);
    const half negative = asc::std::__fp_from_storage<half>(asc::std::uint16_t{0xbc00U});
    failures += asc::std::__fp_get_storage(asc::std::nextafter(
                    negative, asc::std::__fp_from_storage<half>(asc::std::uint16_t{0xc000U}))) != 0xbc01U;
    failures +=
        asc::std::__fp_get_storage(asc::std::nextafter(asc::std::__fp_from_storage<half>(asc::std::uint16_t{0x0000U}),
            asc::std::__fp_from_storage<half>(asc::std::uint16_t{0x8000U}))) != 0x8000U;
    failures += asc::std::__fp_get_storage(asc::std::nextafter(
                    asc::std::__fp_from_storage<half>(asc::std::uint16_t{0x0000U}), negative)) != 0x8001U;
    failures += asc::std::lround(asc::std::__fp_from_storage<half>(asc::std::uint16_t{0x4100U})) != 3L;
    failures += asc::std::llround(asc::std::__fp_from_storage<half>(asc::std::uint16_t{0xc100U})) != -3LL;
    return failures;
}
#endif

CANN_ASC_STL_HOST_SIMT_API CANN_ASC_STL_DETAIL_NO_INLINE int evaluate()
{
    int failures = evaluate_float_cases();
#if CANN_ASC_STL_DETAIL_HAS_HALF()
    failures += evaluate_half_cases();
#endif
#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
    failures += neighbors<bfloat16_t>(0x3f80U, 0x4000U, 0x3f81U, 0x3f7fU);
    failures += public_functions<bfloat16_t>(0x3f80U, 0x4000U, 0x4080U, 0x3f57U);
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3()
    failures += neighbors<float8_e4m3_t>(0x38U, 0x40U, 0x39U, 0x37U);
    failures += public_functions<float8_e4m3_t>(0x38U, 0x40U, 0x48U, 0x35U);
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2()
    failures += neighbors<float8_e5m2_t>(0x3cU, 0x40U, 0x3dU, 0x3bU);
    failures += public_functions<float8_e5m2_t>(0x3cU, 0x40U, 0x44U, 0x3bU);
#endif
#if CANN_ASC_STL_DETAIL_HAS_FP8_E8M0()
    failures += neighbors<float8_e8m0_t>(0x7fU, 0x80U, 0x80U, 0x7eU);
    failures += public_functions<float8_e8m0_t>(0x7fU, 0x80U, 0x81U, 0x7eU);
#endif
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
    static_assert(asc::std::is_same_v<decltype(asc::std::fabs(1.0L)), long double>);
    static_assert(asc::std::is_same_v<decltype(asc::std::copysign(1.0L, -1.0L)), long double>);
    volatile long double input = 1.0L + __LDBL_EPSILON__;
    const long double precise = input;
    failures += asc::std::fabs(-precise) != precise;
    failures += asc::std::copysign(precise, -1.0L) != -precise;
    failures += asc::std::fabsl(-__LDBL_MAX__) != __LDBL_MAX__;
    failures += asc::std::copysignl(__LDBL_MAX__, -1.0L) != -__LDBL_MAX__;
#endif
    return failures;
}
#endif

}  // namespace asc_stl_numeric_math_review

#endif  // ASC_STL_TEST_NUMERIC_MATH_REVIEW_SEMANTICS_H
