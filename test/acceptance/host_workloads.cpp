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
#include <asc/std/mdspan>
#include <asc/std/vector>

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

#ifdef ASC_STL_ACCEPTANCE_REFERENCE
using Sequence = std::vector<int, std::allocator<int>>;
constexpr const char* kImplementation = "std_and_raw_index";
#else
using Sequence = asc::std::vector<int, std::allocator<int>>;
constexpr const char* kImplementation = "asc_stl";
#endif

constexpr std::size_t kSortSize = 32768;
constexpr std::size_t kVectorSize = 65536;
constexpr std::size_t kSide = 256;
volatile std::uint64_t observed_checksum = 0;

void require(bool condition, const char* message)
{
    if (!condition) {
        throw std::runtime_error(message);
    }
}

void verify_aliasing()
{
    Sequence values(std::allocator<int>{});
    values.push_back(11);
    values.push_back(22);
    while (values.size() < values.capacity()) {
        values.push_back(33);
    }
    values.push_back(values[0]);
    require(values.back() == 11, "self-referencing push_back lost its value");
    while (values.size() < values.capacity()) {
        values.push_back(44);
    }
    values.emplace_back(values[1]);
    require(values.back() == 22, "self-referencing emplace_back lost its value");
}

std::uint64_t grow_sequence()
{
    Sequence values(std::allocator<int>{});
    for (std::size_t index = 0; index < kVectorSize; ++index) {
        values.emplace_back(static_cast<int>(index));
    }
    std::uint64_t sum = 0;
    for (std::size_t index = 0; index < values.size(); ++index) {
        require(values[index] == static_cast<int>(index), "vector element mismatch");
        sum += static_cast<unsigned int>(values[index]);
    }
    require(values.size() == kVectorSize, "vector size mismatch");
    require(sum == kVectorSize * (kVectorSize - 1) / 2, "vector checksum mismatch");
    return sum;
}

std::uint64_t sort_records()
{
    std::vector<int> values(kSortSize);
    for (std::size_t index = 0; index < kSortSize; ++index) {
        values[index] = static_cast<int>((index * 73 + 19) % 256);
    }
#ifdef ASC_STL_ACCEPTANCE_REFERENCE
    std::sort(values.begin(), values.end());
#else
    asc::std::sort(values.data(), values.data() + values.size());
#endif
    std::uint64_t sum = 0;
    for (std::size_t index = 0; index < kSortSize; ++index) {
        require(values[index] == static_cast<int>(index / (kSortSize / 256)), "sorted record mismatch");
        sum += static_cast<unsigned int>(values[index]);
    }
    return sum;
}

std::uint64_t update_matrix()
{
    std::vector<int> data(kSide * kSide);
    for (std::size_t index = 0; index < data.size(); ++index) {
        data[index] = static_cast<int>(index % 97);
    }
#ifndef ASC_STL_ACCEPTANCE_REFERENCE
    asc::std::mdspan<int, asc::std::extents<std::size_t, kSide, kSide>> view(data.data());
#endif
    for (std::size_t row = 0; row < kSide; ++row) {
        for (std::size_t column = 0; column < kSide; ++column) {
#ifdef ASC_STL_ACCEPTANCE_REFERENCE
            data[row * kSide + column] += static_cast<int>(row + column);
#else
            view(row, column) += static_cast<int>(row + column);
#endif
        }
    }
    std::uint64_t sum = 0;
    for (std::size_t index = 0; index < data.size(); ++index) {
        const auto expected = static_cast<int>(index % 97 + index / kSide + index % kSide);
        require(data[index] == expected, "matrix element or layout mismatch");
        sum += static_cast<unsigned int>(data[index]);
    }
    return sum;
}

template <class Operation>
void measure(const char* scenario, Operation operation, int samples)
{
    const auto checksum = operation();  // Warmup uses the same workload and golden checks as each sample.
    for (int sample = 0; sample < samples; ++sample) {
        const auto before = std::chrono::steady_clock::now();
        const auto actual = operation();
        const auto after = std::chrono::steady_clock::now();
        observed_checksum = actual;
        require(actual == checksum, "repeat changed the checked result");
        const auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(after - before).count();
        std::cout << "{\"scenario\":\"" << scenario << "\",\"implementation\":\"" << kImplementation
                  << "\",\"sample\":" << sample << ",\"elapsed_ns\":" << elapsed << ",\"checksum\":" << actual << "}\n";
    }
}

}  // namespace

int main(int argc, char** argv)
{
    try {
        const int samples = argc == 2 ? std::stoi(argv[1]) : 7;
        require(samples >= 3 && samples <= 101 && argc <= 2, "expected 3 to 101 samples");
        verify_aliasing();
        measure("sort_records_32768", sort_records, samples);
        measure("vector_growth_65536", grow_sequence, samples);
        measure("matrix_update_256x256", update_matrix, samples);
        return 0;
    } catch (const std::exception& error) {
        std::cerr << "USER_ACCEPTANCE_FAIL: " << error.what() << '\n';
        return 1;
    }
}
