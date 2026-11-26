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

#include <asc/std/memory>

#include <memory>

namespace {
struct failure {};
struct counted {
    static int live;
    static int allowed;
    static void acquire()
    {
        if (allowed-- == 0)
            throw failure{};
        ++live;
    }
    counted()
    {
        acquire();
    }
    counted(const counted&)
    {
        acquire();
    }
    counted(counted&&)
    {
        acquire();
    }
    ~counted()
    {
        --live;
    }
};
int counted::live = 0;
int counted::allowed = 4;

template <class Construct>
bool rolled_back(Construct construct, counted* output)
{
    const int before = counted::live;
    for (int completed = 0; completed < 4; ++completed) {
        counted::allowed = completed;
        try {
            construct(output);
            return false;
        } catch (const failure&) {
            if (counted::live != before)
                return false;
        }
    }
    return true;
}
}  // namespace

int main()
{
    counted input[4]{};
    std::allocator<counted> a;
    counted* out = a.allocate(4);
    namespace s = asc::std;
    const bool passed = rolled_back([&](auto p) { s::uninitialized_copy(input, input + 4, p); }, out) &&
        rolled_back([&](auto p) { s::uninitialized_copy_n(input, 4, p); }, out) &&
        rolled_back([&](auto p) { s::uninitialized_move(input, input + 4, p); }, out) &&
        rolled_back([&](auto p) { s::uninitialized_move_n(input, 4, p); }, out) &&
        rolled_back([&](auto p) { s::uninitialized_fill(p, p + 4, input[0]); }, out) &&
        rolled_back([&](auto p) { s::uninitialized_fill_n(p, 4, input[0]); }, out) &&
        rolled_back([](auto p) { s::uninitialized_default_construct(p, p + 4); }, out) &&
        rolled_back([](auto p) { s::uninitialized_default_construct_n(p, 4); }, out) &&
        rolled_back([](auto p) { s::uninitialized_value_construct(p, p + 4); }, out) &&
        rolled_back([](auto p) { s::uninitialized_value_construct_n(p, 4); }, out);
    a.deallocate(out, 4);
    return passed ? 0 : 1;
}
