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
#include "../../../../../support/hardware_runtime.h"
#include "launch.h"

int main()
{
    asc_stl_test::hardware_runtime runtime;
    int results[64] = {};
    int* device = nullptr;
    aclrtStream stream = nullptr;
    const size_t bytes = sizeof(results);
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device), bytes, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    if (passed && runtime.ready()) {
        launch_asc_stl_b023(device, stream);
        passed = runtime.synchronize(stream) == ACL_SUCCESS &&
            aclrtMemcpy(results, bytes, device, bytes, ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        std::cout << "b023_failures=" << results[0] << '\n';
        passed = passed && results[0] == 0;
    }
    if (device)
        passed = runtime.free_device(device) == ACL_SUCCESS && passed;
    if (stream)
        passed = runtime.destroy_stream(stream) == ACL_SUCCESS && passed;
    passed = runtime.reset_device(0) == ACL_SUCCESS && passed;
    passed = runtime.finalize() == ACL_SUCCESS && passed;
    passed = runtime.finish(passed) == 0;
    std::cout << (passed ? "PASS" : "FAIL") << ": B023 Device semantics\n";
    return passed ? 0 : 1;
}
