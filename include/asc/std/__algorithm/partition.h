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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_PARTITION_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_PARTITION_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD
template <class _Predicate, class _AlgPolicy, class _ForwardIterator, class _Sentinel>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr pair<_ForwardIterator, _ForwardIterator> __partition_impl(
    _ForwardIterator __first, _Sentinel __last, _Predicate __pred, forward_iterator_tag)
{
    while (true) {
        if (__first == __last) {
            return ::asc::std::make_pair(::asc::std::move(__first), ::asc::std::move(__first));
        }
        if (!__pred(*__first)) {
            break;
        }
        ++__first;
    }

    _ForwardIterator __p = __first;
    while (++__p != __last) {
        if (__pred(*__p)) {
            _IterOps<_AlgPolicy>::iter_swap(__first, __p);
            ++__first;
        }
    }
    return ::asc::std::make_pair(::asc::std::move(__first), ::asc::std::move(__p));
}
template <class _Predicate, class _AlgPolicy, class _BidirectionalIterator, class _Sentinel>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr pair<_BidirectionalIterator, _BidirectionalIterator> __partition_impl(
    _BidirectionalIterator __first, _Sentinel __sentinel, _Predicate __pred, bidirectional_iterator_tag)
{
    _BidirectionalIterator __original_last = _IterOps<_AlgPolicy>::next(__first, __sentinel);
    _BidirectionalIterator __last = __original_last;

    while (true) {
        while (true) {
            if (__first == __last) {
                return ::asc::std::make_pair(::asc::std::move(__first), ::asc::std::move(__original_last));
            }
            if (!__pred(*__first)) {
                break;
            }
            ++__first;
        }
        do {
            if (__first == --__last) {
                return ::asc::std::make_pair(::asc::std::move(__first), ::asc::std::move(__original_last));
            }
        } while (!__pred(*__last));
        _IterOps<_AlgPolicy>::iter_swap(__first, __last);
        ++__first;
    }
}
template <class _AlgPolicy, class _ForwardIterator, class _Sentinel, class _Predicate, class _IterCategory>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr pair<_ForwardIterator, _ForwardIterator> __partition(
    _ForwardIterator __first, _Sentinel __last, _Predicate&& __pred, _IterCategory __iter_category)
{
    return ::asc::std::__partition_impl<remove_cvref_t<_Predicate>&, _AlgPolicy>(
        ::asc::std::move(__first), ::asc::std::move(__last), __pred, __iter_category);
}
template <class _ForwardIterator, class _Predicate>
CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr _ForwardIterator partition(
    _ForwardIterator __first, _ForwardIterator __last, _Predicate __pred)
{
    using _IterCategory = __iterator_traits_category_or_concept_t<_ForwardIterator>;
    auto __result = ::asc::std::__partition<_ClassicAlgPolicy>(::asc::std::move(__first),
        ::asc::std::move(__last),  // NOLINT(build/include_what_you_use)
        __pred, _IterCategory());  // NOLINT(build/include_what_you_use)
    return __result.first;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_PARTITION_H
