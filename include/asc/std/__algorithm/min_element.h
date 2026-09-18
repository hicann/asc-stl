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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_MIN_ELEMENT_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_MIN_ELEMENT_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/comp_ref_type.h>
#include <asc/std/__functional/identity.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/is_callable.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Comp, class _Iter, class _Sent, class _Proj>
CANN_ASC_STL_API constexpr _Iter __min_element(_Iter __first, _Sent __last, _Comp __comp, _Proj& __proj)
{
    if (__first == __last) {
        return __first;
    }

    _Iter __i = __first;
    while (++__i != __last) {
        if (::asc::std::invoke(__comp, ::asc::std::invoke(__proj, *__i), ::asc::std::invoke(__proj, *__first))) {
            __first = __i;
        }
    }

    return __first;
}

template <class _Comp, class _Iter, class _Sent>
CANN_ASC_STL_API constexpr _Iter __min_element(_Iter __first, _Sent __last, _Comp __comp)
{
    auto __proj = identity();
    return ::asc::std::__min_element<_Comp>(::asc::std::move(__first), ::asc::std::move(__last), __comp, __proj);
}

template <class _ForwardIterator, class _Compare>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator min_element(
    _ForwardIterator __first, _ForwardIterator __last, _Compare __comp)
{
    static_assert(__has_input_traversal<_ForwardIterator>, "std::min_element requires a ForwardIterator");
    static_assert(
        __is_callable<_Compare, decltype(*__first), decltype(*__first)>::value, "The comparator has to be callable");

    return ::asc::std::__min_element<__comp_ref_type<_Compare>>(
        ::asc::std::move(__first), ::asc::std::move(__last), __comp);  // NOLINT(build/include_what_you_use)
}

template <class _ForwardIterator>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator min_element(_ForwardIterator __first, _ForwardIterator __last)
{
    return ::asc::std::min_element(__first, __last, __less{});  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_MIN_ELEMENT_H
