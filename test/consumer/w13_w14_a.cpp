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

#include <asc/bit>
#include <asc/utility>
#include <asc/std/cctype>
#include <asc/std/linalg>
#include <asc/std/numeric>
#include <asc/std/random>

int asc_stl_w13_w14_consumer_a()
{
    asc::std::philox4x32 engine;
    return asc::std::isdigit('4') && asc::bitmask<>(4, 4) == 0xf0U && asc::std::gcd(18, 12) == 6 && engine.min() == 0 ?
        0 :
        1;
}
