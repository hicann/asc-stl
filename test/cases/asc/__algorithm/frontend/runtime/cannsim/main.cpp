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

int main()
{
    int host_input[16] = {1, 2, 3, 4, 4, 1, 3, 2, 1, 3, 2, 4, 1, 1, 2, 2};
    int host_output[64]{};
    int* device_input = nullptr;
    int* device_output = nullptr;
    void* workspace = nullptr;
    aclrtStream stream = nullptr;
    int callback_count = 0;
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
        passed = launch_asc_stl_b019_cannsim(device_input, device_output, workspace, stream, &callback_count) == 0 &&
            aclrtSynchronizeStream(stream) == ACL_SUCCESS &&
            aclrtMemcpy(host_output, sizeof(host_output), device_output, sizeof(host_output),
                ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        const auto selected_count = *reinterpret_cast<const __SIZE_TYPE__*>(host_output + 32);
        const auto found_index = *reinterpret_cast<const __SIZE_TYPE__*>(host_output + 34);
        passed = passed && host_output[0] == 1 && host_output[5] == 2 && host_output[17] == 10 &&
            host_output[22] == 2 && host_output[23] == 4 && selected_count == 2 && found_index == 2 &&
            host_output[37] == 19 && host_output[38] == 6 && host_output[39] == 6 && callback_count == 0;
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
    if (passed)
        std::cout << "ASC_STL_CANNSIM_B019_PASS\n";
    return passed ? 0 : 1;
}
