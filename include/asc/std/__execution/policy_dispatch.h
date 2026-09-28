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

#ifndef CANN_ASC_STL_ASC_STD___EXECUTION_POLICY_DISPATCH_H
#define CANN_ASC_STL_ASC_STD___EXECUTION_POLICY_DISPATCH_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__execution/execution_policy.h>
#include <asc/std/__execution/type_traits.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __execution_detail {
template <class Policy>
struct __uses_parallel_backend {
    static constexpr bool value = false;
};
template <>
struct __uses_parallel_backend<execution::parallel_policy> {
    static constexpr bool value = true;
};
template <>
struct __uses_parallel_backend<execution::parallel_unsequenced_policy> {
    static constexpr bool value = true;
};

template <class Policy, class SequentialFunction>
CANN_ASC_STL_API constexpr auto __policy_dispatch(Policy, SequentialFunction&& sequential) noexcept(noexcept(
    static_cast<SequentialFunction&&>(sequential)())) -> decltype(static_cast<SequentialFunction&&>(sequential)())
{
    static_assert(is_execution_policy_v<Policy>, "policy dispatch requires an execution policy");
    return static_cast<SequentialFunction&&>(sequential)();
}

template <class Policy, class SequentialFunction, class ParallelFunction>
CANN_ASC_STL_API constexpr auto __policy_dispatch(Policy policy, SequentialFunction&& sequential,
    ParallelFunction&&) noexcept(noexcept(__policy_dispatch(policy, static_cast<SequentialFunction&&>(sequential))))
    -> decltype(__policy_dispatch(policy, static_cast<SequentialFunction&&>(sequential)))
{
    return __policy_dispatch(policy, static_cast<SequentialFunction&&>(sequential));
}
}  // namespace __execution_detail

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___EXECUTION_POLICY_DISPATCH_H
