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

#include "launch.h"

int main()
{
    constexpr unsigned int kWords = 512;
    unsigned int initial[kWords]{};
    unsigned int result[kWords]{};
    unsigned int* device_result = nullptr;
    aclrtStream stream = nullptr;
    const int init_code = aclInit(nullptr);
    const int set_device_code = init_code == ACL_SUCCESS ? aclrtSetDevice(0) : -1;
    const int create_stream_code = set_device_code == ACL_SUCCESS ? aclrtCreateStream(&stream) : -1;
    const int malloc_code = create_stream_code == ACL_SUCCESS ?
        aclrtMalloc(reinterpret_cast<void**>(&device_result), sizeof(initial), ACL_MEM_MALLOC_HUGE_FIRST) :
        -1;
    const int host_to_device_code = malloc_code == ACL_SUCCESS ?
        aclrtMemcpy(device_result, sizeof(initial), initial, sizeof(initial), ACL_MEMCPY_HOST_TO_DEVICE) :
        -1;
    int synchronize_codes[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
    int device_to_host_code = -1;
    if (host_to_device_code == ACL_SUCCESS) {
#if defined(ASC_STL_W13_W14_SIMT)
        using launch_function = void (*)(unsigned int*, void*);
        const launch_function launches[9] = {launch_asc_stl_w13_w14_utility, launch_asc_stl_w13_w14_bit,
            launch_asc_stl_w13_w14_types, launch_asc_stl_w13_w14_cwide_length, launch_asc_stl_w13_w14_cwide_search,
            launch_asc_stl_w13_w14_linalg, launch_asc_stl_w13_w14_random, launch_asc_stl_w13_w14_numeric,
            launch_asc_stl_w13_w14_sync};
        for (unsigned int index = 0; index < 9; ++index) {
            launches[index](device_result, stream);
            synchronize_codes[index] = aclrtSynchronizeStream(stream);
            if (synchronize_codes[index] != ACL_SUCCESS) {
                break;
            }
        }
#else
        launch_asc_stl_w13_w14(device_result, stream);
        synchronize_codes[0] = aclrtSynchronizeStream(stream);
#endif
        device_to_host_code =
            aclrtMemcpy(result, sizeof(result), device_result, sizeof(result), ACL_MEMCPY_DEVICE_TO_HOST);
    }
    int synchronize_code = ACL_SUCCESS;
    for (int code : synchronize_codes) {
        if (code > ACL_SUCCESS) {
            synchronize_code = code;
        }
    }
    bool passed = init_code == ACL_SUCCESS && set_device_code == ACL_SUCCESS && create_stream_code == ACL_SUCCESS &&
        malloc_code == ACL_SUCCESS && host_to_device_code == ACL_SUCCESS && synchronize_code == ACL_SUCCESS &&
        device_to_host_code == ACL_SUCCESS;
    unsigned int failures = 0;
    for (unsigned int index = 0; index < 5; ++index) {
        failures += result[index];
    }
    passed = passed && failures == 0;
    const int free_code = device_result == nullptr ? ACL_SUCCESS : aclrtFree(device_result);
    const int destroy_stream_code = stream == nullptr ? ACL_SUCCESS : aclrtDestroyStream(stream);
    const int reset_device_code = aclrtResetDevice(0);
    const int finalize_code = aclFinalize();
    passed = free_code == ACL_SUCCESS && destroy_stream_code == ACL_SUCCESS && reset_device_code == ACL_SUCCESS &&
        finalize_code == ACL_SUCCESS && passed;
    std::cout << "w13_w14_failures=" << failures << '\n';
    std::cout << "w13_w14_group_failures=" << result[0] << ',' << result[1] << ',' << result[2] << ',' << result[3]
              << ',' << result[4] << '\n';
    std::cout << "w13_w14_cleanup_codes=" << free_code << ',' << destroy_stream_code << ',' << reset_device_code << ','
              << finalize_code << '\n';
    std::cout << "w13_w14_runtime_codes=" << init_code << ',' << set_device_code << ',' << create_stream_code << ','
              << malloc_code << ',' << host_to_device_code << ',' << synchronize_code << ',' << device_to_host_code
              << '\n';
    std::cout << "w13_w14_kernel_codes=" << synchronize_codes[0] << ',' << synchronize_codes[1] << ','
              << synchronize_codes[2] << ',' << synchronize_codes[3] << ',' << synchronize_codes[4] << ','
              << synchronize_codes[5] << ',' << synchronize_codes[6] << ',' << synchronize_codes[7] << ','
              << synchronize_codes[8] << '\n';
    if (passed) {
        std::cout << "ASC_STL_W13_W14_HARDWARE_PASS\n";
    }
    return passed ? 0 : 1;
}
