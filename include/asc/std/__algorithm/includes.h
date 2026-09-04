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

#ifndef CANN_ASC_STL_STD_DETAIL_ALGORITHM_INCLUDES_H
#define CANN_ASC_STL_STD_DETAIL_ALGORITHM_INCLUDES_H

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

template <class _Iter1, class _Sent1, class _Iter2, class _Sent2, class _Comp, class _Proj1, class _Proj2>
CANN_ASC_STL_API constexpr bool __includes(_Iter1 __first1, _Sent1 __last1, _Iter2 __first2, _Sent2 __last2,
    _Comp&& __comp, _Proj1&& __proj1, _Proj2&& __proj2)
{
    bool __result = true;
    for (; __first2 != __last2; ++__first1) {
        if (__first1 == __last1 ||
            ::asc::std::invoke(
                __comp, ::asc::std::invoke(__proj2, *__first2), ::asc::std::invoke(__proj1, *__first1))) {
            __result = false;
            break;
        }
        if (!::asc::std::invoke(
                __comp, ::asc::std::invoke(__proj1, *__first1), ::asc::std::invoke(__proj2, *__first2))) {
            ++__first2;
        }
    }
    return __result;
}

template <class _InputIterator1, class _InputIterator2, class _Compare>
[[nodiscard]] CANN_ASC_STL_API constexpr bool includes(_InputIterator1 __first1, _InputIterator1 __last1,
    _InputIterator2 __first2, _InputIterator2 __last2, _Compare __comp)
{
    static_assert(
        __is_callable<_Compare, decltype(*__first1), decltype(*__first2)>::value, "Comparator has to be callable");

    return ::asc::std::__includes(::asc::std::move(__first1), ::asc::std::move(__last1), ::asc::std::move(__first2),
        ::asc::std::move(__last2), static_cast<__comp_ref_type<_Compare>>(__comp), identity(), identity());
}

template <class _InputIterator1, class _InputIterator2>
[[nodiscard]] CANN_ASC_STL_API constexpr bool includes(
    _InputIterator1 __first1, _InputIterator1 __last1, _InputIterator2 __first2, _InputIterator2 __last2)
{
    return ::asc::std::includes(::asc::std::move(__first1), ::asc::std::move(__last1), ::asc::std::move(__first2),
        ::asc::std::move(__last2), __less{});  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_ALGORITHM_INCLUDES_H
