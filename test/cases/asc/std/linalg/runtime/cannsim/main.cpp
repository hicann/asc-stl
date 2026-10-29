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

#include "support/bit_count_reference.h"

void launch_asc_stl_w13_w14(unsigned int*, void*);

int main()
{
    constexpr unsigned int kWords = 512;
    unsigned int initial[kWords]{};
    asc_stl_bit_count_test::initialize_runtime(initial);
    const unsigned int comparison_input[11] = {0, 1, 2, 3, 0, 1, 2, 0, 1, 1, 2};
    for (unsigned int index = 0; index < 11; ++index) {
        initial[32 + index] = comparison_input[index];
    }
    unsigned int result[kWords]{};
    unsigned int* device_result = nullptr;
    aclrtStream stream = nullptr;
    bool passed = aclInit(nullptr) == ACL_SUCCESS && aclrtSetDevice(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device_result), sizeof(initial), ACL_MEM_MALLOC_HUGE_FIRST) ==
            ACL_SUCCESS &&
        aclrtMemcpy(device_result, sizeof(initial), initial, sizeof(initial), ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
    if (passed) {
        launch_asc_stl_w13_w14(device_result, stream);
        passed = aclrtSynchronizeStream(stream) == ACL_SUCCESS &&
            aclrtMemcpy(result, sizeof(result), device_result, sizeof(result), ACL_MEMCPY_DEVICE_TO_HOST) ==
                ACL_SUCCESS;
    }
    unsigned int failures = 0;
    for (unsigned int index = 0; index < 5; ++index) {
        failures += result[index];
    }
    passed = passed && failures == 0 && result[11] == 358 && result[12] == 66;
#if !defined(ASC_STL_W13_W14_SYNC_ONLY)
    const unsigned int bit_count_failures = asc_stl_bit_count_test::runtime_failures(result);
    passed = passed && bit_count_failures == 0;
#endif
    if (device_result != nullptr) {
        passed = aclrtFree(device_result) == ACL_SUCCESS && passed;
    }
    if (stream != nullptr) {
        passed = aclrtDestroyStream(stream) == ACL_SUCCESS && passed;
    }
    passed = aclrtResetDevice(0) == ACL_SUCCESS && passed;
    passed = aclFinalize() == ACL_SUCCESS && passed;
    std::cout << "w13_w14_failures=" << failures << '\n';
#if !defined(ASC_STL_W13_W14_SYNC_ONLY)
    std::cout << "w13_w14_bit_count_observation=" << result[13] << ',' << bit_count_failures << '\n';
#endif
    std::cout << "w13_w14_comparison_observation=" << result[11] << ',' << result[12] << '\n';
    std::cout << "w13_w14_group_failures=" << result[0] << ',' << result[1] << ',' << result[2] << ',' << result[3]
              << ',' << result[4] << '\n';
    std::cout << "w13_w14_foundation_failures=" << result[5] << ',' << result[6] << ',' << result[7] << '\n';
    std::cout << "w13_w14_type_cwide_failures=" << result[8] << ',' << result[9] << '\n';
    if (passed) {
        std::cout << "ASC_STL_W13_W14_CANNSIM_PASS\n";
    }
    return passed ? 0 : 1;
}
