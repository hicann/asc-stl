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
#ifndef CANN_ASC_STL_STD_DETAIL_BIT_BIT_CAST_H
#define CANN_ASC_STL_STD_DETAIL_BIT_BIT_CAST_H

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
#include <asc/std/__cstring/memcpy.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_trivially_copyable.h>

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_bit_cast)
#define CANN_ASC_STL_DETAIL_BUILTIN_BIT_CAST(...) __builtin_bit_cast(__VA_ARGS__)
#endif

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_BIT_CAST)
#define CANN_ASC_STL_DETAIL_CONSTEXPR_BIT_CAST constexpr
#define CANN_ASC_STL_DETAIL_HAS_CONSTEXPR_BIT_CAST() 1
#else
#define CANN_ASC_STL_DETAIL_CONSTEXPR_BIT_CAST
#define CANN_ASC_STL_DETAIL_HAS_CONSTEXPR_BIT_CAST() 0
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

template <bool, class T = void>
struct __bit_cast_enable_if {};

template <class T>
struct __bit_cast_enable_if<true, T> {
    using type = T;
};

// -Wclass-memaccess is GCC-only; CCE rejects the unknown warning group under
// -Werror, so the suppression is expanded only on GCC.
#if defined(__GNUC__) && !defined(__clang__)
CANN_ASC_STL_DETAIL_DIAGNOSTIC_PUSH()
CANN_ASC_STL_DETAIL_DIAGNOSTIC_IGNORE("-Wclass-memaccess")
#endif

template <class To, class From>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API To __bit_cast_memcpy(const From& fx) noexcept
{
    static_assert(asc::std::is_default_constructible_v<To>,
        "bit_cast memcpy fallback requires the destination type to be default constructible");
    To temp;
    asc::std::memcpy(&temp, &fx, sizeof(To));
    return temp;
}

#if defined(__GNUC__) && !defined(__clang__)
CANN_ASC_STL_DETAIL_DIAGNOSTIC_POP()
#endif

template <class To, class From>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API CANN_ASC_STL_DETAIL_CONSTEXPR_BIT_CAST auto bit_cast(const From& fx) noexcept ->
    typename __bit_cast_enable_if<
        (sizeof(To) == sizeof(From)) && is_trivially_copyable_v<To> && is_trivially_copyable_v<From>, To>::type
{
#if defined(CANN_ASC_STL_DETAIL_BUILTIN_BIT_CAST)
    if constexpr (is_trivially_copyable_v<To> && is_trivially_copyable_v<From>) {
        return CANN_ASC_STL_DETAIL_BUILTIN_BIT_CAST(To, fx);
    } else  // NOLINT(readability/braces)
#endif      // CANN_ASC_STL_DETAIL_BUILTIN_BIT_CAST
    {
        return asc::std::__bit_cast_memcpy<To>(fx);
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_BIT_BIT_CAST_H
