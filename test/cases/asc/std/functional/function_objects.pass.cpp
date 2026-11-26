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

#include <asc/std/functional>

#include <functional>
#include <type_traits>
#include <utility>

namespace {

namespace ast = asc::std;

template <class T, class = void>
struct is_transparent : std::false_type {};
template <class T>
struct is_transparent<T, std::void_t<typename T::is_transparent>> : std::true_type {};

template <class Actual, class Transparent, class Reference>
constexpr bool check_binary(bool nonzero_rhs = false)
{
    static_assert(is_transparent<Transparent>::value);
    const int inputs[] = {-9, -1, 0, 2, 11};
    for (int a : inputs) {
        for (int b : inputs) {
            if ((!nonzero_rhs || b != 0) &&
                (Actual{}(a, b) != Reference{}(a, b) || Transparent{}(a, static_cast<long>(b)) != Reference{}(a, b))) {
                return false;
            }
        }
    }
    return true;
}

template <class Actual, class Transparent, class Reference>
constexpr bool check_unary()
{
    static_assert(is_transparent<Transparent>::value);
    const int inputs[] = {-9, -1, 0, 2, 11};
    for (int a : inputs) {
        if (Actual{}(a) != Reference{}(a) || Transparent{}(static_cast<long>(a)) != Reference{}(a)) {
            return false;
        }
    }
    return true;
}

#define CHECK_BINARY(Name, Nonzero) static_assert(check_binary<ast::Name<int>, ast::Name<>, std::Name<int>>(Nonzero))
CHECK_BINARY(plus, false);
CHECK_BINARY(minus, false);
CHECK_BINARY(multiplies, false);
CHECK_BINARY(divides, true);
CHECK_BINARY(modulus, true);
CHECK_BINARY(bit_and, false);
CHECK_BINARY(bit_or, false);
CHECK_BINARY(bit_xor, false);
CHECK_BINARY(equal_to, false);
CHECK_BINARY(not_equal_to, false);
CHECK_BINARY(less, false);
CHECK_BINARY(less_equal, false);
CHECK_BINARY(greater, false);
CHECK_BINARY(greater_equal, false);
CHECK_BINARY(logical_and, false);
CHECK_BINARY(logical_or, false);
#undef CHECK_BINARY

#define CHECK_UNARY(Name) static_assert(check_unary<ast::Name<int>, ast::Name<>, std::Name<int>>())
CHECK_UNARY(negate);
CHECK_UNARY(bit_not);
CHECK_UNARY(logical_not);
#undef CHECK_UNARY

#define CHECK_RANGES(Name) static_assert(check_binary<ast::ranges::Name, ast::ranges::Name, std::Name<int>>())
CHECK_RANGES(equal_to);
CHECK_RANGES(not_equal_to);
CHECK_RANGES(less);
CHECK_RANGES(less_equal);
CHECK_RANGES(greater);
CHECK_RANGES(greater_equal);
#undef CHECK_RANGES

static_assert(is_transparent<ast::identity>::value);
static_assert(std::is_same_v<decltype(ast::identity{}(std::declval<const int&>())), const int&>);
static_assert(std::is_same_v<decltype(ast::identity{}(std::declval<int&&>())), int&&>);

#define CHECK_PLACEHOLDER(N) \
    static_assert(ast::is_placeholder<std::decay_t<decltype(ast::placeholders::_##N)>>::value == N)
CHECK_PLACEHOLDER(1);
CHECK_PLACEHOLDER(2);
CHECK_PLACEHOLDER(3);
CHECK_PLACEHOLDER(4);
CHECK_PLACEHOLDER(5);
CHECK_PLACEHOLDER(6);
CHECK_PLACEHOLDER(7);
CHECK_PLACEHOLDER(8);
CHECK_PLACEHOLDER(9);
#undef CHECK_PLACEHOLDER
static_assert(ast::is_placeholder<int>::value == 0);

struct accumulator {
    int value;
    constexpr int operator()(int inc) noexcept
    {
        value += inc;
        return value;
    }
};
using wrapper = ast::reference_wrapper<accumulator>;
static_assert(std::is_same_v<wrapper::type, accumulator>);
static_assert(std::is_same_v<ast::unwrap_reference<wrapper>::type, accumulator&>);
static_assert(std::is_same_v<ast::unwrap_reference<int>::type, int>);

bool check_reference_and_search()
{
    accumulator state{4};
    const wrapper reference(state);
    if (&reference.get() != &state || &ast::identity{}(state) != &state || reference(-1) != 3 || reference(8) != 11 ||
        state.value != 11) {
        return false;
    }
    const int values[] = {1, 2, 1, 2, 3};
    const int pattern[] = {1, 2};
    const int absent[] = {2, 2};
    const ast::default_searcher<const int*> match(pattern, pattern + 2);
    const ast::default_searcher<const int*> miss(absent, absent + 2);
    const ast::default_searcher<const int*> empty(pattern, pattern);
    const auto first = match(values, values + 5);
    const auto second = match(values + 1, values + 5);
    const auto none = miss(values, values + 5);
    const auto short_input = match(values, values + 1);
    const auto no_pattern = empty(values, values);
    return first.first == values && first.second == values + 2 && second.first == values + 2 &&
        second.second == values + 4 && none.first == values + 5 && none.second == values + 5 &&
        short_input.first == values + 1 && short_input.second == values + 1 && no_pattern.first == values &&
        no_pattern.second == values;
}

}  // namespace

int main()
{
    return check_reference_and_search() ? 0 : 1;
}
