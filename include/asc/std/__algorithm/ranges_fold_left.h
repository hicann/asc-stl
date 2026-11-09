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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FOLD_LEFT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FOLD_LEFT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/assignable.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__concepts/movable.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {
template <class T, class Iterator, class Function>
using __fold_left_result_t = decay_t<invoke_result_t<Function&, T, iter_reference_t<Iterator>>>;

template <class T, class Iterator, class Function, class = void>
inline constexpr bool __left_foldable = false;

template <class T, class Iterator, class Function>
inline constexpr bool __left_foldable<T, Iterator, Function,
    void_t<invoke_result_t<Function&, T, iter_reference_t<Iterator>>,
        invoke_result_t<Function&, decay_t<invoke_result_t<Function&, T, iter_reference_t<Iterator>>>,
            iter_reference_t<Iterator>>>> = copy_constructible<Function> && movable<T> &&
    movable<decay_t<invoke_result_t<Function&, T, iter_reference_t<Iterator>>>> &&
    convertible_to<T, decay_t<invoke_result_t<Function&, T, iter_reference_t<Iterator>>>> &&
    assignable_from<__fold_left_result_t<T, Iterator, Function>&,
        invoke_result_t<Function&, decay_t<invoke_result_t<Function&, T, iter_reference_t<Iterator>>>,
            iter_reference_t<Iterator>>>;

struct __fold_left_fn {
    CANN_ASC_STL_DETAIL_TEMPLATE(class Iterator, class Sentinel, class T, class Function)
    CANN_ASC_STL_DETAIL_REQUIRES(
        input_iterator<Iterator>&& sentinel_for<Sentinel, Iterator>&& __left_foldable<T, Iterator, Function>)
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr auto operator()(
        Iterator first, Sentinel last, T init, Function function) const
    {
        using Result = decay_t<invoke_result_t<Function&, T, iter_reference_t<Iterator>>>;
        if (first == last) {
            return Result(::asc::std::move(init));
        }
        Result result = ::asc::std::invoke(function, ::asc::std::move(init), *first);
        for (++first; first != last; ++first) {
            result = ::asc::std::invoke(function, ::asc::std::move(result), *first);
        }
        return result;
    }

    CANN_ASC_STL_DETAIL_TEMPLATE(class Range, class T, class Function)
    CANN_ASC_STL_DETAIL_REQUIRES(input_range<Range>&& __left_foldable<T, iterator_t<Range>, Function>)
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr auto operator()(Range&& range, T init, Function function) const
    {
        return (*this)(ranges::__begin_cpo{}(range), ranges::__end_cpo{}(range), ::asc::std::move(init),
            ::asc::std::move(function));  // NOLINT(build/include_what_you_use)
    }
};
inline constexpr __fold_left_fn fold_left{};
}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FOLD_LEFT_H
