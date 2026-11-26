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
#include <asc/std/cstddef>
#include <cstddef>
#include <type_traits>
#include "support/core_semantics.h"

static_assert(std::is_same_v<asc::std::max_align_t, std::max_align_t>);
static_assert(std::is_same_v<asc::std::ptrdiff_t, std::ptrdiff_t>);
static_assert(std::is_same_v<asc::std::size_t, std::size_t>);
static_assert(std::is_same_v<asc::std::nullptr_t, decltype(nullptr)>);
static_assert(alignof(asc::std::max_align_t) >= alignof(long double));
struct offset_pair {
    char first;
    long second;
};
static_assert(offsetof(offset_pair, first) == 0 && offsetof(offset_pair, second) % alignof(long) == 0);
static_assert(NULL == nullptr);

int main()
{
    return asc_stl_core_test::evaluate();
}
