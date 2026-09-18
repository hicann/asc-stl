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

#ifndef CANN_ASC_STL_STD_DETAIL_STRING_STRING_VIEW_H
#define CANN_ASC_STL_STD_DETAIL_STRING_STRING_VIEW_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__exception/exception_macros.h>
#include <asc/std/__host_stdlib/stdexcept>
#include <asc/std/__string/char_traits.h>
#include <asc/std/__type_traits/is_constant_evaluated.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

struct __string_view {
    CANN_ASC_STL_API constexpr __string_view(char const* __str, size_t __len) noexcept : __str_(__str), __len_(__len)
    {}

    CANN_ASC_STL_API constexpr explicit __string_view(char const* __str) noexcept
        : __str_(__str), __len_(__strlen_(__str))
    {}

    [[nodiscard]] CANN_ASC_STL_API constexpr size_t size() const noexcept
    {
        return __len_;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr char const* data() const noexcept
    {
        return __str_;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr char const* begin() const noexcept
    {
        return __str_;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr char const* end() const noexcept
    {
        return __str_ + __len_;
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr char const& operator[](ptrdiff_t __n) const noexcept
    {
        return __str_[__n];
    }

    [[nodiscard]] CANN_ASC_STL_API constexpr __string_view substr(ptrdiff_t __start, ptrdiff_t __stop) const
    {
        return __string_view(__str_ + __check_offset(__start, __len_), __check_offset(__stop - __start, __len_));
    }

private:
    [[nodiscard]] CANN_ASC_STL_API static constexpr int __compare_(
        char const* __s1, size_t __len1, char const* __s2, size_t __len2, size_t __n) noexcept
    {
        // NOLINTNEXTLINE(readability/casting)
        int __result = int(__len1) - int(__len2);
        if (__n) {
            for (;; ++__s1, ++__s2) {
                if (*__s1 < *__s2) {
                    __result = -1;
                    break;
                }
                if (*__s2 < *__s1) {
                    __result = 1;
                    break;
                }
                if (0 == --__n) {
                    break;
                }
            }
        }
        return __result;
    }

    template <bool _Forward>
    [[nodiscard]] CANN_ASC_STL_API static constexpr ptrdiff_t __find(
        const char* __needle, size_t __needle_size, const char* __haystack_begin, const char* __haystack_end) noexcept
    {
        ptrdiff_t __result = -1;
        char const* __it = __haystack_begin;
        for (; __it != __haystack_end; (_Forward ? ++__it : --__it)) {
            size_t __i = 0;
            for (; __i != __needle_size; ++__i) {
                if ((_Forward ? __it : __it - 1)[__i] != __needle[__i]) {
                    break;
                }
            }
            if (__i == __needle_size) {
                __result = _Forward ? __it - __haystack_begin : __it - __haystack_end - 1;
                break;
            }
        }
        return __result;
    }

public:
    template <size_t _Np>
    [[nodiscard]] CANN_ASC_STL_API constexpr ptrdiff_t find(const char (&__other)[_Np]) const noexcept
    {
        return ((_Np - 1) > __len_) ? -1 : __find<true>(__other, _Np - 1, __str_, __str_ + __len_ - (_Np - 1) + 1);
    }

    template <size_t _Np>
    [[nodiscard]] CANN_ASC_STL_API constexpr ptrdiff_t find_end(const char (&__other)[_Np]) const noexcept
    {
        return ((_Np - 1) > __len_) ? -1 : __find<false>(__other, _Np - 1, __str_ + __len_ - (_Np - 1) + 1, __str_);
    }

private:
    // This overload is selected when we're not in a constant evaluated context.
    // Compare the two strings' addresses as a shortcut, and fall back to a string
    // comparison it they are not equal.
    [[nodiscard]] CANN_ASC_STL_API int __compare(__string_view const& __other, false_type) const noexcept
    {
        return __str_ == __other.__str_ ?
            // NOLINTNEXTLINE(readability/casting)
            int(__len_) - int(__other.__len_) :
            __compare_(__str_, __len_, __other.__str_, __other.__len_, (__min_)(__len_, __other.__len_));
    }

    // This overload is selected when we're in a constant evaluated context. We
    // cannot compare the two strings' addresses so fall back to a string
    // comparison.
    [[nodiscard]] CANN_ASC_STL_API constexpr int __compare(__string_view const& __other, true_type) const noexcept
    {
        return __compare_(__str_, __len_, __other.__str_, __other.__len_, (__min_)(__len_, __other.__len_));
    }

public:
    [[nodiscard]] CANN_ASC_STL_API constexpr int compare(__string_view const& __other) const noexcept
    {
        // If we're in a constant evaluated context, we cannot compare the __str_
        // members for equality.
        return __compare(__other, bool_constant<__accl_default_is_constant_evaluated()>());
    }

    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator==(
        __string_view const& __lhs, __string_view const& __rhs) noexcept
    {
        return __lhs.__len_ == __rhs.__len_ && __lhs.compare(__rhs) == 0;
    }

    [[nodiscard]]
    CANN_ASC_STL_API friend constexpr bool operator!=(__string_view const& __lhs, __string_view const& __rhs) noexcept
    {
        return !(__lhs == __rhs);
    }

    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator<(
        __string_view const& __lhs, __string_view const& __rhs) noexcept
    {
        return __lhs.compare(__rhs) < 0;
    }

    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator<=(
        __string_view const& __lhs, __string_view const& __rhs) noexcept
    {
        return __lhs.compare(__rhs) <= 0;
    }

    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator>(
        __string_view const& __lhs, __string_view const& __rhs) noexcept
    {
        return __lhs.compare(__rhs) > 0;
    }

    [[nodiscard]] CANN_ASC_STL_API friend constexpr bool operator>=(
        __string_view const& __lhs, __string_view const& __rhs) noexcept
    {
        return __lhs.compare(__rhs) >= 0;
    }

private:
    [[nodiscard]] CANN_ASC_STL_API static constexpr size_t __min_(size_t __x, size_t __y) noexcept
    {
        return __x < __y ? __x : __y;
    }

    [[nodiscard]] CANN_ASC_STL_API static constexpr size_t __strlen_(char const* __str) noexcept
    {
        return ::asc::std::char_traits<char>::length(__str);
    }

    [[nodiscard]] CANN_ASC_STL_API static constexpr size_t __check_offset(ptrdiff_t __diff, size_t __len)
    {
        if (__diff < 0 || static_cast<size_t>(__diff) > __len) {
            CANN_ASC_STL_DETAIL_ACCL_THROW(::std::out_of_range, "__string_view index out of range");
        }
        return static_cast<size_t>(__diff);
    }

    char const* __str_;
    size_t __len_;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_STRING_STRING_VIEW_H
