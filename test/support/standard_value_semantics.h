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

#ifndef ASC_STL_TEST_STANDARD_VALUE_SEMANTICS_H
#define ASC_STL_TEST_STANDARD_VALUE_SEMANTICS_H

#include <asc/std/array>
#include <asc/std/charconv>
#include <asc/std/complex>
#include <asc/std/cstddef>
#include <asc/std/cstring>
#include <asc/std/expected>
#include <asc/std/functional>
#include <asc/std/optional>
#include <asc/std/string_view>
#include <asc/std/tuple>
#include <asc/std/utility>
#include <asc/std/variant>

namespace asc_stl_standard_value_test {

namespace ast = asc::std;

struct offsets {
    int first;
    int second;

    CANN_ASC_STL_API constexpr offsets(int left, int right) : first(left), second(right)
    {}

    CANN_ASC_STL_API int operator()(int delta) const
    {
        return first + second + delta;
    }
};

CANN_ASC_STL_API int evaluate_function_objects(int seed)
{
    for (int offset = 0; offset < 8; ++offset) {
        const int left = seed + offset;
        const int right = offset + 1;
        if (ast::plus<int>{}(left, right) != left + right ||
            ast::minus<>{}(left, static_cast<long>(right)) != left - right ||
            ast::multiplies<int>{}(left, right) != left * right || ast::divides<int>{}(left, right) != left / right ||
            ast::modulus<int>{}(left, right) != left % right || ast::negate<int>{}(left) != -left)
            return 1;
        if (ast::bit_and<int>{}(left, right) != (left & right) || ast::bit_or<int>{}(left, right) != (left | right) ||
            ast::bit_xor<int>{}(left, right) != (left ^ right) || ast::bit_not<int>{}(left) != ~left)
            return 2;
        const bool less = left < right;
        const bool equal = left == right;
        if (ast::equal_to<>{}(left, right) != equal || ast::not_equal_to<int>{}(left, right) == equal ||
            ast::less<int>{}(left, right) != less || ast::less_equal<int>{}(left, right) != (less || equal) ||
            ast::greater<int>{}(left, right) != !(less || equal) || ast::greater_equal<int>{}(left, right) == less ||
            ast::logical_and<>{}(less, equal) || ast::logical_or<>{}(less, equal) != (less || equal) ||
            ast::logical_not<>{}(less) == less)
            return 3;
        if (ast::ranges::equal_to{}(left, right) != equal || ast::ranges::not_equal_to{}(left, right) == equal ||
            ast::ranges::less{}(left, right) != less || ast::ranges::less_equal{}(left, right) != (less || equal) ||
            ast::ranges::greater{}(left, right) != !(less || equal) ||
            ast::ranges::greater_equal{}(left, right) == less)
            return 4;
    }

    offsets callable{seed, 4};
    ast::reference_wrapper<offsets> reference = ast::ref(callable);
    if (&reference.get() != &callable || reference(2) != seed + 6 || ast::cref(callable)(3) != seed + 7 ||
        &ast::identity{}(callable) != &callable || ast::invoke(reference, 5) != seed + 9)
        return 5;

    const int haystack[] = {seed, seed + 1, seed, seed + 2};
    const int needle[] = {seed, seed + 2};
    const int missing[] = {seed + 2, seed + 1};
    const auto found = ast::default_searcher(needle, needle + 2)(haystack, haystack + 4);
    const auto absent = ast::default_searcher(missing, missing + 2)(haystack, haystack + 4);
    const auto empty = ast::default_searcher(needle, needle)(haystack, haystack + 4);
    if (found.first != haystack + 2 || found.second != haystack + 4 || absent.first != haystack + 4 ||
        absent.second != haystack + 4 || empty.first != haystack || empty.second != haystack)
        return 6;
    return 0;
}

CANN_ASC_STL_API int evaluate_value_types(int seed)
{
    const ast::array<int, 2> low{seed, 1};
    const ast::array<int, 2> high{seed, 2};
    const ast::array<int, 0> empty_a{};
    const ast::array<int, 0> empty_b{};
    if (!(empty_a == empty_b) || !(low != high) || !(low < high) || !(low <= low) || !(high > low) || !(high >= high) ||
        ast::get<0>(low) != seed)
        return 1;
    using pair_type = ast::pair<int, long>;  // NOLINT(build/include_what_you_use)
    pair_type left_pair{seed, 3L};
    pair_type another{seed, 4L};
    if (!(left_pair < another) || left_pair == another)
        return 2;
    left_pair.swap(another);
    ast::swap(left_pair, another);
    left_pair = another;
    if (!(left_pair == another) || left_pair.second != 4L)
        return 3;

    using tuple_type = ast::tuple<int, long>;  // NOLINT(build/include_what_you_use)
    tuple_type left_tuple{seed, 3L};
    tuple_type other{seed, 5L};
    if (left_tuple == other || !(left_tuple != other) || !(left_tuple < other) || !(left_tuple <= left_tuple) ||
        !(other > left_tuple) || !(other >= other) || ast::get<1>(left_tuple) != 3L)
        return 4;
    left_tuple = other;
    if (!(left_tuple == other))
        return 5;
    left_tuple.swap(other);
    using suffix_type = ast::tuple<int>;        // NOLINT(build/include_what_you_use)
    using offset_tuple = ast::tuple<int, int>;  // NOLINT(build/include_what_you_use)
    const auto flat = ast::tuple_cat(left_tuple, suffix_type{seed + 1});
    const auto constructed = ast::make_from_tuple<offsets>(offset_tuple{seed, 2});
    if (ast::get<2>(flat) != seed + 1 || constructed.first != seed || constructed.second != 2)
        return 13;
    int count = seed;
    if (ast::exchange(count, seed + 1) != seed || count != seed + 1 || ast::make_pair(seed, 5L).second != 5L ||
        ast::cmp_equal(-1, static_cast<unsigned>(seed)) || !ast::cmp_not_equal(-1, static_cast<unsigned>(seed)) ||
        ast::cmp_greater(seed, 1u) != (seed > 1) || !ast::cmp_greater_equal(seed, static_cast<unsigned>(seed)) ||
        !ast::cmp_less_equal(-1, 0u))
        return 14;

    ast::optional<int> optional;
    if (optional || optional.value_or(seed) != seed)
        return 6;
    optional.emplace(seed);
    int value = seed + 1;
    ast::optional<int&> borrowed(value);
    if (!borrowed || !borrowed.has_value() || &*borrowed != &value || borrowed.operator->() != &value ||
        *optional != seed)
        return 7;
    borrowed = ast::optional<int&>(seed);
    if (borrowed.operator->() != &seed)
        return 15;
    ast::optional<int> copy = optional;
    optional.reset();
    if (optional || !copy.has_value() || *copy != seed || !(optional < copy) || !(optional <= copy) ||
        !(copy > ast::nullopt) || !(copy >= copy) || !(copy == copy) || !(copy != optional) ||
        copy.operator->() == nullptr)
        return 8;

    const ast::unexpected<int> error(seed + 4);
    const ast::unexpect_t unexpect{};
    ast::expected<int, int> result(unexpect, error.error());
    if (result.has_value() || result.error() != seed + 4 || result.value_or(seed) != seed)
        return 9;
    result = seed;
    if (!result || *result != seed)
        return 10;

    ast::variant<int, long> variant(seed);
    ast::variant<int, long> larger(ast::in_place_index<1>, static_cast<long>(seed + 1));
    if (!ast::holds_alternative<int>(variant) || !(variant < larger) || !(variant <= larger) || !(larger > variant) ||
        !(variant != larger) || !(larger >= variant))
        return 11;
    variant = larger;
    if (!(variant == larger) || variant.index() != 1 || variant.valueless_by_exception() ||
        ast::get<1>(variant) != seed + 1 || ast::get_if<0>(&variant) != nullptr)
        return 12;
    return 0;
}

CANN_ASC_STL_API int evaluate_bytes_and_complex(int seed)
{
    for (unsigned index = 0; index != 16; ++index) {
        const unsigned value = (static_cast<unsigned>(seed) + index * 17) & 255u;
        const ast::byte byte = static_cast<ast::byte>(value);
        const ast::byte mask = static_cast<ast::byte>(0x35u);
        const unsigned shift = index % 8;
        auto bits = byte;
        bits ^= mask;
        bits |= mask;
        bits &= byte;
        if (bits != byte || ast::to_integer<unsigned>(byte & mask) != (value & 0x35u) ||
            ast::to_integer<unsigned>(byte | mask) != (value | 0x35u) ||
            ast::to_integer<unsigned>(byte ^ mask) != (value ^ 0x35u) ||
            ast::to_integer<unsigned>(~byte) != ((~value) & 255u) ||
            ast::to_integer<unsigned>(byte << shift) != ((value << shift) & 255u) ||
            ast::to_integer<unsigned>(byte >> shift) != (value >> shift))
            return 1;
        bits <<= shift;
        bits >>= shift;
        if (ast::to_integer<unsigned>(bits) != (((value << shift) & 255u) >> shift))
            return 2;
    }

    using complex = ast::complex<float>;
    const complex value(static_cast<float>(seed), 2.0f);
    const complex scale(2.0f, 0.0f);
    const complex doubled(static_cast<float>(2 * seed), 4.0f);
    if (value * scale != doubled || doubled / scale != value || value + value != doubled || doubled - value != value ||
        ast::norm(value) != static_cast<float>(seed * seed + 4) ||
        ast::conj(value) != complex(static_cast<float>(seed), -2.0f))
        return 3;
    complex copy{};
    copy = value;
    copy += value;
    copy -= value;
    copy *= scale;
    copy /= scale;
    if (!(copy == value) || ast::real(copy) != static_cast<float>(seed) || ast::imag(copy) != 2.0f)
        return 4;
    return 0;
}

CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_INLINE int evaluate_text_boundaries(int seed)
{
    const char overflow[] = {'1', '2', '8', 'x'};
    signed char decoded = static_cast<signed char>(seed % 16);
    const auto invalid_range = ast::from_chars(overflow, overflow + 4, decoded);
    if (invalid_range.ec != ast::errc::result_out_of_range || invalid_range.ptr != overflow + 3 || decoded != seed % 16)
        return 7;
    const char minimum[] = {'-', '1', '2', '8', '!'};
    const auto minimum_result = ast::from_chars(minimum, minimum + 5, decoded);
    char encoded[] = {'?', '?', '?', '?', '#'};
    const auto exact_fit = ast::to_chars(encoded, encoded + 4, decoded);
    if (minimum_result.ec != ast::errc{} || minimum_result.ptr != minimum + 4 || decoded != -128 ||
        exact_fit.ec != ast::errc{} || exact_fit.ptr != encoded + 4 || encoded[4] != '#')
        return 8;
    for (int i = 0; i < 4; ++i) {
        if (encoded[i] != minimum[i])
            return 9;
    }

    unsigned char bytes[] = {static_cast<unsigned char>(seed % 16), 0xff, 0x80, 0, 4, 5, 113};
    if (ast::memmove(bytes + 2, bytes, 4) != bytes + 2 || bytes[0] != seed % 16 || bytes[1] != 0xff ||
        bytes[2] != bytes[0] || bytes[3] != 0xff || bytes[4] != 0x80 || bytes[5] != 0 || bytes[6] != 113)
        return 10;
    if (ast::memmove(bytes, bytes + 3, 3) != bytes || bytes[0] != 0xff || bytes[1] != 0x80 || bytes[2] != 0 ||
        bytes[6] != 113 || ast::memchr(bytes, 0x180, 2) != bytes + 1 || ast::memchr(bytes, 0x80, 1) != nullptr ||
        ast::memcmp(bytes, bytes + 1, 1) <= 0)
        return 11;
    return 0;
}

CANN_ASC_STL_API int evaluate_text(int seed)
{
    char text[] = {'a', 'b', static_cast<char>('c' + seed % 4), 'a', '\0'};
    ast::string_view view(text, 4);
    if (view.empty() || view.front() != 'a' || view.back() != 'a' || view.find('b') != 1 || view.rfind('a') != 3 ||
        view.find('z') != ast::string_view::npos)
        return 1;
    const ast::string_view central(text + 1, 2);
    const char prefix_chars[] = {'a'};
    const ast::string_view prefix(prefix_chars, 1);
    view.remove_prefix(1);
    view.remove_suffix(1);
    if (view.size() != 2 || central != view || view[1] != text[2] || !(prefix < central) || !(central <= view) ||
        !(central >= view) || !(central > prefix))
        return 2;

    char digit_chars[] = {'4', '2', 'x', '\0'};
    char narrow = 0;
    const auto narrow_parse = ast::from_chars(digit_chars, digit_chars + 3, narrow);
    if (narrow_parse.ptr != digit_chars + 2 || narrow_parse.ec != ast::errc{} || narrow != char{42})
        return 5;
    const auto narrow_write = ast::to_chars(digit_chars, digit_chars + 4, narrow);
    if (narrow_write.ptr != digit_chars + 2 || narrow_write.ec != ast::errc{} || digit_chars[0] != '4' ||
        digit_chars[1] != '2' || digit_chars[2] != 'x')
        return 6;

    for (int radix = 2; radix <= 36; radix += 17) {
        const int input = -seed * 9;
        char encoded[24] = {};
        const auto written = ast::to_chars(encoded, encoded + 24, input, radix);
        int decoded = 0;
        const auto parsed = ast::from_chars(encoded, written.ptr, decoded, radix);
        if (written.ec != ast::errc{} || parsed.ec != ast::errc{} || decoded != input || parsed.ptr != written.ptr ||
            encoded[0] != '-')
            return 3;
        int unchanged = seed;
        const auto invalid = ast::from_chars(encoded, encoded, unchanged, radix);
        const auto short_write = ast::to_chars(encoded, encoded + 1, input, radix);
        if (invalid.ec != ast::errc::invalid_argument || unchanged != seed ||
            short_write.ec != ast::errc::value_too_large || short_write.ptr != encoded + 1)
            return 4;
    }
    return evaluate_text_boundaries(seed);
}

}  // namespace asc_stl_standard_value_test

#endif  // ASC_STL_TEST_STANDARD_VALUE_SEMANTICS_H
