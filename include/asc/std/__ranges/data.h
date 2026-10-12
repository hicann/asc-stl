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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_DATA_H
#define CANN_ASC_STL_ASC_STD___RANGES_DATA_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/reverse_iterator.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_pointer.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/auto_cast.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

// [range.prim.data]

namespace __data_detail {

template <class T>
inline constexpr bool __ptr_to_object = is_pointer_v<T> && is_object_v<remove_pointer_t<T>>;

// 两级分派：成员 data()（返回指针指向对象） -> to_address(ranges::begin(t))。
// 概念约束在此以基座惯用的 void_t 探测结构 + enable_if_t 展开，
// 与 access.h/size.h 的基座写法保持一致，C++17 与设备路径同样可用。
template <class T, class = void>
struct __has_member_data : false_type {};
template <class T>
struct __has_member_data<T, void_t<decltype(::asc::std::declval<T>().data())>>
    : bool_constant<__access_detail::__can_borrow<T> && __ptr_to_object<decltype(::asc::std::declval<T>().data())>> {};

template <class T, class = void>
struct __ranges_begin_invocable : false_type {};
template <class T>
struct __ranges_begin_invocable<T, void_t<decltype((void)::asc::std::ranges::__begin_cpo{}(::asc::std::declval<T>()))>>
    : bool_constant<__access_detail::__can_borrow<T>> {};

struct __fn {
    template <class T, enable_if_t<__has_member_data<T>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(noexcept(value.data()))
    {
        return value.data();
    }

    template <class T, enable_if_t<!__has_member_data<T>::value && __ranges_begin_invocable<T&&>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(::asc::std::to_address(::asc::std::ranges::__begin_cpo{}(value))))
    {
        return ::asc::std::to_address(::asc::std::ranges::__begin_cpo{}(value));
    }
};

}  // namespace __data_detail

inline constexpr __data_detail::__fn data{};

// 内部避免直接使用 CPO 对象（__tile__ 访问问题），统一走 __fn 类型。
using __data_cpo = __data_detail::__fn;

// [range.prim.cdata]

namespace __cdata_detail {

struct __fn {
    template <class T, enable_if_t<is_lvalue_reference_v<T&&>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(::asc::std::ranges::__data_cpo{}(static_cast<const remove_reference_t<T>&>(
            value)))) -> decltype(::asc::std::ranges::__data_cpo{}(static_cast<const remove_reference_t<T>&>(value)))
    {
        return ::asc::std::ranges::__data_cpo{}(static_cast<const remove_reference_t<T>&>(value));
    }

    template <class T, enable_if_t<is_rvalue_reference_v<T&&>, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(noexcept(::asc::std::ranges::__data_cpo{}(
        static_cast<const T&&>(value)))) -> decltype(::asc::std::ranges::__data_cpo{}(static_cast<const T&&>(value)))
    {
        return ::asc::std::ranges::__data_cpo{}(static_cast<const T&&>(value));
    }
};

}  // namespace __cdata_detail

inline constexpr __cdata_detail::__fn cdata{};

// 内部避免直接使用 CPO 对象（__tile__ 访问问题），统一走 __fn 类型。
using __cdata_cpo = __cdata_detail::__fn;

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_DATA_H
