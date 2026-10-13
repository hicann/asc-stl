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

namespace asc_stl_functional_properties {
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
        asc::std::multiplies<unsigned>{}(value, absorbing) == 0;
}
}  // namespace asc_stl_functional_properties

#endif  // ASC_STL_TEST_FUNCTIONAL_PROPERTIES_H
