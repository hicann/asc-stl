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

#ifndef CANN_ASC_STL_ASC_STD___NUMERIC_SATURATING_DIV_H
#define CANN_ASC_STL_ASC_STD___NUMERIC_SATURATING_DIV_H

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
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/limits>

// __config provides no CANN_ASC_STL_DETAIL_ASSERT: this is a minimal
// equivalent of its semantics, guarded by #ifndef to avoid clashing with a
// future definition. Device side has no assertion mechanism and stays a
// no-op; host side checks only when ASC_ENABLE_HOST_ASSERTIONS is explicitly
// enabled.
#ifndef CANN_ASC_STL_DETAIL_ASSERT
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || !defined(ASC_ENABLE_HOST_ASSERTIONS)
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    ((expression) ? static_cast<void>(0) : (__builtin_trap(), static_cast<void>(0)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSERT

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
CANN_ASC_STL_API constexpr T saturating_div(T left, T right) noexcept
{
    static_assert(__is_integer_v<T>, "saturating_div requires an integer type");
    CANN_ASC_STL_DETAIL_ASSERT(right != T(0), "division by zero");
    if constexpr (is_signed_v<T>) {
        if (left == numeric_limits<T>::min() && right == T(-1)) {  // NOLINT(build/include_what_you_use)
            return numeric_limits<T>::max();                       // NOLINT(build/include_what_you_use)
        }
    }
    return static_cast<T>(left / right);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___NUMERIC_SATURATING_DIV_H
