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

#ifndef CANN_ASC_STL_ASC___EXECUTION_REQUIREMENTS_H
#define CANN_ASC_STL_ASC___EXECUTION_REQUIREMENTS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

namespace asc::detail {

// Execution-space requirement bitset.  Status: the public
// <asc/execution.require.h> facade exposes the execution_requirements value
// triple (determinism/output_ordering/tie_break) and does not consume this
// vocabulary; the bitset stays delivered because the semantics suite
// (test/support/b014_semantics.h) pins it, and it remains the reserved
// vocabulary for future parallelism-degree negotiation.  Removing it or
// exposing it through the facade is a product decision; note the
// near-collision with the public execution_requirements class name.
enum class execution_requirement : unsigned char {
    none = 0,
    host = 1,
    device = 2,
    simd = 4,
    simt = 8,
};

CANN_ASC_STL_API constexpr execution_requirement operator|(
    execution_requirement left, execution_requirement right) noexcept
{
    return static_cast<execution_requirement>(static_cast<unsigned char>(left) | static_cast<unsigned char>(right));
}

CANN_ASC_STL_API constexpr execution_requirement operator&(
    execution_requirement left, execution_requirement right) noexcept
{
    return static_cast<execution_requirement>(static_cast<unsigned char>(left) & static_cast<unsigned char>(right));
}

CANN_ASC_STL_API constexpr execution_requirement operator~(execution_requirement value) noexcept
{
    return static_cast<execution_requirement>(~static_cast<unsigned char>(value));
}

CANN_ASC_STL_API constexpr execution_requirement operator|=(
    execution_requirement& left, execution_requirement right) noexcept
{
    return left = left | right;
}

CANN_ASC_STL_API constexpr execution_requirement operator&=(
    execution_requirement& left, execution_requirement right) noexcept
{
    return left = left & right;
}

CANN_ASC_STL_API constexpr bool has_requirement(execution_requirement value, execution_requirement expected) noexcept
{
    return (static_cast<unsigned char>(value) & static_cast<unsigned char>(expected)) != 0;
}

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___EXECUTION_REQUIREMENTS_H
