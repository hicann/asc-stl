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

#ifndef CANN_ASC_STL_ASC___ALGORITHM_BYTE_OPERATIONS_H
#define CANN_ASC_STL_ASC___ALGORITHM_BYTE_OPERATIONS_H

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
#include <asc/stream>

// Prefer the official AscendCL header when it is reachable and fall back to
// the minimal manual declarations otherwise, mirroring the binding pattern of
// <asc/__runtime/stream.h> and <asc/__runtime/devices.h>: the official header
// makes signature drift visible at compile time, the fallback keeps Host-only
// translation units without an AscendCL installation parsable.
#if defined(INC_EXTERNAL_ACL_ACL_RT_H_)
#define CANN_ASC_STL_DETAIL_HAS_ACL_COPY_RUNTIME 1
#elif defined(__has_include)
#if __has_include(<acl/acl_rt.h>)
#include <acl/acl_rt.h>
#define CANN_ASC_STL_DETAIL_HAS_ACL_COPY_RUNTIME 1
#endif
#endif

#if !defined(CANN_ASC_STL_DETAIL_HAS_ACL_COPY_RUNTIME)
extern "C" int aclrtMemcpyAsync(
    void* destination, __SIZE_TYPE__ destination_size, const void* source, __SIZE_TYPE__ bytes, int kind, void* stream);
extern "C" int aclrtMemsetAsync(
    void* destination, __SIZE_TYPE__ destination_size, int value, __SIZE_TYPE__ bytes, void* stream);
#endif

namespace asc::std {
using size_t = __SIZE_TYPE__;
}  // namespace asc::std

namespace asc {
namespace detail {
// AscendCL aclrtMemcpyKind values, including the runtime pointer
// classification, so the enumerators stay at their ACL offsets.
enum class copy_direction : int {
    host_to_host = 0,
    host_to_device = 1,
    device_to_host = 2,
    device_to_device = 3,
    automatic = 4,
};

CANN_ASC_STL_HOST_API execution_status copy_bytes_runtime(stream_ref stream, void* destination, const void* source,
    ::asc::std::size_t bytes, copy_direction direction) noexcept
{
    if (!stream || (bytes != 0 && (destination == nullptr || source == nullptr))) {
        return execution_status{execution_errc::invalid_argument};
    }
    if (bytes == 0) {
        return execution_status{};
    }
#if defined(CANN_ASC_STL_DETAIL_HAS_ACL_COPY_RUNTIME)
    const auto kind = static_cast<aclrtMemcpyKind>(static_cast<int>(direction));
#else
    const int kind = static_cast<int>(direction);
#endif
    return backend_status(::aclrtMemcpyAsync(destination, bytes, source, bytes, kind, stream.native_handle()));
}
}  // namespace detail

// Raw-byte copy through the AscendCL stream.  The void*/bytes form cannot
// validate the destination capacity or the element nature (the dev-side
// reference delivers span/mdspan overloads that check both before enqueueing,
// including trivially-copyable and non-const destination constraints); here
// the caller guarantees that the destination offers at least `bytes` of
// writable storage.  A capacity-aware public overload is a registry decision
// and must not change this signature.
CANN_ASC_STL_HOST_API execution_status copy_bytes(
    stream_ref stream, void* destination, const void* source, ::asc::std::size_t bytes) noexcept
{
    return detail::copy_bytes_runtime(stream, destination, source, bytes, detail::copy_direction::automatic);
}

CANN_ASC_STL_HOST_API execution_status fill_bytes(
    stream_ref stream, void* destination, unsigned char value, ::asc::std::size_t bytes) noexcept
{
    if (!stream || (bytes != 0 && destination == nullptr)) {
        return execution_status{execution_errc::invalid_argument};
    }
    if (bytes == 0) {
        return execution_status{};
    }
    return detail::backend_status(
        ::aclrtMemsetAsync(destination, bytes, static_cast<int>(value), bytes, stream.native_handle()));
}

}  // namespace asc

#if defined(CANN_ASC_STL_DETAIL_HAS_ACL_COPY_RUNTIME)
#undef CANN_ASC_STL_DETAIL_HAS_ACL_COPY_RUNTIME
#endif

#endif  // CANN_ASC_STL_ASC___ALGORITHM_BYTE_OPERATIONS_H
