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

#include <asc/std/__numeric/exclusive_scan.h>

struct Multiply {
    constexpr int operator()(int a, int b) const
    {
        return a * b;
    }
};

constexpr bool test_exclusive_scan()
{
    int input[] = {1, 2, 3, 4};
    int sum[4] = {};
    int product[4] = {};
    auto sum_end = asc::std::exclusive_scan(input, input + 4, sum, 5);
    auto product_end = asc::std::exclusive_scan(input, input + 4, product, 2, Multiply{});
    return sum_end == sum + 4 && product_end == product + 4 && sum[0] == 5 && sum[1] == 6 && sum[2] == 8 &&
        sum[3] == 11 && product[0] == 2 && product[1] == 2 && product[2] == 4 && product[3] == 12;
}

static_assert(test_exclusive_scan());
int main()
{
    return test_exclusive_scan() ? 0 : 1;
}
