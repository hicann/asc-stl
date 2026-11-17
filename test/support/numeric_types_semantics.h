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

#ifndef ASC_STL_TEST_SUPPORT_NUMERIC_TYPES_SEMANTICS_H
#define ASC_STL_TEST_SUPPORT_NUMERIC_TYPES_SEMANTICS_H

#include <asc/numeric_types>
#include <asc/std/type_traits>

namespace numeric_types_test {

template <class T, unsigned Size, unsigned Alignment, unsigned Bits, unsigned Lanes>
struct properties {
    static_assert(sizeof(T) == Size && alignof(T) == Alignment);
    static_assert(asc::std::is_standard_layout_v<T>);
    static_assert(asc::std::is_trivially_constructible_v<T>);
    static_assert(asc::std::is_trivially_copyable_v<T>);
    static_assert(asc::std::is_trivially_copy_constructible_v<T>);
    static_assert(asc::std::is_trivially_move_constructible_v<T>);
    static_assert(asc::std::is_trivially_copy_assignable_v<T>);
    static_assert(asc::std::is_trivially_move_assignable_v<T>);
    static_assert(asc::std::is_trivially_destructible_v<T>);
    static_assert(!asc::std::is_constructible_v<T, float> && !asc::std::is_convertible_v<T, float>);
    static_assert(!asc::std::is_integral_v<T> && !asc::std::is_floating_point_v<T> && !asc::std::is_arithmetic_v<T>);
    static_assert(asc::numeric_format_traits<T>::bits == Bits);
    static_assert(asc::numeric_format_traits<T>::storage_bits == Size * 8);
    static_assert(asc::numeric_format_traits<T>::lanes == Lanes);
    static_assert(asc::to_bits(T{}) == 0);
};
static_assert(sizeof(properties<asc::float16, 2, 2, 16, 1>) != 0);
static_assert(sizeof(properties<asc::bfloat16, 2, 2, 16, 1>) != 0);
static_assert(sizeof(properties<asc::float8_e4m3fn, 1, 1, 8, 1>) != 0);
static_assert(sizeof(properties<asc::float8_e5m2, 1, 1, 8, 1>) != 0);
static_assert(sizeof(properties<asc::float8_e8m0, 1, 1, 8, 1>) != 0);
static_assert(sizeof(properties<asc::hifloat8, 1, 1, 8, 1>) != 0);
static_assert(sizeof(properties<asc::float4_e2m1x2, 1, 1, 4, 2>) != 0);
static_assert(sizeof(properties<asc::float4_e1m2x2, 1, 1, 4, 2>) != 0);
static_assert(sizeof(properties<asc::int4, 1, 1, 4, 1>) != 0);
static_assert(sizeof(properties<asc::int4x2, 1, 1, 4, 2>) != 0);
static_assert(asc::to_bits(asc::pack_elements<asc::int4x2>(8, 7)) == 0x78);
static_assert(asc::unpack_element(asc::from_bits<asc::float4_e2m1x2>(0xa3), 0) == 3);
static_assert(asc::unpack_element(asc::from_bits<asc::float4_e1m2x2>(0xa3), 1) == 10);

#if defined(__NPU_ARCH__) && __NPU_ARCH__ == 3510
inline constexpr bool expected_native = true;
#else
inline constexpr bool expected_native = false;
#endif
static_assert(asc::numeric_format_traits<asc::float16>::has_native_type == expected_native);
static_assert(asc::numeric_format_traits<asc::bfloat16>::has_native_type == expected_native);
static_assert(asc::numeric_format_traits<asc::float8_e4m3fn>::has_native_type == expected_native);
static_assert(asc::numeric_format_traits<asc::float8_e5m2>::has_native_type == expected_native);
static_assert(asc::numeric_format_traits<asc::float8_e8m0>::has_native_type == expected_native);
static_assert(asc::numeric_format_traits<asc::hifloat8>::has_native_type == expected_native);
static_assert(asc::numeric_format_traits<asc::float4_e2m1x2>::has_native_type == expected_native);
static_assert(asc::numeric_format_traits<asc::float4_e1m2x2>::has_native_type == expected_native);
static_assert(!asc::numeric_format_traits<asc::int4>::has_native_type);
static_assert(asc::numeric_format_traits<asc::int4x2>::has_native_type ==
    (expected_native && CANN_ASC_STL_DETAIL_SIMD_COMPILATION()));

using R = asc::rounding_mode;
using S = asc::saturation_mode;

template <class To, class From, R Round, S Sat, class = void>
struct callable : asc::std::false_type {};
template <class To, class From, R Round, S Sat>
struct callable<To, From, Round, Sat,
    asc::std::void_t<decltype(asc::numeric_convert<To, Round, Sat>(asc::std::declval<From>()))>> : asc::std::true_type {
};

template <class T>
inline constexpr bool scalar_float = asc::std::is_same_v<T, asc::float16> || asc::std::is_same_v<T, asc::bfloat16> ||
    asc::std::is_same_v<T, asc::float8_e4m3fn> || asc::std::is_same_v<T, asc::float8_e5m2>;

template <class To, class From, R Round, S Sat>
CANN_ASC_STL_API constexpr bool query_pair()
{
    constexpr bool expected = (asc::std::is_same_v<From, float> && scalar_float<To>) ||
        (asc::std::is_same_v<To, float> && scalar_float<From>) ||
        (asc::std::is_same_v<To, asc::int4> && asc::std::is_same_v<From, asc::std::int32_t> && Sat == S::finite) ||
        (asc::std::is_same_v<From, asc::int4> && asc::std::is_same_v<To, asc::std::int32_t>);
    static_assert(asc::is_numeric_conversion_supported_v<To, From, Round, Sat> == expected);
    static_assert(callable<To, From, Round, Sat>::value == expected);
    return true;
}

template <class To, class From>
CANN_ASC_STL_API constexpr bool query_options()
{
    return query_pair<To, From, R::nearest_even, S::none>() && query_pair<To, From, R::nearest_even, S::finite>() &&
        query_pair<To, From, R::toward_zero, S::none>() && query_pair<To, From, R::toward_zero, S::finite>() &&
        query_pair<To, From, R::toward_positive, S::none>() && query_pair<To, From, R::toward_positive, S::finite>() &&
        query_pair<To, From, R::toward_negative, S::none>() && query_pair<To, From, R::toward_negative, S::finite>();
}

template <class To, class... From>
CANN_ASC_STL_API constexpr bool query_row()
{
    return (query_options<To, From>() && ...);
}

template <class... T>
struct query_matrix {
    template <class To>
    CANN_ASC_STL_API static constexpr bool row()
    {
        return query_row<To, T...>();
    }
    static_assert((row<T>() && ...));
};
static_assert(sizeof(query_matrix<float, asc::std::int32_t, double, asc::float16, asc::bfloat16, asc::float8_e4m3fn,
                  asc::float8_e5m2, asc::float8_e8m0, asc::hifloat8, asc::float4_e2m1x2, asc::float4_e1m2x2, asc::int4,
                  asc::int4x2>) != 0);
static_assert(!asc::is_numeric_conversion_supported_v<const asc::float16, float>);
static_assert(!asc::is_numeric_conversion_supported_v<asc::float16, const float>);
static_assert(!asc::is_numeric_conversion_supported_v<asc::float16, float&>);
static_assert(!asc::is_numeric_conversion_supported_v<asc::float16, float, static_cast<R>(42)>);
static_assert(!asc::is_numeric_conversion_supported_v<asc::float16, float, R::nearest_even, static_cast<S>(42)>);

// Host and hardware exhaust the word encodings. The simulator uses a bounded
// word sample plus explicit special encodings; byte formats remain exhaustive.
template <class T>
CANN_ASC_STL_API constexpr unsigned representation_count()
{
    if constexpr (asc::std::is_same_v<T, asc::int4>)
        return 16;
#if defined(ASC_STL_NUMERIC_TYPES_SIMULATION)
    if constexpr (sizeof(T) == 2)
        return 272;
#endif
    return 1U << (sizeof(T) * 8);
}

template <class T>
CANN_ASC_STL_API constexpr unsigned representation_encoding(unsigned index)
{
#if defined(ASC_STL_NUMERIC_TYPES_SIMULATION)
    if constexpr (sizeof(T) == 2) {
        if (index < 256)
            return index * 257;
        switch (index) {
            case 256:
                return 0x0001;
            case 257:
                return 0x03ff;
            case 258:
                return 0x0400;
            case 259:
                return 0x3c00;
            case 260:
                return 0x7bff;
            case 261:
                return 0x7c00;
            case 262:
                return 0x7c01;
            case 263:
                return 0x7e15;
            case 264:
                return 0x7f7f;
            case 265:
                return 0x7f80;
            case 266:
                return 0x7f81;
            case 267:
                return 0x8000;
            case 268:
                return 0x8001;
            case 269:
                return 0xfc00;
            case 270:
                return 0xfc01;
            case 271:
                return 0xffc1;
            default:
                return 0;
        }
    }
#endif
    return index;
}

template <class T>
CANN_ASC_STL_API unsigned bits(unsigned first = 0, unsigned stride = 1, unsigned limit = 65536)
{
    using Storage = typename asc::numeric_format_traits<T>::storage_type;
    const unsigned count = representation_count<T>();
    unsigned failures = 0;
    for (unsigned raw = first; raw < count && raw < limit; raw += stride) {
        const unsigned code = representation_encoding<T>(raw);
        const auto original = asc::from_bits<T>(static_cast<Storage>(code));
        T copied(original);
        T assigned{};
        assigned = copied;
        failures += asc::to_bits(assigned) != code;
        failures += asc::std::bit_cast<Storage>(assigned) != code;
    }
    return failures;
}

template <class T>
CANN_ASC_STL_API unsigned packed(unsigned first = 0, unsigned stride = 1, unsigned limit = 65536)
{
    unsigned failures = 0;
    for (unsigned raw = first; raw < 256 && raw < limit; raw += stride) {
        const auto value = asc::pack_elements<T>(raw % 16, raw / 16);
        failures += asc::to_bits(value) != raw;
        failures += asc::unpack_element(value, 0) != raw % 16;
        failures += asc::unpack_element(value, 1) != raw / 16;
    }
    return failures;
}

CANN_ASC_STL_API unsigned representations(unsigned first = 0, unsigned stride = 1, unsigned limit = 65536)
{
    return bits<asc::float16>(first, stride, limit) + bits<asc::bfloat16>(first, stride, limit) +
        bits<asc::float8_e4m3fn>(first, stride, limit) + bits<asc::float8_e5m2>(first, stride, limit) +
        bits<asc::float8_e8m0>(first, stride, limit) + bits<asc::hifloat8>(first, stride, limit) +
        bits<asc::float4_e2m1x2>(first, stride, limit) + bits<asc::float4_e1m2x2>(first, stride, limit) +
        bits<asc::int4>(first, stride, limit) + bits<asc::int4x2>(first, stride, limit) +
        packed<asc::float4_e2m1x2>(first, stride, limit) + packed<asc::float4_e1m2x2>(first, stride, limit) +
        packed<asc::int4x2>(first, stride, limit);
}

template <R Round>
CANN_ASC_STL_API unsigned integers()
{
    unsigned failures = 0;
    for (int input = -100; input <= 100; ++input) {
        const auto value = asc::numeric_convert<asc::int4, Round, S::finite>(input);
        const int expected = input < -8 ? -8 : input > 7 ? 7 : input;
        failures += asc::to_bits(value) != (static_cast<unsigned>(expected) & 15);
    }
    failures +=
        asc::to_bits(asc::numeric_convert<asc::int4, Round, S::finite>(asc::std::int32_t{-2147483647 - 1})) != 8;
    failures += asc::to_bits(asc::numeric_convert<asc::int4, Round, S::finite>(asc::std::int32_t{2147483647})) != 7;
    for (unsigned code = 0; code < 16; ++code) {
        const auto value = asc::from_bits<asc::int4>(code);
        const int expected = code < 8 ? static_cast<int>(code) : static_cast<int>(code) - 16;
        failures += asc::numeric_convert<asc::std::int32_t, Round>(value) != expected;
        failures += asc::numeric_convert<asc::std::int32_t, Round, S::finite>(value) != expected;
    }
    return failures;
}

template <class T>
CANN_ASC_STL_API unsigned native_bits(unsigned first = 0, unsigned stride = 1, unsigned limit = 65536)
{
    if constexpr (!asc::numeric_format_traits<T>::has_native_type) {
        return 0;
    } else {
        using Storage = typename asc::numeric_format_traits<T>::storage_type;
        using Native = asc::native_numeric_t<T>;
        unsigned failures = 0;
        for (unsigned raw = first; raw < representation_count<T>() && raw < limit; raw += stride) {
            const unsigned code = representation_encoding<T>(raw);
            const auto native = asc::to_native_numeric(asc::from_bits<T>(static_cast<Storage>(code)));
            if constexpr (asc::std::is_trivially_copyable_v<Native>) {
                failures += asc::std::bit_cast<Storage>(native) != code;
                const auto independent = asc::std::bit_cast<Native>(static_cast<Storage>(code));
                failures += asc::to_bits(asc::from_native_numeric<T>(independent)) != code;
            } else {
                failures += static_cast<unsigned char>(native.val) != code;
                Native independent;
                independent.val = asc::std::bit_cast<char>(static_cast<unsigned char>(code));
                failures += asc::to_bits(asc::from_native_numeric<T>(independent)) != code;
            }
        }
        return failures;
    }
}

CANN_ASC_STL_API unsigned native_representations(unsigned first = 0, unsigned stride = 1, unsigned limit = 65536)
{
    return native_bits<asc::float16>(first, stride, limit) + native_bits<asc::bfloat16>(first, stride, limit) +
        native_bits<asc::float8_e4m3fn>(first, stride, limit) + native_bits<asc::float8_e5m2>(first, stride, limit) +
        native_bits<asc::float8_e8m0>(first, stride, limit) + native_bits<asc::hifloat8>(first, stride, limit) +
        native_bits<asc::float4_e2m1x2>(first, stride, limit) + native_bits<asc::float4_e1m2x2>(first, stride, limit) +
        native_bits<asc::int4x2>(first, stride, limit);
}

}  // namespace numeric_types_test

#endif  // ASC_STL_TEST_SUPPORT_NUMERIC_TYPES_SEMANTICS_H
