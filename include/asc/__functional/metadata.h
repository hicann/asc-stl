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

#ifndef CANN_ASC_STL_ASC___FUNCTIONAL_METADATA_H
#define CANN_ASC_STL_ASC___FUNCTIONAL_METADATA_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// Operation-traits backend for the later public <asc/functional> facade.
// Metadata is registered only where the documented mathematical property is
// true for the approved standard operators and the ASC minimum/maximum
// reducers; floating-point addition is deliberately not associative. The
// reduce/scan backends consume these traits to select legal parallelization,
// so every spelling is a compile-time constant expression valid in Host,
// ordinary AICore and pure SIMT.
namespace asc::detail {

template <bool Value>
struct metadata_bool {
    static constexpr bool value = Value;
    CANN_ASC_STL_API constexpr operator bool() const noexcept
    {
        return Value;
    }
};

// Associativity over the supported integer and logical operator vocabulary.
// Integer multiplication over signed types is not registered: overflow makes
// the mathematical property false under wrapping.
template <class Operator>
struct is_associative_op : metadata_bool<false> {};

struct add_op {};
struct multiply_op {};
struct logical_and_op {};
struct logical_or_op {};
struct bitwise_and_op {};
struct bitwise_or_op {};
struct bitwise_xor_op {};
struct minimum_op {};
struct maximum_op {};

template <>
struct is_associative_op<add_op> : metadata_bool<true> {};
template <>
struct is_associative_op<multiply_op> : metadata_bool<true> {};
template <>
struct is_associative_op<logical_and_op> : metadata_bool<true> {};
template <>
struct is_associative_op<logical_or_op> : metadata_bool<true> {};
template <>
struct is_associative_op<bitwise_and_op> : metadata_bool<true> {};
template <>
struct is_associative_op<bitwise_or_op> : metadata_bool<true> {};
template <>
struct is_associative_op<bitwise_xor_op> : metadata_bool<true> {};
template <>
struct is_associative_op<minimum_op> : metadata_bool<true> {};
template <>
struct is_associative_op<maximum_op> : metadata_bool<true> {};

// Commutativity: every registered associative operator above except that the
// property also holds for equality-style comparisons, which are not reducers
// and stay unregistered.
template <class Operator>
struct is_commutative_op : is_associative_op<Operator> {};

// Identity elements. Absorbing elements follow the same registration rule:
// only mathematically true pairs are recorded.
template <class Operator, class T>
struct identity_element_op {
    static constexpr bool has_value = false;
};

template <class T>
struct identity_element_op<add_op, T> {
    static constexpr bool has_value = true;
    static constexpr T value = T{0};
};

template <class T>
struct identity_element_op<multiply_op, T> {
    static constexpr bool has_value = true;
    static constexpr T value = T{1};
};

template <class T>
struct identity_element_op<logical_and_op, T> {
    static constexpr bool has_value = true;
    static constexpr bool value = true;
};

template <class T>
struct identity_element_op<logical_or_op, T> {
    static constexpr bool has_value = true;
    static constexpr bool value = false;
};

template <class T>
struct identity_element_op<bitwise_and_op, T> {
    static constexpr bool has_value = true;
    static constexpr T value = static_cast<T>(~T{0});
};

template <class T>
struct identity_element_op<bitwise_or_op, T> {
    static constexpr bool has_value = true;
    static constexpr T value = T{0};
};

template <class T>
struct identity_element_op<bitwise_xor_op, T> {
    static constexpr bool has_value = true;
    static constexpr T value = T{0};
};

template <class Operator, class T>
struct absorbing_element_op {
    static constexpr bool has_value = false;
};

template <class T>
struct absorbing_element_op<multiply_op, T> {
    static constexpr bool has_value = true;
    static constexpr T value = T{0};
};

template <class T>
struct absorbing_element_op<logical_and_op, T> {
    static constexpr bool has_value = true;
    static constexpr bool value = false;
};

template <class T>
struct absorbing_element_op<bitwise_and_op, T> {
    static constexpr bool has_value = true;
    static constexpr T value = T{0};
};

// Always-predicates and value reducers used by the public facade; each is a
// stateless callable valid in every execution space.
struct always_true_op {
    CANN_ASC_STL_API constexpr bool operator()() const noexcept
    {
        return true;
    }
};

struct always_false_op {
    CANN_ASC_STL_API constexpr bool operator()() const noexcept
    {
        return false;
    }
};

template <class T>
struct equal_to_value_op {
    T expected;
    CANN_ASC_STL_API constexpr bool operator()(const T& value) const noexcept
    {
        return value == expected;
    }
};

template <class T>
struct maximum_op_of {
    CANN_ASC_STL_API constexpr T operator()(const T& left, const T& right) const noexcept
    {
        return left < right ? right : left;
    }
};

template <class T>
struct minimum_op_of {
    CANN_ASC_STL_API constexpr T operator()(const T& left, const T& right) const noexcept
    {
        return left < right ? left : right;
    }
};

}  // namespace asc::detail

#endif  // CANN_ASC_STL_ASC___FUNCTIONAL_METADATA_H
