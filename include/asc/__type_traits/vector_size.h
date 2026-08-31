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

#ifndef CANN_ASC_STL_DETAIL_TYPE_TRAITS_VECTOR_SIZE_H
#define CANN_ASC_STL_DETAIL_TYPE_TRAITS_VECTOR_SIZE_H

#include <asc/std/detail/__config>

#include <asc/std/__cstddef/types.h>
#include <asc/std/__type_traits/integral_constant.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC
CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_PUSH

template <class _Tp>
inline constexpr ::asc::std::size_t vector_size_v = 0;
template <class _Tp>
inline constexpr ::asc::std::size_t vector_size_v<const _Tp> = vector_size_v<_Tp>;
template <class _Tp>
inline constexpr ::asc::std::size_t vector_size_v<volatile _Tp> = vector_size_v<_Tp>;
template <class _Tp>
inline constexpr ::asc::std::size_t vector_size_v<const volatile _Tp> = vector_size_v<_Tp>;

#if CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()
#define CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(_Vector, _Size) \
    template <>                                                         \
    inline constexpr ::asc::std::size_t vector_size_v<::_Vector> = _Size

CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(char2, 2);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(char4, 4);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(uchar2, 2);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(uchar4, 4);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(short2, 2);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(short4, 4);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(ushort2, 2);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(ushort4, 4);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(int4, 4);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(uint2, 2);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(uint4, 4);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(long2, 2);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(long4, 4);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(ulong2, 2);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(ulong4, 4);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(longlong2, 2);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(longlong4, 4);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(ulonglong2, 2);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(ulonglong4, 4);
CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE(float4, 4);

#undef CANN_ASC_STL_DETAIL_ACCL_SPECIALIZE_VECTOR_SIZE
#endif  // CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()

#if CANN_ASC_STL_DETAIL_HAS_SIMT_INT2()
template <>
inline constexpr ::asc::std::size_t vector_size_v<::int2> = 2;
#endif

#if CANN_ASC_STL_DETAIL_HAS_SIMT_FLOAT2()
template <>
inline constexpr ::asc::std::size_t vector_size_v<::float2> = 2;
#endif

#if CANN_ASC_STL_DETAIL_HAS_SIMT_DIM3()
template <>
inline constexpr ::asc::std::size_t vector_size_v<::dim3> = 3;
#endif

#if CANN_ASC_STL_DETAIL_HAS_HALF2()
template <>
inline constexpr ::asc::std::size_t vector_size_v<::half2> = 2;
#endif  // CANN_ASC_STL_DETAIL_HAS_HALF2()

#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2()
template <>
inline constexpr ::asc::std::size_t vector_size_v<::bfloat16x2_t> = 2;
#endif  // CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2()

template <class _Tp>
using vector_size = ::asc::std::integral_constant<::asc::std::size_t, vector_size_v<_Tp>>;

CANN_ASC_STL_DETAIL_SUPPRESS_DEPRECATED_POP
CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_DETAIL_TYPE_TRAITS_VECTOR_SIZE_H
