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

#ifndef CANN_ASC_STL_ASC_STD___COMPLEX_VECTOR_SUPPORT_H
#define CANN_ASC_STL_ASC_STD___COMPLEX_VECTOR_SUPPORT_H

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
#include <asc/std/__type_traits/is_extended_floating_point.h>
#include <asc/std/__type_traits/is_floating_point.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Tp>
inline constexpr bool __is_complex_float_v = is_floating_point_v<Tp> || __is_extended_floating_point_v<Tp>;

template <class Tp>
inline constexpr size_t __complex_alignment_v = 2 * sizeof(Tp);

#define CANN_ASC_STL_DETAIL_COMPLEX_ALIGNAS alignas(__complex_alignment_v<Tp>)

template <class Tp>
struct __type_to_vector;

template <class Tp>
using __type_to_vector_t = typename __type_to_vector<Tp>::__type;

template <class Tp, class = void>
inline constexpr bool __has_vector_type_v = false;

template <class Tp>
inline constexpr bool __has_vector_type_v<Tp, void_t<__type_to_vector_t<Tp>>> = true;

template <class Tp>
struct __abcd_results {
    Tp __ac;
    Tp __bd;
    Tp __ad;
    Tp __bc;
};

template <class Tp>
struct __ab_results {
    Tp __a;
    Tp __b;
};

template <class Tp, ::asc::std::enable_if_t<!__has_vector_type_v<Tp>, int> = 0>
CANN_ASC_STL_API constexpr __abcd_results<Tp> __complex_calculate_partials(Tp a, Tp b, Tp c, Tp d) noexcept
{
    return {a * c, b * d, a * d, b * c};
}

template <class Tp, ::asc::std::enable_if_t<!__has_vector_type_v<Tp>, int> = 0>
CANN_ASC_STL_API constexpr __ab_results<Tp> __complex_piecewise_mul(Tp x1, Tp y1, Tp x2, Tp y2) noexcept
{
    return {x1 * x2, y1 * y2};
}

template <class Tp, ::asc::std::enable_if_t<__has_vector_type_v<Tp>, int> = 0>
CANN_ASC_STL_API constexpr __abcd_results<Tp> __complex_calculate_partials(Tp a, Tp b, Tp c, Tp d) noexcept
{
    __abcd_results<Tp> ret;

    using Vec = __type_to_vector_t<Tp>;

    Vec first{a, b};
    Vec second{c, d};
    Vec second_flip{d, c};

    Vec ac_bd = first * second;
    Vec ad_bc = first * second_flip;

    ret.__ac = ac_bd.x;
    ret.__bd = ac_bd.y;
    ret.__ad = ad_bc.x;
    ret.__bc = ad_bc.y;

    return ret;
}

template <class Tp, ::asc::std::enable_if_t<__has_vector_type_v<Tp>, int> = 0>
CANN_ASC_STL_API constexpr __ab_results<Tp> __complex_piecewise_mul(Tp x1, Tp y1, Tp x2, Tp y2) noexcept
{
    __ab_results<Tp> ret;

    using Vec = __type_to_vector_t<Tp>;

    Vec v1{x1, y1};
    Vec v2{x2, y2};

    Vec result = v1 * v2;

    ret.__a = result.x;
    ret.__b = result.y;

    return ret;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_VECTOR_SUPPORT_H
