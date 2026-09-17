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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_UPPER_BOUND_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_UPPER_BOUND_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/half_positive.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/distance.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD
template <class _AlgPolicy, class _Compare, class _Iter, class _Sent, class _Tp, class _Proj>
CANN_ASC_STL_API constexpr _Iter __upper_bound(
    _Iter __first, _Sent __last, const _Tp& __value, _Compare&& __comp, _Proj&& __proj)
{
    auto __len = _IterOps<_AlgPolicy>::distance(__first, __last);
    while (__len != 0) {
        auto __half_len = ::asc::std::__half_positive(__len);
        auto __mid = _IterOps<_AlgPolicy>::next(__first, __half_len);
        if (::asc::std::invoke(__comp, __value, ::asc::std::invoke(__proj, *__mid))) {
            __len = __half_len;
        } else {
            __first = ++__mid;
            __len -= __half_len + 1;
        }
    }
    return __first;
}
template <class _ForwardIterator, class _Tp, class _Compare>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator upper_bound(
    _ForwardIterator __first, _ForwardIterator __last, const _Tp& __value, _Compare __comp)
{
    static_assert(is_copy_constructible_v<_ForwardIterator>, "Iterator has to be copy constructible");
    return ::asc::std::__upper_bound<_ClassicAlgPolicy>(
        ::asc::std::move(__first), ::asc::std::move(__last), __value, ::asc::std::move(__comp), ::asc::std::identity());
}
template <class _ForwardIterator, class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator upper_bound(
    _ForwardIterator __first, _ForwardIterator __last, const _Tp& __value)
{
    return ::asc::std::upper_bound(
        ::asc::std::move(__first), ::asc::std::move(__last), __value, __less{});  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_UPPER_BOUND_H
