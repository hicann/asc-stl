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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_COPY_IF_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_COPY_IF_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/in_out_result.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/projected.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/dangling.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {
template <class Iterator, class Output>
using copy_if_result = in_out_result<Iterator, Output>;

struct __copy_if_fn {
    CANN_ASC_STL_DETAIL_TEMPLATE(
        class Iterator, class Sentinel, class Output, class Predicate, class Projection = identity)
    CANN_ASC_STL_DETAIL_REQUIRES(input_iterator<Iterator>&& sentinel_for<Sentinel, Iterator>&&
            weakly_incrementable<Output>&& indirectly_copyable<Iterator, Output>&&
                indirect_unary_predicate<Predicate, projected<Iterator, Projection>>)
    CANN_ASC_STL_API constexpr copy_if_result<Iterator, Output> operator()(
        Iterator first, Sentinel last, Output output, Predicate predicate, Projection projection = {}) const
    {
        for (; first != last; ++first) {
            if (::asc::std::invoke(predicate, ::asc::std::invoke(projection, *first))) {
                *output = *first;
                ++output;
            }
        }
        return {::asc::std::move(first), ::asc::std::move(output)};
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class Range, class Output, class Predicate, class Projection = identity)
    CANN_ASC_STL_DETAIL_REQUIRES(
        input_range<Range>&& weakly_incrementable<Output>&& indirectly_copyable<iterator_t<Range>, Output>&&
            indirect_unary_predicate<Predicate, projected<iterator_t<Range>, Projection>>)
    CANN_ASC_STL_API constexpr copy_if_result<borrowed_iterator_t<Range>, Output> operator()(
        Range&& range, Output output, Predicate predicate, Projection projection = {}) const
    {
        return (*this)(ranges::__begin_cpo{}(range), ranges::__end_cpo{}(range), ::asc::std::move(output),
            ::asc::std::move(predicate), ::asc::std::move(projection));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __copy_if_fn copy_if{};

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_COPY_IF_H
