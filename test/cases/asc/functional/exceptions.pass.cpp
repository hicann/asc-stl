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

#include <asc/functional>
#include <asc/std/type_traits>

#include <cmath>
#include <functional>
#include <limits>
#include <utility>

namespace functional_host {
struct failure {};

template <class Function>
bool throws(Function function)
{
    try {
        function();
    } catch (const failure&) {
        return true;
    } catch (...) {
        return false;
    }
    return false;
}

struct throwing_value {
    int value;
    bool fail_copy = false;
    bool fail_move = false;
    bool fail_compare = false;
    explicit throwing_value(int input) noexcept : value(input)
    {}
    throwing_value(const throwing_value& other) : value(other.value)
    {
        if (other.fail_copy)
            throw failure{};
    }
    throwing_value(throwing_value&& other) : value(other.value)
    {
        if (other.fail_move)
            throw failure{};
        other.value = -1;
    }
    friend bool operator<(const throwing_value& left, const throwing_value& right)
    {
        if (left.fail_compare || right.fail_compare)
            throw failure{};
        return left.value < right.value;
    }
};

struct proxy {
    bool value;
    explicit operator bool() const
    {
        throw failure{};
    }
};
struct proxy_value {
    int value;
    friend proxy operator<(const proxy_value& left, const proxy_value& right) noexcept
    {
        return {left.value < right.value};
    }
    friend proxy operator==(int left, const proxy_value& right) noexcept
    {
        return {left == right.value};
    }
};
struct destructor_proxy {
    bool value;
    explicit operator bool() const noexcept
    {
        return value;
    }
    ~destructor_proxy() noexcept(false)
    {
        throw failure{};
    }
};
struct destructor_value {
    friend destructor_proxy operator<(const destructor_value&, const destructor_value&) noexcept
    {
        return {false};
    }
};

bool construction_exceptions()
{
    throwing_value left(1), right(2);
    right.fail_copy = true;
    if (!throws([&] { (void)asc::maximum<throwing_value>{}(left, right); }))
        return false;
    left.fail_copy = true;
    if (!throws([&] { (void)asc::minimum<>{}(left, right); }))
        return false;
    right.fail_move = true;
    if (!throws([&] { (void)asc::maximum<>{}(std::move(left), std::move(right)); }))
        return false;
    if (!throws([&] { (void)asc::equal_to_value<throwing_value>{right}; }))
        return false;
    if (!throws([&] { (void)asc::equal_to_value<throwing_value>{std::move(right)}; }))
        return false;
    return left.value == 1 && right.value == 2;
}

bool comparison_exceptions()
{
    throwing_value left(1), right(2);
    left.fail_compare = true;
    if (!throws([&] { (void)asc::maximum<>{}(left, right); }))
        return false;
    if (!throws([] { (void)asc::minimum<>{}(proxy_value{1}, proxy_value{2}); }))
        return false;
    const auto equal = asc::equal_to_value{proxy_value{1}};
    if (!throws([&] { (void)equal(1); }))
        return false;
    if (!throws([] { (void)asc::maximum<>{}(destructor_value{}, destructor_value{}); }))
        return false;
    return true;
}

int throwing_argument(int& evaluations)
{
    ++evaluations;
    throw failure{};
}

bool argument_evaluation()
{
    static_assert(noexcept(asc::always_true{}(0)));
    static_assert(!noexcept(asc::always_true{}(throwing_argument(std::declval<int&>()))));
    int count = 0;
    return throws([&] { (void)asc::always_true{}(throwing_argument(count)); }) && count == 1 &&
        throws([&] { (void)asc::always_false{}(throwing_argument(count)); }) && count == 2;
}

bool floating_values()
{
    const float nan = std::numeric_limits<float>::quiet_NaN();
    const float signaling = std::numeric_limits<float>::signaling_NaN();
    const float infinity = std::numeric_limits<float>::infinity();
    if (!std::isnan(asc::maximum<>{}(nan, 3.0f)) || asc::maximum<>{}(3.0f, nan) != 3.0f)
        return false;
    if (!std::isnan(asc::minimum<float>{}(nan, 3.0f)) || asc::minimum<float>{}(3.0f, nan) != 3.0f)
        return false;
    if (!std::isnan(asc::maximum<float>{}(signaling, 1.0f)))
        return false;
    if (asc::maximum<float>{}(infinity, 1.0f) != infinity || asc::minimum<float>{}(-infinity, 1.0f) != -infinity)
        return false;
    const float max_negative_zero = asc::maximum<>{}(-0.0f, 0.0f);
    const float max_positive_zero = asc::maximum<float>{}(0.0f, -0.0f);
    const float min_negative_zero = asc::minimum<float>{}(-0.0f, 0.0f);
    return std::signbit(max_negative_zero) && !std::signbit(max_positive_zero) && std::signbit(min_negative_zero);
}

bool conversions_and_domains()
{
    static_assert(!asc::is_associative_v<std::plus<unsigned>, unsigned>);
    static_assert(!asc::is_commutative_v<std::bit_or<unsigned>, unsigned>);
    if (asc::maximum<>{}(-1, 1u) != (std::numeric_limits<unsigned>::max)())
        return false;
    if (asc::minimum<>{}(-1, 1u) != 1u)
        return false;
    if (asc::maximum<>{}(16777217, 16777216.0f) != 16777216.0f)
        return false;
    volatile float large = 1.0e20f, negative = -1.0e20f, small = 3.25f;
    if ((large + negative) + small == large + (negative + small))
        return false;
    const long long maximum = (std::numeric_limits<int>::max)();
    return maximum + 1 > (std::numeric_limits<int>::max)() && maximum + (1 - 1) == maximum;
}

bool narrow_reference()
{
    // The independent reference uses unsigned arithmetic wider than both operands.
    for (unsigned left = 0; left < 256; ++left) {
        for (unsigned right = 0; right < 256; ++right) {
            const auto a = static_cast<unsigned char>(left);
            const auto b = static_cast<unsigned char>(right);
            const auto c = static_cast<unsigned char>((left * 17U + right * 31U) % 256U);
            const auto sum = asc::std::plus<unsigned char>{}(a, b);
            const auto product = asc::std::multiplies<unsigned char>{}(a, b);
            if (sum != (left + right) % 256U || product != (left * right) % 256U)
                return false;
            const auto add_left = asc::std::plus<unsigned char>{}(sum, c);
            const auto add_right = asc::std::plus<unsigned char>{}(a, asc::std::plus<unsigned char>{}(b, c));
            if (add_left != add_right || add_left != (left + right + c) % 256U)
                return false;
            const auto mul_left = asc::std::multiplies<unsigned char>{}(product, c);
            const auto mul_right =
                asc::std::multiplies<unsigned char>{}(a, asc::std::multiplies<unsigned char>{}(b, c));
            if (mul_left != mul_right || mul_left != (left * right * c) % 256U)
                return false;
        }
    }
    return true;
}

struct common_value {
    int value;
};
struct left_value : common_value {};
struct right_value : common_value {};
bool operator<(const left_value& left, const right_value& right) noexcept
{
    return left.value < right.value;
}
}  // namespace functional_host

namespace asc::std {
template <>
struct common_type<functional_host::left_value, functional_host::right_value> {
    using type = functional_host::common_value;
};
template <>
struct common_type<functional_host::right_value, functional_host::left_value> {
    using type = functional_host::common_value;
};
}  // namespace asc::std

int main()
{
    using functional_host::left_value;
    using functional_host::right_value;
    static_assert(asc::std::is_invocable_v<asc::maximum<>, left_value, right_value>);
    static_assert(!asc::std::is_invocable_v<asc::minimum<>, left_value, right_value>);
    static_assert(!asc::std::is_invocable_v<asc::maximum<>, right_value, left_value>);
    static_assert(asc::std::is_invocable_v<asc::minimum<>, right_value, left_value>);
    if (asc::maximum<>{}(left_value{{1}}, right_value{{9}}).value != 9)
        return 1;
    if (asc::minimum<>{}(right_value{{9}}, left_value{{1}}).value != 1)
        return 2;
    if (!functional_host::construction_exceptions() || !functional_host::comparison_exceptions())
        return 3;
    if (!functional_host::argument_evaluation() || !functional_host::floating_values())
        return 4;
    if (!functional_host::conversions_and_domains() || !functional_host::narrow_reference())
        return 5;
    return 0;
}
