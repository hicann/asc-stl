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

#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <list>
namespace s = asc::std;
int main()
{
    std::list<int> data{1};
    s::back_insert_iterator back(data);
    s::front_insert_iterator front(data);
    s::insert_iterator middle(data, data.begin());
    static_assert(s::is_same_v<decltype(back), s::back_insert_iterator<std::list<int>>>);
    static_assert(s::is_same_v<decltype(front), s::front_insert_iterator<std::list<int>>>);
    static_assert(s::is_same_v<decltype(middle), s::insert_iterator<std::list<int>>>);
    *back = 6;
    *front = -2;
    *middle = 3;
    auto pos = data.begin();
    s::counted_iterator counted(pos, 4);
    static_assert(s::is_same_v<decltype(counted), s::counted_iterator<decltype(pos)>>);
    const int expect[]{-2, 3, 1, 6};
    for (int n : expect) {
        if (counted == s::default_sentinel || *counted != n)
            return 1;
        ++counted;
    }
    return counted == s::default_sentinel ? 0 : 2;
}
