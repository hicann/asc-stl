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

#include <asc/std/compare>
#include "device_checks.h"

namespace s = asc::std;
using strong = s::strong_ordering;
using weak = s::weak_ordering;
using partial = s::partial_ordering;
static_assert(
    s::is_lt(strong::less) && s::is_eq(strong::equal) && s::is_eq(strong::equivalent) && s::is_gt(strong::greater));
static_assert(s::is_lt(weak::less) && s::is_eq(weak::equivalent) && s::is_gt(weak::greater));
static_assert(s::is_lt(partial::less) && s::is_eq(partial::equivalent) && s::is_gt(partial::greater));
static_assert(s::is_neq(partial::unordered) && !s::is_lt(partial::unordered) && !s::is_gt(partial::unordered) &&
    !s::is_lteq(partial::unordered) && !s::is_gteq(partial::unordered));

int main()
{
    return asc_stl_test_compare::check();
}
