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

#ifndef CANN_ASC_STL_ASC_STD___RANDOM_LINEAR_CONGRUENTIAL_ENGINE_H
#define CANN_ASC_STL_ASC_STD___RANDOM_LINEAR_CONGRUENTIAL_ENGINE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__random/is_valid.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/climits>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace detail {

// Ranked-probe seed-sequence detection: a candidate is a seed sequence when it
// is not the engine itself and its result_type converts to the engine's.
template <class _Sseq, class _Engine>
class __is_seed_sequence {
    template <class S,
        class = decltype(static_cast<typename _Engine::result_type>(::asc::std::declval<typename S::result_type>()))>
    static integral_constant<bool, true> probe(int);
    template <class S>
    static integral_constant<bool, false> probe(long);

public:
    static constexpr bool value = decltype(probe<_Sseq>(0))::value && !is_same<_Sseq, _Engine>::value;
};

}  // namespace detail

template <class _UIntType, _UIntType __A, _UIntType __C, _UIntType __M>
class linear_congruential_engine {
    static_assert(
        __asc_random_is_valid_uinttype<_UIntType>, "linear_congruential_engine requires an unsigned integer type");
    // [rand.eng.lcong] preconditions: a == 0 || m == 0 || a < m, and c == 0 || c < m.
    static_assert(__M == 0 || __A < __M, "linear_congruential_engine invalid parameters");
    static_assert(__M == 0 || __C < __M, "linear_congruential_engine invalid parameters");
    static_assert((__C == 0u ? _UIntType(1u) : _UIntType(0u)) <
            (__M == 0u ? static_cast<_UIntType>(~static_cast<_UIntType>(0u)) : static_cast<_UIntType>(__M - 1u)),
        "linear_congruential_engine invalid parameters");

public:
    using result_type = _UIntType;
    static constexpr result_type multiplier = __A;
    static constexpr result_type increment = __C;
    static constexpr result_type modulus = __M;
    static constexpr result_type default_seed = 1u;

    CANN_ASC_STL_API constexpr linear_congruential_engine() noexcept
    {
        seed(default_seed);
    }
    CANN_ASC_STL_API explicit constexpr linear_congruential_engine(result_type seed_value) noexcept
    {
        seed(seed_value);
    }
    template <class _Sseq, enable_if_t<detail::__is_seed_sequence<_Sseq, linear_congruential_engine>::value, int> = 0>
    CANN_ASC_STL_API explicit constexpr linear_congruential_engine(_Sseq& sequence) noexcept
    {
        seed(sequence);
    }

    CANN_ASC_STL_API constexpr void seed(result_type seed_value) noexcept
    {
        seed_from_value(seed_value);
    }
    template <class _Sseq, enable_if_t<detail::__is_seed_sequence<_Sseq, linear_congruential_engine>::value, int> = 0>
    CANN_ASC_STL_API constexpr void seed(_Sseq& sequence) noexcept
    {
        seed_from_value(sequence());
    }

    CANN_ASC_STL_API constexpr result_type operator()() noexcept
    {
        // Keep arithmetic unsigned even when a narrow result_type promotes to int.
        using wide_type = decltype(result_type{} + uint64_t{});
        constexpr wide_type multiplier = __A;
        constexpr wide_type wide_max = ~wide_type{0};
        if constexpr (__M == 0) {
            value_ = static_cast<result_type>(multiplier * value_ + __C);
        } else if constexpr (__A <= (wide_max - __C) / (__M - 1u)) {
            // Every reachable state is at most M - 1, so the multiply-add fits.
            value_ = static_cast<result_type>((multiplier * value_ + __C) % __M);
        } else {
            result_type sum = __C;
            result_type term = value_;
            for (result_type factor = __A; factor != 0; factor >>= 1) {
                if ((factor & 1u) != 0) {
                    sum = add_mod(sum, term);
                }
                term = add_mod(term, term);
            }
            value_ = sum;
        }
        return value_;
    }

    CANN_ASC_STL_API static constexpr result_type min() noexcept
    {
        return __C == 0 ? 1u : 0u;
    }
    CANN_ASC_STL_API static constexpr result_type max() noexcept
    {
        return __M == 0 ? static_cast<result_type>(~static_cast<result_type>(0)) : static_cast<result_type>(__M - 1u);
    }
    CANN_ASC_STL_API constexpr void discard(unsigned long long count) noexcept
    {
        for (unsigned long long index = 0; index < count; ++index) {
            (*this)();
        }
    }

    // CCE cannot friend-match operator templates whose parameters carry
    // non-type template arguments, so the free comparisons read the state
    // through this detail observer instead.
    CANN_ASC_STL_API constexpr result_type __state() const noexcept
    {
        return value_;
    }

private:
    template <class Seed>
    CANN_ASC_STL_API constexpr void seed_from_value(Seed value) noexcept
    {
        if constexpr (__M == 0) {
            value_ = static_cast<result_type>(value);
        } else {
            value_ = static_cast<result_type>(value % __M);
        }
        if (__C == 0 && value_ == 0) {
            value_ = 1;
        }
    }

    CANN_ASC_STL_API static constexpr result_type add_mod(result_type left, result_type right) noexcept
    {
        // Both operands are below M. Subtract the distance to M when the sum would reach it.
        const result_type gap = __M - right;
        return left >= gap ? left - gap : left + right;
    }

    result_type value_{default_seed};
};

template <class _UIntType, _UIntType __A, _UIntType __C, _UIntType __M>
CANN_ASC_STL_API constexpr bool operator==(const linear_congruential_engine<_UIntType, __A, __C, __M>& left,
    const linear_congruential_engine<_UIntType, __A, __C, __M>& right) noexcept
{
    return left.__state() == right.__state();
}

template <class _UIntType, _UIntType __A, _UIntType __C, _UIntType __M>
CANN_ASC_STL_API constexpr bool operator!=(const linear_congruential_engine<_UIntType, __A, __C, __M>& left,
    const linear_congruential_engine<_UIntType, __A, __C, __M>& right) noexcept
{
    return !(left == right);
}

using minstd_rand0 = linear_congruential_engine<uint_fast32_t, 16807, 0, 2147483647>;
using minstd_rand = linear_congruential_engine<uint_fast32_t, 48271, 0, 2147483647>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANDOM_LINEAR_CONGRUENTIAL_ENGINE_H
