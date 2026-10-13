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
#include <asc/std/functional>
#include "support/b008_semantics.h"

static_assert(asc::std::is_same_v<asc::std::unwrap_reference_t<int&>, int&>);
static_assert(asc::std::is_same_v<asc::std::unwrap_reference_t<asc::std::reference_wrapper<int>>, int&>);
static_assert(asc::std::is_same_v<asc::std::unwrap_reference_t<const asc::std::reference_wrapper<int>>,
    const asc::std::reference_wrapper<int>>);
static_assert(asc::std::is_same_v<asc::std::unwrap_ref_decay_t<const asc::std::reference_wrapper<int>&>, int&>);
static_assert(asc::std::is_same_v<typename asc::std::unwrap_ref_decay<int (&)[3]>::type, int*>);

int main()
{
    return asc_stl_b008_test::evaluate();
}
