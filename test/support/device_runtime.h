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

#ifndef ASC_STL_TEST_DEVICE_RUNTIME_H
#define ASC_STL_TEST_DEVICE_RUNTIME_H

#include <iostream>

#if defined(ASC_STL_TEST_CANNSIM)
#include <acl/acl.h>

namespace asc_stl_test {
// Simulator entry only: hardware timeout-control tasks are unsupported by camodel.
// The external cannsim runner imposes the process deadline.
class device_runtime {
public:
    aclError initialize(const char* config)
    {
        return aclInit(config);
    }
    aclError set_device(int device)
    {
        return aclrtSetDevice(device);
    }
    bool ready() const
    {
        return true;
    }
    aclError synchronize(aclrtStream stream)
    {
        return aclrtSynchronizeStream(stream);
    }
    aclError free_device(void* memory)
    {
        return aclrtFree(memory);
    }
    aclError destroy_stream(aclrtStream stream)
    {
        return aclrtDestroyStream(stream);
    }
    aclError reset_device(int device)
    {
        return aclrtResetDevice(device);
    }
    aclError finalize()
    {
        return aclFinalize();
    }
    int finish(bool passed)
    {
        std::cout << "ASC_STL_SIMULATION cleanup_passed=" << passed << '\n';
        return passed ? 0 : 1;
    }
};
}  // namespace asc_stl_test
#else
#include "hardware_runtime.h"
namespace asc_stl_test {
using device_runtime = hardware_runtime;
}  // namespace asc_stl_test
#endif

#endif  // ASC_STL_TEST_DEVICE_RUNTIME_H
