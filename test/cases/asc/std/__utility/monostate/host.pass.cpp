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

#include <asc/std/__utility/monostate.h>

#include <cassert>

int main()
{
    constexpr asc::std::monostate first{};
    constexpr asc::std::monostate second{};
    static_assert(first == second);
    static_assert(!(first != second));
    static_assert(!(first < second));
    static_assert(!(first > second));
    static_assert(first <= second);
    static_assert(first >= second);
    static_assert(sizeof(asc::std::monostate) == 1);
    assert(asc::std::hash<asc::std::monostate>{}(first) == 66740831);
    using result_type = asc::std::hash<asc::std::monostate>::result_type;
    using argument_type = asc::std::hash<asc::std::monostate>::argument_type;
    static_assert(sizeof(result_type) > 0 && sizeof(argument_type) > 0);
    return 0;
}
