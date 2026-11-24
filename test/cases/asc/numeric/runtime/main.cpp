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

#include <cstdlib>
#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>
#include <tuple>
#include <vector>

#include "../reference.h"
#include "launch.h"
#if defined(ASC_STL_NUMERIC_SIMULATION)
#include "simulation_runtime.h"
using runtime_type = numeric_simulation_runtime;
#else
#include "../../../../support/hardware_runtime.h"
using runtime_type = asc_stl_test::hardware_runtime;
#endif

namespace {
using types = std::tuple<signed char, unsigned char, short, unsigned short, int, unsigned int, long, unsigned long,
    long long, unsigned long long>;

struct vectors {
    std::vector<numeric_word> input;
    std::vector<numeric_word> expected;
};

void append_expected(vectors& data, numeric_word value, bool failed)
{
    data.expected.insert(data.expected.end(), {value, failed, 0});
    data.expected.resize(data.expected.size() + numeric_output_stride - numeric_output_words, ~numeric_word{0});
}

template <class T>
std::vector<T> samples()
{
    const auto values = numeric_reference::boundaries<T>();
    return {values[0], values[1], static_cast<T>(-1), T{0}, T{1}, T{2}, values[9], values[10]};
}

template <class T>
void append_pair(vectors& data, unsigned type, T left, T right)
{
    for (unsigned op = 0; op < 4; ++op) {
        const auto expected = numeric_reference::arithmetic(left, right, op);
        data.input.insert(
            data.input.end(), {type, op, static_cast<numeric_word>(left), static_cast<numeric_word>(right), 0});
        append_expected(data, static_cast<numeric_word>(expected.value), expected.failed);
    }
}

template <class T>
void append_arithmetic(vectors& data, unsigned type)
{
#if defined(ASC_STL_NUMERIC_SIMULATION) && defined(ASC_STL_NUMERIC_SIMD)
    const T low = std::numeric_limits<T>::min(), high = std::numeric_limits<T>::max();
    append_pair(data, type, high, T{2});
    if constexpr (std::is_signed_v<T>) {
        append_pair(data, type, low, T{-1});
        append_pair(data, type, low, T{1});
        append_pair(data, type, T{-7}, T{3});
        append_pair(data, type, T{7}, T{-3});
    }
    if constexpr (sizeof(T) == 8)
        if (type >= 8)
            append_pair(data, type, T{0}, T{0});
#elif defined(ASC_STL_NUMERIC_SIMULATION)
    const T low = std::numeric_limits<T>::min(), high = std::numeric_limits<T>::max();
    append_pair(data, type, T{0}, T{0});
    append_pair(data, type, high, T{1});
    append_pair(data, type, low, T{1});
    append_pair(data, type, high, T{2});
    if constexpr (std::is_signed_v<T>) {
        append_pair(data, type, low, T{-1});
        append_pair(data, type, T{-7}, T{3});
        append_pair(data, type, T{7}, T{-3});
    } else {
        append_pair(data, type, T{0}, high);
    }
#else
    for (T left : samples<T>())
        for (T right : samples<T>())
            append_pair(data, type, left, right);
#endif
}

template <class To, class From>
void append_cast(vectors& data, unsigned source, unsigned destination)
{
#if defined(ASC_STL_NUMERIC_SIMULATION) && defined(ASC_STL_NUMERIC_SIMD)
    const std::vector<From> values{std::numeric_limits<From>::max()};
#elif defined(ASC_STL_NUMERIC_SIMULATION)
    const std::vector<From> values{std::numeric_limits<From>::min(), std::numeric_limits<From>::max()};
#else
    const auto values = samples<From>();
#endif
    for (From value : values) {
        const auto expected = numeric_reference::cast<To>(value);
        data.input.insert(data.input.end(), {source, 4, static_cast<numeric_word>(value), 0, destination});
        append_expected(data, static_cast<numeric_word>(expected.value), expected.failed);
    }
}

template <class To, class From>
void explicit_cast(vectors& data, unsigned source, unsigned destination, From value)
{
    const auto expected = numeric_reference::cast<To>(value);
    data.input.insert(data.input.end(), {source, 4, static_cast<numeric_word>(value), 0, destination});
    append_expected(data, static_cast<numeric_word>(expected.value), expected.failed);
}

template <class From, std::size_t... Index>
void destinations(vectors& data, unsigned source, std::index_sequence<Index...>)
{
    (append_cast<std::tuple_element_t<Index, types>, From>(data, source, Index), ...);
}

template <std::size_t... Index>
vectors build_vectors(std::index_sequence<Index...> indices)
{
    vectors data;
    (append_arithmetic<std::tuple_element_t<Index, types>>(data, Index), ...);
    (destinations<std::tuple_element_t<Index, types>>(data, Index, indices), ...);
    append_pair(data, 9, 0xffffffffULL, 0x100000001ULL);
    append_pair(data, 9, 0x100000001ULL, 0xffffffffULL);
    append_pair(data, 9, 0xffffffffULL, 0x100000002ULL);
    append_pair(data, 9, 0x100000000ULL, 0x100000000ULL);
    append_pair(data, 9, 0ULL, std::numeric_limits<unsigned long long>::max());
    append_pair(
        data, 9, std::numeric_limits<unsigned long long>::max(), std::numeric_limits<unsigned long long>::max());
    append_pair(data, 8, std::numeric_limits<long long>::min(), std::numeric_limits<long long>::min());
#if defined(ASC_STL_NUMERIC_SIMULATION) && defined(ASC_STL_NUMERIC_SIMD)
    explicit_cast<unsigned>(data, 4, 5, -1);
    explicit_cast<unsigned long long>(data, 8, 9, std::numeric_limits<long long>::min());
    explicit_cast<signed char>(data, 8, 0, std::numeric_limits<long long>::min());
    explicit_cast<long long>(data, 0, 8, static_cast<signed char>(-128));
    explicit_cast<long long>(data, 9, 8, 0x8000000000000000ULL);
    explicit_cast<int>(data, 9, 4, 0x7fffffffULL);
    explicit_cast<int>(data, 9, 4, 0x80000000ULL);
    explicit_cast<unsigned char>(data, 9, 1, 255ULL);
    explicit_cast<unsigned char>(data, 9, 1, 256ULL);
    explicit_cast<long long>(data, 9, 8, 0x7fffffffffffffffULL);
#endif
    return data;
}

unsigned selected_count(vectors& data)
{
    const unsigned count = data.input.size() / numeric_input_words;
    const char* limit = std::getenv("ASC_STL_NUMERIC_RUNTIME_LIMIT");
    if (!limit || !*limit)
        return count;
    const auto selected = std::strtoul(limit, nullptr, 10);
    if (selected >= count)
        return count;
    data.input.resize(selected == 0 ? numeric_input_words : selected * numeric_input_words);
    data.expected.resize(selected * numeric_output_stride);
    if (selected == 0)
        data.expected.assign(1, ~numeric_word{0});
    return static_cast<unsigned>(selected);
}

bool verify(const std::vector<numeric_word>& actual, const std::vector<numeric_word>& expected)
{
    for (std::size_t index = 0; index < actual.size(); ++index) {
        if (index % numeric_output_stride < numeric_output_words && actual[index] != expected[index]) {
            std::cerr << "numeric record=" << index / numeric_output_stride
                      << " field=" << index % numeric_output_stride << " expected=" << expected[index]
                      << " actual=" << actual[index] << '\n';
            return false;
        }
    }
    std::cout << "numeric device exact comparisons=" << actual.size() / numeric_output_stride << '\n';
    return true;
}
}  // namespace

int main()
{
    auto data = build_vectors(std::make_index_sequence<10>{});
    const unsigned count = selected_count(data);
    std::vector<numeric_word> actual(data.expected.size(), ~numeric_word{0});
    const auto input_bytes = data.input.size() * sizeof(numeric_word),
               output_bytes = actual.size() * sizeof(numeric_word);
    runtime_type runtime;
    numeric_word* input = nullptr;
    numeric_word* output = nullptr;
    aclrtStream stream = nullptr;
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS;
    if (passed) {
        passed = aclrtMalloc(reinterpret_cast<void**>(&input), input_bytes, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
            aclrtMalloc(reinterpret_cast<void**>(&output), output_bytes, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    }
    if (passed && runtime.ready()) {
        passed =
            aclrtMemcpy(input, input_bytes, data.input.data(), input_bytes, ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS &&
            aclrtMemcpy(output, output_bytes, actual.data(), output_bytes, ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
    }
    if (passed && runtime.ready()) {
        launch_numeric(output, input, count, stream);
        passed = runtime.synchronize(stream) == ACL_SUCCESS &&
            aclrtMemcpy(actual.data(), output_bytes, output, output_bytes, ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        passed = passed && verify(actual, data.expected);
    }
    if (output)
        passed = runtime.free_device(output) == ACL_SUCCESS && passed;
    if (input)
        passed = runtime.free_device(input) == ACL_SUCCESS && passed;
    if (stream)
        passed = runtime.destroy_stream(stream) == ACL_SUCCESS && passed;
    passed = runtime.reset_device(0) == ACL_SUCCESS && passed;
    passed = runtime.finalize() == ACL_SUCCESS && passed;
    passed = runtime.finish(passed) == 0;
    if (passed)
        std::cout << (count == 0 ? "ASC_STL_NUMERIC_CONTROL_PASS\n" : "ASC_STL_NUMERIC_RUNTIME_PASS\n");
    return passed ? 0 : 1;
}
