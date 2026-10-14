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

#ifndef CANN_ASC_STL_ASC___SYNCHRONIZATION_BARRIER_H
#define CANN_ASC_STL_ASC___SYNCHRONIZATION_BARRIER_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

namespace asc::detail {
// Placement contract: a barrier_state must reside in device global memory
// that every participating thread accesses through the same address (never
// in per-core private storage or an on-chip local copy). Phase completion is
// a cross-thread handshake on these fields through device-scope atomics; a
// copy that is not globally visible would never observe the completing
// thread's phase release.
struct barrier_state {
    __INT64_TYPE__ expected;
    __INT64_TYPE__ remaining;
    __UINT64_TYPE__ phase;
};
struct barrier_empty_completion {
#if CANN_ASC_STL_DETAIL_SIMT_COMPILATION()
    CANN_ASC_STL_SIMT_API void operator()() const noexcept
    {}
#else
    void operator()() const = delete;
#endif
};
}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___SYNCHRONIZATION_BARRIER_H
