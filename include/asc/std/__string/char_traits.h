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

#ifndef CANN_ASC_STL_STD_DETAIL_STRING_CHAR_TRAITS_H
#define CANN_ASC_STL_STD_DETAIL_STRING_CHAR_TRAITS_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__cstddef/types.h>
#include <asc/std/__fwd/char_traits.h>
#include <asc/std/__string/constexpr_c_functions.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/cstdint>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _CharT, class _IntT, _IntT _EOFVal = _IntT(-1) /*todo: remove default argument*/>
struct __accl_char_traits_impl {
    using char_type = _CharT;
    using int_type = _IntT;
#if 0  // todo: add stream support
  using off_type            = streamoff;
  using pos_type            = fpos<mbstate_t>;
  using state_type          = mbstate_t;
#endif
#if CANN_ASC_STL_DETAIL_ACCL_HAS_SPACESHIP_OPERATOR()
    using comparison_category = strong_ordering;
#endif  // CANN_ASC_STL_DETAIL_ACCL_HAS_SPACESHIP_OPERATOR()

    CANN_ASC_STL_API static constexpr void assign(char_type& __lhs, const char_type& __rhs) noexcept
    {
        __lhs = __rhs;
    }

    [[nodiscard]] CANN_ASC_STL_API static constexpr bool eq(char_type __lhs, char_type __rhs) noexcept
    {
        return __lhs == __rhs;
    }

    [[nodiscard]] CANN_ASC_STL_API static constexpr bool lt(char_type __lhs, char_type __rhs) noexcept
    {
        if constexpr (is_same_v<char_type, char>) {
            return static_cast<unsigned char>(__lhs) < static_cast<unsigned char>(__rhs);
        } else {
            return __lhs < __rhs;
        }
    }

    [[nodiscard]] CANN_ASC_STL_API static constexpr int compare(
        const char_type* __lhs, const char_type* __rhs, size_t __count) noexcept
    {
        if (__count > 0) {
            CANN_ASC_STL_DETAIL_ASSERT(__lhs != nullptr, "char_traits::compare: lhs pointer is null");
            CANN_ASC_STL_DETAIL_ASSERT(__rhs != nullptr, "char_traits::compare: rhs pointer is null");
        }
        return ::asc::std::__accl_memcmp(__lhs, __rhs, __count);
    }

    [[nodiscard]] CANN_ASC_STL_API static constexpr size_t length(const char_type* __s) noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(__s != nullptr, "char_traits::length: nullptr passed as an argument");
        return ::asc::std::__accl_strlen(__s);
    }

    [[nodiscard]] CANN_ASC_STL_API static constexpr const char_type* find(
        const char_type* __s, size_t __n, const char_type& __a) noexcept
    {
        if (__n > 0) {
            CANN_ASC_STL_DETAIL_ASSERT(__s != nullptr, "char_traits::find: nullptr passed as an argument");
        }
        return ::asc::std::__accl_memchr<const char_type>(__s, __a, __n);
    }

    CANN_ASC_STL_API static constexpr char_type* move(
        char_type* __s1, const char_type* __s2, size_t __n) noexcept  // NOLINT(build/include_what_you_use)
    {
        if (__n > 0) {
            CANN_ASC_STL_DETAIL_ASSERT(__s1 != nullptr, "char_traits::move: destination pointer is null");
            CANN_ASC_STL_DETAIL_ASSERT(__s2 != nullptr, "char_traits::move: source pointer is null");
        }
        return ::asc::std::__accl_memmove(__s1, __s2, __n);
    }

    CANN_ASC_STL_API static constexpr char_type* copy(
        char_type* __s1, const char_type* __s2, size_t __n) noexcept  // NOLINT(build/include_what_you_use)
    {
        if (__n > 0) {
            CANN_ASC_STL_DETAIL_ASSERT(__s1 != nullptr, "char_traits::copy: destination pointer is null");
            CANN_ASC_STL_DETAIL_ASSERT(__s2 != nullptr, "char_traits::copy: source pointer is null");
        }
        return ::asc::std::__accl_memcpy(__s1, __s2, __n);
    }

    CANN_ASC_STL_API static constexpr char_type* assign(char_type* __s, size_t __n, char_type __a) noexcept
    {
        if (__n > 0) {
            CANN_ASC_STL_DETAIL_ASSERT(__s != nullptr, "char_traits::assign: destination pointer is null");
        }
        return ::asc::std::__accl_memset(__s, __a, __n);
    }

    [[nodiscard]] CANN_ASC_STL_API static constexpr char_type to_char_type(int_type __c) noexcept
    {
        return char_type(__c);
    }

    [[nodiscard]] CANN_ASC_STL_API static constexpr int_type to_int_type(char_type __c) noexcept
    {
        if constexpr (is_same_v<char_type, char>) {
            return int_type(static_cast<unsigned char>(__c));
        } else {
            return int_type(__c);
        }
    }

    [[nodiscard]] CANN_ASC_STL_API static constexpr bool eq_int_type(int_type __lhs, int_type __rhs) noexcept
    {
        return __lhs == __rhs;
    }

#if 0  // todo: add EOF support
  [[nodiscard]] CANN_ASC_STL_API static constexpr int_type eof() noexcept
  {
    return _EOFVal;
  }

  [[nodiscard]] CANN_ASC_STL_API static constexpr int_type not_eof(int_type __c) noexcept
  {
    return eq_int_type(__c, eof()) ? static_cast<int_type>(~eof()) : __c;
  }
#endif
};

template <>
struct char_traits<char> : __accl_char_traits_impl<char, int /*, EOF*/> {};

#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
template <>
struct char_traits<char8_t> : __accl_char_traits_impl<char8_t, unsigned /*, ?? */> {};
#endif  // CANN_ASC_STL_DETAIL_HAS_CHAR8_T()

template <>
struct char_traits<char16_t> : __accl_char_traits_impl<char16_t, uint_least16_t /*, ?? */> {};

template <>
struct char_traits<char32_t> : __accl_char_traits_impl<char32_t, uint_least32_t /*, ?? */> {};

#if CANN_ASC_STL_DETAIL_HAS_WCHAR_T()
template <>
struct char_traits<wchar_t>                                  // NOLINT(build/include_what_you_use)
    : __accl_char_traits_impl<wchar_t, wint_t /*, WEOF*/> {  // NOLINT(build/include_what_you_use)
};  // NOLINT(build/include_what_you_use)
#endif  // CANN_ASC_STL_DETAIL_HAS_WCHAR_T()

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_STRING_CHAR_TRAITS_H
