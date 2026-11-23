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

#include <asc/argument>
#include <asc/functional>
#include <asc/type_traits>
#include <asc/version>
#include <asc/std/cwctype>
#include <asc/std/new>

struct plus_one {
    constexpr int operator()(int value) const
    {
        return value + 1;
    }
};

int main()
{
    static_assert(asc::args::static_bounds<1, 9>::lower() == 1);
    static_assert(asc::args::constant<7>::value() == 7);
    auto dynamic = asc::args::bounds(2, 8);
    if (dynamic.lower() != 2 || dynamic.upper() != 8)
        return 1;
    asc::args::immediate<int> immediate(4);
    immediate.value() = 5;
    int values[] = {3, 4};
    asc::args::deferred<int> deferred(values);
    asc::args::deferred_sequence<int> sequence(values, 2);
    if (immediate.value() != 5 || deferred.data() != values || sequence.size() != 2)
        return 2;
    if (!asc::always_true{}(1, 2) || asc::always_false{}())
        return 3;
    if (!asc::equal_to_value<int>(4)(4) || asc::minimum<int>{}(5, 2) != 2 || asc::maximum<int>{}(5, 2) != 5)
        return 4;
    if (plus_one{}(8) != 9 || !asc::is_associative_v<asc::minimum<int>, int>)
        return 5;
    static_assert(asc::is_bitwise_comparable_v<int>);
    static_assert(asc::is_trivially_relocatable_v<int>);
    static_assert(!asc::is_extended_floating_point_v<float>);
    if (CANN_ASC_STL < 10000101 || CANN_ASC_STL > 99991231)
        return 6;
    if (!asc::std::iswalpha(L'A') || asc::std::towlower(L'Q') != L'q')
        return 7;
    return 0;
}
