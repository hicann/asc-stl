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

#include <asc/std/__utility/in_place.h>

#include <iostream>

int main()
{
    int failures = 0;
    failures += asc::std::__is_asc_std_inplace_type_v<asc::std::in_place_type_t<int>> ? 0 : 1;
    failures += asc::std::__is_asc_std_inplace_index_v<asc::std::in_place_index_t<2>> ? 0 : 1;
    failures += !asc::std::__is_asc_std_inplace_type_v<int> ? 0 : 1;
    (void)asc::std::in_place;
    (void)asc::in_place_from;
    (void)asc::in_place_from_type<int>;
    std::cout << "[host][in_place] failures=" << failures << '\n';
    return failures == 0 ? 0 : 1;
}
