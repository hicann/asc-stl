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

#ifndef CANN_ASC_STL_ASC___ARGUMENT_WRAPPERS_H
#define CANN_ASC_STL_ASC___ARGUMENT_WRAPPERS_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// Algorithm-argument wrapper backend.  Status: the public <asc/argument>
// facade currently defines its own self-contained wrapper classes and does
// not consume this backend; these types stay delivered because the unit
// tests (test/cases/asc/__argument/wrappers) pin their semantics, and they
// remain the designated layering target should the facade ever delegate to
// them.  Removing the file or rewiring the facade onto it is a product
// decision.  Vocabulary: `constant` communicates a compile-time-known value;
// `immediate` means the value is available to Host dispatch at submission;
// `deferred` means the referenced Device value becomes available only in
// stream order.  Bounds permit safe compile-time/backend selection without
// synchronously reading deferred Device data.  The wrappers never allocate,
// never copy Device storage and never synchronize a stream; internal
// unwrap/access traits and sequence helpers stay private.
namespace asc::detail {

struct no_bounds_state {
    static constexpr bool bounded = false;
};

template <auto LowerBound, auto UpperBound>
struct static_bounds_state {
    static constexpr bool bounded = true;
    static constexpr auto lower = LowerBound;
    static constexpr auto upper = UpperBound;
};

template <class T>
struct runtime_bounds_state {
    static constexpr bool bounded = true;
    T lower{};
    T upper{};

    CANN_ASC_STL_API constexpr runtime_bounds_state(T low, T high) noexcept : lower(low), upper(high)
    {}
};

template <auto Value>
struct constant_argument {
    static constexpr auto value = Value;
    static constexpr bool is_constant = true;
    static constexpr bool is_immediate = true;
    static constexpr bool is_deferred = false;
};

template <class T, class Bounds = no_bounds_state>
struct immediate_argument {
    T value{};
    Bounds bounds{};

    CANN_ASC_STL_API constexpr immediate_argument(T given) noexcept : value(given)
    {}
    CANN_ASC_STL_API constexpr immediate_argument(T given, Bounds given_bounds) noexcept
        : value(given), bounds(given_bounds)
    {}

    static constexpr bool is_constant = false;
    static constexpr bool is_immediate = true;
    static constexpr bool is_deferred = false;
};

template <class T, class Bounds = no_bounds_state>
struct deferred_argument {
    const T* location{};
    Bounds bounds{};

    CANN_ASC_STL_API constexpr deferred_argument(const T* given) noexcept : location(given)
    {}
    CANN_ASC_STL_API constexpr deferred_argument(const T* given, Bounds given_bounds) noexcept
        : location(given), bounds(given_bounds)
    {}

    static constexpr bool is_constant = false;
    static constexpr bool is_immediate = false;
    static constexpr bool is_deferred = true;
};

template <class T, class Bounds = no_bounds_state>
struct deferred_sequence_argument {
    const T* first{};
    __SIZE_TYPE__ length{};
    Bounds bounds{};

    CANN_ASC_STL_API constexpr deferred_sequence_argument(const T* given_first, __SIZE_TYPE__ given_length) noexcept
        : first(given_first), length(given_length)
    {}
    CANN_ASC_STL_API constexpr deferred_sequence_argument(
        const T* given_first, __SIZE_TYPE__ given_length, Bounds given_bounds) noexcept
        : first(given_first), length(given_length), bounds(given_bounds)
    {}

    static constexpr bool is_constant = false;
    static constexpr bool is_immediate = false;
    static constexpr bool is_deferred = true;
    static constexpr bool is_sequence = true;
};

template <class Wrapper>
struct argument_traits {
    static constexpr bool is_constant = false;
    static constexpr bool is_immediate = false;
    static constexpr bool is_deferred = false;
    static constexpr bool is_sequence = false;
};

template <auto Value>
struct argument_traits<constant_argument<Value>> {
    static constexpr bool is_constant = true;
    static constexpr bool is_immediate = true;
    static constexpr bool is_deferred = false;
    static constexpr bool is_sequence = false;
};

template <class T, class Bounds>
struct argument_traits<immediate_argument<T, Bounds>> {
    static constexpr bool is_constant = false;
    static constexpr bool is_immediate = true;
    static constexpr bool is_deferred = false;
    static constexpr bool is_sequence = false;
};

template <class T, class Bounds>
struct argument_traits<deferred_argument<T, Bounds>> {
    static constexpr bool is_constant = false;
    static constexpr bool is_immediate = false;
    static constexpr bool is_deferred = true;
    static constexpr bool is_sequence = false;
};

template <class T, class Bounds>
struct argument_traits<deferred_sequence_argument<T, Bounds>> {
    static constexpr bool is_constant = false;
    static constexpr bool is_immediate = false;
    static constexpr bool is_deferred = true;
    static constexpr bool is_sequence = true;
};

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___ARGUMENT_WRAPPERS_H
