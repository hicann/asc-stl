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

#ifndef CANN_ASC_STL_ASC_STD___EXECUTION_EXECUTION_POLICY_H
#define CANN_ASC_STL_ASC_STD___EXECUTION_EXECUTION_POLICY_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __execution_detail {
// Static self-description of the execution policy tags: every tag carries its
// kind on the type itself, so trait layers (policy_dispatch, later algorithm
// constraints) read the identity directly from the policy instead of keeping
// parallel specialization tables that can drift from these definitions. The
// member name follows the internal __ prefix convention and the tags keep
// their implicit, unannotated default constructors.
enum class __policy_kind : unsigned int {
    sequenced,
    parallel,
    parallel_unsequenced,
    unsequenced,
};
}  // namespace __execution_detail

namespace execution {

class sequenced_policy {
public:
    static constexpr __execution_detail::__policy_kind __asc_policy_kind = __execution_detail::__policy_kind::sequenced;
};

class parallel_policy {
public:
    static constexpr __execution_detail::__policy_kind __asc_policy_kind = __execution_detail::__policy_kind::parallel;
};

class parallel_unsequenced_policy {
public:
    static constexpr __execution_detail::__policy_kind __asc_policy_kind =
        __execution_detail::__policy_kind::parallel_unsequenced;
};

class unsequenced_policy {
public:
    static constexpr __execution_detail::__policy_kind __asc_policy_kind =
        __execution_detail::__policy_kind::unsequenced;
};

inline constexpr sequenced_policy seq{};
inline constexpr parallel_policy par{};
inline constexpr parallel_unsequenced_policy par_unseq{};
inline constexpr unsequenced_policy unseq{};

}  // namespace execution

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___EXECUTION_EXECUTION_POLICY_H
