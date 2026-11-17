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

#include <asc/std/version>

// Exercise the runtime-only bit_cast path, including an upper-endpoint
// correction rather than merely including the public random header.
#undef CANN_ASC_STL_DETAIL_BUILTIN_BIT_CAST
#undef CANN_ASC_STL_DETAIL_CONSTEXPR_BIT_CAST
#undef CANN_ASC_STL_DETAIL_HAS_CONSTEXPR_BIT_CAST
#undef CANN_ASC_STL_LIB_bit_cast
#define CANN_ASC_STL_DETAIL_CONSTEXPR_BIT_CAST
#define CANN_ASC_STL_DETAIL_HAS_CONSTEXPR_BIT_CAST() 0

#include <asc/std/random>

struct MaximumDraw {
    using result_type = unsigned int;
    static constexpr result_type min() noexcept
    {
        return 0;
    }
    static constexpr result_type max() noexcept
    {
        return 0xffffffffu;
    }
    result_type operator()() noexcept
    {
        return max();
    }
};

int main()
{
    MaximumDraw engine;
    asc::std::uniform_real_distribution<float> distribution(2.0f, 5.0f);
    const float ordinary = distribution(engine);
    using Parameters = asc::std::uniform_real_distribution<float>::param_type;
    const float narrow = distribution(engine, Parameters(1.0f, 0x1.000002p+0f));
    // Both raw affine expressions round to b. Independent hexadecimal
    // constants name the representable predecessor of each upper endpoint.
    return ordinary != 0x1.3ffffep+2f || narrow != 1.0f || distribution.a() != 2.0f || distribution.b() != 5.0f;
}
