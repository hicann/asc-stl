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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_REMOVE_IF_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_REMOVE_IF_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/permutable.h>
#include <asc/std/__iterator/projected.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/dangling.h>
#include <asc/std/__ranges/subrange.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {
struct __remove_if_fn {
    CANN_ASC_STL_DETAIL_TEMPLATE(class I, class S, class Pred, class Proj = identity)
    CANN_ASC_STL_DETAIL_REQUIRES(
        permutable<I>&& sentinel_for<S, I>&& indirect_unary_predicate<Pred, projected<I, Proj>>)
    CANN_ASC_STL_API constexpr subrange<I> operator()(I first, S last, Pred pred, Proj projection = {}) const
    {
        while (first != last && !::asc::std::invoke(pred, ::asc::std::invoke(projection, *first))) {
            ++first;
        }
        if (first == last) {
            return {first, first};
        }
        auto current = first;
        while (++current != last) {
            if (!::asc::std::invoke(pred, ::asc::std::invoke(projection, *current))) {
                *first = ::asc::std::iter_move(current);
                ++first;
            }
        }
        return {first, current};
    }
    CANN_ASC_STL_DETAIL_TEMPLATE(class R, class Pred, class Proj = identity)
    CANN_ASC_STL_DETAIL_REQUIRES(
        forward_range<R>&& permutable<iterator_t<R>>&& indirect_unary_predicate<Pred, projected<iterator_t<R>, Proj>>)
    CANN_ASC_STL_API constexpr borrowed_subrange_t<R> operator()(R&& range, Pred pred, Proj projection = {}) const
    {
        return (*this)(ranges::__begin_cpo{}(range), ranges::__end_cpo{}(range), ::asc::std::move(pred),
            ::asc::std::move(projection));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __remove_if_fn remove_if{};

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_REMOVE_IF_H
