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

#include <iostream>

#include "support/bit_contracts.h"

namespace {

template <class T>
unsigned check_pattern(T destination, T source, unsigned long long& windows)
{
    constexpr int bits = bit_test::digits<T>;
    unsigned failures = (asc::bit_reverse(destination) != bit_test::reference_reverse(destination)) +
        (asc::bit_reverse(asc::bit_reverse(destination)) != destination);
    for (int start = 0; start <= bits; ++start) {
        for (int width = 0; width <= bits - start; ++width) {
            failures += bit_test::check_window(destination, source, start, width);
            ++windows;
        }
    }
    const int limits[] = {INT_MIN, INT_MIN + 1, -bits - 1, -1, 0, 1, bits - 1, bits, bits + 1, INT_MAX - 1, INT_MAX};
    for (int start : limits) {
        for (int width : limits) {
            // Volatile reads also exercise the runtime path with constant inputs.
            volatile int runtime_start = start;
            volatile int runtime_width = width;
            failures += bit_test::check_window(destination, source, runtime_start, runtime_width);
            ++windows;
        }
    }
    return failures;
}

template <class T>
unsigned check_type(unsigned long long& windows)
{
    constexpr unsigned long long patterns[] = {0, 1, 0xFFFFFFFFFFFFFFFFULL, 0xAAAAAAAAAAAAAAAAULL,
        0x5555555555555555ULL, 0x0123456789ABCDEFULL, 0xDEADBEEFA5A50000ULL, 0x8000000000000001ULL};
    unsigned failures = 0;
    for (auto pattern : patterns) {
        failures += check_pattern(static_cast<T>(pattern), static_cast<T>(~pattern ^ 0x1234567812345678ULL), windows);
    }
    for (int bit = 0; bit < bit_test::digits<T>; ++bit) {
        const T value = static_cast<T>(1ULL << bit);
        failures += check_pattern(value, static_cast<T>(~value), windows);
        failures += check_pattern(static_cast<T>(~value), value, windows);
    }
    return failures;
}

}  // namespace

int main()
{
    unsigned long long windows = 0;
    const unsigned failures = check_type<bit_test::u32>(windows) + check_type<bit_test::u64>(windows);
    std::cout << "bit windows=" << windows << " failures=" << failures << '\n';
    return failures == 0 ? 0 : 1;
}
