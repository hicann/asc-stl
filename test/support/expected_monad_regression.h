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

#include "vocabulary_copy_test.h"

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

template <class T>
using value_wrapper = asc::std::expected<T, int>;
template <class E>
using error_wrapper = asc::std::expected<int, E>;
static_assert(asc_stl_copy_test::check_traits<value_wrapper>());
static_assert(asc_stl_copy_test::check_traits<error_wrapper>());

CANN_ASC_STL_API int evaluate_expected_copy(int input)
{
    using asc_stl_copy_test::payload;
    using expected = asc::std::expected<payload, payload>;
    asc_stl_copy_test::counts calls;
    int failures = 0;
    {
        const expected value(asc::std::in_place, calls, input);
        const expected error(asc::std::unexpect, calls, input + 1);
        expected from_value(value);
        expected from_error(error);
        failures += !from_value || from_value->value != input || from_error || from_error.error().value != input + 1;
        from_value = value;
        from_error = error;
        from_value = error;
        from_error = value;
        failures += from_value || from_value.error().value != input + 1 || !from_error || from_error->value != input;
        failures += calls.live != 4;
    }
    using move_expected = asc::std::expected<asc_stl_copy_test::move_only, asc_stl_copy_test::move_only>;
    move_expected move_source(asc::std::in_place, input);
    move_expected moved(asc::std::move(move_source));
    failures += !moved || moved->value != input;
    move_expected move_error(asc::std::unexpect, input + 1);
    moved = asc::std::move(move_error);  // NOLINT(build/include_what_you_use)
    failures += moved || moved.error().value != input + 1;
    return failures + (calls.live != 0 || calls.copies != 4 || calls.assignments != 2);
}

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
    return failures + evaluate_expected_copy(17);
}

}  // namespace asc_stl_expected_monad_test

#endif  // ASC_STL_TEST_SUPPORT_EXPECTED_MONAD_REGRESSION_H
