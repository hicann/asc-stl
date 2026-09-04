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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_LEXICOGRAPHICAL_COMPARE_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_LEXICOGRAPHICAL_COMPARE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/comp.h>
#include <asc/std/__algorithm/comp_ref_type.h>
#include <asc/std/__iterator/iterator_traits.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Compare, class _InputIterator1, class _InputIterator2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool __lexicographical_compare(_InputIterator1 __first1,
    _InputIterator1 __last1, _InputIterator2 __first2, _InputIterator2 __last2, _Compare __comp)
{
    bool __result = false;
    for (; __first2 != __last2; ++__first1, (void)++__first2) {
        if (__first1 == __last1 || __comp(*__first1, *__first2)) {
            __result = true;
            break;
        }
        if (__comp(*__first2, *__first1)) {
            break;
        }
    }
    return __result;
}

template <class _InputIterator1, class _InputIterator2, class _Compare>
[[nodiscard]] CANN_ASC_STL_API constexpr bool lexicographical_compare(_InputIterator1 __first1, _InputIterator1 __last1,
    _InputIterator2 __first2, _InputIterator2 __last2, _Compare __comp)
{
    return __lexicographical_compare<__comp_ref_type<_Compare>>(__first1, __last1, __first2, __last2, __comp);
}

template <class _InputIterator1, class _InputIterator2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool lexicographical_compare(
    _InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _InputIterator2 __last2)
{
    return ::asc::std::lexicographical_compare(__first1, __last1, __first2, __last2, __less{});
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_LEXICOGRAPHICAL_COMPARE_H
