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

#include <iostream>
#include "../semantics.h"
int main()
{
    unsigned int host[2]{};
    unsigned int* device = nullptr;
    aclrtStream stream = nullptr;
    bool passed = aclInit(nullptr) == ACL_SUCCESS && aclrtSetDevice(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device), sizeof(host), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    if (passed) {
#if ASC_STL_B018_simt
        launch_asc_stl_b018_simt(device, stream);
#else
        launch_asc_stl_b018_simd(device, stream);
#endif
        passed = aclrtSynchronizeStream(stream) == ACL_SUCCESS &&
            aclrtMemcpy(host, sizeof(host), device, sizeof(host), ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
#if ASC_STL_B018_simt
        passed = passed && host[0] == 2080;
#else
        passed = passed && host[1] == 10;
#endif
    }
    if (device)
        passed = aclrtFree(device) == ACL_SUCCESS && passed;
    if (stream)
        passed = aclrtDestroyStream(stream) == ACL_SUCCESS && passed;
    passed = aclrtResetDevice(0) == ACL_SUCCESS && passed;
    passed = aclFinalize() == ACL_SUCCESS && passed;
    if (passed)
        std::cout << "ASC_STL_HARDWARE_B018_PASS\n";
    return passed ? 0 : 1;
}
