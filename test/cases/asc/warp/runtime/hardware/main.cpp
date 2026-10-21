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
#include "../../../../../support/hardware_runtime.h"
#include "../semantics.h"
int main()
{
    asc_stl_test::hardware_runtime runtime;
    int actual[136] = {0, 0, std::getenv("ASC_STL_WARP_INJECT_FAILURE") == nullptr ? 0 : 1};
    int* device = nullptr;
    aclrtStream stream = nullptr;
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device), sizeof(actual), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMemcpy(device, sizeof(actual), actual, sizeof(actual), ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
    if (passed && runtime.ready()) {
        launch_asc_stl_b017(device, stream);
        passed = runtime.synchronize(stream) == ACL_SUCCESS &&
            aclrtMemcpy(actual, sizeof(actual), device, sizeof(actual), ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS &&
            actual[4] == ASC_STL_ATOMIC_VISIBILITY_ROUNDS && actual[5] == ASC_STL_ATOMIC_VISIBILITY_ROUNDS &&
            actual[6] == 0 && actual[7] == 0;
#if defined(ASC_STL_B017_simt)
        passed = passed && actual[1] == 4;
#endif
    }
    if (device)
        passed = runtime.free_device(device) == ACL_SUCCESS && passed;
    if (stream)
        passed = runtime.destroy_stream(stream) == ACL_SUCCESS && passed;
    passed = runtime.reset_device(0) == ACL_SUCCESS && passed;
    passed = runtime.finalize() == ACL_SUCCESS && passed;
    std::cout << "warp_failures=" << actual[0] << " warp_count=" << actual[1] << " inject=" << actual[2]
              << " published=" << actual[4] << " acknowledged=" << actual[5] << " visibility_failures=" << actual[6]
              << " timeouts=" << actual[7] << '\n';
    const bool injected = actual[2] != 0;
    bool expected_failures = actual[0] == (injected ? 4 : 0);
    for (unsigned int index = 8; index < 136; ++index) {
        const int expected = injected && (index - 8) % 32 == 1 ? 1 << 13 : 0;
        expected_failures = expected_failures && actual[index] == expected;
        if (actual[index] != 0)
            std::cout << "lane_failure index=" << index - 8 << " count=" << actual[index] << '\n';
    }
    const int result = runtime.finish(passed && expected_failures);
    if (injected && result == 0) {
        std::cout << "ASC_STL_EXPECTED_WARP_FAILURE_VERIFIED" << std::endl;
        return 42;
    }
    std::cout << (result == 0 ? "PASS" : "FAIL") << ": B017 warp/atomic Device semantics\n";
    return result;
}
