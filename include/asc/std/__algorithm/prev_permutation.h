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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_PREV_PERMUTATION_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_PREV_PERMUTATION_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/comp_ref_type.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__algorithm/reverse.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD
template <class _AlgPolicy, class _Compare, class _BidirectionalIterator, class _Sentinel>
CANN_ASC_STL_API constexpr pair<_BidirectionalIterator, bool> __prev_permutation(
    _BidirectionalIterator __first, _Sentinel __last, _Compare&& __comp)
{
    using _Result = pair<_BidirectionalIterator, bool>;

    _BidirectionalIterator __last_iter = _IterOps<_AlgPolicy>::next(__first, __last);
    _BidirectionalIterator __i = __last_iter;
    if (__first == __last || __first == --__i) {
        return _Result(::asc::std::move(__last_iter), false);
    }

    bool __result = true;
    while (true) {
        _BidirectionalIterator __ip1 = __i;
        if (__comp(*__ip1, *--__i)) {
            _BidirectionalIterator __j = __last_iter;
            while (!__comp(*--__j, *__i)) {
            }
            _IterOps<_AlgPolicy>::iter_swap(__i, __j);
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
CANN_ASC_STL_API constexpr bool prev_permutation(
    _BidirectionalIterator __first, _BidirectionalIterator __last, _Compare __comp)
{
    return ::asc::std::__prev_permutation<_ClassicAlgPolicy>(::asc::std::move(__first),
        ::asc::std::move(__last),                        // NOLINT(build/include_what_you_use)
        static_cast<__comp_ref_type<_Compare>>(__comp))  // NOLINT(build/include_what_you_use)
        .second;
}

template <class _BidirectionalIterator>
CANN_ASC_STL_API constexpr bool prev_permutation(_BidirectionalIterator __first, _BidirectionalIterator __last)
{
    return ::asc::std::prev_permutation(__first, __last, __less{});
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_PREV_PERMUTATION_H
