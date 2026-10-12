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

#ifndef CANN_ASC_STL_ASC_STD___STRING_CHAR_TRAITS_H
#define CANN_ASC_STL_ASC_STD___STRING_CHAR_TRAITS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__cwchar/types.h>
#include <asc/std/__fwd/char_traits.h>
#include <asc/std/__string/constexpr_c_functions.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/cstdint>

// The master tree does not provide the assertion gate used by the source
// implementation: inline its minimal equivalent (same shape as
// __utility/unreachable.h). Device compilation has no assertion mechanism;
// host checks are opt-in via ASC_ENABLE_HOST_ASSERTIONS.
#ifndef CANN_ASC_STL_DETAIL_ASSERT
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || !defined(ASC_ENABLE_HOST_ASSERTIONS)
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    ((expression) ? static_cast<void>(0) : (__builtin_trap(), static_cast<void>(0)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSERT

// Inline equivalent of the source tree three-way-comparison gate: the
// comparison_category member stays disabled until the ordering vocabulary
// (asc::std::strong_ordering from __compare/ordering.h) is wired into this
// header, mirroring the source-tree default of 0.
#ifndef CANN_ASC_STL_DETAIL_HAS_SPACESHIP_OPERATOR
#define CANN_ASC_STL_DETAIL_HAS_SPACESHIP_OPERATOR() 0
#endif  // CANN_ASC_STL_DETAIL_HAS_SPACESHIP_OPERATOR

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _CharT, class _IntT, _IntT _EOFVal = _IntT(-1) /*todo: remove default argument*/>
struct __asc_char_traits_impl {
    using char_type = _CharT;
    using int_type = _IntT;
#if CANN_ASC_STL_DETAIL_HAS_SPACESHIP_OPERATOR()
    // Requires asc::std::strong_ordering (__compare/ordering.h).
    using comparison_category = strong_ordering;
#endif  // CANN_ASC_STL_DETAIL_HAS_SPACESHIP_OPERATOR()

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
        return ::asc::std::__asc_memcmp(__lhs, __rhs, __count);
    }

    [[nodiscard]] CANN_ASC_STL_API static constexpr size_t length(const char_type* __s) noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(__s != nullptr, "char_traits::length: nullptr passed as an argument");
        return ::asc::std::__asc_strlen(__s);
    }

    [[nodiscard]] CANN_ASC_STL_API static constexpr const char_type* find(
        const char_type* __s, size_t __n, const char_type& __a) noexcept
    {
        if (__n > 0) {
            CANN_ASC_STL_DETAIL_ASSERT(__s != nullptr, "char_traits::find: nullptr passed as an argument");
        }
        return ::asc::std::__asc_memchr<const char_type>(__s, __a, __n);
    }

    CANN_ASC_STL_API static constexpr char_type* move(  // NOLINT(build/include_what_you_use)
        char_type* __s1, const char_type* __s2, size_t __n) noexcept
    {
        if (__n > 0) {
            CANN_ASC_STL_DETAIL_ASSERT(__s1 != nullptr, "char_traits::move: destination pointer is null");
            CANN_ASC_STL_DETAIL_ASSERT(__s2 != nullptr, "char_traits::move: source pointer is null");
        }
        return ::asc::std::__asc_memmove(__s1, __s2, __n);  // NOLINT(build/include_what_you_use)
    }

    CANN_ASC_STL_API static constexpr char_type* copy(  // NOLINT(build/include_what_you_use)
        char_type* __s1, const char_type* __s2, size_t __n) noexcept
    {
        if (__n > 0) {
            CANN_ASC_STL_DETAIL_ASSERT(__s1 != nullptr, "char_traits::copy: destination pointer is null");
            CANN_ASC_STL_DETAIL_ASSERT(__s2 != nullptr, "char_traits::copy: source pointer is null");
        }
        return ::asc::std::__asc_memcpy(__s1, __s2, __n);
    }

    CANN_ASC_STL_API static constexpr char_type* assign(char_type* __s, size_t __n, char_type __a) noexcept
    {
        if (__n > 0) {
            CANN_ASC_STL_DETAIL_ASSERT(__s != nullptr, "char_traits::assign: destination pointer is null");
        }
        return ::asc::std::__asc_memset(__s, __a, __n);
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
struct char_traits<char> : __asc_char_traits_impl<char, int /*, EOF*/> {};

#if CANN_ASC_STL_DETAIL_HAS_CHAR8_T()
template <>
struct char_traits<char8_t> : __asc_char_traits_impl<char8_t, unsigned /*, ??? */> {};
#endif  // CANN_ASC_STL_DETAIL_HAS_CHAR8_T()

template <>
struct char_traits<char16_t> : __asc_char_traits_impl<char16_t, uint_least16_t /*, ??? */> {};

template <>
struct char_traits<char32_t> : __asc_char_traits_impl<char32_t, uint_least32_t /*, ??? */> {};

// Kept unconditional: __fwd/char_traits.h forward-declares this specialization
// unconditionally, so the definition must exist in every dialect. The int_type
// is wint_t, matching the wide-character EOF domain (WEOF).
template <>
struct char_traits<wchar_t>  // NOLINT(build/include_what_you_use)
    : __asc_char_traits_impl<wchar_t, wint_t /*, WEOF*/> {};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___STRING_CHAR_TRAITS_H
