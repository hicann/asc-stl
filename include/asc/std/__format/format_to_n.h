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

#ifndef CANN_ASC_STL_ASC_STD___FORMAT_FORMAT_TO_N_H
#define CANN_ASC_STL_ASC_STD___FORMAT_FORMAT_TO_N_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__format/format_to.h>

#if CANN_ASC_STL_DETAIL_HAS_CXX20()

CANN_ASC_STL_BEGIN_NAMESPACE

// Aggregated result of format_to_n. Deliberately carries no deduction guide:
// the frozen device contract keeps CTAD off the public face and callers spell
// format_to_n_result<char*> out explicitly.
template <class Out>
struct format_to_n_result {
    Out out;
    ptrdiff_t size;
};

// Bounded form of format_to: writes at most count characters and reports the
// untruncated size a full-capacity buffer would have received.
template <class... Args>
CANN_ASC_STL_API constexpr format_to_n_result<char*> format_to_n(
    char* output, ptrdiff_t count, format_string<Args...> format, Args&&... args) noexcept
{
    const __SIZE_TYPE__ capacity = count < 0 ? 0 : static_cast<__SIZE_TYPE__>(count);
    const auto result = __format_detail::render_all(output, capacity, format, static_cast<Args&&>(args)...);
    const __SIZE_TYPE__ written = result.total < capacity ? result.total : capacity;
    return {output + written, static_cast<ptrdiff_t>(result.total)};
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_DETAIL_HAS_CXX20()

#endif  // CANN_ASC_STL_ASC_STD___FORMAT_FORMAT_TO_N_H
