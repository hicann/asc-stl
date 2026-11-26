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

#include <asc/std/tuple>
#include <asc/std/type_traits>
namespace s = asc::std;
int main()
{
    const short n = -3;
    s::tuple elements(n, 9L);
    s::tuple copied(elements);
    s::tuple empty{};
    static_assert(s::is_same_v<decltype(elements), s::tuple<short, long>>);
    static_assert(s::is_same_v<decltype(copied), decltype(elements)>);
    static_assert(s::is_same_v<decltype(empty), s::tuple<>>);
    s::get<0>(elements) = 5;
    return s::get<0>(copied) == -3 && s::get<1>(elements) == 9 ? 0 : 1;
}
