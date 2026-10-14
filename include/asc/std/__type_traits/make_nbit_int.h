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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_MAKE_NBIT_INT_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_MAKE_NBIT_INT_H

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
#include <asc/std/__type_traits/always_false.h>
#include <asc/std/cstdint>

// <asc/__config> does not define these feature macros; provide minimal
// equivalents here, #ifndef-guarded against future definitions.
#ifndef CANN_ASC_STL_DETAIL_HAS_INT128
#if !defined(ASC_DISABLE_INT128_SUPPORT) && defined(__linux__) && defined(__SIZEOF_INT128__)
#define CANN_ASC_STL_DETAIL_HAS_INT128() 1
#else
#define CANN_ASC_STL_DETAIL_HAS_INT128() 0
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_INT128

#ifndef CANN_ASC_STL_DETAIL_UNREACHABLE
#if defined(_MSC_VER)
#define CANN_ASC_STL_DETAIL_UNREACHABLE() __assume(0)
#else
#define CANN_ASC_STL_DETAIL_UNREACHABLE() __builtin_unreachable()
#endif
#endif  // CANN_ASC_STL_DETAIL_UNREACHABLE

CANN_ASC_STL_BEGIN_NAMESPACE

template <size_t NBits, bool IsSigned>
CANN_ASC_STL_API constexpr auto __make_nbit_int_impl() noexcept
{
    if constexpr (IsSigned) {
        if constexpr (NBits == 8) {
            return int8_t{};
        } else if constexpr (NBits == 16) {
            return int16_t{};
        } else if constexpr (NBits == 32) {
            return int32_t{};
        } else if constexpr (NBits == 64) {
            return int64_t{};
#if CANN_ASC_STL_DETAIL_HAS_INT128()
        } else if constexpr (NBits == 128) {
            return __int128_t{};
#endif  // CANN_ASC_STL_DETAIL_HAS_INT128()
        } else {
            static_assert(__always_false_v<decltype(NBits)>, "Unsupported signed integer size");
            CANN_ASC_STL_DETAIL_UNREACHABLE();
        }
    } else {
        if constexpr (NBits == 8) {
            return uint8_t{};
        } else if constexpr (NBits == 16) {
            return uint16_t{};
        } else if constexpr (NBits == 32) {
            return uint32_t{};
        } else if constexpr (NBits == 64) {
            return uint64_t{};
#if CANN_ASC_STL_DETAIL_HAS_INT128()
        } else if constexpr (NBits == 128) {
            return __uint128_t{};
#endif  // CANN_ASC_STL_DETAIL_HAS_INT128()
        } else {
            static_assert(__always_false_v<decltype(NBits)>, "Unsupported unsigned integer size");
            CANN_ASC_STL_DETAIL_UNREACHABLE();
        }
    }
}

template <size_t NBits, bool IsSigned = true>
using __make_nbit_int_t = decltype(__make_nbit_int_impl<NBits, IsSigned>());

template <size_t NBits>
using __make_nbit_uint_t = __make_nbit_int_t<NBits, false>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_MAKE_NBIT_INT_H
