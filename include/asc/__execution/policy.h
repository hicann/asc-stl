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

#ifndef CANN_ASC_STL_ASC___EXECUTION_POLICY_H
#define CANN_ASC_STL_ASC___EXECUTION_POLICY_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

namespace asc::detail {

enum class execution_policy_kind : unsigned char { inline_host, device_simd, device_simt };

struct execution_policy_state {
    execution_policy_kind kind = execution_policy_kind::inline_host;
    void* stream = nullptr;
    unsigned int block_size = 0;
};

CANN_ASC_STL_API constexpr bool has_explicit_stream(const execution_policy_state& state) noexcept
{
    return state.stream != nullptr;
}

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___EXECUTION_POLICY_H
