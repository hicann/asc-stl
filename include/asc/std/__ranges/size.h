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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_SIZE_H
#define CANN_ASC_STL_ASC_STD___RANGES_SIZE_H

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
#include <asc/std/__concepts/arithmetic.h>
#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_unbounded_array.h>
#include <asc/std/__type_traits/make_signed.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

template <class>
inline constexpr bool disable_sized_range = false;

// [range.prim.size]

namespace __size {

template <class _Tp>
void size(_Tp&) = delete;
template <class _Tp>
void size(const _Tp&) = delete;

template <class T>
CANN_ASC_STL_API constexpr auto __adl_size(T& value) noexcept(noexcept(size(value))) -> decltype(size(value))
{
    return size(value);
}

template <class T>
inline constexpr bool __integer_like = integral<T> && !same_as<T, bool>;

template <class T, class = void>
struct __has_member_size : false_type {};
template <class T>
struct __has_member_size<T,
    void_t<decltype(static_cast<decay_t<decltype(::asc::std::declval<remove_reference_t<T>&>().size())>>(
        ::asc::std::declval<remove_reference_t<T>&>().size()))>>
    : bool_constant<!disable_sized_range<remove_cvref_t<T>> && __workaround_52970<T> &&
          __integer_like<decay_t<decltype(::asc::std::declval<remove_reference_t<T>&>().size())>>> {};

template <class T, class = void>
struct __has_adl_size : false_type {};
template <class T>
struct __has_adl_size<T,
    void_t<decltype(static_cast<decay_t<decltype(__adl_size(::asc::std::declval<remove_reference_t<T>&>()))>>(
        __adl_size(::asc::std::declval<remove_reference_t<T>&>())))>>
    : bool_constant<!disable_sized_range<remove_cvref_t<T>> && __class_or_enum<remove_cvref_t<T>> &&
          __integer_like<decay_t<decltype(__adl_size(::asc::std::declval<remove_reference_t<T>&>()))>>> {};

template <class T, class = void>
struct __has_difference : false_type {};
template <class T>
struct __has_difference<T, void_t<iterator_t<T>, decltype(__end_cpo{}(::asc::std::declval<T&>()))>>
    : bool_constant<__class_or_enum<remove_cvref_t<T>> && forward_iterator<iterator_t<T>> &&
          sized_sentinel_for<decltype(__end_cpo{}(::asc::std::declval<T&>())), iterator_t<T>>> {};

struct __fn {
    template <class T, size_t N>
    CANN_ASC_STL_API constexpr size_t operator()(T (&&)[N]) const noexcept
    {
        return N;
    }
    template <class T, size_t N>
    CANN_ASC_STL_API constexpr size_t operator()(T (&)[N]) const noexcept
    {
        return N;
    }
    template <class T, enable_if_t<__has_member_size<T>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(
        noexcept(static_cast<decay_t<decltype(value.size())>>(value.size()))) -> decay_t<decltype(value.size())>
    {
        return static_cast<decay_t<decltype(value.size())>>(value.size());
    }
    template <class T, enable_if_t<!__has_member_size<T>::value && __has_adl_size<T>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(noexcept(
        static_cast<decay_t<decltype(__adl_size(value))>>(__adl_size(value)))) -> decay_t<decltype(__adl_size(value))>
    {
        return static_cast<decay_t<decltype(__adl_size(value))>>(__adl_size(value));
    }
    template <class T,
        enable_if_t<!__has_member_size<T>::value && !__has_adl_size<T>::value && __has_difference<T>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(::asc::std::__to_unsigned_like(__end_cpo{}(value)-__begin_cpo{}(
            value)))) -> decltype(::asc::std::__to_unsigned_like(__end_cpo{}(value)-__begin_cpo{}(value)))
    {
        return ::asc::std::__to_unsigned_like(__end_cpo{}(value)-__begin_cpo{}(value));
    }
};

}  // namespace __size

inline constexpr __size::__fn size{};

// Avoid using the CPO object internally because of __tile__ access.
using __size_cpo = __size::__fn;

// [range.prim.ssize]

namespace __ssize {

struct __fn {
    // Requires-expression equivalent: `ranges::size(__t)` must be a valid call. Unbounded arrays
    // are rejected because no array-bound overload exists for them.
    template <class _Tp>
    CANN_ASC_STL_API constexpr auto operator()(_Tp&& __t) const noexcept(
        noexcept(::asc::std::ranges::__size_cpo{}(__t)))
        -> conditional_t<(sizeof(ptrdiff_t) > sizeof(make_signed_t<decltype(::asc::std::ranges::__size_cpo{}(__t))>)),
            ptrdiff_t, make_signed_t<decltype(::asc::std::ranges::__size_cpo{}(__t))>>
    {
        using _Signed = make_signed_t<decltype(::asc::std::ranges::__size_cpo{}(__t))>;
        using _Result = conditional_t<(sizeof(ptrdiff_t) > sizeof(_Signed)), ptrdiff_t, _Signed>;
        return static_cast<_Result>(::asc::std::ranges::__size_cpo{}(__t));
    }
};

}  // namespace __ssize

inline constexpr __ssize::__fn ssize{};

// Avoid using the CPO object internally because of __tile__ access.
using __ssize_cpo = __ssize::__fn;

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_SIZE_H
