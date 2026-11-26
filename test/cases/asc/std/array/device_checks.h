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

#ifndef ASC_STL_TEST_ARRAY_DEVICE_CHECKS_H
#define ASC_STL_TEST_ARRAY_DEVICE_CHECKS_H

#include <asc/std/array>

namespace asc_stl_test_array {
template <class A>
CANN_ASC_STL_API constexpr bool endpoints(A& a)
{
    return a.begin() == a.data() && a.end() == a.data() + a.size() && a.cbegin() == a.begin() && a.cend() == a.end() &&
        a.rbegin().base() == a.end() && a.rend().base() == a.begin() && a.crbegin() == a.rbegin() &&
        a.crend() == a.rend();
}

CANN_ASC_STL_API constexpr int check(int seed = 7)
{
    asc::std::array<int, 0> empty{}, also_empty{};
    const auto& const_empty = empty;
    empty.fill(4);
    empty.swap(also_empty);
    if (!empty.empty() || empty.max_size() != 0 || !endpoints(empty) || !endpoints(const_empty))
        return 1;
    int raw[] = {seed - 3, -1, 2};
    auto a = asc::std::to_array(raw);
    auto b = asc::std::to_array(static_cast<int(&&)[3]>(raw));
    const auto& c = a;
    static_assert(asc::std::tuple_size<decltype(a)>::value == 3);
    static_assert(asc::std::is_same_v<typename asc::std::tuple_element<2, decltype(a)>::type, int>);
    static_assert(asc::std::is_same_v<decltype(asc::std::get<0>(static_cast<decltype(a)&&>(a))), int&&>);
    static_assert(asc::std::is_same_v<decltype(asc::std::get<0>(static_cast<const decltype(a)&&>(c))), const int&&>);
    int&& moved_element = asc::std::get<1>(static_cast<decltype(a)&&>(a));
    const int&& const_moved_element = asc::std::get<2>(static_cast<const decltype(a)&&>(c));
    if (&moved_element != &a[1] || &const_moved_element != &c[2])
        return 6;
    using zero = decltype(empty);
    static_assert(asc::std::is_same_v<decltype(asc::std::declval<zero&>().front()), int&>);
    static_assert(asc::std::is_same_v<decltype(asc::std::declval<const zero&>().front()), const int&>);
    static_assert(asc::std::is_same_v<decltype(asc::std::declval<zero&>().back()), int&>);
    static_assert(asc::std::is_same_v<decltype(asc::std::declval<const zero&>().back()), const int&>);
    static_assert(asc::std::is_same_v<decltype(asc::std::declval<zero&>()[0]), int&>);
    static_assert(asc::std::is_same_v<decltype(asc::std::declval<const zero&>()[0]), const int&>);
    if (a.empty() || a.max_size() != 3 || !endpoints(a) || !endpoints(c) || c.front() != 4 || c.back() != 2)
        return 2;
    a.back() = a.front();
    if (c[2] != 4 || *(a.rbegin() + 1) != -1 || asc::std::get<1>(c) != -1)
        return 3;
    asc::std::get<1>(a) = 5;
    if (!(a > b && b < a && a >= b && b <= a && a != b && a == a))
        return 4;
    asc::std::swap(a, b);  // NOLINT(build/include_what_you_use)
    b.fill(9);
    return a[1] == -1 && b[0] == 9 && b[1] == 9 && b[2] == 9 ? 0 : 5;
}
}  // namespace asc_stl_test_array

#endif  // ASC_STL_TEST_ARRAY_DEVICE_CHECKS_H
