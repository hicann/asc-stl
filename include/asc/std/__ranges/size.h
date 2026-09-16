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
#include <asc/std/__concepts/arithmetic.h>
#include <asc/std/__concepts/class_or_enum.h>
#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__ranges/access.h>
#include <asc/std/__type_traits/is_unbounded_array.h>
#include <asc/std/__type_traits/make_signed.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/auto_cast.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace ranges {

template <class>
inline constexpr bool disable_sized_range = false;

namespace __size_detail {

template <class T>
void size(T&) = delete;

template <class T>
CANN_ASC_STL_API constexpr auto __adl_size(T&& value) noexcept(
    noexcept(size(static_cast<T&&>(value)))) -> decltype(size(static_cast<T&&>(value)))
{
    return size(static_cast<T&&>(value));
}

template <class T, class = void>
struct __has_member_size : false_type {};
template <class T>
struct __has_member_size<T, void_t<decltype(::asc::std::declval<T>().size())>> : true_type {};
template <class T, class = void>
struct __has_adl_size : false_type {};
template <class T>
struct __has_adl_size<T, void_t<decltype(__adl_size(::asc::std::declval<T>()))>> : true_type {};

struct __member_tag {};
struct __adl_tag {};
struct __difference_tag {};

template <class T>
using __tag = conditional_t<__has_member_size<T>::value && !disable_sized_range<remove_cvref_t<T>>, __member_tag,
    conditional_t<__has_adl_size<T>::value && !disable_sized_range<remove_cvref_t<T>>, __adl_tag, __difference_tag>>;

struct __fn {
private:
    template <class T>
    CANN_ASC_STL_API static constexpr auto __call(T&& value, __member_tag) noexcept(
        noexcept(value.size())) -> decltype(value.size())
    {
        return value.size();
    }
    template <class T>
    CANN_ASC_STL_API static constexpr auto __call(T&& value, __adl_tag) noexcept(
        noexcept(__adl_size(static_cast<T&&>(value)))) -> decltype(__adl_size(static_cast<T&&>(value)))
    {
        return __adl_size(static_cast<T&&>(value));
    }
    template <class T>
    CANN_ASC_STL_API static constexpr auto __call(T&& value, __difference_tag) noexcept(noexcept(ranges::end(value) -
        ranges::begin(value))) -> make_unsigned_t<decltype(ranges::end(value) - ranges::begin(value))>
    {
        using result_type = make_unsigned_t<decltype(ranges::end(value) - ranges::begin(value))>;
        return static_cast<result_type>(ranges::end(value) - ranges::begin(value));
    }

public:
    template <class T, size_t N>
    CANN_ASC_STL_API constexpr size_t operator()(T (&)[N]) const noexcept
    {
        return N;
    }

    template <class T>
    CANN_ASC_STL_API constexpr auto operator()(T&& value) const
        noexcept(noexcept(__call(static_cast<T&&>(value), __tag<T&&>{})))
    {
        return __call(static_cast<T&&>(value), __tag<T&&>{});
    }
};

}  // namespace __size_detail

inline constexpr __size_detail::__fn size{};
using __size_cpo = __size_detail::__fn;

struct __ssize_fn {
    template <class T>
    CANN_ASC_STL_API constexpr auto operator()(T& value) const
        noexcept(noexcept(size(value))) -> make_signed_t<decltype(size(value))>
    {
        return static_cast<make_signed_t<decltype(size(value))>>(size(value));
    }
};
inline constexpr __ssize_fn ssize{};

}  // namespace ranges

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANGES_SIZE_H
