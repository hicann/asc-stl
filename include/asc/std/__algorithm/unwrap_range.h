/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_UNWRAP_RANGE_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_UNWRAP_RANGE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/unwrap_iter.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/next.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// __unwrap_range and __rewrap_range are used to unwrap ranges which may have different iterator and sentinel types.
// __unwrap_iter and __rewrap_iter don't work for this, because they assume that the iterator and sentinel have
// the same type. __unwrap_range tries to get two iterators and then forward to __unwrap_iter.

#if CANN_ASC_STL_DETAIL_STD_VER >= 2020
template <class _Iter, class _Sent>
struct __unwrap_range_impl {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(bool _Dummy = true)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(random_access_iterator<_Iter>&& sized_sentinel_for<_Sent, _Iter>)
    CANN_ASC_STL_API static constexpr auto __unwrap(_Iter __first, _Sent __sent)
    {
        auto __last = ::asc::std::ranges::__next_cpo{}(__first, __sent);
        return ::asc::std::make_pair(
            ::asc::std::__unwrap_iter(::asc::std::move(__first)), ::asc::std::__unwrap_iter(::asc::std::move(__last)));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(bool _Dummy = true)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(!(random_access_iterator<_Iter> && sized_sentinel_for<_Sent, _Iter>))
    CANN_ASC_STL_API static constexpr auto __unwrap(_Iter __first, _Sent __last)
    {
        return ::asc::std::make_pair(::asc::std::move(__first), ::asc::std::move(__last));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(bool _Dummy = true)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(random_access_iterator<_Iter>&& sized_sentinel_for<_Sent, _Iter>)
    CANN_ASC_STL_API static constexpr auto __rewrap(
        _Iter __orig_iter, decltype(::asc::std::__unwrap_iter(::asc::std::move(__orig_iter))) __iter)
    {
        return ::asc::std::__rewrap_iter(::asc::std::move(__orig_iter), ::asc::std::move(__iter));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(bool _Dummy = true)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(!(random_access_iterator<_Iter> && sized_sentinel_for<_Sent, _Iter>))
    CANN_ASC_STL_API static constexpr auto __rewrap(const _Iter&, _Iter __iter)
    {
        return __iter;
    }
};

template <class _Iter>
struct __unwrap_range_impl<_Iter, _Iter> {
    CANN_ASC_STL_API static constexpr auto __unwrap(_Iter __first, _Iter __last)
    {
        return ::asc::std::make_pair(
            ::asc::std::__unwrap_iter(::asc::std::move(__first)), ::asc::std::__unwrap_iter(::asc::std::move(__last)));
    }

    CANN_ASC_STL_API static constexpr auto __rewrap(
        _Iter __orig_iter, decltype(::asc::std::__unwrap_iter(__orig_iter)) __iter)
    {
        return ::asc::std::__rewrap_iter(::asc::std::move(__orig_iter), ::asc::std::move(__iter));
    }
};

template <class _Iter, class _Sent>
CANN_ASC_STL_API constexpr auto __unwrap_range(_Iter __first, _Sent __last)
{
    return __unwrap_range_impl<_Iter, _Sent>::__unwrap(::asc::std::move(__first), ::asc::std::move(__last));
}

template <class _Sent, class _Iter, class _Unwrapped>
CANN_ASC_STL_API constexpr _Iter __rewrap_range(_Iter __orig_iter, _Unwrapped __iter)
{
    return __unwrap_range_impl<_Iter, _Sent>::__rewrap(::asc::std::move(__orig_iter), ::asc::std::move(__iter));
}
#else   // ^^^ C++20 ^^^ / vvv C++17 vvv
template <class _Iter, class _Unwrapped = decltype(::asc::std::__unwrap_iter(::asc::std::declval<_Iter>()))>
CANN_ASC_STL_API constexpr pair<_Unwrapped, _Unwrapped> __unwrap_range(_Iter __first, _Iter __last)
{
    return ::asc::std::make_pair(
        ::asc::std::__unwrap_iter(::asc::std::move(__first)), ::asc::std::__unwrap_iter(::asc::std::move(__last)));
}

template <class _Iter, class _Unwrapped>
CANN_ASC_STL_API constexpr _Iter __rewrap_range(_Iter __orig_iter, _Unwrapped __iter)
{
    return ::asc::std::__rewrap_iter(
        ::asc::std::move(__orig_iter), ::asc::std::move(__iter));  // NOLINT(build/include_what_you_use)
}
#endif  // CANN_ASC_STL_DETAIL_STD_VER <= 2017

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_UNWRAP_RANGE_H
