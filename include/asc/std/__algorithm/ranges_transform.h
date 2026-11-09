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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_TRANSFORM_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_TRANSFORM_H

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
#include <asc/std/__algorithm/in_in_out_result.h>
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
using unary_transform_result = in_out_result<Iterator, Output>;

template <class Iterator1, class Iterator2, class Output>
using binary_transform_result = in_in_out_result<Iterator1, Iterator2, Output>;

struct __transform_fn {
    CANN_ASC_STL_DETAIL_TEMPLATE(class I, class S, class O, class F, class Proj = identity)
    CANN_ASC_STL_DETAIL_REQUIRES(input_iterator<I>&& sentinel_for<S, I>&& weakly_incrementable<O>&&
            copy_constructible<F>&& indirectly_writable<O, indirect_result_t<F&, projected<I, Proj>>>)
    CANN_ASC_STL_API constexpr unary_transform_result<I, O> operator()(
        I first, S last, O out, F function, Proj projection = {}) const
    {
        for (; first != last; ++first, (void)++out) {
            *out = ::asc::std::invoke(function, ::asc::std::invoke(projection, *first));
        }
        return {::asc::std::move(first), ::asc::std::move(out)};
    }
    CANN_ASC_STL_DETAIL_TEMPLATE(class R, class O, class F, class Proj = identity)
    CANN_ASC_STL_DETAIL_REQUIRES(input_range<R>&& weakly_incrementable<O>&& copy_constructible<F>&&
            indirectly_writable<O, indirect_result_t<F&, projected<iterator_t<R>, Proj>>>)
    CANN_ASC_STL_API constexpr unary_transform_result<borrowed_iterator_t<R>, O> operator()(
        R&& range, O out, F function, Proj projection = {}) const
    {
        return (*this)(ranges::__begin_cpo{}(range), ranges::__end_cpo{}(range), ::asc::std::move(out),
            ::asc::std::move(function), ::asc::std::move(projection));
    }
    CANN_ASC_STL_DETAIL_TEMPLATE(
        class I1, class S1, class I2, class S2, class O, class F, class Proj1 = identity, class Proj2 = identity)
    CANN_ASC_STL_DETAIL_REQUIRES(input_iterator<I1>&& sentinel_for<S1, I1>&& input_iterator<I2>&& sentinel_for<S2, I2>&&
            weakly_incrementable<O>&& copy_constructible<F>&&
                indirectly_writable<O, indirect_result_t<F&, projected<I1, Proj1>, projected<I2, Proj2>>>)
    CANN_ASC_STL_API constexpr binary_transform_result<I1, I2, O> operator()(I1 first1, S1 last1, I2 first2, S2 last2,
        O output, F function, Proj1 projection1 = {}, Proj2 projection2 = {}) const
    {
        for (; first1 != last1 && first2 != last2; ++first1, (void)++first2, (void)++output) {
            *output = ::asc::std::invoke(
                function, ::asc::std::invoke(projection1, *first1), ::asc::std::invoke(projection2, *first2));
        }
        return {::asc::std::move(first1), ::asc::std::move(first2), ::asc::std::move(output)};
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class R1, class R2, class O, class F, class Proj1 = identity, class Proj2 = identity)
    CANN_ASC_STL_DETAIL_REQUIRES(
        input_range<R1>&& input_range<R2>&& weakly_incrementable<O>&& copy_constructible<F>&& indirectly_writable<O,
            indirect_result_t<F&, projected<iterator_t<R1>, Proj1>, projected<iterator_t<R2>, Proj2>>>)
    CANN_ASC_STL_API constexpr binary_transform_result<borrowed_iterator_t<R1>, borrowed_iterator_t<R2>, O> operator()(
        R1&& range1, R2&& range2, O output, F function, Proj1 projection1 = {}, Proj2 projection2 = {}) const
    {
        return (*this)(ranges::__begin_cpo{}(range1), ranges::__end_cpo{}(range1), ranges::__begin_cpo{}(range2),
            ranges::__end_cpo{}(range2), ::asc::std::move(output), ::asc::std::move(function),
            ::asc::std::move(projection1), ::asc::std::move(projection2));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __transform_fn transform{};

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_TRANSFORM_H
