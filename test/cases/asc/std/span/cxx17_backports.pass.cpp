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

#include "support/cxx17_container_semantics.h"

#if CANN_ASC_STL_DETAIL_HAS_CXX20()
#include <deque>
#include <span>
#include <vector>

static_assert(asc::std::is_constructible_v<asc::std::span<int>, std::vector<int>&>);
static_assert(asc::std::is_constructible_v<asc::std::span<int>, std::span<int>&>);
static_assert(!asc::std::is_constructible_v<asc::std::span<int>, std::deque<int>&>);
static_assert(!asc::std::is_constructible_v<asc::std::span<int>, std::vector<bool>&>);
#endif

static_assert(asc_stl_cxx17_container_test::evaluate_pointer_constexpr());
static_assert(asc_stl_cxx17_container_test::evaluate_span_slicing(4));
static_assert(asc_stl_cxx17_container_test::evaluate_span_constraints());

int main()
{
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
    std::vector<int> values{1, 2};
    asc::std::span<int> view(values);
    view[1] = 3;
    if (view.data() != values.data() || values[1] != 3) {
        return 1;
    }
#endif
    return asc_stl_cxx17_container_test::evaluate();
}
