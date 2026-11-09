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
#include <algorithm>
#include <iostream>

#include "config.h"
#include "launch.h"
#if defined(ASC_STL_RANGES_HARDWARE)
#include "support/hardware_runtime.h"
using Runtime = asc_stl_test::hardware_runtime;
#else
class Runtime {
public:
    aclError initialize(const char* config)
    {
        return aclInit(config);
    }
    aclError set_device(int device)
    {
        return aclrtSetDevice(device);
    }
    bool ready() const
    {
        return true;
    }
    aclError synchronize(aclrtStream stream)
    {
        return aclrtSynchronizeStream(stream);
    }
    aclError free_device(void* pointer)
    {
        return aclrtFree(pointer);
    }
    aclError destroy_stream(aclrtStream stream)
    {
        return aclrtDestroyStream(stream);
    }
    aclError reset_device(int device)
    {
        return aclrtResetDevice(device);
    }
    aclError finalize()
    {
        return aclFinalize();
    }
    int finish(bool passed)
    {
        return passed ? 0 : 1;
    }
};
#endif

namespace {
void expected_path(const int* input, int length, int* result)
{
    for (int i = 0; i < asc_stl_ranges_runtime::path_length; ++i)
        result[i] = asc_stl_ranges_runtime::poison;
    int selected = 0, rejected = 0;
    result[0] = length;
    result[1] = 0;
    for (int i = 0; i < length; ++i) {
        if (input[i] == -3 && result[0] == length)
            result[0] = i;
        if (input[i] == 4)
            result[1] = 1;
        result[32 + i] = input[i];
        result[32 + 2 * 32 + i] = 17;
        result[32 + 3 * 32 + i] = input[i] * 2;
        if (input[i] % 2 == 0) {
            result[32 + 32 + selected] = input[i];
            result[32 + 5 * 32 + selected] = input[i];
            ++selected;
        } else {
            result[32 + 6 * 32 + rejected] = input[i];
            result[32 + 7 * 32 + rejected] = input[i];
            result[32 + 8 * 32 + rejected] = input[i];
            ++rejected;
        }
        result[32 + 9 * 32 + i] = input[i];
    }
    const int binary_length = length < 8 ? length : 8;
    for (int i = 0; i < binary_length; ++i)
        result[32 + 4 * 32 + i] = input[i] * 3 + input[i + 16];
    // The CPU reference uses an independent stable insertion sort.
    for (int i = 1; i < length; ++i) {
        int value = result[32 + 9 * 32 + i], j = i;
        while (j > 0 && result[32 + 9 * 32 + j - 1] > value) {
            result[32 + 9 * 32 + j] = result[32 + 9 * 32 + j - 1];
            --j;
        }
        result[32 + 9 * 32 + j] = value;
    }
    result[2] = length;
    result[3] = length;
    result[4] = selected;
    result[5] = length;
    result[6] = length;
    // Unary transform consumes the entire range, including an empty range.
    result[7] = result[6] == length;
    result[8] = binary_length;
    result[9] = binary_length;
    result[10] = binary_length;
    result[11] = selected;
    result[12] = rejected;
    result[13] = rejected;
    result[14] = rejected;
    result[15] = length;
    int folded = 0;
    for (int i = 0; i < length && i < 4; ++i)
        folded = folded * 10 + input[i];
    result[16] = folded;
    result[17] = length;
    result[18] = length;
    result[19] = length;
    result[20] = length;
    // Slots 21-26 exercise projections on a fixed record fixture, not input[0:length].
    constexpr int count = asc_stl_ranges_runtime::projection_count;
    int keys[count]{};
    std::copy_n(asc_stl_ranges_runtime::projection_keys, count, keys);
    result[21] = std::find(keys, keys + count, asc_stl_ranges_runtime::projection_find_key) - keys;
    result[22] = std::find(keys, keys + count, asc_stl_ranges_runtime::projection_contains_key) != keys + count;
    std::sort(keys, keys + count);
    result[23] = count;
    result[24] = 0;
    result[25] = 0;
    result[26] = 0;
    for (int key : keys) {
        if (key % 2 == 0) {
            ++result[24];
            result[25] += key;
        } else {
            result[26] = result[26] * 10 + key;
        }
    }
    // Slots 27-28 swap a separate pair in both GM and UB, regardless of length.
    result[27] = asc_stl_ranges_runtime::swap_right;
    result[28] = asc_stl_ranges_runtime::swap_left;
}
}  // namespace
int main()
{
    Runtime runtime;
    int values[asc_stl_ranges_runtime::input_count]{};
    int results[asc_stl_ranges_runtime::output_count]{};
    int expected[asc_stl_ranges_runtime::path_length]{};
    int* input = nullptr;
    int* output = nullptr;
    aclrtStream stream = nullptr;
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&input), sizeof(values), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&output), sizeof(results), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    // Keep every length and both address spaces, but submit only one simulator task.
    for (int index = 0; index < asc_stl_ranges_runtime::case_count; ++index)
        for (int i = 0; i < asc_stl_ranges_runtime::storage_length; ++i)
            values[index * asc_stl_ranges_runtime::storage_length + i] =
                i < 64 ? i % 9 - 4 : asc_stl_ranges_runtime::poison;
    for (int& value : results)
        value = asc_stl_ranges_runtime::poison;
    if (passed && runtime.ready()) {
        passed = aclrtMemcpy(input, sizeof(values), values, sizeof(values), ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS &&
            aclrtMemcpy(output, sizeof(results), results, sizeof(results), ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
        if (passed) {
            launch_ranges(stream, input, output);
            passed = runtime.synchronize(stream) == ACL_SUCCESS &&
                aclrtMemcpy(results, sizeof(results), output, sizeof(results), ACL_MEMCPY_DEVICE_TO_HOST) ==
                    ACL_SUCCESS;
        }
    } else {
        passed = false;
    }
    for (int index = 0; passed && index < asc_stl_ranges_runtime::case_count; ++index) {
        const int length = asc_stl_ranges_runtime::lengths[index];
        expected_path(values + index * asc_stl_ranges_runtime::storage_length, length, expected);
        for (int mode = 0; passed && mode < 2; ++mode)
            for (int i = 0; i < asc_stl_ranges_runtime::path_length; ++i) {
                const int offset =
                    index * asc_stl_ranges_runtime::result_count + mode * asc_stl_ranges_runtime::path_length;
                if (results[offset + i] != expected[i]) {
                    std::cerr << "ranges mismatch length=" << length << " mode=" << mode << " position=" << i << '\n';
                    passed = false;
                    break;
                }
            }
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
#if defined(ASC_STL_RANGES_HARDWARE)
    std::cout << (passed ? "PASS: ranges algorithms GM/UB" : "FAIL: ranges algorithms GM/UB") << '\n';
#else
    std::cout << (passed ? "ASC_STL_CANNSIM_RANGES_PASS" : "RANGES_FAIL") << '\n';
#endif
    return passed ? 0 : 1;
}
