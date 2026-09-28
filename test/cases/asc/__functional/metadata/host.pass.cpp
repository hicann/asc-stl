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
#include <asc/__functional/metadata.h>

#include <cassert>

int main()
{
    using asc::detail::add_op;
    using asc::detail::bitwise_and_op;
    using asc::detail::bitwise_or_op;
    using asc::detail::bitwise_xor_op;
    using asc::detail::logical_and_op;
    using asc::detail::logical_or_op;
    using asc::detail::maximum_op;
    using asc::detail::minimum_op;
    using asc::detail::multiply_op;

    static_assert(asc::detail::is_associative_op<add_op>::value);
    static_assert(asc::detail::is_associative_op<multiply_op>::value);
    static_assert(asc::detail::is_associative_op<logical_and_op>::value);
    static_assert(asc::detail::is_associative_op<bitwise_xor_op>::value);
    static_assert(asc::detail::is_associative_op<minimum_op>::value);
    static_assert(asc::detail::is_associative_op<maximum_op>::value);
    static_assert(!asc::detail::is_associative_op<int>::value);

    static_assert(asc::detail::is_commutative_op<add_op>::value);
    static_assert(!asc::detail::is_commutative_op<int>::value);

    static_assert(asc::detail::identity_element_op<add_op, int>::has_value);
    static_assert(asc::detail::identity_element_op<add_op, int>::value == 0);
    static_assert(asc::detail::identity_element_op<multiply_op, int>::value == 1);
    static_assert(asc::detail::identity_element_op<logical_and_op, bool>::value);
    static_assert(!asc::detail::identity_element_op<logical_or_op, bool>::value);
    static_assert(asc::detail::identity_element_op<bitwise_and_op, unsigned>::value == ~0u);
    static_assert(asc::detail::identity_element_op<bitwise_or_op, unsigned>::value == 0u);
    static_assert(asc::detail::identity_element_op<maximum_op, int>::has_value == false);

    static_assert(asc::detail::absorbing_element_op<multiply_op, int>::has_value);
    static_assert(asc::detail::absorbing_element_op<multiply_op, int>::value == 0);
    static_assert(!asc::detail::absorbing_element_op<add_op, int>::has_value);
    static_assert(!asc::detail::absorbing_element_op<bitwise_or_op, int>::has_value);

    static_assert(asc::detail::always_true_op{}());
    static_assert(!asc::detail::always_false_op{}());
    assert(asc::detail::equal_to_value_op<int>{42}(42));
    assert(!asc::detail::equal_to_value_op<int>{42}(41));
    static_assert(asc::detail::maximum_op_of<int>{}(3, 9) == 9);
    static_assert(asc::detail::minimum_op_of<int>{}(3, 9) == 3);
    return 0;
}
