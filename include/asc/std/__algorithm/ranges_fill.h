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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FILL_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FILL_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/dangling.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {
struct __fill_fn {
    CANN_ASC_STL_DETAIL_TEMPLATE(class O, class S, class T)
    CANN_ASC_STL_DETAIL_REQUIRES(output_iterator<O, const T&>&& sentinel_for<S, O>)
    CANN_ASC_STL_API constexpr O operator()(O first, S last, const T& value) const
    {
        for (; first != last; ++first) {
            *first = value;
        }
        return first;
    }
    CANN_ASC_STL_DETAIL_TEMPLATE(class R, class T)
    CANN_ASC_STL_DETAIL_REQUIRES(output_range<R, const T&>)
    CANN_ASC_STL_API constexpr borrowed_iterator_t<R> operator()(R&& range, const T& value) const
    {
        return (*this)(ranges::__begin_cpo{}(range), ranges::__end_cpo{}(range), value);
    }
};
inline constexpr __fill_fn fill{};

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FILL_H
