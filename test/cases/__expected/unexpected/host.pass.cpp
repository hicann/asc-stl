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

#include <asc/std/__expected/unexpected.h>
#include <type_traits>

constexpr bool test_unexpected()
{
    asc::std::unexpected<int> a{7};
    asc::std::unexpected<int> b{asc::std::in_place, 9};
    a.swap(b);
    return a.error() == 9 && b.error() == 7 && a != b;
}

static_assert(test_unexpected());
static_assert(std::is_same_v<decltype(asc::std::unexpected{3}), asc::std::unexpected<int>>);

int main()
{
    return test_unexpected() ? 0 : 1;
}
