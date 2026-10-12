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

#include <asc/std/__functional/bind_front.h>
#include <asc/std/__numeric/accumulate.h>
#include <asc/std/__numeric/exclusive_scan.h>
#include <asc/std/__numeric/inner_product.h>
#include <asc/std/__compare/compare_fallback.h>
#include <asc/std/__utility/monostate.h>
#include <asc/std/__bit/has_single_bit.h>

int asc_stl_b025_consumer_b()
{
    constexpr int data[5]{1, 2, 3, 4, 5};
    auto leading = asc::std::bind_front([](int first, int second) { return first * 10 + second; }, 4);
    int scanned[5]{};
    (void)asc::std::exclusive_scan(data, data + 5, scanned, 10);
    const asc::std::monostate empty_state{};
    return leading(2) == 42 && asc::std::accumulate(data, data + 5, 0) == 15 &&
            asc::std::inner_product(data, data + 3, data, 0) == 14 && asc::std::has_single_bit(4u) &&
            asc::std::compare_weak_order_fallback{}(1, 2) == asc::std::weak_ordering::less &&
            empty_state == asc::std::monostate{} ?
        0 :
        1;
}
