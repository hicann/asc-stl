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

#include <asc/__functional/proclaim_return_type.h>
#include <type_traits>

struct QualifiedCallable {
    constexpr int operator()(int value) & noexcept
    {
        return value + 1;
    }
    constexpr int operator()(int value) && noexcept
    {
        return value + 2;
    }
    constexpr int operator()(int value) const& noexcept
    {
        return value + 3;
    }
    constexpr int operator()(int value) const&& noexcept
    {
        return value + 4;
    }
};

bool test_proclaimed()
{
    auto wrapper = asc::proclaim_return_type<int>(QualifiedCallable{});
    return wrapper(4) == 5 && asc::proclaim_return_type<int>(QualifiedCallable{})(4) == 6;
}

static_assert(std::is_same_v<decltype(asc::proclaim_return_type<int>(QualifiedCallable{})(0)), int>);

int main()
{
    return test_proclaimed() ? 0 : 1;
}
