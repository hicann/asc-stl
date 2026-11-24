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

#include <asc/numeric>

#include <cstdlib>
#include <iostream>
#include <limits>
#include <random>
#include <tuple>
#include <type_traits>

#include "reference.h"
#include "support/numeric_contracts.h"

namespace {
std::size_t arithmetic_cases = 0;
std::size_t conversion_cases = 0;

void require(bool passed, const char* message)
{
    if (!passed) {
        std::cerr << message << " arithmetic=" << arithmetic_cases << " casts=" << conversion_cases << '\n';
        std::exit(1);
    }
}

template <class T>
void pair(T left, T right)
{
    for (unsigned operation = 0; operation != 4; ++operation) {
        const auto expected = numeric_reference::arithmetic(left, right, operation);
        const auto actual = numeric_test::call(left, right, operation);
        require(actual.value == expected.value && actual.failed == expected.failed, "object result mismatch");
        T output = T{9};
        require(numeric_test::call(left, right, output, operation) == expected.failed && output == expected.value,
            "reference result mismatch");
        T alias_left = left, alias_right = right;
        require(numeric_test::call(alias_left, right, alias_left, operation) == expected.failed &&
                alias_left == expected.value,
            "left alias mismatch");
        require(numeric_test::call(left, alias_right, alias_right, operation) == expected.failed &&
                alias_right == expected.value,
            "right alias mismatch");
        ++arithmetic_cases;
    }
}

template <class T>
void arithmetic()
{
    for (T left : numeric_reference::boundaries<T>())
        for (T right : numeric_reference::boundaries<T>())
            pair(left, right);
    if constexpr (std::numeric_limits<T>::digits <= 8) {
        for (int left = std::numeric_limits<T>::min(); left <= std::numeric_limits<T>::max(); ++left)
            for (int right = std::numeric_limits<T>::min(); right <= std::numeric_limits<T>::max(); ++right)
                pair(static_cast<T>(left), static_cast<T>(right));
    } else {
        std::mt19937_64 engine(0x9120261123ULL);
        for (unsigned i = 0; i != 4096; ++i)
            pair(numeric_reference::random_value<T>(engine), numeric_reference::random_value<T>(engine));
    }
}

template <class To, class From>
void conversions()
{
    std::mt19937_64 engine(0x91ca57ULL);
    auto values = numeric_reference::boundaries<From>();
    const numeric_reference::wide low = std::numeric_limits<To>::min();
    const numeric_reference::wide high = std::numeric_limits<To>::max();
    for (auto edge : {low - 1, low, low + 1, high - 1, high, high + 1}) {
        if (edge >= static_cast<numeric_reference::wide>(std::numeric_limits<From>::min()) &&
            edge <= static_cast<numeric_reference::wide>(std::numeric_limits<From>::max()))
            values.push_back(static_cast<From>(edge));
    }
    for (unsigned i = 0; i != 1024; ++i)
        values.push_back(numeric_reference::random_value<From>(engine));
    for (From value : values) {
        const auto expected = numeric_reference::cast<To>(value);
        const auto actual = asc::overflow_cast<To>(value);
        require(actual.value == expected.value && actual.failed == expected.failed, "conversion mismatch");
        ++conversion_cases;
    }
}

using integers = std::tuple<signed char, unsigned char, short, unsigned short, int, unsigned int, long, unsigned long,
    long long, unsigned long long>;

template <class From, std::size_t... Index>
void destinations(std::index_sequence<Index...>)
{
    (conversions<std::tuple_element_t<Index, integers>, From>(), ...);
}

template <std::size_t... Index>
void all_types(std::index_sequence<Index...> indices)
{
    (arithmetic<std::tuple_element_t<Index, integers>>(), ...);
    (destinations<std::tuple_element_t<Index, integers>>(indices), ...);
}
}  // namespace

int main()
{
    auto [value, failed] = asc::add_overflow(2, 3);
    require(value == 5 && !failed, "structured binding mismatch");
    all_types(std::make_index_sequence<10>{});
    pair(0xffffffffULL, 0x100000001ULL);
    pair(0x100000001ULL, 0xffffffffULL);
    pair(0xffffffffULL, 0x100000002ULL);
    pair(0x100000000ULL, 0x100000000ULL);
    pair(0x8000000000000000ULL, 2ULL);
    pair(-0x100000000LL, 0x80000000LL);
    pair(0x100000000LL, 0x7fffffffLL);
    pair(-0xffffffffLL, 0x80000001LL);
    std::cout << "numeric exact arithmetic cases=" << arithmetic_cases << " casts=" << conversion_cases << '\n';
    return 0;
}
