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

#ifndef CANN_ASC_STL_ASC___RUNTIME_DEVICES_H
#define CANN_ASC_STL_ASC___RUNTIME_DEVICES_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/cstdint>

#if !defined(__CCE__) && !defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__) && defined(__has_include)
#if __has_include(<acl/acl_rt.h>)
#include <acl/acl_rt.h>
#define CANN_ASC_STL_DETAIL_HAS_ACL_DEVICE_RUNTIME 1
#endif
#endif

#if !defined(CANN_ASC_STL_DETAIL_HAS_ACL_DEVICE_RUNTIME)
extern "C" int aclrtGetDeviceCount(asc::std::uint32_t*);
extern "C" int aclrtGetDevice(int*);
extern "C" int aclrtSetDevice(int);
extern "C" int aclrtGetDeviceInfo(asc::std::uint32_t, int, asc::std::int64_t*);
#endif
namespace asc {
enum class npu_arch : std::uint32_t { unknown = 0, ascend_2201 = 2201, ascend_3101 = 3101, ascend_3510 = 3510 };
struct device_properties {
    std::uint32_t aicore_count{};
    std::uint32_t vector_core_count{};
    std::uint32_t warp_size{};
    std::uint32_t maximum_threads_per_block{};
    std::uint64_t unified_buffer_bytes_per_vector_core{};
    std::uint64_t total_global_memory_bytes{};
    std::uint64_t l2_cache_bytes{};
    npu_arch architecture{npu_arch::unknown};
};
class device_ref {
public:
    explicit constexpr device_ref(std::uint32_t ordinal) noexcept : ordinal_(ordinal)
    {}
    constexpr std::uint32_t ordinal() const noexcept
    {
        return ordinal_;
    }
    bool properties(device_properties& output) const noexcept;
    friend constexpr bool operator==(device_ref lhs, device_ref rhs) noexcept
    {
        return lhs.ordinal_ == rhs.ordinal_;
    }
    friend constexpr bool operator!=(device_ref lhs, device_ref rhs) noexcept
    {
        return !(lhs == rhs);
    }

private:
    std::uint32_t ordinal_;
};
inline bool device_count(std::uint32_t& output) noexcept
{
    std::uint32_t value = 0;
    if (::aclrtGetDeviceCount(&value) != 0)
        return false;
    output = value;
    return true;
}
inline bool devices(device_ref* output, std::uint32_t capacity, std::uint32_t& count) noexcept
{
    std::uint32_t available = 0;
    if (!device_count(available))
        return false;
    if (output == nullptr && capacity != 0)
        return false;
    const std::uint32_t written = capacity < available ? capacity : available;
    for (std::uint32_t i = 0; i < written; ++i)
        output[i] = device_ref(i);
    count = available;
    return true;
}
inline bool current_device(device_ref& output) noexcept
{
    int ordinal = 0;
    if (::aclrtGetDevice(&ordinal) != 0 || ordinal < 0)
        return false;
    output = device_ref(static_cast<std::uint32_t>(ordinal));
    return true;
}
inline bool set_current_device(device_ref device) noexcept
{
    return ::aclrtSetDevice(static_cast<int>(device.ordinal())) == 0;
}
inline bool device_ref::properties(device_properties& output) const noexcept
{
#if defined(CANN_ASC_STL_DETAIL_HAS_ACL_DEVICE_RUNTIME)
    constexpr aclrtDevAttr attrs[] = {ACL_DEV_ATTR_AICORE_CORE_NUM, ACL_DEV_ATTR_VECTOR_CORE_NUM,
        ACL_DEV_ATTR_WARP_SIZE, ACL_DEV_ATTR_MAX_THREADS_PER_BLOCK, ACL_DEV_ATTR_UBUF_PER_VECTOR_CORE,
        ACL_DEV_ATTR_TOTAL_GLOBAL_MEM_SIZE, ACL_DEV_ATTR_L2_CACHE_SIZE, ACL_DEV_ATTR_NPU_ARCH};
#else
    constexpr int attrs[] = {101, 201, 202, 209, 204, 301, 302, 601};
#endif
    std::int64_t values[8]{};
    for (std::uint32_t i = 0; i < 8; ++i)
        if (::aclrtGetDeviceInfo(ordinal_, attrs[i], &values[i]) != 0 || values[i] < 0)
            return false;
    device_properties value{};
    value.aicore_count = static_cast<std::uint32_t>(values[0]);
    value.vector_core_count = static_cast<std::uint32_t>(values[1]);
    value.warp_size = static_cast<std::uint32_t>(values[2]);
    value.maximum_threads_per_block = static_cast<std::uint32_t>(values[3]);
    value.unified_buffer_bytes_per_vector_core = static_cast<std::uint64_t>(values[4]);
    value.total_global_memory_bytes = static_cast<std::uint64_t>(values[5]);
    value.l2_cache_bytes = static_cast<std::uint64_t>(values[6]);
    const auto arch = static_cast<std::uint32_t>(values[7]);
    value.architecture = arch == 2201 ? npu_arch::ascend_2201 :
        arch == 3101                  ? npu_arch::ascend_3101 :
        arch == 3510                  ? npu_arch::ascend_3510 :
                                        npu_arch::unknown;
    output = value;
    return true;
}
}  // namespace asc

#if defined(CANN_ASC_STL_DETAIL_HAS_ACL_DEVICE_RUNTIME)
#undef CANN_ASC_STL_DETAIL_HAS_ACL_DEVICE_RUNTIME
#endif

#endif  // CANN_ASC_STL_ASC___RUNTIME_DEVICES_H
