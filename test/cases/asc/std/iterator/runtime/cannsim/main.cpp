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
#include <iostream>

void launch_asc_stl_b024_cannsim(unsigned long long*, asc::detail::work_cursor*, void*);

int main()
{
    constexpr unsigned long long modulus = 0xffffffffffffffc5ULL;
    unsigned long long results[] = {1, 1, 3, 0, modulus - 7};
    asc::detail::work_cursor cursor(0, 10, 4);
    unsigned long long* device = nullptr;
    asc::detail::work_cursor* device_cursor = nullptr;
    aclrtStream stream = nullptr;
    const size_t bytes = sizeof(results);
    bool passed = aclInit(nullptr) == ACL_SUCCESS && aclrtSetDevice(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device), bytes, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device_cursor), sizeof(cursor), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    if (passed) {
        passed = aclrtMemcpy(device_cursor, sizeof(cursor), &cursor, sizeof(cursor), ACL_MEMCPY_HOST_TO_DEVICE) ==
                ACL_SUCCESS &&
            aclrtMemcpy(device, bytes, results, bytes, ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
    }
    if (passed) {
        launch_asc_stl_b024_cannsim(device, device_cursor, stream);
        passed = aclrtSynchronizeStream(stream) == ACL_SUCCESS &&
            aclrtMemcpy(results, bytes, device, bytes, ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        std::cout << "b024_payload=" << results[0] << " b024_runtime_failures=" << results[1] << '\n';
        std::cout << "lcg_draws=" << results[2] << ',' << results[3] << ',' << results[4] << '\n';
        const bool lcg_matches = results[2] == 0 && results[3] == 5 && results[4] == 32;
        passed = passed && results[0] == 0 && results[1] == 0 && lcg_matches;
    }
    if (device)
        passed = aclrtFree(device) == ACL_SUCCESS && passed;
    if (device_cursor)
        passed = aclrtFree(device_cursor) == ACL_SUCCESS && passed;
    if (stream)
        passed = aclrtDestroyStream(stream) == ACL_SUCCESS && passed;
    passed = aclrtResetDevice(0) == ACL_SUCCESS && passed;
    passed = aclFinalize() == ACL_SUCCESS && passed;
    if (passed)
        std::cout << "ASC_STL_CANNSIM_B024_PASS\n";
    return passed ? 0 : 1;
}
