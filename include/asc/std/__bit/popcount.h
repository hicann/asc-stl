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

#ifndef CANN_ASC_STL_ASC_STD___BIT_POPCOUNT_H
#define CANN_ASC_STL_ASC_STD___BIT_POPCOUNT_H

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
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_unsigned_integer.h>
#include <asc/std/cstdint>
#include <asc/std/limits>

// The shared <asc/__config> does not provide CANN_ASC_STL_DETAIL_ASSUME:
// inline a minimal equivalent of its semantics, guarded by #ifndef so a
// future centralized definition wins.
#ifndef CANN_ASC_STL_DETAIL_ASSUME
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_assume)
#define CANN_ASC_STL_DETAIL_ASSUME(...) __builtin_assume(__VA_ARGS__)
#else
#define CANN_ASC_STL_DETAIL_ASSUME(...) ((void)sizeof(!(__VA_ARGS__)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSUME

CANN_ASC_STL_BEGIN_NAMESPACE

//! @brief Counts the set bits in @p value (Kernighan's bit-clearing method:
//! clears the lowest set bit on each iteration).
template <class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr __unsigned_integer_result_t<T, int> popcount(T value) noexcept
{
    int __count = 0;
    while (value != 0) {
        value &= static_cast<T>(value - 1);
        ++__count;
    }
    CANN_ASC_STL_DETAIL_ASSUME(
        __count >= 0 && __count <= numeric_limits<T>::digits);  // NOLINT(build/include_what_you_use)
    return __count;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___BIT_POPCOUNT_H
