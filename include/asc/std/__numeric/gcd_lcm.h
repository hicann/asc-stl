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

#ifndef CANN_ASC_STL_ASC_STD___NUMERIC_GCD_LCM_H
#define CANN_ASC_STL_ASC_STD___NUMERIC_GCD_LCM_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cmath/uabs.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/limits>

// 基座 __config 未提供 CANN_ASC_STL_DETAIL_ASSERT：内联其语义的最小等价，
// #ifndef 守卫以免与未来基座定义冲突。设备侧无断言机制恒为 no-op；宿主侧
// 仅在显式开启 ASC_ENABLE_HOST_ASSERTIONS 时检查。
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
CANN_ASC_STL_API constexpr T __gcd_unsigned(T left, T right)
{
    // AI Core does not support recursive function calls. Euclid's iterative
    // form preserves the same result and is valid in constant evaluation.
    while (right != 0) {
        const T remainder = left % right;
        left = right;
        right = remainder;
    }
    return left;
}

template <class T, class U>
CANN_ASC_STL_API constexpr common_type_t<T, U> gcd(T left, U right)
{
    static_assert(is_integral_v<T> && is_integral_v<U>, "gcd arguments must be integral");
    static_assert(!is_same_v<remove_cv_t<T>, bool> && !is_same_v<remove_cv_t<U>, bool>, "gcd arguments cannot be bool");
    using result_type = common_type_t<T, U>;
    using unsigned_type = make_unsigned_t<result_type>;
    return static_cast<result_type>(__gcd_unsigned(
        static_cast<unsigned_type>(::asc::std::__uabs(left)), static_cast<unsigned_type>(::asc::std::__uabs(right))));
}

template <class T, class U>
CANN_ASC_STL_API constexpr common_type_t<T, U> lcm(T left, U right)
{
    static_assert(is_integral_v<T> && is_integral_v<U>, "lcm arguments must be integral");
    static_assert(!is_same_v<remove_cv_t<T>, bool> && !is_same_v<remove_cv_t<U>, bool>, "lcm arguments cannot be bool");
    using result_type = common_type_t<T, U>;
    if (left == 0 || right == 0) {
        return 0;
    }
    // The magnitudes are folded into the unsigned domain of the common type
    // (explicit casts: unsigned long and unsigned long long stay distinct on
    // LP64), so the division and the overflow check never touch signed
    // overflow. The most-negative values travel correctly through the wide
    // negation inside __uabs.
    using unsigned_type = make_unsigned_t<result_type>;
    const unsigned_type left_magnitude =
        static_cast<unsigned_type>(::asc::std::__uabs(left)) / static_cast<unsigned_type>(::asc::std::gcd(left, right));
    const unsigned_type right_magnitude = static_cast<unsigned_type>(::asc::std::__uabs(right));
    [[maybe_unused]] const unsigned_type limit =
        static_cast<unsigned_type>(numeric_limits<result_type>::max());  // NOLINT(build/include_what_you_use)
    CANN_ASC_STL_DETAIL_ASSERT(limit / left_magnitude >= right_magnitude, "Overflow in lcm");
    return static_cast<result_type>(left_magnitude * right_magnitude);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___NUMERIC_GCD_LCM_H
