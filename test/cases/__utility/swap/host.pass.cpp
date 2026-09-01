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

#include <asc/std/__utility/swap.h>

constexpr bool test_swap()
{
    int lhs = 3;
    int rhs = 8;
    asc::std::swap(lhs, rhs);
    int a[] = {1, 2};
    int b[] = {4, 5};
    asc::std::swap(a, b);  // NOLINT(build/include_what_you_use)
    return lhs == 8 && rhs == 3 && a[0] == 4 && a[1] == 5 && b[0] == 1 && b[1] == 2;
}

static_assert(test_swap());

int main()
{
    return test_swap() ? 0 : 1;
}
