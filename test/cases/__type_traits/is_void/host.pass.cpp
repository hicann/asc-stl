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

#include <asc/std/__type_traits/is_void.h>

#include <type_traits>

static_assert(asc::std::is_void<int>::value == std::is_void<int>::value);
static_assert(asc::std::is_void<void>::value == std::is_void<void>::value);
static_assert(asc::std::is_void<int[3]>::value == std::is_void<int[3]>::value);
static_assert(asc::std::is_void<int*>::value == std::is_void<int*>::value);
static_assert(asc::std::is_void<double>::value == std::is_void<double>::value);

int main()
{
    return 0;
}
