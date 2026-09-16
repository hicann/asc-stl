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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_MIN_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_MIN_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/comp_ref_type.h>
#include <asc/std/__algorithm/min_element.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T, class Compare>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr const T& min(const T& left, const T& right, Compare compare)
{
    return compare(right, left) ? right : left;
}
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr const T& min(const T& left, const T& right)
{
    return ::asc::std::min(left, right, __less{});  // NOLINT(build/include_what_you_use)
}
#if !defined(CANN_ASC_STL_DETAIL_RANGES_MIN_DEFINED)
#define CANN_ASC_STL_DETAIL_RANGES_MIN_DEFINED
namespace ranges {
struct __min_fn {
    template <class T, class Compare = __less>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr const T& operator()(
        const T& left, const T& right, Compare compare = {}) const
    {
        return ::asc::std::min(left, right, compare);  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __min_fn min{};
}  // namespace ranges
#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_MIN_H
