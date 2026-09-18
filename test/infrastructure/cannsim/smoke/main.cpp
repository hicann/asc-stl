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

#include <cstddef>
#include <cstdint>
#include <iostream>

#include "acl_runtime.h"
#include "launcher.h"

namespace {

constexpr size_t kElementCount = 64;
constexpr size_t kByteCount = kElementCount * sizeof(int32_t);

struct Main {
public:
    bool Allocate(asc_stl_test::AclRuntime* runtime)
    {
        return runtime->AllocateHost(reinterpret_cast<void**>(&host_x_), kByteCount, "aclrtFreeHost(host_x)") &&
            runtime->AllocateHost(reinterpret_cast<void**>(&host_y_), kByteCount, "aclrtFreeHost(host_y)") &&
            runtime->AllocateHost(reinterpret_cast<void**>(&host_output_), kByteCount, "aclrtFreeHost(host_output)") &&
            runtime->AllocateDevice(&device_x_, kByteCount, "aclrtFree(device_x)") &&
            runtime->AllocateDevice(&device_y_, kByteCount, "aclrtFree(device_y)") &&
            runtime->AllocateDevice(&device_output_, kByteCount, "aclrtFree(device_output)");
    }

    bool Run(aclrtStream stream)
    {
        InitializeInput();
        return CopyInput() && Launch(stream) && CopyOutput(stream) && Verify();
    }

private:
    void InitializeInput()
    {
        for (size_t index = 0; index < kElementCount; ++index) {
            host_x_[index] = static_cast<int32_t>(index * 3) - 41;
            host_y_[index] = 107 - static_cast<int32_t>(index * 2);
            host_output_[index] = 0;
        }
    }

    bool CopyInput() const
    {
        const aclError copy_x = aclrtMemcpy(device_x_, kByteCount, host_x_, kByteCount, ACL_MEMCPY_HOST_TO_DEVICE);
        const aclError copy_y = aclrtMemcpy(device_y_, kByteCount, host_y_, kByteCount, ACL_MEMCPY_HOST_TO_DEVICE);
        return asc_stl_test::CheckAcl(copy_x, "aclrtMemcpy(H2D x)") &&
            asc_stl_test::CheckAcl(copy_y, "aclrtMemcpy(H2D y)");
    }

    bool Launch(aclrtStream stream) const
    {
        return asc_stl_test::CheckAcl(
            launch_asc_stl_cannsim_add(stream, device_x_, device_y_, device_output_), "asc_stl_cannsim_add launch");
    }

    bool CopyOutput(aclrtStream stream) const
    {
        return asc_stl_test::CheckAcl(aclrtSynchronizeStream(stream), "aclrtSynchronizeStream") &&
            asc_stl_test::CheckAcl(
                aclrtMemcpy(host_output_, kByteCount, device_output_, kByteCount, ACL_MEMCPY_DEVICE_TO_HOST),
                "aclrtMemcpy(D2H output)");
    }

    bool Verify() const
    {
        for (size_t index = 0; index < kElementCount; ++index) {
            const int32_t expected = host_x_[index] + host_y_[index];
            if (host_output_[index] != expected) {
                std::cerr << "Mismatch at " << index << ": got " << host_output_[index] << ", expected " << expected
                          << '\n';
                return false;
            }
        }
        return true;
    }

    int32_t* host_x_ = nullptr;
    int32_t* host_y_ = nullptr;
    int32_t* host_output_ = nullptr;
    void* device_x_ = nullptr;
    void* device_y_ = nullptr;
    void* device_output_ = nullptr;
};

}  // namespace

int main()
{
    Main test_case;
    return asc_stl_test::RunCannsimCase(&test_case, "ASC_STL_CANNSIM_SMOKE_PASS");
}
