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

#include <iterator>
#include <type_traits>

#include "../../../support/w09_w10_semantics.h"

using strided_pointer = asc::strided_iterator<int*>;
static_assert(std::is_same<typename std::iterator_traits<strided_pointer>::value_type, int>::value, "");
static_assert(std::is_same<typename std::iterator_traits<strided_pointer>::iterator_category,
                  std::random_access_iterator_tag>::value,
    "");
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
static_assert(std::random_access_iterator<strided_pointer>);
#endif

int main()
{
    return asc_stl_w09_w10_test::evaluate_iterator();
}
