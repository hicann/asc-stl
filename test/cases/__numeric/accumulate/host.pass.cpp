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

struct Product {
    constexpr int operator()(int a, int b) const
    {
        return a * b;
    }
};

constexpr bool test_accumulate()
{
    int values[] = {1, 2, 3, 4};
    return asc::std::accumulate(values, values + 4, 5) == 15 &&
        asc::std::accumulate(values, values + 4, 1, Product{}) == 24;
}

static_assert(test_accumulate());
int main()
{
    return test_accumulate() ? 0 : 1;
}
