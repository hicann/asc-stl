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

#ifndef CANN_ASC_STL_STD_DETAIL_RANGES_DATA_H
#define CANN_ASC_STL_STD_DETAIL_RANGES_DATA_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/reverse_iterator.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_pointer.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/auto_cast.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

// [range.prim.data]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__data)

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __ptr_to_object = is_pointer_v<_Tp> && is_object_v<remove_pointer_t<_Tp>>;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Tp>
concept __member_data = __can_borrow<_Tp> && __workaround_52970<_Tp> && requires(_Tp&& __t) {
    {
        __t.data()
    } -> __ptr_to_object;  // the return-type requirement is expanded at the use site (data() returns the pointer by
                           // value)
};

template <class _Tp>
concept __ranges_begin_invocable = !__member_data<_Tp> && __can_borrow<_Tp> && requires(_Tp&& __t) {
    { ::asc::std::ranges::__begin_cpo{}(__t) } -> contiguous_iterator;
};

#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !concepts vvv

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__member_data_,
    requires(_Tp&& __t)(requires(__can_borrow<_Tp>), requires(__workaround_52970<_Tp>),
        requires(__ptr_to_object<decltype(__t.data())>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __member_data = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__member_data_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__ranges_begin_invocable_,
    requires(_Tp&& __t)(requires(!__member_data<_Tp>), requires(__can_borrow<_Tp>),
        requires(contiguous_iterator<decltype(::asc::std::ranges::__begin_cpo{}(__t))>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __ranges_begin_invocable =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__ranges_begin_invocable_, _Tp);
#endif  // !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__member_data<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const noexcept(noexcept(__t.data()))
    {
        return __t.data();
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__ranges_begin_invocable<_Tp>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(::asc::std::to_address(::asc::std::ranges::__begin_cpo{}(__t))))
    {
        return ::asc::std::to_address(::asc::std::ranges::__begin_cpo{}(__t));
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto data = __data::__fn{};

// We want to avoid using the CPO internally because of __tile__ access
using __data_cpo = __data::__fn;
}  // namespace __cpo

// [range.prim.cdata]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__cdata)
struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_lvalue_reference_v<_Tp&&>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(::asc::std::ranges::__data_cpo{}(static_cast<const remove_reference_t<_Tp>&>(
            __t)))) -> decltype(::asc::std::ranges::__data_cpo{}(static_cast<const remove_reference_t<_Tp>&>(__t)))
    {
        return ::asc::std::ranges::__data_cpo{}(static_cast<const remove_reference_t<_Tp>&>(__t));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_rvalue_reference_v<_Tp&&>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const
        noexcept(noexcept(::asc::std::ranges::__data_cpo{}(static_cast<const _Tp&&>(
            __t)))) -> decltype(::asc::std::ranges::__data_cpo{}(static_cast<const _Tp&&>(__t)))
    {
        return ::asc::std::ranges::__data_cpo{}(static_cast<const _Tp&&>(__t));
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto cdata = __cdata::__fn{};

// We want to avoid using the CPO internally because of __tile__ access
using __cdata_cpo = __cdata::__fn;
}  // namespace __cpo

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_RANGES_DATA_H
