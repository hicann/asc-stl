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

#include <asc/__config>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/version>

#ifdef CANN_ASC_STL_DETAIL_CONCEPT
#error "C++20 concept syntax macros must not be exposed in C++17"
#endif

int main()
{
    static_assert(CANN_ASC_STL_DETAIL_HAS_CXX17());
    static_assert(!CANN_ASC_STL_DETAIL_HAS_CXX20());
    static_assert(!CANN_ASC_STL_DETAIL_HAS_CONCEPTS());
    static_assert(!CANN_ASC_STL_DETAIL_HAS_CHAR8_T());
    return 0;
}
