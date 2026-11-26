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
#include <asc/std/type_traits>
#include <asc/std/utility>
#include <cassert>
#include "device_checks.h"

int main()
{
    int values[] = {1, 2, 3};
    using subrange = asc::std::ranges::subrange<int*>;
    using endpoints = asc::std::pair<const int*, const int*>;
    const subrange selected(values + 1, values + 3);
    endpoints converted = selected;
    assert(converted.first == values + 1 && converted.second == values + 3);
    endpoints assigned{};
    assigned = selected;
    assert(assigned.first == values + 1 && assigned.second == values + 3);
    const subrange empty(values + 3, values + 3);
    endpoints end = empty;
    assert(end.first == end.second && end.first == values + 3);
    static_assert(!asc::std::is_convertible_v<const subrange&, asc::std::pair<int*, int>>);
    struct base {};
    struct derived : base {};
    using derived_range = asc::std::ranges::subrange<derived*>;
    using sliced = asc::std::pair<base*, base*>;
    static_assert(!asc::std::is_convertible_v<const derived_range&, sliced>);
    static_assert(!asc::std::is_assignable_v<sliced&, const derived_range&>);
    return asc_stl_test_ranges::check();
}
