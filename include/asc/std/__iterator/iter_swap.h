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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_ITER_SWAP_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_ITER_SWAP_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__concepts/swappable.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iter_move.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__type_traits/add_lvalue_reference.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
// [iter.cust.swap]
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__iter_swap)
template <class _I1, class _I2>
void iter_swap(_I1, _I2) = delete;

template <class _T1, class _T2>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __unqualified_iter_swap = CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_T1, _T2), _T1&& __x,
    _T2&& __y)(requires(__class_or_enum<remove_cvref_t<_T1>> || __class_or_enum<remove_cvref_t<_T2>>),
    ((void)iter_swap(::asc::std::forward<_T1>(__x), ::asc::std::forward<_T2>(__y))));

#if CANN_ASC_STL_DETAIL_ACCL_HAS_NOEXCEPT_MANGLING()  // older GCC cannot use noexcept inside a requires clause
template <class _T1, class _T2>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __noexcept_unqualified_iter_swap = CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR(
    (_T1, _T2), _T1&& __x, _T2&& __y)(requires(__unqualified_iter_swap<_T1, _T2>),
    noexcept(iter_swap(::asc::std::forward<_T1>(__x), ::asc::std::forward<_T2>(__y))));
#else   // ^^^ CANN_ASC_STL_DETAIL_ACCL_HAS_NOEXCEPT_MANGLING() ^^^ / vvv
        // !CANN_ASC_STL_DETAIL_ACCL_HAS_NOEXCEPT_MANGLING() vvv
template <class _T1, class _T2, bool = __unqualified_iter_swap<_T1, _T2>>
inline constexpr bool __noexcept_unqualified_iter_swap = false;

template <class _T1, class _T2>
inline constexpr bool __noexcept_unqualified_iter_swap<_T1, _T2, true> =
    noexcept(iter_swap(::asc::std::declval<_T1>(), ::asc::std::declval<_T2>()));
#endif  // !CANN_ASC_STL_DETAIL_ACCL_HAS_NOEXCEPT_MANGLING()

template <class _T1, class _T2>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __readable_swappable =
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_T1, _T2))(requires(!__unqualified_iter_swap<_T1, _T2>),
        requires(indirectly_readable<_T1>), requires(indirectly_readable<_T2>),
        requires(__can_reference<iter_reference_t<_T1>>), requires(__can_reference<iter_reference_t<_T2>>),
        requires(swappable_with<iter_reference_t<_T1>, iter_reference_t<_T2>>));

#if CANN_ASC_STL_DETAIL_ACCL_HAS_NOEXCEPT_MANGLING()  // older GCC cannot use noexcept inside a requires clause
template <class _T1, class _T2>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __noexcept_readable_swappable =
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_T1, _T2), _T1&& __x, _T2&& __y)  //
    (requires(__readable_swappable<_T1, _T2>),
        noexcept(::asc::std::ranges::__swap_cpo{}(*::asc::std::forward<_T1>(__x), *::asc::std::forward<_T2>(__y))));
#else   // ^^^ CANN_ASC_STL_DETAIL_ACCL_HAS_NOEXCEPT_MANGLING() ^^^ / vvv
        // !CANN_ASC_STL_DETAIL_ACCL_HAS_NOEXCEPT_MANGLING() vvv
template <class _T1, class _T2, bool = __readable_swappable<_T1, _T2>>
inline constexpr bool __noexcept_readable_swappable = false;

template <class _T1, class _T2>
inline constexpr bool __noexcept_readable_swappable<_T1, _T2, true> =
    noexcept(::asc::std::ranges::__swap_cpo{}(*::asc::std::declval<_T1>(), *::asc::std::declval<_T2>()));
#endif  // !CANN_ASC_STL_DETAIL_ACCL_HAS_NOEXCEPT_MANGLING()

template <class _T1, class _T2>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __movable_storable = CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_T1, _T2))(
    requires(!__unqualified_iter_swap<_T1, _T2>), requires(!__readable_swappable<_T1, _T2>),
    requires(indirectly_movable_storable<_T1, _T2>), requires(indirectly_movable_storable<_T2, _T1>));

#if CANN_ASC_STL_DETAIL_ACCL_HAS_NOEXCEPT_MANGLING()  // older GCC cannot use noexcept inside a requires clause
template <class _T1, class _T2>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __noexcept_movable_storable =
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES_EXPR((_T1, _T2), _T1&& __x, _T2&& __y, iter_value_t<_T2> __old)(
        requires(__movable_storable<_T1, _T2>), noexcept(iter_value_t<_T2>(::asc::std::ranges::__iter_move_cpo{}(__y))),
        noexcept(*__y = ::asc::std::ranges::__iter_move_cpo{}(__x)),
        noexcept(*::asc::std::forward<_T1>(__x) = ::asc::std::move(__old)));
#else   // ^^^ CANN_ASC_STL_DETAIL_ACCL_HAS_NOEXCEPT_MANGLING() ^^^ / vvv
        // !CANN_ASC_STL_DETAIL_ACCL_HAS_NOEXCEPT_MANGLING() vvv
template <class _T1, class _T2, bool = __movable_storable<_T1, _T2>>
inline constexpr bool __noexcept_movable_storable = false;

template <class _T1, class _T2>
inline constexpr bool __noexcept_movable_storable<_T1, _T2, true> =
    noexcept(
        iter_value_t<_T2>(::asc::std::ranges::__iter_move_cpo{}(::asc::std::declval<add_lvalue_reference_t<_T2>>()))) &&
    noexcept(*::asc::std::declval<add_lvalue_reference_t<_T2>>() =
                 ::asc::std::ranges::__iter_move_cpo{}(::asc::std::declval<add_lvalue_reference_t<_T1>>())) &&
    noexcept(*::asc::std::declval<_T1>() = ::asc::std::declval<iter_value_t<_T2>>());
#endif  // !CANN_ASC_STL_DETAIL_ACCL_HAS_NOEXCEPT_MANGLING()

struct __fn {
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _T1, class _T2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__unqualified_iter_swap<_T1, _T2>)
    CANN_ASC_STL_API constexpr void operator()(_T1&& __x, _T2&& __y) const
        noexcept(__noexcept_unqualified_iter_swap<_T1, _T2>)
    {
        (void)iter_swap(::asc::std::forward<_T1>(__x), ::asc::std::forward<_T2>(__y));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _T1, class _T2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__readable_swappable<_T1, _T2>)
    CANN_ASC_STL_API constexpr void operator()(_T1&& __x, _T2&& __y) const
        noexcept(__noexcept_readable_swappable<_T1, _T2>)
    {
        ::asc::std::ranges::__swap_cpo{}(*::asc::std::forward<_T1>(__x), *::asc::std::forward<_T2>(__y));
    }

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _T1, class _T2)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__movable_storable<_T2, _T1>)
    CANN_ASC_STL_API constexpr void operator()(_T1&& __x, _T2&& __y) const
        noexcept(__noexcept_movable_storable<_T1, _T2>)
    {
        iter_value_t<_T2> __old(::asc::std::ranges::__iter_move_cpo{}(__y));
        *__y = ::asc::std::ranges::__iter_move_cpo{}(__x);
        *::asc::std::forward<_T1>(__x) = ::asc::std::move(__old);  // NOLINT(build/include_what_you_use)
    }
};
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto iter_swap = __iter_swap::__fn{};

// Avoid using the public CPO internally so lookup stays constrained to this implementation.
using __iter_swap_cpo = __iter_swap::__fn;
}  // namespace __cpo
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class _I1, class _I2 = _I1>
concept indirectly_swappable =
    indirectly_readable<_I1> && indirectly_readable<_I2> && requires(const _I1 __i1, const _I2 __i2) {
        ::asc::std::ranges::__iter_swap_cpo{}(__i1, __i1);
        ::asc::std::ranges::__iter_swap_cpo{}(__i2, __i2);
        ::asc::std::ranges::__iter_swap_cpo{}(__i1, __i2);
        ::asc::std::ranges::__iter_swap_cpo{}(__i2, __i1);
    };
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv
template <class _I1, class _I2>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT_FRAGMENT(__indirectly_swappable_,
    requires(const _I1 __i1, const _I2 __i2)(requires(indirectly_readable<_I1>), requires(indirectly_readable<_I2>),
        (::asc::std::ranges::__iter_swap_cpo{}(__i1, __i1)), (::asc::std::ranges::__iter_swap_cpo{}(__i2, __i2)),
        (::asc::std::ranges::__iter_swap_cpo{}(__i1, __i2)), (::asc::std::ranges::__iter_swap_cpo{}(__i2, __i1))));

template <class _I1, class _I2 = _I1>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT indirectly_swappable =
    CANN_ASC_STL_DETAIL_ACCL_FRAGMENT(__indirectly_swappable_, _I1, _I2);
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

template <class _I1, class _I2 = _I1, class = void>
inline constexpr bool __noexcept_swappable = false;

template <class _I1, class _I2>
inline constexpr bool __noexcept_swappable<_I1, _I2, enable_if_t<indirectly_swappable<_I1, _I2>>> =
    noexcept(::asc::std::ranges::__iter_swap_cpo{}(::asc::std::declval<_I1&>(), ::asc::std::declval<_I2&>()));

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD
#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_ITER_SWAP_H
