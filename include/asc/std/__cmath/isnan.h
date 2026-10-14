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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_ISNAN_H
#define CANN_ASC_STL_ASC_STD___CMATH_ISNAN_H

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
#include <asc/std/__bit/bit_cast.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/cstdint>

// Inline definition of the CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() gate (the
// config does not provide it): long double is host-only — AI-core compilation
// does not support long double.
#if !defined(CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE)
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && !defined(ASC_DISABLE_LONG_DOUBLE_SUPPORT)
#define CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE

// Inline definition of the CANN_ASC_STL_DETAIL_HAS_FLOAT128() gate: __float128
// needs __int128, a Linux non-ARM64 target, a compiler that advertises the type,
// host compilation only, and GCC must not run strict-ANSI without extended
// numeric literals.
#if !defined(CANN_ASC_STL_DETAIL_HAS_FLOAT128)
#define CANN_ASC_STL_DETAIL_HAS_FLOAT128() 0
#if (defined(__SIZEOF_FLOAT128__) || defined(__FLOAT128__)) && defined(__SIZEOF_INT128__) &&                         \
    (defined(__linux__) || defined(__LP64__)) &&                                                                     \
    !(defined(__aarch64__) || defined(_M_ARM64) || defined(_M_ARM64EC)) && !defined(ASC_DISABLE_FLOAT128_SUPPORT) && \
    !defined(ASC_DISABLE_INT128_SUPPORT) && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() &&                             \
    !(defined(__GNUC__) && !defined(__clang__) && defined(__STRICT_ANSI__) &&                                        \
        !defined(ASC_GCC_HAS_EXTENDED_NUMERIC_LITERALS))
#undef CANN_ASC_STL_DETAIL_HAS_FLOAT128
#define CANN_ASC_STL_DETAIL_HAS_FLOAT128() 1
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_FLOAT128

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Tp>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool __isnan_impl(Tp x) noexcept
{
    static_assert(is_floating_point_v<Tp>, "Only standard floating-point types are supported");
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    if constexpr (sizeof(Tp) == sizeof(uint32_t)) {
        const auto bits = ::asc::std::bit_cast<uint32_t>(x);
        return (bits & uint32_t{0x7fffffffu}) > uint32_t{0x7f800000u};
    } else {
        const auto bits = ::asc::std::bit_cast<uint64_t>(x);
        return (bits & uint64_t{0x7fffffffffffffffull}) > uint64_t{0x7ff0000000000000ull};
    }
#else
    return x != x;
#endif
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isnan(float x) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    return __builtin_isnan(x);
#else
    return ::asc::std::__isnan_impl(x);
#endif
}

CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isnan(double x) noexcept
{
    return ::asc::std::__isnan_impl(x);
}

#if CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isnan(long double x) noexcept
{
    return ::asc::std::__isnan_impl(x);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_LONG_DOUBLE()

#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isnan(__float128 x) noexcept
{
    return x != x;
}
#endif  // CANN_ASC_STL_DETAIL_HAS_FLOAT128()

template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isnan(Tp x) noexcept
{
    return ::asc::std::isnan(static_cast<float>(x));
}

template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool isnan(Tp) noexcept
{
    return false;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_ISNAN_H
