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

#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_VECTOR_TYPES_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_VECTOR_TYPES_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

// The reference gates the whole file on its toolkit vector-type capability (dim3 and the
// reduced-precision vector families); the ASC counterpart is the CCE built-in short-vector
// family and dim3 (see the CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()/HAS_SIMT_DIM3()
// gates in __asc/asc_capabilities.h). The type set aligns one-to-one with the list
// established by __type_traits/vector_size.h (no 1/3-component members; the *_16a/_32a
// and reduced-precision 8/4/6-bit families have no ASC counterpart). The __get_element
// accessor machinery does not depend on built-in types (it works for any type with
// .x/.y/.z/.w members), so it stays outside the gate: host tests can exercise the same
// machinery with custom structs (same precedent as the primary-template-outside,
// specializations-inside split of vector_size.h).
#include <asc/std/__asc/asc_capabilities.h>
#include <asc/std/__fwd/get.h>
#include <asc/std/__tuple_dir/tuple_element.h>
#include <asc/std/__tuple_dir/tuple_size.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

#define CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(__vec, __base, __size)    \
    template <>                                                                  \
    struct tuple_size<__vec> : ::asc::std::integral_constant<size_t, __size> {}; \
                                                                                 \
    template <size_t _Ip>                                                        \
    struct tuple_element<_Ip, __vec> {                                           \
        static_assert(_Ip < __size, "tuple_element index out of range");         \
        using type = __base;                                                     \
    };

#define CANN_ASC_STL_DETAIL_SPECIALIZE_GET(__vec, __base)                                                      \
    template <size_t _Ip>                                                                                      \
    CANN_ASC_STL_API constexpr __base& get(__vec& __val) noexcept                                              \
    {                                                                                                          \
        return ::asc::std::__get_element<_Ip>::template get<__vec, __base>(__val);                             \
    }                                                                                                          \
    template <size_t _Ip>                                                                                      \
    CANN_ASC_STL_API constexpr const __base& get(const __vec& __val) noexcept                                  \
    {                                                                                                          \
        return ::asc::std::__get_element<_Ip>::template get<__vec, __base>(__val);                             \
    }                                                                                                          \
    template <size_t _Ip>                                                                                      \
    CANN_ASC_STL_API constexpr __base&& get(__vec&& __val) noexcept                                            \
    {                                                                                                          \
        return ::asc::std::__get_element<_Ip>::template get<__vec, __base>(static_cast<__vec&&>(__val));       \
    }                                                                                                          \
    template <size_t _Ip>                                                                                      \
    CANN_ASC_STL_API constexpr const __base&& get(const __vec&& __val) noexcept                                \
    {                                                                                                          \
        return ::asc::std::__get_element<_Ip>::template get<__vec, __base>(static_cast<const __vec&&>(__val)); \
    }

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <size_t _Ip>
struct __get_element;

template <>
struct __get_element<0> {
    template <class _Vec, class _BaseType>
    static CANN_ASC_STL_API constexpr _BaseType& get(_Vec& __val) noexcept
    {
        return __val.x;
    }

    template <class _Vec, class _BaseType>
    static CANN_ASC_STL_API constexpr const _BaseType& get(const _Vec& __val) noexcept
    {
        return __val.x;
    }

    template <class _Vec, class _BaseType>
    static CANN_ASC_STL_API constexpr _BaseType&& get(_Vec&& __val) noexcept
    {
        return static_cast<_BaseType&&>(__val.x);
    }

    template <class _Vec, class _BaseType>
    static CANN_ASC_STL_API constexpr const _BaseType&& get(const _Vec&& __val) noexcept
    {
        return static_cast<const _BaseType&&>(__val.x);
    }
};

template <>
struct __get_element<1> {
    template <class _Vec, class _BaseType>
    static CANN_ASC_STL_API constexpr _BaseType& get(_Vec& __val) noexcept
    {
        return __val.y;
    }

    template <class _Vec, class _BaseType>
    static CANN_ASC_STL_API constexpr const _BaseType& get(const _Vec& __val) noexcept
    {
        return __val.y;
    }

    template <class _Vec, class _BaseType>
    static CANN_ASC_STL_API constexpr _BaseType&& get(_Vec&& __val) noexcept
    {
        return static_cast<_BaseType&&>(__val.y);
    }

    template <class _Vec, class _BaseType>
    static CANN_ASC_STL_API constexpr const _BaseType&& get(const _Vec&& __val) noexcept
    {
        return static_cast<const _BaseType&&>(__val.y);
    }
};

template <>
struct __get_element<2> {
    template <class _Vec, class _BaseType>
    static CANN_ASC_STL_API constexpr _BaseType& get(_Vec& __val) noexcept
    {
        return __val.z;
    }

    template <class _Vec, class _BaseType>
    static CANN_ASC_STL_API constexpr const _BaseType& get(const _Vec& __val) noexcept
    {
        return __val.z;
    }

    template <class _Vec, class _BaseType>
    static CANN_ASC_STL_API constexpr _BaseType&& get(_Vec&& __val) noexcept
    {
        return static_cast<_BaseType&&>(__val.z);
    }

    template <class _Vec, class _BaseType>
    static CANN_ASC_STL_API constexpr const _BaseType&& get(const _Vec&& __val) noexcept
    {
        return static_cast<const _BaseType&&>(__val.z);
    }
};

template <>
struct __get_element<3> {
    template <class _Vec, class _BaseType>
    static CANN_ASC_STL_API constexpr _BaseType& get(_Vec& __val) noexcept
    {
        return __val.w;
    }

    template <class _Vec, class _BaseType>
    static CANN_ASC_STL_API constexpr const _BaseType& get(const _Vec& __val) noexcept
    {
        return __val.w;
    }

    template <class _Vec, class _BaseType>
    static CANN_ASC_STL_API constexpr _BaseType&& get(_Vec&& __val) noexcept
    {
        return static_cast<_BaseType&&>(__val.w);
    }

    template <class _Vec, class _BaseType>
    static CANN_ASC_STL_API constexpr const _BaseType&& get(const _Vec&& __val) noexcept
    {
        return static_cast<const _BaseType&&>(__val.w);
    }
};

// --- CCE built-in short-vector family (the 950 dual mode and the 310 mixed mode provide the full X2/X4 family) ---
#if CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()

CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::char2, char, 2)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::char4, char, 4)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::uchar2, unsigned char, 2)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::uchar4, unsigned char, 4)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::short2, short, 2)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::short4, short, 4)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::ushort2, unsigned short, 2)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::ushort4, unsigned short, 4)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::int4, int, 4)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::uint2, unsigned int, 2)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::uint4, unsigned int, 4)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::long2, long, 2)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::long4, long, 4)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::ulong2, unsigned long, 2)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::ulong4, unsigned long, 4)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::longlong2, long long, 2)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::longlong4, long long, 4)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::ulonglong2, unsigned long long, 2)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::ulonglong4, unsigned long long, 4)
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::float4, float, 4)

CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::char2, char)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::char4, char)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::uchar2, unsigned char)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::uchar4, unsigned char)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::short2, short)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::short4, short)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::ushort2, unsigned short)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::ushort4, unsigned short)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::int4, int)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::uint2, unsigned int)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::uint4, unsigned int)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::long2, long)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::long4, long)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::ulong2, unsigned long)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::ulong4, unsigned long)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::longlong2, long long)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::longlong4, long long)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::ulonglong2, unsigned long long)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::ulonglong4, unsigned long long)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::float4, float)

#endif  // CANN_ASC_STL_DETAIL_HAS_SIMT_VECTOR_TYPES()

// --- Fine-grained gated types (same gates as vector_size.h) ---
#if CANN_ASC_STL_DETAIL_HAS_SIMT_INT2()
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::int2, int, 2)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::int2, int)
#endif  // CANN_ASC_STL_DETAIL_HAS_SIMT_INT2()

#if CANN_ASC_STL_DETAIL_HAS_SIMT_FLOAT2()
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::float2, float, 2)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::float2, float)
#endif  // CANN_ASC_STL_DETAIL_HAS_SIMT_FLOAT2()

// dim3 (the grid-dimension coordinate type): the spelling depends on the compilation
// mode — the 310 mixed mode uses cce::dim3 from the CCE built-in namespace (default
// construction is device-only [aicore]); a pure-SIMT TU (-cce-enable-puresimt + the dpp
// runtime wrapper) gets the global ::dim3. Detected via PURE_SIMT_TU():
// __NPU_COMPILER_INTERNAL_PURE_SIMT__ is predefined in no mode at all, and the
// wrapper guard macro is also injected in ordinary kernel preprocess passes,
// so it must combine with !__CCE__ to be a puresimt signal.
// dpp runtime wrapper layer, with the classic shape.
#if CANN_ASC_STL_DETAIL_HAS_SIMT_DIM3()
#if CANN_ASC_STL_DETAIL_PURE_SIMT_TU()
#define CANN_ASC_STL_DETAIL_ASC_DIM3 ::dim3
#else
#define CANN_ASC_STL_DETAIL_ASC_DIM3 cce::dim3
#endif
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(CANN_ASC_STL_DETAIL_ASC_DIM3, unsigned int, 3)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(CANN_ASC_STL_DETAIL_ASC_DIM3, unsigned int)
#undef CANN_ASC_STL_DETAIL_ASC_DIM3
#endif  // CANN_ASC_STL_DETAIL_HAS_SIMT_DIM3()

// half2 (counterpart of the reference fp16-gated type; see extended_data_types.h)
#if CANN_ASC_STL_DETAIL_HAS_HALF2()
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::half2, ::half, 2)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::half2, ::half)
#endif  // CANN_ASC_STL_DETAIL_HAS_HALF2()

// bfloat16x2_t (counterpart of the reference bf16-gated type)
#if CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2()
CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE(::bfloat16x2_t, ::bfloat16_t, 2)
CANN_ASC_STL_DETAIL_SPECIALIZE_GET(::bfloat16x2_t, ::bfloat16_t)
#endif  // CANN_ASC_STL_DETAIL_HAS_BFLOAT16X2()

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#undef CANN_ASC_STL_DETAIL_SPECIALIZE_TUPLE_INTERFACE
#undef CANN_ASC_STL_DETAIL_SPECIALIZE_GET

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_VECTOR_TYPES_H
