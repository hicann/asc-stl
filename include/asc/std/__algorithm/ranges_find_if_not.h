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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FIND_IF_NOT_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FIND_IF_NOT_H

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
#include <asc/std/__algorithm/ranges_find_if.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__functional/ranges_operations.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/projected.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/dangling.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if !defined(CANN_ASC_STL_DETAIL_FIND_IF_NOT_DEFINED)
#define CANN_ASC_STL_DETAIL_FIND_IF_NOT_DEFINED
template <class InputIterator, class Predicate>
CANN_ASC_STL_API constexpr InputIterator find_if_not(InputIterator first, InputIterator last, Predicate predicate)
{
    for (; first != last; ++first) {
        if (!predicate(*first)) {
            break;
        }
    }
    return first;
}
#endif

namespace ranges {
template <class Predicate>
struct __not_pred {
    CANN_ASC_STL_API constexpr __not_pred(Predicate& predicate) noexcept : __pred_(predicate)
    {}

    Predicate& __pred_;

    template <class T>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
    {
        return !::asc::std::invoke(__pred_, ::asc::std::forward<T>(value));
    }
};

struct __find_if_not_fn {
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class Iterator, class Sentinel, class Predicate, class Projection = identity>
        requires input_iterator<Iterator> && sentinel_for<Sentinel, Iterator> &&
        indirect_unary_predicate<Predicate, projected<Iterator, Projection>>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr Iterator operator()(
        Iterator first, Sentinel last, Predicate predicate, Projection projection = {}) const
    {
        return ranges::find_if(::asc::std::move(first), ::asc::std::move(last), __not_pred{predicate},
            ::asc::std::move(projection));  // NOLINT(build/include_what_you_use)
    }

    template <class Range, class Predicate, class Projection = identity>
        requires input_range<Range> && indirect_unary_predicate<Predicate, projected<iterator_t<Range>, Projection>>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr borrowed_iterator_t<Range> operator()(
        Range&& range, Predicate predicate, Projection projection = {}) const
    {
        // NOLINTNEXTLINE(build/include_what_you_use)
        return ranges::find_if(::asc::std::forward<Range>(range), __not_pred{predicate}, ::asc::std::move(projection));
    }
#else
    template <class Iterator, class Sentinel, class Predicate, class Projection = identity,
        class = decltype(::asc::std::declval<Iterator&>() != ::asc::std::declval<Sentinel&>()),
        class = enable_if_t<is_invocable_v<Predicate&, invoke_result_t<Projection&, iter_reference_t<Iterator>>>>>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr Iterator operator()(
        Iterator first, Sentinel last, Predicate predicate, Projection projection = {}) const
    {
        return ranges::find_if(::asc::std::move(first), ::asc::std::move(last), __not_pred{predicate},
            ::asc::std::move(projection));  // NOLINT(build/include_what_you_use)
    }

    template <class Range, class Predicate, class Projection = identity,
        class =
            enable_if_t<is_invocable_v<Predicate&, invoke_result_t<Projection&, iter_reference_t<iterator_t<Range>>>>>>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr borrowed_iterator_t<Range> operator()(
        Range&& range, Predicate predicate, Projection projection = {}) const
    {
        // NOLINTNEXTLINE(build/include_what_you_use)
        return ranges::find_if(::asc::std::forward<Range>(range), __not_pred{predicate}, ::asc::std::move(projection));
    }
#endif
};
inline constexpr __find_if_not_fn find_if_not{};
}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_RANGES_FIND_IF_NOT_H
