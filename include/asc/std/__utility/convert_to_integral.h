/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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
#ifndef CANN_ASC_STL_STD_DETAIL_UTILITY_CONVERT_TO_INTEGRAL_H
#define CANN_ASC_STL_STD_DETAIL_UTILITY_CONVERT_TO_INTEGRAL_H

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
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/underlying_type.h>

CANN_ASC_STL_BEGIN_NAMESPACE

CANN_ASC_STL_API constexpr int __convert_to_integral(int value)
{
    return value;
}

CANN_ASC_STL_API constexpr unsigned __convert_to_integral(unsigned value)
{
    return value;
}

CANN_ASC_STL_API constexpr long __convert_to_integral(long value)
{
    return value;
}

CANN_ASC_STL_API constexpr unsigned long __convert_to_integral(unsigned long value)
{
    return value;
}

CANN_ASC_STL_API constexpr long long __convert_to_integral(long long value)
{
    return value;
}

CANN_ASC_STL_API constexpr unsigned long long __convert_to_integral(unsigned long long value)
{
    return value;
}

template <class Fp>
CANN_ASC_STL_API constexpr enable_if_t<is_floating_point_v<Fp>, long long> __convert_to_integral(Fp value)
{
    return value;
}

template <class T, bool = is_enum_v<T>>
struct __sfinae_underlying_type {
    using type = typename underlying_type<T>::type;
    using __promoted_type = decltype(static_cast<type>(1) + 0);
};

template <class T>
struct __sfinae_underlying_type<T, false> {};

template <class T>
CANN_ASC_STL_API constexpr typename __sfinae_underlying_type<T>::__promoted_type __convert_to_integral(T value)
{
    return value;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_UTILITY_CONVERT_TO_INTEGRAL_H
