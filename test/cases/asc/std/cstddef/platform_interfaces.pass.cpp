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

#include <asc/std/cstdalign>
#include <asc/std/cstdbool>
#include <asc/std/version>

#if CANN_ASC_STL_DETAIL_HAS_CXX20()
#if defined(__alignas_is_defined) || defined(__bool_true_false_are_defined)
#error "Legacy macros must not be provided in C++20"
#endif
#else
static_assert(__alignas_is_defined == 1);
static_assert(__bool_true_false_are_defined == 1);
#endif

#include <asc/std/cerrno>
#include <asc/std/charconv>
#include <asc/std/cinttypes>
#include <asc/std/cstdint>
#include <asc/std/cstdlib>
#include <asc/std/cstring>
#include <asc/std/ctime>
#include <asc/std/cuchar>
#include <asc/std/cwchar>
#include <asc/std/execution>
#include <asc/std/limits>

#include <charconv>
#include <clocale>
#include <cstdio>
#include <cstdint>
#include <ctime>
#include <limits>
#include <string_view>
#include <type_traits>

namespace {

namespace ast = asc::std;

static_assert(std::is_same_v<ast::intptr_t, std::intptr_t>);
static_assert(std::is_same_v<ast::intmax_t, std::intmax_t> && std::is_same_v<ast::uintmax_t, std::uintmax_t>);
static_assert(std::is_same_v<ast::clock_t, std::clock_t> && std::is_same_v<ast::time_t, std::time_t>);
static_assert(std::is_same_v<decltype(ast::numeric_limits<float>::round_style), const ast::float_round_style>);
static_assert(std::is_same_v<decltype(ast::numeric_limits<float>::has_denorm), const ast::float_denorm_style>);
static_assert(static_cast<int>(ast::round_to_nearest) == static_cast<int>(std::round_to_nearest));
static_assert(static_cast<int>(ast::denorm_present) == static_cast<int>(std::denorm_present));
static_assert(WCHAR_MIN == std::numeric_limits<wchar_t>::min() && WCHAR_MAX == std::numeric_limits<wchar_t>::max());
static_assert(std::is_same_v<std::remove_cv_t<decltype(ast::execution::seq)>, ast::execution::sequenced_policy>);
static_assert(std::is_same_v<std::remove_cv_t<decltype(ast::execution::unseq)>, ast::execution::unsequenced_policy>);
static_assert(
    std::is_same_v<std::remove_cv_t<decltype(ast::execution::par_unseq)>, ast::execution::parallel_unsequenced_policy>);
static_assert(ast::is_execution_policy<ast::execution::sequenced_policy>::value);
static_assert(ast::is_execution_policy<ast::execution::parallel_unsequenced_policy>::value);
static_assert(!ast::is_execution_policy<int>::value);

static_assert(CANN_ASC_STL_HAS_ALLOCATE_AT_LEAST == 1);
static_assert(CANN_ASC_STL_HAS_CONCEPT_PREDICATES == 1);
static_assert(CANN_ASC_STL_HAS_EXPECTED == 1);
static_assert(CANN_ASC_STL_HAS_INPLACE_VECTOR == 1);
static_assert(CANN_ASC_STL_HAS_MDSPAN == 1);
static_assert(CANN_ASC_STL_HAS_OPTIONAL_REFERENCE == 1);
static_assert(CANN_ASC_STL_HAS_PHILOX == 1);
static_assert(CANN_ASC_STL_HAS_SPAN == 1);
static_assert(CANN_ASC_STL_HAS_SUBMDSPAN == 1);
static_assert(CANN_ASC_STL_HAS_TO_ARRAY == 1);
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
static_assert(CANN_ASC_STL_HAS_NATIVE_CONCEPTS == 1);
static_assert(CANN_ASC_STL_HAS_FORMAT == 1);
static_assert(CANN_ASC_STL_HAS_FORMAT_TO_N_RESULT == 1);
#else
static_assert(CANN_ASC_STL_HAS_NATIVE_CONCEPTS == 0);
static_assert(CANN_ASC_STL_HAS_FORMAT == 0);
static_assert(CANN_ASC_STL_HAS_FORMAT_TO_N_RESULT == 1);
#endif

bool check_integers_and_time()
{
    const int numbers[] = {-19, -5, 0, 7, 21};
    const int denominators[] = {-4, -1, 1, 4};
    for (int n : numbers) {
        for (int d : denominators) {
            const ast::div_t small = ast::div(n, d);
            const ast::ldiv_t large = ast::ldiv(n, d);
            const ast::lldiv_t largest = ast::lldiv(n, d);
            const ast::imaxdiv_t widest = ast::imaxdiv(n, d);
            if (small.quot != n / d || small.rem != n % d || large.quot != n / d || large.rem != n % d ||
                largest.quot != n / d || largest.rem != n % d || widest.quot != n / d || widest.rem != n % d) {
                return false;
            }
        }
    }

    char text[48]{};
    const ast::intmax_t signed_value = -76543;
    const ast::uintmax_t unsigned_value = 123456;
    const int digits = std::snprintf(text, sizeof(text), "%" PRIdMAX "/%" PRIuMAX, signed_value, unsigned_value);
    if (digits != 13 || std::string_view(text) != "-76543/123456") {
        return false;
    }

    int object = 19;
    const ast::intptr_t bits = reinterpret_cast<ast::intptr_t>(&object);
    const int* null_pointer = NULL;
    const ast::timespec exact{-1, 999999999};
    const ast::clock_t first = ast::clock();
    const ast::clock_t next = ast::clock();
    const auto unsupported = static_cast<ast::clock_t>(-1);
    return reinterpret_cast<int*>(bits) == &object && null_pointer == nullptr && exact.tv_sec == -1 &&
        exact.tv_nsec == 999999999 && (first == unsupported || next == unsupported || next >= first);
}

bool check_character_conversion()
{
    const char values[] = {std::numeric_limits<char>::min(), 0, 17, std::numeric_limits<char>::max()};
    const int bases[] = {2, 10, 16, 36};
    for (int base : bases) {
        for (char value : values) {
            char ours[32]{};
            char expected[32]{};
            const auto actual = ast::to_chars(ours, ours + sizeof(ours), value, base);
            const auto reference = std::to_chars(expected, expected + sizeof(expected), static_cast<int>(value), base);
            if (actual.ec != ast::errc{} || reference.ec != std::errc{} ||
                actual.ptr - ours != reference.ptr - expected ||
                std::string_view(ours, static_cast<std::size_t>(actual.ptr - ours)) !=
                    std::string_view(expected, static_cast<std::size_t>(reference.ptr - expected))) {
                return false;
            }
            char restored = 'z';
            const auto parsed = ast::from_chars(ours, actual.ptr, restored, base);
            if (parsed.ec != ast::errc{} || parsed.ptr != actual.ptr || restored != value) {
                return false;
            }
        }
    }
    char value = 'b';
    const char malformed[] = "-?";
    const auto bad = ast::from_chars(malformed, malformed + 2, value);
    return bad.ec == ast::errc::invalid_argument && bad.ptr == malformed && value == 'b';
}

bool check_bounded_strings()
{
    const unsigned budgets[] = {0, 1, 2, 3, 5};
    for (auto n : budgets) {
        char destination[8]{'x', '#', '#', '#', '#', '#', '#', '#'};
        char source[4]{'a', 'b', 'c', '\0'};
        if (ast::strncpy(destination, source, n) != destination || destination[7] != '#') {
            return false;
        }
        for (unsigned i = 0; i < n; ++i) {
            if (destination[i] != (i < 3 ? source[i] : '\0')) {
                return false;
            }
        }
        char append[9]{'p', ':', '\0', '#', '#', '#', '#', '#', '#'};
        const unsigned expected = n < 3 ? n : 3;
        if (ast::strncat(append, source, n) != append || append[0] != 'p' || append[1] != ':' ||
            append[2 + expected] != '\0' || append[8] != '#') {
            return false;
        }
        for (unsigned i = 0; i < expected; ++i) {
            if (append[2 + i] != source[i]) {
                return false;
            }
        }
    }
    return true;
}

bool check_multibyte()
{
    if (!std::setlocale(LC_CTYPE, "C")) {
        return false;
    }
    const char inputs[] = {'a', 'Z', '\0'};
    for (char input : inputs) {
        ast::mbstate_t state{};
        char encoded[4]{'#', '#', '#', '#'};
        const char16_t expected16 = static_cast<char16_t>(input);
        const char32_t expected32 = static_cast<char32_t>(input);
        const std::size_t read = input == '\0' ? 0 : 1;
        char16_t decoded16{};
        char32_t decoded32{};
        if (ast::c16rtomb(encoded, expected16, &state) != 1 || encoded[0] != input || encoded[1] != '#' ||
            ast::mbrtoc16(&decoded16, encoded, 1, &state) != read || decoded16 != expected16 ||
            ast::c32rtomb(encoded, expected32, &state) != 1 || encoded[0] != input || encoded[1] != '#' ||
            ast::mbrtoc32(&decoded32, encoded, 1, &state) != read || decoded32 != expected32) {
            return false;
        }
#if CANN_ASC_STL_DETAIL_HAS_CXX20()
        char8_t decoded8{};
        const auto expected8 = static_cast<char8_t>(input);
        if (ast::c8rtomb(encoded, expected8, &state) != 1 || encoded[0] != input || encoded[1] != '#' ||
            ast::mbrtoc8(&decoded8, encoded, 1, &state) != read || decoded8 != expected8) {
            return false;
        }
#endif
    }

    ast::mbstate_t state{};
    char32_t scalar{};
    const char invalid[] = {static_cast<char>(0xff), '\0'};
    errno = 0;
    return ast::mbrtoc32(&scalar, invalid, 1, &state) == static_cast<std::size_t>(-1) && errno == EILSEQ;
}

}  // namespace

int main()
{
    if (!check_integers_and_time()) {
        return 1;
    }
    if (!check_character_conversion()) {
        return 2;
    }
    if (!check_bounded_strings()) {
        return 3;
    }
    return check_multibyte() ? 0 : 4;
}
