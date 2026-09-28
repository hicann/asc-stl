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

#ifndef CANN_ASC_STL_ASC_STD___BIT_ROTATE_H
#define CANN_ASC_STL_ASC_STD___BIT_ROTATE_H

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
#include <asc/std/__limits/numeric_limits.h>
#include <asc/std/__type_traits/is_unsigned_integer.h>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class _Tp>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _Tp rotl(const _Tp value, const int count) noexcept
{
    static_assert(__is_unsigned_integer_v<_Tp>, "rotl requires an unsigned integer type");
    // NOLINTNEXTLINE(build/include_what_you_use)
    const int digits = numeric_limits<_Tp>::digits;
    int effective = count % digits;
    if (effective < 0) {
        effective += digits;
    }
    if (effective == 0) {
        return value;
    }
    return static_cast<_Tp>((value << effective) | (value >> (digits - effective)));
}

template <class _Tp>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr _Tp rotr(const _Tp value, const int count) noexcept
{
    static_assert(__is_unsigned_integer_v<_Tp>, "rotr requires an unsigned integer type");
    // NOLINTNEXTLINE(build/include_what_you_use)
    const int digits = numeric_limits<_Tp>::digits;
    int effective = count % digits;
    if (effective < 0) {
        effective += digits;
    }
    if (effective == 0) {
        return value;
    }
    return static_cast<_Tp>((value >> effective) | (value << (digits - effective)));
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___BIT_ROTATE_H
