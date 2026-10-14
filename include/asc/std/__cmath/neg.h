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

#ifndef CANN_ASC_STL_ASC_STD___CMATH_NEG_H
#define CANN_ASC_STL_ASC_STD___CMATH_NEG_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_integral.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// Two's-complement negation through the 64-bit unsigned lane, integral
// arguments only. Floating point or pointer arguments would be silently
// truncated by the wraparound, so the enable_if guard keeps them out of the
// overload set instead of returning garbage. Pure integer bit arithmetic of
// this shape folds as constexpr on both host and device; do not copy this
// CANN_ASC_STL_API + constexpr combination onto routing functions that call
// simt_api or libm — device math library calls must stay out of constant
// evaluation.
template <class T, enable_if_t<is_integral<T>::value, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr T __neg(T value) noexcept
{
    static_assert(sizeof(T) <= 8, "__neg wraps through the 64-bit unsigned lane; wider integer types are unsupported");
    return static_cast<T>(__UINT64_C(0) - static_cast<__UINT64_TYPE__>(value));
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CMATH_NEG_H
