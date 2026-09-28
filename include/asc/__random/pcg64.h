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

CANN_ASC_STL_API constexpr random_uint128 shift_right(random_uint128 value, unsigned int count) noexcept
{
    if (count == 0) {
        return value;
    }
    if (count >= 64) {
        return {0, value.high >> (count - 64)};
    }
    return {value.high >> count, (value.low >> count) | (value.high << (64 - count))};
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

template <class Index>
class feistel_bijection {
public:
    using index_type = Index;

    CANN_ASC_STL_API constexpr feistel_bijection() noexcept : mask_(0), multiplier_(1), offset_(0)
    {}

    template <class RNG>
    CANN_ASC_STL_API constexpr feistel_bijection(Index size, RNG&& generator) noexcept
        : mask_(domain_mask(size)),
          multiplier_(static_cast<Index>(generator()) | Index{1}),
          offset_(static_cast<Index>(generator()) & mask_)
    {}

    CANN_ASC_STL_API constexpr Index operator()(Index value) const noexcept
    {
        return static_cast<Index>((value * multiplier_ + offset_) & mask_);
    }

private:
    CANN_ASC_STL_API static constexpr Index domain_mask(Index size) noexcept
    {
        Index mask = 1;
        while (mask < size) {
            mask = static_cast<Index>((mask << 1) | 1);
        }
        return mask;
    }

    Index mask_;
    Index multiplier_;
    Index offset_;
};

// Retained private foundation name used by the already delivered iterator
// semantic payload. It is not exported by <asc/random>; the public PCG64 below
// uses the exact 128-bit-state contract.
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
