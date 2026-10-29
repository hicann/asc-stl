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

#ifndef CANN_ASC_STL_ASC_STD___COMPARE_ORDERING_H
#define CANN_ASC_STL_ASC_STD___COMPARE_ORDERING_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

class partial_ordering {
public:
    static const partial_ordering less;
    static const partial_ordering equivalent;
    static const partial_ordering greater;
    static const partial_ordering unordered;
    CANN_ASC_STL_API constexpr explicit partial_ordering(signed char value) noexcept : value_(value)
    {}
    CANN_ASC_STL_API constexpr signed char value() const noexcept
    {
        return value_;
    }

private:
    constexpr partial_ordering(signed char value, bool) noexcept : value_(value)
    {}
    signed char value_{};
};

class weak_ordering {
public:
    static const weak_ordering less;
    static const weak_ordering equivalent;
    static const weak_ordering greater;
    CANN_ASC_STL_API constexpr explicit weak_ordering(signed char value) noexcept : value_(value)
    {}
    CANN_ASC_STL_API constexpr operator partial_ordering() const noexcept
    {
        return partial_ordering{value_};
    }
    CANN_ASC_STL_API constexpr signed char value() const noexcept
    {
        return value_;
    }

private:
    constexpr weak_ordering(signed char value, bool) noexcept : value_(value)
    {}
    signed char value_{};
};

class strong_ordering {
public:
    static const strong_ordering less;
    static const strong_ordering equal;
    static const strong_ordering equivalent;
    static const strong_ordering greater;
    CANN_ASC_STL_API constexpr explicit strong_ordering(signed char value) noexcept : value_(value)
    {}
    CANN_ASC_STL_API constexpr operator weak_ordering() const noexcept
    {
        return weak_ordering{value_};
    }
    CANN_ASC_STL_API constexpr operator partial_ordering() const noexcept
    {
        return partial_ordering{value_};
    }
    CANN_ASC_STL_API constexpr signed char value() const noexcept
    {
        return value_;
    }

private:
    constexpr strong_ordering(signed char value, bool) noexcept : value_(value)
    {}
    signed char value_{};
};

inline constexpr partial_ordering partial_ordering::less{-1, false};
inline constexpr partial_ordering partial_ordering::equivalent{0, false};
inline constexpr partial_ordering partial_ordering::greater{1, false};
inline constexpr partial_ordering partial_ordering::unordered{2, false};
inline constexpr weak_ordering weak_ordering::less{-1, false};
inline constexpr weak_ordering weak_ordering::equivalent{0, false};
inline constexpr weak_ordering weak_ordering::greater{1, false};
inline constexpr strong_ordering strong_ordering::less{-1, false};
inline constexpr strong_ordering strong_ordering::equal{0, false};
inline constexpr strong_ordering strong_ordering::equivalent{0, false};
inline constexpr strong_ordering strong_ordering::greater{1, false};

#define CANN_ASC_STL_DETAIL_ORDERING_OPERATORS(type)                           \
    CANN_ASC_STL_API constexpr bool operator==(type left, type right) noexcept \
    {                                                                          \
        return left.value() == right.value();                                  \
    }                                                                          \
    CANN_ASC_STL_API constexpr bool operator!=(type left, type right) noexcept \
    {                                                                          \
        return !(left == right);                                               \
    }                                                                          \
    CANN_ASC_STL_API constexpr bool operator==(type value, void*) noexcept     \
    {                                                                          \
        return value.value() == 0;                                             \
    }                                                                          \
    CANN_ASC_STL_API constexpr bool operator==(void*, type value) noexcept     \
    {                                                                          \
        return value == nullptr;                                               \
    }                                                                          \
    CANN_ASC_STL_API constexpr bool operator!=(type value, void*) noexcept     \
    {                                                                          \
        return value.value() != 0;                                             \
    }                                                                          \
    CANN_ASC_STL_API constexpr bool operator!=(void*, type value) noexcept     \
    {                                                                          \
        return value != nullptr;                                               \
    }

CANN_ASC_STL_DETAIL_ORDERING_OPERATORS(partial_ordering)
CANN_ASC_STL_DETAIL_ORDERING_OPERATORS(weak_ordering)
CANN_ASC_STL_DETAIL_ORDERING_OPERATORS(strong_ordering)

#undef CANN_ASC_STL_DETAIL_ORDERING_OPERATORS

#define CANN_ASC_STL_DETAIL_TOTAL_ORDERING_ZERO_OPERATORS(type)            \
    CANN_ASC_STL_API constexpr bool operator<(type value, void*) noexcept  \
    {                                                                      \
        return value.value() < 0;                                          \
    }                                                                      \
    CANN_ASC_STL_API constexpr bool operator<(void*, type value) noexcept  \
    {                                                                      \
        return value.value() > 0;                                          \
    }                                                                      \
    CANN_ASC_STL_API constexpr bool operator>(type value, void*) noexcept  \
    {                                                                      \
        return value.value() > 0;                                          \
    }                                                                      \
    CANN_ASC_STL_API constexpr bool operator>(void*, type value) noexcept  \
    {                                                                      \
        return value.value() < 0;                                          \
    }                                                                      \
    CANN_ASC_STL_API constexpr bool operator<=(type value, void*) noexcept \
    {                                                                      \
        return value.value() <= 0;                                         \
    }                                                                      \
    CANN_ASC_STL_API constexpr bool operator<=(void*, type value) noexcept \
    {                                                                      \
        return value.value() >= 0;                                         \
    }                                                                      \
    CANN_ASC_STL_API constexpr bool operator>=(type value, void*) noexcept \
    {                                                                      \
        return value.value() >= 0;                                         \
    }                                                                      \
    CANN_ASC_STL_API constexpr bool operator>=(void*, type value) noexcept \
    {                                                                      \
        return value.value() <= 0;                                         \
    }

CANN_ASC_STL_DETAIL_TOTAL_ORDERING_ZERO_OPERATORS(weak_ordering)
CANN_ASC_STL_DETAIL_TOTAL_ORDERING_ZERO_OPERATORS(strong_ordering)

#undef CANN_ASC_STL_DETAIL_TOTAL_ORDERING_ZERO_OPERATORS

CANN_ASC_STL_API constexpr bool operator<(partial_ordering value, void*) noexcept
{
    return value.value() == -1;
}
CANN_ASC_STL_API constexpr bool operator<(void*, partial_ordering value) noexcept
{
    return value.value() == 1;
}
CANN_ASC_STL_API constexpr bool operator>(partial_ordering value, void*) noexcept
{
    return value.value() == 1;
}
CANN_ASC_STL_API constexpr bool operator>(void*, partial_ordering value) noexcept
{
    return value.value() == -1;
}
CANN_ASC_STL_API constexpr bool operator<=(partial_ordering value, void*) noexcept
{
    return value.value() == -1 || value.value() == 0;
}
CANN_ASC_STL_API constexpr bool operator<=(void*, partial_ordering value) noexcept
{
    return value.value() == 0 || value.value() == 1;
}
CANN_ASC_STL_API constexpr bool operator>=(partial_ordering value, void*) noexcept
{
    return value.value() == 0 || value.value() == 1;
}
CANN_ASC_STL_API constexpr bool operator>=(void*, partial_ordering value) noexcept
{
    return value.value() == -1 || value.value() == 0;
}

CANN_ASC_STL_API constexpr bool is_eq(partial_ordering value) noexcept
{
    return value == 0;
}

CANN_ASC_STL_API constexpr bool is_neq(partial_ordering value) noexcept
{
    return value != 0;
}

CANN_ASC_STL_API constexpr bool is_lt(partial_ordering value) noexcept
{
    return value < 0;
}

CANN_ASC_STL_API constexpr bool is_lteq(partial_ordering value) noexcept
{
    return value <= 0;
}

CANN_ASC_STL_API constexpr bool is_gt(partial_ordering value) noexcept
{
    return value > 0;
}

CANN_ASC_STL_API constexpr bool is_gteq(partial_ordering value) noexcept
{
    return value >= 0;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPARE_ORDERING_H
