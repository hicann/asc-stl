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

#include <asc/std/functional>
#include <asc/std/type_traits>
namespace s = asc::std;
int main()
{
    int n = 2;
    const int& ref = n;
    s::reference_wrapper mutable_ref(n);
    s::reference_wrapper const_ref(ref);
    static_assert(s::is_same_v<decltype(mutable_ref), s::reference_wrapper<int>>);
    static_assert(s::is_same_v<decltype(const_ref), s::reference_wrapper<const int>>);
    mutable_ref.get() = -5;
    const int pattern[]{3, 1};
    int haystack[]{2, 3, 1, 4};
    s::default_searcher find(pattern, pattern + 2);
    static_assert(s::is_same_v<decltype(find), s::default_searcher<const int*>>);
    auto result = find(haystack, haystack + 4);
    return const_ref.get() == -5 && result.first == haystack + 1 && result.second == haystack + 3 ? 0 : 1;
}
