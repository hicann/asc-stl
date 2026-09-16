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

#if !defined(__CCE__) && !defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__) && defined(__has_include)
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

namespace asc::detail {
struct memory_resource_state {
    void* handle{};
};

CANN_ASC_STL_HOST_API int memory_current_device(int* device) noexcept
{
    return ::aclrtGetDevice(device);
}
CANN_ASC_STL_HOST_API int memory_allocate_device(void** output, ::asc::std::size_t bytes) noexcept
{
#if defined(CANN_ASC_STL_DETAIL_HAS_ACL_MEMORY_RUNTIME)
    return ::aclrtMalloc(output, bytes, ACL_MEM_MALLOC_HUGE_FIRST);
#else
    return ::aclrtMalloc(output, bytes, 0);
#endif
}
CANN_ASC_STL_HOST_API int memory_deallocate_device(void* pointer) noexcept
{
    return ::aclrtFree(pointer);
}
CANN_ASC_STL_HOST_API int memory_allocate_pinned(void** output, ::asc::std::size_t bytes) noexcept
{
    return ::aclrtMallocHost(output, bytes);
}
CANN_ASC_STL_HOST_API int memory_deallocate_pinned(void* pointer) noexcept
{
    return ::aclrtFreeHost(pointer);
}
}  // namespace asc::detail

#if defined(CANN_ASC_STL_DETAIL_HAS_ACL_MEMORY_RUNTIME)
#undef CANN_ASC_STL_DETAIL_HAS_ACL_MEMORY_RUNTIME
#endif

#endif  // CANN_ASC_STL_ASC___MEMORY_RESOURCES_H
