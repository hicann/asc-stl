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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_SWAP_RANGES_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_SWAP_RANGES_H

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
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// 2+2 迭代器：按两个范围的较短者截断，返回双方停止位置。
// 首个模板参数为算法策略占位（默认 void），供按策略分派的内部算法以
// __swap_ranges<策略>(...) 形式复用。
template <class _AlgPolicy = void, class _ForwardIterator1, class _Sentinel1, class _ForwardIterator2, class _Sentinel2>
CANN_ASC_STL_API constexpr pair<_ForwardIterator1, _ForwardIterator2> __swap_ranges(
    _ForwardIterator1 __first1, _Sentinel1 __last1, _ForwardIterator2 __first2, _Sentinel2 __last2)
{
    while (__first1 != __last1 && __first2 != __last2) {
        ::asc::std::iter_swap(__first1, __first2);
        ++__first1;
        ++__first2;
    }
    return {::asc::std::move(__first1), ::asc::std::move(__first2)};  // NOLINT(build/include_what_you_use)
}

// 2+1 迭代器：要求第二范围不短于第一范围。
template <class _AlgPolicy = void, class _ForwardIterator1, class _Sentinel1, class _ForwardIterator2>
CANN_ASC_STL_API constexpr pair<_ForwardIterator1, _ForwardIterator2> __swap_ranges(
    _ForwardIterator1 __first1, _Sentinel1 __last1, _ForwardIterator2 __first2)
{
    while (__first1 != __last1) {
        ::asc::std::iter_swap(__first1, __first2);
        ++__first1;
        ++__first2;
    }
    return {::asc::std::move(__first1), ::asc::std::move(__first2)};  // NOLINT(build/include_what_you_use)
}

template <class ForwardIterator1, class ForwardIterator2>
CANN_ASC_STL_API constexpr ForwardIterator2 swap_ranges(
    ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2)
{
    return ::asc::std::__swap_ranges(::asc::std::move(first1),
        ::asc::std::move(last1),   // NOLINT(build/include_what_you_use)
        ::asc::std::move(first2))  // NOLINT(build/include_what_you_use)
        .second;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_SWAP_RANGES_H
