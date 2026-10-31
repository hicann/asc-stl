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

#ifndef ASC_STL_EXAMPLES_ACL_CLEANUP_H
#define ASC_STL_EXAMPLES_ACL_CLEANUP_H

#include <acl/acl.h>
#include <cstdio>

struct DeviceExampleState {
    bool initialized = false;
    bool selected = false;
    bool pending = false;
};

inline bool finish_device_example(
    const DeviceExampleState& state, aclrtStream stream, void* output, void* input = nullptr)
{
    bool passed = !state.pending;
    if (!state.pending) {
        if (input != nullptr)
            passed = aclrtFree(input) == ACL_SUCCESS && passed;
        if (output != nullptr)
            passed = aclrtFree(output) == ACL_SUCCESS && passed;
        if (stream != nullptr)
            passed = aclrtDestroyStream(stream) == ACL_SUCCESS && passed;
    }
    if (state.selected)
        passed = aclrtResetDevice(0) == ACL_SUCCESS && passed;
    if (state.initialized)
        passed = aclFinalize() == ACL_SUCCESS && passed;
    std::printf("cleanup_passed=%d\n", passed ? 1 : 0);
    return passed;
}

#endif  // ASC_STL_EXAMPLES_ACL_CLEANUP_H
