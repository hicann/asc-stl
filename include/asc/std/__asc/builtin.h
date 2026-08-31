/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_STD_DETAIL_BUILTIN_H
#define CANN_ASC_STL_STD_DETAIL_BUILTIN_H

#include <asc/std/__asc/compiler.h>
#include <asc/std/__asc/preprocessor.h>
#include <asc/std/__asc/system_header.h>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__asc/asc_capabilities.h>
#include <asc/std/__asc/extended_data_types.h>
#include <asc/std/__asc/host_std_lib.h>

// Compiler builtin detection for ASC-STL.
//
// Generic compiler builtins are wrapped when the current host/CCE compiler
// advertises support.  Builtins that exist only on compilers ASC-STL does not
// target remain unavailable and are documented as such at the bottom of the
// file.

#ifndef CANN_ASC_STL_DETAIL_HAS_BUILTIN
#ifdef __has_builtin
#define CANN_ASC_STL_DETAIL_HAS_BUILTIN(__x) __has_builtin(__x)
#else
#define CANN_ASC_STL_DETAIL_HAS_BUILTIN(__x) 0
#endif
#endif

#ifdef __has_feature
#define CANN_ASC_STL_DETAIL_HAS_FEATURE(__x) __has_feature(__x)
#else
#define CANN_ASC_STL_DETAIL_HAS_FEATURE(__x) 0
#endif

// '__is_identifier' returns 0 if '__x' is a reserved identifier provided by
// the compiler and 1 otherwise.
#ifdef __is_identifier
#define CANN_ASC_STL_DETAIL_IS_IDENTIFIER(__x) __is_identifier(__x)
#else
#define CANN_ASC_STL_DETAIL_IS_IDENTIFIER(__x) 1
#endif

#define CANN_ASC_STL_DETAIL_HAS_KEYWORD(__x) !(CANN_ASC_STL_DETAIL_IS_IDENTIFIER(__x))
#define CANN_ASC_STL_DETAIL_CHECK_BUILTIN(__x)                                               \
    (CANN_ASC_STL_DETAIL_HAS_BUILTIN(__##__x) || CANN_ASC_STL_DETAIL_HAS_KEYWORD(__##__x) || \
        CANN_ASC_STL_DETAIL_HAS_FEATURE(__x))

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__add_lvalue_reference)
#define CANN_ASC_STL_DETAIL_BUILTIN_ADD_LVALUE_REFERENCE(...) __add_lvalue_reference(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__add_pointer)
#define CANN_ASC_STL_DETAIL_BUILTIN_ADD_POINTER(...) __add_pointer(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__add_rvalue_reference)
#define CANN_ASC_STL_DETAIL_BUILTIN_ADD_RVALUE_REFERENCE(...) __add_rvalue_reference(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_addressof) || CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 7)
#define CANN_ASC_STL_DETAIL_BUILTIN_ADDRESSOF(...) __builtin_addressof(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_assume)
#define CANN_ASC_STL_DETAIL_BUILTIN_ASSUME(...) __builtin_assume(__VA_ARGS__)
#elif CANN_ASC_STL_DETAIL_COMPILER(MSVC)
#define CANN_ASC_STL_DETAIL_BUILTIN_ASSUME(...) __assume(__VA_ARGS__)
#else
#define CANN_ASC_STL_DETAIL_BUILTIN_ASSUME(...)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_constant_p) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_BUILTIN_CONSTANT_P(...) __builtin_constant_p(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_expect) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_BUILTIN_EXPECT(_EXPR, _VAL) __builtin_expect(_EXPR, _VAL)
#else
#define CANN_ASC_STL_DETAIL_BUILTIN_EXPECT(_EXPR, _VAL) (_EXPR)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_huge_valf) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_BUILTIN_HUGE_VALF() __builtin_huge_valf()
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_huge_val) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_BUILTIN_HUGE_VAL() __builtin_huge_val()
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_huge_vall) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_BUILTIN_HUGE_VALL() __builtin_huge_vall()
#endif

#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_huge_valf128) || CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 7)
#define CANN_ASC_STL_DETAIL_BUILTIN_HUGE_VALF128() __builtin_huge_valf128()
#endif
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_is_constant_evaluated) || CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 9)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTANT_EVALUATED(...) __builtin_is_constant_evaluated(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_is_corresponding_member)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_CORRESPONDING_MEMBER(_C1, _C2, _MPtr1, _MPtr2) \
    __builtin_is_corresponding_member(_MPtr1, _MPtr2)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_is_pointer_interconvertible_with_class)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_POINTER_INTERCONVERTIBLE_WITH_CLASS(_S, _MPtr) \
    __builtin_is_pointer_interconvertible_with_class(_MPtr)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_nanf) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_BUILTIN_NANF(...) __builtin_nanf(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_nan) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_BUILTIN_NAN(...) __builtin_nan(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_nanl) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_BUILTIN_NANL(...) __builtin_nanl(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_nanf128) || CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 7)
#define CANN_ASC_STL_DETAIL_BUILTIN_NANF128(...) __builtin_nanf128(__VA_ARGS__)
#endif
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_nansf) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_BUILTIN_NANSF(...) __builtin_nansf(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_nans) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_BUILTIN_NANS(...) __builtin_nans(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_nansl) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_BUILTIN_NANSL(...) __builtin_nansl(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_FLOAT128()
#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_nansf128) || CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 7)
#define CANN_ASC_STL_DETAIL_BUILTIN_NANSF128(...) __builtin_nansf128(__VA_ARGS__)
#endif
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_memcmp) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_BUILTIN_MEMCMP(...) __builtin_memcmp(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_memmove) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_BUILTIN_MEMMOVE(...) __builtin_memmove(__VA_ARGS__)
#endif

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_operator_new) && \
    CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_operator_delete)
#define CANN_ASC_STL_DETAIL_BUILTIN_OPERATOR_DELETE(...) __builtin_operator_delete(__VA_ARGS__)
#define CANN_ASC_STL_DETAIL_BUILTIN_OPERATOR_NEW(...) __builtin_operator_new(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_prefetch) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_BUILTIN_PREFETCH(...) __builtin_prefetch(__VA_ARGS__)
#else
#define CANN_ASC_STL_DETAIL_BUILTIN_PREFETCH(...)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__decay)
#define CANN_ASC_STL_DETAIL_BUILTIN_DECAY(...) __decay(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(has_nothrow_assign)
#define CANN_ASC_STL_DETAIL_BUILTIN_HAS_NOTHROW_ASSIGN(...) __has_nothrow_assign(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(has_nothrow_constructor)
#define CANN_ASC_STL_DETAIL_BUILTIN_HAS_NOTHROW_CONSTRUCTOR(...) __has_nothrow_constructor(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(has_nothrow_copy)
#define CANN_ASC_STL_DETAIL_BUILTIN_HAS_NOTHROW_COPY(...) __has_nothrow_copy(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__integer_pack)
#define CANN_ASC_STL_DETAIL_BUILTIN_INTEGER_PACK(...) __integer_pack(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_array)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_ARRAY(...) __is_array(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_assignable)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_ASSIGNABLE(...) __is_assignable(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_constructible)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_CONSTRUCTIBLE(...) __is_constructible(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_convertible_to)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_CONVERTIBLE_TO(...) __is_convertible_to(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_destructible)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_DESTRUCTIBLE(...) __is_destructible(__VA_ARGS__)
#endif

// These are generic compiler type-trait builtins.  Keep their availability
// tied to the active Host/BiSheng compiler rather than to any fixed
// compiler-version assumption.
#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_trivially_destructible) || CANN_ASC_STL_DETAIL_COMPILER(MSVC)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_TRIVIALLY_DESTRUCTIBLE(...) __is_trivially_destructible(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(has_trivial_destructor) || CANN_ASC_STL_DETAIL_COMPILER(GCC) || \
    CANN_ASC_STL_DETAIL_COMPILER(MSVC)
#define CANN_ASC_STL_DETAIL_BUILTIN_HAS_TRIVIAL_DESTRUCTOR(...) __has_trivial_destructor(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_layout_compatible)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_LAYOUT_COMPATIBLE(...) __is_layout_compatible(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_lvalue_reference)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_LVALUE_REFERENCE(...) __is_lvalue_reference(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_member_function_pointer)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_MEMBER_FUNCTION_POINTER(...) __is_member_function_pointer(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_member_object_pointer)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_MEMBER_OBJECT_POINTER(...) __is_member_object_pointer(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_member_pointer)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_MEMBER_POINTER(...) __is_member_pointer(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_nothrow_assignable)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_ASSIGNABLE(...) __is_nothrow_assignable(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_nothrow_constructible)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_CONSTRUCTIBLE(...) __is_nothrow_constructible(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_nothrow_destructible)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_NOTHROW_DESTRUCTIBLE(...) __is_nothrow_destructible(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_object)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_OBJECT(...) __is_object(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(is_pointer_interconvertible_base_of)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_POINTER_INTERCONVERTIBLE_BASE_OF(...) \
    __is_pointer_interconvertible_base_of(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_reference)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_REFERENCE(...) __is_reference(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_rvalue_reference)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_RVALUE_REFERENCE(...) __is_rvalue_reference(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(make_integer_seq)
#define CANN_ASC_STL_DETAIL_BUILTIN_MAKE_INTEGER_SEQ(...) __make_integer_seq<__VA_ARGS__>
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__reference_constructs_from_temporary)
#define CANN_ASC_STL_DETAIL_BUILTIN_REFERENCE_CONSTRUCTS_FROM_TEMPORARY(...) \
    __reference_constructs_from_temporary(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__reference_converts_from_temporary)
#define CANN_ASC_STL_DETAIL_BUILTIN_REFERENCE_CONVERTS_FROM_TEMPORARY(...) \
    __reference_converts_from_temporary(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__remove_const)
#define CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_CONST(...) __remove_const(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__remove_cv)
#define CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_CV(...) __remove_cv(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__remove_cvref)
#define CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_CVREF(...) __remove_cvref(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__remove_extent)
#define CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_EXTENT(...) __remove_extent(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__remove_pointer)
#define CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_POINTER(...) __remove_pointer(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__remove_reference)
#define CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_REFERENCE_T(...) __remove_reference(__VA_ARGS__)
#elif CANN_ASC_STL_DETAIL_HAS_BUILTIN(__remove_reference_t)
#define CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_REFERENCE_T(...) __remove_reference_t(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__remove_volatile)
#define CANN_ASC_STL_DETAIL_BUILTIN_REMOVE_VOLATILE(...) __remove_volatile(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__type_pack_element)
#define CANN_ASC_STL_DETAIL_BUILTIN_TYPE_PACK_ELEMENT(...) __type_pack_element<__VA_ARGS__>
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_complete_type)
#define CANN_ASC_STL_DETAIL_BUILTIN_IS_COMPLETE_TYPE(...) __is_complete_type(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_clear_padding) && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_BUILTIN_CLEAR_PADDING(...) __builtin_clear_padding(__VA_ARGS__)
#endif

#if CANN_ASC_STL_DETAIL_COMPILER(MSVC)
#define CANN_ASC_STL_DETAIL_BUILTIN_PRETTY_FUNCTION() __FUNCSIG__
#else
#define CANN_ASC_STL_DETAIL_BUILTIN_PRETTY_FUNCTION() __PRETTY_FUNCTION__
#endif

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() && !CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_BUILTIN_STRLEN(...) __builtin_strlen(__VA_ARGS__)
#elif CANN_ASC_STL_DETAIL_CHECK_BUILTIN(builtin_strlen)
#define CANN_ASC_STL_DETAIL_BUILTIN_STRLEN(...) __builtin_strlen(__VA_ARGS__)
#endif

#endif  // CANN_ASC_STL_STD_DETAIL_BUILTIN_H
