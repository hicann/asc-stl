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

#ifndef CANN_ASC_STL_STD_DETAIL_RANGES_REND_H
#define CANN_ASC_STL_STD_DETAIL_RANGES_REND_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/reverse_iterator.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/rbegin.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/auto_cast.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

// [range.access.rend]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__rend)
template <class _Tp>
void rend(_Tp&) = delete;
template <class _Tp>
void rend(const _Tp&) = delete;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Tp>
concept __member_rend = __can_borrow<_Tp> && __workaround_52970<_Tp> && requires(_Tp&& __t) {
    ::asc::std::ranges::__rbegin_cpo{}(__t);
    {
        __t.rend()
    } -> sentinel_for<decltype(::asc::std::ranges::__rbegin_cpo{}(__t))>;  // the return-type requirement is expanded at
                                                                           // the use site
};

template <class _Tp>
concept __unqualified_rend =
    !__member_rend<_Tp> && __can_borrow<_Tp> && __class_or_enum<remove_cvref_t<_Tp>> && requires(_Tp&& __t) {
        ::asc::std::ranges::__rbegin_cpo{}(__t);
        { rend(__t) } -> sentinel_for<decltype(::asc::std::ranges::__rbegin_cpo{}(__t))>;
    };

template <class _Tp>
concept __can_reverse = __can_borrow<_Tp> && !__member_rend<_Tp> && !__unqualified_rend<_Tp> && requires(_Tp&& __t) {
    { ::asc::std::ranges::__begin_cpo{}(__t) } -> same_as<decltype(::asc::std::ranges::__end_cpo{}(__t))>;
    { ::asc::std::ranges::__begin_cpo{}(__t) } -> bidirectional_iterator;
};

#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !concepts vvv

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__member_rend_,
    requires(_Tp&& __t)(requires(__can_borrow<_Tp>), requires(__workaround_52970<_Tp>),
        typename(decltype(::asc::std::ranges::__rbegin_cpo{}(__t))),
        requires(sentinel_for<decltype(__t.rend()), decltype(::asc::std::ranges::__rbegin_cpo{}(__t))>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __member_rend = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__member_rend_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__unqualified_rend_,
    requires(_Tp&& __t)(requires(!__member_rend<_Tp>), requires(__can_borrow<_Tp>),
        requires(__class_or_enum<remove_cvref_t<_Tp>>), typename(decltype(::asc::std::ranges::__rbegin_cpo{}(__t))),
        requires(sentinel_for<decltype(rend(__t)), decltype(::asc::std::ranges::__rbegin_cpo{}(__t))>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __unqualified_rend = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__unqualified_rend_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__can_reverse_,
    requires(_Tp&& __t)(requires(!__member_rend<_Tp>), requires(!__unqualified_rend<_Tp>), requires(__can_borrow<_Tp>),
        requires(
            same_as<decltype(::asc::std::ranges::__begin_cpo{}(__t)), decltype(::asc::std::ranges::__end_cpo{}(__t))>),
        requires(bidirectional_iterator<decltype(::asc::std::ranges::__begin_cpo{}(__t))>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __can_reverse = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__can_reverse_, _Tp);
#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

class __fn {
public:
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__member_rend<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const noexcept(noexcept(__t.rend()))
    {
        return __t.rend();
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__unqualified_rend<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const noexcept(noexcept(rend(__t)))
    {
        return rend(__t);
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__can_reverse<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(::asc::std::ranges::__begin_cpo{}(__t)))
    {
        return ::asc::std::make_reverse_iterator(::asc::std::ranges::__begin_cpo{}(__t));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES((!__member_rend<_Tp> && !__unqualified_rend<_Tp> && !__can_reverse<_Tp>))
    void operator()(_Tp&&) const = delete;
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto rend = __rend::__fn{};

// We want to avoid using the CPO internally because of __tile__ access
using __rend_cpo = __rend::__fn;
}  // namespace __cpo

// [range.access.crend]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__crend)
struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_lvalue_reference_v<_Tp&&>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(::asc::std::ranges::__rend_cpo{}(static_cast<const remove_reference_t<_Tp>&>(
            __t)))) -> decltype(::asc::std::ranges::__rend_cpo{}(static_cast<const remove_reference_t<_Tp>&>(__t)))
    {
        return ::asc::std::ranges::__rend_cpo{}(static_cast<const remove_reference_t<_Tp>&>(__t));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_rvalue_reference_v<_Tp&&>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(::asc::std::ranges::__rend_cpo{}(static_cast<const _Tp&&>(
            __t)))) -> decltype(::asc::std::ranges::__rend_cpo{}(static_cast<const _Tp&&>(__t)))
    {
        return ::asc::std::ranges::__rend_cpo{}(static_cast<const _Tp&&>(__t));
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto crend = __crend::__fn{};

// We want to avoid using the CPO internally because of __tile__ access
using __crend_cpo = __crend::__fn;
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_RANGES_REND_H
