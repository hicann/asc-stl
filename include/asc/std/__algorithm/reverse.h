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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_REVERSE_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_REVERSE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/iter_swap.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _AlgPolicy, class _BidirectionalIterator>
CANN_ASC_STL_API constexpr void __reverse_impl(
    _BidirectionalIterator __first, _BidirectionalIterator __last, bidirectional_iterator_tag)
{
    while (__first != __last) {
        if (__first == --__last) {
            break;
        }
        _AlgPolicy::iter_swap(__first, __last);
        ++__first;
    }
}

template <class _AlgPolicy, class _RandomAccessIterator>
CANN_ASC_STL_API constexpr void __reverse_impl(
    _RandomAccessIterator __first, _RandomAccessIterator __last, random_access_iterator_tag)
{
    if (__first != __last) {
        for (; __first < --__last; ++__first) {
            _AlgPolicy::iter_swap(__first, __last);
        }
    }
}

template <class _AlgPolicy, class _BidirectionalIterator, class _Sentinel>
CANN_ASC_STL_API constexpr void __reverse(_BidirectionalIterator __first, _Sentinel __last)
{
    using _IterCategory = typename iterator_traits<_BidirectionalIterator>::iterator_category;
    ::asc::std::__reverse_impl<_AlgPolicy>(::asc::std::move(__first), ::asc::std::move(__last), _IterCategory());
}

template <class _BidirectionalIterator>
CANN_ASC_STL_API constexpr void reverse(_BidirectionalIterator __first, _BidirectionalIterator __last)
{
    ::asc::std::__reverse<__classic_algorithm_iterator_operations>(  // NOLINT(build/include_what_you_use)
                                                                     // NOLINTNEXTLINE(build/include_what_you_use)
        ::asc::std::move(__first), ::asc::std::move(__last));
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_REVERSE_H
