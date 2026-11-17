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

#include <cfenv>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

#include "../../../support/numeric_types_semantics.h"
#include "reference.h"

namespace {
using R = asc::rounding_mode;
using S = asc::saturation_mode;
using numeric_types_reference::float_bits;
using numeric_types_reference::from_float_bits;

unsigned long long comparisons = 0;

template <class T, R Round, S Sat>
bool conversions(const numeric_types_reference::format& reference, const std::vector<std::uint32_t>& inputs)
{
    for (auto bits : inputs) {
        const auto actual = asc::to_bits(asc::numeric_convert<T, Round, Sat>(from_float_bits(bits)));
        const auto expected = reference.encode(bits, static_cast<unsigned>(Round), static_cast<unsigned>(Sat));
        ++comparisons;
        if (actual != expected) {
            std::cerr << "encode mismatch input=" << std::hex << bits << " actual=" << actual
                      << " expected=" << expected << " format=" << sizeof(T) << " round=" << unsigned(Round)
                      << " saturation=" << unsigned(Sat) << '\n';
            return false;
        }
    }
    for (unsigned code = 0; code < (1U << (8 * sizeof(T))); ++code) {
        using Storage = typename asc::numeric_format_traits<T>::storage_type;
        const auto actual =
            float_bits(asc::numeric_convert<float, Round, Sat>(asc::from_bits<T>(static_cast<Storage>(code))));
        const auto expected = reference.decode(code, static_cast<unsigned>(Sat));
        ++comparisons;
        if (actual != expected) {
            std::cerr << "decode mismatch code=" << std::hex << code << " actual=" << actual << " expected=" << expected
                      << '\n';
            return false;
        }
    }
    return true;
}

template <class T>
bool options(const numeric_types_reference::format& reference)
{
    const auto source = numeric_types_reference::inputs(reference);
    return conversions<T, R::nearest_even, S::none>(reference, source) &&
        conversions<T, R::nearest_even, S::finite>(reference, source) &&
        conversions<T, R::toward_zero, S::none>(reference, source) &&
        conversions<T, R::toward_zero, S::finite>(reference, source) &&
        conversions<T, R::toward_positive, S::none>(reference, source) &&
        conversions<T, R::toward_positive, S::finite>(reference, source) &&
        conversions<T, R::toward_negative, S::none>(reference, source) &&
        conversions<T, R::toward_negative, S::finite>(reference, source);
}

void vectors(const char* path)
{
    const auto records = numeric_types_reference::device_vectors();
    std::ofstream stream(path, std::ios::binary);
    stream.write(reinterpret_cast<const char*>(records.data()), records.size() * sizeof(records[0]));
    if (!stream) {
        throw std::runtime_error("writing independent numeric conversion vectors failed");
    }
}

bool floating_environment(const std::vector<numeric_types_reference::format>& formats)
{
    const auto original = std::fegetround();
    bool passed = true;
    for (const auto mode : {FE_TONEAREST, FE_TOWARDZERO, FE_UPWARD, FE_DOWNWARD}) {
        passed = std::fesetround(mode) == 0 && passed;
        for (const auto raw : {0x3f801000U, 0x33000001U, 0x477ff000U, 0xc3e80001U}) {
            const auto value = asc::numeric_convert<asc::float16>(from_float_bits(raw));
            passed = asc::to_bits(value) == formats[0].encode(raw, 0, 0) && passed;
        }
        passed = std::fegetround() == mode && passed;
    }
    return std::fesetround(original) == 0 && passed;
}
}  // namespace

int main(int argc, char** argv)
{
    const auto formats = numeric_types_reference::formats();
    bool passed = numeric_types_test::representations() == 0 && numeric_types_test::integers<R::nearest_even>() == 0 &&
        numeric_types_test::integers<R::toward_zero>() == 0 &&
        numeric_types_test::integers<R::toward_positive>() == 0 &&
        numeric_types_test::integers<R::toward_negative>() == 0;
    passed = options<asc::float16>(formats[0]) && options<asc::bfloat16>(formats[1]) &&
        options<asc::float8_e4m3fn>(formats[2]) && options<asc::float8_e5m2>(formats[3]) && passed;
    passed = floating_environment(formats) && passed;
    if (passed && argc == 2) {
        vectors(argv[1]);
    }
    std::cout << "numeric_types comparisons=" << comparisons << " passed=" << passed << '\n';
    return passed ? 0 : 1;
}
