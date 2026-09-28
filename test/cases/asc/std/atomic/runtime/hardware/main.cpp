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

void launch_asc_stl_b022(int*, aclrtStream);

int main()
{
    int results[64] = {};
    int* device = nullptr;
    aclrtStream stream = nullptr;
    const size_t bytes = sizeof(results);
    bool passed = aclInit(nullptr) == ACL_SUCCESS && aclrtSetDevice(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device), bytes, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMemcpy(device, bytes, results, bytes, ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
    if (passed) {
        launch_asc_stl_b022(device, stream);
        passed = aclrtSynchronizeStream(stream) == ACL_SUCCESS &&
            aclrtMemcpy(results, bytes, device, bytes, ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        std::cout << "atomic_failures=" << results[31] << " algorithm_failures=" << results[32] << '\n';
        std::cout << "standard_atomic_published=" << results[41] << " acknowledged=" << results[42]
                  << " visibility_failures=" << results[43] << " timeouts=" << results[44] << '\n';
        passed = passed && results[31] == 0 && results[32] == 0;
#if ASC_STL_B022_SIMT
        passed = passed && results[41] == 20000 && results[42] == 20000 && results[43] == 0 && results[44] == 0;
#else
        passed = passed && results[41] == 0 && results[42] == 0 && results[43] == 0 && results[44] == 0;
#endif
    }
    if (device)
        passed = aclrtFree(device) == ACL_SUCCESS && passed;
    if (stream)
        passed = aclrtDestroyStream(stream) == ACL_SUCCESS && passed;
    passed = aclrtResetDevice(0) == ACL_SUCCESS && passed;
    passed = aclFinalize() == ACL_SUCCESS && passed;
    std::cout << (passed ? "PASS" : "FAIL") << ": B022 Device semantics\n";
    return passed ? 0 : 1;
}
