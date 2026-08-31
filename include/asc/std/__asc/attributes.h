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

#ifndef CANN_ASC_STL_STD_DETAIL_ATTRIBUTES_H
#define CANN_ASC_STL_STD_DETAIL_ATTRIBUTES_H

#include <asc/std/__asc/compiler.h>
#include <asc/std/__asc/system_header.h>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__asc/builtin.h>
#include <asc/std/__asc/diagnostic.h>
#include <asc/std/__asc/dialect.h>

// CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE and CANN_ASC_STL_DETAIL_HAS_CPP_ATTRIBUTE are defined in asc/std/__config
// (included transitively via compiler.h).

#ifdef __has_declspec_attribute
#define CANN_ASC_STL_DETAIL_HAS_DECLSPEC_ATTRIBUTE(__x) __has_declspec_attribute(__x)
#else  // ^^^ __has_declspec_attribute ^^^ / vvv !__has_declspec_attribute vvv
#define CANN_ASC_STL_DETAIL_HAS_DECLSPEC_ATTRIBUTE(__x) 0
#endif  // !__has_declspec_attribute

// MSVC needs extra help with empty base classes
#if CANN_ASC_STL_DETAIL_COMPILER(MSVC) || CANN_ASC_STL_DETAIL_HAS_DECLSPEC_ATTRIBUTE(empty_bases)
#define CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES __declspec(empty_bases)
#else  // ^^^ CANN_ASC_STL_DETAIL_COMPILER(MSVC) ^^^ / vvv !CANN_ASC_STL_DETAIL_COMPILER(MSVC) vvv
#define CANN_ASC_STL_DETAIL_DECLSPEC_EMPTY_BASES
#endif  // !CANN_ASC_STL_DETAIL_COMPILER(MSVC)

#if CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(__nodebug__)
#define CANN_ASC_STL_DETAIL_NODEBUG __attribute__((__nodebug__))
#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(__nodebug__) ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(__nodebug__)
       // vvv
#define CANN_ASC_STL_DETAIL_NODEBUG
#endif  // !CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(__nodebug__)

// Debuggers do not step into functions marked with __attribute__((__artificial__)). This
// is useful for small wrapper functions that just dispatch to other functions and that
// are inlined into the caller.
#if CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(__artificial__)
#define CANN_ASC_STL_DETAIL_ARTIFICIAL __attribute__((__artificial__))
#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(__artificial__) ^^^ / vvv
       // !CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(__artificial__) vvv
#define CANN_ASC_STL_DETAIL_ARTIFICIAL
#endif  // !CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(__artificial__)

// CANN_ASC_STL_DETAIL_ASSUME
#if CANN_ASC_STL_DETAIL_HAS_CPP_ATTRIBUTE(assume)
#define CANN_ASC_STL_DETAIL_ASSUME(...) [[assume(__VA_ARGS__)]]
#else
#define CANN_ASC_STL_DETAIL_ASSUME(...) CANN_ASC_STL_DETAIL_BUILTIN_ASSUME(__VA_ARGS__)
#endif

// CANN_ASC_STL_DETAIL_CONST

#if CANN_ASC_STL_DETAIL_HAS_CPP_ATTRIBUTE(__gnu__::__const__)
#define CANN_ASC_STL_DETAIL_CONST [[__gnu__::__const__]]
#else  // ^^^ has gnu::const ^^^ / vvv no gnu::const vvv
#define CANN_ASC_STL_DETAIL_CONST CANN_ASC_STL_DETAIL_PURE
#endif  // ^^^ no gnu::const ^^^

// CANN_ASC_STL_DETAIL_DIAGNOSE_IF

#if CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(__diagnose_if__)
#define CANN_ASC_STL_DETAIL_DIAGNOSE_IF(_COND, _MSG, _TYPE) __attribute__((__diagnose_if__(_COND, _MSG, _TYPE)))
#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(diagnose_if) ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(diagnose_if)
       // vvv
#define CANN_ASC_STL_DETAIL_DIAGNOSE_IF(_COND, _MSG, _TYPE)
#endif  // !CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(__diagnose_if__)

// CANN_ASC_STL_DETAIL_INTRINSIC

// MSVC provides a way to mark functions as intrinsic provided the function's body consists of a single
// return statement of a cast expression (e.g., move(x) or forward<T>(u)).
#if CANN_ASC_STL_DETAIL_COMPILER(MSVC) && CANN_ASC_STL_DETAIL_HAS_CPP_ATTRIBUTE(msvc::intrinsic)
#define CANN_ASC_STL_DETAIL_INTRINSIC [[msvc::intrinsic]]
#else
#define CANN_ASC_STL_DETAIL_INTRINSIC
#endif

// CANN_ASC_STL_DETAIL_PURE

#if CANN_ASC_STL_DETAIL_HAS_CPP_ATTRIBUTE(__gnu__::__pure__)
#define CANN_ASC_STL_DETAIL_PURE [[__gnu__::__pure__]]
#elif CANN_ASC_STL_DETAIL_COMPILER(MSVC)
#define CANN_ASC_STL_DETAIL_PURE __declspec(noalias)
#else
#define CANN_ASC_STL_DETAIL_PURE
#endif

// CANN_ASC_STL_DETAIL_NO_CFI

#if !CANN_ASC_STL_DETAIL_COMPILER(GCC)
#define CANN_ASC_STL_DETAIL_NO_CFI CANN_ASC_STL_DETAIL_NO_SANITIZE("cfi")
#else
#define CANN_ASC_STL_DETAIL_NO_CFI
#endif

// CANN_ASC_STL_DETAIL_NO_SANITIZE

#if CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(__no_sanitize__)
#define CANN_ASC_STL_DETAIL_NO_SANITIZE(_STR) __attribute__((__no_sanitize__(_STR)))
#else  // ^^^ CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(no_sanitize) ^^^ / vvv !CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(no_sanitize)
       // vvv
#define CANN_ASC_STL_DETAIL_NO_SANITIZE(_STR)
#endif  // !CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(__no_sanitize__)

// CANN_ASC_STL_DETAIL_NO_SPECIALIZATIONS

#if CANN_ASC_STL_DETAIL_HAS_CPP_ATTRIBUTE(clang::__no_specializations__)
#define CANN_ASC_STL_DETAIL_NO_SPECIALIZATIONS_BECAUSE(_MSG) [[clang::__no_specializations__(_MSG)]]
#define CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE_NO_SPECIALIZATIONS() 1
#elif CANN_ASC_STL_DETAIL_HAS_CPP_ATTRIBUTE(msvc::no_specializations)
#define CANN_ASC_STL_DETAIL_NO_SPECIALIZATIONS_BECAUSE(_MSG) [[msvc::no_specializations(_MSG)]]
#define CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE_NO_SPECIALIZATIONS() 1
#else  // ^^^ has attribute no_specializations ^^^ / vvv hasn't attribute no_specializations vvv
#define CANN_ASC_STL_DETAIL_NO_SPECIALIZATIONS_BECAUSE(_MSG)
#define CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE_NO_SPECIALIZATIONS() 0
#endif  // ^^^ hasn't attribute no_specializations ^^^

#define CANN_ASC_STL_DETAIL_NO_SPECIALIZATIONS \
    CANN_ASC_STL_DETAIL_NO_SPECIALIZATIONS_BECAUSE("Users are not allowed to specialize this asc entity")

// CANN_ASC_STL_DETAIL_LIFETIMEBOUND

#if CANN_ASC_STL_DETAIL_HAS_CPP_ATTRIBUTE(clang::lifetimebound) || CANN_ASC_STL_DETAIL_COMPILER(CLANG)
#define CANN_ASC_STL_DETAIL_LIFETIMEBOUND [[clang::lifetimebound]]
#elif CANN_ASC_STL_DETAIL_HAS_CPP_ATTRIBUTE(msvc::lifetimebound) || CANN_ASC_STL_DETAIL_COMPILER(MSVC, >=, 19, 37)
#define CANN_ASC_STL_DETAIL_LIFETIMEBOUND [[msvc::lifetimebound]]
#else
#define CANN_ASC_STL_DETAIL_LIFETIMEBOUND
#endif

// CANN_ASC_STL_NO_UNIQUE_ADDRESS

#if CANN_ASC_STL_DETAIL_COMPILER(MSVC) || CANN_ASC_STL_DETAIL_HAS_CPP_ATTRIBUTE(no_unique_address) < 201803L
// MSVC implementation has lead to multiple issues with silent runtime corruption when passing data into kernels
#define CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE_NO_UNIQUE_ADDRESS() 0
#define CANN_ASC_STL_NO_UNIQUE_ADDRESS
#elif CANN_ASC_STL_DETAIL_HAS_CPP_ATTRIBUTE(no_unique_address)
#define CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE_NO_UNIQUE_ADDRESS() 1
#define CANN_ASC_STL_NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#define CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE_NO_UNIQUE_ADDRESS() 0
#define CANN_ASC_STL_NO_UNIQUE_ADDRESS
#endif

#if CANN_ASC_STL_DETAIL_HAS_ATTRIBUTE(__require_constant_initialization__)
#define CANN_ASC_STL_DETAIL_REQUIRE_CONSTANT_INITIALIZATION __attribute__((__require_constant_initialization__))
#else
#define CANN_ASC_STL_DETAIL_REQUIRE_CONSTANT_INITIALIZATION
#endif

// CANN_ASC_STL_DETAIL_RESTRICT

#if CANN_ASC_STL_DETAIL_COMPILER(MSVC)  // vvv CANN_ASC_STL_DETAIL_COMPILER(MSVC) vvv
#define CANN_ASC_STL_DETAIL_RESTRICT __restrict
#else  // ^^^ CANN_ASC_STL_DETAIL_COMPILER(MSVC) ^^^ / vvv !CANN_ASC_STL_DETAIL_COMPILER(MSVC) vvv
#define CANN_ASC_STL_DETAIL_RESTRICT __restrict__
#endif  // ^^^ !CANN_ASC_STL_DETAIL_COMPILER(MSVC) ^^^

#endif  // CANN_ASC_STL_STD_DETAIL_ATTRIBUTES_H
