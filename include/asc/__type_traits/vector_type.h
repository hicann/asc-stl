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

#ifndef CANN_ASC_STL_DETAIL_TYPE_TRAITS_VECTOR_TYPE_H
#define CANN_ASC_STL_DETAIL_TYPE_TRAITS_VECTOR_TYPE_H

#include <asc/std/detail/__config>

#include <asc/std/__cstddef/types.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_same.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

// vector_type

template <class _Tp, ::asc::std::size_t _Size>
struct vector_type {
    using type = void;
};

#if CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()

template <>
struct vector_type<signed char, 2> {
    using type = ::char2;
};
template <>
struct vector_type<signed char, 4> {
    using type = ::char4;
};

template <>
struct vector_type<unsigned char, 2> {
    using type = ::uchar2;
};
template <>
struct vector_type<unsigned char, 4> {
    using type = ::uchar4;
};

template <>
struct vector_type<short, 2> {
    using type = ::short2;
};
template <>
struct vector_type<short, 4> {
    using type = ::short4;
};

template <>
struct vector_type<unsigned short, 2> {
    using type = ::ushort2;
};
template <>
struct vector_type<unsigned short, 4> {
    using type = ::ushort4;
};

template <>
struct vector_type<int, 4> {
    using type = ::int4;
};

template <>
struct vector_type<unsigned, 2> {
    using type = ::uint2;
};
template <>
struct vector_type<unsigned, 4> {
    using type = ::uint4;
};

template <>
struct vector_type<long, 2> {
    using type = ::long2;
};
template <>
struct vector_type<long, 4> {
    using type = ::long4;
};

template <>
struct vector_type<unsigned long, 2> {
    using type = ::ulong2;
};
template <>
struct vector_type<unsigned long, 4> {
    using type = ::ulong4;
};

template <>
struct vector_type<long long, 2> {
    using type = ::longlong2;
};
template <>
struct vector_type<long long, 4> {
    using type = ::longlong4;
};

template <>
struct vector_type<unsigned long long, 2> {
    using type = ::ulonglong2;
};
template <>
struct vector_type<unsigned long long, 4> {
    using type = ::ulonglong4;
};

template <>
struct vector_type<float, 4> {
    using type = ::float4;
};

#endif  // CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()

#if CANN_ASC_STL_DETAIL_HAS_SIMT_INT2()
template <>
struct vector_type<int, 2> {
    using type = ::int2;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_SIMT_INT2()

#if CANN_ASC_STL_DETAIL_HAS_SIMT_FLOAT2()
template <>
struct vector_type<float, 2> {
    using type = ::float2;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_SIMT_FLOAT2()

#if CANN_ASC_STL_DETAIL_HAS_HALF2()
template <>
struct vector_type<::half, 2> {
    using type = ::half2;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_HALF2()

#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2()
template <>
struct vector_type<::bfloat16_t, 2> {
    using type = ::bfloat16x2_t;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2()

#if CANN_ASC_STL_DETAIL_HAS_FP8_E4M3X2()
template <>
struct vector_type<::float8_e4m3_t, 2> {
    using type = ::float8_e4m3x2_t;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E4M3X2()

#if CANN_ASC_STL_DETAIL_HAS_FP8_E5M2X2()
template <>
struct vector_type<::float8_e5m2_t, 2> {
    using type = ::float8_e5m2x2_t;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_FP8_E5M2X2()

template <class _Tp, ::asc::std::size_t _Size>
using vector_type_t = typename vector_type<_Tp, _Size>::type;

// has_vector_type

template <class _Tp, ::asc::std::size_t _Size>
inline constexpr bool has_vector_type_v = !::asc::std::is_same_v<vector_type_t<_Tp, _Size>, void>;

template <class _Tp, ::asc::std::size_t _Size>
using has_vector_type = ::asc::std::bool_constant<has_vector_type_v<_Tp, _Size>>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_TYPE_TRAITS_VECTOR_TYPE_H
