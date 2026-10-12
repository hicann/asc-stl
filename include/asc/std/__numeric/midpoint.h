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
#include <asc/__detail/execution_space.h>
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
#include <limits>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
CANN_ASC_STL_API constexpr enable_if_t<is_integral_v<T> && !is_same_v<bool, T> && !is_null_pointer_v<T>, T> midpoint(
    T left, T right) noexcept
{
    using unsigned_type = make_unsigned_t<T>;

    if (left > right) {
        const unsigned_type difference = unsigned_type(left) - unsigned_type(right);
        return static_cast<T>(left - static_cast<T>(difference / 2));
    } else {
        const unsigned_type difference = unsigned_type(right) - unsigned_type(left);
        return static_cast<T>(left + static_cast<T>(difference / 2));
    }
}

template <class T, enable_if_t<is_object_v<T> && !is_void_v<T> && (sizeof(T) > 0), int> = 0>
CANN_ASC_STL_API constexpr T* midpoint(T* left, T* right) noexcept
{
    return left + ::asc::std::midpoint(ptrdiff_t(0), right - left);
}

template <class T>
CANN_ASC_STL_API constexpr T __fp_abs(T value) noexcept
{
    return value >= 0 ? value : -value;
}

template <class T>
CANN_ASC_STL_API constexpr enable_if_t<is_floating_point_v<T>, T> midpoint(T left, T right) noexcept
{
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
    // 设备侧 numeric_limits 极值不可达，用编译器内建常量替代
    constexpr T low = static_cast<T>(__DBL_MIN__) * 2;
    constexpr T high = static_cast<T>(__DBL_MAX__) / 2;
#else
    constexpr T low = ::asc::std::numeric_limits<T>::min() * 2;
    constexpr T high = ::asc::std::numeric_limits<T>::max() / 2;
#endif
    return ::asc::std::__fp_abs(left) <= high && ::asc::std::__fp_abs(right) <= high ?
        // typical case: overflow is impossible
        (left + right) / 2 :
        // always correctly rounded
        ::asc::std::__fp_abs(left) < low ? left + right / 2 :        // not safe to halve left
            (::asc::std::__fp_abs(right) < low ? left / 2 + right :  // not safe to halve right
                    left / 2 + right / 2);  // otherwise correct...  // NOLINT(whitespace/line_length)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___NUMERIC_MIDPOINT_H
