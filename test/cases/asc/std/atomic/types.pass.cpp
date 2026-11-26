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

#include <asc/std/atomic>
#include <type_traits>

namespace s = asc::std;

static_assert(std::is_enum_v<s::memory_order>);
static_assert(std::is_same_v<decltype(s::memory_order_seq_cst), s::memory_order>);

static_assert(!std::is_copy_constructible_v<s::atomic<int>> && !std::is_copy_assignable_v<s::atomic<int>>);
static_assert(!std::is_copy_constructible_v<s::atomic_flag> && !std::is_copy_assignable_v<s::atomic_flag>);
static_assert(std::is_copy_constructible_v<s::atomic_ref<int>> && !std::is_copy_assignable_v<s::atomic_ref<int>>);

int main()
{}
