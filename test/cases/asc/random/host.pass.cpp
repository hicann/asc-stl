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

#include <asc/random>
#include <asc/std/expected>
#if __cplusplus >= 202002L
#include <random>
static_assert(std::uniform_random_bit_generator<asc::pcg64>);
#endif
#include "../../../support/random_semantics.h"

struct tracker {
    int value;
    constexpr explicit tracker(int input = 0) noexcept : value(input)
    {}
    constexpr tracker(const tracker&) noexcept = default;
    constexpr tracker& operator=(const tracker&) noexcept = default;
    ~tracker() = default;
};

int main()
{
    if (!asc_stl_random_test::state_contracts() || !asc_stl_random_test::large_discard())
        return 10;
    for (unsigned i = 0; i != 128; ++i) {
        if (!asc_stl_random_test::composition(i) || !asc_stl_random_test::short_discard(i, i))
            return 11;
    }
    asc::pcg64 engine;
    unsigned long long value = 0;
    for (int index = 0; index < 10000; ++index)
        value = engine();
    if (value != 11135645891219275043ULL)
        return 1;
    asc::pcg64 advanced;
    asc::pcg64 stepped;
    advanced.discard(127);
    for (int index = 0; index < 127; ++index)
        stepped();
    if (advanced != stepped || asc::pcg64::min() != 0 || asc::pcg64::max() != ~0ULL)
        return 2;
    asc::std::expected<tracker, int> result(tracker{7});
    if (!result || result->value != 7 || (*result).value != 7)
        return 4;
    asc::std::expected<tracker, int> error(asc::std::unexpect, 5);
    if (error || error.error() != 5 || error.value_or(tracker{9}).value != 9)
        return 5;
    auto transformed = result.transform([](const tracker& item) noexcept { return item.value + 1; });
    if (!transformed || *transformed != 8)
        return 6;
    return 0;
}
