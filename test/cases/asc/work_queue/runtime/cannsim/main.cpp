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
#include <asc/__work_queue/cursor.h>
#include <cstdint>
#include <iostream>

void launch_asc_stl_b026_work_queue_cannsim(
    std::uint32_t*, asc::detail::work_cursor*, std::uint32_t*, asc::detail::work_cursor*, void*);

int main()
{
    constexpr std::uint32_t kItems = 257;
    std::uint32_t* visits = nullptr;
    asc::detail::work_cursor* cursor = nullptr;
    std::uint32_t* boundary_result = nullptr;
    asc::detail::work_cursor* boundary_cursor = nullptr;
    aclrtStream stream = nullptr;
    const asc::detail::work_cursor initial(0, 257, 11);
    constexpr std::uint64_t high_bit = std::uint64_t{1} << 63;
    const asc::detail::work_cursor boundary_initial(high_bit - 2, high_bit + 3, 2);
    std::uint32_t boundary_zero = 0;
    std::uint32_t zeros[kItems] = {};
    bool passed = aclInit(nullptr) == ACL_SUCCESS && aclrtSetDevice(0) == ACL_SUCCESS &&
        aclrtCreateStream(&stream) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&visits), kItems * 4, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&cursor), sizeof(initial), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&boundary_result), 4, ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS &&
        aclrtMalloc(reinterpret_cast<void**>(&boundary_cursor), sizeof(boundary_initial), ACL_MEM_MALLOC_HUGE_FIRST) ==
            ACL_SUCCESS &&
        aclrtMemcpy(visits, kItems * 4, zeros, kItems * 4, ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS &&
        aclrtMemcpy(cursor, sizeof(initial), &initial, sizeof(initial), ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS &&
        aclrtMemcpy(boundary_result, 4, &boundary_zero, 4, ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS &&
        aclrtMemcpy(boundary_cursor, sizeof(boundary_initial), &boundary_initial, sizeof(boundary_initial),
            ACL_MEMCPY_HOST_TO_DEVICE) == ACL_SUCCESS;
    if (passed) {
        launch_asc_stl_b026_work_queue_cannsim(visits, cursor, boundary_result, boundary_cursor, stream);
        std::uint32_t host_visits[kItems] = {};
        std::uint32_t boundary_failures = 1;
        passed = aclrtSynchronizeStream(stream) == ACL_SUCCESS &&
            aclrtMemcpy(host_visits, kItems * 4, visits, kItems * 4, ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS &&
            aclrtMemcpy(&boundary_failures, 4, boundary_result, 4, ACL_MEMCPY_DEVICE_TO_HOST) == ACL_SUCCESS;
        std::uint32_t mismatches = 0;
        for (std::uint32_t item = 0; item < kItems; ++item) {
            mismatches += host_visits[item] != 1u;
        }
        std::cout << "b026_work_queue_cannsim_visit_mismatches=" << mismatches << '\n';
        std::cout << "b026_work_queue_cannsim_uint64_boundary_failures=" << boundary_failures << '\n';
        passed = passed && mismatches == 0 && boundary_failures == 0;
    }
    if (visits)
        passed = aclrtFree(visits) == ACL_SUCCESS && passed;
    if (cursor)
        passed = aclrtFree(cursor) == ACL_SUCCESS && passed;
    if (boundary_result)
        passed = aclrtFree(boundary_result) == ACL_SUCCESS && passed;
    if (boundary_cursor)
        passed = aclrtFree(boundary_cursor) == ACL_SUCCESS && passed;
    if (stream)
        passed = aclrtDestroyStream(stream) == ACL_SUCCESS && passed;
    passed = aclrtResetDevice(0) == ACL_SUCCESS && passed;
    passed = aclFinalize() == ACL_SUCCESS && passed;
    if (passed)
        std::cout << "ASC_STL_CANNSIM_B026_PASS\n";
    return passed ? 0 : 1;
}
