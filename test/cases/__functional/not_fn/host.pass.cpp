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

#include <asc/std/__functional/not_fn.h>

struct IsEven {
    constexpr bool operator()(int value) const noexcept
    {
        return value % 2 == 0;
    }
};

constexpr bool test_not_fn()
{
    auto is_odd = asc::std::not_fn(IsEven{});
    return is_odd(3) && !is_odd(4) && asc::std::move(is_odd)(5);  // NOLINT(build/include_what_you_use)
}

static_assert(test_not_fn());

int main()
{
    return test_not_fn() ? 0 : 1;
}
