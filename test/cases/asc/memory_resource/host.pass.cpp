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

#if defined(__has_include)
#if __has_include(<acl/acl_rt.h>)
#include <acl/acl_rt.h>
#define ASC_STL_B021_TEST_HAS_ACL_RT 1
#endif
#endif

#include "../../../support/b021_semantics.h"

namespace {
alignas(64) unsigned char device_storage[128];
alignas(64) unsigned char pinned_storage[128];
int active_device = 3;
int device_free_count = 0;
int pinned_free_count = 0;
}  // namespace

#if defined(ASC_STL_B021_TEST_HAS_ACL_RT)
extern "C" aclError aclrtGetDevice(int32_t* device)
{
    *device = active_device;
    return ACL_SUCCESS;
}
extern "C" aclError aclrtMalloc(void** pointer, size_t bytes, aclrtMemMallocPolicy)
{
    if (bytes > sizeof(device_storage))
        return ACL_ERROR_RT_MEMORY_ALLOCATION;
    *pointer = device_storage;
    return ACL_SUCCESS;
}
extern "C" aclError aclrtFree(void* pointer)
{
    static_cast<void>(pointer);
    ++device_free_count;
    return ACL_SUCCESS;
}
extern "C" aclError aclrtMallocHost(void** pointer, size_t bytes)
{
    if (bytes > sizeof(pinned_storage))
        return ACL_ERROR_RT_MEMORY_ALLOCATION;
    *pointer = pinned_storage;
    return ACL_SUCCESS;
}
extern "C" aclError aclrtFreeHost(void* pointer)
{
    static_cast<void>(pointer);
    ++pinned_free_count;
    return ACL_SUCCESS;
}
#else
extern "C" int aclrtGetDevice(int* device)
{
    *device = active_device;
    return 0;
}
extern "C" int aclrtMalloc(void** pointer, __SIZE_TYPE__ bytes, int)
{
    if (bytes > sizeof(device_storage))
        return 7;
    *pointer = device_storage;
    return 0;
}
extern "C" int aclrtFree(void* pointer)
{
    static_cast<void>(pointer);
    ++device_free_count;
    return 0;
}
extern "C" int aclrtMallocHost(void** pointer, __SIZE_TYPE__ bytes)
{
    if (bytes > sizeof(pinned_storage))
        return 7;
    *pointer = pinned_storage;
    return 0;
}
extern "C" int aclrtFreeHost(void* pointer)
{
    static_cast<void>(pointer);
    ++pinned_free_count;
    return 0;
}
#endif

static_assert(asc_stl_b021_test::evaluate_chrono() == 0);

int main()
{
    int failures = asc_stl_b021_test::evaluate_common() + asc_stl_b021_test::evaluate_memory_resource();
    asc::device_memory_resource device{3};
    void* pointer = nullptr;
    failures += !device.allocate(&pointer, 64, 32).success() || pointer != device_storage;
    failures += !device.deallocate(pointer, 64, 32).success() || device_free_count != 1;
    pointer = device_storage;
    failures += device.allocate(&pointer, 8, 8).code() != asc::execution_errc::invalid_argument;
    pointer = nullptr;
    failures += device.allocate(&pointer, 8, 3).code() != asc::execution_errc::invalid_argument;
    active_device = 2;
    failures += device.allocate(&pointer, 8, 8).code() != asc::execution_errc::invalid_argument;
    active_device = 3;

    asc::pinned_memory_resource pinned;
    pointer = nullptr;
    failures += !pinned.allocate(&pointer, 64).success() || pointer != pinned_storage;
    failures += !pinned.deallocate(pointer, 64).success() || pinned_free_count != 1;
    pointer = nullptr;
    const auto too_large = pinned.allocate(&pointer, 256);
    failures += too_large.code() != asc::execution_errc::backend_error || too_large.native_code() != 7;
    return failures;
}
