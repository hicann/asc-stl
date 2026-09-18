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

// -*- C++ -*-
#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_SWAP_RANGES_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_SWAP_RANGES_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// 2+2 iterators: the shorter size will be used.
template <class _AlgPolicy, class _ForwardIterator1, class _Sentinel1, class _ForwardIterator2, class _Sentinel2>
CANN_ASC_STL_API constexpr pair<_ForwardIterator1, _ForwardIterator2> __swap_ranges(
    _ForwardIterator1 __first1, _Sentinel1 __last1, _ForwardIterator2 __first2, _Sentinel2 __last2)
{
    while (__first1 != __last1 && __first2 != __last2) {
        _IterOps<_AlgPolicy>::iter_swap(__first1, __first2);
        ++__first1;
        ++__first2;
    }

    return pair<_ForwardIterator1, _ForwardIterator2>(::asc::std::move(__first1), ::asc::std::move(__first2));
}

// 2+1 iterators: size2 >= size1.
template <class _AlgPolicy, class _ForwardIterator1, class _Sentinel1, class _ForwardIterator2>
CANN_ASC_STL_API constexpr pair<_ForwardIterator1, _ForwardIterator2> __swap_ranges(
    _ForwardIterator1 __first1, _Sentinel1 __last1, _ForwardIterator2 __first2)
{
    while (__first1 != __last1) {
        _IterOps<_AlgPolicy>::iter_swap(__first1, __first2);
        ++__first1;
        ++__first2;
    }

    return pair<_ForwardIterator1, _ForwardIterator2>(::asc::std::move(__first1), ::asc::std::move(__first2));
}
template <class _ForwardIterator1, class _ForwardIterator2>
CANN_ASC_STL_API constexpr _ForwardIterator2 swap_ranges(
    _ForwardIterator1 __first1, _ForwardIterator1 __last1, _ForwardIterator2 __first2)
{
    return ::asc::std::__swap_ranges<_ClassicAlgPolicy>(::asc::std::move(__first1), ::asc::std::move(__last1),
        ::asc::std::move(__first2))  // NOLINT(build/include_what_you_use)
        .second;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_SWAP_RANGES_H
