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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_ACCESS_H
#define CANN_ASC_STL_ASC_STD___RANGES_ACCESS_H

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
#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__type_traits/decay.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/auto_cast.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

// [range.access.begin]

namespace __access_detail {

template <class T>
void begin(T&) = delete;
template <class T>
void begin(const T&) = delete;

template <class T>
CANN_ASC_STL_API constexpr auto __adl_begin(T& value) noexcept(noexcept(begin(value))) -> decltype(begin(value))
{
    return begin(value);
}

template <class T>
inline constexpr bool __can_borrow = is_lvalue_reference_v<T> || enable_borrowed_range<remove_cvref_t<T>>;

// Result conversion and overload participation are shared by both dialects.
// begin deliberately retains the established expression-validity contract;
// end separately validates the sentinel relationship.
template <class T, class = void>
struct __has_member_begin : false_type {};
template <class T>
struct __has_member_begin<T,
    void_t<decltype(static_cast<decay_t<decltype(::asc::std::declval<remove_reference_t<T>&>().begin())>>(
        ::asc::std::declval<remove_reference_t<T>&>().begin()))>>
    : bool_constant<__can_borrow<T> && __workaround_52970<T>> {};

template <class T, class = void>
struct __has_adl_begin : false_type {};
template <class T>
struct __has_adl_begin<T,
    void_t<decltype(static_cast<decay_t<decltype(__adl_begin(::asc::std::declval<remove_reference_t<T>&>()))>>(
        __adl_begin(::asc::std::declval<remove_reference_t<T>&>())))>>
    : bool_constant<__can_borrow<T> && __class_or_enum<remove_cvref_t<T>>> {};

struct __begin_fn {
#if !defined(__GNUC__) || defined(__clang__) || __GNUC__ >= 11
    template <class T, size_t = sizeof(T)>
    CANN_ASC_STL_API constexpr T* operator()(T (&array)[]) const noexcept
    {
        return array;
    }
#endif
    template <class T, size_t N, size_t = sizeof(T)>
    CANN_ASC_STL_API constexpr T* operator()(T (&array)[N]) const noexcept
    {
        return array;
    }
    template <class T, enable_if_t<__has_member_begin<T>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(
        noexcept(static_cast<decay_t<decltype(value.begin())>>(value.begin()))) -> decay_t<decltype(value.begin())>
    {
        return static_cast<decay_t<decltype(value.begin())>>(value.begin());
    }
    template <class T, enable_if_t<!__has_member_begin<T>::value && __has_adl_begin<T>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(static_cast<decay_t<decltype(__adl_begin(value))>>(
            __adl_begin(value)))) -> decay_t<decltype(__adl_begin(value))>
    {
        return static_cast<decay_t<decltype(__adl_begin(value))>>(__adl_begin(value));
    }
};

}  // namespace __access_detail

inline constexpr __access_detail::__begin_fn begin{};
// Internal callers invoke the __fn type so the public CPO object is not found via
// ADL and cannot be hijacked.
using __begin_cpo = __access_detail::__begin_fn;

// [range.range]

template <class T>
using iterator_t = decltype(__begin_cpo{}(::asc::std::declval<T&>()));

// [range.access.end]

namespace __end_detail {

template <class T>
void end(T&) = delete;
template <class T>
void end(const T&) = delete;

template <class T>
CANN_ASC_STL_API constexpr auto __adl_end(T& value) noexcept(noexcept(end(value))) -> decltype(end(value))
{
    return end(value);
}

template <class T, class = void>
struct __has_member_end : false_type {};
template <class T>
struct __has_member_end<T,
    void_t<iterator_t<T>,
        decltype(static_cast<decay_t<decltype(::asc::std::declval<remove_reference_t<T>&>().end())>>(
            ::asc::std::declval<remove_reference_t<T>&>().end()))>>
    : bool_constant<__access_detail::__can_borrow<T> && __workaround_52970<T> &&
          sentinel_for<decay_t<decltype(::asc::std::declval<remove_reference_t<T>&>().end())>, iterator_t<T>>> {};

template <class T, class = void>
struct __has_adl_end : false_type {};
template <class T>
struct __has_adl_end<T,
    void_t<iterator_t<T>,
        decltype(static_cast<decay_t<decltype(__adl_end(::asc::std::declval<remove_reference_t<T>&>()))>>(
            __adl_end(::asc::std::declval<remove_reference_t<T>&>())))>>
    : bool_constant<__access_detail::__can_borrow<T> && __class_or_enum<remove_cvref_t<T>> &&
          sentinel_for<decay_t<decltype(__adl_end(::asc::std::declval<remove_reference_t<T>&>()))>, iterator_t<T>>> {};

struct __end_fn {
    template <class T, size_t N, size_t = sizeof(T)>
    CANN_ASC_STL_API constexpr T* operator()(T (&array)[N]) const noexcept
    {
        return array + N;
    }
    template <class T, enable_if_t<__has_member_end<T>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(static_cast<decay_t<decltype(value.end())>>(value.end()))) -> decay_t<decltype(value.end())>
    {
        return static_cast<decay_t<decltype(value.end())>>(value.end());
    }
    template <class T, enable_if_t<!__has_member_end<T>::value && __has_adl_end<T>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(noexcept(
        static_cast<decay_t<decltype(__adl_end(value))>>(__adl_end(value)))) -> decay_t<decltype(__adl_end(value))>
    {
        return static_cast<decay_t<decltype(__adl_end(value))>>(__adl_end(value));
    }
};

}  // namespace __end_detail

inline constexpr __end_detail::__end_fn end{};
// Internal callers invoke the __fn type so the public CPO object is not found via
// ADL and cannot be hijacked.
using __end_cpo = __end_detail::__end_fn;

// [range.access.cbegin]

struct __cbegin_fn {
    template <class T, enable_if_t<is_lvalue_reference_v<T&&>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(__begin_cpo{}(static_cast<const remove_reference_t<T>&>(
            value)))) -> decltype(__begin_cpo{}(static_cast<const remove_reference_t<T>&>(value)))
    {
        return __begin_cpo{}(static_cast<const remove_reference_t<T>&>(value));
    }

    template <class T, enable_if_t<is_rvalue_reference_v<T&&>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(noexcept(
        __begin_cpo{}(static_cast<const T&&>(value)))) -> decltype(__begin_cpo{}(static_cast<const T&&>(value)))
    {
        return __begin_cpo{}(static_cast<const T&&>(value));
    }
};
struct __cend_fn {
    template <class T, enable_if_t<is_lvalue_reference_v<T&&>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(__end_cpo{}(static_cast<const remove_reference_t<T>&>(
            value)))) -> decltype(__end_cpo{}(static_cast<const remove_reference_t<T>&>(value)))
    {
        return __end_cpo{}(static_cast<const remove_reference_t<T>&>(value));
    }

    template <class T, enable_if_t<is_rvalue_reference_v<T&&>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(
        noexcept(__end_cpo{}(static_cast<const T&&>(value)))) -> decltype(__end_cpo{}(static_cast<const T&&>(value)))
    {
        return __end_cpo{}(static_cast<const T&&>(value));
    }
};
inline constexpr __cbegin_fn cbegin{};
inline constexpr __cend_fn cend{};

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_ACCESS_H
