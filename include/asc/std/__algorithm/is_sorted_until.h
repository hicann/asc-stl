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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_IS_SORTED_UNTIL_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_IS_SORTED_UNTIL_H

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
#include <asc/std/__iterator/iterator_traits.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _Compare, class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator __is_sorted_until(
    _ForwardIterator __first, _ForwardIterator __last, _Compare __comp)
{
    if (__first != __last) {
        _ForwardIterator __i = __first;
        while (++__i != __last) {
            if (__comp(*__i, *__first)) {
                __last = __i;
                break;
            }
            __first = __i;
        }
    }
    return __last;
}

template <class _ForwardIterator, class _Compare>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator is_sorted_until(
    _ForwardIterator __first, _ForwardIterator __last, _Compare __comp)
{
    return ::asc::std::__is_sorted_until<__comp_ref_type<_Compare>>(__first, __last, __comp);
}

template <class _ForwardIterator>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator is_sorted_until(
    _ForwardIterator __first, _ForwardIterator __last)
{
    return ::asc::std::is_sorted_until(__first, __last, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_IS_SORTED_UNTIL_H
