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

#include <asc/std/unordered_set>
#include "../../../../support/b028_allocator.h"
struct H {
    unsigned long operator()(int x) const
    {
        return x;
    }
};
struct E {
    bool operator()(int a, int b) const
    {
        return a == b;
    }
};
using A = asc_stl_b028_test::arena_allocator<int>;
using C = asc::std::unordered_set<int, H, E, A>;
void fail(C& x)
{
    C y(x);
}
