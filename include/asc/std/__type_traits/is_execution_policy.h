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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_EXECUTION_POLICY_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_EXECUTION_POLICY_H

#include <asc/std/detail/__config>

#include <asc/std/__fwd/execution_policy.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/void_t.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class, class = void>
inline constexpr bool is_execution_policy_v = false;

template <class _Policy>
inline constexpr bool is_execution_policy_v<_Policy, void_t<decltype(_Policy::__asc_policy_)>> = true;

template <class _Tp>
struct CANN_ASC_STL_DETAIL_NO_SPECIALIZATIONS is_execution_policy : bool_constant<is_execution_policy_v<_Tp>> {};

// Detect parallel policies
template <class _Policy, bool = is_execution_policy_v<_Policy>>
inline constexpr bool __is_parallel_execution_policy_v = false;

template <class _Policy>
inline constexpr bool __is_parallel_execution_policy_v<_Policy, true> =
    _Policy::__get_policy() == execution::__execution_policy::__parallel ||
    _Policy::__get_policy() == execution::__execution_policy::__parallel_unsequenced;

// Detect unsequenced policies
template <class _Policy, bool = is_execution_policy_v<_Policy>>
inline constexpr bool __is_unsequenced_execution_policy_v = false;

template <class _Policy>
inline constexpr bool __is_unsequenced_execution_policy_v<_Policy, true> =
    _Policy::__get_policy() == execution::__execution_policy::__unsequenced ||
    _Policy::__get_policy() == execution::__execution_policy::__parallel_unsequenced;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_EXECUTION_POLICY_H
