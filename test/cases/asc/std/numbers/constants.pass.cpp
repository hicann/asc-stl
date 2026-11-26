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

#include <asc/std/numbers>

// Decimal references carry enough significant digits to round to the target binary formats.
#define CHECK_CONSTANT(name, decimal)                                                 \
    static_assert(asc::std::numbers::name == static_cast<double>(decimal));           \
    static_assert(asc::std::numbers::name##_v<float> == static_cast<float>(decimal)); \
    static_assert(asc::std::name##_v<float> == static_cast<float>(decimal))

CHECK_CONSTANT(e, 2.71828182845904523536L);
CHECK_CONSTANT(log2e, 1.44269504088896340736L);
CHECK_CONSTANT(log10e, 0.43429448190325182765L);
CHECK_CONSTANT(pi, 3.14159265358979323846L);
CHECK_CONSTANT(inv_pi, 0.31830988618379067154L);
CHECK_CONSTANT(inv_sqrtpi, 0.56418958354775628695L);
CHECK_CONSTANT(ln2, 0.69314718055994530942L);
CHECK_CONSTANT(ln10, 2.30258509299404568402L);
CHECK_CONSTANT(sqrt2, 1.41421356237309504880L);
CHECK_CONSTANT(sqrt3, 1.73205080756887729353L);
CHECK_CONSTANT(inv_sqrt3, 0.57735026918962576451L);
CHECK_CONSTANT(egamma, 0.57721566490153286061L);
CHECK_CONSTANT(phi, 1.61803398874989484820L);

int main()
{}
