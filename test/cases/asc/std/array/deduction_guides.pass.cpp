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

#include <asc/std/array>
#include <asc/std/type_traits>
namespace s = asc::std;
int main()
{
    const short first = -7;
    s::array items{first, short{0}, short{5}};
    s::array singleton{first};
    static_assert(s::is_same_v<decltype(items), s::array<short, 3>>);
    static_assert(s::is_same_v<decltype(singleton), s::array<short, 1>>);
    return items[0] == -7 && items[1] == 0 && items[2] == 5 && singleton[0] == -7 ? 0 : 1;
}
