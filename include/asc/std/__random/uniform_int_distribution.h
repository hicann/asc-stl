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

#ifndef CANN_ASC_STL_ASC_STD___RANDOM_UNIFORM_INT_DISTRIBUTION_H
#define CANN_ASC_STL_ASC_STD___RANDOM_UNIFORM_INT_DISTRIBUTION_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__bit/countl.h>
#include <asc/std/__bit/integral.h>
#include <asc/std/__limits/numeric_limits.h>
#include <asc/std/__random/is_valid.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/cstddef>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

//! @brief Independent-bits engine: regroups any URNG's output into an
//! unbiased bit stream of the requested width.
//!
//! All arithmetic is unsigned, giving one unified host and AI-core path.
//! The rejection limits are guarded at the working-type width (not the
//! result-type width), so engines with non-power-of-two ranges produce the
//! same seeded output sequence as libc++.
template <class Engine, class UIntType>
class __independent_bits_engine {
public:
    // types
    using result_type = UIntType;

private:
    using engine_result_type = typename Engine::result_type;
    using working_result_type =
        conditional_t<(sizeof(engine_result_type) <= sizeof(UIntType)), UIntType, engine_result_type>;

    Engine& engine_;
    size_t width_;
    size_t small_width_{};
    size_t chunks_{};
    size_t small_chunks_{};
    working_result_type small_limit_{};
    working_result_type large_limit_{};
    engine_result_type small_mask_{};
    engine_result_type large_mask_{};

    static constexpr working_result_type range = Engine::max() - Engine::min() + working_result_type(1);
    static constexpr size_t log2_range = static_cast<size_t>(::asc::std::__bit_log2(range));
    static constexpr size_t working_digits = static_cast<size_t>(numeric_limits<working_result_type>::digits);
    static constexpr size_t engine_digits = static_cast<size_t>(numeric_limits<engine_result_type>::digits);

public:
    CANN_ASC_STL_API constexpr __independent_bits_engine(Engine& engine, size_t width) noexcept
        : engine_(engine), width_(width)
    {
        chunks_ = width_ / log2_range + (width_ % log2_range != 0);
        small_width_ = width_ / chunks_;
        if (range == 0) {
            small_limit_ = range;
        } else if (small_width_ < working_digits) {
            small_limit_ = (range >> small_width_) << small_width_;
        } else {
            small_limit_ = 0;
        }
        if (range - small_limit_ > small_limit_ / chunks_) {
            ++chunks_;
            small_width_ = width_ / chunks_;
            if (small_width_ < working_digits) {
                small_limit_ = (range >> small_width_) << small_width_;
            } else {
                small_limit_ = 0;
            }
        }
        small_chunks_ = chunks_ - width_ % chunks_;
        if (small_width_ < working_digits - 1) {
            large_limit_ = (range >> (small_width_ + 1)) << (small_width_ + 1);
        } else {
            large_limit_ = 0;
        }
        small_mask_ = small_width_ > 0 ?
            static_cast<engine_result_type>(~engine_result_type(0)) >> (engine_digits - small_width_) :
            engine_result_type(0);
        large_mask_ = small_width_ < engine_digits - 1 ?
            static_cast<engine_result_type>(~engine_result_type(0)) >> (engine_digits - (small_width_ + 1)) :
            static_cast<engine_result_type>(~engine_result_type(0));
    }

    // generating functions
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr result_type operator()() noexcept
    {
        if (range == 0) {
            return static_cast<result_type>(engine_() & small_mask_);
        }
        constexpr size_t result_width = static_cast<size_t>(numeric_limits<result_type>::digits);
        result_type result = 0;
        for (size_t index = 0; index < small_chunks_; ++index) {
            engine_result_type sample = engine_() - Engine::min();
            while (sample >= small_limit_) {
                sample = engine_() - Engine::min();
            }
            if (small_width_ < result_width) {
                result <<= small_width_;
            } else {
                result = 0;
            }
            result += static_cast<result_type>(sample & small_mask_);
        }
        for (size_t index = small_chunks_; index < chunks_; ++index) {
            engine_result_type sample = engine_() - Engine::min();
            while (sample >= large_limit_) {
                sample = engine_() - Engine::min();
            }
            if (small_width_ < result_width - 1) {
                result <<= small_width_ + 1;
            } else {
                result = 0;
            }
            result += static_cast<result_type>(sample & large_mask_);
        }
        return result;
    }
};

template <class IntType = int>
class uniform_int_distribution {
    static_assert(
        __asc_random_is_valid_inttype<IntType>, "uniform_int_distribution requires a supported integer result type");

public:
    using result_type = IntType;
    class param_type {
    public:
        using distribution_type = uniform_int_distribution;
        CANN_ASC_STL_API explicit constexpr param_type(
            result_type lower = 0, result_type upper = numeric_limits<result_type>::max()) noexcept
            : lower_(lower), upper_(upper)
        {}
        CANN_ASC_STL_API constexpr result_type a() const noexcept
        {
            return lower_;
        }
        CANN_ASC_STL_API constexpr result_type b() const noexcept
        {
            return upper_;
        }
        friend CANN_ASC_STL_API constexpr bool operator==(param_type left, param_type right) noexcept
        {
            return left.lower_ == right.lower_ && left.upper_ == right.upper_;
        }
        friend CANN_ASC_STL_API constexpr bool operator!=(param_type left, param_type right) noexcept
        {
            return !(left == right);
        }

    private:
        result_type lower_;
        result_type upper_;
    };

    CANN_ASC_STL_API constexpr uniform_int_distribution() noexcept = default;
    CANN_ASC_STL_API explicit constexpr uniform_int_distribution(result_type lower,
        result_type upper = numeric_limits<result_type>::max()) noexcept  // NOLINT(build/include_what_you_use)
        : parameters_(lower, upper)
    {}
    CANN_ASC_STL_API explicit constexpr uniform_int_distribution(const param_type& parameters) noexcept
        : parameters_(parameters)
    {}
    CANN_ASC_STL_API constexpr void reset() noexcept
    {}
    template <class URng>
    CANN_ASC_STL_API constexpr result_type operator()(URng& generator) noexcept
    {
        return (*this)(generator, parameters_);
    }
    template <class URng>
    CANN_ASC_STL_API constexpr result_type operator()(URng& generator, const param_type& parameters) noexcept
    {
        static_assert(__asc_random_is_valid_urng<URng>,
            "uniform_int_distribution requires an unsigned uniform random bit generator");
        using UnsignedResult =
            conditional_t<(sizeof(result_type) <= sizeof(uint32_t)), uint32_t, make_unsigned_t<result_type>>;
        const UnsignedResult span = static_cast<UnsignedResult>(parameters.b()) -
            static_cast<UnsignedResult>(parameters.a()) + UnsignedResult(1);
        if (span == 1) {
            return parameters.a();
        }
        if (span == 0) {
            return static_cast<result_type>(
                __independent_bits_engine<URng, UnsignedResult>(generator, numeric_limits<UnsignedResult>::digits)());
        }
        constexpr size_t digits = numeric_limits<UnsignedResult>::digits;
        size_t width = digits - countl_zero(span) - 1;
        const UnsignedResult maximum = numeric_limits<UnsignedResult>::max();  // NOLINT(build/include_what_you_use)
        if ((span & (maximum >> (digits - width))) != 0) {
            ++width;
        }
        __independent_bits_engine<URng, UnsignedResult> engine(generator, width);
        UnsignedResult sample = engine();
        while (sample >= span) {
            sample = engine();
        }
        return static_cast<result_type>(sample + static_cast<UnsignedResult>(parameters.a()));
    }
    CANN_ASC_STL_API constexpr result_type a() const noexcept
    {
        return parameters_.a();
    }
    CANN_ASC_STL_API constexpr result_type b() const noexcept
    {
        return parameters_.b();
    }
    CANN_ASC_STL_API constexpr result_type min() const noexcept
    {
        return a();
    }
    CANN_ASC_STL_API constexpr result_type max() const noexcept
    {
        return b();
    }
    CANN_ASC_STL_API constexpr param_type param() const noexcept
    {
        return parameters_;
    }
    CANN_ASC_STL_API constexpr void param(const param_type& parameters) noexcept
    {
        parameters_ = parameters;
    }
    friend CANN_ASC_STL_API constexpr bool operator==(
        const uniform_int_distribution& left, const uniform_int_distribution& right) noexcept
    {
        return left.parameters_ == right.parameters_;
    }
    friend CANN_ASC_STL_API constexpr bool operator!=(
        const uniform_int_distribution& left, const uniform_int_distribution& right) noexcept
    {
        return !(left == right);
    }

private:
    param_type parameters_{};
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANDOM_UNIFORM_INT_DISTRIBUTION_H
