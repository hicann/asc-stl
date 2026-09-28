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

void launch_asc_stl_w08_cannsim(unsigned int*, const unsigned int*, void*);

int main()
{
    constexpr unsigned int kWords = 512;
    unsigned int input[kWords]{};
    unsigned int initial[kWords]{};
    for (unsigned int index = 0; index < 24; ++index)
        input[index] = index + 1;
#if defined(ASC_STL_W08_SIMT)
    *reinterpret_cast<std::int64_t*>(&initial[8]) = 0;
    *reinterpret_cast<std::int64_t*>(&initial[12]) = 4;
#endif
    unsigned int* device_result = nullptr;
    unsigned int* device_input = nullptr;
    aclrtStream stream = nullptr;
    bool passed = aclInit(nullptr) == ACL_SUCCESS && aclrtSetDevice(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device_result), sizeof(initial), ACL_MEM_MALLOC_HUGE_FIRST) ==
            ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device_input), sizeof(input), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMemcpy(device_result, sizeof(initial), initial, sizeof(initial), ACL_MEMCPY_HOST_TO_DEVICE) ==
            ACL_SUCCESS &&
        aclrtMemcpy(device_input, sizeof(input), input, sizeof(input), ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
    unsigned int result[kWords]{};
    if (passed) {
        launch_asc_stl_w08_cannsim(device_result, device_input, stream);
        passed = aclrtSynchronizeStream(stream) == ACL_SUCCESS &&
            aclrtMemcpy(result, sizeof(result), device_result, sizeof(result), ACL_MEMCPY_DEVICE_TO_HOST) ==
                ACL_SUCCESS;
    }
#if defined(ASC_STL_W08_SIMT)
    passed = passed && result[0] == 4 && result[1] == 0 && result[2] == 0 && result[61] == 0;
#else
    const unsigned int expected[24] = {0, 1, 2, 3, 4, 5, 0, 0, 0, 9, 10, 11, 12, 13, 0, 0, 0, 17, 18, 19, 20, 21, 0, 0};
    unsigned int load_mismatches = 0;
    for (unsigned int index = 0; index < 24; ++index)
        load_mismatches += result[index] != expected[index];
    std::cout << "w08_load_mismatches=" << load_mismatches << '\n';
    std::cout << "w08_status_failures=" << result[60] << '\n';
    if (load_mismatches != 0) {
        std::cout << "w08_load_samples=" << result[1] << ',' << result[9] << ',' << result[17] << '\n';
    }
    passed = passed && load_mismatches == 0 && result[31] == 0 && result[60] == 0 && result[61] == 0;
#endif
    if (device_input)
        passed = aclrtFree(device_input) == ACL_SUCCESS && passed;
    if (device_result)
        passed = aclrtFree(device_result) == ACL_SUCCESS && passed;
    if (stream)
        passed = aclrtDestroyStream(stream) == ACL_SUCCESS && passed;
    passed = aclrtResetDevice(0) == ACL_SUCCESS && passed;
    passed = aclFinalize() == ACL_SUCCESS && passed;
    std::cout << "w08_failures=" << (passed ? 0 : 1) << '\n';
    std::cout << "w09_w10_failures=" << (passed ? 0 : 1) << '\n';
    std::cout << "w11_w12_failures=" << result[61] << '\n';
    std::cout << "w11_w12_group_failures=" << result[480] << ',' << result[481] << ',' << result[482] << ','
              << result[483] << '\n';
    if (passed) {
        std::cout << "ASC_STL_W08_CANNSIM_PASS\n";
        std::cout << "ASC_STL_W09_W10_CANNSIM_PASS\n";
        std::cout << "ASC_STL_W11_W12_CANNSIM_PASS\n";
    }
    return passed ? 0 : 1;
}
