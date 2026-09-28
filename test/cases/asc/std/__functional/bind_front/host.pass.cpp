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

#include <asc/std/__functional/bind_front.h>

#include <cassert>
#include <string>

int main()
{
    auto leading =
        asc::std::bind_front([](int first, int second, int third) { return first * 100 + second * 10 + third; }, 1, 2);
    assert(leading(3) == 123);

    auto single = asc::std::bind_front([](int value) { return value * 2; }, 21);
    assert(single() == 42);

    int moves = 0;
    struct Counted {
        int* counter;
        explicit Counted(int* given) : counter(given)
        {}
        Counted(Counted&& other) : counter(other.counter)
        {
            ++*counter;
        }
        Counted(const Counted&) = delete;
        Counted& operator=(Counted&&) = default;
        Counted& operator=(const Counted&) = delete;
    };
    auto consuming = asc::std::bind_front([](Counted&, int extra) { return extra; }, Counted(&moves));
    assert(consuming(42) == 42 && moves == 1);

    auto copyable = asc::std::bind_front([](int left, int right) { return left + right; }, 40);
    assert(copyable(2) == 42);
    const auto copied = copyable;
    assert(copied(2) == 42);

    constexpr int constant_evaluated = asc::std::bind_front([](int left, int right) { return left * right; }, 6)(7);
    static_assert(constant_evaluated == 42);
    return 0;
}
