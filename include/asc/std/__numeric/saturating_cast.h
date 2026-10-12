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

#ifndef CANN_ASC_STL_ASC_STD___NUMERIC_SATURATING_CAST_H
#define CANN_ASC_STL_ASC_STD___NUMERIC_SATURATING_CAST_H

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
#include <asc/std/__type_traits/is_integer.h>
#include <asc/std/__utility/cmp.h>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

// Saturation compares the exact integer domains through the cmp helpers and
// numeric_limits instead of a floating-point intermediate: every compared
// value stays precise for each supported width (a long double mantissa cannot
// be assumed to carry a full 64-bit integer), and mixed sign comparisons stay
// well-defined. All paths are plain constexpr arithmetic, valid in Host,
// ordinary AICore and pure SIMT alike.
template <class To, class From>
CANN_ASC_STL_API constexpr To saturating_cast(From value) noexcept
{
    static_assert(__is_integer_v<To> && __is_integer_v<From>, "saturating_cast requires integer types");
    if (::asc::std::cmp_less(value, numeric_limits<To>::min())) {  // NOLINT(build/include_what_you_use)
        return numeric_limits<To>::min();                          // NOLINT(build/include_what_you_use)
    }
    if (::asc::std::cmp_greater(value, numeric_limits<To>::max())) {  // NOLINT(build/include_what_you_use)
        return numeric_limits<To>::max();                             // NOLINT(build/include_what_you_use)
    }
    return static_cast<To>(value);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___NUMERIC_SATURATING_CAST_H
