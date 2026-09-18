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

#include <asc/std/__type_traits/can_extract_key.h>

#include <iostream>

constexpr int key_tag(asc::std::__extract_key_fail_tag)
{
    return 0;
}
constexpr int key_tag(asc::std::__extract_key_self_tag)
{
    return 1;
}
constexpr int key_tag(asc::std::__extract_key_first_tag)
{
    return 2;
}

int main()
{
    int failures = 0;
    failures += key_tag(asc::std::__can_extract_key<int, int>{}) == 1 ? 0 : 1;
    failures += key_tag(asc::std::__can_extract_key<asc::std::pair<const int, float>, int>{}) == 2 ? 0 : 1;
    failures += key_tag(asc::std::__can_extract_key<float, int>{}) == 0 ? 0 : 1;
    failures += asc::std::__can_extract_map_key<int, int, asc::std::pair<const int, float>>::value ? 0 : 1;
    failures += !asc::std::__can_extract_map_key<int, int, int>::value ? 0 : 1;
    std::cout << "[host][can_extract_key] failures=" << failures << '\n';
    return failures == 0 ? 0 : 1;
}
