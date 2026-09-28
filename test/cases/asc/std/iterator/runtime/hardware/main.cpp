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
#include <asc/__work_queue/cursor.h>
#include <cstdint>
#include <iostream>

#if defined(ASC_STL_B024_SIMD)
void launch_asc_stl_b024_simd(std::uint32_t*, const std::uint32_t*, void*);
#else
void launch_asc_stl_b024_simt(__INT32_TYPE__*, asc::detail::work_cursor*, void*);
#endif

int main()
{
    constexpr std::uint32_t kElements = 256;
    std::uint32_t host_input[kElements];
    std::uint32_t host_output[kElements] = {};
    for (std::uint32_t index = 0; index < kElements; ++index) {
        host_input[index] = index;
    }
    __INT32_TYPE__ simt_results[8] = {};
    asc::detail::work_cursor cursor(0, 10, 4);
    __INT32_TYPE__* simt_device = nullptr;
    asc::detail::work_cursor* device_cursor = nullptr;
    std::uint32_t* input = nullptr;
    std::uint32_t* output = nullptr;
    aclrtStream stream = nullptr;
    const size_t bytes = sizeof(host_input);
    bool passed = aclInit(nullptr) == ACL_SUCCESS && aclrtSetDevice(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS;
#if defined(ASC_STL_B024_SIMD)
    passed = passed && aclrtMalloc(reinterpret_cast<void**>(&input), bytes, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&output), bytes, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMemcpy(input, bytes, host_input, bytes, ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
#else
    passed = passed &&
        aclrtMalloc(reinterpret_cast<void**>(&simt_device), sizeof(simt_results), ACL_MEM_MALLOC_HUGE_FIRST) ==
            ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device_cursor), sizeof(cursor), ACL_MEM_MALLOC_HUGE_FIRST) ==
            ACL_SUCCESS &&
        aclrtMemcpy(device_cursor, sizeof(cursor), &cursor, sizeof(cursor), ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
#endif
    if (passed) {
#if defined(ASC_STL_B024_SIMD)
        launch_asc_stl_b024_simd(output, input, stream);
        passed = aclrtSynchronizeStream(stream) == ACL_SUCCESS &&
            aclrtMemcpy(host_output, bytes, output, bytes, ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        std::uint32_t mismatches = 0;
        for (std::uint32_t index = 0; index < kElements; ++index) {
            mismatches += host_output[index] != host_input[index] + 7u;
        }
        std::cout << "b024_pipeline_mismatches=" << mismatches << '\n';
        passed = passed && mismatches == 0;
#else
        launch_asc_stl_b024_simt(simt_device, device_cursor, stream);
        passed = aclrtSynchronizeStream(stream) == ACL_SUCCESS &&
            aclrtMemcpy(simt_results, sizeof(simt_results), simt_device, sizeof(simt_results),
                ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        std::cout << "b024_payload=" << simt_results[0] << " runtime_failures=" << simt_results[1] << '\n';
        passed = passed && simt_results[0] == 0 && simt_results[1] == 0;
#endif
    }
    if (input)
        passed = aclrtFree(input) == ACL_SUCCESS && passed;
    if (output)
        passed = aclrtFree(output) == ACL_SUCCESS && passed;
    if (simt_device)
        passed = aclrtFree(simt_device) == ACL_SUCCESS && passed;
    if (device_cursor)
        passed = aclrtFree(device_cursor) == ACL_SUCCESS && passed;
    if (stream)
        passed = aclrtDestroyStream(stream) == ACL_SUCCESS && passed;
    passed = aclrtResetDevice(0) == ACL_SUCCESS && passed;
    passed = aclFinalize() == ACL_SUCCESS && passed;
    if (passed)
        std::cout << "ASC_STL_B024_HARDWARE_PASS\n";
    return passed ? 0 : 1;
}
