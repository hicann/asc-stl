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

#ifndef ASC_STL_TEST_CMATH_CONTRACTS_H
#define ASC_STL_TEST_CMATH_CONTRACTS_H

#include <asc/cmath>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

namespace asc_stl_cmath_test {

enum ordinary { one = 1 };
enum class scoped : unsigned { one = 1 };
struct convertible {
    operator int() const;
};

template <class A, class B, class = void>
struct can_divide {
    static constexpr bool value = false;
};
template <class A, class B>
struct can_divide<A, B,
    ::asc::std::void_t<decltype(asc::ceil_div(::asc::std::declval<A>(), ::asc::std::declval<B>()))>> {
    static constexpr bool value = true;
};
template <class T, class E, class = void>
struct can_power {
    static constexpr bool value = false;
};
template <class T, class E>
struct can_power<T, E,
    ::asc::std::void_t<decltype(asc::integer_pow(::asc::std::declval<T>(), ::asc::std::declval<E>()))>> {
    static constexpr bool value = true;
};
template <class T, class = void>
struct can_multiply_high {
    static constexpr bool value = false;
};
template <class T>
struct can_multiply_high<T,
    ::asc::std::void_t<decltype(asc::mul_hi(::asc::std::declval<T>(), ::asc::std::declval<T>()))>> {
    static constexpr bool value = true;
};

static_assert(can_divide<int, int>::value);
static_assert(!can_divide<short, int>::value && !can_divide<int, unsigned>::value);
static_assert(!can_divide<long, long long>::value);
static_assert(!can_divide<bool, bool>::value && !can_divide<char, char>::value);
static_assert(!can_divide<wchar_t, wchar_t>::value && !can_divide<char16_t, char16_t>::value);
static_assert(!can_divide<char32_t, char32_t>::value);
#if __cplusplus >= 202002L
static_assert(!can_divide<char8_t, char8_t>::value);
#endif
static_assert(!can_divide<ordinary, ordinary>::value && !can_divide<scoped, scoped>::value);
static_assert(!can_divide<float, float>::value && !can_divide<convertible, convertible>::value);
static_assert(!can_power<bool, int>::value && !can_power<int, bool>::value);
static_assert(!can_power<int, ordinary>::value && !can_power<int, double>::value);
static_assert(!can_multiply_high<int>::value && !can_multiply_high<bool>::value);
static_assert(can_multiply_high<unsigned char>::value && can_multiply_high<unsigned long long>::value);
static_assert(noexcept(asc::ceil_div(1, 2)) && noexcept(asc::floor_div(1, 2)));
static_assert(noexcept(asc::round_up(1, 2)) && noexcept(asc::integer_pow(2, 3)));
static_assert(noexcept(asc::integer_sqrt(1)) && noexcept(asc::mul_hi(1u, 2u)));
static_assert(asc::ceil_div(-7, 3) == -2 && asc::floor_div(-7, 3) == -3);
static_assert(asc::ceil_div(7, -3) == -2 && asc::floor_div(7, -3) == -3);
static_assert(asc::ceil_div(-7, -3) == 3 && asc::floor_div(-7, -3) == 2);
static_assert(asc::ceil_div(static_cast<signed char>(-128), static_cast<signed char>(1)) == -128);
static_assert(asc::integer_pow(0, 0) == 1 && asc::integer_pow(0, 7) == 0);
static_assert(asc::integer_pow(-2LL, 63U) == (-9223372036854775807LL - 1));
static_assert(asc::integer_pow(-9223372036854775807LL - 1, 1) == (-9223372036854775807LL - 1));
static_assert(asc::integer_pow(-1, ~0ULL) == -1 && asc::integer_pow(1, ~0ULL) == 1);
static_assert(asc::integer_sqrt(~0ULL) == 4294967295ULL);
static_assert(asc::integer_sqrt(18446744065119617024ULL) == 4294967294ULL);
static_assert(asc::mul_hi(~0ULL, ~0ULL) == ~0ULL - 1);

template <class T>
CANN_ASC_STL_API constexpr int typed_contract(T value) noexcept
{
    static_assert(::asc::std::is_same_v<decltype(asc::ceil_div(value, value)), T>);
    static_assert(::asc::std::is_same_v<decltype(asc::floor_div(value, value)), T>);
    static_assert(::asc::std::is_same_v<decltype(asc::round_up(value, value)), T>);
    static_assert(::asc::std::is_same_v<decltype(asc::integer_pow(value, 2U)), T>);
    static_assert(::asc::std::is_same_v<decltype(asc::integer_sqrt(value)), T>);
    int failures = asc::ceil_div(value, T{3}) != T{3};
    failures += asc::floor_div(value, T{3}) != T{2};
    failures += asc::round_up(value, T{3}) != T{9};
    failures += asc::integer_pow(value, static_cast<unsigned short>(2)) != T{49};
    failures += asc::integer_sqrt(value) != T{2};
    if constexpr (::asc::std::is_unsigned_v<T>) {
        static_assert(::asc::std::is_same_v<decltype(asc::mul_hi(value, value)), T>);
        failures += asc::mul_hi(value, value) != T{0};
    }
    return failures;
}

// Inputs are loaded from GM by the runtime kernel. Expected values are exact
// integer constants, independently computed with Python arbitrary precision.
CANN_ASC_STL_API constexpr int evaluate(unsigned long long maximum, long long negative) noexcept
{
    const int seven = static_cast<int>(maximum & 7ULL);
    int failures = typed_contract(static_cast<signed char>(seven));
    failures += typed_contract(static_cast<unsigned char>(seven));
    failures += typed_contract(static_cast<short>(seven));
    failures += typed_contract(static_cast<unsigned short>(seven));
    failures += typed_contract(seven) + typed_contract(static_cast<unsigned>(seven));
    failures += typed_contract(static_cast<long>(seven)) + typed_contract(static_cast<unsigned long>(seven));
    failures += typed_contract(static_cast<long long>(seven)) + typed_contract(static_cast<unsigned long long>(seven));
    failures += asc::ceil_div(maximum, 2ULL) != 9223372036854775808ULL;
    failures += asc::floor_div(maximum, 2ULL) != 9223372036854775807ULL;
    failures += asc::round_up(maximum - 1, 2ULL) != maximum - 1;
    failures += asc::round_up(maximum, 1ULL) != maximum;
    failures += asc::integer_sqrt(maximum) != 4294967295ULL;
    failures += asc::integer_sqrt(maximum - 8589934591ULL) != 4294967294ULL;
    failures += asc::integer_pow(negative + 5, 63U) != (-9223372036854775807LL - 1);
    failures += asc::ceil_div(negative, 3LL) != -2;
    failures += asc::floor_div(negative, 3LL) != -3;
    failures += asc::ceil_div(negative, -3LL) != 3;
    failures += asc::floor_div(negative, -3LL) != 2;
    failures += asc::mul_hi(maximum, maximum) != maximum - 1;
    failures += asc::mul_hi(static_cast<unsigned short>(maximum), static_cast<unsigned short>(maximum)) != 65534;
    return failures;
}

}  // namespace asc_stl_cmath_test

#endif  // ASC_STL_TEST_CMATH_CONTRACTS_H
