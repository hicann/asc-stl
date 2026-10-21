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

/* Copyright 2026 湖北多样性算力应用创新研究院. Licensed under Apache-2.0. */
#include <acl/acl.h>
#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include "../../../../../support/hardware_runtime.h"
#include "launch.h"
#if defined(ASC_STL_ATOMIC_SIMD)
int main()
{
    asc_stl_test::hardware_runtime runtime;
    std::cout << "NOT_APPLICABLE: scoped atomic runtime is D-SIMT-only\n";
    return 0;
}
#else

int main()
{
    asc_stl_test::hardware_runtime runtime;
    constexpr std::array<std::int32_t, 16> expected = {11, 10, 15, 12, 1, 12, 8, 13, 14, 4, 9, 9, 11, 10, 1, 11};
    std::array<std::int32_t, 21> actual{};
    std::int32_t* device = nullptr;
    aclrtStream stream = nullptr;
    bool passed = runtime.initialize(nullptr) == ACL_SUCCESS && runtime.set_device(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device), sizeof(actual), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMemcpy(device, sizeof(actual), actual.data(), sizeof(actual), ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
    if (passed && runtime.ready()) {
        launch_asc_stl_atomic_simt(device, stream);
        passed = runtime.synchronize(stream) == ACL_SUCCESS &&
            aclrtMemcpy(actual.data(), sizeof(actual), device, sizeof(actual), ACL_MEMCPY_DEVICE_TO_HOST) ==
                ACL_SUCCESS &&
            std::equal(expected.begin(), expected.end(), actual.begin()) && actual[17] == 20000 &&
            actual[18] == 20000 && actual[19] == 0 && actual[20] == 0;
    }
    if (device != nullptr)
        passed = runtime.free_device(device) == ACL_SUCCESS && passed;
    if (stream != nullptr)
        passed = runtime.destroy_stream(stream) == ACL_SUCCESS && passed;
    passed = runtime.reset_device(0) == ACL_SUCCESS && passed;
    passed = runtime.finalize() == ACL_SUCCESS && passed;
    passed = runtime.finish(passed) == 0;
    std::cout << "scoped_atomic_published=" << actual[17] << " acknowledged=" << actual[18]
              << " visibility_failures=" << actual[19] << " timeouts=" << actual[20] << '\n';
    std::cout << (passed ? "PASS" : "FAIL") << ": D-SIMT scoped atomic hardware semantics\n";
    return passed ? 0 : 1;
}
#endif
