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
#include "../../../../../../support/b022_runtime_inputs.h"
#include "../../../../../../support/hardware_runtime.h"
#include "launch.h"

int main()
{
    asc_stl_test::hardware_runtime runtime;
    int results[64] = {};
    asc_stl_b022_runtime_inputs::initialize(results);
    int* device = nullptr;
    aclrtStream stream = nullptr;
    const size_t bytes = sizeof(results);
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device), bytes, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMemcpy(device, bytes, results, bytes, ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
    if (passed && runtime.ready()) {
        launch_asc_stl_b022(device, stream);
        const aclError synchronized = runtime.synchronize(stream);
        const aclError copied = synchronized == ACL_SUCCESS ?
            aclrtMemcpy(results, bytes, device, bytes, ACL_MEMCPY_DEVICE_TO_HOST) :
            synchronized;
        std::cout << "synchronize_status=" << synchronized << " copy_status=" << copied << '\n';
        passed = synchronized == ACL_SUCCESS && copied == ACL_SUCCESS;
        const bool inputs_unchanged = passed && asc_stl_b022_runtime_inputs::unchanged(results);
        std::cout << "runtime_inputs_unchanged=" << inputs_unchanged << '\n';
        std::cout << "atomic_failures=" << results[31] << " algorithm_failures=" << results[32] << '\n';
        std::cout << "standard_atomic_published=" << results[41] << " acknowledged=" << results[42]
                  << " visibility_failures=" << results[43] << " timeouts=" << results[44] << '\n';
        passed = passed && inputs_unchanged && results[31] == 0 && results[32] == 0;
#if ASC_STL_B022_SIMT
        passed = passed && results[41] == 20000 && results[42] == 20000 && results[43] == 0 && results[44] == 0;
#else
        passed = passed && results[41] == 0 && results[42] == 0 && results[43] == 0 && results[44] == 0;
#endif
    }
    if (device)
        passed = runtime.free_device(device) == ACL_SUCCESS && passed;
    if (stream)
        passed = runtime.destroy_stream(stream) == ACL_SUCCESS && passed;
    passed = runtime.reset_device(0) == ACL_SUCCESS && passed;
    passed = runtime.finalize() == ACL_SUCCESS && passed;
    passed = runtime.finish(passed) == 0;
    std::cout << (passed ? "PASS" : "FAIL") << ": B022 Device semantics\n";
    return passed ? 0 : 1;
}
