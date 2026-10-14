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

#ifndef CANN_ASC_STL_ASC_STD___BIT_ENDIAN_H
#define CANN_ASC_STL_ASC_STD___BIT_ENDIAN_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>

// Centralized endianness probing, inlined here with #ifndef guards so a future
// centralized definition in <asc/__config> wins.
#ifndef CANN_ASC_STL_DETAIL_ENDIAN_LITTLE
#define CANN_ASC_STL_DETAIL_ENDIAN_LITTLE() 0xDEAD
#endif  // CANN_ASC_STL_DETAIL_ENDIAN_LITTLE

#ifndef CANN_ASC_STL_DETAIL_ENDIAN_BIG
#define CANN_ASC_STL_DETAIL_ENDIAN_BIG() 0xFACE
#endif  // CANN_ASC_STL_DETAIL_ENDIAN_BIG

#ifndef CANN_ASC_STL_DETAIL_ENDIAN_PDP
#define CANN_ASC_STL_DETAIL_ENDIAN_PDP() 0xBEEF
#endif  // CANN_ASC_STL_DETAIL_ENDIAN_PDP

#ifndef CANN_ASC_STL_DETAIL_ENDIAN_NATIVE
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || __LITTLE_ENDIAN__
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_LITTLE()
#elif __BIG_ENDIAN__
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_BIG()
#elif defined(__BYTE_ORDER__)
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_LITTLE()
#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_PDP()
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_BIG()
#endif  // __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#elif __has_include(<endian.h>)
#include <endian.h>
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_LITTLE()
#elif __BYTE_ORDER == __PDP_ENDIAN
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_PDP()
#elif __BYTE_ORDER == __BIG_ENDIAN
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_BIG()
#endif  // __BYTE_ORDER == __BIG_ENDIAN
#endif  // ^^^ has endian.h ^^^

#if !defined(CANN_ASC_STL_DETAIL_ENDIAN_NATIVE)
// Failed to determine the endianness of the host architecture; default to
// little-endian in that case.
#define CANN_ASC_STL_DETAIL_ENDIAN_NATIVE() CANN_ASC_STL_DETAIL_ENDIAN_LITTLE()
#endif  // !defined(CANN_ASC_STL_DETAIL_ENDIAN_NATIVE)
#endif  // CANN_ASC_STL_DETAIL_ENDIAN_NATIVE

CANN_ASC_STL_BEGIN_NAMESPACE

enum class endian {
    little = CANN_ASC_STL_DETAIL_ENDIAN_LITTLE(),
    big = CANN_ASC_STL_DETAIL_ENDIAN_BIG(),
    native = CANN_ASC_STL_DETAIL_ENDIAN_NATIVE(),
};

static_assert(endian::native == endian::little || endian::native == endian::big,
    "mixed endianness is not a scalar representation");
static_assert(endian::little != endian::big, "the little and big encodings must be distinct");

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___BIT_ENDIAN_H
