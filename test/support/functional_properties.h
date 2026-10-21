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

#ifndef ASC_STL_TEST_FUNCTIONAL_PROPERTIES_H
#define ASC_STL_TEST_FUNCTIONAL_PROPERTIES_H

#include <asc/functional>
#include <asc/std/type_traits>

namespace asc_stl_functional_properties {
struct value_operation {
    CANN_ASC_STL_API constexpr unsigned operator()(unsigned value) const
    {
        return value + 1;
    }
};

struct reference_operation {
    CANN_ASC_STL_API constexpr unsigned& operator()(unsigned& value) const
    {
        return value;
    }
};

struct void_operation {
    CANN_ASC_STL_API constexpr void operator()(unsigned& value) const
    {
        ++value;
    }
};

CANN_ASC_STL_API bool evaluate_copyable_wrapper(unsigned value)
{
    const auto by_value = asc::proclaim_copyable_arguments(value_operation{});
    const auto by_reference = asc::proclaim_copyable_arguments(reference_operation{});
    const auto no_result = asc::proclaim_copyable_arguments(void_operation{});
    using wrapped_type = asc::std::remove_cv_t<decltype(by_value)>;
    static_assert(asc::proclaims_copyable_arguments_v<wrapped_type, unsigned>);
    static_assert(asc::proclaims_copyable_arguments_v<asc::always_true, unsigned, unsigned>);
    static_assert(asc::proclaims_copyable_arguments_v<asc::always_false, unsigned>);
    static_assert(!asc::proclaims_copyable_arguments_v<value_operation, unsigned>);
    static_assert(asc::std::is_same_v<decltype(by_value(value)), unsigned>);
    static_assert(asc::std::is_same_v<decltype(by_reference(value)), unsigned&>);
    static_assert(asc::std::is_same_v<decltype(no_result(value)), void>);
    const unsigned previous = value;
    const bool reference_preserved = &by_reference(value) == &value;
    no_result(value);
    return reference_preserved && value == previous + 1 && by_value(previous) == value;
}

CANN_ASC_STL_API bool evaluate(unsigned value)
{
    static_assert(asc::has_identity_element_v<asc::std::plus<int>, int>);
    static_assert(asc::identity_element<asc::std::plus<int>, int>() == 0);
    static_assert(asc::identity_element<asc::std::multiplies<int>, int>() == 1);
    static_assert(asc::identity_element<asc::std::logical_and<bool>, bool>());
    static_assert(!asc::identity_element<asc::std::logical_or<bool>, bool>());
    static_assert(asc::identity_element<asc::std::bit_and<unsigned>, unsigned>() == ~0U);
    static_assert(asc::identity_element<asc::std::bit_or<unsigned>, unsigned>() == 0U);
    static_assert(asc::identity_element<asc::std::bit_xor<unsigned>, unsigned>() == 0U);
    static_assert(asc::absorbing_element<asc::std::multiplies<int>, int>() == 0);
    static_assert(!asc::absorbing_element<asc::std::logical_and<bool>, bool>());
    static_assert(asc::absorbing_element<asc::std::logical_or<bool>, bool>());
    static_assert(!asc::has_identity_element_v<asc::std::plus<float>, float>);
    static_assert(!asc::has_absorbing_element_v<asc::std::plus<int>, int>);
    static_assert(!asc::is_associative_v<asc::std::plus<float>, float>);
    static_assert(asc::is_associative_v<asc::std::plus<unsigned>, unsigned>);

    static_assert(asc::identity_element<asc::std::plus<>, unsigned>() == 0U);
    static_assert(!asc::has_identity_element_v<asc::std::plus<int>, unsigned>);
    static_assert(!asc::has_identity_element_v<asc::std::logical_and<int>, bool>);
    static_assert(asc::absorbing_element<asc::std::bit_or<unsigned>, unsigned>() == ~0U);
    static_assert(!asc::has_absorbing_element_v<asc::std::bit_or<int>, int>);
    static_assert(asc::absorbing_element<asc::std::bit_and<unsigned>, unsigned>() == 0U);
    static_assert(!asc::has_absorbing_element_v<asc::std::bit_xor<unsigned>, unsigned>);
    static_assert(!asc::is_associative_v<asc::std::multiplies<unsigned short>, unsigned short>);
    static_assert(asc::is_associative_v<asc::std::multiplies<unsigned>, unsigned>);
    static_assert(!asc::has_identity_element_v<asc::std::plus<void>, void>);
    const unsigned zero = asc::identity_element<asc::std::plus<unsigned>, unsigned>();
    const unsigned one = asc::identity_element<asc::std::multiplies<unsigned>, unsigned>();
    const unsigned absorbing = asc::absorbing_element<asc::std::multiplies<unsigned>, unsigned>();
    return asc::std::plus<unsigned>{}(value, zero) == value && asc::std::multiplies<unsigned>{}(value, one) == value &&
        asc::std::multiplies<unsigned>{}(value, absorbing) == 0 && evaluate_copyable_wrapper(value);
}
}  // namespace asc_stl_functional_properties

#endif  // ASC_STL_TEST_FUNCTIONAL_PROPERTIES_H
