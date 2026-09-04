/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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
#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__ranges/enable_borrowed_range.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_reference.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/auto_cast.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

namespace __access_detail {

template <class T>
void begin(T&) = delete;
template <class T>
void end(T&) = delete;

template <class T>
CANN_ASC_STL_API constexpr auto __adl_begin(T&& value) noexcept(
    noexcept(begin(static_cast<T&&>(value)))) -> decltype(begin(static_cast<T&&>(value)))
{
    return begin(static_cast<T&&>(value));
}
template <class T>
CANN_ASC_STL_API constexpr auto __adl_end(T&& value) noexcept(
    noexcept(end(static_cast<T&&>(value)))) -> decltype(end(static_cast<T&&>(value)))
{
    return end(static_cast<T&&>(value));
}

template <class T>
inline constexpr bool __can_borrow = is_lvalue_reference_v<T> || enable_borrowed_range<remove_cvref_t<T>>;

template <class T, class = void>
struct __has_member_begin : false_type {};
template <class T>
struct __has_member_begin<T, void_t<decltype(::asc::std::declval<T>().begin())>> : true_type {};
template <class T, class = void>
struct __has_member_end : false_type {};
template <class T>
struct __has_member_end<T, void_t<decltype(::asc::std::declval<T>().end())>> : true_type {};

struct __begin_fn {
    template <class T, size_t N>
    CANN_ASC_STL_API constexpr T* operator()(T (&array)[N]) const noexcept
    {
        return array;
    }
    template <class T, enable_if_t<__can_borrow<T&&> && __has_member_begin<T&&>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(static_cast<T&&>(value).begin())) -> decltype(static_cast<T&&>(value).begin())
    {
        return static_cast<T&&>(value).begin();
    }
    template <class T, enable_if_t<__can_borrow<T&&> && !__has_member_begin<T&&>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(__adl_begin(static_cast<T&&>(value)))) -> decltype(__adl_begin(static_cast<T&&>(value)))
    {
        return __adl_begin(static_cast<T&&>(value));
    }
};

struct __end_fn {
    template <class T, size_t N>
    CANN_ASC_STL_API constexpr T* operator()(T (&array)[N]) const noexcept
    {
        return array + N;
    }
    template <class T, enable_if_t<__can_borrow<T&&> && __has_member_end<T&&>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(static_cast<T&&>(value).end())) -> decltype(static_cast<T&&>(value).end())
    {
        return static_cast<T&&>(value).end();
    }
    template <class T, enable_if_t<__can_borrow<T&&> && !__has_member_end<T&&>::value, int> = 0>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(__adl_end(static_cast<T&&>(value)))) -> decltype(__adl_end(static_cast<T&&>(value)))
    {
        return __adl_end(static_cast<T&&>(value));
    }
};

}  // namespace __access_detail

inline constexpr __access_detail::__begin_fn begin{};
inline constexpr __access_detail::__end_fn end{};
using __begin_cpo = __access_detail::__begin_fn;
using __end_cpo = __access_detail::__end_fn;

template <class T>
using iterator_t = decltype(begin(::asc::std::declval<T&>()));

struct __cbegin_fn {
    template <class T>
    CANN_ASC_STL_API constexpr auto operator()(T& value) const
        noexcept(noexcept(begin(static_cast<const T&>(value)))) -> decltype(begin(static_cast<const T&>(value)))
    {
        return begin(static_cast<const T&>(value));
    }
    template <class T>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(begin(static_cast<const T&&>(value)))) -> decltype(begin(static_cast<const T&&>(value)))
    {
        return begin(static_cast<const T&&>(value));
    }
};
struct __cend_fn {
    template <class T>
    CANN_ASC_STL_API constexpr auto operator()(T& value) const
        noexcept(noexcept(end(static_cast<const T&>(value)))) -> decltype(end(static_cast<const T&>(value)))
    {
        return end(static_cast<const T&>(value));
    }
    template <class T>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(end(static_cast<const T&&>(value)))) -> decltype(end(static_cast<const T&&>(value)))
    {
        return end(static_cast<const T&&>(value));
    }
};
inline constexpr __cbegin_fn cbegin{};
inline constexpr __cend_fn cend{};

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_ACCESS_H
