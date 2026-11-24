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

#include <asc/__detail/attributes.h>
#include <asc/std/cstdint>

namespace asc::detail {

using random_uint64 = ::asc::std::uint64_t;

struct random_uint128 {
    random_uint64 high;
    random_uint64 low;

    CANN_ASC_STL_API constexpr random_uint128(random_uint64 value = 0) noexcept : high(0), low(value)
    {}
    CANN_ASC_STL_API constexpr random_uint128(random_uint64 upper, random_uint64 lower) noexcept
        : high(upper), low(lower)
    {}
};

// Compute the carry from 32-bit limbs, avoiding a full-width comparison on
// AICore scalar backends. All arithmetic is unsigned and modulo 2^128.
CANN_ASC_STL_API constexpr random_uint128 add(random_uint128 left, random_uint128 right) noexcept
{
    constexpr random_uint64 mask = 0xffffffffULL;
    const random_uint64 lower = (left.low & mask) + (right.low & mask);
    const random_uint64 upper = (left.low >> 32U) + (right.low >> 32U) + (lower >> 32U);
    return {left.high + right.high + (upper >> 32U), (upper << 32U) | (lower & mask)};
}

CANN_ASC_STL_API constexpr random_uint64 multiply_high(random_uint64 left, random_uint64 right) noexcept
{
    constexpr random_uint64 mask = 0xffffffffULL;
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
    // The high-by-high term is a multiple of 2^128 and is discarded.
    return {multiply_high(left.low, right.low) + left.high * right.low + left.low * right.high, left.low * right.low};
}

CANN_ASC_STL_API constexpr random_uint64 rotate_right(random_uint64 value, unsigned count) noexcept
{
    const unsigned rotation = count & 63U;
    return (value >> rotation) | (value << ((64U - rotation) & 63U));
}

}  // namespace asc::detail

namespace asc {

// PCG XSL-RR 128/64 oneseq, matching the author's pcg64_oneseq variant.
// The two-word path is also the constexpr path; no native 128-bit type is needed.
class pcg64 {
public:
    using result_type = ::asc::std::uint64_t;
    static constexpr result_type default_seed = 0xcafef00dd15ea5e5ULL;

    CANN_ASC_STL_API constexpr pcg64() noexcept : pcg64(default_seed)
    {}
    CANN_ASC_STL_API constexpr explicit pcg64(result_type value) noexcept
    {
        seed(value);
    }
    CANN_ASC_STL_API constexpr pcg64(const pcg64&) noexcept = default;
    CANN_ASC_STL_API constexpr pcg64& operator=(const pcg64&) noexcept = default;

    CANN_ASC_STL_API static constexpr result_type min() noexcept
    {
        return 0;
    }
    CANN_ASC_STL_API static constexpr result_type max() noexcept
    {
        return ~result_type{0};
    }

    CANN_ASC_STL_API constexpr void seed(result_type value = default_seed) noexcept
    {
        state_ = detail::add(
            detail::multiply(detail::add(detail::random_uint128(value), increment()), multiplier()), increment());
    }

    CANN_ASC_STL_API constexpr result_type operator()() noexcept
    {
        state_ = detail::add(detail::multiply(state_, multiplier()), increment());
        return detail::rotate_right(state_.low ^ state_.high, static_cast<unsigned>(state_.high >> 58U));
    }

    CANN_ASC_STL_API constexpr void discard(unsigned long long count) noexcept
    {
        detail::random_uint128 accumulated_multiplier(1);
        detail::random_uint128 accumulated_increment(0);
        detail::random_uint128 current_multiplier = multiplier();
        detail::random_uint128 current_increment = increment();
        while (count != 0) {
            if ((count & 1U) != 0) {
                accumulated_multiplier = detail::multiply(accumulated_multiplier, current_multiplier);
                accumulated_increment =
                    detail::add(detail::multiply(accumulated_increment, current_multiplier), current_increment);
            }
            current_increment =
                detail::multiply(detail::add(current_multiplier, detail::random_uint128(1)), current_increment);
            current_multiplier = detail::multiply(current_multiplier, current_multiplier);
            count >>= 1U;
        }
        state_ = detail::add(detail::multiply(state_, accumulated_multiplier), accumulated_increment);
    }

    CANN_ASC_STL_API friend constexpr bool operator==(const pcg64& left, const pcg64& right) noexcept;

private:
    CANN_ASC_STL_API static constexpr detail::random_uint128 multiplier() noexcept
    {
        return {2549297995355413924ULL, 4865540595714422341ULL};
    }
    CANN_ASC_STL_API static constexpr detail::random_uint128 increment() noexcept
    {
        return {6364136223846793005ULL, 1442695040888963407ULL};
    }

    detail::random_uint128 state_{};
};

CANN_ASC_STL_API constexpr bool operator==(const pcg64& left, const pcg64& right) noexcept
{
    return left.state_.high == right.state_.high && left.state_.low == right.state_.low;
}

CANN_ASC_STL_API constexpr bool operator!=(const pcg64& left, const pcg64& right) noexcept
{
    return !(left == right);
}

}  // namespace asc

#endif  // CANN_ASC_STL_ASC___RANDOM_PCG64_H
