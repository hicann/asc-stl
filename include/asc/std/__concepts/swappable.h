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

#ifndef CANN_ASC_STL_ASC_STD___CONCEPTS_SWAPPABLE_H
#define CANN_ASC_STL_ASC_STD___CONCEPTS_SWAPPABLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/__detail/execution_space.h>
#include <asc/std/__concepts/assignable.h>
#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__concepts/common_reference_with.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/extent.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_assignable.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/type_identity.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/exchange.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

// [concept.swappable]

namespace __swap_detail {

template <class T>
void swap(T&, T&) = delete;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

template <class T, class U>
concept __unqualified_swappable_with = (__class_or_enum<remove_cvref_t<T>> || __class_or_enum<remove_cvref_t<U>>) &&
    requires(T&& t, U&& u) { swap(::asc::std::forward<T>(t), ::asc::std::forward<U>(u)); };

template <class T>
concept __exchangeable = !__unqualified_swappable_with<T&, T&> && move_constructible<T> && assignable_from<T&, T>;

struct __fn;

template <class T, class U, size_t N>
concept __swappable_arrays = !__unqualified_swappable_with<T (&)[N], U (&)[N]> && extent_v<T> == extent_v<U> &&
    requires(T (&t)[N], U (&u)[N], const __fn& action) { action(t[0], u[0]); };

#else  // ^^^ concepts ^^^ / vvv !concepts vvv

// Non-concept path (also used for device compilation): void_t detection
// unfolded into bool variable templates, matching the concept version's semantics.
template <class T, class U, class = void>
inline constexpr bool __unqualified_swappable_with_impl = false;

template <class T, class U>
inline constexpr bool __unqualified_swappable_with_impl<T, U,
    void_t<decltype(swap(::asc::std::declval<T>(), ::asc::std::declval<U>()))>> =
    __class_or_enum<remove_cvref_t<T>> || __class_or_enum<remove_cvref_t<U>>;

template <class T, class U>
inline constexpr bool __unqualified_swappable_with = __unqualified_swappable_with_impl<T, U>;

template <class T>
inline constexpr bool __exchangeable =
    !__unqualified_swappable_with<T&, T&> && move_constructible<T> && assignable_from<T&, T>;

template <class T, class U, size_t N, class = void>
inline constexpr bool __swappable_arrays = false;

#endif  // !concepts

template <class T, class U, class = void>
inline constexpr bool __noexcept_swappable_arrays = false;

struct __fn {
    // (2.1) `S` is `(void)swap(E1, E2)`: E1/E2 have class or enumeration type and
    // (unqualified) swap(E1, E2) is valid (the name `swap` is found by unqualified lookup).
#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    template <class T, class U>
        requires __unqualified_swappable_with<T, U>
    CANN_ASC_STL_API constexpr void operator()(T&& t, U&& u) const
        noexcept(noexcept(swap(::asc::std::forward<T>(t), ::asc::std::forward<U>(u))))
    {
        swap(::asc::std::forward<T>(t), ::asc::std::forward<U>(u));
    }

    // (2.2) Otherwise, if E1/E2 are array lvalues of equal extent, dispatch element-wise recursively.
    template <class T, class U, size_t N>
        requires __swappable_arrays<T, U, N>
    CANN_ASC_STL_API constexpr void operator()(T (&t)[N], U (&u)[N]) const noexcept(__noexcept_swappable_arrays<T, U>)
    {
        for (size_t index = 0; index < N; ++index) {
            (*this)(t[index], u[index]);
        }
    }

    // (2.3) Otherwise, if E1/E2 are lvalues of the same type T and T is move
    // constructible/move assignable, swap by moving through exchange.
    template <class T>
        requires __exchangeable<T>
    CANN_ASC_STL_API constexpr void operator()(T& x, T& y) const
        noexcept(is_nothrow_move_constructible_v<T> && is_nothrow_move_assignable_v<T>)
    {
        y = ::asc::std::exchange(x, ::asc::std::move(y));
    }
#else   // ^^^ concepts ^^^ / vvv !concepts vvv
    template <class T, class U, enable_if_t<__unqualified_swappable_with<T, U>, int> = 0>
    CANN_ASC_STL_API constexpr void operator()(T&& t, U&& u) const
        noexcept(noexcept(swap(::asc::std::forward<T>(t), ::asc::std::forward<U>(u))))
    {
        swap(::asc::std::forward<T>(t), ::asc::std::forward<U>(u));
    }

    template <class T, class U, size_t N, enable_if_t<__swappable_arrays<T, U, N>, int> = 0>
    CANN_ASC_STL_API constexpr void operator()(T (&t)[N], U (&u)[N]) const noexcept(__noexcept_swappable_arrays<T, U>)
    {
        for (size_t index = 0; index < N; ++index) {
            (*this)(t[index], u[index]);
        }
    }

    template <class T, enable_if_t<__exchangeable<T>, int> = 0>
    CANN_ASC_STL_API constexpr void operator()(T& x, T& y) const
        noexcept(is_nothrow_move_constructible_v<T> && is_nothrow_move_assignable_v<T>)
    {
        y = ::asc::std::exchange(x, ::asc::std::move(y));
    }
#endif  // !concepts
};

#if !(CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION())
// The swappable-arrays detection needs __fn to be complete (it requires the
// element call to be a valid expression), so it is defined after __fn.
template <class T, class U, size_t N>
inline constexpr bool __swappable_arrays<T, U, N,
    void_t<decltype(::asc::std::declval<const __fn&>()(
        ::asc::std::declval<T (&)[N]>()[0], ::asc::std::declval<U (&)[N]>()[0]))>> =
    !__unqualified_swappable_with<T (&)[N], U (&)[N]> && extent_v<T> == extent_v<U>;
#endif

template <class T, class U>
inline constexpr bool __noexcept_swappable_arrays<T, U, void_t<type_identity_t<T>>> =
    noexcept(__fn{}(::asc::std::declval<T&>(), ::asc::std::declval<U&>()));

}  // namespace __swap_detail

inline constexpr __swap_detail::__fn swap{};

// Internal code avoids using the CPO object directly (a __tile__ access issue)
// and uniformly goes through the __fn type instead.
using __swap_cpo = __swap_detail::__fn;

}  // namespace ranges

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class T>
concept swappable = requires(T& left, T& right) { ::asc::std::ranges::__swap_cpo{}(left, right); };

template <class T, class U>
concept swappable_with = common_reference_with<T, U> && requires(T&& left, U&& right) {
    ::asc::std::ranges::__swap_cpo{}(::asc::std::forward<T>(left), ::asc::std::forward<T>(left));
    ::asc::std::ranges::__swap_cpo{}(::asc::std::forward<U>(right), ::asc::std::forward<U>(right));
    ::asc::std::ranges::__swap_cpo{}(::asc::std::forward<T>(left), ::asc::std::forward<U>(right));
    ::asc::std::ranges::__swap_cpo{}(
        ::asc::std::forward<U>(right), ::asc::std::forward<T>(left));  // NOLINT(build/include_what_you_use)
};
#else
template <class T, class = void>
inline constexpr bool __swappable_impl = false;

template <class T>
inline constexpr bool __swappable_impl<T,
    void_t<decltype(::asc::std::ranges::__swap_cpo{}(::asc::std::declval<T&>(), ::asc::std::declval<T&>()))>> = true;

template <class T, class U, class = void>
inline constexpr bool __swappable_with_impl = false;

template <class T, class U>
inline constexpr bool __swappable_with_impl<T, U,
    void_t<decltype(::asc::std::ranges::__swap_cpo{}(::asc::std::declval<T>(), ::asc::std::declval<T>())),
        decltype(::asc::std::ranges::__swap_cpo{}(::asc::std::declval<U>(), ::asc::std::declval<U>())),
        decltype(::asc::std::ranges::__swap_cpo{}(::asc::std::declval<T>(), ::asc::std::declval<U>())),
        decltype(::asc::std::ranges::__swap_cpo{}(::asc::std::declval<U>(), ::asc::std::declval<T>()))>> =
    __common_reference_with_impl<T, U>;

template <class T>
inline constexpr bool swappable = __swappable_impl<T>;
template <class T, class U>
inline constexpr bool swappable_with = __swappable_with_impl<T, U>;

#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CONCEPTS_SWAPPABLE_H
