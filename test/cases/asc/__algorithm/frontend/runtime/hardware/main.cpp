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

#include "../semantics.h"

namespace {
bool verify(const int* input, const int* output, int callback_count)
{
    const int expected_copy[] = {1, 2, 3, 4};
    const int expected_transform[] = {2, 3, 4, 5};
    const int expected_difference[] = {1, 1, 1, 1};
    const int expected_scan[] = {0, 1, 3, 6};
    const int expected_duplicates[] = {1, 1, 2, 2};
    const int expected_replaced[] = {1, 8, 3, 4, 1, 8, 9, 4};
    for (int index = 0; index != 4; ++index) {
        if (output[index] != expected_copy[index] || output[index + 5] != expected_transform[index] ||
            output[index + 9] != expected_difference[index] || output[index + 13] != expected_copy[index] ||
            output[index + 18] != expected_scan[index] || input[index + 4] != expected_copy[index] ||
            input[index + 12] != expected_duplicates[index])
            return false;
        if (output[index + 40] != expected_copy[index] || output[index + 44] != expected_scan[index])
            return false;
    }
    for (int index = 0; index != 8; ++index) {
        if (output[index + 54] != expected_replaced[index])
            return false;
    }
    const auto partition_count = *reinterpret_cast<const __SIZE_TYPE__*>(output + 30);
    const auto selected_count = *reinterpret_cast<const __SIZE_TYPE__*>(output + 32);
    const auto found_index = *reinterpret_cast<const __SIZE_TYPE__*>(output + 34);
    return output[4] == 0x7f7f7f7f && output[17] == 10 && output[22] == 2 && output[23] == 4 && partition_count == 2 &&
        selected_count == 2 && found_index == 2 && output[37] == 19 && output[38] == 6 && output[39] == 6 &&
        callback_count == 1 && output[48] == 2 && output[49] == 4 && output[52] == 1 && output[53] == 3;
}
}  // namespace

int main()
{
    int host_input[16] = {1, 2, 3, 4, 4, 1, 3, 2, 1, 3, 2, 4, 1, 1, 2, 2};
    int host_output[64]{};
    int* device_input = nullptr;
    int* device_output = nullptr;
    void* workspace = nullptr;
    aclrtStream stream = nullptr;
    int callback_count = 0;
    int submission_status = 0;
    int synchronization_status = -1;
    int input_copy_status = -1;
    int output_copy_status = -1;
    bool passed = aclInit(nullptr) == ACL_SUCCESS && aclrtSetDevice(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device_input), sizeof(host_input), ACL_MEM_MALLOC_HUGE_FIRST) ==
            ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device_output), sizeof(host_output), ACL_MEM_MALLOC_HUGE_FIRST) ==
            ACL_SUCCESS &&
        aclrtMalloc(&workspace, 256, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMemcpy(device_input, sizeof(host_input), host_input, sizeof(host_input), ACL_MEMCPY_HOST_TO_DEVICE) ==
            ACL_SUCCESS;
    if (passed) {
#if ASC_STL_B019_simt
        submission_status = launch_asc_stl_b019_simt(device_input, device_output, workspace, stream, &callback_count);
#else
        submission_status = launch_asc_stl_b019_simd(device_input, device_output, workspace, stream, &callback_count);
#endif
        passed = submission_status == 0;
        if (passed) {
            synchronization_status = aclrtSynchronizeStream(stream);
            passed = synchronization_status == ACL_SUCCESS;
        }
        if (passed) {
            input_copy_status = aclrtMemcpy(
                host_input, sizeof(host_input), device_input, sizeof(host_input), ACL_MEMCPY_DEVICE_TO_HOST);
            passed = input_copy_status == ACL_SUCCESS;
        }
        if (passed) {
            output_copy_status = aclrtMemcpy(
                host_output, sizeof(host_output), device_output, sizeof(host_output), ACL_MEMCPY_DEVICE_TO_HOST);
            passed = output_copy_status == ACL_SUCCESS;
        }
        passed = passed && verify(host_input, host_output, callback_count);
    }
    if (workspace)
        passed = aclrtFree(workspace) == ACL_SUCCESS && passed;
    if (device_output)
        passed = aclrtFree(device_output) == ACL_SUCCESS && passed;
    if (device_input)
        passed = aclrtFree(device_input) == ACL_SUCCESS && passed;
    if (stream)
        passed = aclrtDestroyStream(stream) == ACL_SUCCESS && passed;
    passed = aclrtResetDevice(0) == ACL_SUCCESS && passed;
    passed = aclFinalize() == ACL_SUCCESS && passed;
    if (passed) {
        std::cout << "ASC_STL_HARDWARE_B019_PASS\n";
    } else {
        std::cerr << "B019 failure submission=" << submission_status << " synchronization=" << synchronization_status
                  << " input_copy=" << input_copy_status << " output_copy=" << output_copy_status
                  << " callback=" << callback_count << " input=";
        for (int value : host_input)
            std::cerr << value << ',';
        std::cerr << " output=";
        for (int value : host_output)
            std::cerr << value << ',';
        std::cerr << '\n';
    }
    return passed ? 0 : 1;
}
