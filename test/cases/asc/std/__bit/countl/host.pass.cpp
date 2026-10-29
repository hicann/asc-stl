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

#include <asc/std/algorithm>
#include <asc/std/functional>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "support/bit_count_reference.h"

namespace {

template <class T, class = void>
struct accepts_count : std::false_type {};

template <class T>
struct accepts_count<T, std::void_t<decltype(asc::std::countl_zero(std::declval<T>()))>> : std::true_type {};

static_assert(!accepts_count<bool>::value && !accepts_count<int>::value && !accepts_count<char>::value);
static_assert(std::is_same_v<decltype(asc::std::countl_zero(1U)), int>);
static_assert(noexcept(asc::std::countl_zero(1U)) && noexcept(asc::std::countr_zero(1U)));
static_assert(noexcept(asc::std::countl_one(1U)) && noexcept(asc::std::countr_one(1U)));

template <class T>
constexpr bool constant_contract()
{
    constexpr int digits = std::numeric_limits<T>::digits;
    constexpr T maximum = std::numeric_limits<T>::max();
    constexpr T high = static_cast<T>(T{1} << (digits - 1));
    return asc::std::countl_zero(T{0}) == digits && asc::std::countr_zero(T{0}) == digits &&
        asc::std::countl_one(T{0}) == 0 && asc::std::countr_one(T{0}) == 0 &&
        asc::std::countl_zero(T{1}) == digits - 1 && asc::std::countr_zero(T{1}) == 0 &&
        asc::std::countl_one(maximum) == digits && asc::std::countr_one(maximum) == digits &&
        asc::std::countl_zero(high) == 0 && asc::std::countr_zero(high) == digits - 1 &&
        asc::std::countl_one(high) == 1 && asc::std::countr_one(static_cast<T>(high - 1)) == digits - 1;
}

static_assert(constant_contract<unsigned char>() && constant_contract<unsigned short>());
static_assert(constant_contract<unsigned int>() && constant_contract<unsigned long>());
static_assert(constant_contract<unsigned long long>());
static_assert(asc::std::countl_zero(static_cast<unsigned short>(0x100)) == 7);
static_assert(asc::std::countl_zero(static_cast<unsigned char>(1)) == 7);

template <class T>
bool check_value(T value)
{
    return asc_stl_bit_count_test::observe(value) ==
        asc_stl_bit_count_test::reference(static_cast<std::uint64_t>(value), std::numeric_limits<T>::digits);
}

template <class T>
bool exhaustive()
{
    const unsigned int count = 1U << std::numeric_limits<T>::digits;
    for (unsigned int value = 0; value < count; ++value) {
        if (!check_value(static_cast<T>(value))) {
            return false;
        }
    }
    return true;
}

template <class T>
bool wide(std::mt19937_64& generator)
{
    if (!check_value(T{0}) || !check_value(std::numeric_limits<T>::max())) {
        return false;
    }
    for (int index = 0; index < std::numeric_limits<T>::digits; ++index) {
        const T value = static_cast<T>(T{1} << index);
        if (!check_value(value) || !check_value(static_cast<T>(value - 1)) || !check_value(static_cast<T>(value + 1))) {
            return false;
        }
    }
    for (int index = 0; index < 100000; ++index) {
        if (!check_value(static_cast<T>(generator()))) {
            return false;
        }
    }
    return true;
}

bool dynamic_matrix()
{
    unsigned int words[512]{};
    asc_stl_bit_count_test::initialize_runtime(words);
    words[13] = asc_stl_bit_count_test::evaluate_runtime(words);
    if (asc_stl_bit_count_test::runtime_failures(words) != 0) {
        return false;
    }
    // Each field and width must affect the Host golden result.
    for (unsigned int width = 0; width < 4; ++width) {
        for (unsigned int field = 0; field < 4; ++field) {
            auto& observed = words[asc_stl_bit_count_test::output_start + width * 9];
            observed ^= 1U << (7 * field);
            const bool rejected = asc_stl_bit_count_test::runtime_failures(words) != 0;
            observed ^= 1U << (7 * field);
            if (!rejected) {
                return false;
            }
        }
    }
    return true;
}

bool integer_sort(std::size_t size, std::mt19937_64& generator)
{
    if (size == 0) {
        int sentinel = 0;
        asc::std::sort(&sentinel, &sentinel);
        return sentinel == 0;
    }
    std::vector<int> values(size);
    for (auto& value : values) {
        value = static_cast<int>(generator() % 37) - 18;
    }
    auto expected = values;
    std::sort(expected.begin(), expected.end());
    asc::std::sort(values.data(), values.data() + size);
    if (values != expected) {
        return false;
    }
    std::reverse(expected.begin(), expected.end());
    asc::std::sort(values.data(), values.data() + size, asc::std::greater<int>{});
    return values == expected;
}

bool floating_sort(std::size_t size, std::mt19937_64& generator)
{
    std::vector<double> values(size);
    for (auto& value : values) {
        value = static_cast<double>(static_cast<int>(generator() % 1000) - 500) / 7.0;
    }
    auto expected = values;
    std::sort(expected.begin(), expected.end());
    asc::std::sort(values.data(), values.data() + size);
    return values == expected;
}

struct record {
    inline static int live = 0;
    int key;
    int id;
    std::string text;

    record(int key_value, int id_value) : key(key_value), id(id_value), text(std::to_string(id_value))
    {
        ++live;
    }
    record(const record& other) : key(other.key), id(other.id), text(other.text)
    {
        ++live;
    }
    record(record&& other) noexcept : key(other.key), id(other.id), text(std::move(other.text))
    {
        ++live;
    }
    record& operator=(const record&) = default;
    record& operator=(record&&) = default;
    ~record()
    {
        --live;
    }
};

bool nontrivial_sort(std::size_t size)
{
    std::vector<record> values;
    for (std::size_t index = 0; index < size; ++index) {
        values.emplace_back(static_cast<int>((index * 17) % 37), static_cast<int>(index));
    }
    const auto compare = [](const record& left, const record& right) { return left.key < right.key; };
    asc::std::sort(values.data(), values.data() + size, compare);
    std::vector<bool> seen(size);
    for (std::size_t index = 0; index < size; ++index) {
        const auto& value = values[index];
        if (value.id < 0 || static_cast<std::size_t>(value.id) >= size || seen[value.id] ||
            value.text != std::to_string(value.id) || value.key != (value.id * 17) % 37 ||
            (index != 0 && value.key < values[index - 1].key)) {
            return false;
        }
        seen[value.id] = true;
    }
    return true;
}

struct move_only {
    int key;
    std::unique_ptr<int> id;
};

bool move_only_sort(std::size_t size)
{
    std::vector<move_only> values;
    for (std::size_t index = 0; index < size; ++index) {
        values.push_back({static_cast<int>((index * 17) % 37), std::make_unique<int>(static_cast<int>(index))});
    }
    const auto compare = [](const move_only& left, const move_only& right) { return left.key < right.key; };
    asc::std::sort(values.data(), values.data() + size, compare);
    std::vector<bool> seen(size);
    for (std::size_t index = 0; index < size; ++index) {
        const auto& value = values[index];
        if (!value.id || *value.id < 0 || static_cast<std::size_t>(*value.id) >= size || seen[*value.id] ||
            value.key != (*value.id * 17) % 37 || (index != 0 && value.key < values[index - 1].key)) {
            return false;
        }
        seen[*value.id] = true;
    }
    return true;
}

bool sort_matrix(std::mt19937_64& generator)
{
    if (!integer_sort(0, generator)) {
        return false;
    }
    for (std::size_t size = 1; size < 512; ++size) {
        if (!integer_sort(size, generator) || !floating_sort(size, generator) || !nontrivial_sort(size) ||
            record::live != 0 || !move_only_sort(size)) {
            return false;
        }
    }
    return true;
}

}  // namespace

int main()
{
    std::mt19937_64 generator(10723);
    const bool bits = exhaustive<std::uint8_t>() && exhaustive<std::uint16_t>() && wide<std::uint32_t>(generator) &&
        wide<std::uint64_t>(generator) && wide<unsigned long long>(generator) && dynamic_matrix();
    const bool sorts = bits && sort_matrix(generator);
    std::cout << "bit_count_exhaustive_8_16_random_32_64=" << bits << " sort_consumers=" << sorts << '\n';
    return bits && sorts ? 0 : 1;
}
