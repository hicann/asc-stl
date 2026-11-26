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

#include <asc/std/ranges>

// Exercise the public algorithm declarations when a range adaptor is included first.
#include <asc/std/algorithm>

int main()
{
    int data[] = {2, 3, 5, 8};
    const auto odd = [](int i) { return (i & 1) != 0; };
    if (asc::std::find_if(data, data + 4, odd) != data + 1 || asc::std::find_if(data, data, odd) != data)
        return 1;
    auto filtered = data | asc::std::ranges::views::filter(odd);
    auto pos = filtered.begin();
    if (pos == filtered.end() || *pos++ != 3 || pos == filtered.end() || *pos++ != 5 || pos != filtered.end())
        return 2;
    return asc::std::ranges::find_if(data, odd) == data + 1 ? 0 : 3;
}
