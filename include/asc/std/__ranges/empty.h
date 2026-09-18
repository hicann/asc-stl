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

#ifndef CANN_ASC_STL_STD_DETAIL_RANGES_EMPTY_H
#define CANN_ASC_STL_STD_DETAIL_RANGES_EMPTY_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/size.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

// [range.prim.empty]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__empty)

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Tp>
concept __member_empty = __workaround_52970<_Tp> && requires(_Tp&& __t) { static_cast<bool>(__t.empty()); };

template <class _Tp>
concept __can_invoke_size = !__member_empty<_Tp> && requires(_Tp&& __t) { ::asc::std::ranges::__size_cpo{}(__t); };

template <class _Tp>
concept __can_compare_begin_end = !__member_empty<_Tp> && !__can_invoke_size<_Tp> && requires(_Tp&& __t) {
    static_cast<bool>(::asc::std::ranges::__begin_cpo{}(__t) == ::asc::std::ranges::__end_cpo{}(__t));
    { ::asc::std::ranges::__begin_cpo{}(__t) } -> forward_iterator;
};

#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(
    __member_empty_, requires(_Tp&& __t)(requires(__workaround_52970<_Tp>), (static_cast<bool>(__t.empty()))));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __member_empty = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__member_empty_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__can_invoke_size_,
    requires(_Tp&& __t)(requires(!__member_empty<_Tp>), ((void)::asc::std::ranges::__size_cpo{}(__t))));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __can_invoke_size = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__can_invoke_size_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__can_compare_begin_end_,
    requires(_Tp&& __t)(requires(!__member_empty<_Tp>), requires(!__can_invoke_size<_Tp>),
        (static_cast<bool>(::asc::std::ranges::__begin_cpo{}(__t) == ::asc::std::ranges::__end_cpo{}(__t))),
        requires(forward_iterator<decltype(::asc::std::ranges::__begin_cpo{}(__t))>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __can_compare_begin_end =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__can_compare_begin_end_, _Tp);
#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__member_empty<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(_Tp&& __t) const
        noexcept(noexcept(static_cast<bool>(__t.empty())))
    {
        return static_cast<bool>(__t.empty());
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_invoke_size<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(_Tp&& __t) const
        noexcept(noexcept(::asc::std::ranges::__size_cpo{}(__t)))
    {
        return ::asc::std::ranges::__size_cpo{}(__t) == 0;
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_compare_begin_end<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr bool operator()(_Tp&& __t) const noexcept(
        noexcept(static_cast<bool>(::asc::std::ranges::__begin_cpo{}(__t) == ::asc::std::ranges::__end_cpo{}(__t))))
    {
        return ::asc::std::ranges::__begin_cpo{}(__t) == ::asc::std::ranges::__end_cpo{}(__t);
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto empty = __empty::__fn{};

// We want to avoid using the CPO internally because of __tile__ access
using __empty_cpo = __empty::__fn;
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_RANGES_EMPTY_H
