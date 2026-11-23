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

#ifndef ASC_STL_TEST_BIT_SIMULATION_RUNTIME_H
#define ASC_STL_TEST_BIT_SIMULATION_RUNTIME_H

#include <acl/acl.h>
#include <iostream>

// Simulator-only adapter, matching the existing cannsim test entrypoints.
// The CTest/runner process deadline bounds software emulation. Real hardware
// uses hardware_runtime and its operation/stream timeouts instead.
class bit_simulation_runtime {
    bool failed_ = false;
    bool synchronization_failed_ = false;
    bool initialized_ = false;
    bool selected_ = false;

    aclError check(aclError status, const char* operation)
    {
        if (status != ACL_SUCCESS) {
            failed_ = true;
            std::cerr << operation << " status=" << status << '\n';
        }
        return status;
    }

public:
    aclError initialize(const char* config)
    {
        const auto status = check(aclInit(config), "aclInit");
        initialized_ = status == ACL_SUCCESS;
        return status;
    }
    aclError set_device(int device)
    {
        const auto status = check(aclrtSetDevice(device), "aclrtSetDevice");
        selected_ = status == ACL_SUCCESS;
        return status;
    }
    bool ready() const
    {
        return !failed_;
    }
    aclError synchronize(aclrtStream stream)
    {
        const auto status = check(aclrtSynchronizeStream(stream), "aclrtSynchronizeStream");
        synchronization_failed_ = status != ACL_SUCCESS;
        return status;
    }
    aclError free_device(void* value)
    {
        return synchronization_failed_ ? static_cast<aclError>(-1) : check(aclrtFree(value), "aclrtFree");
    }
    aclError destroy_stream(aclrtStream stream)
    {
        return synchronization_failed_ ? static_cast<aclError>(-1) :
                                         check(aclrtDestroyStream(stream), "aclrtDestroyStream");
    }
    aclError reset_device(int device)
    {
        if (!selected_)
            return ACL_SUCCESS;
        selected_ = false;
        return check(aclrtResetDevice(device), "aclrtResetDevice");
    }
    aclError finalize()
    {
        if (!initialized_)
            return ACL_SUCCESS;
        initialized_ = false;
        return check(aclFinalize(), "aclFinalize");
    }
    int finish(bool passed) const
    {
        return passed && !failed_ && !initialized_ && !selected_ ? 0 : 1;
    }
};

#endif  // ASC_STL_TEST_BIT_SIMULATION_RUNTIME_H
