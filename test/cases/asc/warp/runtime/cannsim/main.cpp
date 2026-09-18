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

/* Copyright 2026 湖北多样性算力应用创新研究院 */
#include <acl/acl.h>
#include <cstdlib>
#include <iostream>
#include "../semantics.h"
int main()
{
    int actual[136] = {0, 0, std::getenv("ASC_STL_WARP_INJECT_FAILURE") == nullptr ? 0 : 1};
    int* device = nullptr;
    aclrtStream stream = nullptr;
    bool passed = aclInit(nullptr) == ACL_SUCCESS && aclrtSetDevice(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device), sizeof(actual), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMemcpy(device, sizeof(actual), actual, sizeof(actual), ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
    if (passed) {
        launch_asc_stl_b017_cannsim(device, stream);
        passed = aclrtSynchronizeStream(stream) == ACL_SUCCESS &&
            aclrtMemcpy(actual, sizeof(actual), device, sizeof(actual), ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS &&
            actual[0] == 0 && actual[1] == 4;
    }
    if (device)
        passed = aclrtFree(device) == ACL_SUCCESS && passed;
    if (stream)
        passed = aclrtDestroyStream(stream) == ACL_SUCCESS && passed;
    passed = aclrtResetDevice(0) == ACL_SUCCESS && passed;
    passed = aclFinalize() == ACL_SUCCESS && passed;
    std::cout << "warp_failures=" << actual[0] << " warp_count=" << actual[1] << " inject=" << actual[2] << '\n';
    for (unsigned int index = 8; index < 136; ++index)
        if (actual[index] != 0)
            std::cout << "lane_failure index=" << index - 8 << " count=" << actual[index] << '\n';
    if (passed)
        std::cout << "ASC_STL_CANNSIM_B017_PASS\n";
    return passed ? 0 : 1;
}
