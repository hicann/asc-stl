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

#ifndef ASC_STL_TEST_NUMERIC_DEVICE_CHECKS_H
#define ASC_STL_TEST_NUMERIC_DEVICE_CHECKS_H

#include <asc/std/numeric>
#include <asc/std/limits>

namespace asc_stl_test_numeric {
struct add {
    CANN_ASC_STL_API int operator()(int a, int b) const
    {
        return a + b;
    }
};
struct multiply {
    CANN_ASC_STL_API int operator()(int a, int b) const
    {
        return a * b;
    }
};
struct twice {
    CANN_ASC_STL_API int operator()(int a) const
    {
        return a * 2;
    }
};

enum class expected_sequence { sum, differences, neighboring_sum, previous_sum };

CANN_ASC_STL_API int expected_element(expected_sequence sequence, int index)
{
    if (sequence == expected_sequence::sum)
        return index * (index + 1);
    if (sequence == expected_sequence::previous_sum)
        return index * (index - 1);
    if (sequence == expected_sequence::differences)
        return index ? 2 : 0;
    return index ? 4 * index - 2 : 0;
}

CANN_ASC_STL_API int check(int seed, void* workspace)
{
    auto* a = static_cast<int*>(workspace);
    a[0] = 91;
    a[5] = 96;
    ::asc::std::iota(a + 1, a + 5, seed - 9);
    if (a[0] != 91 || a[1] != -2 || a[2] != -1 || a[3] != 0 || a[4] != 1 || a[5] != 96)
        return 1;
    int* b = a + 6;
    for (int i = 0; i < 4; ++i)
        b[i] = i * 2;
    if (::asc::std::accumulate(a + 1, a + 5, 5) != 3 || ::asc::std::accumulate(b + 1, b + 4, 1, multiply{}) != 48 ||
        ::asc::std::inner_product(a + 1, a + 5, b, 3) != 7 ||
        ::asc::std::inner_product(a + 1, a + 5, b, 3, add{}, add{}) != 13)
        return 2;
    if (::asc::std::reduce(a + 1, a + 5) != -2 || ::asc::std::reduce(a + 1, a + 5, 5) != 3 ||
        ::asc::std::reduce(b + 1, b + 4, 1, multiply{}) != 48 ||
        ::asc::std::transform_reduce(a + 1, a + 5, b, 3) != 7 ||
        ::asc::std::transform_reduce(a + 1, a + 5, b, 3, add{}, add{}) != 13 ||
        ::asc::std::transform_reduce(a + 1, a + 5, 3, add{}, twice{}) != -1)
        return 3;

    for (int n = 0; n <= 4; ++n) {
        int* out = b + 4;
        for (int i = 0; i < 5; ++i)
            out[i] = 111;
        auto verify = [&](int* result, expected_sequence oracle, int scale, int offset) {
            if (result != out + n || out[n] != 111)
                return false;
            for (int i = 0; i < n; ++i) {
                if (out[i] != expected_element(oracle, i) * scale + offset)
                    return false;
                out[i] = 111;
            }
            return true;
        };
        if (!verify(::asc::std::adjacent_difference(b, b + n, out), expected_sequence::differences, 1, 0) ||
            !verify(::asc::std::adjacent_difference(b, b + n, out, add{}), expected_sequence::neighboring_sum, 1, 0) ||
            !verify(::asc::std::partial_sum(b, b + n, out), expected_sequence::sum, 1, 0) ||
            !verify(::asc::std::partial_sum(b, b + n, out, add{}), expected_sequence::sum, 1, 0))
            return 4;
        if (!verify(::asc::std::exclusive_scan(b, b + n, out, 3), expected_sequence::previous_sum, 1, 3) ||
            !verify(::asc::std::exclusive_scan(b, b + n, out, 3, add{}), expected_sequence::previous_sum, 1, 3) ||
            !verify(::asc::std::inclusive_scan(b, b + n, out), expected_sequence::sum, 1, 0) ||
            !verify(::asc::std::inclusive_scan(b, b + n, out, add{}), expected_sequence::sum, 1, 0) ||
            !verify(::asc::std::inclusive_scan(b, b + n, out, add{}, 3), expected_sequence::sum, 1, 3) ||
            !verify(::asc::std::transform_exclusive_scan(b, b + n, out, 3, add{}, twice{}),
                expected_sequence::previous_sum, 2, 3) ||
            !verify(
                ::asc::std::transform_inclusive_scan(b, b + n, out, add{}, twice{}), expected_sequence::sum, 2, 0) ||
            !verify(
                ::asc::std::transform_inclusive_scan(b, b + n, out, add{}, twice{}, 3), expected_sequence::sum, 2, 3))
            return 5;
    }
    const int lo = ::asc::std::numeric_limits<int>::min();
    const int hi = ::asc::std::numeric_limits<int>::max();
    if (::asc::std::midpoint(lo, hi) != -1 || ::asc::std::midpoint(hi, lo) != 0 ||
        ::asc::std::midpoint(b, b + 3) != b + 1 || ::asc::std::midpoint(b + 3, b) != b + 2 ||
        ::asc::std::midpoint(-4.0F, 2.0F) != -1.0F || ::asc::std::gcd(-12, 18) != 6 || ::asc::std::gcd(0, 0) != 0 ||
        ::asc::std::lcm(-12, 18) != 36 || ::asc::std::lcm(0, -12) != 0)
        return 6;
    if (::asc::std::saturating_add(hi, 1) != hi || ::asc::std::saturating_sub(lo, 1) != lo ||
        ::asc::std::saturating_mul(lo, -2) != hi || ::asc::std::saturating_div(lo, -1) != hi ||
        ::asc::std::saturating_cast<unsigned char>(-1) != 0 || ::asc::std::saturating_cast<signed char>(500) != 127)
        return 7;
    return 0;
}
}  // namespace asc_stl_test_numeric

#endif  // ASC_STL_TEST_NUMERIC_DEVICE_CHECKS_H
