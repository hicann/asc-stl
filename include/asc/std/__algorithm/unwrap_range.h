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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_UNWRAP_RANGE_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_UNWRAP_RANGE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/unwrap_iter.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/next.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// __unwrap_range and __rewrap_range are used to unwrap ranges which may have different iterator and sentinel types.
// __unwrap_iter and __rewrap_iter don't work for this, because they assume that the iterator and sentinel have
// the same type. __unwrap_range tries to get two iterators and then forward to __unwrap_iter.

template <class Iter, class Sent, bool Unwrap = random_access_iterator<Iter> && sized_sentinel_for<Sent, Iter>>
struct __unwrap_range_impl {
    CANN_ASC_STL_API static constexpr auto __unwrap(Iter first, Sent last)
    {
        if constexpr (Unwrap) {
            auto iter_last = ::asc::std::next(first, last - first);
            auto unwrapped_first = ::asc::std::__unwrap_iter(::asc::std::move(first));
            auto unwrapped_last = ::asc::std::__unwrap_iter(::asc::std::move(iter_last));
            return pair<decltype(unwrapped_first), decltype(unwrapped_last)>(
                ::asc::std::move(unwrapped_first), ::asc::std::move(unwrapped_last));
        } else {
            return pair<Iter, Sent>(::asc::std::move(first), ::asc::std::move(last));
        }
    }

    template <class Unwrapped>
    CANN_ASC_STL_API static constexpr Iter __rewrap(Iter original, Unwrapped current)
    {
        if constexpr (Unwrap) {
            return ::asc::std::__rewrap_iter(::asc::std::move(original), ::asc::std::move(current));
        } else {
            return current;
        }
    }
};

template <class Iter, bool Unwrap>
struct __unwrap_range_impl<Iter, Iter, Unwrap> {
    CANN_ASC_STL_API static constexpr auto __unwrap(Iter first, Iter last)
    {
        auto unwrapped_first = ::asc::std::__unwrap_iter(::asc::std::move(first));
        auto unwrapped_last = ::asc::std::__unwrap_iter(::asc::std::move(last));
        return pair<decltype(unwrapped_first), decltype(unwrapped_last)>(
            ::asc::std::move(unwrapped_first), ::asc::std::move(unwrapped_last));
    }

    template <class Unwrapped>
    CANN_ASC_STL_API static constexpr Iter __rewrap(Iter original, Unwrapped current)
    {
        return ::asc::std::__rewrap_iter(::asc::std::move(original), ::asc::std::move(current));
    }
};

template <class Iter, class Sent>
CANN_ASC_STL_API constexpr auto __unwrap_range(Iter first, Sent last)
{
    return __unwrap_range_impl<Iter, Sent>::__unwrap(::asc::std::move(first), ::asc::std::move(last));
}

template <class Sent, class Iter, class Unwrapped>
CANN_ASC_STL_API constexpr Iter __rewrap_range(Iter original, Unwrapped current)
{
    return __unwrap_range_impl<Iter, Sent>::__rewrap(
        ::asc::std::move(original), ::asc::std::move(current));  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_UNWRAP_RANGE_H
