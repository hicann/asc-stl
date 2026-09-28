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

#ifndef CANN_ASC_STL_ASC_STD___BIT_BYTESWAP_H
#define CANN_ASC_STL_ASC_STD___BIT_BYTESWAP_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/make_nbit_int.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/cstdint>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
struct __byteswap_allowed {
    static constexpr bool value = is_integral_v<T>;
};
template <>
struct __byteswap_allowed<bool> {
    static constexpr bool value = false;
};

template <class Integer>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr Integer byteswap(Integer value) noexcept
{
    static_assert(__byteswap_allowed<Integer>::value, "byteswap requires a non-bool integral type");
    if constexpr (!__byteswap_allowed<Integer>::value || sizeof(Integer) == 1) {
        return value;
    } else {
        using unsigned_type = make_unsigned_t<Integer>;
        unsigned_type input = static_cast<unsigned_type>(value);
        unsigned_type result = 0;
        for (__SIZE_TYPE__ index = 0; index < sizeof(Integer); ++index) {
            result = static_cast<unsigned_type>((result << 8) | (input & 0xffu));
            input >>= 8;
        }
        return static_cast<Integer>(result);
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___BIT_BYTESWAP_H
