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

#include <asc/std/__type_traits/common_type.h>
#include <type_traits>

struct A {};
struct B {};

template <class, class = void>
struct HasType : std::false_type {};
template <class T>
struct HasType<T, std::void_t<typename T::type>> : std::true_type {};

static_assert(!HasType<asc::std::common_type<>>::value);
static_assert(std::is_same_v<asc::std::common_type_t<const int>, int>);
static_assert(std::is_same_v<asc::std::common_type_t<int, double>, double>);
static_assert(std::is_same_v<asc::std::common_type_t<int&, const int&>, int>);
static_assert(std::is_same_v<asc::std::common_type_t<int, short, double>, double>);
static_assert(std::is_same_v<asc::std::common_type_t<int[3]>, int*>);
static_assert(!asc::std::__has_common_type<A, B>);
static_assert(asc::std::__has_common_type<int, long>);

int main()
{
    return 0;
}
