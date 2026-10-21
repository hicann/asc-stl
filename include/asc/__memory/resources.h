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

#ifndef CANN_ASC_STL_ASC___MEMORY_RESOURCES_H
#define CANN_ASC_STL_ASC___MEMORY_RESOURCES_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__cstddef/types.h>

#if defined(INC_EXTERNAL_ACL_ACL_RT_H_)
#define CANN_ASC_STL_DETAIL_HAS_ACL_MEMORY_RUNTIME 1
#elif defined(__has_include)
#if __has_include(<acl/acl_rt.h>)
#include <acl/acl_rt.h>
#define CANN_ASC_STL_DETAIL_HAS_ACL_MEMORY_RUNTIME 1
#endif
#endif

#if !defined(CANN_ASC_STL_DETAIL_HAS_ACL_MEMORY_RUNTIME)
extern "C" int aclrtGetDevice(int* device);
extern "C" int aclrtMalloc(void** pointer, __SIZE_TYPE__ bytes, int policy);
extern "C" int aclrtFree(void* pointer);
extern "C" int aclrtMallocHost(void** pointer, __SIZE_TYPE__ bytes);
extern "C" int aclrtFreeHost(void* pointer);
#endif

// Allocation policy constant. ACL_MEM_MALLOC_HUGE_FIRST is numerically 0 in
// the real header; the internal macro keeps one spelling for the policy so
// the header-present and header-absent arms cannot drift apart, and a future
// toolkit that renumbers the enum only needs this single place updated.
#if defined(CANN_ASC_STL_DETAIL_HAS_ACL_MEMORY_RUNTIME)
#define CANN_ASC_STL_DETAIL_ACL_MALLOC_HUGE_FIRST ACL_MEM_MALLOC_HUGE_FIRST
#else
#define CANN_ASC_STL_DETAIL_ACL_MALLOC_HUGE_FIRST 0
#endif

namespace asc::detail {
struct memory_resource_state {
    void* handle{};
};

CANN_ASC_STL_HOST_API int memory_current_device(int* device) noexcept
{
    return ::aclrtGetDevice(device);
}
CANN_ASC_STL_HOST_API int memory_allocate_device(void** output, __SIZE_TYPE__ bytes) noexcept
{
    return ::aclrtMalloc(output, bytes, CANN_ASC_STL_DETAIL_ACL_MALLOC_HUGE_FIRST);
}
CANN_ASC_STL_HOST_API int memory_deallocate_device(void* pointer) noexcept
{
    return ::aclrtFree(pointer);
}
CANN_ASC_STL_HOST_API int memory_allocate_pinned(void** output, __SIZE_TYPE__ bytes) noexcept
{
    return ::aclrtMallocHost(output, bytes);
}
CANN_ASC_STL_HOST_API int memory_deallocate_pinned(void* pointer) noexcept
{
    return ::aclrtFreeHost(pointer);
}
}  // namespace asc::detail

#undef CANN_ASC_STL_DETAIL_ACL_MALLOC_HUGE_FIRST

#if defined(CANN_ASC_STL_DETAIL_HAS_ACL_MEMORY_RUNTIME)
#undef CANN_ASC_STL_DETAIL_HAS_ACL_MEMORY_RUNTIME
#endif

#endif  // CANN_ASC_STL_ASC___MEMORY_RESOURCES_H
