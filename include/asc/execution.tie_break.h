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

#ifndef CANN_ASC_STL_EXECUTION_TIE_BREAK_H
#define CANN_ASC_STL_EXECUTION_TIE_BREAK_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

namespace asc {

// Policy for resolving equal extremes in min/max_element-style fronts.
enum class tie_break {
    // Any implementation choice is allowed; implementations pick their
    // fastest path and the returned index among equal elements is
    // unspecified.
    unspecified,
    // Among equal elements the earliest (smallest index) is returned.
    prefer_smaller_index,
    // Among equal elements the latest (largest index) is returned.
    prefer_larger_index,
};

// Current behaviour boundary: the value is recorded and observable through
// execution_requirements::tie_break_value(), but the parallel extreme-value
// fronts do not yet consult the policy, so results currently behave as
// `unspecified` regardless of the requested tie break.  Honouring the policy
// is a parallel-backend follow-up.

}  // namespace asc

#endif  // CANN_ASC_STL_EXECUTION_TIE_BREAK_H
