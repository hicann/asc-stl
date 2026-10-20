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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_REND_H
#define CANN_ASC_STL_ASC_STD___RANGES_REND_H

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
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/reverse_iterator.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__ranges/rbegin.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_union.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/auto_cast.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

// [range.access.rend]

namespace __rend_detail {

template <class T>
void rend(T&) = delete;
template <class T>
void rend(const T&) = delete;

template <class T>
CANN_ASC_STL_API constexpr auto __adl_rend(T&& value) noexcept(noexcept(rend(value))) -> decltype(rend(value))
{
    return rend(value);
}

template <class T, class = void>
struct __has_member_rend : false_type {};
template <class T>
struct __has_member_rend<T,
    void_t<decltype(__rbegin_cpo{}(::asc::std::declval<remove_reference_t<T>&>())),
        decltype(static_cast<decay_t<decltype(::asc::std::declval<remove_reference_t<T>&>().rend())>>(
            ::asc::std::declval<remove_reference_t<T>&>().rend()))>>
    : bool_constant<__access_detail::__can_borrow<T> && __workaround_52970<T> &&
          sentinel_for<decay_t<decltype(::asc::std::declval<remove_reference_t<T>&>().rend())>,
              decltype(__rbegin_cpo{}(::asc::std::declval<remove_reference_t<T>&>()))>> {};

template <class T, class = void>
struct __has_adl_rend : false_type {};
template <class T>
struct __has_adl_rend<T,
    void_t<decltype(__rbegin_cpo{}(::asc::std::declval<remove_reference_t<T>&>())),
        decltype(static_cast<decay_t<decltype(__adl_rend(::asc::std::declval<remove_reference_t<T>&>()))>>(
            __adl_rend(::asc::std::declval<remove_reference_t<T>&>())))>>
    : bool_constant<__access_detail::__can_borrow<T> && __class_or_enum<remove_cvref_t<T>> &&
          sentinel_for<decay_t<decltype(__adl_rend(::asc::std::declval<remove_reference_t<T>&>()))>,
              decltype(__rbegin_cpo{}(::asc::std::declval<remove_reference_t<T>&>()))>> {};

template <class T, class = void>
struct __same_begin_end : false_type {};
template <class T>
struct __same_begin_end<T, void_t<iterator_t<T>, decltype(__end_cpo{}(::asc::std::declval<T&>()))>>
    : bool_constant<__access_detail::__can_borrow<T> &&
          is_same_v<iterator_t<T>, decltype(__end_cpo{}(::asc::std::declval<T&>()))> &&
          bidirectional_iterator<iterator_t<T>>> {};

struct __fn {
    template <class T, enable_if_t<__has_member_rend<T>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(
        noexcept(static_cast<decay_t<decltype(value.rend())>>(value.rend()))) -> decay_t<decltype(value.rend())>
    {
        return static_cast<decay_t<decltype(value.rend())>>(value.rend());
    }
    template <class T, enable_if_t<!__has_member_rend<T>::value && __has_adl_rend<T>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(noexcept(
        static_cast<decay_t<decltype(__adl_rend(value))>>(__adl_rend(value)))) -> decay_t<decltype(__adl_rend(value))>
    {
        return static_cast<decay_t<decltype(__adl_rend(value))>>(__adl_rend(value));
    }
    template <class T,
        enable_if_t<!__has_member_rend<T>::value && !__has_adl_rend<T>::value && __same_begin_end<T>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(noexcept(::asc::std::make_reverse_iterator(
        __begin_cpo{}(value)))) -> decltype(::asc::std::make_reverse_iterator(__begin_cpo{}(value)))
    {
        return ::asc::std::make_reverse_iterator(__begin_cpo{}(value));
    }
};

}  // namespace __rend_detail

inline constexpr __rend_detail::__fn rend{};

// Internal uses go through the __fn type rather than the CPO object directly
// (avoids the __tile__ access problem).
using __rend_cpo = __rend_detail::__fn;

// [range.access.crend]

namespace __crend_detail {

struct __fn {
    template <class T, enable_if_t<is_lvalue_reference_v<T&&>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& __t) const
        noexcept(noexcept(::asc::std::ranges::__rend_cpo{}(static_cast<const remove_reference_t<T>&>(
            __t)))) -> decltype(::asc::std::ranges::__rend_cpo{}(static_cast<const remove_reference_t<T>&>(__t)))
    {
        return ::asc::std::ranges::__rend_cpo{}(static_cast<const remove_reference_t<T>&>(__t));
    }

    template <class T, enable_if_t<is_rvalue_reference_v<T&&>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& __t) const noexcept(noexcept(::asc::std::ranges::__rend_cpo{}(
        static_cast<const T&&>(__t)))) -> decltype(::asc::std::ranges::__rend_cpo{}(static_cast<const T&&>(__t)))
    {
        return ::asc::std::ranges::__rend_cpo{}(static_cast<const T&&>(__t));
    }
};

}  // namespace __crend_detail

inline constexpr __crend_detail::__fn crend{};

// Internal uses go through the __fn type rather than the CPO object directly
// (avoids the __tile__ access problem).
using __crend_cpo = __crend_detail::__fn;

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_REND_H
