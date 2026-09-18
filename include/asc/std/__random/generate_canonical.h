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

#ifndef CANN_ASC_STL_ASC_STD___RANDOM_GENERATE_CANONICAL_H
#define CANN_ASC_STL_ASC_STD___RANDOM_GENERATE_CANONICAL_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__bit/integral.h>
#include <asc/std/__limits/numeric_limits.h>
#include <asc/std/cstdint>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class RealType>
struct __generate_canonical_result;

template <>
struct __generate_canonical_result<float> {
    using type = float;
};

template <class RealType, size_t Bits, class UniformRandomBitGenerator>
CANN_ASC_STL_API typename __generate_canonical_result<RealType>::type generate_canonical(
    UniformRandomBitGenerator& generator) noexcept
{
    constexpr size_t requested = Bits < static_cast<size_t>(numeric_limits<RealType>::digits) ?
        Bits :
        static_cast<size_t>(numeric_limits<RealType>::digits);  // NOLINT(build/include_what_you_use)
    const RealType range = static_cast<RealType>(generator.max() - generator.min()) + RealType(1);
    RealType scale = RealType(1);
    RealType sum = RealType(0);
    size_t produced = 0;
    do {
        sum += static_cast<RealType>(generator() - generator.min()) * scale;
        scale *= range;
        size_t range_bits = 0;
        auto remaining = generator.max() - generator.min();
        while (remaining != 0) {
            ++range_bits;
            remaining >>= 1;
        }
        produced += range_bits == 0 ? 1 : range_bits;
    } while (produced < requested);
    const RealType result = sum / scale;
    return result < RealType(1) ? result : RealType(1) - static_cast<RealType>(__FLT_EPSILON__) / RealType(2);
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___RANDOM_GENERATE_CANONICAL_H
