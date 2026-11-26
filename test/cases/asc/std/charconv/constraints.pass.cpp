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

#include <asc/std/charconv>
#include <utility>
#include "support/detected.h"

template <class T>
using to_chars_result =
    decltype(asc::std::to_chars(std::declval<char*>(), std::declval<char*>(), std::declval<T>(), 10));
static_assert(
    asc_stl_test::detected<to_chars_result, unsigned> && asc_stl_test::detected<to_chars_result, signed char>);
static_assert(!asc_stl_test::detected<to_chars_result, bool>);

int main()
{}
