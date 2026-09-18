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

#ifndef CANN_ASC_STL_STD_DETAIL_ASSERT_H
#define CANN_ASC_STL_STD_DETAIL_ASSERT_H

#include <asc/std/__asc/compiler.h>
#include <asc/std/__asc/system_header.h>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__asc/attributes.h>
#include <asc/std/__asc/builtin.h>
#include <asc/std/__asc/execution_space.h>
#include <asc/std/__asc/preprocessor.h>
#include <asc/std/__asc/os.h>

#if CANN_ASC_STL_DETAIL_HOSTED()
#include <assert.h>
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

#if defined(_DEBUG) || defined(DEBUG)
#ifndef CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#define CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#endif  // !CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#endif  // _DEBUG || DEBUG

// Automatically enable assertions when debug mode is enabled
#ifdef CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#ifndef ASC_ENABLE_ASSERTIONS
#define ASC_ENABLE_ASSERTIONS
#endif  // !ASC_ENABLE_ASSERTIONS
#endif  // CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE

//! Ensure that we switch on host assertions when all assertions are enabled
#ifndef ASC_ENABLE_HOST_ASSERTIONS
#ifdef ASC_ENABLE_ASSERTIONS
#define ASC_ENABLE_HOST_ASSERTIONS
#endif  // ASC_ENABLE_ASSERTIONS
#endif  // !ASC_ENABLE_HOST_ASSERTIONS

//! Ensure that we switch on device assertions when all assertions are enabled
#ifndef ASC_ENABLE_DEVICE_ASSERTIONS
#ifdef ASC_ENABLE_ASSERTIONS
#define ASC_ENABLE_DEVICE_ASSERTIONS
#endif  // ASC_ENABLE_ASSERTIONS
#endif  // !ASC_ENABLE_DEVICE_ASSERTIONS

//! Use the different standard library implementations to implement host side asserts
//! CANN_ASC_STL_DETAIL_ASSERT_IMPL_HOST should never be used directly
#if CANN_ASC_STL_DETAIL_OS(QNX)
#define CANN_ASC_STL_DETAIL_ASSERT_IMPL_HOST(expression, message) ((void)0)
#elif CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()  // There is no host standard library in CCE device compilation
#define CANN_ASC_STL_DETAIL_ASSERT_IMPL_HOST(expression, message) ((void)0)
#elif __has_include(<yvals.h>) && CANN_ASC_STL_DETAIL_OS(WINDOWS)  // Windows uses _STL_VERIFY from <yvals.h>
#include <yvals.h>
#define CANN_ASC_STL_DETAIL_ASSERT_IMPL_HOST(expression, message) _STL_VERIFY(expression, message)
#else  // ^^^ MSVC STL ^^^ / vvv !MSVC STL vvv
#ifdef NDEBUG
// Reintroduce the __assert_fail / __assert_rtn declaration
extern "C" {
#if CANN_ASC_STL_DETAIL_OS(APPLE)
void __assert_rtn(const char* __function, const char* __assertion, const char* __file, unsigned int __line) noexcept
    __attribute__((__noreturn__));
#else   // ^^^ CANN_ASC_STL_DETAIL_OS(APPLE) ^^^ / vvv !CANN_ASC_STL_DETAIL_OS(APPLE) ^^^
void __assert_fail(const char* __assertion, const char* __file, unsigned int __line, const char* __function) noexcept
    __attribute__((__noreturn__));
#endif  // !CANN_ASC_STL_DETAIL_OS(APPLE)
}
#endif  // NDEBUG

#if CANN_ASC_STL_DETAIL_OS(APPLE)
#define CANN_ASC_STL_DETAIL_ASSERT_IMPL_HOST(expression, message)        \
    CANN_ASC_STL_DETAIL_BUILTIN_EXPECT(static_cast<bool>(expression), 1) \
    ? (void)0 : __assert_rtn(__func__, __FILE__, __LINE__, message)
#elif CANN_ASC_STL_DETAIL_OS(ANDROID)
#define CANN_ASC_STL_DETAIL_ASSERT_IMPL_HOST(expression, message)        \
    CANN_ASC_STL_DETAIL_BUILTIN_EXPECT(static_cast<bool>(expression), 1) \
    ? (void)0 : __assert2(__FILE__, __LINE__, __func__, message)
#else  // ^^^ CANN_ASC_STL_DETAIL_OS(APPLE) ^^^ / vvv !CANN_ASC_STL_DETAIL_OS(APPLE) ^^^
#define CANN_ASC_STL_DETAIL_ASSERT_IMPL_HOST(expression, message)        \
    CANN_ASC_STL_DETAIL_BUILTIN_EXPECT(static_cast<bool>(expression), 1) \
    ? (void)0 : __assert_fail(message, __FILE__, __LINE__, __func__)
#endif  // !CANN_ASC_STL_DETAIL_OS(APPLE)
#endif  // !MSVC STL

//! ASC has no device-side assertion mechanism.
//! Device assertions are no-ops in ASC-STL.
//! CANN_ASC_STL_DETAIL_ASSERT_IMPL_DEVICE should never be used directly
#define CANN_ASC_STL_DETAIL_ASSERT_IMPL_DEVICE(expression, message) ((void)0)

//! CANN_ASC_STL_DETAIL_ASSERT_HOST is enabled conditionally depending on ASC_ENABLE_HOST_ASSERTIONS
#ifdef ASC_ENABLE_HOST_ASSERTIONS
#define CANN_ASC_STL_DETAIL_ASSERT_HOST(expression, message) CANN_ASC_STL_DETAIL_ASSERT_IMPL_HOST(expression, message)
#else  // ^^^ ASC_ENABLE_HOST_ASSERTIONS ^^^ / vvv !ASC_ENABLE_HOST_ASSERTIONS vvv
#define CANN_ASC_STL_DETAIL_ASSERT_HOST(expression, message) ((void)0)
#endif  // !ASC_ENABLE_HOST_ASSERTIONS

//! CANN_ASC_STL_DETAIL_ASSERT_DEVICE is enabled conditionally depending on ASC_ENABLE_DEVICE_ASSERTIONS
#ifdef ASC_ENABLE_DEVICE_ASSERTIONS
#define CANN_ASC_STL_DETAIL_ASSERT_DEVICE(expression, message) \
    CANN_ASC_STL_DETAIL_ASSERT_IMPL_DEVICE(expression, message)
#else  // ^^^ ASC_ENABLE_DEVICE_ASSERTIONS ^^^ / vvv !ASC_ENABLE_DEVICE_ASSERTIONS vvv
#define CANN_ASC_STL_DETAIL_ASSERT_DEVICE(expression, message) ((void)0)
#endif  // !ASC_ENABLE_DEVICE_ASSERTIONS

//! CANN_ASC_STL_DETAIL_VERIFY is enabled unconditionally and reserved for critical checks that are required to always
//! be on CANN_ASC_STL_DETAIL_ASSERT is enabled conditionally depending on ASC_ENABLE_HOST_ASSERTIONS and
//! ASC_ENABLE_DEVICE_ASSERTIONS
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#define CANN_ASC_STL_DETAIL_VERIFY(expression, message) CANN_ASC_STL_DETAIL_ASSERT_IMPL_DEVICE(expression, message)
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) CANN_ASC_STL_DETAIL_ASSERT_DEVICE(expression, message)
#else  // ^^^ CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() ^^^ / vvv !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() vvv
#define CANN_ASC_STL_DETAIL_VERIFY(expression, message) CANN_ASC_STL_DETAIL_ASSERT_IMPL_HOST(expression, message)
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) CANN_ASC_STL_DETAIL_ASSERT_HOST(expression, message)
#endif  // !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

#endif  // CANN_ASC_STL_STD_DETAIL_ASSERT_H
