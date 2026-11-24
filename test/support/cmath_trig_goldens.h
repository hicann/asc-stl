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

#ifndef ASC_STL_TEST_CMATH_TRIG_GOLDENS_H
#define ASC_STL_TEST_CMATH_TRIG_GOLDENS_H

// Host-only data: 150-digit decimal Chudnovsky/Taylor reference, rounded to float.
namespace asc_stl_cmath_test {
inline constexpr float trig_goldens[][3] = {
    {0x0.0p+0f, 0x0.0p+0f, 0x1.0000000000000p+0f},
    {-0x0.0p+0f, -0x0.0p+0f, 0x1.0000000000000p+0f},
    {0x1.0000000000000p-149f, 0x1.0000000000000p-149f, 0x1.0000000000000p+0f},
    {-0x1.0000000000000p-149f, -0x1.0000000000000p-149f, 0x1.0000000000000p+0f},
    {0x1.0000000000000p-126f, 0x1.0000000000000p-126f, 0x1.0000000000000p+0f},
    {-0x1.0000000000000p-126f, -0x1.0000000000000p-126f, 0x1.0000000000000p+0f},
    {0x1.0000000000000p-1f, 0x1.eaee880000000p-2f, 0x1.c152800000000p-1f},
    {-0x1.0000000000000p-1f, -0x1.eaee880000000p-2f, 0x1.c152800000000p-1f},
    {0x1.0000000000000p+0f, 0x1.aed5480000000p-1f, 0x1.14a2800000000p-1f},
    {-0x1.0000000000000p+0f, -0x1.aed5480000000p-1f, 0x1.14a2800000000p-1f},
    {0x1.921fb60000000p+0f, 0x1.0000000000000p+0f, -0x1.777a5c0000000p-25f},
    {-0x1.921fb60000000p+0f, -0x1.0000000000000p+0f, -0x1.777a5c0000000p-25f},
    {0x1.17340e0000000p+16f, -0x1.fcf0000000000p-1f, 0x1.bf54200000000p-4f},
    {0x1.1734100000000p+16f, -0x1.fc7c320000000p-1f, 0x1.df1f8c0000000p-4f},
    {0x1.1734120000000p+16f, -0x1.fc00720000000p-1f, 0x1.fee37a0000000p-4f},
    {0x1.5af1d80000000p+66f, 0x1.502ad20000000p-1f, 0x1.822e460000000p-1f},
    {-0x1.5af1d80000000p+66f, -0x1.502ad20000000p-1f, 0x1.822e460000000p-1f},
    {0x1.93e5940000000p+99f, -0x1.9513600000000p-1f, -0x1.3924440000000p-1f},
    {0x1.fffffe0000000p+127f, -0x1.0b33660000000p-1f, 0x1.b4bf2c0000000p-1f},
    {-0x1.fffffe0000000p+127f, 0x1.0b33660000000p-1f, 0x1.b4bf2c0000000p-1f},
    {__builtin_inff(), __builtin_nanf(""), __builtin_nanf("")},
    {-__builtin_inff(), __builtin_nanf(""), __builtin_nanf("")},
    {__builtin_nanf(""), __builtin_nanf(""), __builtin_nanf("")},
};
}  // namespace asc_stl_cmath_test

#endif  // ASC_STL_TEST_CMATH_TRIG_GOLDENS_H
