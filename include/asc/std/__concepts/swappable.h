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

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
namespace __swap_detail {
template <class T>
void swap(T&, T&) = delete;

template <class T, class U>
concept __adl_swappable_with = (__class_or_enum<remove_cvref_t<T>> || __class_or_enum<remove_cvref_t<U>>) &&
    requires(T&& left, U&& right) { swap(::asc::std::forward<T>(left), ::asc::std::forward<U>(right)); };

struct __fn;
template <class T, class U, size_t N>
concept __swappable_arrays = !__adl_swappable_with<T (&)[N], U (&)[N]> &&
    requires(T (&left)[N], U (&right)[N], const __fn& action) { action(left[0], right[0]); };

struct __fn {
    template <class T, class U>
        requires __adl_swappable_with<T, U>
    CANN_ASC_STL_API constexpr void operator()(T&& left, U&& right) const
        noexcept(noexcept(swap(::asc::std::forward<T>(left), ::asc::std::forward<U>(right))))
    {
        swap(::asc::std::forward<T>(left), ::asc::std::forward<U>(right));
    }

    template <class T, class U, size_t N>
        requires __swappable_arrays<T, U, N>
    CANN_ASC_STL_API constexpr void operator()(T (&left)[N], U (&right)[N]) const
        noexcept(noexcept(__fn{}(left[0], right[0])))
    {
        for (size_t index = 0; index < N; ++index) {
            (*this)(left[index], right[index]);
        }
    }

    template <class T>
        requires(!__adl_swappable_with<T&, T&>) && move_constructible<T> && assignable_from<T&, T>
    CANN_ASC_STL_API constexpr void operator()(T& left, T& right) const
        noexcept(is_nothrow_move_constructible_v<T> && is_nothrow_move_assignable_v<T>)
    {
        right = ::asc::std::exchange(left, ::asc::std::move(right));
    }
};
}  // namespace __swap_detail

template <class T>
concept swappable = requires(T& left, T& right) { __swap_detail::__fn{}(left, right); };

template <class T, class U>
concept swappable_with = common_reference_with<T, U> && requires(T&& left, U&& right) {
    __swap_detail::__fn{}(::asc::std::forward<T>(left), ::asc::std::forward<T>(left));
    __swap_detail::__fn{}(::asc::std::forward<U>(right), ::asc::std::forward<U>(right));
    __swap_detail::__fn{}(::asc::std::forward<T>(left), ::asc::std::forward<U>(right));
    __swap_detail::__fn{}(
        ::asc::std::forward<U>(right), ::asc::std::forward<T>(left));  // NOLINT(build/include_what_you_use)
};
#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CONCEPTS_SWAPPABLE_H
