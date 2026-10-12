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

// 2026-09-01 晟腾 950 真机实验：CANN 9.2 真机（aicore）上 __builtin_bswap
// 数值正确，但 CANN 9.0.0 的 dav 向量核（aiv）后端对任何宽度的运行时
// bswap 均无法 select（16/32/64 全部 Cannot select，常量折叠路径除外）。
// 故 builtin 仅用于宿主 TU；设备 TU 一律走可移植移位循环（真机已验）。
// 源侧 __byte_perm 设备路径不迁移。
#if defined(__has_builtin) && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#if __has_builtin(__builtin_bswap16)
#define CANN_ASC_STL_BUILTIN_BSWAP16(__v) __builtin_bswap16(__v)
#endif
#if __has_builtin(__builtin_bswap32)
#define CANN_ASC_STL_BUILTIN_BSWAP32(__v) __builtin_bswap32(__v)
#endif
#endif  // __has_builtin

// 基座 __config 未提供 dev 的 CANN_ASC_STL_DETAIL_HAS_INT128 / PRAGMA_UNROLL_FULL
// （dev 定义于 asc/std/__asc/extended_data_types.h、__asc/compiler.h）：内联其
// 语义的最小等价，#ifndef 守卫以免与未来基座定义冲突。
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

//! @brief 通用字节序反转回退：按字节循环移位重组（constexpr，任意宽度）。
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
    // 宿主：两个 32 位 builtin 交换 + 半字交换（避免部分版本对 64 位
    // builtin 的支持差异；与源侧 __byte_perm 的 64 位分解同构）
    const uint32_t __lo = static_cast<uint32_t>(__val);
    const uint32_t __hi = static_cast<uint32_t>(__val >> 32);
    return (static_cast<uint64_t>(CANN_ASC_STL_BUILTIN_BSWAP32(__lo)) << 32) |
        static_cast<uint64_t>(CANN_ASC_STL_BUILTIN_BSWAP32(__hi));
#else
    // 设备：可移植移位循环（aiv 后端无标量 bswap）
    return ::asc::std::__byteswap_generic(__val);
#endif
}

#if CANN_ASC_STL_DETAIL_HAS_INT128()
[[nodiscard]] CANN_ASC_STL_API constexpr __uint128_t __byteswap_impl(__uint128_t __val) noexcept
{
    // CCE 无 bswap128 builtin：递归分解为两个已验证的 64 位交换（基座
    // numeric_limits 无 int128 特化，等价展开 dev __byteswap_recursive
    // 的 128 位实例：高半字交换置于低位、低半字交换置于高位）
    constexpr int __shift = 64;
    return static_cast<__uint128_t>(::asc::std::__byteswap_impl(static_cast<uint64_t>(__val >> __shift))) |
        (static_cast<__uint128_t>(::asc::std::__byteswap_impl(static_cast<uint64_t>(__val))) << __shift);
}
#endif  // CANN_ASC_STL_DETAIL_HAS_INT128()

//! @brief 反转 @p value 的字节序（按对象表示逐字节反转）；单字节类型恒等，
//! bool 与非整型不参与（遵循上游标准库的整数契约，bool 显式排除）。
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
