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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_EQUAL_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_EQUAL_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__algorithm/comp.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _InputIterator1, class _InputIterator2, class _BinaryPredicate>
[[nodiscard]] CANN_ASC_STL_API constexpr bool equal(
    _InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _BinaryPredicate __pred)
{
    bool __result = true;
    for (; __first1 != __last1; ++__first1, (void)++__first2) {
        if (!__pred(*__first1, *__first2)) {
            __result = false;
            break;
        }
    }
    return __result;
}

template <class _InputIterator1, class _InputIterator2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool equal(
    _InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2)
{
    return ::asc::std::equal(__first1, __last1, __first2, __equal_to{});
}

template <class _BinaryPredicate, class _InputIterator1, class _InputIterator2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool __equal(_InputIterator1 __first1, _InputIterator1 __last1,
    _InputIterator2 __first2, _InputIterator2 __last2, _BinaryPredicate __pred, input_iterator_tag, input_iterator_tag)
{
    bool __result = true;
    for (; __first1 != __last1 && __first2 != __last2; ++__first1, (void)++__first2) {
        if (!__pred(*__first1, *__first2)) {
            __result = false;
            break;
        }
    }
    return __result && __first1 == __last1 && __first2 == __last2;
}

template <class _BinaryPredicate, class _RandomAccessIterator1, class _RandomAccessIterator2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool __equal(_RandomAccessIterator1 __first1, _RandomAccessIterator1 __last1,
    _RandomAccessIterator2 __first2, _RandomAccessIterator2 __last2, _BinaryPredicate __pred,
    random_access_iterator_tag, random_access_iterator_tag)
{
    if (__last1 - __first1 != __last2 - __first2) {
        return false;
    }
    return ::asc::std::equal<_RandomAccessIterator1, _RandomAccessIterator2, add_lvalue_reference_t<_BinaryPredicate>>(
        __first1, __last1, __first2, __pred);
}

template <class _InputIterator1, class _InputIterator2, class _BinaryPredicate>
[[nodiscard]] CANN_ASC_STL_API constexpr bool equal(_InputIterator1 __first1, _InputIterator1 __last1,
    _InputIterator2 __first2, _InputIterator2 __last2, _BinaryPredicate __pred)
{
    return ::asc::std::__equal<add_lvalue_reference_t<_BinaryPredicate>>(__first1, __last1, __first2, __last2, __pred,
        __iterator_traits_category_or_concept_t<_InputIterator1>(),
        __iterator_traits_category_or_concept_t<_InputIterator2>());
}

template <class _InputIterator1, class _InputIterator2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool equal(
    _InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _InputIterator2 __last2)
{
    return ::asc::std::__equal(__first1, __last1, __first2, __last2, __equal_to{},
        __iterator_traits_category_or_concept_t<_InputIterator1>(),
        __iterator_traits_category_or_concept_t<_InputIterator2>());
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_EQUAL_H
