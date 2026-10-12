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

#ifndef CANN_ASC_STL_ASC_STD___ITERATOR_ITER_MOVE_H
#define CANN_ASC_STL_ASC_STD___ITERATOR_ITER_MOVE_H

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
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __iter_move_detail {

void iter_move();

template <class T, class = void>
struct __has_adl_iter_move : false_type {};

// 仅当 remove_cvref_t<T> 是类/联合/枚举类型时，ADL 找到的 iter_move 才构成定制点；
// 标量类型的关联命名空间不含候选，保持走解引用分派路径。
template <class T>
struct __has_adl_iter_move<T,
    void_t<decltype(iter_move(::asc::std::declval<T>())), enable_if_t<__class_or_enum<remove_cvref_t<T>>>>>
    : true_type {};

template <class T, bool = is_lvalue_reference_v<decltype(*::asc::std::declval<T>())>>
struct __deref_move;

template <class T>
struct __deref_move<T, true> {
    CANN_ASC_STL_API static constexpr auto call(T&& value) noexcept(noexcept(
        ::asc::std::move(*::asc::std::forward<T>(value)))) -> decltype(::asc::std::move(*::asc::std::forward<T>(value)))
    {
        return ::asc::std::move(*::asc::std::forward<T>(value));
    }
};

template <class T>
struct __deref_move<T, false> {
    CANN_ASC_STL_API static constexpr auto call(T&& value) noexcept(
        noexcept(*::asc::std::forward<T>(value))) -> decltype(*::asc::std::forward<T>(value))
    {
        return *::asc::std::forward<T>(value);
    }
};

template <class T, bool = __has_adl_iter_move<T&&>::value>
struct __dispatch;

template <class T>
struct __dispatch<T, true> {
    CANN_ASC_STL_API static constexpr auto call(T&& value) noexcept(
        noexcept(iter_move(::asc::std::forward<T>(value)))) -> decltype(iter_move(::asc::std::forward<T>(value)))
    {
        return iter_move(::asc::std::forward<T>(value));
    }
};

template <class T>
struct __dispatch<T, false> {
    CANN_ASC_STL_API static constexpr auto call(T&& value) noexcept(noexcept(__deref_move<T&&>::call(
        ::asc::std::forward<T>(value)))) -> decltype(__deref_move<T&&>::call(::asc::std::forward<T>(value)))
    {
        return __deref_move<T&&>::call(::asc::std::forward<T>(value));
    }
};

struct __fn {
    template <class T>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const noexcept(noexcept(__dispatch<T>::call(
        ::asc::std::forward<T>(value)))) -> decltype(__dispatch<T>::call(::asc::std::forward<T>(value)))
    {
        return __dispatch<T>::call(::asc::std::forward<T>(value));  // NOLINT(build/include_what_you_use)
    }
};

}  // namespace __iter_move_detail

inline constexpr __iter_move_detail::__fn iter_move{};

template <class T>
using iter_rvalue_reference_t = decltype(iter_move(::asc::std::declval<T&>()));

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___ITERATOR_ITER_MOVE_H
