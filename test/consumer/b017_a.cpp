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

/* Copyright 2026 湖北多样性算力应用创新研究院 */
#include <asc/std/complex>
#include <asc/std/ctgmath>
#include <asc/warp>

int asc_stl_b017_consumer_b();
int asc_stl_b017_consumer_a()
{
    constexpr asc::lane_mask mask(7U);
    static_assert(mask.value() == 7U);
    const asc::std::complex<float> value(2.0F, 3.0F);
    return value.real() == 2.0F && asc_stl_b017_consumer_b() == 0 ? 0 : 1;
}
