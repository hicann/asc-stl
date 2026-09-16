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

#ifndef CANN_ASC_STL_DETAIL_TYPE_TRAITS_SCALAR_TYPE_H
#define CANN_ASC_STL_DETAIL_TYPE_TRAITS_SCALAR_TYPE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

template <class _Tp>
struct scalar_type {};

template <class _Tp>
struct scalar_type<const _Tp> : scalar_type<_Tp> {};

template <class _Tp>
struct scalar_type<volatile _Tp> : scalar_type<_Tp> {};

template <class _Tp>
struct scalar_type<const volatile _Tp> : scalar_type<_Tp> {};

#if CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()
#define CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(_Vector, _Scalar) \
    template <>                                                           \
    struct scalar_type<::_Vector> {                                       \
        using type = _Scalar;                                             \
    }

CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(char2, signed char);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(char4, signed char);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(uchar2, unsigned char);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(uchar4, unsigned char);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(short2, short);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(short4, short);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(ushort2, unsigned short);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(ushort4, unsigned short);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(int4, int);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(uint2, unsigned);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(uint4, unsigned);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(long2, long);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(long4, long);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(ulong2, unsigned long);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(ulong4, unsigned long);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(longlong2, long long);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(longlong4, long long);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(ulonglong2, unsigned long long);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(ulonglong4, unsigned long long);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE(float4, float);

#undef CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_SCALAR_TYPE
#endif  // CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()

#if CANN_ASC_STL_DETAIL_HAS_SIMT_INT2()
template <>
struct scalar_type<::int2> {
    using type = int;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_SIMT_INT2()

#if CANN_ASC_STL_DETAIL_HAS_SIMT_FLOAT2()
template <>
struct scalar_type<::float2> {
    using type = float;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_SIMT_FLOAT2()

#if CANN_ASC_STL_DETAIL_HAS_SIMT_DIM3()
// The dim3 spelling is mode-dependent: a pure-SIMT TU provides the global ::dim3
// through the dpp runtime wrapper, while ordinary kernel mode provides cce::dim3
// from the CCE built-in namespace (same conditional as vector_size.h).
#if CANN_ASC_STL_DETAIL_PURE_SIMT_TU()
template <>
struct scalar_type<::dim3> {
    using type = unsigned;
};
#else
template <>
struct scalar_type<::cce::dim3> {
    using type = unsigned;
};
#endif  // CANN_ASC_STL_DETAIL_PURE_SIMT_TU()
#endif  // CANN_ASC_STL_DETAIL_HAS_SIMT_DIM3()

#if CANN_ASC_STL_DETAIL_HAS_HALF2()
template <>
struct scalar_type<::half2> {
    using type = ::half;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_HALF2()

#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2()
template <>
struct scalar_type<::bfloat16x2_t> {
    using type = ::bfloat16_t;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2()

template <class _Tp>
using scalar_type_t = typename scalar_type<_Tp>::type;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_TYPE_TRAITS_SCALAR_TYPE_H
