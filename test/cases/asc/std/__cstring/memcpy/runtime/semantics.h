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

#ifndef ASC_STL_TEST_FOUNDATION_RUNTIME_SEMANTICS_H
#define ASC_STL_TEST_FOUNDATION_RUNTIME_SEMANTICS_H
#include <asc/std/__bit/bit_cast.h>
#include <asc/std/__cstring/memcpy.h>
#include <asc/std/__cstring/memset.h>
#include <asc/std/__floating_point/storage.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__type_traits/is_constant_evaluated.h>
#include <asc/std/__utility/as_const.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/forward_like.h>
#include <asc/std/cstdint>
#include <asc/std/numbers>
#include "../../../../../../support/b010_semantics.h"
#include "../../../../../../support/b011_semantics.h"
namespace asc_stl_foundation_runtime {
struct address_probe {
    CANN_ASC_STL_API address_probe* operator&() noexcept  // NOLINT(runtime/operator)
    {
        return nullptr;
    }
};

CANN_ASC_STL_API void evaluate_core(asc::std::uint32_t* output) noexcept
{
    output[0] = 0x13579BDFU;
    output[1] = 0x1001U;
    output[2] = asc::std::is_constant_evaluated() ? 1U : 0U;
    int value = 17;
    output[3] = 0x1002U;
    output[4] = static_cast<asc::std::uint32_t>(asc::std::as_const(value));
    unsigned char source[6] = {11, 22, 33, 44, 55, 66};
    unsigned char target[8] = {0xA5, 0, 0, 0, 0, 0, 0, 0x5A};
    output[5] = 0x1003U;
    asc::std::memcpy(target + 1, source, 6);
    output[6] = target[0] + target[1] + target[3] + target[6] + target[7];
    output[7] = 0x1004U;
    asc::std::memset(target + 2, 0x7C, 3);
    output[8] = target[1] + target[2] + target[4] + target[5];
    address_probe probe;
    output[9] = 0x1005U;
    output[10] = asc::std::addressof(probe) != nullptr ? 1U : 0U;
    output[11] = 0x1006U;
    output[12] = asc::std::addressof(asc::std::as_const(value)) == asc::std::addressof(value) ? 1U : 0U;
    output[13] = 0xA5A5A5A5U;
    output[14] = 0x5A5A5A5AU;
    output[15] = 0x2468ACE0U;
}

CANN_ASC_STL_API void evaluate_forwarding(asc::std::uint32_t* output) noexcept
{
    // forward/forward_like: reference identity is a language property and the
    // expected values below are independent Host goldens.
    int forward_base = 41;
    output[16] = 0x1007U;
    int& forwarded_lvalue = asc::std::forward<int&>(forward_base);  // NOLINT(build/include_what_you_use)
    output[17] = &forwarded_lvalue == &forward_base ? 1U : 0U;
    output[18] = 0x1008U;
    int&& forwarded_rvalue = asc::std::forward<int>(forward_base);  // NOLINT(build/include_what_you_use)
    output[19] = &forwarded_rvalue == &forward_base ? 1U : 0U;
    output[20] = 0x1009U;
    const int& const_borrowed = asc::std::forward_like<const long&>(forward_base);
    output[21] = &const_borrowed == &forward_base ? 1U : 0U;
    output[22] = 0x100AU;
    int&& move_borrowed = asc::std::forward_like<long&&>(forward_base);
    output[23] = &move_borrowed == &forward_base ? 1U : 0U;
}

CANN_ASC_STL_API void evaluate_numeric(asc::std::uint32_t* output) noexcept
{
    // bit_cast / fp storage / numbers: IEEE 754 bit patterns are
    // the independent goldens, and the numbers paths stay constant-folded or
    // float because ordinary AICore does not deliver runtime double
    // operations.
    output[24] = 0x100BU;
    output[25] = asc::std::bit_cast<asc::std::uint32_t>(2.0f) == 0x40000000u ? 1U : 0U;
    output[26] = 0x100CU;
    output[27] = asc::std::__fp_get_storage(4.0f) == 0x40800000u ? 1U : 0U;
    output[28] = 0x100DU;
    output[29] = asc::std::__fp_from_storage<float>(0x40800000u) == 4.0f ? 1U : 0U;
    output[30] = 0x100EU;
    output[31] = static_cast<unsigned>(asc::std::pi_v<float> * 100.0f) == 314u &&
            static_cast<unsigned>(static_cast<float>(asc::std::numbers::e) * 100.0f) == 271u ?
        1U :
        0U;
}

CANN_ASC_STL_API void evaluate_w03(asc::std::uint32_t* output) noexcept
{
    output[32] = 0x100FU;
    output[33] = asc_stl_b010_test::evaluate_runtime() == 0 ? 1U : 0U;
    output[34] = 0x1010U;
    output[35] = asc::std::__uabs(-23) == 23U ? 1U : 0U;
    output[36] = 0x1011U;
    int ordered[3] = {7, 8, 9};
    auto bounded = asc::std::__make_bounded_iter(ordered + 1, ordered, ordered + 3);
    output[37] = *bounded == 8 ? 1U : 0U;
    output[38] = 0x1012U;
    asc::std::pair<int, long> pair_value(11, 13);
    output[39] = asc::std::get<0>(pair_value) == 11 && asc::std::get<long>(pair_value) == 13 ? 1U : 0U;
    output[40] = 0x1013U;
    output[41] = asc_stl_b011_test::evaluate_runtime_failures();
}

CANN_ASC_STL_API void evaluate(asc::std::uint32_t* output) noexcept
{
    evaluate_core(output);
    evaluate_forwarding(output);
    evaluate_numeric(output);
    evaluate_w03(output);
}
}  // namespace asc_stl_foundation_runtime
#endif
