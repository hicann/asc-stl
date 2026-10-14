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

#ifndef CANN_ASC_STL_ASC_STD___BIT_BYTESWAP_H
#define CANN_ASC_STL_ASC_STD___BIT_BYTESWAP_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/make_nbit_int.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/cstdint>
#include <asc/std/limits>

// On CANN 9.2 real hardware (aicore) __builtin_bswap yields correct values,
// but the CANN 9.0.0 dav vector-core (aiv) backend cannot select a runtime
// bswap of any width (16/32/64 all fail with "Cannot select", except on the
// constant-folding path). The builtins are therefore host-TU only; device TUs
// always take the portable shift loop (verified on hardware).
#if defined(__has_builtin) && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#if __has_builtin(__builtin_bswap16)
#define CANN_ASC_STL_BUILTIN_BSWAP16(__v) __builtin_bswap16(__v)
#endif
#if __has_builtin(__builtin_bswap32)
#define CANN_ASC_STL_BUILTIN_BSWAP32(__v) __builtin_bswap32(__v)
#endif
#endif  // __has_builtin

// The shared <asc/__config> does not provide CANN_ASC_STL_DETAIL_HAS_INT128 /
// PRAGMA_UNROLL_FULL: inline minimal equivalents of their semantics, guarded
// by #ifndef so a future centralized definition wins.
#ifndef CANN_ASC_STL_DETAIL_HAS_INT128
#if !defined(ASC_DISABLE_INT128_SUPPORT) && defined(__linux__) && defined(__SIZEOF_INT128__)
#define CANN_ASC_STL_DETAIL_HAS_INT128() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_INT128() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_INT128
#ifndef CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || defined(__clang__)
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL() _Pragma("unroll")
#elif defined(__GNUC__) && __GNUC__ >= 8
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL() _Pragma("GCC unroll 65534")
#else
#define CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL()
#endif
#endif  // CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
struct __byteswap_allowed {
    static constexpr bool value = is_integral_v<T>;
};
template <>
struct __byteswap_allowed<bool> {
    static constexpr bool value = false;
};

//! @brief Generic byte-order swap fallback: rebuilds the value with a per-byte
//! shift loop (constexpr, any width).
template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp __byteswap_generic(_Tp __val) noexcept
{
    constexpr auto __shift = numeric_limits<uint8_t>::digits;
    _Tp __result{};
    CANN_ASC_STL_DETAIL_PRAGMA_UNROLL_FULL()
    for (__SIZE_TYPE__ __index = 0; __index < sizeof(_Tp); ++__index) {
        __result <<= __shift;
        __result |= _Tp(__val & _Tp(numeric_limits<uint8_t>::max()));  // NOLINT(build/include_what_you_use)
        __val >>= __shift;
    }
    return __result;
}

[[nodiscard]] CANN_ASC_STL_API constexpr uint16_t __byteswap_impl(uint16_t __val) noexcept
{
#if defined(CANN_ASC_STL_BUILTIN_BSWAP16)
    return CANN_ASC_STL_BUILTIN_BSWAP16(__val);
#else
    return ::asc::std::__byteswap_generic(__val);
#endif
}

[[nodiscard]] CANN_ASC_STL_API constexpr uint32_t __byteswap_impl(uint32_t __val) noexcept
{
#if defined(CANN_ASC_STL_BUILTIN_BSWAP32)
    return CANN_ASC_STL_BUILTIN_BSWAP32(__val);
#else
    return ::asc::std::__byteswap_generic(__val);
#endif
}

[[nodiscard]] CANN_ASC_STL_API constexpr uint64_t __byteswap_impl(uint64_t __val) noexcept
{
#if defined(CANN_ASC_STL_BUILTIN_BSWAP32)
    // Host: two 32-bit builtin swaps plus a half-word swap (avoids version
    // differences in 64-bit builtin support)
    const uint32_t __lo = static_cast<uint32_t>(__val);
    const uint32_t __hi = static_cast<uint32_t>(__val >> 32);
    return (static_cast<uint64_t>(CANN_ASC_STL_BUILTIN_BSWAP32(__lo)) << 32) |
        static_cast<uint64_t>(CANN_ASC_STL_BUILTIN_BSWAP32(__hi));
#else
    // Device: portable shift loop (the aiv backend has no scalar bswap)
    return ::asc::std::__byteswap_generic(__val);
#endif
}

#if CANN_ASC_STL_DETAIL_HAS_INT128()
[[nodiscard]] CANN_ASC_STL_API constexpr __uint128_t __byteswap_impl(__uint128_t __val) noexcept
{
    // CCE has no bswap128 builtin: decompose into two already-verified 64-bit
    // swaps (the base numeric_limits has no int128 specialization; the swapped
    // high half lands in the low position and vice versa)
    constexpr int __shift = 64;
    return static_cast<__uint128_t>(::asc::std::__byteswap_impl(static_cast<uint64_t>(__val >> __shift))) |
        (static_cast<__uint128_t>(::asc::std::__byteswap_impl(static_cast<uint64_t>(__val))) << __shift);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_INT128()

//! @brief Reverses the byte order of @p value (per-byte reversal of the object
//! representation); single-byte types are the identity, and bool and
//! non-integral types do not participate (bool is explicitly excluded).
template <class Integer>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr Integer byteswap(Integer value) noexcept
{
    static_assert(__byteswap_allowed<Integer>::value, "byteswap requires a non-bool integral type");
    if constexpr (!__byteswap_allowed<Integer>::value || sizeof(Integer) == 1) {
        return value;
    } else if constexpr (sizeof(Integer) == 2) {
        return static_cast<Integer>(
            ::asc::std::__byteswap_impl(static_cast<uint16_t>(::asc::std::__to_unsigned_like(value))));
    } else if constexpr (sizeof(Integer) == 4) {
        return static_cast<Integer>(
            ::asc::std::__byteswap_impl(static_cast<uint32_t>(::asc::std::__to_unsigned_like(value))));
    } else if constexpr (sizeof(Integer) == 8) {
        return static_cast<Integer>(
            ::asc::std::__byteswap_impl(static_cast<uint64_t>(::asc::std::__to_unsigned_like(value))));
    } else {
        return static_cast<Integer>(
            ::asc::std::__byteswap_impl(static_cast<__uint128_t>(::asc::std::__to_unsigned_like(value))));
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___BIT_BYTESWAP_H
