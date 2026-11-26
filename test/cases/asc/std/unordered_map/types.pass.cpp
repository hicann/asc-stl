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

#include <asc/std/unordered_map>
#include <cstddef>
#include <type_traits>
#include <utility>
#include "device_checks.h"

namespace s = asc::std;

namespace fixture = asc_stl_test_unordered_map;
using element = s::__arena_pair<const int, int>;
using alloc = asc_stl_test::inline_arena_allocator<element>;
using container = s::unordered_map<int, int, fixture::collide, fixture::equal, alloc>;
using iter = container::iterator;
static_assert(std::is_same_v<container::size_type, std::size_t>);
static_assert(std::is_same_v<container::value_type, element>);
static_assert(std::is_same_v<decltype(*std::declval<iter&>()), element&>);
static_assert(std::is_same_v<decltype(std::declval<iter&>().operator->()), element*>);
static_assert(std::is_same_v<decltype(++std::declval<iter&>()), iter&>);

static_assert(!std::is_copy_constructible_v<container> && !std::is_copy_assignable_v<container>);

struct default_key {
    int value;
    default_key() : value(17)
    {}
};
int main()
{
    using pair = s::unordered_map<default_key, int, fixture::collide, fixture::equal, alloc>::value_type;
    pair result{};
    static_assert(!std::is_default_constructible_v<element>);
    return result.first.value != 17 || result.second != 0;
}
