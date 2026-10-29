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

#ifndef ASC_STL_TEST_COMPARISON_HELPERS_SEMANTICS_H
#define ASC_STL_TEST_COMPARISON_HELPERS_SEMANTICS_H

#include <asc/std/compare>

namespace asc_stl_comparison_helpers_test {

template <class Ordering>
CANN_ASC_STL_API constexpr unsigned int predicate_mask(Ordering value) noexcept
{
    return (asc::std::is_eq(value) ? 1U : 0U) | (asc::std::is_neq(value) ? 2U : 0U) |
        (asc::std::is_lt(value) ? 4U : 0U) | (asc::std::is_lteq(value) ? 8U : 0U) |
        (asc::std::is_gt(value) ? 16U : 0U) | (asc::std::is_gteq(value) ? 32U : 0U);
}

CANN_ASC_STL_API constexpr unsigned int observe_case(unsigned int index, signed char value) noexcept
{
    if (index < 4) {
        return predicate_mask(asc::std::partial_ordering(value));
    }
    if (index < 7) {
        return predicate_mask(asc::std::weak_ordering(value));
    }
    return predicate_mask(asc::std::strong_ordering(value));
}

struct evaluation {
    unsigned int failures;
    unsigned int signature;
    unsigned int checks;
};

template <class InputPointer>
CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE evaluation evaluate(InputPointer input) noexcept
{
    // Bits name eq, neq, lt, lteq, gt, gteq. These are independent truth-table goldens.
    const unsigned int expected[11] = {14, 41, 50, 2, 14, 41, 50, 14, 41, 41, 50};
    evaluation result{0, 0, 0};
    for (unsigned int position = 0; position < 11; ++position) {
        // The caller supplies encoded -1/0/1/2 values at runtime. Do not select
        // a named constant in a switch: that would fold each helper to a literal.
        const unsigned int encoded = input[position];
        if (encoded > 3 || (position >= 4 && encoded > 2)) {
            ++result.failures;
            continue;
        }
        const auto value = static_cast<signed char>(static_cast<int>(encoded) - 1);
        const unsigned int actual = observe_case(position, value);
        result.failures += actual != expected[position];
        result.signature += actual;
        result.checks += 6;
    }
    return result;
}

}  // namespace asc_stl_comparison_helpers_test

#endif  // ASC_STL_TEST_COMPARISON_HELPERS_SEMANTICS_H
