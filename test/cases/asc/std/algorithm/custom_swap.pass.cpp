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

#include <asc/std/algorithm>
#include <asc/std/concepts>

struct adl_value {
    int value;
    int swaps;
    friend void swap(adl_value& left, adl_value& right) noexcept  // NOLINT(build/include_what_you_use)
    {
        int saved = left.value;
        left.value = right.value;
        right.value = saved;
        ++left.swaps;
        ++right.swaps;
    }
};

int main()
{
    adl_value a{3, 0}, b{-2, 0};
    asc::std::ranges::swap(a, b);
    if (a.value != -2 || b.value != 3 || a.swaps != 1 || b.swaps != 1)
        return 1;
    // Heterogeneous writable references exercise the move-exchange fallback.
    int x = -4;
    short y = 27;
    asc::std::ranges::iter_swap(&x, &y);
    return x != 27 || y != -4;
}
