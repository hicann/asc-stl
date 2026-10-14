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
#include <asc/std/__type_traits/is_same.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __execution_detail {
// Reads the kind each policy type carries on itself (see execution_policy.h):
// the tag definition is the single source of truth, so adding or retargeting
// a policy cannot leave a parallel specialization table behind.
template <class Policy>
struct __uses_parallel_backend {
    static constexpr bool value = Policy::__asc_policy_kind == __policy_kind::parallel ||
        Policy::__asc_policy_kind == __policy_kind::parallel_unsequenced;
};
template <class Policy>
inline constexpr bool __uses_parallel_backend_v = __uses_parallel_backend<Policy>::value;

template <class Policy, class SequentialFunction>
CANN_ASC_STL_HOST_API constexpr auto __policy_dispatch(Policy, SequentialFunction&& sequential) noexcept(noexcept(
    static_cast<SequentialFunction&&>(sequential)())) -> decltype(static_cast<SequentialFunction&&>(sequential)())
{
    static_assert(is_execution_policy_v<Policy>, "policy dispatch requires an execution policy");
    return static_cast<SequentialFunction&&>(sequential)();
}

// Parallel backend pending: no heterogeneous parallel engine is wired behind
// __policy_dispatch yet, so parallel policies route to the same conforming
// sequential baseline as sequenced policies. The routing is a real compile-time
// branch on __uses_parallel_backend_v (never a silent fall-through), and the
// static_assert below keeps the pending state visible at every instantiation
// while proving the parallel callable is well-formed and result-compatible, so
// connecting the backend later cannot change observable behavior by accident.
// When the E1 device backend lands, this two-function shape is expected to
// grow into per-(algorithm, backend) dispatch entries with the same rule: a
// missing backend must fail at compile time, never silently fall through.
template <class Policy, class SequentialFunction, class ParallelFunction>
CANN_ASC_STL_HOST_API constexpr auto __policy_dispatch([[maybe_unused]] Policy policy, SequentialFunction&& sequential,
    ParallelFunction&& parallel) noexcept(noexcept(static_cast<SequentialFunction&&>(sequential)()))
    -> decltype(static_cast<SequentialFunction&&>(sequential)())
{
    static_assert(is_execution_policy_v<Policy>, "policy dispatch requires an execution policy");
    if constexpr (__uses_parallel_backend_v<Policy>) {
        static_assert(is_same_v<decltype(static_cast<ParallelFunction&&>(parallel)()),
                          decltype(static_cast<SequentialFunction&&>(sequential)())>,
            "parallel backend pending: parallel policies dispatch to the conforming sequential baseline");
        return static_cast<SequentialFunction&&>(sequential)();
    } else {
        return static_cast<SequentialFunction&&>(sequential)();
    }
}
}  // namespace __execution_detail

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___EXECUTION_POLICY_DISPATCH_H
