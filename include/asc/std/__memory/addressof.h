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

#ifndef CANN_ASC_STL_STD_DETAIL_MEMORY_ADDRESSOF_H
#define CANN_ASC_STL_STD_DETAIL_MEMORY_ADDRESSOF_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#if CANN_ASC_STL_DETAIL_COMPILER(CLANG, >=, 15) || CANN_ASC_STL_DETAIL_COMPILER(GCC, >=, 12)
#define CANN_ASC_STL_DETAIL_HAS_BUILTIN_STD_ADDRESSOF() 1
#else  // ^^^ has builtin std::addressof ^^^ / vvv no builtin std::addressof vvv
#define CANN_ASC_STL_DETAIL_HAS_BUILTIN_STD_ADDRESSOF() 0
#endif  // ^^^ no builtin std::addressof ^^^

// We cannot use host features if we are building in freestanding
#if CANN_ASC_STL_DETAIL_FREESTANDING()
#undef CANN_ASC_STL_DETAIL_HAS_BUILTIN_STD_ADDRESSOF
#define CANN_ASC_STL_DETAIL_HAS_BUILTIN_STD_ADDRESSOF() 0
#endif  // CANN_ASC_STL_DETAIL_FREESTANDING()

// include minimal std:: headers
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN_STD_ADDRESSOF()
#if CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX) && __has_include(<bits/move.h>)
#include <bits/move.h>
#elif CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBCXX) && __has_include(<__memory/addressof.h>)
#include <__memory/addressof.h>
#else
#include <asc/std/__host_stdlib/memory>
#endif
#endif  // CANN_ASC_STL_DETAIL_HAS_BUILTIN_STD_ADDRESSOF()

CANN_ASC_STL_DETAIL_DIAG_PUSH
CANN_ASC_STL_DETAIL_DIAG_SUPPRESS_MSVC(
    4312)  // warning C4312: 'type cast': conversion from '_Tp' to '_Tp *' of greater size

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN_STD_ADDRESSOF()

// The compiler treats ::std::addressof as a builtin function so it does not need to be
// instantiated and will be compiled away even at -O0.
using ::std::addressof;

#elif defined(CANN_ASC_STL_DETAIL_BUILTIN_ADDRESSOF)

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_CFI constexpr _Tp* addressof(_Tp& __x) noexcept
{
    return CANN_ASC_STL_DETAIL_BUILTIN_ADDRESSOF(__x);
}

template <class _Tp>
_Tp* addressof(const _Tp&&) noexcept = delete;

#else

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_API CANN_ASC_STL_DETAIL_NO_CFI _Tp* addressof(_Tp& __x) noexcept
{
    return reinterpret_cast<_Tp*>(
        const_cast<char*>(&reinterpret_cast<const volatile char&>(__x)));  // NOLINT(runtime/casting)
}

template <class _Tp>
_Tp* addressof(const _Tp&&) noexcept = delete;

#endif  // defined(CANN_ASC_STL_DETAIL_BUILTIN_ADDRESSOF)

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

CANN_ASC_STL_DETAIL_DIAG_POP

#endif  // CANN_ASC_STL_STD_DETAIL_MEMORY_ADDRESSOF_H
