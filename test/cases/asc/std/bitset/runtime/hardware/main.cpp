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
#include "../../../../../../support/hardware_runtime.h"
#include "launch.h"

int main()
{
    asc_stl_test::hardware_runtime runtime;
    unsigned int* device = nullptr;
    aclrtStream stream = nullptr;
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device), sizeof(unsigned int), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    unsigned int result = 1;
    if (passed && runtime.ready()) {
        launch_asc_stl_b027_simd(device, stream);
        passed = runtime.synchronize(stream) == ACL_SUCCESS &&
            aclrtMemcpy(&result, sizeof(result), device, sizeof(result), ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS &&
            result == 0;
    }
    if (device)
        passed = runtime.free_device(device) == ACL_SUCCESS && passed;
    if (stream)
        passed = runtime.destroy_stream(stream) == ACL_SUCCESS && passed;
    passed = runtime.reset_device(0) == ACL_SUCCESS && passed;
    passed = runtime.finalize() == ACL_SUCCESS && passed;
    passed = runtime.finish(passed) == 0;
    if (passed)
        std::cout << "ASC_STL_B027_HARDWARE_PASS\n";
    return passed ? 0 : 1;
}
