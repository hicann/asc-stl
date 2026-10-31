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

#include <iostream>

#include "../../common/acl_cleanup.h"

#include "example.h"

int main()
{
    unsigned int actual[256]{};
    unsigned int input[256]{};
    for (unsigned int index = 0; index < 256; ++index)
        input[index] = index;
    unsigned int* storage = nullptr;
    unsigned int* device = nullptr;
    aclrtStream stream = nullptr;
    DeviceExampleState state;
    state.initialized = aclInit(nullptr) == ACL_SUCCESS;
    state.selected = state.initialized && aclrtSetDevice(0) == ACL_SUCCESS;
    bool passed = state.selected;
    passed = passed && aclrtSetOpExecuteTimeOut(10) == ACL_SUCCESS;
    passed = passed && aclrtCreateStream(&stream) == ACL_SUCCESS;
    passed = passed &&
        aclrtMalloc(reinterpret_cast<void**>(&device), sizeof(actual), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    passed = passed &&
        aclrtMalloc(reinterpret_cast<void**>(&storage), sizeof(input), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS;
    passed =
        passed && aclrtMemcpy(storage, sizeof(input), input, sizeof(input), ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
    passed = passed && aclrtMemset(device, sizeof(actual), 0xa5, sizeof(actual)) == ACL_SUCCESS;
    if (passed) {
        state.pending = true;
        launch_example(device, storage, stream);
        passed = aclrtSynchronizeStreamWithTimeout(stream, 10000) == ACL_SUCCESS;
        state.pending = !passed;
        passed = passed &&
            aclrtMemcpy(actual, sizeof(actual), device, sizeof(actual), ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        for (unsigned int index = 0; index < 256; ++index)
            passed = passed && actual[index] == index + 1U;
    }
    passed = finish_device_example(state, stream, device, storage) && passed;
    std::cout << (passed ? "PASS" : "FAIL") << ": pipeline_copy\n";
    return passed ? 0 : 1;
}
