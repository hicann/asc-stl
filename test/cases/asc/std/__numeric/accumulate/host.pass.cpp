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

#include <asc/std/__numeric/accumulate.h>
#include <asc/std/__numeric/exclusive_scan.h>
#include <asc/std/__numeric/inner_product.h>

#include <cassert>
#include <string>

int main()
{
    constexpr int data[5]{1, 2, 3, 4, 5};

    // accumulate: empty range returns the init value.
    assert(asc::std::accumulate(data, data, 10) == 10);
    assert(asc::std::accumulate(data, data, 0) == 0);
    assert(asc::std::accumulate(data, data + 5, 0) == 15);
    assert(asc::std::accumulate(data, data + 5, -15) == 0);
    assert(asc::std::accumulate(data, data + 5, 1, [](int total, int value) { return total * value; }) == 120);

    const std::string words[3]{"a", "b", "c"};
    assert(asc::std::accumulate(words, words + 3, std::string("x")) == "xabc");

    // exclusive_scan: the init is excluded; the result has the same length.
    int scanned[5]{};
    assert(asc::std::exclusive_scan(data, data + 5, scanned, 10) == scanned + 5);
    assert(scanned[0] == 10 && scanned[1] == 11 && scanned[2] == 13 && scanned[3] == 16 && scanned[4] == 20);
    assert(asc::std::exclusive_scan(data, data, scanned, 7) == scanned);
    int single[1]{};
    assert(asc::std::exclusive_scan(data, data + 1, single, 4) == single + 1 && single[0] == 4);
    assert(asc::std::exclusive_scan(data, data + 5, scanned, 1, [](int total, int value) { return total * value; }) ==
        scanned + 5);
    assert(scanned[0] == 1 && scanned[1] == 1 && scanned[2] == 2 && scanned[3] == 6 && scanned[4] == 24);

    // inner_product: empty range returns the init value.
    assert(asc::std::inner_product(data, data, data, 5) == 5);
    assert(asc::std::inner_product(data, data + 3, data, 0) == 14);
    assert(asc::std::inner_product(data, data + 5, data, 0) == 55);
    assert(asc::std::inner_product(
               data, data + 3, data, 0, [](int total, int value) { return total + value; },
               [](int left, int right) { return left * right + 1; }) == 17);

    constexpr int constant_evaluated = asc::std::accumulate(data, data + 3, 100);
    static_assert(constant_evaluated == 106);
    return 0;
}
