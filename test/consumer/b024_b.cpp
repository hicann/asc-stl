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

#include <asc/std/__expected/expected.h>
#include <asc/std/__variant/comparison.h>
#include <asc/std/__algorithm/is_permutation.h>
#include <asc/std/iterator>

int asc_stl_b024_consumer_b()
{
    const asc::std::expected<int, int> value(21);
    const asc::std::expected<int, int> failure(asc::std::unexpect, 2);
    int data[] = {3, 1, 2};
    const bool ordered = asc::std::is_permutation(data, data + 3, data, data + 3);
    const asc::std::variant<int, double> left(1);
    const asc::std::variant<int, double> right(2);
    return value.has_value() && *value == 21 && failure.error() == 2 && ordered && left < right &&
            asc::std::size(data) == 3 ?
        0 :
        1;
}
