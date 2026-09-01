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
#ifndef CANN_ASC_STL_STD_DETAIL_CSTDDEF_BYTE_H
#define CANN_ASC_STL_STD_DETAIL_CSTDDEF_BYTE_H

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

CANN_ASC_STL_BEGIN_NAMESPACE

template <bool, class T = void>
struct __byte_enable_if {};

template <class T>
struct __byte_enable_if<true, T> {
    using type = T;
};

enum class byte : unsigned char {};

CANN_ASC_STL_API constexpr byte operator|(byte lhs, byte rhs) noexcept
{
    return static_cast<byte>(
        static_cast<unsigned char>(static_cast<unsigned int>(lhs) | static_cast<unsigned int>(rhs)));
}

CANN_ASC_STL_API constexpr byte& operator|=(byte& lhs, byte rhs) noexcept
{
    return lhs = lhs | rhs;
}

CANN_ASC_STL_API constexpr byte operator&(byte lhs, byte rhs) noexcept
{
    return static_cast<byte>(
        static_cast<unsigned char>(static_cast<unsigned int>(lhs) & static_cast<unsigned int>(rhs)));
}

CANN_ASC_STL_API constexpr byte& operator&=(byte& lhs, byte rhs) noexcept
{
    return lhs = lhs & rhs;
}

CANN_ASC_STL_API constexpr byte operator^(byte lhs, byte rhs) noexcept
{
    return static_cast<byte>(
        static_cast<unsigned char>(static_cast<unsigned int>(lhs) ^ static_cast<unsigned int>(rhs)));
}

CANN_ASC_STL_API constexpr byte& operator^=(byte& lhs, byte rhs) noexcept
{
    return lhs = lhs ^ rhs;
}

CANN_ASC_STL_API constexpr byte operator~(byte value) noexcept
{
    return static_cast<byte>(static_cast<unsigned char>(~static_cast<unsigned int>(value)));
}

template <class Integer>
CANN_ASC_STL_API constexpr auto operator<<=(byte& lhs, Integer shift) noexcept ->
    typename __byte_enable_if<is_integral_v<Integer>, byte&>::type
{
    return lhs = lhs << shift;
}

template <class Integer>
CANN_ASC_STL_API constexpr auto operator<<(byte lhs, Integer shift) noexcept ->
    typename __byte_enable_if<is_integral_v<Integer>, byte>::type
{
    return static_cast<byte>(static_cast<unsigned char>(static_cast<unsigned int>(lhs) << shift));
}

template <class Integer>
CANN_ASC_STL_API constexpr auto operator>>=(byte& lhs, Integer shift) noexcept ->
    typename __byte_enable_if<is_integral_v<Integer>, byte&>::type
{
    return lhs = lhs >> shift;
}

template <class Integer>
CANN_ASC_STL_API constexpr auto operator>>(byte lhs, Integer shift) noexcept ->
    typename __byte_enable_if<is_integral_v<Integer>, byte>::type
{
    return static_cast<byte>(static_cast<unsigned char>(static_cast<unsigned int>(lhs) >> shift));
}

template <class Integer>
CANN_ASC_STL_API constexpr auto to_integer(byte value) noexcept ->
    typename __byte_enable_if<is_integral_v<Integer>, Integer>::type
{
    return static_cast<Integer>(value);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_CSTDDEF_BYTE_H
