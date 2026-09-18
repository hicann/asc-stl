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

#ifndef CANN_ASC_STL_STD_DETAIL_RANGES_RBEGIN_H
#define CANN_ASC_STL_STD_DETAIL_RANGES_RBEGIN_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/reverse_iterator.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/auto_cast.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

// [ranges.access.rbegin]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__rbegin)
template <class _Tp>
void rbegin(_Tp&) = delete;
template <class _Tp>
void rbegin(const _Tp&) = delete;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Tp>
concept __member_rbegin = __can_borrow<_Tp> && __workaround_52970<_Tp> && requires(_Tp&& __t) {
    {
        __t.rbegin()
    } -> input_or_output_iterator;  // the return-type requirement is expanded at the use site (returns the iterator by
                                    // value)
};

template <class _Tp>
concept __unqualified_rbegin =
    !__member_rbegin<_Tp> && __can_borrow<_Tp> && __class_or_enum<remove_cvref_t<_Tp>> && requires(_Tp&& __t) {
        { rbegin(__t) } -> input_or_output_iterator;
    };

template <class _Tp>
concept __can_reverse =
    __can_borrow<_Tp> && !__member_rbegin<_Tp> && !__unqualified_rbegin<_Tp> && requires(_Tp&& __t) {
        { ::asc::std::ranges::__begin_cpo{}(__t) } -> same_as<decltype(::asc::std::ranges::__end_cpo{}(__t))>;
        { ::asc::std::ranges::__begin_cpo{}(__t) } -> bidirectional_iterator;
    };

#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !concepts vvv

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__member_rbegin_,
    requires(_Tp&& __t)(requires(__can_borrow<_Tp>), requires(__workaround_52970<_Tp>),
        requires(input_or_output_iterator<decltype(__t.rbegin())>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __member_rbegin = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__member_rbegin_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__unqualified_rbegin_,
    requires(_Tp&& __t)(requires(!__member_rbegin<_Tp>), requires(__can_borrow<_Tp>),
        requires(__class_or_enum<remove_cvref_t<_Tp>>), requires(input_or_output_iterator<decltype(rbegin(__t))>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __unqualified_rbegin = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__unqualified_rbegin_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__can_reverse_,
    requires(_Tp&& __t)(requires(__can_borrow<_Tp>), requires(!__member_rbegin<_Tp>),
        requires(!__unqualified_rbegin<_Tp>),
        requires(
            same_as<decltype(::asc::std::ranges::__end_cpo{}(__t)), decltype(::asc::std::ranges::__begin_cpo{}(__t))>),
        requires(bidirectional_iterator<decltype(::asc::std::ranges::__begin_cpo{}(__t))>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __can_reverse = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__can_reverse_, _Tp);
#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__member_rbegin<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const noexcept(noexcept(__t.rbegin()))
    {
        return __t.rbegin();
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__unqualified_rbegin<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const noexcept(noexcept(rbegin(__t)))
    {
        return rbegin(__t);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_reverse<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(::asc::std::ranges::__end_cpo{}(__t)))
    {
        return ::asc::std::make_reverse_iterator(::asc::std::ranges::__end_cpo{}(__t));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!__member_rbegin<_Tp> && !__unqualified_rbegin<_Tp> && !__can_reverse<_Tp>))
    void operator()(_Tp&&) const = delete;
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto rbegin = __rbegin::__fn{};

// We want to avoid using the CPO internally because of __tile__ access
using __rbegin_cpo = __rbegin::__fn;
}  // namespace __cpo

// [range.access.crbegin]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__crbegin)
struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_lvalue_reference_v<_Tp&&>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(::asc::std::ranges::__rbegin_cpo{}(static_cast<const remove_reference_t<_Tp>&>(
            __t)))) -> decltype(::asc::std::ranges::__rbegin_cpo{}(static_cast<const remove_reference_t<_Tp>&>(__t)))
    {
        return ::asc::std::ranges::__rbegin_cpo{}(static_cast<const remove_reference_t<_Tp>&>(__t));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_rvalue_reference_v<_Tp&&>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(::asc::std::ranges::__rbegin_cpo{}(static_cast<const _Tp&&>(
            __t)))) -> decltype(::asc::std::ranges::__rbegin_cpo{}(static_cast<const _Tp&&>(__t)))
    {
        return ::asc::std::ranges::__rbegin_cpo{}(static_cast<const _Tp&&>(__t));
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto crbegin = __crbegin::__fn{};

// We want to avoid using the CPO internally because of __tile__ access
using __crbegin_cpo = __crbegin::__fn;
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_RANGES_RBEGIN_H
