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

#include <asc/std/__algorithm/iter_swap.h>
namespace custom {
struct Iterator {
    int* p;
    constexpr int& operator*() const
    {
        return *p;
    }
};
constexpr void iter_swap(Iterator a, Iterator b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
}  // namespace custom
constexpr bool test_iter_swap()
{
    int values[] = {1, 2, 3};
    asc::std::iter_swap(values, values + 2);
    if (values[0] != 3 || values[2] != 1)
        return false;
    custom::Iterator a{values};
    custom::Iterator b{values + 1};
    asc::std::iter_swap(a, b);
    return values[0] == 2 && values[1] == 3;
}
static_assert(test_iter_swap());
int main()
{
    return test_iter_swap() ? 0 : 1;
}
