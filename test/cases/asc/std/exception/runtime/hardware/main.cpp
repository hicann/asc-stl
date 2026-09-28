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
    if (aclInit(nullptr) != ACL_SUCCESS)
        return 2;
    if (aclrtSetDevice(0) != ACL_SUCCESS) {
        aclFinalize();
        return 2;
    }
    int* output = nullptr;
    aclrtStream stream = nullptr;
    bool ready =
        aclrtMalloc(reinterpret_cast<void**>(&output), sizeof(int), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS;
    aclError control_status = static_cast<aclError>(-1);
    aclError fault_status = static_cast<aclError>(-1);
    int control_value = 0;
    if (ready) {
        launch_terminate_control(output, stream);
        control_status = aclrtSynchronizeStream(stream);
        ready = control_status == ACL_SUCCESS &&
            aclrtMemcpy(&control_value, sizeof(control_value), output, sizeof(control_value),
                ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS &&
            control_value == 7;
    }
    if (ready) {
        launch_terminate_fault(output, stream);
        fault_status = aclrtSynchronizeStream(stream);
    }
    const bool passed = ready && fault_status != ACL_SUCCESS;
    std::cout << "terminate_control=" << control_value << " fault_sync_status=" << fault_status << '\n';
    if (stream)
        aclrtDestroyStream(stream);
    if (output)
        aclrtFree(output);
    aclrtResetDevice(0);
    aclFinalize();
    return passed ? 0 : 1;
}
