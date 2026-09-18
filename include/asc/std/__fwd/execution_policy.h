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

#ifndef CANN_ASC_STL_STD_DETAIL_FWD_EXECUTION_POLICY_H
#define CANN_ASC_STL_STD_DETAIL_FWD_EXECUTION_POLICY_H

#include <asc/std/detail/__config>

#include <asc/std/cstdint>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_EXECUTION

//! @brief Enumerates the standard execution policies
enum class __execution_policy : uint8_t {
    __invalid_execution_policy = 0,
    __sequenced = 1 << 0,
    __parallel = 1 << 1,
    __unsequenced = 1 << 2,
    __parallel_unsequenced = __execution_policy::__parallel | __execution_policy::__unsequenced,
};

//! @brief Extracts the execution policy from the stored _Policy
template <uint32_t _Policy>
inline constexpr __execution_policy __policy_to_execution_policy = __execution_policy{(_Policy & uint32_t{0x000000FF})};

//! @brief Enumerates the different backends we support
//! @note Not an enum class because a user might specify multiple backends
enum __execution_backend : uint8_t {
    // The backends we provide
    __none = 0,
    // TODO: enable when ASC backend feature macros are available
    // __omp = 1 << 1,
    // __tbb = 1 << 2,
};

//! @brief Extracts the execution backend from the stored _Policy
template <uint32_t _Policy>
inline constexpr __execution_backend __policy_to_execution_backend =
    __execution_backend{(_Policy & uint32_t{0x0000FF00}) >> 8};

template <uint32_t _Policy, class... _Envs>
struct __execution_policy_base;

//! @brief Sets the execution backend
template <uint32_t _Policy, __execution_backend _Backend>
[[nodiscard]] CANN_ASC_STL_API constexpr uint32_t __with_backend() noexcept
{
    constexpr uint32_t __backend_mask{0xFFFF00FF};
    constexpr uint32_t __new_policy = (_Policy & __backend_mask) | (static_cast<uint32_t>(_Backend) << 8);
    return __new_policy;
}

//! @brief Checks whether a policy supports the given backend
template <uint32_t _Policy, __execution_backend _Backend>
[[nodiscard]] CANN_ASC_STL_API constexpr bool __has_backend() noexcept
{
    constexpr uint32_t __backend_mask{0x0000FF00};
    return (_Policy & __backend_mask) & (static_cast<uint32_t>(_Backend) << 8);
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_EXECUTION

#endif  // CANN_ASC_STL_STD_DETAIL_FWD_EXECUTION_POLICY_H
