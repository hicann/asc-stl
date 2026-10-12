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

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

// begin 结果校验保持表达式有效性级（含 decay 转换）：产品冻结用例要求仅有
// operator-> 的经典代理迭代器可经 begin 路由（ranges::data 的回退依赖此形状），
// 严于 input_or_output_iterator 的标准校验会破坏既有交付面。
template <class T>
concept __member_begin = __can_borrow<T> && __workaround_52970<T> &&
    requires(T&& value) { static_cast<decay_t<decltype((value.begin()))>>(value.begin()); };

template <class T>
concept __unqualified_begin = !__member_begin<T> && __can_borrow<T> && __class_or_enum<remove_cvref_t<T>> &&
    requires(T&& value) { static_cast<decay_t<decltype((begin(value)))>>(begin(value)); };

struct __begin_fn {
    // 未知边界数组的 begin 自 C++17 起为缺陷报告接纳；gcc 11 以下未实现，按编译器版本门控。
#if !defined(__GNUC__) || defined(__clang__) || __GNUC__ >= 11
    template <class T>
        requires(sizeof(T) >= 0)  // 不允许不完整元素类型
    CANN_ASC_STL_API constexpr T* operator()(T (&array)[]) const noexcept
    {
        return array;
    }
#endif

    template <class T, size_t N>
        requires(sizeof(T) >= 0)  // 不允许不完整元素类型
    CANN_ASC_STL_API constexpr T* operator()(T (&array)[N]) const noexcept
    {
        return array;
    }

    template <class T>
        requires __member_begin<T>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(
        noexcept(static_cast<decay_t<decltype((value.begin()))>>(value.begin()))) -> decay_t<decltype((value.begin()))>
    {
        return static_cast<decay_t<decltype((value.begin()))>>(value.begin());
    }

    template <class T>
        requires __unqualified_begin<T>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(
        noexcept(static_cast<decay_t<decltype((begin(value)))>>(begin(value)))) -> decay_t<decltype((begin(value)))>
    {
        return static_cast<decay_t<decltype((begin(value)))>>(begin(value));
    }

    template <class T>
        requires(!__member_begin<T> && !__unqualified_begin<T>)
    void operator()(T&&) const = delete;
};

#else  // ^^^ concepts ^^^ / vvv !concepts vvv

// 非概念路径保持基座惯用形状（void_t 探测 + enable_if_t 分派）；begin 结果上的
// input_or_output_iterator 概念校验与 decay 转换在此路径降级为表达式有效性级检查。
template <class T, class = void>
struct __has_member_begin : false_type {};
template <class T>
struct __has_member_begin<T, void_t<decltype(::asc::std::declval<remove_reference_t<T>&>().begin())>> : true_type {};

struct __begin_fn {
    template <class T, size_t N>
    CANN_ASC_STL_API constexpr T* operator()(T (&array)[N]) const noexcept
    {
        return array;
    }
    template <class T, enable_if_t<__can_borrow<T&&> && __has_member_begin<T&&>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(
        noexcept(remove_cvref_t<decltype(value.begin())>(value.begin()))) -> remove_cvref_t<decltype(value.begin())>
    {
        return value.begin();
    }
    template <class T, enable_if_t<__can_borrow<T&&> && !__has_member_begin<T&&>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(remove_cvref_t<decltype(__adl_begin(value))>(
            __adl_begin(value)))) -> remove_cvref_t<decltype(__adl_begin(value))>
    {
        return __adl_begin(value);
    }
};

#endif  // !concepts

}  // namespace __access_detail

inline constexpr __access_detail::__begin_fn begin{};
// 内部实现统一经 __fn 类型调用，避免公开 CPO 对象参与 ADL 名字查找被劫持。
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

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

template <class T>
concept __member_end = __access_detail::__can_borrow<T> && __workaround_52970<T> && requires(T&& value) {
    typename iterator_t<T>;
    { static_cast<decay_t<decltype((value.end()))>>(value.end()) } -> sentinel_for<iterator_t<T>>;
};

template <class T>
concept __unqualified_end =
    !__member_end<T> && __access_detail::__can_borrow<T> && __class_or_enum<remove_cvref_t<T>> && requires(T&& value) {
        typename iterator_t<T>;
        { static_cast<decay_t<decltype((end(value)))>>(end(value)) } -> sentinel_for<iterator_t<T>>;
    };

struct __end_fn {
    template <class T, size_t N>
        requires(sizeof(T) >= 0)  // 不允许不完整元素类型
    CANN_ASC_STL_API constexpr T* operator()(T (&array)[N]) const noexcept
    {
        return array + N;
    }

    template <class T>
        requires __member_end<T>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(
        noexcept(static_cast<decay_t<decltype((value.end()))>>(value.end()))) -> decay_t<decltype((value.end()))>
    {
        return static_cast<decay_t<decltype((value.end()))>>(value.end());
    }

    template <class T>
        requires __unqualified_end<T>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(static_cast<decay_t<decltype((end(value)))>>(end(value)))) -> decay_t<decltype((end(value)))>
    {
        return static_cast<decay_t<decltype((end(value)))>>(end(value));
    }

    template <class T>
        requires(!__member_end<T> && !__unqualified_end<T>)
    void operator()(T&&) const = delete;
};

#else  // ^^^ concepts ^^^ / vvv !concepts vvv

// 非概念路径保持基座惯用形状（void_t 探测 + enable_if_t 分派）；end 结果上的
// sentinel_for 概念校验与 decay 转换在此路径降级为表达式有效性级检查。
template <class T, class = void>
struct __has_member_end : false_type {};
template <class T>
struct __has_member_end<T, void_t<decltype(::asc::std::declval<remove_reference_t<T>&>().end())>> : true_type {};

struct __end_fn {
    template <class T, size_t N>
    CANN_ASC_STL_API constexpr T* operator()(T (&array)[N]) const noexcept
    {
        return array + N;
    }
    template <class T, enable_if_t<__access_detail::__can_borrow<T&&> && __has_member_end<T&&>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(remove_cvref_t<decltype(value.end())>(value.end()))) -> remove_cvref_t<decltype(value.end())>
    {
        return value.end();
    }
    template <class T, enable_if_t<__access_detail::__can_borrow<T&&> && !__has_member_end<T&&>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(noexcept(
        remove_cvref_t<decltype(__adl_end(value))>(__adl_end(value)))) -> remove_cvref_t<decltype(__adl_end(value))>
    {
        return __adl_end(value);
    }
};

#endif  // !concepts

}  // namespace __end_detail

inline constexpr __end_detail::__end_fn end{};
// 内部实现统一经 __fn 类型调用，避免公开 CPO 对象参与 ADL 名字查找被劫持。
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
