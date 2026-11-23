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

#include <acl/acl.h>
#include <iostream>
#include <vector>

#include "launch.h"
#include "../../../../support/bit_reference.h"
#if defined(ASC_STL_BIT_SIMULATION)
#include "simulation_runtime.h"
using bit_runtime = bit_simulation_runtime;
#else
#include "../../../../support/hardware_runtime.h"
using bit_runtime = asc_stl_test::hardware_runtime;
#endif

namespace {

std::vector<bit_record> make_records()
{
    const int windows[][2] = {{0, 0}, {32, 0}, {64, 0}, {0, 32}, {0, 64}, {31, 1}, {63, 1}, {28, 4}, {60, 4}, {1, 31},
        {1, 63}, {31, 2}, {63, 2}, {32, 1}, {64, 1}, {0, -1}, {-1, 1}, {33, 0}, {65, 0}, {0, 33}, {0, 65},
        {INT_MIN, INT_MAX}, {INT_MAX, INT_MAX}, {INT_MIN, 0}, {0, INT_MIN}, {INT_MAX, 0}, {1, INT_MAX},
        {INT_MAX, INT_MIN}, {-1, 0}, {0, INT_MAX}, {INT_MAX - 1, INT_MIN + 1}};
    constexpr bit_test::u64 patterns[] = {0, 1, 0xFFFFFFFFFFFFFFFFULL, 0xAAAAAAAAAAAAAAAAULL, 0x5555555555555555ULL,
        0x0123456789ABCDEFULL, 0xDEADBEEFA5A50000ULL, 0x8000000000000001ULL};
    std::vector<bit_record> records;
    for (auto value : patterns) {
        for (const auto& window : windows) {
            records.push_back({value, value ^ 0x1234567812345678ULL, window[0], window[1]});
        }
    }
    return records;
}

template <class T>
void append_expected(std::vector<bit_test::u64>& expected, const bit_record& record)
{
    const T destination = static_cast<T>(record.destination);
    const T source = static_cast<T>(record.source);
    expected.push_back(bit_test::reference_reverse(destination));
    expected.push_back(bit_test::reference_extract(destination, record.start, record.width));
    expected.push_back(bit_test::reference_insert(destination, source, record.start, record.width));
    expected.push_back(bit_test::reference_mask<T>(record.start, record.width));
}

bool verify(const std::vector<bit_test::u64>& actual, const std::vector<bit_record>& records)
{
    std::vector<bit_test::u64> expected;
    for (const auto& record : records) {
        append_expected<bit_test::u32>(expected, record);
        append_expected<bit_test::u64>(expected, record);
    }
    for (std::size_t index = 0; index < expected.size(); ++index) {
        if (actual[index] != expected[index]) {
            std::cerr << "bit mismatch record=" << index / bit_output_words << " operation=" << index % bit_output_words
                      << " actual=" << std::hex << actual[index] << " expected=" << expected[index] << '\n';
            return false;
        }
    }
    std::cout << "bit device comparisons=" << expected.size() << '\n';
    return true;
}

}  // namespace

int main()
{
    const auto records = make_records();
    const auto input_bytes = records.size() * sizeof(bit_record);
    std::vector<bit_test::u64> actual(records.size() * bit_output_words, 0xDEADBEEFDEADBEEFULL);
    const auto output_bytes = actual.size() * sizeof(bit_test::u64);
    bit_runtime runtime;
    bit_record* device_records = nullptr;
    bit_test::u64* output = nullptr;
    aclrtStream stream = nullptr;
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device_records), input_bytes, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&output), output_bytes, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    if (passed && runtime.ready()) {
        passed = aclrtMemcpy(device_records, input_bytes, records.data(), input_bytes, ACL_MEMCPY_HOST_TO_DEVICE) ==
                ACL_SUCCESS &&
            aclrtMemcpy(output, output_bytes, actual.data(), output_bytes, ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
    }
    if (passed && runtime.ready()) {
        launch_bit(output, device_records, static_cast<unsigned>(records.size()), stream);
        passed = runtime.synchronize(stream) == ACL_SUCCESS &&
            aclrtMemcpy(actual.data(), output_bytes, output, output_bytes, ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        passed = passed && verify(actual, records);
    }
    if (output) {
        passed = runtime.free_device(output) == ACL_SUCCESS && passed;
    }
    if (device_records) {
        passed = runtime.free_device(device_records) == ACL_SUCCESS && passed;
    }
    if (stream) {
        passed = runtime.destroy_stream(stream) == ACL_SUCCESS && passed;
    }
    passed = runtime.reset_device(0) == ACL_SUCCESS && passed;
    passed = runtime.finalize() == ACL_SUCCESS && passed;
    passed = runtime.finish(passed) == 0;
    if (passed) {
        std::cout << "ASC_STL_BIT_RUNTIME_PASS\n";
    }
    return passed ? 0 : 1;
}
