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

#ifndef ASC_STL_TEST_SPAN_DEVICE_CHECKS_H
#define ASC_STL_TEST_SPAN_DEVICE_CHECKS_H

#include <asc/std/span>
#include <asc/std/array>

namespace asc_stl_test_span {
template <class S>
CANN_ASC_STL_API constexpr bool check_slices(S s)
{
    for (unsigned first = 0; first <= s.size(); ++first) {
        if (s.first(first).data() != s.data() || s.first(first).size() != first ||
            s.last(first).data() != s.end() - first || s.subspan(first).size() != s.size() - first)
            return false;
        for (unsigned n = 0; n <= s.size() - first; ++n) {
            auto sub = s.subspan(first, n);
            if (sub.data() != s.data() + first || sub.size() != n || sub.empty() != (n == 0))
                return false;
        }
    }
    return s.template first<0>().empty() && s.template last<2>().data() == s.data() + 2 &&
        s.template subspan<1, 2>().back() == 3 && s.template subspan<4>().empty() && s.begin() == s.data() &&
        s.end() == s.data() + 4 && s.rbegin().base() == s.end() && s.rend().base() == s.begin() && s.front() == 1 &&
        s.back() == 4 && s.size_bytes() == 4 * sizeof(int);
}

CANN_ASC_STL_API int check(int seed = 7)
{
    asc::std::span<int, 0> zero;
    asc::std::span<const int> empty;
    int raw[] = {seed - 6, 2, 3, 4};
    asc::std::array<int, 4> array{{1, 2, 3, 4}};
    const auto& const_array = array;
    asc::std::span<int, 4> fixed(raw);
    asc::std::span<int> dynamic(fixed);
    asc::std::span<int, 4> from_pair(raw + 0, raw + 4);
    asc::std::span<int> from_count(raw + 0, 4);
    asc::std::span<const int, 4> immutable(const_array);
    asc::std::span<int> writable(array);
    if (!empty.empty() || !zero.empty() || !check_slices(fixed) || !check_slices(dynamic) || !check_slices(from_pair) ||
        !check_slices(from_count) || !check_slices(immutable))
        return 1;
    writable[3] = 13;
    if (immutable.back() != 13 || asc::std::as_bytes(immutable).size() != sizeof(raw) ||
        asc::std::as_writable_bytes(writable).size() != sizeof(raw))
        return 2;
    return 0;
}
}  // namespace asc_stl_test_span

#endif  // ASC_STL_TEST_SPAN_DEVICE_CHECKS_H
