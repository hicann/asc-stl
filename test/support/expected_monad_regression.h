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

#ifndef ASC_STL_TEST_SUPPORT_EXPECTED_MONAD_REGRESSION_H
#define ASC_STL_TEST_SUPPORT_EXPECTED_MONAD_REGRESSION_H

#include <asc/std/expected>
#include <asc/std/utility>

namespace asc_stl_expected_monad_test {

struct value_probe {
    int value;
    CANN_ASC_STL_API explicit value_probe(int input) noexcept : value(input)
    {}
    CANN_ASC_STL_API value_probe(const value_probe& other) noexcept : value(other.value)
    {}
    CANN_ASC_STL_API value_probe(value_probe&& other) noexcept : value(other.value)
    {
        other.value = -1;
    }
};

struct recover_error {
    int* calls;
    CANN_ASC_STL_API asc::std::expected<value_probe, long> operator()(int& error) const noexcept
    {
        ++*calls;
        return asc::std::unexpected<long>(error + 1);
    }
};

struct convert_error {
    int* calls;
    CANN_ASC_STL_API long operator()(int& error) const noexcept
    {
        ++*calls;
        return error + 2;
    }
};

CANN_ASC_STL_API unsigned int evaluate()
{
    int calls = 0;
    asc::std::expected<value_probe, int> source(asc::std::in_place, 7);
    auto recovered = source.or_else(recover_error{&calls});
    unsigned int failures = !recovered || recovered->value != 7 || source->value != 7 || calls != 0;
    auto transformed = source.transform_error(convert_error{&calls});
    failures += !transformed || transformed->value != 7 || source->value != 7 || calls != 0;
    asc::std::expected<value_probe, int> error(asc::std::unexpect, 3);
    auto recovered_error = error.or_else(recover_error{&calls});
    failures += recovered_error.has_value() || recovered_error.error() != 4 || error.error() != 3 || calls != 1;
    auto transformed_error = error.transform_error(convert_error{&calls});
    failures += transformed_error.has_value() || transformed_error.error() != 5 || error.error() != 3 || calls != 2;
    return failures;
}

}  // namespace asc_stl_expected_monad_test

#endif  // ASC_STL_TEST_SUPPORT_EXPECTED_MONAD_REGRESSION_H
