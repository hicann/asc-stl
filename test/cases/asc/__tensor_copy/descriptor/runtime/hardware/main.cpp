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
#include <cstdint>
#include <iostream>
#include "../../../../../../support/hardware_runtime.h"
#include "launch.h"

int main()
{
    asc_stl_test::hardware_runtime runtime;
    constexpr std::uint32_t kRows = 3;
    constexpr std::uint32_t kSourceColumns = 8;
    constexpr std::uint32_t kPaddedColumns = 8;
    constexpr std::uint32_t kOutputElements = kRows * kPaddedColumns;
    std::uint32_t* input = nullptr;
    std::uint32_t* output = nullptr;
    aclrtStream stream = nullptr;
    std::uint32_t host_input[kOutputElements];
    for (std::uint32_t row = 0; row < kRows; ++row) {
        for (std::uint32_t column = 0; column < kSourceColumns; ++column) {
            host_input[row * kSourceColumns + column] = row * 100u + column;
        }
    }
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&input), sizeof(host_input), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&output), sizeof(host_input), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMemcpy(input, sizeof(host_input), host_input, sizeof(host_input), ACL_MEMCPY_HOST_TO_DEVICE) ==
            ACL_SUCCESS;
    if (passed && runtime.ready()) {
#if defined(ASC_STL_B026_SIMD)
        launch_asc_stl_b026_tensor_copy_simd(output, input, stream);
        std::uint32_t host_output[kOutputElements] = {};
        passed = runtime.synchronize(stream) == ACL_SUCCESS &&
            aclrtMemcpy(host_output, sizeof(host_output), output, sizeof(host_output), ACL_MEMCPY_DEVICE_TO_HOST) ==
                ACL_SUCCESS;
        std::uint32_t mismatches = 0;
        for (std::uint32_t row = 0; row < kRows; ++row) {
            for (std::uint32_t column = 0; column < kPaddedColumns; ++column) {
                std::uint32_t expected = 0;
                if (column == 0) {
                    expected = 0;
                } else if (column >= 1 && column < 6) {
                    expected = row * 100u + (column - 1);
                } else {
                    expected = 0;
                }
                mismatches += host_output[row * kPaddedColumns + column] != expected;
            }
        }
        std::cout << "b026_tensor_copy_mismatches=" << mismatches << '\n';
        passed = passed && mismatches == 0;
#else
        launch_asc_stl_b026_tensor_copy_simt(output, stream);
        std::uint32_t failures = 1;
        passed = runtime.synchronize(stream) == ACL_SUCCESS &&
            aclrtMemcpy(&failures, 4, output, 4, ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        std::cout << "b026_tensor_copy_simt_failures=" << failures << '\n';
        passed = passed && failures == 0;
#endif
    }
    if (input)
        passed = runtime.free_device(input) == ACL_SUCCESS && passed;
    if (output)
        passed = runtime.free_device(output) == ACL_SUCCESS && passed;
    if (stream)
        passed = runtime.destroy_stream(stream) == ACL_SUCCESS && passed;
    passed = runtime.reset_device(0) == ACL_SUCCESS && passed;
    passed = runtime.finalize() == ACL_SUCCESS && passed;
    passed = runtime.finish(passed) == 0;
    if (passed)
        std::cout << "ASC_STL_B026_TENSOR_COPY_HARDWARE_PASS\n";
    return passed ? 0 : 1;
}
