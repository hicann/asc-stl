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

#ifndef CANN_ASC_STL_ASC_STD___ALGORITHM_MERGE_H
#define CANN_ASC_STL_ASC_STD___ALGORITHM_MERGE_H

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
#include <asc/std/__algorithm/copy.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// Internal merge: the comparator is passed by reference via __comp_ref_type
// (a strict-weak-ordering assertion wrapper in debug mode); once one side is
// exhausted, the tail is finished via ::asc::std::copy, inheriting copy's fast
// paths.
template <class _Compare, class _InputIterator1, class _InputIterator2, class _OutputIterator>
CANN_ASC_STL_API constexpr _OutputIterator __merge(_InputIterator1 __first1, _InputIterator1 __last1,
    _InputIterator2 __first2, _InputIterator2 __last2, _OutputIterator __result, _Compare __comp)
{
    bool __second_remains = true;
    for (; __first1 != __last1; ++__result) {
        if (__first2 == __last2) {
            __second_remains = false;
            break;
        }
        if (__comp(*__first2, *__first1)) {
            *__result = *__first2;
            ++__first2;
        } else {
            *__result = *__first1;
            ++__first1;
        }
    }
    if (__second_remains) {
        return ::asc::std::copy(__first2, __last2, __result);  // NOLINT(build/include_what_you_use)
    }
    return ::asc::std::copy(__first1, __last1, __result);  // NOLINT(build/include_what_you_use)
}

template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
CANN_ASC_STL_API constexpr OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2,
    InputIterator2 last2, OutputIterator result, Compare compare)
{
    return ::asc::std::__merge<__comp_ref_type<Compare>>(first1, last1, first2, last2, result, compare);
}

template <class InputIterator1, class InputIterator2, class OutputIterator>
CANN_ASC_STL_API constexpr OutputIterator merge(
    InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
{
    return ::asc::std::merge(first1, last1, first2, last2, result, __less{});
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ALGORITHM_MERGE_H
