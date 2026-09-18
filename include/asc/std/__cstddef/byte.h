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

#ifndef CANN_ASC_STL_STD_DETAIL_CSTDDEF_BYTE_H
#define CANN_ASC_STL_STD_DETAIL_CSTDDEF_BYTE_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_integral.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_NOVERSION

enum class byte : unsigned char {};

CANN_ASC_STL_API constexpr byte operator|(byte __lhs, byte __rhs) noexcept
{
    return static_cast<byte>(
        static_cast<unsigned char>(static_cast<unsigned int>(__lhs) | static_cast<unsigned int>(__rhs)));
}

CANN_ASC_STL_API constexpr byte& operator|=(byte& __lhs, byte __rhs) noexcept
{
    return __lhs = __lhs | __rhs;
}

CANN_ASC_STL_API constexpr byte operator&(byte __lhs, byte __rhs) noexcept
{
    return static_cast<byte>(
        static_cast<unsigned char>(static_cast<unsigned int>(__lhs) & static_cast<unsigned int>(__rhs)));
}

CANN_ASC_STL_API constexpr byte& operator&=(byte& __lhs, byte __rhs) noexcept
{
    return __lhs = __lhs & __rhs;
}

CANN_ASC_STL_API constexpr byte operator^(byte __lhs, byte __rhs) noexcept
{
    return static_cast<byte>(
        static_cast<unsigned char>(static_cast<unsigned int>(__lhs) ^ static_cast<unsigned int>(__rhs)));
}

CANN_ASC_STL_API constexpr byte& operator^=(byte& __lhs, byte __rhs) noexcept
{
    return __lhs = __lhs ^ __rhs;
}

CANN_ASC_STL_API constexpr byte operator~(byte __b) noexcept
{
    return static_cast<byte>(static_cast<unsigned char>(~static_cast<unsigned int>(__b)));
}

template <class _Integer, class = enable_if_t<is_integral_v<_Integer>>>
CANN_ASC_STL_API constexpr byte& operator<<=(byte& __lhs, _Integer __shift) noexcept
{
    return __lhs = __lhs << __shift;
}

template <class _Integer, class = enable_if_t<is_integral_v<_Integer>>>
CANN_ASC_STL_API constexpr byte operator<<(byte __lhs, _Integer __shift) noexcept
{
    return static_cast<byte>(static_cast<unsigned char>(static_cast<unsigned int>(__lhs) << __shift));
}

template <class _Integer, class = enable_if_t<is_integral_v<_Integer>>>
CANN_ASC_STL_API constexpr byte& operator>>=(byte& __lhs, _Integer __shift) noexcept
{
    return __lhs = __lhs >> __shift;
}

template <class _Integer, class = enable_if_t<is_integral_v<_Integer>>>
CANN_ASC_STL_API constexpr byte operator>>(byte __lhs, _Integer __shift) noexcept
{
    return static_cast<byte>(static_cast<unsigned char>(static_cast<unsigned int>(__lhs) >> __shift));
}

template <class _Integer, class = enable_if_t<is_integral_v<_Integer>>>
CANN_ASC_STL_API constexpr _Integer to_integer(byte __b) noexcept
{
    return static_cast<_Integer>(__b);
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_NOVERSION

#endif  // CANN_ASC_STL_STD_DETAIL_CSTDDEF_BYTE_H
