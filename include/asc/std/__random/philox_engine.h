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

#ifndef CANN_ASC_STL_ASC_STD___RANDOM_PHILOX_ENGINE_H
#define CANN_ASC_STL_ASC_STD___RANDOM_PHILOX_ENGINE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__algorithm/min.h>
#include <asc/std/__random/is_valid.h>
#include <asc/std/__type_traits/make_nbit_int.h>
#include <asc/std/__utility/pair.h>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class UIntType, size_t WordSize, size_t WordCount, size_t NumRounds, UIntType... Constants>
class philox_engine {
    static_assert(__asc_random_is_valid_uinttype<UIntType>, "philox_engine requires an unsigned result type");
    static_assert(WordSize == 32 || WordSize == 64, "philox_engine supports 32-bit or 64-bit words");
    static_assert(WordCount == 2 || WordCount == 4, "philox_engine word count must be two or four");
    static_assert(sizeof...(Constants) == WordCount, "philox_engine requires one constant per word");
    static_assert(NumRounds > 0, "philox_engine requires at least one round");

    CANN_ASC_STL_API static constexpr auto make_multipliers() noexcept
    {
        constexpr UIntType constants[] = {Constants...};
        if constexpr (WordCount == 2) {
            return array<UIntType, 1>{constants[0]};
        } else {
            return array<UIntType, 2>{constants[0], constants[2]};
        }
    }

    CANN_ASC_STL_API static constexpr auto make_round_consts() noexcept
    {
        constexpr UIntType constants[] = {Constants...};
        if constexpr (WordCount == 2) {
            return array<UIntType, 1>{constants[1]};
        } else {
            return array<UIntType, 2>{constants[1], constants[3]};
        }
    }

public:
    using result_type = UIntType;
    static constexpr size_t word_size = WordSize;
    static constexpr size_t word_count = WordCount;
    static constexpr size_t round_count = NumRounds;
    static constexpr auto multipliers = make_multipliers();
    static constexpr auto round_consts = make_round_consts();
    static constexpr result_type default_seed = 20111115u;

    CANN_ASC_STL_API constexpr philox_engine() noexcept
    {
        seed();
    }

    CANN_ASC_STL_API constexpr explicit philox_engine(result_type value) noexcept
    {
        seed(value);
    }

    CANN_ASC_STL_API static constexpr result_type min() noexcept
    {
        return 0;
    }

    CANN_ASC_STL_API static constexpr result_type max() noexcept
    {
        return (result_type{1} << (word_size - 1)) | ((result_type{1} << (word_size - 1)) - 1);
    }

    CANN_ASC_STL_API constexpr void seed(result_type value = default_seed) noexcept
    {
        counter_ = {};
        key_ = {};
        output_ = {};
        key_[0] = value & max();
        position_ = word_count - 1;
    }

    CANN_ASC_STL_API constexpr void set_counter(const array<result_type, word_count>& counter) noexcept
    {
        for (size_t index = 0; index < word_count; ++index) {
            counter_[index] = counter[word_count - 1 - index] & max();
        }
        position_ = word_count - 1;
    }

    CANN_ASC_STL_API constexpr result_type operator()() noexcept
    {
        ++position_;
        if (position_ == word_count) {
            generate();
            increment_counter();
            position_ = 0;
        }
        return output_[position_];
    }

    CANN_ASC_STL_API constexpr void discard(unsigned long long count) noexcept
    {
        const unsigned long long advance =
            ::asc::std::min(count, static_cast<unsigned long long>(word_count - 1 - position_));  // NOLINT
        position_ += static_cast<size_t>(advance);
        count -= advance;
        unsigned long long increment = count / word_count;
        const unsigned long long remainder = count % word_count;
        result_type carry = 0;
        for (size_t index = 0; index < word_count; ++index) {
            if (increment == 0 && carry == 0) {
                break;
            }
            const result_type previous = counter_[index];
            counter_[index] = static_cast<result_type>((previous + (increment & max()) + carry) & max());
            carry = counter_[index] < previous ? 1 : 0;
            if constexpr (word_size < 64) {
                increment >>= word_size;
            } else {
                increment = 0;
            }
        }
        if (remainder != 0) {
            generate();
            increment_counter();
            position_ = static_cast<size_t>(remainder - 1);
        }
    }

    CANN_ASC_STL_API friend constexpr bool operator==(const philox_engine& left, const philox_engine& right) noexcept
    {
        if (left.counter_ != right.counter_ || left.key_ != right.key_ || left.position_ != right.position_) {
            return false;
        }
        return left.position_ == word_count - 1 || left.output_ == right.output_;
    }

    CANN_ASC_STL_API friend constexpr bool operator!=(const philox_engine& left, const philox_engine& right) noexcept
    {
        return !(left == right);
    }

private:
    CANN_ASC_STL_API static constexpr pair<result_type, result_type> multiply(  // NOLINT
        result_type left, result_type right) noexcept
    {
        if constexpr (word_size == 32) {
            const unsigned long long wide =
                static_cast<unsigned long long>(left) * static_cast<unsigned long long>(right);
            return {static_cast<result_type>((wide >> 32) & max()), static_cast<result_type>(wide & max())};
        } else {
            constexpr result_type half = word_size / 2;
            constexpr result_type mask = (result_type{1} << half) - 1;
            const result_type low = left * right;
            const result_type left_high = left >> half;
            const result_type left_low = left & mask;
            const result_type right_high = right >> half;
            const result_type right_low = right & mask;
            const result_type cross0 = left_high * right_low;
            const result_type cross1 = left_low * right_high;
            const result_type cross_low = (cross0 & mask) + (cross1 & mask);
            result_type high = left_high * right_high + (cross0 >> half) + (cross1 >> half);
            high += cross_low >> half;
            high += (low >> half) < (cross_low & mask) ? 1 : 0;
            return {high, low};
        }
    }

    CANN_ASC_STL_API constexpr void increment_counter() noexcept
    {
        for (size_t index = 0; index < word_count; ++index) {
            counter_[index] = static_cast<result_type>((counter_[index] + 1) & max());
            if (counter_[index] != 0) {
                break;
            }
        }
    }

    CANN_ASC_STL_API constexpr void generate() noexcept
    {
        array<result_type, word_count> state = counter_;
        array<result_type, word_count / 2> key = key_;
        for (size_t round = 0; round < round_count; ++round) {
            if constexpr (word_count == 2) {
                const auto product = multiply(state[0], multipliers[0]);
                state[0] = product.first ^ key[0] ^ state[1];
                state[1] = product.second;
                key[0] = static_cast<result_type>((key[0] + round_consts[0]) & max());
            } else {
                const array<result_type, 4> values{state[2], state[1], state[0], state[3]};
                const auto first = multiply(values[0], multipliers[0]);
                const auto second = multiply(values[2], multipliers[1]);
                state[0] = first.first ^ key[0] ^ values[1];
                state[1] = first.second;
                state[2] = second.first ^ key[1] ^ values[3];
                state[3] = second.second;
                key[0] = static_cast<result_type>((key[0] + round_consts[0]) & max());
                key[1] = static_cast<result_type>((key[1] + round_consts[1]) & max());
            }
        }
        output_ = state;
    }

    array<result_type, word_count> counter_{};
    array<result_type, word_count / 2> key_{};
    array<result_type, word_count> output_{};
    size_t position_ = 0;
};

using philox4x32 = philox_engine<uint_fast32_t, 32, 4, 10, 3449720151U, 2654435769U, 3528531795U, 3144134277U>;
using philox4x64 = philox_engine<uint_fast64_t, 64, 4, 10, 14581110107779764567UL, 11400714819323198485UL,
    15197193596820024467UL, 13503953896175478587UL>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANDOM_PHILOX_ENGINE_H
