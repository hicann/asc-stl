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

#include <asc/std/__type_traits/maybe_const.h>

#include <cassert>
#include <type_traits>

int main()
{
    static_assert(std::is_same_v<asc::std::maybe_const<true, int>, const int>);
    static_assert(std::is_same_v<asc::std::maybe_const<false, int>, int>);

    struct Local {};
    static_assert(std::is_same_v<asc::std::maybe_const<true, Local*>, Local* const>);
    static_assert(std::is_same_v<asc::std::maybe_const<false, Local*>, Local*>);
    static_assert(std::is_same_v<asc::std::maybe_const<true, const Local>, const Local>);

    // The value of the boolean parameter fully decides the qualification.
    constexpr bool add_const = true;
    static_assert(std::is_same_v<asc::std::maybe_const<add_const, char>, const char>);
    static_assert(std::is_same_v<asc::std::maybe_const<!add_const, char>, char>);
    return 0;
}
