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

#ifndef CANN_ASC_STL_ASC___NUMERIC_TYPES_STORAGE_H
#define CANN_ASC_STL_ASC___NUMERIC_TYPES_STORAGE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/std/cstdint>

// The pure-SIMT frontend also compiles Host argument preparation in ASC files.
#if defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
#define CANN_ASC_STL_DETAIL_NUMERIC_API __host__ __aicore__ CANN_ASC_STL_DETAIL_VISIBILITY_HIDDEN inline
#else
#define CANN_ASC_STL_DETAIL_NUMERIC_API CANN_ASC_STL_API
#endif

namespace asc {

enum class numeric_format {
    fp16 = 0,
    bf16 = 1,
    fp8_e4m3fn = 2,
    fp8_e5m2 = 3,
    fp8_e8m0 = 4,
    hif8 = 5,
    fp4_e2m1x2 = 6,
    fp4_e1m2x2 = 7,
    int4x2 = 8,
    int4 = 9
};

namespace detail {

template <numeric_format Format>
struct numeric_descriptor;

template <numeric_format Format, class Storage, unsigned Bits, unsigned Lanes>
struct numeric_description {
    using storage_type = Storage;
    static constexpr numeric_format format = Format;
    static constexpr unsigned bits = Bits;
    static constexpr unsigned storage_bits = sizeof(Storage) * 8;
    static constexpr unsigned lanes = Lanes;
};

#define CANN_ASC_STL_DETAIL_NUMERIC_DESCRIPTION(FORMAT, STORAGE, BITS, LANES) \
    template <>                                                               \
    struct numeric_descriptor<numeric_format::FORMAT>                         \
        : numeric_description<numeric_format::FORMAT, STORAGE, BITS, LANES> {};
CANN_ASC_STL_DETAIL_NUMERIC_DESCRIPTION(fp16, asc::std::uint16_t, 16, 1)
CANN_ASC_STL_DETAIL_NUMERIC_DESCRIPTION(bf16, asc::std::uint16_t, 16, 1)
CANN_ASC_STL_DETAIL_NUMERIC_DESCRIPTION(fp8_e4m3fn, asc::std::uint8_t, 8, 1)
CANN_ASC_STL_DETAIL_NUMERIC_DESCRIPTION(fp8_e5m2, asc::std::uint8_t, 8, 1)
CANN_ASC_STL_DETAIL_NUMERIC_DESCRIPTION(fp8_e8m0, asc::std::uint8_t, 8, 1)
CANN_ASC_STL_DETAIL_NUMERIC_DESCRIPTION(hif8, asc::std::uint8_t, 8, 1)
CANN_ASC_STL_DETAIL_NUMERIC_DESCRIPTION(fp4_e2m1x2, asc::std::uint8_t, 4, 2)
CANN_ASC_STL_DETAIL_NUMERIC_DESCRIPTION(fp4_e1m2x2, asc::std::uint8_t, 4, 2)
CANN_ASC_STL_DETAIL_NUMERIC_DESCRIPTION(int4x2, asc::std::uint8_t, 4, 2)
CANN_ASC_STL_DETAIL_NUMERIC_DESCRIPTION(int4, asc::std::uint8_t, 4, 1)
#undef CANN_ASC_STL_DETAIL_NUMERIC_DESCRIPTION

struct numeric_access;

// Kernel argument setup copies these values in the pure-SIMT Host launch pass.
#if defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
#define CANN_ASC_STL_DETAIL_NUMERIC_VALUE_HD __host__ __aicore__
#else
#define CANN_ASC_STL_DETAIL_NUMERIC_VALUE_HD CANN_ASC_STL_HOST_DEVICE
#endif

template <numeric_format Format>
class numeric_storage {
    using storage_type = typename numeric_descriptor<Format>::storage_type;
    storage_type bits_;
    friend struct numeric_access;

    CANN_ASC_STL_DETAIL_NUMERIC_VALUE_HD explicit constexpr numeric_storage(storage_type bits) noexcept : bits_(bits)
    {}

public:
    // Defaulting on the first declaration, without a member initializer, keeps
    // default construction trivial. Value initialization still clears bits_.
    CANN_ASC_STL_DETAIL_NUMERIC_VALUE_HD numeric_storage() = default;
    CANN_ASC_STL_DETAIL_NUMERIC_VALUE_HD numeric_storage(const numeric_storage&) = default;
    CANN_ASC_STL_DETAIL_NUMERIC_VALUE_HD numeric_storage(numeric_storage&&) = default;
    CANN_ASC_STL_DETAIL_NUMERIC_VALUE_HD numeric_storage& operator=(const numeric_storage&) = default;
    CANN_ASC_STL_DETAIL_NUMERIC_VALUE_HD numeric_storage& operator=(numeric_storage&&) = default;
    CANN_ASC_STL_DETAIL_NUMERIC_VALUE_HD ~numeric_storage() = default;
};

#undef CANN_ASC_STL_DETAIL_NUMERIC_VALUE_HD

struct numeric_access {
    template <numeric_format F>
    CANN_ASC_STL_DETAIL_NUMERIC_API static constexpr auto read(numeric_storage<F> value) noexcept
    {
        return value.bits_;
    }

    template <numeric_format F>
    CANN_ASC_STL_DETAIL_NUMERIC_API static constexpr numeric_storage<F> make(
        typename numeric_descriptor<F>::storage_type bits) noexcept
    {
        return numeric_storage<F>(bits);
    }
};

static_assert(__CHAR_BIT__ == 8, "numeric_types requires eight-bit bytes");
static_assert(sizeof(asc::std::uint16_t) == 2 && alignof(asc::std::uint16_t) == 2,
    "numeric_types requires a two-byte uint16_t ABI");

}  // namespace detail

using float16 = detail::numeric_storage<numeric_format::fp16>;
using bfloat16 = detail::numeric_storage<numeric_format::bf16>;
using float8_e4m3fn = detail::numeric_storage<numeric_format::fp8_e4m3fn>;
using float8_e5m2 = detail::numeric_storage<numeric_format::fp8_e5m2>;
using float8_e8m0 = detail::numeric_storage<numeric_format::fp8_e8m0>;
using hifloat8 = detail::numeric_storage<numeric_format::hif8>;
using float4_e2m1x2 = detail::numeric_storage<numeric_format::fp4_e2m1x2>;
using float4_e1m2x2 = detail::numeric_storage<numeric_format::fp4_e1m2x2>;
using int4x2 = detail::numeric_storage<numeric_format::int4x2>;
using int4 = detail::numeric_storage<numeric_format::int4>;

}  // namespace asc

#endif  // CANN_ASC_STL_ASC___NUMERIC_TYPES_STORAGE_H
