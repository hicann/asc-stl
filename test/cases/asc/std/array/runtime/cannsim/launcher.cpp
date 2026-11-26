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

#include "../semantics.h"

void launch_asc_stl_standard(asc_stl_standard_runtime::test_data* io, aclrtStream stream, int selected);

namespace asc_stl_standard_runtime {

bool run(test_data& data, int selected)
{
    test_data* device = nullptr;
    aclrtStream stream = nullptr;
    const bool initialized = aclInit(nullptr) == ACL_SUCCESS;
    const bool device_selected = initialized && aclrtSetDevice(0) == ACL_SUCCESS;
    bool passed = device_selected && aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&device), sizeof(data), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMemcpy(device, sizeof(data), &data, sizeof(data), ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
    if (passed) {
        launch_asc_stl_standard(device, stream, selected);
        passed = aclrtSynchronizeStream(stream) == ACL_SUCCESS &&
            aclrtMemcpy(&data, sizeof(data), device, sizeof(data), ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
    }

    if (device)
        passed = (aclrtFree(device) == ACL_SUCCESS) && passed;
    if (stream)
        passed = (aclrtDestroyStream(stream) == ACL_SUCCESS) && passed;
    if (device_selected)
        passed = (aclrtResetDevice(0) == ACL_SUCCESS) && passed;
    if (initialized)
        passed = (aclFinalize() == ACL_SUCCESS) && passed;
    return passed;
}

}  // namespace asc_stl_standard_runtime
