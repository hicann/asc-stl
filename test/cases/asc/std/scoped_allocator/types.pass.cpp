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

#include <asc/std/scoped_allocator>
#include <cstddef>
#include <type_traits>
#include "device_checks.h"

namespace s = asc::std;

using outer = asc_stl_test_scoped_allocator::local<int>;
using inner = asc_stl_test_scoped_allocator::local<char>;
using other = asc_stl_test_scoped_allocator::local<long>;
using nested = s::scoped_allocator_adaptor<outer, inner>;
static_assert(std::is_same_v<nested::outer_allocator_type, outer>);
static_assert(std::is_same_v<nested::inner_allocator_type, s::scoped_allocator_adaptor<inner>>);
static_assert(std::is_same_v<nested::value_type, int>);
static_assert(std::is_same_v<nested::pointer, int*>);
static_assert(std::is_same_v<nested::size_type, std::size_t>);
static_assert(std::is_same_v<nested::difference_type, std::ptrdiff_t>);
static_assert(std::is_same_v<nested::rebind<long>::other, s::scoped_allocator_adaptor<other, inner>>);

int main()
{}
