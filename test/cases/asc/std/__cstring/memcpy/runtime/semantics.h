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
#include <asc/std/__cstring/memcpy.h>
#include <asc/std/__cstring/memset.h>
#include <asc/std/__memory/addressof.h>
#include <asc/std/__type_traits/is_constant_evaluated.h>
#include <asc/std/__utility/as_const.h>
#include <asc/std/cstdint>
namespace asc_stl_foundation_runtime {
struct address_probe {
    CANN_ASC_STL_API address_probe* operator&() noexcept  // NOLINT(runtime/operator)
    {
        return nullptr;
    }
};
CANN_ASC_STL_API void evaluate(asc::std::uint32_t* output) noexcept
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
}  // namespace asc_stl_foundation_runtime
#endif
