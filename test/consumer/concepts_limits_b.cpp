/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#include <asc/std/concepts>
#include <asc/std/limits>
#include <asc/std/__iterator/data.h>
#include <asc/std/__iterator/empty.h>
#include <asc/std/__memory/allocator_arg_t.h>
#include <asc/std/__utility/swap.h>
#include <asc/std/__utility/exchange.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__concepts/predicate.h>
#include <asc/std/__concepts/invocable.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/common_reference_with.h>

#include "core_consumers.h"

int asc_stl_concepts_limits_consumer_b()
{
    static_assert(asc::std::numeric_limits<const unsigned long long>::is_specialized);
    static_assert(asc::std::numeric_limits<signed char>::digits == 7);
    static_assert(asc::std::numeric_limits<double>::lowest() < 0.0);
    static_assert(asc::std::is_swappable_v<int>);
    static_assert(asc::std::copyable<int> && asc::std::semiregular<int>);
    static_assert(asc::std::is_same_v<decltype(asc::std::allocator_arg), const asc::std::allocator_arg_t>);
    int left = 2;
    int right = 5;
    int values[1] = {7};
    asc::std::swap(left, right);  // NOLINT(build/include_what_you_use)
    return left == 5 && right == 2 && asc::std::data(values)[0] == 7 && !asc::std::empty(values) ? 0 : 1;
}
