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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_NEXT_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_NEXT_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__iterator/advance.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/enable_if.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _InputIter)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__has_input_traversal<_InputIter>)
[[nodiscard]] CANN_ASC_STL_API constexpr _InputIter next(
    _InputIter __x, typename iterator_traits<_InputIter>::difference_type __n = 1)
{
    CANN_ASC_STL_DETAIL_ASSERT(__n >= 0 || __has_bidirectional_traversal<_InputIter>,
        "Attempt to next(it, n) with negative n on a non-bidirectional iterator");

    ::asc::std::advance(__x, __n);
    return __x;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

// [range.iter.op.next]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__next)
struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Ip)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(input_or_output_iterator<_Ip>)
    [[nodiscard]] CANN_ASC_STL_API constexpr _Ip operator()(_Ip __x) const
    {
        ++__x;
        return __x;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Ip)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(input_or_output_iterator<_Ip>)
    [[nodiscard]] CANN_ASC_STL_API constexpr _Ip operator()(_Ip __x, iter_difference_t<_Ip> __n) const
    {
        ::asc::std::ranges::__advance_cpo{}(__x, __n);
        return __x;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Ip, class _Sp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(input_or_output_iterator<_Ip>&& sentinel_for<_Sp, _Ip>)
    [[nodiscard]] CANN_ASC_STL_API constexpr _Ip operator()(_Ip __x, _Sp __bound_sentinel) const
    {
        ::asc::std::ranges::__advance_cpo{}(__x, __bound_sentinel);
        return __x;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Ip, class _Sp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(input_or_output_iterator<_Ip>&& sentinel_for<_Sp, _Ip>)
    [[nodiscard]] CANN_ASC_STL_API constexpr _Ip operator()(
        _Ip __x, iter_difference_t<_Ip> __n, _Sp __bound_sentinel) const
    {
        ::asc::std::ranges::__advance_cpo{}(__x, __n, __bound_sentinel);
        return __x;
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto next = __next::__fn{};

// We want to avoid using the CPO internally because of __tile__ access
using __next_cpo = __next::__fn;
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_NEXT_H
