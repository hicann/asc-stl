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
#include <asc/cmath>
#include <asc/work_queue>
#include <asc/std/__charconv/from_chars.h>
#include <asc/std/__cwctype/classification.h>
#include <asc/std/__cwctype/descriptors.h>
#include <asc/std/__numeric/reduce.h>
#include <asc/std/__numeric/transform_reduce.h>

#include <cstdint>

int asc_stl_b026_consumer_b();

int asc_stl_b026_consumer_a()
{
    // The two new public entries plus the B026 private roots parse and keep
    // their exact vocabulary on the installed tree; the work-queue claim and
    // the sincos float link run in the dedicated runtime payloads instead.
    static_assert(asc::ceil_div(7, 3) == 3);
    static_assert(asc::mul_hi(std::uint8_t{0xFF}, std::uint8_t{0xFF}) == std::uint8_t{0xFE});
    double sine = 0.0;
    double cosine = 0.0;
    asc::sincos(0.0, &sine, &cosine);
    constexpr asc::work_chunk<unsigned> chunk{3, 9};
    static_assert(!chunk.empty() && chunk.size() == 6);
    asc::detail::work_cursor cursor{0, 4, 2};
    const auto queue = asc::make_work_queue<unsigned>(cursor, 4u, 2u);
    asc::work_chunk<unsigned> claimed{};
    unsigned covered = 0;
    while (asc::acquire_work(queue, claimed)) {
        covered += claimed.size();
    }
    const int data[4]{1, 2, 3, 4};
    if (asc::std::reduce(data, data + 4, 0) != 10 || asc::std::transform_reduce(data, data + 4, data, 0) != 30) {
        return 1;
    }
    if (!asc::std::iswalpha(L'a') || asc::std::wctype("alpha") == 0) {
        return 1;
    }
    std::int32_t parsed = 0;
    return covered == 4 && asc::std::from_chars("42", "42" + 2, parsed).ptr != nullptr && parsed == 42 ?
        asc_stl_b026_consumer_b() :
        1;
}
