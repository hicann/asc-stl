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

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/type_traits>

template <class T>
CANN_ASC_STL_DETAIL_CONCEPT integer_type = asc::std::same_as<T, int>;

struct constrained_function {
    CANN_ASC_STL_DETAIL_TEMPLATE(class T)
    CANN_ASC_STL_DETAIL_REQUIRES(integer_type<T>)
    constexpr int operator()(T value) const
    {
        return value + 1;
    }
};

int main()
{
    static_assert(integer_type<int> && !integer_type<long>);
    static_assert(asc::std::is_invocable_v<constrained_function, int>);
    static_assert(!asc::std::is_invocable_v<constrained_function, long>);
    static_assert(constrained_function{}(3) == 4);
    return 0;
}
