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

#if defined(ASC_STL_B028_SIMD)
void launch_asc_stl_b028_simd(unsigned int*, void*);
#else
void launch_asc_stl_b028_simt(unsigned int*, unsigned char*, void*);
#endif
int main()
{
    unsigned int* result_device = nullptr;
    unsigned char* storage_device = nullptr;
    aclrtStream stream = nullptr;
    bool passed = aclInit(nullptr) == ACL_SUCCESS && aclrtSetDevice(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&result_device), sizeof(unsigned int), ACL_MEM_MALLOC_HUGE_FIRST) ==
            ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&storage_device), 8192, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    unsigned int result = 99;
    if (passed) {
#if defined(ASC_STL_B028_SIMD)
        launch_asc_stl_b028_simd(result_device, stream);
#else
        launch_asc_stl_b028_simt(result_device, storage_device, stream);
#endif
        passed = aclrtSynchronizeStream(stream) == ACL_SUCCESS &&
            aclrtMemcpy(&result, sizeof(result), result_device, sizeof(result), ACL_MEMCPY_DEVICE_TO_HOST) ==
                ACL_SUCCESS &&
            result == 0;
    }
    if (storage_device)
        passed = aclrtFree(storage_device) == ACL_SUCCESS && passed;
    if (result_device)
        passed = aclrtFree(result_device) == ACL_SUCCESS && passed;
    if (stream)
        passed = aclrtDestroyStream(stream) == ACL_SUCCESS && passed;
    passed = aclrtResetDevice(0) == ACL_SUCCESS && passed;
    passed = aclFinalize() == ACL_SUCCESS && passed;
    std::cout << "b028_failures=" << result << '\n';
    if (passed)
        std::cout << "ASC_STL_B028_HARDWARE_PASS\n";
    return passed ? 0 : 1;
}
