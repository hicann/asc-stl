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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_MIN_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_MIN_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/min_element.h>
#include <asc/std/__concepts/copyable.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__functional/ranges_operations.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/projected.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {
struct __min_fn {
    template <class T, class Projection = identity, class Compare = ranges::less>
    CANN_ASC_STL_API constexpr const T& operator()(
        const T& left, const T& right, Compare compare = {}, Projection projection = {}) const
    {
        return ::asc::std::invoke(
                   compare, ::asc::std::invoke(projection, right), ::asc::std::invoke(projection, left)) ?
            right :
            left;
    }
    template <class Range, class Compare = ranges::less, class Projection = identity,
        class = enable_if_t<is_invocable_v<Compare&, invoke_result_t<Projection&, iter_reference_t<iterator_t<Range>>>,
            invoke_result_t<Projection&, iter_reference_t<iterator_t<Range>>>>>>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr range_value_t<Range> operator()(
        Range&& range, Compare compare = {}, Projection projection = {}) const
    {
        auto first = ranges::begin(range);
        const auto last = ranges::end(range);
        range_value_t<Range> result = *first;
        while (++first != last) {
            if (::asc::std::invoke(
                    compare, ::asc::std::invoke(projection, *first), ::asc::std::invoke(projection, result))) {
                result = *first;
            }
        }
        return result;
    }
};
inline constexpr __min_fn min{};
}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_MIN_H
