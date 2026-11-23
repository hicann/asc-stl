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

#include <limits>
#include <type_traits>

#include "support/utility_semantics.h"

namespace {

struct token {
    int value;
    explicit token(int n) noexcept : value(n)
    {}
    token(const token&) = delete;
    token(token&& other) noexcept : value(other.value)
    {
        other.value = -1;
    }
};

struct throwing_result {
    ~throwing_result() noexcept(false)
    {}
};

struct result_operation {
    throwing_result operator()(asc::std::integral_constant<int, 0>) & noexcept;
};

struct maybe_copy {
    maybe_copy() = default;
    maybe_copy(const maybe_copy&) noexcept(false);
};

struct copying_operation {
    template <class Tag>
    void operator()(Tag, maybe_copy) & noexcept;
};

static_assert(asc_stl_utility_test::evaluate() == 0);
static_assert(!noexcept(asc::static_for<1>(asc::std::declval<result_operation&>())));
static_assert(!noexcept(asc::static_for<1>(asc::std::declval<copying_operation&>(), asc::std::declval<maybe_copy&>())));
static_assert(noexcept(asc::static_for<0>(asc::std::declval<result_operation&>())));

unsigned forwarding()
{
    int consumed[2]{};
    int calls = 0;
    token data{9};
    asc::static_for<2>([&](auto, token value) { consumed[calls++] = value.value; }, static_cast<token&&>(data));
    int lvalue = 0;
    asc::static_for<3>([](auto, int& value) noexcept { ++value; }, lvalue);
    int empty_evaluations = 0;
    asc::static_for<0>(0, ++empty_evaluations);
    int constructions = 0;
    asc::static_for<0>(0, [&] {
        ++constructions;
        return token{1};
    }());
    return calls != 2 || consumed[0] != 9 || consumed[1] != -1 || data.value != -1 || lvalue != 3 ||
        empty_evaluations != 1 || constructions != 1;
}

struct result_event {
    int* events;
    int* count;
    int index;
    ~result_event() noexcept
    {
        events[(*count)++] = index + 10;
    }
    int operator,(const result_event&) const
    {
        return 1;
    }
};

unsigned sequencing()
{
    int events[6]{};
    int count = 0;
    asc::static_for<3>([&](auto index) noexcept {
        events[count++] = index.value;
        return result_event{events, &count, index.value};
    });
    const int expected[] = {0, 10, 1, 11, 2, 12};
    for (int i = 0; i < 6; ++i) {
        if (events[i] != expected[i]) {
            return 1;
        }
    }
    return count != 6;
}

unsigned exceptions()
{
    int calls = 0;
    bool caught = false;
    try {
        asc::static_for<5>([&](auto index) {
            ++calls;
            if constexpr (index.value == 2) {
                throw 7;
            }
        });
    } catch (int value) {
        caught = value == 7;
    }
    return !caught || calls != 3;
}

template <class T>
unsigned floating_ranges()
{
    const T nan = std::numeric_limits<T>::quiet_NaN();
    const T infinity = std::numeric_limits<T>::infinity();
    unsigned failures = asc_stl_utility_test::numeric_ranges<T>();
    failures += asc::in_range(nan, T{0}, T{1});
    failures += asc::in_range(T{0}, nan, T{1});
    failures += asc::in_range(T{0}, T{0}, nan);
    failures += !asc::in_range(infinity, T{0}, infinity);
    failures += !asc::in_range(-infinity, -infinity, T{0});
    failures += asc::in_range(infinity, -infinity, T{0});
    failures += !asc::in_range(T{-0.0}, T{0.0}, T{-0.0});
    failures += !asc::in_range(T{0.0}, T{-0.0}, T{0.0});
    return failures;
}

template <class A, class B, class C, class = void>
struct mixed_range : std::false_type {};

template <class A, class B, class C>
struct mixed_range<A, B, C,
    std::void_t<decltype(asc::in_range(std::declval<A>(), std::declval<B>(), std::declval<C>()))>> : std::true_type {};

static_assert(!mixed_range<unsigned, int, int>::value);
static_assert(!mixed_range<float, double, double>::value);
static_assert(!asc_stl_utility_test::supports_count<wchar_t>::value);
static_assert(!asc_stl_utility_test::supports_range<wchar_t>::value);
static_assert(asc_stl_utility_test::supports_range<const long double>::value);

struct converted_value {
    operator int() const noexcept(false);
};

static_assert(!noexcept(asc::in_range<int>(converted_value{}, 0, 1)));

unsigned typed_default_step()
{
    asc_stl_utility_test::recorder<short> sequence;
    asc::static_for<short, 1, 4>(sequence);
    const short expected[] = {1, 2, 3};
    return !asc_stl_utility_test::matches(sequence, expected);
}

unsigned integer_ranges()
{
    using I = long long;
    using U = unsigned long long;
    constexpr I low = std::numeric_limits<I>::min();
    constexpr I high = std::numeric_limits<I>::max();
    constexpr U top = std::numeric_limits<U>::max();
    unsigned failures = !asc::in_range(low, low, high) || !asc::in_range(high, low, high);
    failures += asc::in_range(I{0}, high, low);
    failures += !asc::in_range(top, U{0}, top);
    failures += asc::in_range(top, U{1}, top - 1);
    failures += asc::in_range(U{0}, top, U{0});
    return failures;
}

}  // namespace

int main()
{
    return static_cast<int>(asc_stl_utility_test::evaluate() + forwarding() + sequencing() + exceptions() +
        floating_ranges<float>() + floating_ranges<double>() + floating_ranges<long double>() + integer_ranges() +
        typed_default_step());
}
