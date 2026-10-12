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
#include <cstdint>
#include <iostream>
namespace {
constexpr int kDeviceId = 0;
constexpr std::array<std::uint32_t, 44> kExpected = {0x13579BDFU, 0x1001U, 0U, 0x1002U, 17U, 0x1003U, 365U, 0x1004U,
    314U, 0x1005U, 1U, 0x1006U, 1U, 0xA5A5A5A5U, 0x5A5A5A5AU, 0x2468ACE0U, 0x1007U, 1U, 0x1008U, 1U, 0x1009U, 1U,
    0x100AU, 1U, 0x100BU, 1U, 0x100CU, 1U, 0x100DU, 1U, 0x100EU, 1U, 0x100FU, 1U, 0x1010U, 1U, 0x1011U, 1U, 0x1012U, 1U,
    0x1013U, 0U, 0x1014U,
#if defined(ASC_STL_FOUNDATION_SIMD)
    0xFFFFFFFFU};
#else
    0U};
#endif
bool check(aclError result, const char* operation)
{
    if (result == ACL_SUCCESS)
        return true;
    std::cerr << operation << " failed with ACL error " << result << '\n';
    return false;
}
}  // namespace
#if defined(ASC_STL_FOUNDATION_SIMD)
void launch_asc_stl_foundation_simd(std::uint32_t*, aclrtStream);
#else
void launch_asc_stl_foundation_simt(std::uint32_t*, aclrtStream);
#endif
int main()
{
    std::array<std::uint32_t, kExpected.size()> actual{};
    std::uint32_t* device_output = nullptr;
    aclrtStream stream = nullptr;
    bool passed = check(aclInit(nullptr), "aclInit") && check(aclrtSetDevice(kDeviceId), "aclrtSetDevice") &&
        check(aclrtCreateStream(&stream), "aclrtCreateStream") &&
        check(aclrtMalloc(reinterpret_cast<void**>(&device_output), sizeof(actual), ACL_MEM_MALLOC_HUGE_FIRST),
            "aclrtMalloc");
    if (passed) {
#if defined(ASC_STL_FOUNDATION_SIMD)
        launch_asc_stl_foundation_simd(device_output, stream);
#else
        launch_asc_stl_foundation_simt(device_output, stream);
#endif
        passed = check(aclrtSynchronizeStream(stream), "aclrtSynchronizeStream") &&
            check(aclrtMemcpy(actual.data(), sizeof(actual), device_output, sizeof(actual), ACL_MEMCPY_DEVICE_TO_HOST),
                "aclrtMemcpy") &&
            actual == kExpected;
    }
    if (actual != kExpected) {
        for (std::size_t i = 0; i < actual.size(); ++i)
            std::cerr << "result[" << i << "]=" << actual[i] << " expected=" << kExpected[i] << '\n';
    }
    if (device_output != nullptr)
        passed = check(aclrtFree(device_output), "aclrtFree") && passed;
    if (stream != nullptr)
        passed = check(aclrtDestroyStream(stream), "aclrtDestroyStream") && passed;
    passed = check(aclrtResetDevice(kDeviceId), "aclrtResetDevice") && passed;
    passed = check(aclFinalize(), "aclFinalize") && passed;
    std::cout << (passed ? "PASS" : "FAIL") << ": foundation runtime hardware semantics\n";
    return passed ? 0 : 1;
}
