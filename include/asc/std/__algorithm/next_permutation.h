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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_NEXT_PERMUTATION_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_NEXT_PERMUTATION_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/comp_ref_type.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/reverse.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// Policy-based core returning the last iterator plus whether a next permutation existed, kept as
// the extension point for the ranges flavour. The sentinel is converted to an iterator up front;
// the classic policy's `next(__first, __last)` degenerates to the sentinel itself for iterator
// sentinels.
template <class _AlgPolicy, class _Compare, class _BidirectionalIterator, class _Sentinel>
CANN_ASC_STL_API constexpr pair<_BidirectionalIterator, bool> __next_permutation(
    _BidirectionalIterator __first, _Sentinel __last, _Compare&& __comp)
{
    using _Result = pair<_BidirectionalIterator, bool>;

    _BidirectionalIterator __last_iter = ::asc::std::move(__last);  // NOLINT(build/include_what_you_use)
    _BidirectionalIterator __i = __last_iter;
    if (__first == __last || __first == --__i) {
        return _Result(::asc::std::move(__last_iter), false);
    }

    bool __result = true;
    while (true) {
        _BidirectionalIterator __ip1 = __i;
        if (__comp(*--__i, *__ip1)) {
            _BidirectionalIterator __j = __last_iter;
            while (!__comp(*__i, *--__j)) {
            }
            _AlgPolicy::iter_swap(__i, __j);
            ::asc::std::__reverse<_AlgPolicy>(__ip1, __last_iter);
            __result = true;
            break;
        }
        if (__i == __first) {
            ::asc::std::__reverse<_AlgPolicy>(__first, __last_iter);
            __result = false;
            break;
        }
    }
    return _Result(::asc::std::move(__last_iter), __result);
}

template <class _BidirectionalIterator, class _Compare>
CANN_ASC_STL_API constexpr bool next_permutation(
    _BidirectionalIterator __first, _BidirectionalIterator __last, _Compare __comp)
{
    return ::asc::std::__next_permutation<
        __classic_algorithm_iterator_operations>(  // NOLINT(build/include_what_you_use)
        ::asc::std::move(__first),
        ::asc::std::move(__last),                        // NOLINT(build/include_what_you_use)
        static_cast<__comp_ref_type<_Compare>>(__comp))  // NOLINT(build/include_what_you_use)
        .second;
}

template <class _BidirectionalIterator>
CANN_ASC_STL_API constexpr bool next_permutation(_BidirectionalIterator __first, _BidirectionalIterator __last)
{
    return ::asc::std::next_permutation(__first, __last, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_NEXT_PERMUTATION_H
