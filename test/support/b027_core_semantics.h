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

#ifndef ASC_STL_TEST_B027_CORE_SEMANTICS_H
#define ASC_STL_TEST_B027_CORE_SEMANTICS_H
#include <asc/std/__functional/default_searcher.h>
#include <asc/std/__numeric/gcd_lcm.h>
#include <asc/std/__numeric/midpoint.h>
#include <asc/std/bitset>
#include <asc/std/inplace_vector>

#include "vector_aliasing_semantics.h"
namespace asc_stl_b027_core_test {
CANN_ASC_STL_API int evaluate_inplace_search()
{
    asc::std::inplace_vector<int, 4> values;
    values.unchecked_push_back(3);
    values.unchecked_push_back(5);
    if (values.size() != 2 || values.front() != 3 || values.back() != 5)
        return 10;
    const int pattern[] = {5};
    asc::std::default_searcher<const int*> searcher(pattern, pattern + 1);
    const auto found = searcher(values.begin(), values.end());
    if (found.first != values.begin() + 1 || found.second != values.end())
        return 11;
    return 0;
}

CANN_ASC_STL_API int evaluate_numeric()
{
    if (asc::std::gcd(84, -30) != 6 || asc::std::lcm(21, 6) != 42)
        return 12;
    if (asc::std::midpoint(-5, 4) != -1)
        return 13;
    int pointer_values[6]{};
    if (asc::std::midpoint(pointer_values, pointer_values + 5) != pointer_values + 2)
        return 14;
    if (asc::std::midpoint(2.0f, 4.0f) != 3.0f)
        return 15;
    volatile float runtime_max = __FLT_MAX__;
    const float largest = runtime_max;
    if (asc::std::midpoint(largest, largest) != largest || asc::std::midpoint(-largest, -largest) != -largest ||
        asc::std::midpoint(-largest, largest) != 0.0F || asc::std::midpoint(largest, 0.0F) != largest / 2.0F)
        return 17;
    return 0;
}

CANN_ASC_STL_API int evaluate()
{
    asc::std::bitset<16> bits(0x1234u);
    if (bits.count() != 5 || !bits.any() || bits.none() || bits.all())
        return 1;
    bits <<= 4;
    if (bits.to_ulong() != 0x2340u)
        return 2;
    bits >>= 8;
    if (bits.to_ullong() != 0x23u)
        return 3;
    bits.flip();
    if (bits.count() != 13)
        return 4;
    const asc::std::bitset<16> mask(0x00ffu);
    if ((bits & mask).to_ulong() != 0xdcu)
        return 5;
    if ((bits | mask).count() != 16)
        return 6;
    if ((bits ^ mask).count() != 11)
        return 7;
    bits.reset();
    if (!bits.none())
        return 8;
    bits.set();
    if (!bits.all() || bits.size() != 16)
        return 9;

    const int inplace_result = evaluate_inplace_search();
    if (inplace_result != 0)
        return inplace_result;
    const int numeric_result = evaluate_numeric();
    if (numeric_result != 0)
        return numeric_result;
    if (asc::std::hash<asc::std::bitset<16>>{}(mask) == asc::std::hash<asc::std::bitset<16>>{}(bits))
        return 16;
    const int vector_result = asc_stl_vector_aliasing_test::evaluate();
    return vector_result == 0 ? 0 : 20 + vector_result;
}
}  // namespace asc_stl_b027_core_test
#endif  // ASC_STL_TEST_B027_CORE_SEMANTICS_H
