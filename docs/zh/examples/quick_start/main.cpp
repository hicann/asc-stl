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
#include <array>
#include <csignal>
#include <cstring>
#include <iostream>

#include "aclrtlaunch_add_relu_kernel.h"

namespace {
constexpr int kDevice = 0;
constexpr std::size_t kCount = 64;
constexpr std::size_t kBytes = kCount * sizeof(float);
volatile std::sig_atomic_t interrupted = 0;

void request_stop(int signal)
{
    interrupted = signal;
}

bool check(aclError status, const char* operation)
{
    std::cout << "operation=" << operation << " status=" << status << std::endl;
    return status == ACL_SUCCESS;
}

struct resources {
    bool initialized = false;
    bool selected = false;
    bool synchronization_failed = false;
    aclrtStream stream = nullptr;
    void* x = nullptr;
    void* y = nullptr;
    void* z = nullptr;

    bool open()
    {
        initialized = check(aclInit(nullptr), "aclInit");
        if (!initialized)
            return false;
        selected = check(aclrtSetDevice(kDevice), "aclrtSetDevice");
        return selected && check(aclrtSetOpExecuteTimeOut(10U), "aclrtSetOpExecuteTimeOut") &&
            check(aclrtCreateStream(&stream), "aclrtCreateStream") &&
            check(aclrtMalloc(&x, kBytes, ACL_MEM_MALLOC_HUGE_FIRST), "allocate_x") &&
            check(aclrtMalloc(&y, kBytes, ACL_MEM_MALLOC_HUGE_FIRST), "allocate_y") &&
            check(aclrtMalloc(&z, kBytes, ACL_MEM_MALLOC_HUGE_FIRST), "allocate_z");
    }

    bool close()
    {
        bool passed = true;
        if (!synchronization_failed) {
            if (z != nullptr)
                passed = check(aclrtFree(z), "free_z") && passed;
            if (y != nullptr)
                passed = check(aclrtFree(y), "free_y") && passed;
            if (x != nullptr)
                passed = check(aclrtFree(x), "free_x") && passed;
            if (stream != nullptr)
                passed = check(aclrtDestroyStream(stream), "aclrtDestroyStream") && passed;
        } else {
            std::cerr << "Synchronization failed: leave in-flight resources for device reset.\n";
            passed = false;
        }
        if (selected)
            passed = check(aclrtResetDevice(kDevice), "aclrtResetDevice") && passed;
        if (initialized)
            passed = check(aclFinalize(), "aclFinalize") && passed;
        std::cout << "cleanup_passed=" << passed << std::endl;
        return passed;
    }
};

bool run(resources& device, std::array<float, kCount>& actual, std::array<float, kCount>& expected)
{
    std::array<float, kCount> x{};
    std::array<float, kCount> y{};
    for (std::size_t index = 0; index < kCount; ++index) {
        x[index] = static_cast<float>(static_cast<int>(index) - 32);
        y[index] = static_cast<float>(static_cast<int>(index % 5) - 2);
        const float sum = x[index] + y[index];
        // The Host golden does not call the ASC-STL operation being checked.
        expected[index] = sum > 0.0F ? sum : 0.0F;
        actual[index] = -999.0F;
    }
    if (interrupted || !check(aclrtMemcpy(device.x, kBytes, x.data(), kBytes, ACL_MEMCPY_HOST_TO_DEVICE), "upload_x") ||
        !check(aclrtMemcpy(device.y, kBytes, y.data(), kBytes, ACL_MEMCPY_HOST_TO_DEVICE), "upload_y") ||
        !check(aclrtMemcpy(device.z, kBytes, actual.data(), kBytes, ACL_MEMCPY_HOST_TO_DEVICE), "upload_sentinel"))
        return false;
    if (interrupted)
        return false;
    const bool launched =
        check(ACLRT_LAUNCH_KERNEL(add_relu_kernel)(1, device.stream, device.x, device.y, device.z), "add_relu_kernel");
    // Drain the stream even if submission reported an error before cleanup.
    const bool synchronized = check(aclrtSynchronizeStreamWithTimeout(device.stream, 10000), "synchronize");
    device.synchronization_failed = !synchronized;
    return launched && synchronized && !interrupted &&
        check(aclrtMemcpy(actual.data(), kBytes, device.z, kBytes, ACL_MEMCPY_DEVICE_TO_HOST), "download_z");
}

std::size_t mismatches(const std::array<float, kCount>& actual, const std::array<float, kCount>& expected)
{
    std::size_t count = 0;
    for (std::size_t index = 0; index < kCount; ++index) {
        if (actual[index] != expected[index]) {
            ++count;
            std::cerr << "element=" << index << " actual=" << actual[index] << " expected=" << expected[index] << '\n';
        }
    }
    return count;
}
}  // namespace

int main(int argc, char** argv)
{
    const bool inject = argc == 2 && std::strcmp(argv[1], "--inject-mismatch") == 0;
    if (argc != 1 && !inject) {
        std::cerr << "Usage: asc_stl_quick_start [--inject-mismatch]\n";
        return 2;
    }
    const auto previous_term = std::signal(SIGTERM, request_stop);
    const auto previous_int = std::signal(SIGINT, request_stop);
    resources device;
    std::array<float, kCount> actual{};
    std::array<float, kCount> expected{};
    const bool executed = device.open() && !interrupted && run(device, actual, expected);
    const std::size_t original_failures = executed ? mismatches(actual, expected) : kCount;
    if (inject && original_failures == 0)
        expected[7] += 1.0F;
    const std::size_t failures = inject && original_failures == 0 ? mismatches(actual, expected) : original_failures;
    const bool cleaned = device.close();
    std::signal(SIGTERM, previous_term);
    std::signal(SIGINT, previous_int);
    std::cout << "elements=" << kCount << " mismatches=" << failures << std::endl;
    if (!executed || !cleaned || interrupted || original_failures != 0)
        return 1;
    if (inject && failures == 1) {
        std::cout << "ASC_STL_QUICK_START_EXPECTED_MISMATCH\n";
        return 42;
    }
    if (failures != 0 || inject)
        return 1;
    std::cout << "ASC_STL_QUICK_START_PASS\n";
    return 0;
}
