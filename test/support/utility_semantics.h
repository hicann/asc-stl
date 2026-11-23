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

#ifndef ASC_STL_TEST_UTILITY_SEMANTICS_H
#define ASC_STL_TEST_UTILITY_SEMANTICS_H

#include <asc/utility>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/limits>

namespace asc_stl_utility_test {

template <class I>
struct recorder {
    I values[16]{};
    unsigned count = 0;

    template <class Tag>
    CANN_ASC_STL_API constexpr void operator()(Tag) & noexcept
    {
        static_assert(asc::std::is_same_v<Tag, asc::std::integral_constant<I, Tag::value>>);
        values[count++] = Tag::value;
    }
};

template <class I, asc::std::size_t N>
CANN_ASC_STL_API constexpr bool matches(const recorder<I>& actual, const I (&expected)[N]) noexcept
{
    if (actual.count != N) {
        return false;
    }
    for (unsigned i = 0; i < N; ++i) {
        if (actual.values[i] != expected[i]) {
            return false;
        }
    }
    return true;
}

template <class I>
CANN_ASC_STL_API constexpr unsigned integer_sequences()
{
    recorder<I> count;
    asc::static_for<I, 4>(count);
    const I zero_based[] = {0, 1, 2, 3};
    recorder<I> strided;
    asc::static_for<I, 1, 8, 3>(strided);
    const I positive[] = {1, 4, 7};
    recorder<I> last;
    constexpr I maximum = asc::std::numeric_limits<I>::max();
    asc::static_for<I, maximum - 1, maximum, 2>(last);
    const I near_limit[] = {static_cast<I>(maximum - 1)};
    return !matches(count, zero_based) + !matches(strided, positive) + !matches(last, near_limit);
}

template <class I>
CANN_ASC_STL_API constexpr unsigned signed_sequences()
{
    recorder<I> descending;
    asc::static_for<I, 5, 0, -2>(descending);
    const I negative_step[] = {5, 3, 1};
    recorder<I> cross_zero;
    asc::static_for<I, -5, 7, 3>(cross_zero);
    const I across[] = {-5, -2, 1, 4};
    constexpr I minimum = asc::std::numeric_limits<I>::min();
    constexpr I maximum = asc::std::numeric_limits<I>::max();
    recorder<I> last;
    asc::static_for<I, minimum + 1, minimum, -2>(last);
    const I lower_limit[] = {static_cast<I>(minimum + 1)};
    recorder<I> minimum_step;
    asc::static_for<I, maximum, minimum, minimum>(minimum_step);
    const I large_step[] = {maximum, -1};
    recorder<I> wide_distance;
    asc::static_for<I, minimum, maximum, maximum>(wide_distance);
    const I large_distance[] = {minimum, -1, static_cast<I>(maximum - 1)};
    return !matches(descending, negative_step) + !matches(cross_zero, across) + !matches(last, lower_limit) +
        !matches(minimum_step, large_step) + !matches(wide_distance, large_distance);
}

struct noncopyable_operation {
    int calls = 0;
    CANN_ASC_STL_API constexpr noncopyable_operation() noexcept = default;
    noncopyable_operation(const noncopyable_operation&) = delete;
    noncopyable_operation(noncopyable_operation&&) = delete;

    template <class Tag>
    CANN_ASC_STL_API constexpr void operator()(Tag) & noexcept
    {
        ++calls;
    }
};

struct poison {
    template <class Tag>
    CANN_ASC_STL_API void operator()(Tag) noexcept
    {
        static_assert(sizeof(Tag) == 0, "an empty sequence instantiated its callback");
    }
};

struct conditional_operation {
    template <class Tag>
    CANN_ASC_STL_API void operator()(Tag) noexcept(Tag::value != 2)
    {}
};

template <class T, class = void>
struct supports_range : asc::std::false_type {};

template <class T>
struct supports_range<T,
    asc::std::void_t<decltype(asc::in_range(asc::std::declval<T>(), asc::std::declval<T>(), asc::std::declval<T>()))>>
    : asc::std::true_type {};

template <class T, class = void>
struct supports_count : asc::std::false_type {};

template <class T>
struct supports_count<T, asc::std::void_t<decltype(asc::static_for<T, T{0}>(0))>> : asc::std::true_type {};

static_assert(supports_count<unsigned long long>::value);
static_assert(!supports_count<bool>::value && !supports_count<char>::value);
static_assert(!supports_count<const int>::value);
static_assert(!supports_range<bool>::value && !supports_range<char>::value);
static_assert(!supports_range<int*>::value && !supports_range<poison>::value);

enum class excluded_index : unsigned { zero };
static_assert(!supports_count<excluded_index>::value && !supports_range<excluded_index>::value);

struct move_value {
    int value;
    CANN_ASC_STL_API explicit constexpr move_value(int n) noexcept : value(n)
    {}
    move_value(const move_value&) = delete;
    CANN_ASC_STL_API constexpr move_value(move_value&& other) noexcept : value(other.value)
    {
        other.value = -1;
    }
};

CANN_ASC_STL_API constexpr unsigned argument_categories()
{
    int lvalue = 0;
    asc::static_for<3>([](auto, int& value) noexcept { ++value; }, lvalue);
    move_value input{9};
    int observed[2]{};
    asc::static_for<2>([&](auto index, move_value value) noexcept { observed[index.value] = value.value; },
        static_cast<move_value&&>(input));
    return lvalue != 3 || observed[0] != 9 || observed[1] != -1 || input.value != -1;
}

CANN_ASC_STL_API constexpr unsigned auto_and_empty()
{
    recorder<int> count;
    asc::static_for<4>(count);
    const int expected_count[] = {0, 1, 2, 3};
    recorder<unsigned> strided;
    asc::static_for<1u, 8u, 3u>(strided);
    const unsigned expected_range[] = {1, 4, 7};
    recorder<int> default_step;
    asc::static_for<1, 4>(default_step);
    const int expected_default[] = {1, 2, 3};
    noncopyable_operation operation;
    asc::static_for<4>(operation);
    asc::static_for<2>(noncopyable_operation{});
    asc::static_for<0>(poison{});
    asc::static_for<-7>(0);
    asc::static_for<2, 2, -1>(poison{});
    asc::static_for<4, 0>(0);
    asc::static_for<0, 4, -1>(0);
    static_assert(noexcept(asc::static_for<0>(0)));
    static_assert(noexcept(asc::static_for<0, 2>(conditional_operation{})));
    static_assert(!noexcept(asc::static_for<3>(conditional_operation{})));
    return !matches(count, expected_count) + !matches(strided, expected_range) +
        !matches(default_step, expected_default) + (operation.calls != 4);
}

template <class T>
CANN_ASC_STL_API constexpr unsigned numeric_ranges()
{
    unsigned failures = 0;
    failures += !asc::in_range(T{3}, T{3}, T{7});
    failures += !asc::in_range(T{7}, T{3}, T{7});
    failures += !asc::in_range(T{5}, T{3}, T{7});
    failures += asc::in_range(T{2}, T{3}, T{7});
    failures += asc::in_range(T{8}, T{3}, T{7});
    failures += !asc::in_range(T{5}, T{5}, T{5});
    failures += asc::in_range(T{4}, T{5}, T{5});
    failures += asc::in_range(T{5}, T{7}, T{3});
    static_assert(noexcept(asc::in_range(T{0}, T{0}, T{1})));
    return failures;
}

CANN_ASC_STL_API constexpr unsigned evaluate()
{
    unsigned failures = auto_and_empty() + argument_categories();
    failures += integer_sequences<signed char>() + integer_sequences<unsigned char>();
    failures += integer_sequences<short>() + integer_sequences<unsigned short>();
    failures += integer_sequences<int>() + integer_sequences<unsigned>();
    failures += integer_sequences<long>() + integer_sequences<unsigned long>();
    failures += integer_sequences<long long>() + integer_sequences<unsigned long long>();
    failures += signed_sequences<signed char>() + signed_sequences<short>();
    failures += signed_sequences<int>() + signed_sequences<long>() + signed_sequences<long long>();
    failures += numeric_ranges<signed char>() + numeric_ranges<unsigned char>();
    failures += numeric_ranges<short>() + numeric_ranges<unsigned short>();
    failures += numeric_ranges<int>() + numeric_ranges<unsigned>();
    failures += numeric_ranges<long>() + numeric_ranges<unsigned long>();
    failures += numeric_ranges<long long>() + numeric_ranges<unsigned long long>();
    failures += numeric_ranges<float>();
    return failures;
}

}  // namespace asc_stl_utility_test

#endif  // ASC_STL_TEST_UTILITY_SEMANTICS_H
