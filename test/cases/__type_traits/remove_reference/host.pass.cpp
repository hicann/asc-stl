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

#include <asc/std/__type_traits/remove_reference.h>

#include <type_traits>

static_assert(std::is_same_v<asc::std::remove_reference<int>::type, std::remove_reference<int>::type>);
static_assert(std::is_same_v<asc::std::remove_reference<int[3]>::type, std::remove_reference<int[3]>::type>);
static_assert(std::is_same_v<asc::std::remove_reference<int[3][4]>::type, std::remove_reference<int[3][4]>::type>);
static_assert(std::is_same_v<asc::std::remove_reference<const int&>::type, std::remove_reference<const int&>::type>);
static_assert(std::is_same_v<asc::std::remove_reference<int*>::type, std::remove_reference<int*>::type>);

int main()
{
    return 0;
}
