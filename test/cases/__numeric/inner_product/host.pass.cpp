/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#include <asc/std/__numeric/inner_product.h>
struct Add {
    constexpr int operator()(int a, int b) const
    {
        return a + b;
    }
};
struct Difference {
    constexpr int operator()(int a, int b) const
    {
        return a - b;
    }
};
constexpr bool test_inner_product()
{
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    return asc::std::inner_product(a, a + 3, b, 2) == 34 &&
        asc::std::inner_product(a, a + 3, b, 10, Add{}, Difference{}) == 1;
}
static_assert(test_inner_product());
int main()
{
    return test_inner_product() ? 0 : 1;
}
