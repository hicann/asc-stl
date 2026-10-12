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

#ifndef CANN_ASC_STL_ASC_STD___NUMERIC_SATURATING_SUB_H
#define CANN_ASC_STL_ASC_STD___NUMERIC_SATURATING_SUB_H

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
#include <asc/__numeric/checked.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__numeric/saturating_cast.h>
#include <asc/std/__type_traits/is_integer.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

// Delegates to the shared checked/saturating backend instead of deriving the
// saturation bounds from a fixed 64-bit constant pair: the backend decides
// overflow per operation in the unsigned domain, so every supported integer
// width saturates exactly (the bounds no longer inherit any limit from the
// saturating_cast width), and the overflow flag stays reusable. Valid in Host,
// ordinary AICore and pure SIMT.
template <class T>
CANN_ASC_STL_API constexpr T saturating_sub(T left, T right) noexcept
{
    static_assert(__is_integer_v<T>, "saturating_sub requires an integer type");
    return ::asc::detail::saturating_sub_impl(left, right).value;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___NUMERIC_SATURATING_SUB_H
