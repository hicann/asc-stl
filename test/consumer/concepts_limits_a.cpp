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

#include <asc/std/concepts>
#include <asc/std/__iterator/access.h>
#include <asc/std/__iterator/iterator_traits.h>
#include <asc/std/__memory/pointer_traits.h>
#include <asc/std/__concepts/constructible.h>
#include <asc/std/__concepts/invocable.h>
#include <asc/std/__concepts/predicate.h>
#include <asc/std/__functional/invoke.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__iterator/readable_traits.h>
#include <asc/std/__utility/exchange.h>
#include <asc/std/__utility/swap.h>
#include <asc/std/limits>

int asc_stl_concepts_limits_consumer_b();

namespace {
struct consumer_callable {
    constexpr int operator()(int value) const noexcept
    {
        return value + 3;
    }
};
struct consumer_readable {
    using value_type = const long;
};
struct consumer_incrementable {
    using difference_type = long long;
};
}  // namespace

int asc_stl_concepts_limits_consumer_a()
{
    static_assert(asc::std::integral<int>);
    static_assert(asc::std::common_reference_with<int&, const int&>);
    static_assert(asc::std::copy_constructible<int>);
    static_assert(asc::std::invocable<consumer_callable, int>);
    static_assert(asc::std::predicate<consumer_callable, int>);
    static_assert(asc::std::regular<int> && asc::std::totally_ordered<int>);
    static_assert(asc::std::is_same_v<asc::std::iterator_traits<int*>::value_type, int>);
    static_assert(asc::std::is_same_v<asc::std::pointer_traits<int*>::rebind<long>, long*>);
    static_assert(asc::std::is_same_v<asc::std::iter_value_t<consumer_readable>, long>);
    static_assert(asc::std::is_same_v<asc::std::iter_difference_t<consumer_incrementable>, long long>);
    static_assert(asc::std::numeric_limits<unsigned int>::is_modulo);
    static_assert(asc::std::numeric_limits<float>::is_iec559);
    int value = 4;
    int values[2] = {4, 8};
    int old = asc::std::exchange(value, 8);
    return old == 4 && value == 8 && *asc::std::begin(values) == 4 &&
            asc::std::invoke(consumer_callable{}, value) == 11 ?
        asc_stl_concepts_limits_consumer_b() :
        1;
}
