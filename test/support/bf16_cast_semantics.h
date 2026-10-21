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

#ifndef ASC_STL_TEST_BF16_CAST_SEMANTICS_H
#define ASC_STL_TEST_BF16_CAST_SEMANTICS_H

#include <asc/std/__floating_point/cast.h>

namespace asc_stl_bf16_cast_test {

struct encode_case {
    asc::std::uint32_t binary32;
    asc::std::uint16_t bfloat16;
};

struct decode_case {
    asc::std::uint16_t bfloat16;
    asc::std::uint32_t binary32;
};

template <class Operation>
CANN_ASC_STL_API unsigned check_encoding(Operation operation)
{
    // Independent IEEE bit goldens: ties alternate their retained low bit,
    // including the zero/subnormal, subnormal/normal and overflow boundaries.
    const encode_case cases[] = {{0x00000000U, 0x0000U}, {0x80000000U, 0x8000U}, {0x00000001U, 0x0000U},
        {0x00008000U, 0x0000U}, {0x00008001U, 0x0001U}, {0x00010000U, 0x0001U}, {0x00017fffU, 0x0001U},
        {0x00018000U, 0x0002U}, {0x00028000U, 0x0002U}, {0x007f8000U, 0x0080U}, {0x00800000U, 0x0080U},
        {0x3f807fffU, 0x3f80U}, {0x3f808000U, 0x3f80U}, {0x3f808001U, 0x3f81U}, {0x3f818000U, 0x3f82U},
        {0xbf808000U, 0xbf80U}, {0xbf818000U, 0xbf82U}, {0x7f7f7fffU, 0x7f7fU}, {0x7f7f8000U, 0x7f80U},
        {0x7f800000U, 0x7f80U}, {0xff800000U, 0xff80U}, {0x7fc12345U, 0x7fc1U}, {0x7f800001U, 0x7fc0U},
        {0xff800001U, 0xffc0U}, {0x7fa12345U, 0x7fe1U}};
    unsigned failures = 0;
    for (const auto& item : cases) {
        volatile asc::std::uint32_t materialized = item.binary32;
        const float input = asc::std::bit_cast<float>(static_cast<asc::std::uint32_t>(materialized));
        failures += operation(input) != item.bfloat16;
    }
    return failures;
}

template <class Operation>
CANN_ASC_STL_API unsigned check_decoding(Operation operation)
{
    const decode_case cases[] = {{0x0000U, 0x00000000U}, {0x8000U, 0x80000000U}, {0x0001U, 0x00010000U},
        {0x8001U, 0x80010000U}, {0x007fU, 0x007f0000U}, {0x0080U, 0x00800000U}, {0x3f80U, 0x3f800000U},
        {0xbf80U, 0xbf800000U}, {0x7f7fU, 0x7f7f0000U}, {0x7f80U, 0x7f800000U}, {0xff80U, 0xff800000U},
        {0x7fc5U, 0x7fc50000U}, {0x7f81U, 0x7f810000U}};
    unsigned failures = 0;
    for (const auto& item : cases) {
        volatile asc::std::uint16_t materialized = item.bfloat16;
        const float output = operation(static_cast<asc::std::uint16_t>(materialized));
        failures += asc::std::bit_cast<asc::std::uint32_t>(output) != item.binary32;
    }
    return failures;
}

struct software_encode {
    CANN_ASC_STL_API asc::std::uint16_t operator()(float input) const
    {
        return asc::std::__detail::__bf16_encode(input);
    }
};

struct software_decode {
    CANN_ASC_STL_API float operator()(asc::std::uint16_t input) const
    {
        return asc::std::__detail::__bf16_decode(input);
    }
};

#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION() && CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
struct simd_encode {
    CANN_ASC_STL_DEVICE_API asc::std::uint16_t operator()(float input) const
    {
        return asc::std::__fp_get_storage(asc::std::__fp_cast<bfloat16_t>(input));
    }
};

struct simd_decode {
    CANN_ASC_STL_DEVICE_API float operator()(asc::std::uint16_t input) const
    {
        return asc::std::__fp_cast<float>(asc::std::__fp_from_storage<bfloat16_t>(input));
    }
};
#endif

CANN_ASC_STL_DEVICE_API unsigned evaluate()
{
    unsigned failures = check_encoding(software_encode{}) + check_decoding(software_decode{});
#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION() && CANN_ASC_STL_DETAIL_HAS_BFLOAT16()
    failures += check_encoding(simd_encode{}) + check_decoding(simd_decode{});
    const auto payload = asc::std::__fp_from_storage<bfloat16_t>(asc::std::uint16_t{0x7f81U});
    failures += asc::std::__fp_get_storage(asc::std::__fp_cast<bfloat16_t>(payload)) != 0x7f81U;
#endif
    return failures;
}

}  // namespace asc_stl_bf16_cast_test

#endif  // ASC_STL_TEST_BF16_CAST_SEMANTICS_H
