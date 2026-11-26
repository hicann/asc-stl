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

#include <asc/std/limits>

#include <cmath>
#include <limits>
#include <type_traits>

static_assert(std::is_same_v<decltype(asc::std::round_to_nearest), asc::std::float_round_style>);
static_assert(std::is_same_v<decltype(asc::std::denorm_present), asc::std::float_denorm_style>);
static_assert(asc::std::numeric_limits<const int>::min() == std::numeric_limits<int>::min() &&
    asc::std::numeric_limits<volatile int>::max() == std::numeric_limits<int>::max() &&
    asc::std::numeric_limits<const volatile int>::digits == std::numeric_limits<int>::digits);

template <class T>
constexpr bool same_facets()
{
    using a = asc::std::numeric_limits<T>;
    using b = std::numeric_limits<T>;
    return a::is_specialized == b::is_specialized && a::is_integer == b::is_integer && a::is_signed == b::is_signed &&
        a::is_exact == b::is_exact && a::digits == b::digits && a::digits10 == b::digits10 &&
        a::max_digits10 == b::max_digits10 && a::radix == b::radix && a::min() == b::min() &&
        a::lowest() == b::lowest() && a::max() == b::max() && a::epsilon() == b::epsilon() &&
        a::min_exponent == b::min_exponent && a::max_exponent == b::max_exponent &&
        a::min_exponent10 == b::min_exponent10 && a::max_exponent10 == b::max_exponent10 &&
        a::has_infinity == b::has_infinity && a::infinity() == b::infinity() && a::has_quiet_NaN == b::has_quiet_NaN &&
        a::has_signaling_NaN == b::has_signaling_NaN && a::denorm_min() == b::denorm_min() &&
        static_cast<int>(a::has_denorm) == static_cast<int>(b::has_denorm) &&
        a::has_denorm_loss == b::has_denorm_loss && a::is_iec559 == b::is_iec559 && a::is_bounded == b::is_bounded &&
        a::is_modulo == b::is_modulo && a::round_error() == b::round_error() &&
        static_cast<int>(a::round_style) == static_cast<int>(b::round_style) &&
        a::tinyness_before == b::tinyness_before;
}

template <class... Ts>
constexpr bool standard_types()
{
    return (same_facets<Ts>() && ...);
}
static_assert(standard_types<bool, char, signed char, unsigned char, wchar_t, char16_t, char32_t, short, unsigned short,
    int, unsigned, long, unsigned long, long long, unsigned long long, float, double, long double>());
static_assert(standard_types<const int, volatile unsigned, const volatile double>());
static_assert(!asc::std::numeric_limits<void*>::is_specialized && asc::std::numeric_limits<void*>::min() == nullptr);
static_assert(asc::std::round_indeterminate == -1 && asc::std::round_toward_zero == 0 &&
    asc::std::round_to_nearest == 1 && asc::std::round_toward_infinity == 2 &&
    asc::std::round_toward_neg_infinity == 3);
static_assert(asc::std::denorm_indeterminate == -1 && asc::std::denorm_absent == 0 && asc::std::denorm_present == 1);

#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
using quad = asc::std::numeric_limits<__float128>;
using quad_word = unsigned __int128;
constexpr quad_word quad_top = static_cast<quad_word>(0x7fffU) << 112;
static_assert(quad::digits == 113 && quad::min_exponent == -16381 && quad::max_exponent == 16384);
static_assert(quad::min_exponent10 == -4931 && quad::max_exponent10 == 4932 && quad::max_digits10 == 36);
static_assert(asc::std::bit_cast<quad_word>(quad::min()) == (quad_word{1} << 112));
static_assert(asc::std::bit_cast<quad_word>(quad::max()) == quad_top - 1);
static_assert(asc::std::bit_cast<quad_word>(quad::lowest()) == ((quad_word{1} << 127) | (quad_top - 1)));
static_assert(asc::std::bit_cast<quad_word>(quad::epsilon()) == (quad_word{16383 - 112} << 112));
static_assert(quad::round_error() == 0.5F && asc::std::bit_cast<quad_word>(quad::denorm_min()) == 1);
static_assert(asc::std::bit_cast<quad_word>(quad::infinity()) == quad_top);
static_assert(asc::std::bit_cast<quad_word>(quad::quiet_NaN()) == (quad_top | (quad_word{1} << 111)));
static_assert((asc::std::bit_cast<quad_word>(quad::signaling_NaN()) & quad_top) == quad_top &&
    asc::std::bit_cast<quad_word>(quad::signaling_NaN()) != quad_top);
#endif

int main()
{
    using a = asc::std::numeric_limits<float>;
    return std::isnan(a::quiet_NaN()) && std::isnan(a::signaling_NaN()) && !a::traps ? 0 : 1;
}
