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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FIND_IF_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FIND_IF_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/__detail/execution_space.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__functional/ranges_operations.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/projected.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/dangling.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if !defined(CANN_ASC_STL_DETAIL_FIND_IF_DEFINED)
#define CANN_ASC_STL_DETAIL_FIND_IF_DEFINED
template <class InputIterator, class Predicate>
CANN_ASC_STL_API constexpr InputIterator find_if(InputIterator first, InputIterator last, Predicate predicate)
{
    for (; first != last; ++first) {
        if (predicate(*first)) {
            break;
        }
    }
    return first;
}
#endif

namespace ranges {
struct __find_if_fn {
    template <class Iterator, class Sentinel, class Predicate, class Projection>
    CANN_ASC_STL_API static constexpr Iterator __find_if_impl(
        Iterator first, Sentinel last, Predicate& predicate, Projection& projection)
    {
        for (; first != last; ++first) {
            if (::asc::std::invoke(predicate, ::asc::std::invoke(projection, *first))) {
                break;
            }
        }
        return first;
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class Iterator, class Sentinel, class Predicate, class Projection = identity)
    CANN_ASC_STL_DETAIL_REQUIRES(input_iterator<Iterator>&& sentinel_for<Sentinel, Iterator>&&
            indirect_unary_predicate<Predicate, projected<Iterator, Projection>>)
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr Iterator operator()(
        Iterator first, Sentinel last, Predicate predicate, Projection projection = {}) const
    {
        // NOLINTNEXTLINE(build/include_what_you_use)
        return __find_if_impl(::asc::std::move(first), ::asc::std::move(last), predicate, projection);
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class Range, class Predicate, class Projection = identity)
    CANN_ASC_STL_DETAIL_REQUIRES(
        input_range<Range>&& indirect_unary_predicate<Predicate, projected<iterator_t<Range>, Projection>>)
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr borrowed_iterator_t<Range> operator()(
        Range&& range, Predicate predicate, Projection projection = {}) const
    {
        return __find_if_impl(ranges::__begin_cpo{}(range), ranges::__end_cpo{}(range), predicate, projection);
    }
};
inline constexpr __find_if_fn find_if{};
}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FIND_IF_H
