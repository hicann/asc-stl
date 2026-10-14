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

#ifndef CANN_ASC_STL_ASC___RANDOM_PCG64_H
#define CANN_ASC_STL_ASC___RANDOM_PCG64_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

namespace asc::detail {

using random_uint64 = __UINT64_TYPE__;

struct random_uint128 {
    random_uint64 high;
    random_uint64 low;

    CANN_ASC_STL_API constexpr random_uint128(random_uint64 value = 0) noexcept : high(0), low(value)
    {}
    CANN_ASC_STL_API constexpr random_uint128(random_uint64 high_value, random_uint64 low_value) noexcept
        : high(high_value), low(low_value)
    {}
};

CANN_ASC_STL_API constexpr random_uint128 add(random_uint128 left, random_uint128 right) noexcept
{
    const random_uint64 low = left.low + right.low;
    return {left.high + right.high + (low < left.low ? 1U : 0U), low};
}

CANN_ASC_STL_API constexpr random_uint64 multiply_high(random_uint64 left, random_uint64 right) noexcept
{
    const random_uint64 mask = 0xffffffffULL;
    const random_uint64 left_low = left & mask;
    const random_uint64 left_high = left >> 32U;
    const random_uint64 right_low = right & mask;
    const random_uint64 right_high = right >> 32U;
    const random_uint64 low_product = left_low * right_low;
    const random_uint64 middle = left_high * right_low + (low_product >> 32U);
    return left_high * right_high + (middle >> 32U) + (((middle & mask) + left_low * right_high) >> 32U);
}

CANN_ASC_STL_API constexpr random_uint128 multiply(random_uint128 left, random_uint128 right) noexcept
{
    return {multiply_high(left.low, right.low) + left.high * right.low + left.low * right.high, left.low * right.low};
}

CANN_ASC_STL_API constexpr bool equal(random_uint128 left, random_uint128 right) noexcept
{
    return left.high == right.high && left.low == right.low;
}

CANN_ASC_STL_API constexpr random_uint64 rotate_right(random_uint64 value, unsigned int count) noexcept
{
    const unsigned int normalized = count & 63U;
    return normalized == 0 ? value : (value >> normalized) | (value << (64U - normalized));
}

// 24-round Feistel network over the power-of-two domain covering the
// requested size: a genuine pseudo-random permutation, unlike the affine
// multiplier it replaces (which was linearly predictable from two probes).
// Each round splits the index into left/right halves, mixes the left half
// through a product with the 64-bit constant below (its high half feeds a
// keyed xor, its low half feeds the right-half rotation), and swaps; the
// network is invertible for any round keys because the odd constant makes
// the low bits of the product a bijection of the left half. Round keys are
// drawn from the caller supplied generator at construction time; evaluation
// is pure arithmetic, so it stays usable in constexpr contexts and device
// kernels. Expected generator contract: a uniform random bit source whose
// outputs are convertible to 64 bits (high 32 bits are used per key).
template <class Index>
class feistel_bijection {
public:
    using index_type = Index;

    CANN_ASC_STL_API constexpr feistel_bijection() noexcept
        : left_bits_(0), right_bits_(0), left_mask_(0), right_mask_(0), keys_()
    {}

    template <class RNG>
    CANN_ASC_STL_API constexpr feistel_bijection(Index size, RNG&& generator) noexcept
        : left_bits_(0), right_bits_(0), left_mask_(0), right_mask_(0), keys_()
    {
        // Bits needed for size - 1, clamped so that even size 0/1 keeps the
        // minimum 4+4 bit split usable by the network.
        const random_uint64 highest = static_cast<random_uint64>(size) > 0 ? static_cast<random_uint64>(size) - 1 : 0;
        random_uint64 total_bits = 8;
        while (total_bits != 64 && (random_uint64{1} << total_bits) <= highest) {
            ++total_bits;
        }
        left_bits_ = static_cast<unsigned int>(total_bits / 2);
        right_bits_ = static_cast<unsigned int>(total_bits - total_bits / 2);
        left_mask_ = (random_uint64{1} << left_bits_) - 1;
        right_mask_ = (random_uint64{1} << right_bits_) - 1;
        for (unsigned int round = 0; round != round_count; ++round) {
            keys_[round] = static_cast<unsigned int>(static_cast<random_uint64>(generator()) >> 32U);
        }
    }

    CANN_ASC_STL_API constexpr Index operator()(Index value) const noexcept
    {
        const random_uint64 input = static_cast<random_uint64>(value);
        unsigned int left = static_cast<unsigned int>(input >> right_bits_);
        unsigned int right = static_cast<unsigned int>(input & right_mask_);
        for (unsigned int round = 0; round != round_count; ++round) {
            const random_uint64 product = round_constant * left;
            const unsigned int keyed = static_cast<unsigned int>(product >> 32U) ^ keys_[round];
            const unsigned int carried = static_cast<unsigned int>(product);
            const unsigned int next_left = keyed ^ right;
            const unsigned int next_right =
                static_cast<unsigned int>(((static_cast<random_uint64>(carried) << (right_bits_ - left_bits_)) |
                                              (static_cast<random_uint64>(right) >> left_bits_)) &
                    right_mask_);
            left = next_left & static_cast<unsigned int>(left_mask_);
            right = next_right;
        }
        return static_cast<Index>((static_cast<random_uint64>(left) << right_bits_) | right);
    }

private:
    static constexpr unsigned int round_count = 24;
    static constexpr random_uint64 round_constant = 0xD2B74407B1CE6E93ULL;

    unsigned int left_bits_{};
    unsigned int right_bits_{};
    random_uint64 left_mask_{};
    random_uint64 right_mask_{};
    unsigned int keys_[round_count]{};
};

// Legacy single-word linear congruential engine retained only because the
// delivered semantics payload (test/support/b024_semantics.h) still refers to
// it by its detail name. It is NOT a PCG64: no 128-bit multiplier/increment
// state and no output permutation, so its raw LCG stream is linearly related
// across seeds. It has no users inside the library itself - <asc/random>
// builds the public engine on the 128-bit state helpers above. Do not add
// new uses; retire it together with the semantics payload that pins it.
class pcg64_engine {
public:
    using result_type = random_uint64;
    static constexpr result_type default_seed = 0x853c49e6748fea9bULL;
    CANN_ASC_STL_API constexpr pcg64_engine() noexcept : state_(default_seed)
    {}
    CANN_ASC_STL_API constexpr result_type operator()() noexcept
    {
        state_ = state_ * 6364136223846793005ULL + 1442695040888963407ULL;
        return state_;
    }
    CANN_ASC_STL_API constexpr void discard(unsigned long long count) noexcept
    {
        for (unsigned long long discarded = 0; discarded < count; ++discarded) {
            (void)(*this)();
        }
    }
    CANN_ASC_STL_API constexpr bool equal(const pcg64_engine& other) const noexcept
    {
        return state_ == other.state_;
    }

private:
    result_type state_;
};

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___RANDOM_PCG64_H
