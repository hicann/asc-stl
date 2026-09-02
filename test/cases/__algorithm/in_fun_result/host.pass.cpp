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

#include <asc/std/__algorithm/in_fun_result.h>
#include <type_traits>

struct Fun {};

constexpr bool test_result()
{
    asc::std::ranges::in_fun_result<int, Fun> source{7, {}};
    asc::std::ranges::in_fun_result<long, Fun> copied = source;
    asc::std::ranges::in_fun_result<long, Fun> moved = asc::std::move(source);  // NOLINT(build/include_what_you_use)
    return copied.in == 7 && moved.in == 7;
}

static_assert(test_result());
static_assert(std::is_same_v<decltype(asc::std::ranges::in_fun_result<int, Fun>{}.in), int>);

int main()
{
    return test_result() ? 0 : 1;
}
