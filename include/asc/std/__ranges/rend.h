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

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

template <class T>
concept __member_rend = __access_detail::__can_borrow<T> && __workaround_52970<T> && requires(T&& __t) {
    ::asc::std::ranges::__rbegin_cpo{}(__t);
    {
        __t.rend()
    } -> sentinel_for<decltype(::asc::std::ranges::__rbegin_cpo{}(__t))>;  // the return-type requirement is expanded
                                                                           // at the use site
};

template <class T>
concept __unqualified_rend =
    !__member_rend<T> && __access_detail::__can_borrow<T> && __class_or_enum<remove_cvref_t<T>> && requires(T&& __t) {
        ::asc::std::ranges::__rbegin_cpo{}(__t);
        { __adl_rend(__t) } -> sentinel_for<decltype(::asc::std::ranges::__rbegin_cpo{}(__t))>;
    };

template <class T>
concept __can_reverse =
    __access_detail::__can_borrow<T> && !__member_rend<T> && !__unqualified_rend<T> && requires(T&& __t) {
        { ::asc::std::ranges::__begin_cpo{}(__t) } -> same_as<decltype(::asc::std::ranges::__end_cpo{}(__t))>;
        { ::asc::std::ranges::__begin_cpo{}(__t) } -> bidirectional_iterator;
    };

class __fn {
public:
    template <class T>
        requires __member_rend<T>
    CANN_ASC_STL_API constexpr auto operator()(T&& __t) const noexcept(noexcept(__t.rend()))
    {
        return __t.rend();
    }

    template <class T>
        requires __unqualified_rend<T>
    CANN_ASC_STL_API constexpr auto operator()(T&& __t) const noexcept(noexcept(__adl_rend(__t)))
    {
        return __adl_rend(__t);
    }

    template <class T>
        requires __can_reverse<T>
    CANN_ASC_STL_API constexpr auto operator()(T&& __t) const noexcept(noexcept(::asc::std::ranges::__begin_cpo{}(__t)))
    {
        return ::asc::std::make_reverse_iterator(::asc::std::ranges::__begin_cpo{}(__t));
    }

    template <class T>
        requires(!__member_rend<T> && !__unqualified_rend<T> && !__can_reverse<T>)
    void operator()(T&&) const = delete;
};

#else  // ^^^ concepts ^^^ / vvv !concepts vvv

// 非概念路径：按基座惯用的 void_t 探测 + enable_if_t 展开，语义与概念版对齐；
// 返回类型上的哨位/迭代器概念约束（sentinel_for/bidirectional_iterator）在此路径降为
// 表达式有效性级检查（与基座原实现同级），其余门控（can_borrow/类或枚举/rbegin 可调用/begin-end 同型）保持不变。
template <class T>
inline constexpr bool __is_class_or_union_v = is_class_v<remove_cvref_t<T>> || is_union_v<remove_cvref_t<T>>;
template <class T>
inline constexpr bool __is_class_or_enum_v = __is_class_or_union_v<T> || is_enum_v<remove_cvref_t<T>>;

template <class T, class = void>
struct __has_member_rend : false_type {};
template <class T>
struct __has_member_rend<T,
    void_t<decltype(::asc::std::ranges::__rbegin_cpo{}(::asc::std::declval<T>())),
        decltype(::asc::std::declval<T>().rend())>>
    : bool_constant<__access_detail::__can_borrow<T> && __is_class_or_union_v<T>> {};

template <class T, class = void>
struct __has_adl_rend : false_type {};
template <class T>
struct __has_adl_rend<T,
    void_t<decltype(::asc::std::ranges::__rbegin_cpo{}(::asc::std::declval<T>())),
        decltype(__adl_rend(::asc::std::declval<T>()))>>
    : bool_constant<__access_detail::__can_borrow<T> && __is_class_or_enum_v<T>> {};

template <class T, class = void>
struct __same_begin_end : false_type {};
template <class T>
struct __same_begin_end<T,
    void_t<decltype(::asc::std::ranges::__begin_cpo{}(::asc::std::declval<T>())),
        decltype(::asc::std::ranges::__end_cpo{}(::asc::std::declval<T>()))>>
    : bool_constant<is_same_v<decltype(::asc::std::ranges::__begin_cpo{}(::asc::std::declval<T>())),
          decltype(::asc::std::ranges::__end_cpo{}(::asc::std::declval<T>()))>> {};

class __fn {
public:
    template <class T, enable_if_t<__has_member_rend<T>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& __t) const noexcept(noexcept(__t.rend()))
    {
        return __t.rend();
    }

    template <class T, enable_if_t<!__has_member_rend<T>::value && __has_adl_rend<T>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& __t) const noexcept(noexcept(__adl_rend(__t)))
    {
        return __adl_rend(__t);
    }

    template <class T,
        enable_if_t<!__has_member_rend<T>::value && !__has_adl_rend<T>::value && __access_detail::__can_borrow<T> &&
                __same_begin_end<T>::value,
            int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& __t) const
        noexcept(noexcept(::asc::std::make_reverse_iterator(::asc::std::ranges::__begin_cpo{}(__t))))
    {
        return ::asc::std::make_reverse_iterator(::asc::std::ranges::__begin_cpo{}(__t));
    }

    template <class T,
        enable_if_t<!__has_member_rend<T>::value && !__has_adl_rend<T>::value && !__same_begin_end<T>::value, int> = 0>
    void operator()(T&&) const = delete;
};

#endif  // !concepts

}  // namespace __rend_detail

inline constexpr __rend_detail::__fn rend{};

// 内部避免直接使用 CPO 对象（__tile__ 访问问题），统一走 __fn 类型。
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

// 内部避免直接使用 CPO 对象（__tile__ 访问问题），统一走 __fn 类型。
using __crend_cpo = __crend_detail::__fn;

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_REND_H
