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

/* Copyright 2026 湖北多样性算力应用创新究院. Licensed under Apache-2.0. */
#include <acl/acl.h>
#include <array>
#include <cstdint>
#include <iostream>
void launch_asc_stl_atomic_cannsim(std::int32_t*, aclrtStream);
namespace {
constexpr std::array<std::int32_t, 16> expected = {11, 10, 15, 12, 1, 12, 8, 13, 14, 4, 9, 9, 11, 10, 1, 11};
bool ok(aclError result, const char* name)
{
    if (result == ACL_SUCCESS)
        return true;
    std::cerr << name << " failed with ACL error " << result << '\n';
    return false;
}
}  // namespace
int main()
{
    std::array<std::int32_t, 16> actual{};
    void* device = nullptr;
    aclrtStream stream = nullptr;
    bool passed = ok(aclInit(nullptr), "aclInit") && ok(aclrtSetDevice(0), "aclrtSetDevice") &&
        ok(aclrtCreateStream(&stream), "aclrtCreateStream") &&
        ok(aclrtMalloc(&device, sizeof(actual), ACL_MEM_MALLOC_HUGE_FIRST), "aclrtMalloc");
    if (passed) {
        launch_asc_stl_atomic_cannsim(static_cast<std::int32_t*>(device), stream);
        passed = ok(aclrtSynchronizeStream(stream), "aclrtSynchronizeStream") &&
            ok(aclrtMemcpy(actual.data(), sizeof(actual), device, sizeof(actual), ACL_MEMCPY_DEVICE_TO_HOST),
                "aclrtMemcpy") &&
            actual == expected;
    }
    if (device != nullptr)
        passed = ok(aclrtFree(device), "aclrtFree") && passed;
    if (stream != nullptr)
        passed = ok(aclrtDestroyStream(stream), "aclrtDestroyStream") && passed;
    passed = ok(aclrtResetDevice(0), "aclrtResetDevice") && passed;
    passed = ok(aclFinalize(), "aclFinalize") && passed;
    if (passed)
        std::cout << "ASC_STL_CANNSIM_ATOMIC_PASS\n";
    return passed ? 0 : 1;
}
