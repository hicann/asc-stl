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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_REMOVE_IF_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_REMOVE_IF_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/find_if.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _ForwardIterator, class _Predicate>
[[nodiscard]] CANN_ASC_STL_API constexpr _ForwardIterator remove_if(
    _ForwardIterator __first, _ForwardIterator __last, _Predicate __pred)
{
    __first = ::asc::std::find_if<_ForwardIterator, add_lvalue_reference_t<_Predicate>>(__first, __last, __pred);
    if (__first != __last) {
        _ForwardIterator __i = __first;
        while (++__i != __last) {
            if (!__pred(*__i)) {
                *__first = ::asc::std::move(*__i);  // NOLINT(build/include_what_you_use)
                ++__first;
            }
        }
    }
    return __first;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_REMOVE_IF_H
