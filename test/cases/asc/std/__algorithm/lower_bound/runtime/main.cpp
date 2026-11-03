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
#if defined(ASC_STL_BOUNDS_HARDWARE)
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

int main()
{
    Runtime runtime;
    int values[asc_stl_bounds_runtime::storage_length]{};
    const int lengths[asc_stl_bounds_runtime::length_count] = {
        0, 1, 2, 3, 7, 8, 15, 16, 17, 31, 32, 33, 63, 64, 65, 127, 128, 129, 255, 256, 257};
    int results[asc_stl_bounds_runtime::result_count]{};
    int* input = nullptr;
    int* sizes = nullptr;
    int* output = nullptr;
    aclrtStream stream = nullptr;
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&input), sizeof(values), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&sizes), sizeof(lengths), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&output), sizeof(results), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    for (int descending = 0; passed && runtime.ready() && descending < 2; ++descending) {
        for (int i = 0; i < asc_stl_bounds_runtime::storage_length; ++i) {
            values[i] = descending ? 40 - i / 3 : i / 3 - 40;
        }
        passed = aclrtMemcpy(input, sizeof(values), values, sizeof(values), ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS &&
            aclrtMemcpy(sizes, sizeof(lengths), lengths, sizeof(lengths), ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS &&
            aclrtMemset(output, sizeof(results), 0xA5, sizeof(results)) == ACL_SUCCESS;
        if (!passed) {
            break;
        }
        launch_bounds(stream, input, sizes, output, descending);
        passed = runtime.synchronize(stream) == ACL_SUCCESS &&
            aclrtMemcpy(results, sizeof(results), output, sizeof(results), ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        for (int k = 0; passed && k < asc_stl_bounds_runtime::length_count; ++k) {
            for (int tid = 0; passed && tid < asc_stl_bounds_runtime::query_count; ++tid) {
                const auto comp = [descending](int lhs, int rhs) { return descending ? lhs > rhs : lhs < rhs; };
                const int query = (tid - 32) * 3;
                const auto lower = std::lower_bound(values, values + lengths[k], query, comp) - values;
                const auto upper = std::upper_bound(values, values + lengths[k], query, comp) - values;
                const int offset = (k * asc_stl_bounds_runtime::query_count + tid) * 4;
                passed = results[offset] == lower && results[offset + 1] == upper && results[offset + 2] == lower &&
                    results[offset + 3] == upper;
            }
        }
    }
    if (output) {
        passed = runtime.free_device(output) == ACL_SUCCESS && passed;
    }
    if (sizes) {
        passed = runtime.free_device(sizes) == ACL_SUCCESS && passed;
    }
    if (input) {
        passed = runtime.free_device(input) == ACL_SUCCESS && passed;
    }
    if (stream) {
        passed = runtime.destroy_stream(stream) == ACL_SUCCESS && passed;
    }
    passed = runtime.reset_device(0) == ACL_SUCCESS && passed;
    passed = runtime.finalize() == ACL_SUCCESS && passed;
    passed = runtime.finish(passed) == 0;
#if defined(ASC_STL_BOUNDS_HARDWARE)
    std::cout << (passed ? "PASS: Device GM/UB bounds" : "FAIL: Device GM/UB bounds") << '\n';
#else
    std::cout << (passed ? "ASC_STL_CANNSIM_BOUNDS_PASS" : "BOUNDS_FAIL") << '\n';
#endif
    return passed ? 0 : 1;
}
