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

#include <asc/std/array>

#include <array>
#include <type_traits>

namespace {

namespace ast = asc::std;

static_assert(std::is_same_v<ast::tuple_element<0, ast::array<int, 2>>::type, int>);
static_assert(std::is_same_v<ast::tuple_element<1, const ast::array<int, 2>>::type, const int>);

template <class A, class B>
constexpr bool check_order(const A& left, const A& right, const B& expected_left, const B& expected_right)
{
    return (left == right) == (expected_left == expected_right) &&
        (left != right) == (expected_left != expected_right) && (left < right) == (expected_left < expected_right) &&
        (left <= right) == (expected_left <= expected_right) && (left > right) == (expected_left > expected_right) &&
        (left >= right) == (expected_left >= expected_right);
}

constexpr bool check_array_order()
{
    const ast::array<int, 0> empty{};
    const std::array<int, 0> reference_empty{};
    if (!check_order(empty, empty, reference_empty, reference_empty)) {
        return false;
    }
    for (int a = -1; a <= 2; ++a) {
        for (int b = -1; b <= 2; ++b) {
            const ast::array<int, 3> left{{0, a, b}};
            const ast::array<int, 3> right{{0, b, a}};
            const std::array<int, 3> expected_left{{0, a, b}};
            const std::array<int, 3> expected_right{{0, b, a}};
            if (!check_order(left, right, expected_left, expected_right) ||
                !check_order(left, left, expected_left, expected_left)) {
                return false;
            }
        }
    }
    return true;
}

}  // namespace

int main()
{
    return check_array_order() ? 0 : 1;
}
