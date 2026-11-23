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

#ifndef CANN_ASC_STL_ASC___NUMERIC_TYPES_TRAITS_H
#define CANN_ASC_STL_ASC___NUMERIC_TYPES_TRAITS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__numeric_types/storage.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_member_object_pointer.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/void_t.h>

namespace asc {
namespace detail {

template <class Native, class = void>
struct numeric_native_byte_member {
    static constexpr bool value = false;
};

template <class Native>
struct numeric_native_byte_member<Native,
    asc::std::void_t<decltype(&Native::val), decltype(static_cast<Native*>(nullptr)->val)>> {
    using member_type = decltype(static_cast<Native*>(nullptr)->val);
    static constexpr bool value = asc::std::is_member_object_pointer_v<decltype(&Native::val)> &&
        (asc::std::is_same_v<member_type, char> || asc::std::is_same_v<member_type, signed char> ||
            asc::std::is_same_v<member_type, unsigned char>) &&
        asc::std::is_constructible_v<Native> && asc::std::is_constructible_v<Native, Native&>;
};

// Shared type identity for format metadata and extension queries. The registry
// contains no conversion implementation and is complete before public queries.
template <class T>
struct numeric_type_registration {
    static constexpr bool value = false;
};

template <numeric_format F>
struct numeric_type_registration<numeric_storage<F>> : numeric_descriptor<F> {
    static constexpr bool value = true;
};

template <class T>
struct numeric_native_mapping {
    static constexpr bool has_native_type = false;
};

// The native format/ABI adapter is qualified for BiSheng 15, dav-3510.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && defined(__NPU_ARCH__) && __NPU_ARCH__ == 3510 && \
    defined(__BISHENG_CCEC__) && __clang_major__ == 15
template <class Native, bool Compatible>
struct numeric_native_registration {
    static constexpr bool has_native_type = false;
};

template <class Native>
struct numeric_native_registration<Native, true> {
    using native_type = Native;
    static constexpr bool has_native_type = true;
};

#define CANN_ASC_STL_DETAIL_NUMERIC_NATIVE(TYPE, NATIVE, REQUIRE_TRIVIAL)                                           \
    template <>                                                                                                     \
    struct numeric_native_mapping<TYPE>                                                                             \
        : numeric_native_registration<NATIVE,                                                                       \
              sizeof(TYPE) == sizeof(NATIVE) && alignof(TYPE) == alignof(NATIVE) && __is_standard_layout(NATIVE) && \
                  (__is_trivially_copyable(NATIVE) ||                                                               \
                      (!(REQUIRE_TRIVIAL) && numeric_native_byte_member<NATIVE>::value))> {};                       \
    template <>                                                                                                     \
    struct numeric_type_registration<NATIVE> : numeric_type_registration<TYPE> {};
CANN_ASC_STL_DETAIL_NUMERIC_NATIVE(float16, ::half, true)
CANN_ASC_STL_DETAIL_NUMERIC_NATIVE(bfloat16, ::bfloat16_t, true)
CANN_ASC_STL_DETAIL_NUMERIC_NATIVE(float8_e4m3fn, ::float8_e4m3_t, true)
CANN_ASC_STL_DETAIL_NUMERIC_NATIVE(float8_e5m2, ::float8_e5m2_t, true)
CANN_ASC_STL_DETAIL_NUMERIC_NATIVE(float8_e8m0, ::float8_e8m0_t, true)
CANN_ASC_STL_DETAIL_NUMERIC_NATIVE(hifloat8, ::hifloat8_t, true)
CANN_ASC_STL_DETAIL_NUMERIC_NATIVE(float4_e2m1x2, ::float4_e2m1x2_t, true)
CANN_ASC_STL_DETAIL_NUMERIC_NATIVE(float4_e1m2x2, ::float4_e1m2x2_t, true)
#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
CANN_ASC_STL_DETAIL_NUMERIC_NATIVE(int4x2, ::int4x2_t, false)
#endif
#undef CANN_ASC_STL_DETAIL_NUMERIC_NATIVE
#endif

}  // namespace detail

template <class T>
struct numeric_format_traits {};

template <numeric_format F>
struct numeric_format_traits<detail::numeric_storage<F>>
    : detail::numeric_descriptor<F>, detail::numeric_native_mapping<detail::numeric_storage<F>> {};

template <class T>
using native_numeric_t = typename numeric_format_traits<T>::native_type;

}  // namespace asc

#endif  // CANN_ASC_STL_ASC___NUMERIC_TYPES_TRAITS_H
