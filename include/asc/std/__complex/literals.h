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

#ifndef CANN_ASC_STL_ASC_STD___COMPLEX_LITERALS_H
#define CANN_ASC_STL_ASC_STD___COMPLEX_LITERALS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/__detail/execution_space.h>
#include <asc/std/__complex/complex.h>

// Inline definition of the CANN_ASC_STL_DETAIL_HOSTED() gate (the __config
// does not provide it): AI-core kernel compilation has no host standard
// library and counts as freestanding, as does an explicit opt-out.
#if !defined(CANN_ASC_STL_DETAIL_HOSTED)
#if defined(CANN_ASC_STL_DETAIL_ENABLE_FREESTANDING) || defined(__CCE__)
#define CANN_ASC_STL_DETAIL_HOSTED() 0
#else
#define CANN_ASC_STL_DETAIL_HOSTED() 1
#endif
#endif  // CANN_ASC_STL_DETAIL_HOSTED

// User-defined literal declarations have long-double arguments. Keep these in
// Host code: AI-core compilation has no long-double arithmetic or UDL call
// path. complex is float-only in this tree, so only the imaginary-float
// suffix family is deliverable; the double/long-double suffixes (i, il)
// arrive together with a widened complex.
#if CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wliteral-suffix"
#endif
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wuser-defined-literals"
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

// Mixed complex/float multiplication in direct form: the binary
// operator* of complex is itself a template over complex<T>, so a scalar
// right operand cannot deduce T and these non-template overloads are the
// only direct-form spelling. They predate the literals below and stay.
CANN_ASC_STL_API constexpr complex<float> operator*(const complex<float>& left, float right) noexcept
{
    return {left.real() * right, left.imag() * right};
}
CANN_ASC_STL_API constexpr complex<float> operator*(float left, const complex<float>& right) noexcept
{
    return right * left;
}

inline namespace literals {
inline namespace complex_literals {
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr complex<float> operator""if(long double x) noexcept
{
    return {0.0f, static_cast<float>(x)};
}
CANN_ASC_STL_NODISCARD CANN_ASC_STL_HOST_API constexpr complex<float> operator""if(unsigned long long x) noexcept
{
    return {0.0f, static_cast<float>(x)};
}
}  // namespace complex_literals
}  // namespace literals

CANN_ASC_STL_END_NAMESPACE

#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
#endif  // CANN_ASC_STL_DETAIL_HOSTED() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

#endif  // CANN_ASC_STL_ASC_STD___COMPLEX_LITERALS_H
