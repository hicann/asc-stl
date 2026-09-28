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

#if defined(ASC_STL_B026_SIMD)
void launch_asc_stl_b026_cmath_simd(std::uint32_t*, void*);
#else
void launch_asc_stl_b026_cmath_simt(std::uint32_t*, void*);
#endif

int main()
{
    std::uint32_t* result = nullptr;
    aclrtStream stream = nullptr;
    bool passed = aclInit(nullptr) == ACL_SUCCESS && aclrtSetDevice(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&result), 4, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    if (passed) {
#if defined(ASC_STL_B026_SIMD)
        launch_asc_stl_b026_cmath_simd(result, stream);
#else
        launch_asc_stl_b026_cmath_simt(result, stream);
#endif
        std::uint32_t failures = 1;
        passed = aclrtSynchronizeStream(stream) == ACL_SUCCESS &&
            aclrtMemcpy(&failures, 4, result, 4, ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        std::cout << "b026_cmath_failures=" << failures << '\n';
        passed = passed && failures == 0;
    }
    if (result)
        passed = aclrtFree(result) == ACL_SUCCESS && passed;
    if (stream)
        passed = aclrtDestroyStream(stream) == ACL_SUCCESS && passed;
    passed = aclrtResetDevice(0) == ACL_SUCCESS && passed;
    passed = aclFinalize() == ACL_SUCCESS && passed;
    if (passed)
        std::cout << "ASC_STL_B026_CMATH_HARDWARE_PASS\n";
    return passed ? 0 : 1;
}
