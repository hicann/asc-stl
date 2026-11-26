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

#include <asc/std/variant>
#include <initializer_list>

namespace {
using asc::std::get;
using asc::std::get_if;
using asc::std::in_place_index;
using asc::std::in_place_type;
using asc::std::move;
using asc::std::variant;

struct digits {
    int value;
    digits(std::initializer_list<int> list, int bias) : value(bias)
    {
        for (int digit : list)
            value = 10 * value + digit;
    }
};
}  // namespace

int main()
{
    using choice = variant<int, digits>;
    choice index(in_place_index<1>, {2, 4}, 1);
    choice type(in_place_type<digits>, std::initializer_list<int>{}, 9);
    if (get<digits>(index).value != 124 || get<1>(type).value != 9)
        return 1;
    const auto& fixed = index;
    if (get<digits>(fixed).value != 124 || get_if<digits>(&fixed) != &get<1>(fixed) ||
        get_if<1>(&fixed) != &get<digits>(fixed) || get_if<0>(&fixed))
        return 2;
    digits&& mutable_ref = get<digits>(move(index));
    const digits&& fixed_ref = get<1>(move(fixed));
    if (&mutable_ref != &fixed_ref || get<digits>(move(fixed)).value != 124 ||
        get<1>(move(index)).value != 124)  // NOLINT(build/include_what_you_use)
        return 3;
    choice empty_list(6);
    auto& changed = empty_list.emplace<digits>({3, 0}, 2);
    auto& restored = type.emplace<1>(std::initializer_list<int>{}, 8);
    return changed.value == 230 && restored.value == 8 ? 0 : 4;
}
