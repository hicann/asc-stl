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

#include <asc/std/__concepts/equality_comparable.h>
struct Eq {
    int v;
    friend constexpr bool operator==(Eq a, Eq b)
    {
        return a.v == b.v;
    }
    friend constexpr bool operator!=(Eq a, Eq b)
    {
        return !(a == b);
    }
};
struct None {};
static_assert(asc::std::equality_comparable<int>);
static_assert(asc::std::equality_comparable<Eq>);
static_assert(asc::std::equality_comparable_with<int, long>);
static_assert(!asc::std::equality_comparable<None>);
int main()
{
    return 0;
}
