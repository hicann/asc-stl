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

#ifndef CANN_ASC_STL_ASC___PARALLEL_TEMPORARY_STORAGE_H
#define CANN_ASC_STL_ASC___PARALLEL_TEMPORARY_STORAGE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/execution>
#include <asc/execution.policy.h>
#include <asc/memory>

namespace asc::detail {

CANN_ASC_STL_HOST_API execution_status validate_parallel_policy(device_policy policy) noexcept
{
    return policy.stream() ? execution_status{} : execution_status{execution_errc::invalid_argument};
}

CANN_ASC_STL_HOST_API execution_status require_temporary_storage(device_policy policy, __SIZE_TYPE__ bytes) noexcept
{
    execution_status status = validate_parallel_policy(policy);
    if (!status.success()) {
        return status;
    }
    temporary_storage_ref storage = policy.temporary_storage();
    if (storage.data() == nullptr || storage.space() != memory_space::global || storage.size_bytes() < bytes) {
        return execution_status{execution_errc::insufficient_storage};
    }
    return execution_status{};
}

template <class T>
CANN_ASC_STL_HOST_API T* temporary_storage_pointer(device_policy policy, __SIZE_TYPE__ offset = 0) noexcept
{
    unsigned char* data = static_cast<unsigned char*>(policy.temporary_storage().data());
    return reinterpret_cast<T*>(data + offset);
}

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___PARALLEL_TEMPORARY_STORAGE_H
