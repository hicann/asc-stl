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

#include <asc/std/bit>
#include <asc/std/cmath>

#include <climits>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "../../../support/cmath_contracts.h"

namespace p = asc;
enum number { one = 1 };
enum class scoped_number : unsigned { one = 1 };
template <class A, class B, class = void>
struct can_divide : std::false_type {};
template <class A, class B>
struct can_divide<A, B, std::void_t<decltype(p::ceil_div(std::declval<A>(), std::declval<B>()))>> : std::true_type {};
static_assert(can_divide<int, int>::value);
static_assert(!can_divide<int, unsigned>::value);
static_assert(!can_divide<short, int>::value);
static_assert(!can_divide<bool, bool>::value);
static_assert(!can_divide<char, char>::value);
static_assert(!can_divide<wchar_t, wchar_t>::value);
static_assert(!can_divide<number, number>::value);
static_assert(!can_divide<scoped_number, scoped_number>::value);
static_assert(!can_divide<float, float>::value);
static_assert(std::is_same_v<decltype(p::ceil_div(short{}, short{1})), short>);
static_assert(std::is_same_v<decltype(p::integer_sqrt(1ULL)), unsigned long long>);
static_assert(p::ceil_div(-7, 3) == -2 && p::floor_div(-7, 3) == -3);
static_assert(p::ceil_div(7, -3) == -2 && p::floor_div(7, -3) == -3);
static_assert(p::ceil_div(-7, -3) == 3 && p::floor_div(-7, -3) == 2);
static_assert(p::ceil_div(ULLONG_MAX, 2ULL) == (1ULL << 63));
static_assert(p::round_up(ULLONG_MAX - 1, 2ULL) == ULLONG_MAX - 1);
static_assert(p::round_up(17, 6) == 18);
static_assert(p::integer_pow(0, 0) == 1 && p::integer_pow(0, 4U) == 0);
static_assert(p::integer_pow(-1, ULLONG_MAX) == -1);
static_assert(p::integer_pow(LLONG_MIN, 1) == LLONG_MIN);
static_assert(p::integer_pow(-2LL, 63U) == LLONG_MIN);
static_assert(p::integer_pow<signed char>(-2, static_cast<unsigned short>(7)) == -128);
static_assert(p::integer_sqrt(ULLONG_MAX) == 4294967295ULL);
static_assert(p::integer_sqrt(18446744065119617025ULL) == 4294967295ULL);
static_assert(p::integer_sqrt(18446744065119617024ULL) == 4294967294ULL);
static_assert(p::mul_hi(ULLONG_MAX, ULLONG_MAX) == ULLONG_MAX - 1);
static_assert(p::mul_hi(static_cast<unsigned char>(255), static_cast<unsigned char>(255)) == 254);
static_assert(asc::std::bit_width(0ULL) == 0);
static_assert(asc::std::bit_width(ULLONG_MAX) == 64);
static_assert(std::is_same_v<decltype(asc::std::bit_width(1ULL)), int>);
static_assert(std::is_same_v<decltype(asc::std::sqrt(1)), double>);
static_assert(std::is_same_v<decltype(asc::std::pow(2, 3)), double>);
static_assert(std::is_same_v<decltype(asc::std::ceil(1.0F)), float>);

// Observe normal language conversion of the three proposed non-template forms.
template <class V, class = void>
struct can_use_double_output : std::false_type {};
template <class V>
struct can_use_double_output<V,
    std::void_t<decltype(asc::sincos(std::declval<V>(), static_cast<double*>(nullptr), static_cast<double*>(nullptr)))>>
    : std::true_type {};
static_assert(can_use_double_output<int>::value && can_use_double_output<bool>::value);
static_assert(can_use_double_output<number>::value && !can_use_double_output<scoped_number>::value);

template <class T>
T read_integer(const std::string& s)
{
    if constexpr (std::is_signed_v<T>)
        return static_cast<T>(std::stoll(s));
    else
        return static_cast<T>(std::stoull(s));
}
template <class T>
bool check(char op, const std::string& as, const std::string& bs, const std::string& expected)
{
    const T a = read_integer<T>(as), e = read_integer<T>(expected);
    const T b = (op == 'p' || op == 's') ? T{0} : read_integer<T>(bs);
    T actual{};
    switch (op) {
        case 'c':
            actual = p::ceil_div(a, b);
            break;
        case 'f':
            actual = p::floor_div(a, b);
            break;
        case 'r':
            actual = p::round_up(a, b);
            break;
        case 'p':
            actual = p::integer_pow(a, std::stoull(bs));
            break;
        case 's':
            actual = p::integer_sqrt(a);
            break;
        case 'm':
            if constexpr (std::is_unsigned_v<T>)
                actual = p::mul_hi(a, b);
            break;
    }
    return actual == e;
}

template <class T>
bool check_floating()
{
    const T inputs[] = {T{0}, -T{0}, T{0.5}, T{1}, T{-1}, T{71476.0625}, std::numeric_limits<T>::max(),
        std::numeric_limits<T>::infinity(), -std::numeric_limits<T>::infinity(), std::numeric_limits<T>::quiet_NaN()};
    for (T value : inputs) {
        T sine{}, cosine{};
        asc::sincos(value, &sine, &cosine);
        if (!std::isfinite(value)) {
            if (!std::isnan(sine) || !std::isnan(cosine))
                return false;
        } else if (value == T{0}) {
            if (sine != T{0} || std::signbit(sine) != std::signbit(value) || cosine != T{1})
                return false;
        } else {
            const T tolerance = 8 * std::numeric_limits<T>::epsilon();
            if (std::abs(sine - std::sin(value)) > tolerance || std::abs(cosine - std::cos(value)) > tolerance)
                return false;
        }
    }
    return true;
}
bool floating_contracts()
{
    float sine{}, cosine{};
    asc::sincos(true, &sine, &cosine);
    if (sine != std::sin(1.0F) || cosine != std::cos(1.0F))
        return false;
    return check_floating<float>() && check_floating<double>() && check_floating<long double>();
}

int main()
{
    if (asc_stl_cmath_test::evaluate(~0ULL, -7) != 0)
        return 1;
    if (!floating_contracts())
        return 1;
    const std::string source = __FILE__;
    std::ifstream input(source.substr(0, source.find_last_of("/\\")) + "/integer-goldens.txt");
    if (!input)
        return 1;
    std::string type, a, b, expected;
    char op;
    std::size_t count = 0;
    while (input >> type >> op >> a >> b >> expected) {
        bool ok = false;
#define CMATH_CASE(KEY, T)                 \
    if (type == KEY) {                     \
        ok = check<T>(op, a, b, expected); \
    }
        CMATH_CASE("i8", signed char);
        CMATH_CASE("u8", unsigned char);
        CMATH_CASE("i16", short);
        CMATH_CASE("u16", unsigned short);
        CMATH_CASE("i32", int);
        CMATH_CASE("u32", unsigned int);
        CMATH_CASE("il", long);
        CMATH_CASE("ul", unsigned long);
        CMATH_CASE("ill", long long);
        CMATH_CASE("ull", unsigned long long);
#undef CMATH_CASE
        if (!ok) {
            std::cerr << type << ' ' << op << ' ' << a << ' ' << b << '\n';
            return 1;
        }
        ++count;
    }
    std::cout << "Exact integer oracle cases: " << count << '\n';
    return count >= 1000 ? 0 : 1;
}
