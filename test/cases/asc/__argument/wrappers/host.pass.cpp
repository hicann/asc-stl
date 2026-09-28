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
#include <asc/__argument/wrappers.h>

#include <cassert>

int main()
{
    using asc::detail::constant_argument;
    using asc::detail::deferred_argument;
    using asc::detail::deferred_sequence_argument;
    using asc::detail::immediate_argument;
    using asc::detail::runtime_bounds_state;
    using asc::detail::static_bounds_state;

    constexpr constant_argument<7> constant;
    static_assert(constant.value == 7);
    static_assert(asc::detail::argument_traits<constant_argument<7>>::is_constant);

    immediate_argument<int, static_bounds_state<0, 16>> immediate{9};
    assert(immediate.value == 9 && immediate.bounds.lower == 0 && immediate.bounds.upper == 16);
    static_assert(asc::detail::argument_traits<immediate_argument<int>>::is_immediate);

    int device_value = 11;
    deferred_argument<int, runtime_bounds_state<int>> deferred{&device_value, {0, 32}};
    assert(*deferred.location == 11 && deferred.bounds.upper == 32);
    static_assert(asc::detail::argument_traits<deferred_argument<int>>::is_deferred);
    static_assert(!asc::detail::argument_traits<deferred_argument<int>>::is_sequence);

    const int sequence[4]{1, 2, 3, 4};
    deferred_sequence_argument<int> elements{sequence, 4};
    assert(elements.length == 4 && elements.first == sequence);
    static_assert(asc::detail::argument_traits<deferred_sequence_argument<int>>::is_sequence);
    static_assert(asc::detail::argument_traits<deferred_sequence_argument<int>>::is_deferred);

    // The wrappers copy nothing and allocate nothing: all state is inline.
    static_assert(sizeof(constant_argument<3>) <= 8);
    return 0;
}
