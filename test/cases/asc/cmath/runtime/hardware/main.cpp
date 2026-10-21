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
#include "../../../../../support/hardware_runtime.h"
#include "launch.h"

int main()
{
    asc_stl_test::hardware_runtime runtime;
    std::uint32_t* result = nullptr;
    aclrtStream stream = nullptr;
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&result), 4, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    if (passed && runtime.ready()) {
#if defined(ASC_STL_B026_SIMD)
        launch_asc_stl_b026_cmath_simd(result, stream);
#else
        launch_asc_stl_b026_cmath_simt(result, stream);
#endif
        std::uint32_t failures = 1;
        passed = runtime.synchronize(stream) == ACL_SUCCESS &&
            aclrtMemcpy(&failures, 4, result, 4, ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        std::cout << "b026_cmath_failures=" << failures << '\n';
        passed = passed && failures == 0;
    }
    if (result)
        passed = runtime.free_device(result) == ACL_SUCCESS && passed;
    if (stream)
        passed = runtime.destroy_stream(stream) == ACL_SUCCESS && passed;
    passed = runtime.reset_device(0) == ACL_SUCCESS && passed;
    passed = runtime.finalize() == ACL_SUCCESS && passed;
    passed = runtime.finish(passed) == 0;
    if (passed)
        std::cout << "ASC_STL_B026_CMATH_HARDWARE_PASS\n";
    return passed ? 0 : 1;
}
