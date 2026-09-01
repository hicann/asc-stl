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

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/underlying_type.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

CANN_ASC_STL_API constexpr int __convert_to_integral(int __val)
{
    return __val;
}

CANN_ASC_STL_API constexpr unsigned __convert_to_integral(unsigned __val)
{
    return __val;
}

CANN_ASC_STL_API constexpr long __convert_to_integral(long __val)
{
    return __val;
}

CANN_ASC_STL_API constexpr unsigned long __convert_to_integral(unsigned long __val)
{
    return __val;
}

CANN_ASC_STL_API constexpr long long __convert_to_integral(long long __val)
{
    return __val;
}

CANN_ASC_STL_API constexpr unsigned long long __convert_to_integral(unsigned long long __val)
{
    return __val;
}

template <typename _Fp>
CANN_ASC_STL_API constexpr enable_if_t<is_floating_point_v<_Fp>, long long> __convert_to_integral(_Fp __val)
{
    return __val;
}

#if CANN_ASC_STL_DETAIL_HAS_INT128()
CANN_ASC_STL_API constexpr __int128_t __convert_to_integral(__int128_t __val)
{
    return __val;
}

CANN_ASC_STL_API constexpr __uint128_t __convert_to_integral(__uint128_t __val)
{
    return __val;
}
#endif  // CANN_ASC_STL_DETAIL_HAS_INT128()

template <class _Tp, bool = is_enum_v<_Tp>>
struct __sfinae_underlying_type {
    using type = typename underlying_type<_Tp>::type;
    using __promoted_type = decltype(((type)1) + 0);
};

template <class _Tp>
struct __sfinae_underlying_type<_Tp, false> {};

template <class _Tp>
CANN_ASC_STL_API constexpr typename __sfinae_underlying_type<_Tp>::__promoted_type __convert_to_integral(_Tp __val)
{
    return __val;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_UTILITY_CONVERT_TO_INTEGRAL_H
