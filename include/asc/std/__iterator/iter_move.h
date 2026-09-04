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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_ITER_MOVE_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_ITER_MOVE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_DIAG_PUSH
CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_CLANG("-Wvoid-ptr-dereference")

// [iterator.cust.move]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__iter_move)

CANN_ASC_STL_API void iter_move();

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class _Tp>
concept __unqualified_iter_move =
    __class_or_enum<remove_cvref_t<_Tp>> && requires(_Tp&& __t) { iter_move(::asc::std::forward<_Tp>(__t)); };

template <class _Tp>
concept __move_deref = !__unqualified_iter_move<_Tp> && requires(_Tp&& __t) {
    *__t;
    requires is_lvalue_reference_v<decltype(*__t)>;
};

template <class _Tp>
concept __just_deref = !__unqualified_iter_move<_Tp> && !__move_deref<_Tp> && requires(_Tp&& __t) {
    *__t;
    requires(!is_lvalue_reference_v<decltype(*__t)>);
};

#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__unqualified_iter_move_,
    requires(_Tp&& __t)(
        requires(__class_or_enum<remove_cvref_t<_Tp>>), ((void)iter_move(::asc::std::forward<_Tp>(__t)))));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __unqualified_iter_move =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__unqualified_iter_move_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__move_deref_,
    requires(_Tp&& __t)(requires(!__unqualified_iter_move<_Tp>), requires(is_lvalue_reference_v<decltype(*__t)>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __move_deref = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__move_deref_, _Tp);

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__just_deref_,
    requires(_Tp&& __t)(requires(!__unqualified_iter_move<_Tp>), requires(!__move_deref<_Tp>),
        requires(!is_lvalue_reference_v<decltype(*__t)>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __just_deref = CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__just_deref_, _Tp);
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

// [iterator.cust.move]

struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Ip)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__unqualified_iter_move<_Ip>)
    [[nodiscard]] CANN_ASC_STL_API constexpr decltype(auto) operator()(_Ip&& __i) const
        noexcept(noexcept(iter_move(::asc::std::forward<_Ip>(__i))))
    {
        return iter_move(::asc::std::forward<_Ip>(__i));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Ip)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__move_deref<_Ip>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Ip&& __i) const noexcept(noexcept(
        ::asc::std::move(*::asc::std::forward<_Ip>(__i)))) -> decltype(::asc::std::move(*::asc::std::forward<_Ip>(__i)))
    {
        return ::asc::std::move(*::asc::std::forward<_Ip>(__i));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Ip)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__just_deref<_Ip>)
    [[nodiscard]] CANN_ASC_STL_API constexpr auto operator()(_Ip&& __i) const
        noexcept(noexcept(*::asc::std::forward<_Ip>(__i))) -> decltype(*::asc::std::forward<_Ip>(__i))
    {
        return *::asc::std::forward<_Ip>(__i);  // NOLINT(build/include_what_you_use)
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO
inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto iter_move = __iter_move::__fn{};

// We want to avoid using the CPO internally because of __tile__ access
using __iter_move_cpo = __iter_move::__fn;
}  // namespace __cpo
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <__dereferenceable _Tp>
    requires requires(_Tp& __t) {
        { ::asc::std::ranges::__iter_move_cpo{}(__t) } -> __can_reference;
    }
using iter_rvalue_reference_t = decltype(::asc::std::ranges::__iter_move_cpo{}(::asc::std::declval<_Tp&>()));

#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__can_iter_rvalue_reference_t_,
    requires(_Tp& __t)(requires(__dereferenceable<_Tp>),
        requires(__can_reference<decltype(::asc::std::ranges::__iter_move_cpo{}(__t))>)));

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __can_iter_rvalue_reference_t =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__can_iter_rvalue_reference_t_, _Tp);

template <class _Tp>
using __iter_rvalue_reference_t = decltype(::asc::std::ranges::__iter_move_cpo{}(::asc::std::declval<_Tp&>()));

template <class _Tp>
using iter_rvalue_reference_t = enable_if_t<__can_iter_rvalue_reference_t<_Tp>, __iter_rvalue_reference_t<_Tp>>;
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_DIAG_POP

#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_ITER_MOVE_H
