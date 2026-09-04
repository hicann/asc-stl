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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_MAX_ELEMENT_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_MAX_ELEMENT_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/comp_ref_type.h>
#include <asc/std/__iterator/iterator_traits.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Compare, class _ForwardIterator>
CANN_ASC_STL_API constexpr _ForwardIterator __max_element(
    _ForwardIterator __first, _ForwardIterator __last, _Compare __comp)
{
    static_assert(__has_input_traversal<_ForwardIterator>, "::asc::std::max_element requires a ForwardIterator");
    if (__first != __last) {
        _ForwardIterator __i = __first;
        while (++__i != __last) {
            if (__comp(*__first, *__i)) {
                __first = __i;
            }
        }
    }
    return __first;
}

template <class _ForwardIterator, class _Compare>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator max_element(
    _ForwardIterator __first, _ForwardIterator __last, _Compare __comp)
{
    return ::asc::std::__max_element<__comp_ref_type<_Compare>>(__first, __last, __comp);
}

template <class _ForwardIterator>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator max_element(_ForwardIterator __first, _ForwardIterator __last)
{
    return ::asc::std::max_element(__first, __last, __less{});
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_MAX_ELEMENT_H
