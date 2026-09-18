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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_PARTITION_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_PARTITION_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _Predicate, class _AlgPolicy, class _ForwardIterator, class _Sentinel>
CANN_ASC_STL_API constexpr pair<_ForwardIterator, _ForwardIterator> __partition_impl(
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
            _AlgPolicy::iter_swap(__first, __p);
            ++__first;
        }
    }
    return ::asc::std::make_pair(::asc::std::move(__first), ::asc::std::move(__p));
}

template <class _Predicate, class _AlgPolicy, class _BidirectionalIterator, class _Sentinel>
CANN_ASC_STL_API constexpr pair<_BidirectionalIterator, _BidirectionalIterator> __partition_impl(
    _BidirectionalIterator __first, _Sentinel __sentinel, _Predicate __pred, bidirectional_iterator_tag)
{
    _BidirectionalIterator __original_last = __first;
    while (__original_last != __sentinel) {
        ++__original_last;
    }
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
        _AlgPolicy::iter_swap(__first, __last);
        ++__first;
    }
}

template <class _AlgPolicy, class _ForwardIterator, class _Sentinel, class _Predicate, class _IterCategory>
CANN_ASC_STL_API constexpr pair<_ForwardIterator, _ForwardIterator> __partition(
    _ForwardIterator __first, _Sentinel __last, _Predicate&& __pred, _IterCategory __iter_category)
{
    return ::asc::std::__partition_impl<remove_cvref_t<_Predicate>&, _AlgPolicy>(
        ::asc::std::move(__first), ::asc::std::move(__last), __pred, __iter_category);
}

template <class _ForwardIterator, class _Predicate>
CANN_ASC_STL_API constexpr _ForwardIterator partition(
    _ForwardIterator __first, _ForwardIterator __last, _Predicate __pred)
{
    using _IterCategory = typename iterator_traits<_ForwardIterator>::iterator_category;
    auto __result = ::asc::std::__partition<__classic_algorithm_iterator_operations>(::asc::std::move(__first),
        ::asc::std::move(__last), __pred, _IterCategory());  // NOLINT(build/include_what_you_use)
    return __result.first;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_PARTITION_H
