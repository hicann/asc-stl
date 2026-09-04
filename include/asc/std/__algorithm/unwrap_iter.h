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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_UNWRAP_ITER_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_UNWRAP_ITER_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// TODO: Change the name of __unwrap_iter_impl to something more appropriate
// The job of __unwrap_iter is to remove iterator wrappers (like reverse_iterator or __wrap_iter),
// to reduce the number of template instantiations and to enable pointer-based optimizations e.g. in ::asc::std::copy.
// In debug mode, we don't do this.
//
// Some algorithms (e.g. ::asc::std::copy, but not ::asc::std::sort) need to convert an
// "unwrapped" result back into the original iterator type. Doing that is the job of __rewrap_iter.

// Default case - we can't unwrap anything
template <class _Iter, bool = __has_contiguous_traversal<_Iter>>
struct __unwrap_iter_impl {
    static CANN_ASC_STL_API constexpr _Iter __rewrap(_Iter, _Iter __iter)
    {
        return __iter;
    }
    static CANN_ASC_STL_API constexpr _Iter __unwrap(_Iter __i) noexcept
    {
        return __i;
    }
};

// It's a contiguous iterator, so we can use a raw pointer instead
template <class _Iter>
struct __unwrap_iter_impl<_Iter, true> {
    using _ToAddressT = decltype(::asc::std::__to_address(::asc::std::declval<_Iter>()));

    static CANN_ASC_STL_API constexpr _Iter __rewrap(_Iter __orig_iter, _ToAddressT __unwrapped_iter)
    {
        return __orig_iter + (__unwrapped_iter - ::asc::std::__to_address(__orig_iter));
    }

    static CANN_ASC_STL_API constexpr _ToAddressT __unwrap(_Iter __i) noexcept
    {
        return ::asc::std::__to_address(__i);
    }
};

template <class _Iter, class _Impl = __unwrap_iter_impl<_Iter>, enable_if_t<is_copy_constructible_v<_Iter>, int> = 0>
CANN_ASC_STL_API constexpr decltype(_Impl::__unwrap(::asc::std::declval<_Iter>())) __unwrap_iter(_Iter __i) noexcept
{
    return _Impl::__unwrap(__i);
}

template <class _OrigIter, class _Iter, class _Impl = __unwrap_iter_impl<_OrigIter>>
CANN_ASC_STL_API constexpr _OrigIter __rewrap_iter(_OrigIter __orig_iter, _Iter __iter) noexcept
{
    return _Impl::__rewrap(
        ::asc::std::move(__orig_iter), ::asc::std::move(__iter));  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_UNWRAP_ITER_H
