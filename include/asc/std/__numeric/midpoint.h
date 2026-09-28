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

#ifndef CANN_ASC_STL_ASC_STD___NUMERIC_MIDPOINT_H
#define CANN_ASC_STL_ASC_STD___NUMERIC_MIDPOINT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_null_pointer.h>
#include <asc/std/__type_traits/is_object.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_pointer.h>
#include <asc/std/cstddef>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
CANN_ASC_STL_API constexpr enable_if_t<is_integral_v<T> && !is_same_v<bool, T> && !is_null_pointer_v<T>, T> midpoint(
    T left, T right) noexcept
{
    using unsigned_type = make_unsigned_t<T>;
    if (left > right) {
        const unsigned_type difference = unsigned_type(left) - unsigned_type(right);
        return static_cast<T>(left - static_cast<T>(difference / 2));
    }
    const unsigned_type difference = unsigned_type(right) - unsigned_type(left);
    return static_cast<T>(left + static_cast<T>(difference / 2));
}

template <class T, enable_if_t<is_object_v<T> && !is_void_v<T> && (sizeof(T) > 0), int> = 0>
CANN_ASC_STL_API constexpr T* midpoint(T* left, T* right) noexcept
{
    return left + ::asc::std::midpoint(ptrdiff_t(0), right - left);
}

template <class T>
CANN_ASC_STL_API constexpr T __midpoint_abs(T value)
{
    return value >= 0 ? value : -value;
}

template <class T>
CANN_ASC_STL_API constexpr enable_if_t<is_floating_point_v<T>, T> midpoint(T left, T right) noexcept
{
    constexpr T low =
        (is_same_v<T, float> ? static_cast<T>(__FLT_MIN__) :
                               (is_same_v<T, double> ? static_cast<T>(__DBL_MIN__) : static_cast<T>(__LDBL_MIN__))) *
        2;
    constexpr T high =
        (is_same_v<T, float> ? static_cast<T>(__FLT_MAX__) :
                               (is_same_v<T, double> ? static_cast<T>(__DBL_MAX__) : static_cast<T>(__LDBL_MAX__))) /
        2;
    return __midpoint_abs(left) <= high && __midpoint_abs(right) <= high ?
        (left + right) / 2 :
        (__midpoint_abs(left) < low ? left + right / 2 :
                                      (__midpoint_abs(right) < low ? left / 2 + right : left / 2 + right / 2));
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___NUMERIC_MIDPOINT_H
