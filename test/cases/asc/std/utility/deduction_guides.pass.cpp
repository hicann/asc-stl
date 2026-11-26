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

#include <asc/std/utility>
#include <asc/std/type_traits>
namespace s = asc::std;
int main()
{
    char text[] = "ok";
    const long n = -8;
    s::pair p(text, n);
    static_assert(s::is_same_v<decltype(p), s::pair<char*, long>>);
    p.first[0] = 'O';
    return text[0] == 'O' && p.second == -8 ? 0 : 1;
}
