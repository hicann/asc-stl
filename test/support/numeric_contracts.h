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

#ifndef ASC_STL_TEST_SUPPORT_NUMERIC_CONTRACTS_H
#define ASC_STL_TEST_SUPPORT_NUMERIC_CONTRACTS_H

#include <asc/numeric>
#include <asc/std/type_traits>
#include <asc/std/utility>

namespace numeric_test {

// Dispatch API calls only; expected results are computed independently.
template <class T>
CANN_ASC_STL_API asc::checked_result<T> call(T left, T right, unsigned operation)
{
    switch (operation) {
        case 0:
            return asc::add_overflow(left, right);
        case 1:
            return asc::sub_overflow(left, right);
        case 2:
            return asc::mul_overflow(left, right);
        default:
            return asc::div_overflow(left, right);
    }
}

template <class T>
CANN_ASC_STL_API bool call(T left, T right, T& output, unsigned operation)
{
    switch (operation) {
        case 0:
            return asc::add_overflow(left, right, output);
        case 1:
            return asc::sub_overflow(left, right, output);
        case 2:
            return asc::mul_overflow(left, right, output);
        default:
            return asc::div_overflow(left, right, output);
    }
}

template <class L, class R, class = void>
struct arithmetic_callable : asc::std::false_type {};

template <class L, class R>
struct arithmetic_callable<L, R,
    asc::std::void_t<decltype(asc::add_overflow(asc::std::declval<L>(), asc::std::declval<R>())),
        decltype(asc::sub_overflow(asc::std::declval<L>(), asc::std::declval<R>())),
        decltype(asc::mul_overflow(asc::std::declval<L>(), asc::std::declval<R>())),
        decltype(asc::div_overflow(asc::std::declval<L>(), asc::std::declval<R>()))>> : asc::std::true_type {};

template <class L, class R, class Out, class = void>
struct output_callable : asc::std::false_type {};

template <class L, class R, class Out>
struct output_callable<L, R, Out,
    asc::std::void_t<decltype(asc::add_overflow(
                         asc::std::declval<L>(), asc::std::declval<R>(), asc::std::declval<Out&>())),
        decltype(asc::sub_overflow(asc::std::declval<L>(), asc::std::declval<R>(), asc::std::declval<Out&>())),
        decltype(asc::mul_overflow(asc::std::declval<L>(), asc::std::declval<R>(), asc::std::declval<Out&>())),
        decltype(asc::div_overflow(asc::std::declval<L>(), asc::std::declval<R>(), asc::std::declval<Out&>()))>>
    : asc::std::true_type {};

template <class To, class From, class = void>
struct cast_callable : asc::std::false_type {};

template <class To, class From>
struct cast_callable<To, From, asc::std::void_t<decltype(asc::overflow_cast<To>(asc::std::declval<From>()))>>
    : asc::std::true_type {};

template <class T>
CANN_ASC_STL_API constexpr bool equal(asc::checked_result<T> result, T expected, bool failed)
{
    return result.value == expected && result.failed == failed;
}

template <class T>
CANN_ASC_STL_API constexpr bool addition()
{
    constexpr T high = asc::std::numeric_limits<T>::max();
    T output = T{9};
    if (!equal(asc::add_overflow(high, T{1}), T{0}, true) || !asc::add_overflow(high, T{1}, output) || output != T{0})
        return false;
    if constexpr (asc::std::numeric_limits<T>::is_signed) {
        constexpr T low = asc::std::numeric_limits<T>::min();
        if (!equal(asc::add_overflow(low, T{-1}), T{0}, true) || !equal(asc::add_overflow(low, high), T{-1}, false))
            return false;
    }
    return equal(asc::add_overflow(T{2}, T{3}), T{5}, false);
}

template <class T>
CANN_ASC_STL_API constexpr bool subtraction()
{
    constexpr T low = asc::std::numeric_limits<T>::min();
    T output = T{9};
    if (!equal(asc::sub_overflow(low, T{1}), T{0}, true) || !asc::sub_overflow(low, T{1}, output) || output != T{0})
        return false;
    return equal(asc::sub_overflow(T{3}, T{2}), T{1}, false);
}

template <class T>
CANN_ASC_STL_API constexpr bool multiplication()
{
    constexpr T high = asc::std::numeric_limits<T>::max();
    T output = T{9};
    if (!equal(asc::mul_overflow(high, T{2}), T{0}, true) || !asc::mul_overflow(high, T{2}, output) || output != T{0})
        return false;
    return equal(asc::mul_overflow(T{2}, T{3}), T{6}, false) && equal(asc::mul_overflow(T{0}, high), T{0}, false);
}

template <class T>
CANN_ASC_STL_API constexpr bool division()
{
    T output = T{9};
    if (!equal(asc::div_overflow(T{0}, T{0}), T{0}, true) || !asc::div_overflow(T{1}, T{0}, output) || output != T{0})
        return false;
    if constexpr (asc::std::numeric_limits<T>::is_signed) {
        constexpr T low = asc::std::numeric_limits<T>::min();
        if (!equal(asc::div_overflow(low, T{-1}), T{0}, true) || !equal(asc::div_overflow(T{-7}, T{3}), T{-2}, false) ||
            !equal(asc::div_overflow(T{7}, T{-3}), T{-2}, false) ||
            !equal(asc::div_overflow(T{-7}, T{-3}), T{2}, false))
            return false;
    }
    return equal(asc::div_overflow(T{7}, T{3}), T{2}, false);
}

template <class T>
CANN_ASC_STL_API constexpr bool aliases()
{
    T value = T{3};
    if (asc::add_overflow(value, value, value) || value != T{6})
        return false;
    if (asc::sub_overflow(value, value, value) || value != T{0})
        return false;
    value = T{3};
    if (asc::mul_overflow(value, value, value) || value != T{9})
        return false;
    if (asc::div_overflow(value, value, value) || value != T{1})
        return false;
    value = asc::std::numeric_limits<T>::max();
    return asc::add_overflow(value, T{1}, value) && value == T{0};
}

template <class T>
CANN_ASC_STL_API constexpr bool contracts()
{
    asc::checked_result<T> defaulted;
    const asc::checked_result<T> initialized{};
    static_assert(asc::std::is_aggregate_v<asc::checked_result<T>>);
    static_assert(asc::std::is_standard_layout_v<asc::checked_result<T>>);
    static_assert(asc::std::is_trivially_copyable_v<asc::checked_result<T>>);
    static_assert(!asc::std::is_constructible_v<bool, asc::checked_result<T>>);
    static_assert(arithmetic_callable<const T, T>::value);
    static_assert(output_callable<T, T, T>::value);
    static_assert(!output_callable<T, T, const T>::value);
    static_assert(noexcept(asc::add_overflow(T{1}, T{2})));
    static_assert(noexcept(asc::sub_overflow(T{1}, T{2})));
    static_assert(noexcept(asc::mul_overflow(T{1}, T{2})));
    static_assert(noexcept(asc::div_overflow(T{1}, T{2})));
    static_assert(noexcept(asc::overflow_cast<T>(T{1})));
    if (defaulted.value != T{0} || defaulted.failed || initialized.value != T{0} || initialized.failed)
        return false;
    if (!addition<T>() || !subtraction<T>())
        return false;
    return multiplication<T>() && division<T>() && aliases<T>();
}

enum class excluded_enum { value };
struct convertible {
    CANN_ASC_STL_HOST_DEVICE operator int() const noexcept;
};
static_assert(!arithmetic_callable<int, unsigned>::value);
static_assert(!output_callable<int, int, long>::value);
static_assert(!arithmetic_callable<bool, bool>::value);
static_assert(!arithmetic_callable<char, char>::value);
static_assert(!arithmetic_callable<wchar_t, wchar_t>::value);
static_assert(!arithmetic_callable<char16_t, char16_t>::value);
static_assert(!arithmetic_callable<char32_t, char32_t>::value);
static_assert(!arithmetic_callable<excluded_enum, excluded_enum>::value);
static_assert(!arithmetic_callable<convertible, convertible>::value);
static_assert(!arithmetic_callable<float, float>::value);
static_assert(!cast_callable<bool, int>::value && !cast_callable<int, bool>::value);
static_assert(!cast_callable<const int, int>::value && !cast_callable<int&, int>::value);
static_assert(!cast_callable<int, excluded_enum>::value && !cast_callable<int, convertible>::value);
#if defined(__cpp_char8_t)
static_assert(!arithmetic_callable<char8_t, char8_t>::value);
#endif
#if defined(__SIZEOF_INT128__)
static_assert(!arithmetic_callable<__int128_t, __int128_t>::value);
static_assert(!cast_callable<int, __int128_t>::value && !cast_callable<__uint128_t, int>::value);
#endif
static_assert(contracts<signed char>() && contracts<unsigned char>());
static_assert(contracts<short>() && contracts<unsigned short>());
static_assert(contracts<int>() && contracts<unsigned>());
static_assert(contracts<long>() && contracts<unsigned long>());
static_assert(contracts<long long>() && contracts<unsigned long long>());
static_assert(equal(asc::overflow_cast<unsigned>(-1), 0U, true));
static_assert(equal(asc::overflow_cast<signed char>(128), static_cast<signed char>(0), true));
static_assert(equal(asc::overflow_cast<unsigned char>(256), static_cast<unsigned char>(0), true));
static_assert(equal(asc::overflow_cast<long long>(-1), -1LL, false));
static_assert(equal(asc::add_overflow<unsigned>(-1, 0), asc::std::numeric_limits<unsigned>::max(), false));

// Runtime inputs force the delivered operations into each Device compilation.
template <class T>
CANN_ASC_STL_API unsigned long long dynamic(T a, T b)
{
    const auto sum = asc::add_overflow(a, b);
    const auto difference = asc::sub_overflow(a, b);
    const auto product = asc::mul_overflow(a, b);
    const auto quotient = asc::div_overflow(a, b);
    const auto narrowed = asc::overflow_cast<signed char>(a);
    T output{};
    const bool f0 = asc::add_overflow(a, b, output);
    const bool f1 = asc::sub_overflow(a, b, output);
    const bool f2 = asc::mul_overflow(a, b, output);
    const bool f3 = asc::div_overflow(a, b, output);
    return static_cast<unsigned long long>(sum.value) ^ static_cast<unsigned long long>(difference.value) ^
        static_cast<unsigned long long>(product.value) ^ static_cast<unsigned long long>(quotient.value) ^
        static_cast<unsigned long long>(narrowed.value) ^ static_cast<unsigned long long>(output) ^
        static_cast<unsigned>(
            sum.failed + difference.failed + product.failed + quotient.failed + narrowed.failed + f0 + f1 + f2 + f3);
}

}  // namespace numeric_test

#endif  // ASC_STL_TEST_SUPPORT_NUMERIC_CONTRACTS_H
