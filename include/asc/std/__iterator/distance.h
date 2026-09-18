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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_DISTANCE_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_DISTANCE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/concepts.h>
#include <asc/std/__ranges/size.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/remove_cvref.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _InputIter>
[[nodiscard]] CANN_ASC_STL_API constexpr typename iterator_traits<_InputIter>::difference_type distance(
    _InputIter __first, _InputIter __last)
{
    if constexpr (__has_random_access_traversal<_InputIter>) {  // To support pointers to incomplete types
        return __last - __first;
    } else if constexpr (sized_sentinel_for<_InputIter, _InputIter>) {
        return __last - __first;
    } else {
        typename iterator_traits<_InputIter>::difference_type __r(0);
        for (; __first != __last; ++__first) {
            ++__r;
        }
        return __r;
    }
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

// [range.iter.op.distance]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__distance)
struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Ip, class _Sp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((sentinel_for<_Sp, _Ip> && !sized_sentinel_for<_Sp, _Ip>))
    [[nodiscard]] CANN_ASC_STL_API constexpr iter_difference_t<_Ip> operator()(_Ip __first, _Sp __last) const
    {
        iter_difference_t<_Ip> __n = 0;
        while (__first != __last) {
            ++__first;
            ++__n;
        }
        return __n;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Ip, class _Sp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((sized_sentinel_for<_Sp, decay_t<_Ip>>))
    [[nodiscard]] CANN_ASC_STL_API constexpr iter_difference_t<_Ip> operator()(_Ip&& __first, _Sp __last) const
    {
        if constexpr (sized_sentinel_for<_Sp, remove_cvref_t<_Ip>>) {
            return __last - __first;
        } else {
            return __last - decay_t<_Ip>(__first);
        }
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Rp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((range<_Rp>))
    [[nodiscard]] CANN_ASC_STL_API constexpr range_difference_t<_Rp> operator()(_Rp&& __r) const
    {
        if constexpr (sized_range<_Rp>) {
            return static_cast<range_difference_t<_Rp>>(::asc::std::ranges::__size_cpo{}(__r));
        } else {
            return operator()(::asc::std::ranges::__begin_cpo{}(__r), ::asc::std::ranges::__end_cpo{}(__r));
        }
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto distance = __distance::__fn{};

// We want to avoid using the CPO internally because of __tile__ access
using __distance_cpo = __distance::__fn;
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_DISTANCE_H
