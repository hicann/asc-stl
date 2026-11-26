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

#include <asc/std/stack>
#include <cstddef>
#include <type_traits>
#include "../../../../support/fixed_sequence.h"

namespace s = asc::std;

using data = asc_stl_test::fixed_sequence<int, 8>;
using adaptor = s::stack<int, data>;
static_assert(std::is_same_v<adaptor::value_type, int>);
static_assert(std::is_same_v<adaptor::container_type, data>);
static_assert(std::is_same_v<adaptor::size_type, std::size_t>);
static_assert(std::is_same_v<adaptor::reference, int&>);
static_assert(std::is_same_v<adaptor::const_reference, const int&>);

int main()
{}
