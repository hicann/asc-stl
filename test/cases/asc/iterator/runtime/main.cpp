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
#include "launch.h"
#if defined(ASC_STL_ITERATOR_SIMULATION)
#include "../../numeric_types/runtime/simulation_runtime.h"
using iterator_runtime = numeric_simulation_runtime;
#else
#include "../../../../support/hardware_runtime.h"
using iterator_runtime = asc_stl_test::hardware_runtime;
#endif

namespace {
bool verify(const unsigned* result)
{
    const unsigned expected[16] = {0, 10, 6, 2, 11, 7, 6, 2, 137, 9, 2, 3, 8, 1, 1, 1};
    unsigned mismatches = 0;
    for (unsigned index = 0; index < 32; ++index) {
        const unsigned value = index >= 8 && index < 24 ? expected[index - 8] : 0xaabbccddu;
        if (result[index] != value) {
            ++mismatches;
            std::cerr << "iterator_mismatch index=" << index << " actual=" << result[index] << " expected=" << value
                      << '\n';
        }
    }
    std::cout << "iterator_mismatches=" << mismatches << '\n';
    return mismatches == 0;
}
}  // namespace

int main()
{
    iterator_runtime runtime;
    unsigned initial[32];
    for (auto& value : initial) {
        value = 0xaabbccddu;
    }
    const unsigned input[5] = {1, 2, 3, 4, 5};
    unsigned result[32] = {};
    unsigned* device_input = nullptr;
    unsigned* device_output = nullptr;
    aclrtStream stream = nullptr;
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device_input), sizeof(input), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device_output), sizeof(initial), ACL_MEM_MALLOC_HUGE_FIRST) ==
            ACL_SUCCESS;
    if (passed && runtime.ready()) {
        passed =
            aclrtMemcpy(device_input, sizeof(input), input, sizeof(input), ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS &&
            aclrtMemcpy(device_output, sizeof(initial), initial, sizeof(initial), ACL_MEMCPY_HOST_TO_DEVICE) ==
                ACL_SUCCESS;
    }
    if (passed && runtime.ready()) {
        launch_iterator(device_output, device_input, stream);
        passed = runtime.synchronize(stream) == ACL_SUCCESS &&
            aclrtMemcpy(result, sizeof(result), device_output, sizeof(result), ACL_MEMCPY_DEVICE_TO_HOST) ==
                ACL_SUCCESS;
        passed = verify(result) && passed;
    }
    if (device_input) {
        passed = runtime.free_device(device_input) == ACL_SUCCESS && passed;
    }
    if (device_output) {
        passed = runtime.free_device(device_output) == ACL_SUCCESS && passed;
    }
    if (stream) {
        passed = runtime.destroy_stream(stream) == ACL_SUCCESS && passed;
    }
    passed = runtime.reset_device(0) == ACL_SUCCESS && passed;
    passed = runtime.finalize() == ACL_SUCCESS && passed;
    passed = runtime.finish(passed) == 0;
    if (passed) {
        std::cout << "ASC_STL_ITERATOR_RUNTIME_PASS\n";
    }
    return passed ? 0 : 1;
}
