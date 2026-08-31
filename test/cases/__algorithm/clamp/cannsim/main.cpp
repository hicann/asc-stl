/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#include <cmath>
#include <cstddef>
#include <iostream>

#include "acl_runtime.h"
#include "launcher.h"

namespace {

constexpr size_t kElementCount = 64;
constexpr size_t kByteCount = kElementCount * sizeof(float);

struct Main {
public:
    bool Allocate(asc_stl_test::AclRuntime* runtime)
    {
        return AllocateHost(runtime) && AllocateDevice(runtime);
    }

    bool Run(aclrtStream stream)
    {
        InitializeInput();
        if (!CopyInput() || !Launch(stream) || !CopyOutput(stream)) {
            return false;
        }
        return Verify();
    }

private:
    bool AllocateHost(asc_stl_test::AclRuntime* runtime)
    {
        return runtime->AllocateHost(reinterpret_cast<void**>(&host_input_), kByteCount, "aclrtFreeHost(host_input)") &&
            runtime->AllocateHost(
                reinterpret_cast<void**>(&host_default_output_), kByteCount, "aclrtFreeHost(host_default_output)") &&
            runtime->AllocateHost(reinterpret_cast<void**>(&host_comparator_output_), kByteCount,
                "aclrtFreeHost(host_comparator_output)");
    }

    bool AllocateDevice(asc_stl_test::AclRuntime* runtime)
    {
        return runtime->AllocateDevice(&device_input_, kByteCount, "aclrtFree(device_input)") &&
            runtime->AllocateDevice(&device_default_output_, kByteCount, "aclrtFree(device_default_output)") &&
            runtime->AllocateDevice(&device_comparator_output_, kByteCount, "aclrtFree(device_comparator_output)");
    }

    void InitializeInput()
    {
        constexpr float values[] = {-20.0F, 10.0F, 25.0F, 100.0F, 140.0F, 55.0F, 0.0F, 75.0F};
        constexpr size_t kValueCount = sizeof(values) / sizeof(values[0]);
        for (size_t index = 0; index < kElementCount; ++index) {
            host_input_[index] = values[index % kValueCount];
            host_default_output_[index] = 0.0F;
            host_comparator_output_[index] = 0.0F;
        }
    }

    bool CopyInput() const
    {
        return asc_stl_test::CheckAcl(
            aclrtMemcpy(device_input_, kByteCount, host_input_, kByteCount, ACL_MEMCPY_HOST_TO_DEVICE),
            "aclrtMemcpy(H2D input)");
    }

    bool Launch(aclrtStream stream) const
    {
        return asc_stl_test::CheckAcl(
            launch_asc_stl_cannsim_clamp(stream, device_input_, device_default_output_, device_comparator_output_),
            "asc_stl_cannsim_clamp launch");
    }

    bool CopyOutput(aclrtStream stream) const
    {
        return asc_stl_test::CheckAcl(aclrtSynchronizeStream(stream), "aclrtSynchronizeStream") &&
            CopyOneOutput(host_default_output_, device_default_output_, "aclrtMemcpy(D2H default output)") &&
            CopyOneOutput(host_comparator_output_, device_comparator_output_, "aclrtMemcpy(D2H comparator output)");
    }

    static bool CopyOneOutput(float* host, void* device, const char* operation)
    {
        return asc_stl_test::CheckAcl(
            aclrtMemcpy(host, kByteCount, device, kByteCount, ACL_MEMCPY_DEVICE_TO_HOST), operation);
    }

    bool Verify() const
    {
        size_t mismatches = 0;
        for (size_t index = 0; index < kElementCount; ++index) {
            mismatches += CheckDefault(index);
            mismatches += CheckComparator(index);
        }
        if (mismatches != 0) {
            std::cerr << "clamp checked " << kElementCount << " elements per overload, mismatches " << mismatches
                      << '\n';
            return false;
        }
        std::cout << "clamp checked " << kElementCount << " elements per overload, mismatches 0\n";
        return true;
    }

    size_t CheckDefault(size_t index) const
    {
        const float value = host_input_[index];
        const float expected = value < 10.0F ? 10.0F : (100.0F < value ? 100.0F : value);
        return ReportMismatch(index, "default", host_default_output_[index], expected);
    }

    size_t CheckComparator(size_t index) const
    {
        const float value = host_input_[index];
        const float expected = value > 100.0F ? 100.0F : (10.0F > value ? 10.0F : value);
        return ReportMismatch(index, "comparator", host_comparator_output_[index], expected);
    }

    static size_t ReportMismatch(size_t index, const char* output, float actual, float expected)
    {
        if (std::fabs(actual - expected) <= 1e-5F) {
            return 0;
        }
        std::cerr << "Mismatch at " << index << ' ' << output << " output: got " << actual << ", expected " << expected
                  << '\n';
        return 1;
    }

    float* host_input_ = nullptr;
    float* host_default_output_ = nullptr;
    float* host_comparator_output_ = nullptr;
    void* device_input_ = nullptr;
    void* device_default_output_ = nullptr;
    void* device_comparator_output_ = nullptr;
};

}  // namespace

int main()
{
    Main test_case;
    return asc_stl_test::RunCannsimCase(&test_case, "ASC_STL_CANNSIM_CLAMP_PASS");
}
