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

#ifndef CANN_ASC_STL_STD_DETAIL_VERSION_FEATURES_H
#define CANN_ASC_STL_STD_DETAIL_VERSION_FEATURES_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

// Public ISO-equivalent feature tests: __cpp_lib_x -> CANN_ASC_STL_LIB_x.
// Values describe asc::std in this translation unit, including real backports.
// A partial facility has no version macro. See the version API's feature table
// for revision requirements and reasons for withholding newer/partial features.
#define CANN_ASC_STL_LIB_apply 201603L
#define CANN_ASC_STL_LIB_as_const 201510L
#define CANN_ASC_STL_LIB_bitops 201907L
#define CANN_ASC_STL_LIB_bool_constant 201505L
#define CANN_ASC_STL_LIB_bounded_array_traits 201902L
#define CANN_ASC_STL_LIB_byte 201603L
#define CANN_ASC_STL_LIB_clamp 201603L
#define CANN_ASC_STL_LIB_constexpr_numeric 201911L
#define CANN_ASC_STL_LIB_endian 201907L
#define CANN_ASC_STL_LIB_exchange_function 201304L
#define CANN_ASC_STL_LIB_gcd_lcm 201606L
#define CANN_ASC_STL_LIB_int_pow2 202002L
#define CANN_ASC_STL_LIB_integer_comparison_functions 202002L
#define CANN_ASC_STL_LIB_integer_sequence 201304L
#define CANN_ASC_STL_LIB_integral_constant_callable 201304L
#define CANN_ASC_STL_LIB_invoke 201411L
#define CANN_ASC_STL_LIB_invoke_r 202106L
#define CANN_ASC_STL_LIB_is_invocable 201703L
#define CANN_ASC_STL_LIB_is_nothrow_convertible 201806L
#define CANN_ASC_STL_LIB_is_null_pointer 201309L
#define CANN_ASC_STL_LIB_is_scoped_enum 202011L
#define CANN_ASC_STL_LIB_is_swappable 201603L
#define CANN_ASC_STL_LIB_logical_traits 201510L
#define CANN_ASC_STL_LIB_make_from_tuple 201606L
#define CANN_ASC_STL_LIB_make_reverse_iterator 201402L
#define CANN_ASC_STL_LIB_not_fn 201603L
#define CANN_ASC_STL_LIB_raw_memory_algorithms 201606L
#define CANN_ASC_STL_LIB_remove_cvref 201711L
#define CANN_ASC_STL_LIB_robust_nonmodifying_seq_ops 201304L
#define CANN_ASC_STL_LIB_sample 201603L
#define CANN_ASC_STL_LIB_shift 201806L
#define CANN_ASC_STL_LIB_ssize 201902L
#define CANN_ASC_STL_LIB_to_address 201711L
#define CANN_ASC_STL_LIB_to_array 201907L
#define CANN_ASC_STL_LIB_to_underlying 202102L
#define CANN_ASC_STL_LIB_tuple_element_t 201402L
#define CANN_ASC_STL_LIB_tuples_by_type 201304L
#define CANN_ASC_STL_LIB_type_identity 201806L
#define CANN_ASC_STL_LIB_unreachable 202202L
#define CANN_ASC_STL_LIB_unwrap_ref 201811L
#define CANN_ASC_STL_LIB_void_t 201411L

// Compiler-dependent features use the same decisions as their implementation.
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_launder) || defined(__GNUC__)
#define CANN_ASC_STL_LIB_launder 201606L
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_addressof) || defined(__GNUC__)
#define CANN_ASC_STL_LIB_addressof_constexpr 201603L
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_bit_cast)
#define CANN_ASC_STL_DETAIL_BUILTIN_BIT_CAST(...) __builtin_bit_cast(__VA_ARGS__)
#endif
#if defined(CANN_ASC_STL_DETAIL_BUILTIN_BIT_CAST)
#define CANN_ASC_STL_DETAIL_CONSTEXPR_BIT_CAST constexpr
#define CANN_ASC_STL_DETAIL_HAS_CONSTEXPR_BIT_CAST() 1
#define CANN_ASC_STL_LIB_bit_cast 201806L
#else
#define CANN_ASC_STL_DETAIL_CONSTEXPR_BIT_CAST
#define CANN_ASC_STL_DETAIL_HAS_CONSTEXPR_BIT_CAST() 0
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__has_unique_object_representations)
#define CANN_ASC_STL_LIB_has_unique_object_representations 201606L
#endif
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_aggregate)
#define CANN_ASC_STL_LIB_is_aggregate 201703L
#endif
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_final)
#define CANN_ASC_STL_LIB_is_final 201402L
#endif

#ifndef CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_is_constant_evaluated) || \
    (defined(__GNUC__) && !defined(__clang__) && __GNUC__ >= 9)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED(...) __builtin_is_constant_evaluated(__VA_ARGS__)
#endif
#endif
#if defined(CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED)
#define CANN_ASC_STL_LIB_is_constant_evaluated 201811L
#endif

// source_location::current must be immediate. The Device subset cannot provide
// the standard's string observers, even when the compiler supports consteval.
#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && CANN_ASC_STL_DETAIL_HAS_CONSTEVAL() && \
    (CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_FILE) || defined(__GNUC__)) &&           \
    (CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_LINE) || defined(__GNUC__)) &&           \
    (CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_FUNCTION) || defined(__GNUC__))
#define CANN_ASC_STL_LIB_source_location 201907L
#define CANN_ASC_STL_DETAIL_SOURCE_LOCATION_CURRENT consteval
#else
#define CANN_ASC_STL_DETAIL_SOURCE_LOCATION_CURRENT constexpr
#endif

// These capabilities describe ASC-STL's selected interface subsets in the
// current supported configuration. They do not describe the Host std library
// or claim full conformance to an entire ISO library revision.
#define CANN_ASC_STL_HAS_SOURCE_LOCATION 1
#define CANN_ASC_STL_HAS_UNREACHABLE 1
#define CANN_ASC_STL_HAS_TYPE_IDENTITY 1
#define CANN_ASC_STL_HAS_ENDIAN 1
#define CANN_ASC_STL_HAS_CONCEPT_PREDICATES 1
#define CANN_ASC_STL_HAS_NATIVE_CONCEPTS CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
#define CANN_ASC_STL_HAS_SPAN 1
#define CANN_ASC_STL_HAS_TO_ARRAY 1
#define CANN_ASC_STL_HAS_MDSPAN 1
#define CANN_ASC_STL_HAS_SUBMDSPAN 1
#define CANN_ASC_STL_HAS_EXPECTED 1
#define CANN_ASC_STL_HAS_OPTIONAL_REFERENCE 1
#define CANN_ASC_STL_HAS_INPLACE_VECTOR 1
#define CANN_ASC_STL_HAS_PHILOX 1
#define CANN_ASC_STL_HAS_ALLOCATE_AT_LEAST 1
#define CANN_ASC_STL_HAS_FORMAT_TO_N_RESULT 1
#define CANN_ASC_STL_HAS_FORMAT CANN_ASC_STL_DETAIL_HAS_CONSTEVAL()

#if defined(CANN_ASC_STL_LIB_is_constant_evaluated)
#define CANN_ASC_STL_HAS_IS_CONSTANT_EVALUATED 1
#else
#define CANN_ASC_STL_HAS_IS_CONSTANT_EVALUATED 0
#endif

// Existing implementation vocabulary; these are not public feature macros.
#define CANN_ASC_STL_DETAIL_LIB_bool_constant CANN_ASC_STL_LIB_bool_constant
#define CANN_ASC_STL_DETAIL_LIB_integral_constant_callable CANN_ASC_STL_LIB_integral_constant_callable
#define CANN_ASC_STL_DETAIL_LIB_void_t CANN_ASC_STL_LIB_void_t
#define CANN_ASC_STL_DETAIL_LIB_endian CANN_ASC_STL_LIB_endian
#define CANN_ASC_STL_DETAIL_LIB_type_identity CANN_ASC_STL_LIB_type_identity
#define CANN_ASC_STL_DETAIL_LIB_unreachable CANN_ASC_STL_LIB_unreachable
#if defined(CANN_ASC_STL_LIB_is_constant_evaluated)
#define CANN_ASC_STL_DETAIL_LIB_is_constant_evaluated CANN_ASC_STL_LIB_is_constant_evaluated
#endif

#endif  // CANN_ASC_STL_STD_DETAIL_VERSION_FEATURES_H
