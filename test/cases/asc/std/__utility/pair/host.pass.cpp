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

#include <asc/std/utility>
#include <asc/std/type_traits>
#include "support/b010_semantics.h"
#include "../../utility/support/pair_piecewise_regression.h"

struct NonTupleSource {};
using IntPair = asc::std::pair<int, int>;
static_assert(!asc::std::is_constructible_v<IntPair, int>);
static_assert(!asc::std::is_constructible_v<IntPair, NonTupleSource>);
static_assert(!asc::std::is_assignable_v<IntPair&, int>);
static_assert(!asc::std::is_assignable_v<IntPair&, NonTupleSource>);
static_assert(asc::std::is_constructible_v<IntPair, const IntPair&>);
static_assert(asc::std::is_constructible_v<IntPair, asc::std::tuple<int, int>>);
static_assert(asc::std::is_assignable_v<IntPair&, asc::std::tuple<int, int>>);

int main()
{
    return asc_stl_b010_test::evaluate_runtime() + (asc_stl_pair_piecewise_test::evaluate(7) ? 0 : 101);
}
