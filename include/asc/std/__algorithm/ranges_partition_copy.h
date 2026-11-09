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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_PARTITION_COPY_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_PARTITION_COPY_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/in_out_out_result.h>
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
template <class Iterator, class Output1, class Output2>
using partition_copy_result = in_out_out_result<Iterator, Output1, Output2>;

struct __partition_copy_fn {
    CANN_ASC_STL_DETAIL_TEMPLATE(class I, class S, class O1, class O2, class Pred, class Proj = identity)
    CANN_ASC_STL_DETAIL_REQUIRES(input_iterator<I>&& sentinel_for<S, I>&& weakly_incrementable<O1>&&
            weakly_incrementable<O2>&& indirectly_copyable<I, O1>&& indirectly_copyable<I, O2>&&
                indirect_unary_predicate<Pred, projected<I, Proj>>)
    CANN_ASC_STL_API constexpr partition_copy_result<I, O1, O2> operator()(
        I first, S last, O1 yes, O2 no, Pred pred, Proj projection = {}) const
    {
        for (; first != last; ++first) {
            if (::asc::std::invoke(pred, ::asc::std::invoke(projection, *first))) {
                *yes = *first;
                ++yes;
            } else {
                *no = *first;
                ++no;
            }
        }
        return {::asc::std::move(first), ::asc::std::move(yes), ::asc::std::move(no)};
    }
    CANN_ASC_STL_DETAIL_TEMPLATE(class R, class O1, class O2, class Pred, class Proj = identity)
    CANN_ASC_STL_DETAIL_REQUIRES(
        input_range<R>&& weakly_incrementable<O1>&& weakly_incrementable<O2>&& indirectly_copyable<iterator_t<R>, O1>&&
            indirectly_copyable<iterator_t<R>, O2>&& indirect_unary_predicate<Pred, projected<iterator_t<R>, Proj>>)
    CANN_ASC_STL_API constexpr partition_copy_result<borrowed_iterator_t<R>, O1, O2> operator()(
        R&& range, O1 yes, O2 no, Pred pred, Proj projection = {}) const
    {
        return (*this)(ranges::__begin_cpo{}(range), ranges::__end_cpo{}(range), ::asc::std::move(yes),
            ::asc::std::move(no), ::asc::std::move(pred),
            ::asc::std::move(projection));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __partition_copy_fn partition_copy{};

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_PARTITION_COPY_H
