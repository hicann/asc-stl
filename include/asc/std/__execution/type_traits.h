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

#ifndef CANN_ASC_STL_ASC_STD___EXECUTION_TYPE_TRAITS_H
#define CANN_ASC_STL_ASC_STD___EXECUTION_TYPE_TRAITS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

namespace execution {
class sequenced_policy;
class parallel_policy;
class parallel_unsequenced_policy;
class unsequenced_policy;
}  // namespace execution

template <class T>
struct is_execution_policy {
    static constexpr bool value = false;
};

#define CANN_ASC_STL_DETAIL_EXECUTION_POLICY_TRAIT(policy) \
    template <>                                            \
    struct is_execution_policy<execution::policy> {        \
        static constexpr bool value = true;                \
    }

CANN_ASC_STL_DETAIL_EXECUTION_POLICY_TRAIT(sequenced_policy);
CANN_ASC_STL_DETAIL_EXECUTION_POLICY_TRAIT(parallel_policy);
CANN_ASC_STL_DETAIL_EXECUTION_POLICY_TRAIT(parallel_unsequenced_policy);
CANN_ASC_STL_DETAIL_EXECUTION_POLICY_TRAIT(unsequenced_policy);

#undef CANN_ASC_STL_DETAIL_EXECUTION_POLICY_TRAIT

template <class T>
inline constexpr bool is_execution_policy_v = is_execution_policy<T>::value;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___EXECUTION_TYPE_TRAITS_H
