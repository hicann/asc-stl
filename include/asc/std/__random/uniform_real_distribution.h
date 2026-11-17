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

#ifndef CANN_ASC_STL_ASC_STD___RANDOM_UNIFORM_REAL_DISTRIBUTION_H
#define CANN_ASC_STL_ASC_STD___RANDOM_UNIFORM_REAL_DISTRIBUTION_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__bit/bit_cast.h>
#include <asc/std/__limits/numeric_limits.h>
#include <asc/std/__random/generate_canonical.h>
#include <asc/std/__random/is_valid.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class RealType = double>
class uniform_real_distribution;

template <>
class uniform_real_distribution<float> {
public:
    using result_type = float;

    class param_type {
    public:
        using distribution_type = uniform_real_distribution;

        CANN_ASC_STL_API constexpr explicit param_type(result_type low = 0.0F, result_type high = 1.0F) noexcept
            : low_(low), high_(high)
        {}

        CANN_ASC_STL_API constexpr result_type a() const noexcept
        {
            return low_;
        }

        CANN_ASC_STL_API constexpr result_type b() const noexcept
        {
            return high_;
        }

        CANN_ASC_STL_API friend constexpr bool operator==(const param_type& left, const param_type& right) noexcept
        {
            return left.low_ == right.low_ && left.high_ == right.high_;
        }

        CANN_ASC_STL_API friend constexpr bool operator!=(const param_type& left, const param_type& right) noexcept
        {
            return !(left == right);
        }

    private:
        result_type low_;
        result_type high_;
    };

    CANN_ASC_STL_API constexpr uniform_real_distribution() noexcept = default;

    CANN_ASC_STL_API constexpr explicit uniform_real_distribution(result_type low, result_type high = 1.0F) noexcept
        : parameters_(low, high)
    {}

    CANN_ASC_STL_API constexpr explicit uniform_real_distribution(const param_type& parameters) noexcept
        : parameters_(parameters)
    {}

    CANN_ASC_STL_API constexpr void reset() noexcept
    {}

    template <class URng>
    CANN_ASC_STL_API constexpr result_type operator()(URng& engine) const noexcept
    {
        return (*this)(engine, parameters_);
    }

    template <class URng>
    CANN_ASC_STL_API constexpr result_type operator()(URng& engine, const param_type& parameters) const noexcept
    {
        static_assert(__asc_random_is_valid_urng<URng>, "URng must be an unsigned uniform random bit generator");
        const result_type canonical =
            // NOLINTNEXTLINE(build/include_what_you_use)
            generate_canonical<result_type, numeric_limits<result_type>::digits>(engine);
        const result_type result = (parameters.b() - parameters.a()) * canonical + parameters.a();
        if (result < parameters.b())
            return result;
        const __UINT32_TYPE__ bits = ::asc::std::bit_cast<__UINT32_TYPE__>(parameters.b());
        const __UINT32_TYPE__ previous_bits =
            bits == 0U ? 0x80000001U : (parameters.b() > 0.0F ? bits - 1U : bits + 1U);
        const result_type previous = ::asc::std::bit_cast<result_type>(previous_bits);
        return previous < parameters.a() ? parameters.a() : previous;
    }

    CANN_ASC_STL_API constexpr result_type a() const noexcept
    {
        return parameters_.a();
    }

    CANN_ASC_STL_API constexpr result_type b() const noexcept
    {
        return parameters_.b();
    }

    CANN_ASC_STL_API constexpr param_type param() const noexcept
    {
        return parameters_;
    }

    CANN_ASC_STL_API constexpr void param(const param_type& parameters) noexcept
    {
        parameters_ = parameters;
    }

    CANN_ASC_STL_API constexpr result_type min() const noexcept
    {
        return a();
    }

    CANN_ASC_STL_API constexpr result_type max() const noexcept
    {
        return b();
    }

    CANN_ASC_STL_API friend constexpr bool operator==(
        const uniform_real_distribution& left, const uniform_real_distribution& right) noexcept
    {
        return left.parameters_ == right.parameters_;
    }

    CANN_ASC_STL_API friend constexpr bool operator!=(
        const uniform_real_distribution& left, const uniform_real_distribution& right) noexcept
    {
        return !(left == right);
    }

private:
    param_type parameters_{};
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANDOM_UNIFORM_REAL_DISTRIBUTION_H
