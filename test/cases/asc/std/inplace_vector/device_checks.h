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

#ifndef ASC_STL_TEST_INPLACE_VECTOR_DEVICE_CHECKS_H
#define ASC_STL_TEST_INPLACE_VECTOR_DEVICE_CHECKS_H

#include <asc/std/inplace_vector>

namespace asc_stl_test_inplace_vector {
struct fixed_identity {
    fixed_identity() = delete;
    fixed_identity(const fixed_identity&) = delete;
    fixed_identity& operator=(const fixed_identity&) = delete;
};

struct odd {
    CANN_ASC_STL_API bool operator()(int n) const
    {
        return n % 2 != 0;
    }
};

CANN_ASC_STL_API int check(int seed = 7)
{
    using seq = asc::std::inplace_vector<int, 4>;
    using empty_only = asc::std::inplace_vector<fixed_identity, 0>;
    empty_only first;
    empty_only second(first);
    first = static_cast<empty_only&&>(second);
    second.swap(first);
    if (!second.empty() || first.size() != 0)
        return 7;
    asc::std::inplace_vector<int, 0> zero;
    auto empty_copy = zero;
    auto empty_moved = static_cast<decltype(zero)&&>(empty_copy);
    empty_copy = zero;
    zero = static_cast<decltype(zero)&&>(empty_moved);
    empty_copy.swap(zero);
    if (!zero.empty() || zero.capacity() || zero.data() || zero.try_push_back(5) || zero.erase_if(odd{}) != 0)
        return 1;
    seq a;
    const seq& c = a;
    int one = seed - 6;
    if (&a.unchecked_push_back(one) != a.data() || &a.unchecked_push_back(2) != a.data() + 1 || !a.try_push_back(one) ||
        !a.try_emplace_back(4) || a.try_emplace_back(5) || a.try_push_back(6))
        return 2;
    if (a.size() != a.max_size() || a.begin() != c.cbegin() || a.end() != c.cend() || c.begin() != c.data() ||
        c.end() != c.data() + 4 || a.front() != 1 || c.front() != 1 || a.back() != 4 || c.back() != 4 || c[1] != 2)
        return 3;
    seq b(c);
    seq d(static_cast<seq&&>(b));
    d = c;
    b.clear();
    b = static_cast<seq&&>(d);
    if (b.erase(b.cbegin() + 1) != b.begin() + 1 || b[1] != 1 || b.erase(b.cend(), b.cend()) != b.end() ||
        b.erase_if(odd{}) != 2 || b.size() != 1 || b[0] != 4)
        return 4;
    a.swap(b);
    if (a.size() != 1 || a[0] != 4 || b.size() != 4 || b[0] != 1)
        return 5;
    b.erase(b.begin() + 1, b.end());
    b.pop_back();
    b.unchecked_emplace_back(9);
    return b.size() == 1 && b.front() == 9 ? 0 : 6;
}
}  // namespace asc_stl_test_inplace_vector

#endif  // ASC_STL_TEST_INPLACE_VECTOR_DEVICE_CHECKS_H
