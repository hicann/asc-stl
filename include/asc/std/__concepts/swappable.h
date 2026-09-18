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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPTS_SWAPPABLE_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPTS_SWAPPABLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/assignable.h>
#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__concepts/common_reference_with.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__type_traits/extent.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/type_identity.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/exchange.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

// [concept.swappable]

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_CPO(__swap)

template <class _Tp>
void swap(_Tp&, _Tp&) = delete;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class _Tp, class _Up>
concept __unqualified_swappable_with = (__class_or_enum<remove_cvref_t<_Tp>> || __class_or_enum<remove_cvref_t<_Up>>) &&
    requires(_Tp&& __t, _Up&& __u) { swap(::asc::std::forward<_Tp>(__t), ::asc::std::forward<_Up>(__u)); };

template <class _Tp>
concept __exchangeable =
    !__unqualified_swappable_with<_Tp&, _Tp&> && move_constructible<_Tp> && assignable_from<_Tp&, _Tp>;

#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv

template <class _Tp, class _Up, class = void>
inline constexpr bool __unqualified_swappable_with_impl = false;

template <class _Tp, class _Up>
inline constexpr bool __unqualified_swappable_with_impl<_Tp, _Up,
    void_t<decltype(swap(::asc::std::declval<_Tp>(), ::asc::std::declval<_Up>()))>> =
    __class_or_enum<remove_cvref_t<_Tp>> || __class_or_enum<remove_cvref_t<_Up>>;

template <class _Tp, class _Up>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __unqualified_swappable_with = __unqualified_swappable_with_impl<_Tp, _Up>;

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __exchangeable =
    !__unqualified_swappable_with<_Tp&, _Tp&> && move_constructible<_Tp> && assignable_from<_Tp&, _Tp>;
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
struct __fn;

template <class _Tp, class _Up, size_t _Size>
concept __swappable_arrays =
    !__unqualified_swappable_with<_Tp (&)[_Size], _Up (&)[_Size]> && extent_v<_Tp> == extent_v<_Up> &&
    requires(_Tp (&__t)[_Size], _Up (&__u)[_Size], const __fn& __swap) { __swap(__t[0], __u[0]); };
#else
template <class _Tp, class _Up, size_t _Size, class = void>
inline constexpr bool __swappable_arrays = false;
#endif

template <class _Tp, class _Up, class = void>
inline constexpr bool __noexcept_swappable_arrays = false;

struct __fn {
    // 2.1   `S` is `(void)swap(E1, E2)`* if `E1` or `E2` has class or enumeration type and...
    // *The name `swap` is used here unqualified.
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Up)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__unqualified_swappable_with<_Tp, _Up>)
    CANN_ASC_STL_API constexpr void operator()(_Tp&& __t, _Up&& __u) const
        noexcept(noexcept(swap(::asc::std::forward<_Tp>(__t), ::asc::std::forward<_Up>(__u))))
    {
        swap(::asc::std::forward<_Tp>(__t), ::asc::std::forward<_Up>(__u));
    }

    // 2.2   Otherwise, if `E1` and `E2` are lvalues of array types with equal extent and...
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp, class _Up, size_t _Size)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__swappable_arrays<_Tp, _Up, _Size>)
    CANN_ASC_STL_API constexpr void operator()(_Tp (&__t)[_Size], _Up (&__u)[_Size]) const
        noexcept(__noexcept_swappable_arrays<_Tp, _Up>)
    {
        for (size_t __i = 0; __i < _Size; ++__i) {
            (*this)(__t[__i], __u[__i]);
        }
    }

    // 2.3   Otherwise, if `E1` and `E2` are lvalues of the same type `T` that models...
    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _Tp)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(__exchangeable<_Tp>)
    CANN_ASC_STL_API constexpr void operator()(_Tp& __x, _Tp& __y) const
        noexcept(is_nothrow_move_constructible_v<_Tp> && is_nothrow_move_assignable_v<_Tp>)
    {
        __y = ::asc::std::exchange(__x, ::asc::std::move(__y));
    }
};

#if !CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class _Tp, class _Up, size_t _Size>
inline constexpr bool __swappable_arrays<_Tp, _Up, _Size,
    void_t<decltype(::asc::std::declval<const __fn&>()(
        ::asc::std::declval<_Tp (&)[_Size]>()[0], ::asc::std::declval<_Up (&)[_Size]>()[0]))>> =
    !__unqualified_swappable_with<_Tp (&)[_Size], _Up (&)[_Size]> && extent_v<_Tp> == extent_v<_Up>;
#endif

template <class _Tp, class _Up>
inline constexpr bool __noexcept_swappable_arrays<_Tp, _Up, void_t<type_identity_t<_Tp>>> =
    noexcept(__swap::__fn{}(::asc::std::declval<_Tp&>(), ::asc::std::declval<_Up&>()));

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_CPO

inline namespace __cpo {
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT auto swap = __swap::__fn{};

using __swap_cpo = __swap::__fn;
}  // namespace __cpo
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class _Tp>
concept swappable = requires(_Tp& __a, _Tp& __b) { ::asc::std::ranges::__swap_cpo{}(__a, __b); };

template <class _Tp, class _Up>
concept swappable_with = common_reference_with<_Tp, _Up> && requires(_Tp&& __t, _Up&& __u) {
    ::asc::std::ranges::__swap_cpo{}(::asc::std::forward<_Tp>(__t), ::asc::std::forward<_Tp>(__t));
    ::asc::std::ranges::__swap_cpo{}(::asc::std::forward<_Up>(__u), ::asc::std::forward<_Up>(__u));
    ::asc::std::ranges::__swap_cpo{}(::asc::std::forward<_Tp>(__t), ::asc::std::forward<_Up>(__u));
    ::asc::std::ranges::__swap_cpo{}(
        ::asc::std::forward<_Up>(__u), ::asc::std::forward<_Tp>(__t));  // NOLINT(build/include_what_you_use)
};
#else   // ^^^ CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() vvv
template <class _Tp, class = void>
inline constexpr bool __swappable_impl = false;

template <class _Tp>
inline constexpr bool __swappable_impl<_Tp,
    void_t<decltype(::asc::std::ranges::__swap_cpo{}(::asc::std::declval<_Tp&>(), ::asc::std::declval<_Tp&>()))>> =
    true;

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT swappable = __swappable_impl<_Tp>;

template <class _Tp, class _Up, class = void>
inline constexpr bool __swappable_with_impl = false;

template <class _Tp, class _Up>
inline constexpr bool __swappable_with_impl<_Tp, _Up,
    void_t<decltype(::asc::std::ranges::__swap_cpo{}(::asc::std::declval<_Tp>(), ::asc::std::declval<_Tp>())),
        decltype(::asc::std::ranges::__swap_cpo{}(::asc::std::declval<_Up>(), ::asc::std::declval<_Up>())),
        decltype(::asc::std::ranges::__swap_cpo{}(::asc::std::declval<_Tp>(), ::asc::std::declval<_Up>())),
        decltype(::asc::std::ranges::__swap_cpo{}(::asc::std::declval<_Up>(), ::asc::std::declval<_Tp>()))>> =
    common_reference_with<_Tp, _Up>;

template <class _Tp, class _Up>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT swappable_with = __swappable_with_impl<_Tp, _Up>;
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CONCEPTS_SWAPPABLE_H
