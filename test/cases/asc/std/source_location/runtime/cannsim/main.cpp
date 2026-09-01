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

#include <array>
#include <cstdint>
#include <iostream>

#include "launcher.h"

namespace {

constexpr int kDeviceId = 0;
constexpr std::size_t kResultCount = 8;

bool check(aclError result, const char* operation)
{
    if (result == ACL_SUCCESS) {
        return true;
    }
    std::cerr << operation << " failed with ACL error " << result << '\n';
    return false;
}

}  // namespace

int main()
{
    const std::array<std::uint32_t, kResultCount> expected = {
        0x13579BDFU, 321U, 27U, 654U, 23U, 24U, 0x2468ACE0U, 0x55AA55AAU};
    std::array<std::uint32_t, kResultCount> actual{};
    void* device_output = nullptr;
    aclrtStream stream = nullptr;

    bool passed = check(aclInit(nullptr), "aclInit") && check(aclrtSetDevice(kDeviceId), "aclrtSetDevice") &&
        check(aclrtCreateStream(&stream), "aclrtCreateStream") &&
        check(aclrtMalloc(&device_output, sizeof(actual), ACL_MEM_MALLOC_HUGE_FIRST), "aclrtMalloc");
    if (passed) {
        passed = check(launch_asc_stl_source_location_cannsim(stream, device_output), "kernel launch") &&
            check(aclrtSynchronizeStream(stream), "aclrtSynchronizeStream") &&
            check(aclrtMemcpy(actual.data(), sizeof(actual), device_output, sizeof(actual), ACL_MEMCPY_DEVICE_TO_HOST),
                "aclrtMemcpy") &&
            actual == expected;
    }

    if (actual != expected) {
        for (std::size_t index = 0; index < actual.size(); ++index) {
            std::cerr << "result[" << index << "]=" << actual[index] << " expected=" << expected[index] << '\n';
        }
    }
    if (device_output != nullptr) {
        passed = check(aclrtFree(device_output), "aclrtFree") && passed;
    }
    if (stream != nullptr) {
        passed = check(aclrtDestroyStream(stream), "aclrtDestroyStream") && passed;
    }
    passed = check(aclrtResetDevice(kDeviceId), "aclrtResetDevice") && passed;
    passed = check(aclFinalize(), "aclFinalize") && passed;

    if (passed) {
        std::cout << "ASC_STL_CANNSIM_ASC_STD_SOURCE_LOCATION_PASS\n";
        std::cout << "source_location marker=0x55AA55AA line=321 column=27\n";
    }
    return passed ? 0 : 1;
}
