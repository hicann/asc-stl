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

#ifndef CANN_ASC_STL_ASC_EXECUTION_POLICY_H
#define CANN_ASC_STL_ASC_EXECUTION_POLICY_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__execution/policy.h>
#include <asc/execution.require.h>
#include <asc/memory>
#include <asc/stream>

namespace asc {

class device_policy {
public:
    CANN_ASC_STL_HOST constexpr device_policy() noexcept = default;

    CANN_ASC_STL_HOST constexpr device_policy on(stream_ref value) const noexcept
    {
        return {value, storage_, requirements_};
    }
    CANN_ASC_STL_HOST constexpr device_policy with_temporary_storage(temporary_storage_ref value) const noexcept
    {
        return {stream_, value, requirements_};
    }
    CANN_ASC_STL_HOST constexpr device_policy require(execution_requirements value) const noexcept
    {
        return {stream_, storage_, value};
    }
    CANN_ASC_STL_HOST constexpr stream_ref stream() const noexcept
    {
        return stream_;
    }
    CANN_ASC_STL_HOST constexpr temporary_storage_ref temporary_storage() const noexcept
    {
        return storage_;
    }
    CANN_ASC_STL_HOST constexpr execution_requirements requirements() const noexcept
    {
        return requirements_;
    }

private:
    CANN_ASC_STL_HOST constexpr device_policy(
        stream_ref stream, temporary_storage_ref storage, execution_requirements requirements) noexcept
        : stream_(stream), storage_(storage), requirements_(requirements)
    {}

    stream_ref stream_{};
    temporary_storage_ref storage_{};
    execution_requirements requirements_{};
};

namespace execution {
inline constexpr device_policy device{};
}  // namespace execution

}  // namespace asc

#endif  // CANN_ASC_STL_ASC_EXECUTION_POLICY_H
