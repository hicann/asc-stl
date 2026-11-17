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

#ifndef ASC_STL_TEST_NUMERIC_TYPES_REFERENCE_H
#define ASC_STL_TEST_NUMERIC_TYPES_REFERENCE_H

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <vector>

namespace numeric_types_reference {

inline std::uint32_t float_bits(float value) noexcept
{
    return __builtin_bit_cast(std::uint32_t, value);
}
inline float from_float_bits(std::uint32_t bits) noexcept
{
    return __builtin_bit_cast(float, bits);
}

// Independent reference: enumerate representable numbers with ldexp, then
// search neighboring values and compare distances. No product bit-rounding
// routine, layout descriptor or native SDK conversion is used.
struct format {
    unsigned mantissa;
    unsigned exponent;
    int bias;
    unsigned maximum;
    unsigned nan;
    bool has_infinity;
    std::vector<double> values;

    format(unsigned m, unsigned e, int b, unsigned max_code, unsigned nan_code, bool infinity)
        : mantissa(m), exponent(e), bias(b), maximum(max_code), nan(nan_code), has_infinity(infinity)
    {
        for (unsigned code = 0; code <= maximum; ++code) {
            const unsigned exp = code / (1U << mantissa);
            const double fraction = static_cast<double>(code % (1U << mantissa)) / (1U << mantissa);
            values.push_back(
                std::ldexp(exp == 0 ? fraction : 1.0 + fraction, (exp == 0 ? 1 : static_cast<int>(exp)) - bias));
        }
        values.push_back(values.back() + (values.back() - values[values.size() - 2]));
    }

    unsigned sign() const noexcept
    {
        return 1U << (mantissa + exponent);
    }
    unsigned infinity() const noexcept
    {
        return ((1U << exponent) - 1) << mantissa;
    }

    unsigned overflow(bool negative, unsigned round, unsigned saturation) const noexcept
    {
        const unsigned signed_part = negative ? sign() : 0;
        if (saturation != 0) {
            return signed_part + maximum;
        }
        if (!has_infinity) {
            return nan;
        }
        const bool to_inf = round == 0 || (round == 2 && !negative) || (round == 3 && negative);
        return signed_part + (to_inf ? infinity() : maximum);
    }

    bool choose_lower(double value, unsigned upper, bool negative, unsigned round) const noexcept
    {
        if (round == 0) {
            const double midpoint = (values[upper - 1] + values[upper]) / 2;
            return value < midpoint || (value == midpoint && (upper - 1) % 2 == 0);
        }
        const bool upward = (round == 2 && !negative) || (round == 3 && negative);
        return !upward;
    }

    unsigned encode(std::uint32_t raw, unsigned round, unsigned saturation) const
    {
        const bool negative = (raw & 0x80000000U) != 0;
        const unsigned signed_part = negative ? sign() : 0;
        const unsigned magnitude = raw & 0x7fffffffU;
        if (magnitude > 0x7f800000U) {
            return nan;
        }
        if (magnitude == 0x7f800000U) {
            return saturation == 0 && has_infinity ? signed_part + infinity() : overflow(negative, round, saturation);
        }
        const double value = from_float_bits(magnitude);
        const auto upper = std::lower_bound(values.begin(), values.end(), value);
        if (upper == values.end()) {
            return overflow(negative, round, saturation);
        }
        unsigned index = static_cast<unsigned>(upper - values.begin());
        if (*upper != value && index > 0) {
            if (choose_lower(value, index, negative, round)) {
                --index;
            }
        }
        return index > maximum ? overflow(negative, round, saturation) : signed_part + index;
    }

    std::uint32_t decode(unsigned code, unsigned saturation) const
    {
        const auto signed_part = code >= sign() ? 0x80000000U : 0;
        const unsigned magnitude = code % sign();
        if (magnitude <= maximum) {
            return signed_part | float_bits(static_cast<float>(values[magnitude]));
        }
        if (has_infinity && magnitude == infinity()) {
            return signed_part | (saturation == 0 ? 0x7f800000U : 0x7f7fffffU);
        }
        return 0x7fc00000U;
    }
};

inline std::vector<format> formats()
{
    return {format(10, 5, 15, 0x7bff, 0x7e00, true), format(7, 8, 127, 0x7f7f, 0x7fc0, true),
        format(3, 4, 7, 0x7e, 0x7f, false), format(2, 5, 15, 0x7b, 0x7e, true)};
}

inline std::vector<std::uint32_t> inputs(const format& f, unsigned random_count = 20000)
{
    std::vector<std::uint32_t> result{
        0, 1, 0x007fffff, 0x00800000, 0x7f7fffff, 0x7f800000, 0x7f800001, 0x7fc00000, 0x7fffffff};
    for (unsigned i = 0; i <= f.maximum; ++i) {
        result.push_back(float_bits(static_cast<float>(f.values[i])));
        const double midpoint = (f.values[i] + f.values[i + 1]) / 2;
        if (midpoint <= std::numeric_limits<float>::max()) {
            const auto raw = float_bits(static_cast<float>(midpoint));
            result.push_back(raw);
            if (raw != 0) {
                result.push_back(raw - 1);
            }
            result.push_back(raw + 1);
        }
    }
    std::uint32_t random = 0xb17a1289U;
    for (unsigned i = 0; i < random_count; ++i) {
        random = random * 1664525U + 1013904223U;
        result.push_back(random & 0x7fffffffU);
    }
    const auto positive_count = result.size();
    for (std::size_t i = 0; i < positive_count; ++i) {
        result.push_back(result[i] | 0x80000000U);
    }
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;
}

inline std::vector<std::uint32_t> simulation_inputs(const format& f)
{
    std::vector<std::uint32_t> result{
        0, 1, 0x007fffff, 0x00800000, 0x7f7fffff, 0x7f800000, 0x7f800001, 0x7fc00000, 0x7fffffff};
    const unsigned normal = 1U << f.mantissa;
    const unsigned one = static_cast<unsigned>(f.bias) * normal;
    for (auto code :
        {0U, 1U, 2U, 3U, normal - 1, normal, normal + 1, one - 1, one, one + 1, f.maximum - 1, f.maximum}) {
        result.push_back(float_bits(static_cast<float>(f.values[code])));
        const double midpoint = (f.values[code] + f.values[code + 1]) / 2;
        if (midpoint <= std::numeric_limits<float>::max()) {
            const auto bits = float_bits(static_cast<float>(midpoint));
            result.push_back(bits);
            if (bits != 0)
                result.push_back(bits - 1);
            result.push_back(bits + 1);
        }
    }
    const auto count = result.size();
    for (std::size_t i = 0; i < count; ++i)
        result.push_back(result[i] | 0x80000000U);
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;
}

inline bool simulation_decode_code(const format& f, unsigned code)
{
    const unsigned value = code % f.sign();
    const unsigned normal = 1U << f.mantissa;
    const unsigned one = static_cast<unsigned>(f.bias) * normal;
    return value <= 3 || value == normal - 1 || value == normal || value == normal + 1 || value == one - 1 ||
        value == one || value == one + 1 || value == f.maximum - 1 || value == f.maximum || value == f.infinity() ||
        value == f.infinity() + 1 || value == f.nan || value == f.sign() - 1;
}

inline std::vector<std::uint32_t> device_vectors(bool simulation = false)
{
    std::vector<std::uint32_t> result;
    const auto reference = formats();
    for (unsigned id = 0; id < reference.size(); ++id) {
        const auto& f = reference[id];
        const auto source = simulation ? simulation_inputs(f) : inputs(f, 0);
        for (unsigned option = 0; option < 8; ++option) {
            for (std::size_t i = 0; i < source.size(); ++i) {
                if (!simulation && id < 2 && i % 127 != 0 && (source[i] & 0x7fffffffU) < 0x7f7fffffU && i > 5) {
                    continue;
                }
                result.insert(result.end(), {id, 0, option, source[i], f.encode(source[i], option / 2, option % 2)});
            }
            for (unsigned code = 0; code < (1U << (f.mantissa + f.exponent + 1)); ++code) {
                if (id < 2 &&
                    (simulation ? !simulation_decode_code(f, code) :
                                  code % 127 != 0 && (code % f.sign()) < f.maximum)) {
                    continue;
                }
                result.insert(result.end(), {id, 1, option, code, f.decode(code, option % 2)});
            }
        }
    }
    return result;
}

}  // namespace numeric_types_reference

#endif  // ASC_STL_TEST_NUMERIC_TYPES_REFERENCE_H
