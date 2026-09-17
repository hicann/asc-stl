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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_UNIQUE_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_UNIQUE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/adjacent_find.h>
#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/iterator_operations.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD
template <class _AlgPolicy, class _Iter, class _Sent, class _BinaryPredicate>
[[nodiscard]] CANN_ASC_STL_API constexpr ::asc::std::pair<_Iter, _Iter> __unique(
    _Iter __first, _Sent __last, _BinaryPredicate&& __pred)
{
    __first = ::asc::std::adjacent_find(__first, __last, __pred);
    if (__first != __last) {
        // ...  a  a  ?  ...
        //      f     i
        _Iter __i = __first;
        for (++__i; ++__i != __last;) {
            if (!__pred(*__first, *__i)) {
                *++__first = _IterOps<_AlgPolicy>::__iter_move(__i);
            }
        }
        ++__first;
        return ::asc::std::pair<_Iter, _Iter>(::asc::std::move(__first), ::asc::std::move(__i));
    }
    return ::asc::std::pair<_Iter, _Iter>(__first, __first);
}
template <class _ForwardIterator, class _BinaryPredicate>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator unique(
    _ForwardIterator __first, _ForwardIterator __last, _BinaryPredicate __pred)
{
    return ::asc::std::__unique<_ClassicAlgPolicy>(
        ::asc::std::move(__first), ::asc::std::move(__last), __pred)  // NOLINT(build/include_what_you_use)
        .first;                                                       // NOLINT(build/include_what_you_use)
}

template <class _ForwardIterator>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator unique(_ForwardIterator __first, _ForwardIterator __last)
{
    return ::asc::std::unique(__first, __last, __equal_to{});
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_UNIQUE_H
