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

#ifndef CANN_ASC_STL_ASC_EXECUTION_REQUIRE_H
#define CANN_ASC_STL_ASC_EXECUTION_REQUIRE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__execution/requirements.h>
#include <asc/execution.determinism.h>
#include <asc/execution.output_ordering.h>
#include <asc/execution.tie_break.h>

namespace asc {

class execution_requirements {
public:
    CANN_ASC_STL_HOST inline constexpr execution_requirements() noexcept = default;

    CANN_ASC_STL_HOST inline constexpr determinism determinism_value() const noexcept
    {
        return determinism_;
    }
    CANN_ASC_STL_HOST inline constexpr output_ordering output_ordering_value() const noexcept
    {
        return output_ordering_;
    }
    CANN_ASC_STL_HOST inline constexpr tie_break tie_break_value() const noexcept
    {
        return tie_break_;
    }

private:
    CANN_ASC_STL_HOST inline constexpr execution_requirements(
        determinism determinism_value, output_ordering ordering_value, tie_break tie_value) noexcept
        : determinism_(determinism_value), output_ordering_(ordering_value), tie_break_(tie_value)
    {}

    determinism determinism_{determinism::not_guaranteed};
    output_ordering output_ordering_{output_ordering::unsorted};
    tie_break tie_break_{tie_break::unspecified};

    friend CANN_ASC_STL_HOST inline constexpr execution_requirements require(
        execution_requirements, determinism) noexcept;
    friend CANN_ASC_STL_HOST inline constexpr execution_requirements require(
        execution_requirements, output_ordering) noexcept;
    friend CANN_ASC_STL_HOST inline constexpr execution_requirements require(
        execution_requirements, tie_break) noexcept;
};

CANN_ASC_STL_HOST inline constexpr execution_requirements require(
    execution_requirements base, determinism value) noexcept
{
    return {value, base.output_ordering_, base.tie_break_};
}
CANN_ASC_STL_HOST inline constexpr execution_requirements require(
    execution_requirements base, output_ordering value) noexcept
{
    return {base.determinism_, value, base.tie_break_};
}
CANN_ASC_STL_HOST inline constexpr execution_requirements require(execution_requirements base, tie_break value) noexcept
{
    return {base.determinism_, base.output_ordering_, value};
}
CANN_ASC_STL_HOST inline constexpr execution_requirements require(determinism value) noexcept
{
    return require(execution_requirements{}, value);
}
CANN_ASC_STL_HOST inline constexpr execution_requirements require(output_ordering value) noexcept
{
    return require(execution_requirements{}, value);
}
CANN_ASC_STL_HOST inline constexpr execution_requirements require(tie_break value) noexcept
{
    return require(execution_requirements{}, value);
}

}  // namespace asc

#endif  // CANN_ASC_STL_ASC_EXECUTION_REQUIRE_H
