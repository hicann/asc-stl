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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_MIN_ELEMENT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_MIN_ELEMENT_H

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
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__functional/ranges_operations.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/projected.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/dangling.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {
struct __min_element_fn {
    CANN_ASC_STL_DETAIL_TEMPLATE(
        class Iterator, class Sentinel, class Compare = ranges::less, class Projection = identity)
    CANN_ASC_STL_DETAIL_REQUIRES(forward_iterator<Iterator>&& sentinel_for<Sentinel, Iterator>&&
            indirect_strict_weak_order<Compare, projected<Iterator, Projection>>)
    CANN_ASC_STL_API constexpr Iterator operator()(
        Iterator first, Sentinel last, Compare compare = {}, Projection projection = {}) const
    {
        if (first == last) {
            return first;
        }
        Iterator result = first;
        while (++first != last) {
            if (::asc::std::invoke(
                    compare, ::asc::std::invoke(projection, *first), ::asc::std::invoke(projection, *result))) {
                result = first;
            }
        }
        return result;
    }
    CANN_ASC_STL_DETAIL_TEMPLATE(class Range, class Compare = ranges::less, class Projection = identity)
    CANN_ASC_STL_DETAIL_REQUIRES(
        forward_range<Range>&& indirect_strict_weak_order<Compare, projected<iterator_t<Range>, Projection>>)
    CANN_ASC_STL_API constexpr borrowed_iterator_t<Range> operator()(
        Range&& range, Compare compare = {}, Projection projection = {}) const
    {
        return (*this)(ranges::__begin_cpo{}(range), ranges::__end_cpo{}(range), compare, projection);
    }
};
inline constexpr __min_element_fn min_element{};
}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_MIN_ELEMENT_H
