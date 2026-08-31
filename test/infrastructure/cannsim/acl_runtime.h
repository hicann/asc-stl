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

#ifndef CANN_ASC_STL_TEST_INFRASTRUCTURE_CANNSIM_ACL_RUNTIME_H
#define CANN_ASC_STL_TEST_INFRASTRUCTURE_CANNSIM_ACL_RUNTIME_H

#include <acl/acl.h>

#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace asc_stl_test {

inline bool CheckAcl(aclError result, const char* operation)
{
    if (result == ACL_SUCCESS) {
        return true;
    }
    std::cerr << "ACL error " << result << " from " << operation << '\n';
    return false;
}

class AclRuntime {
public:
    AclRuntime() = default;
    AclRuntime(const AclRuntime&) = delete;
    AclRuntime& operator=(const AclRuntime&) = delete;

    ~AclRuntime()
    {
        (void)Release();
    }

    bool Initialize()
    {
        if (!CheckAcl(aclInit(nullptr), "aclInit")) {
            return false;
        }
        acl_initialized_ = true;
        if (!CheckAcl(aclrtSetDevice(kDeviceId), "aclrtSetDevice")) {
            return InitializationFailed();
        }
        device_set_ = true;
        if (!CheckAcl(aclrtCreateStream(&stream_), "aclrtCreateStream")) {
            return InitializationFailed();
        }
        return true;
    }

    bool AllocateHost(void** address, size_t bytes, const char* name)
    {
        if (!CheckAcl(aclrtMallocHost(address, bytes), name)) {
            return false;
        }
        allocations_.push_back({*address, true, name});
        return true;
    }

    bool AllocateDevice(void** address, size_t bytes, const char* name)
    {
        if (!CheckAcl(aclrtMalloc(address, bytes, ACL_MEM_MALLOC_HUGE_FIRST), name)) {
            return false;
        }
        allocations_.push_back({*address, false, name});
        return true;
    }

    aclrtStream stream() const
    {
        return stream_;
    }

    bool Release()
    {
        bool success = ReleaseAllocations();
        if (stream_ != nullptr) {
            success = CheckAcl(aclrtDestroyStream(stream_), "aclrtDestroyStream") && success;
            stream_ = nullptr;
        }
        if (device_set_) {
            success = CheckAcl(aclrtResetDevice(kDeviceId), "aclrtResetDevice") && success;
            device_set_ = false;
        }
        if (acl_initialized_) {
            success = CheckAcl(aclFinalize(), "aclFinalize") && success;
            acl_initialized_ = false;
        }
        return success;
    }

private:
    struct Allocation {
        void* address;
        bool host;
        const char* name;
    };

    bool InitializationFailed()
    {
        (void)Release();
        return false;
    }

    bool ReleaseAllocations()
    {
        bool success = true;
        for (auto allocation = allocations_.rbegin(); allocation != allocations_.rend(); ++allocation) {
            const aclError result =
                allocation->host ? aclrtFreeHost(allocation->address) : aclrtFree(allocation->address);
            success = CheckAcl(result, allocation->name) && success;
        }
        allocations_.clear();
        return success;
    }

    static constexpr int32_t kDeviceId = 0;
    std::vector<Allocation> allocations_;
    aclrtStream stream_ = nullptr;
    bool device_set_ = false;
    bool acl_initialized_ = false;
};

template <class TestCase>
int RunCannsimCase(TestCase* test_case, const char* pass_marker, const char* success_message = nullptr)
{
    AclRuntime runtime;
    if (!runtime.Initialize() || !test_case->Allocate(&runtime)) {
        return 1;
    }
    const bool semantic_passed = test_case->Run(runtime.stream());
    const bool cleanup_passed = runtime.Release();
    if (!semantic_passed || !cleanup_passed) {
        return 1;
    }
    std::cout << pass_marker << '\n';
    if (success_message != nullptr) {
        std::cout << success_message << '\n';
    }
    return 0;
}

inline int64_t GetPrintSampleCount()
{
    const char* value = std::getenv("KERNEL_PRINT_SAMPLES");
    return value == nullptr || *value == '\0' ? 8 : std::atoll(value);
}

template <class T, size_t InputCount, size_t OutputCount>
class CannsimBuffers {
public:
    explicit CannsimBuffers(size_t element_count) : element_count_(element_count)
    {
        for (auto& input : inputs_) {
            input.resize(element_count);
        }
        for (auto& output : outputs_) {
            output.resize(element_count);
        }
    }

    bool Allocate(AclRuntime* runtime)
    {
        for (void*& input : device_inputs_) {
            if (!runtime->AllocateDevice(&input, ByteCount(), "aclrtFree(device_input)")) {
                return false;
            }
        }
        for (void*& output : device_outputs_) {
            if (!runtime->AllocateDevice(&output, ByteCount(), "aclrtFree(device_output)")) {
                return false;
            }
        }
        return true;
    }

    bool CopyInputs() const
    {
        for (size_t index = 0; index < InputCount; ++index) {
            void* device = device_inputs_[index];
            const void* host = inputs_[index].data();
            const aclError result = aclrtMemcpy(device, ByteCount(), host, ByteCount(), ACL_MEMCPY_HOST_TO_DEVICE);
            if (!CheckAcl(result, "aclrtMemcpy(H2D input)")) {
                return false;
            }
        }
        return true;
    }

    bool CopyOutputs(aclrtStream stream)
    {
        if (!CheckAcl(aclrtSynchronizeStream(stream), "aclrtSynchronizeStream")) {
            return false;
        }
        for (size_t index = 0; index < OutputCount; ++index) {
            if (!CopyOutput(index)) {
                return false;
            }
        }
        return true;
    }

    std::vector<T>& input(size_t index)
    {
        return inputs_[index];
    }

    const std::vector<T>& input(size_t index) const
    {
        return inputs_[index];
    }

    const std::vector<T>& output(size_t index = 0) const
    {
        return outputs_[index];
    }

    void* device_input(size_t index) const
    {
        return device_inputs_[index];
    }

    void* device_output(size_t index = 0) const
    {
        return device_outputs_[index];
    }

private:
    size_t ByteCount() const
    {
        return element_count_ * sizeof(T);
    }

    bool CopyOutput(size_t index)
    {
        void* host = outputs_[index].data();
        const void* device = device_outputs_[index];
        const aclError result = aclrtMemcpy(host, ByteCount(), device, ByteCount(), ACL_MEMCPY_DEVICE_TO_HOST);
        return CheckAcl(result, "aclrtMemcpy(D2H output)");
    }

    size_t element_count_;
    std::array<std::vector<T>, InputCount> inputs_;
    std::array<std::vector<T>, OutputCount> outputs_;
    std::array<void*, InputCount> device_inputs_{};
    std::array<void*, OutputCount> device_outputs_{};
};

template <class T, size_t InputCount>
using SingleOutputBuffers = CannsimBuffers<T, InputCount, 1>;

template <class T>
bool OutputMismatch(T actual, T expected)
{
    return actual != expected;
}

inline bool OutputMismatch(float actual, float expected)
{
    return std::abs(actual - expected) > 1e-5F;
}

inline bool OutputMismatch(double actual, double expected)
{
    return std::abs(actual - expected) > 1e-5;
}

template <class T>
void RecordOutputMismatch(size_t index, size_t output_index, T actual, T expected, size_t* mismatches)
{
    if (!OutputMismatch(actual, expected)) {
        return;
    }
    ++(*mismatches);
    if (*mismatches <= 8) {
        std::cerr << "Mismatch at i=" << index << ", out" << output_index << ", got=" << actual
                  << ", expected=" << expected << '\n';
    }
}

template <class Derived, class T, size_t ElementCount, size_t InputCount, size_t OutputCount>
class CannsimCaseBase {
public:
    bool Allocate(AclRuntime* runtime)
    {
        return buffers_.Allocate(runtime);
    }

    bool Run(aclrtStream stream)
    {
        auto& derived = static_cast<Derived&>(*this);
        derived.InitializeInput();
        if (!buffers_.CopyInputs() || !derived.Launch(stream) || !buffers_.CopyOutputs(stream)) {
            return false;
        }
        return derived.Verify();
    }

protected:
    bool VerifyElements(const char* case_name) const
    {
        const int64_t print_samples = GetPrintSampleCount();
        size_t mismatches = 0;
        const auto& derived = static_cast<const Derived&>(*this);
        for (size_t index = 0; index < ElementCount; ++index) {
            derived.VerifyElement(index, print_samples, &mismatches);
        }
        std::cout << "[kernel][" << case_name << "] checked " << ElementCount << " elements, mismatches " << mismatches
                  << '\n';
        return mismatches == 0;
    }

    CannsimBuffers<T, InputCount, OutputCount> buffers_{ElementCount};
};

template <class Derived, class T, size_t ElementCount, size_t InputCount>
using SingleOutputCannsimCase = CannsimCaseBase<Derived, T, ElementCount, InputCount, 1>;

}  // namespace asc_stl_test

#endif  // CANN_ASC_STL_TEST_INFRASTRUCTURE_CANNSIM_ACL_RUNTIME_H
