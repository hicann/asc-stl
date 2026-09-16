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

#ifndef CANN_ASC_STL_ASC_STD___FLOATING_POINT_OVERFLOW_HANDLER_H
#define CANN_ASC_STL_ASC_STD___FLOATING_POINT_OVERFLOW_HANDLER_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__floating_point/arithmetic.h>
#include <asc/std/__floating_point/constants.h>
#include <asc/std/__floating_point/format.h>
#include <asc/std/__floating_point/properties.h>
#include <asc/std/__floating_point/storage.h>
#include <asc/std/__type_traits/always_false.h>

CANN_ASC_STL_BEGIN_NAMESPACE

enum class __fp_overflow_handler_kind { __no_sat, __sat_finite };
template <__fp_overflow_handler_kind Kind>
struct __fp_overflow_handler;
template <>
struct __fp_overflow_handler<__fp_overflow_handler_kind::__no_sat> {
    template <class T>
    CANN_ASC_STL_API static constexpr T __handle_overflow() noexcept
    {
        return __fp_inf<T>();
    }
    template <class T>
    CANN_ASC_STL_API static constexpr T __handle_underflow() noexcept
    {
        return __fp_neg(__fp_inf<T>());
    }
};
template <>
struct __fp_overflow_handler<__fp_overflow_handler_kind::__sat_finite> {
    template <class T>
    CANN_ASC_STL_API static constexpr T __handle_overflow() noexcept
    {
        return __fp_max<T>();
    }
    template <class T>
    CANN_ASC_STL_API static constexpr T __handle_underflow() noexcept
    {
        return __fp_lowest<T>();
    }
};
template <class T>
inline constexpr bool __fp_is_overflow_handler_v = false;
template <class T>
inline constexpr bool __fp_is_overflow_handler_v<const T> = __fp_is_overflow_handler_v<T>;
template <class T>
inline constexpr bool __fp_is_overflow_handler_v<volatile T> = __fp_is_overflow_handler_v<T>;
template <class T>
inline constexpr bool __fp_is_overflow_handler_v<const volatile T> = __fp_is_overflow_handler_v<T>;
template <__fp_overflow_handler_kind Kind>
inline constexpr bool __fp_is_overflow_handler_v<__fp_overflow_handler<Kind>> = true;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FLOATING_POINT_OVERFLOW_HANDLER_H
