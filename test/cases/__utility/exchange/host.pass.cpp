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

#include <asc/std/__utility/exchange.h>
#include <type_traits>
struct Box {
    int value;
    constexpr Box(int v) : value(v)  // NOLINT(runtime/explicit)
    {}
    constexpr Box(Box&& other) noexcept : value(other.value)
    {
        other.value = -1;
    }
    constexpr Box& operator=(Box&& other) noexcept
    {
        value = other.value;
        other.value = -1;
        return *this;
    }
};
constexpr bool test_exchange()
{
    int x = 4;
    int old = asc::std::exchange(x, 9);
    Box a{7};
    Box b{12};
    Box prior = asc::std::exchange(a, asc::std::move(b));  // NOLINT(build/include_what_you_use)
    return old == 4 && x == 9 && prior.value == 7 && a.value == 12;
}
static_assert(test_exchange());
static_assert(noexcept(asc::std::exchange(*static_cast<int*>(nullptr), 3)));
int main()
{
    return test_exchange() ? 0 : 1;
}
