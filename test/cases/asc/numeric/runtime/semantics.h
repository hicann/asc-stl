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

#ifndef ASC_STL_TEST_NUMERIC_RUNTIME_SEMANTICS_H
#define ASC_STL_TEST_NUMERIC_RUNTIME_SEMANTICS_H

#include "../../../../support/numeric_contracts.h"
#include "launch.h"

namespace numeric_runtime_test {
struct result {
    numeric_word value;
    bool failed;
    bool consistent;
};

template <class T>
CANN_ASC_STL_API T decode(numeric_word value)
{
    if constexpr (asc::std::numeric_limits<T>::is_signed) {
        constexpr T low = asc::std::numeric_limits<T>::min();
        constexpr T high = asc::std::numeric_limits<T>::max();
        if (value > static_cast<numeric_word>(high)) {
            return static_cast<T>(low + static_cast<T>(value - static_cast<numeric_word>(low)));
        }
    }
    return static_cast<T>(value);
}

template <class To, class From>
CANN_ASC_STL_API result convert(From value)
{
    const auto actual = asc::overflow_cast<To>(value);
    return {static_cast<numeric_word>(actual.value), actual.failed, true};
}

template <class T>
CANN_ASC_STL_API result destination(T value, unsigned type)
{
    switch (type) {
        case 0:
            return convert<signed char>(value);
        case 1:
            return convert<unsigned char>(value);
        case 2:
            return convert<short>(value);
        case 3:
            return convert<unsigned short>(value);
        case 4:
            return convert<int>(value);
        case 5:
            return convert<unsigned int>(value);
        case 6:
            return convert<long>(value);
        case 7:
            return convert<unsigned long>(value);
        case 8:
            return convert<long long>(value);
        default:
            return convert<unsigned long long>(value);
    }
}

template <class T>
CANN_ASC_STL_API result evaluate(unsigned operation, numeric_word raw_left, numeric_word raw_right, unsigned to)
{
    const T left = decode<T>(raw_left), right = decode<T>(raw_right);
    if (operation == 4)
        return destination(left, to);
    const auto actual = numeric_test::call(left, right, operation);
    T value = T{9};
    const bool failed = numeric_test::call(left, right, value, operation);
    T alias_left = left, alias_right = right;
    const bool failed_left = numeric_test::call(alias_left, right, alias_left, operation);
    const bool failed_right = numeric_test::call(left, alias_right, alias_right, operation);
    const bool ordinary = value == actual.value && failed == actual.failed;
    const bool aliases = alias_left == value && alias_right == value && failed_left == failed && failed_right == failed;
    return {static_cast<numeric_word>(actual.value), actual.failed, ordinary && aliases};
}

CANN_ASC_STL_API result dispatch(unsigned type, unsigned operation, numeric_word left, numeric_word right, unsigned to)
{
    switch (type) {
        case 0:
            return evaluate<signed char>(operation, left, right, to);
        case 1:
            return evaluate<unsigned char>(operation, left, right, to);
        case 2:
            return evaluate<short>(operation, left, right, to);
        case 3:
            return evaluate<unsigned short>(operation, left, right, to);
        case 4:
            return evaluate<int>(operation, left, right, to);
        case 5:
            return evaluate<unsigned int>(operation, left, right, to);
        case 6:
            return evaluate<long>(operation, left, right, to);
        case 7:
            return evaluate<unsigned long>(operation, left, right, to);
        case 8:
            return evaluate<long long>(operation, left, right, to);
        default:
            return evaluate<unsigned long long>(operation, left, right, to);
    }
}
}  // namespace numeric_runtime_test

#endif  // ASC_STL_TEST_NUMERIC_RUNTIME_SEMANTICS_H
