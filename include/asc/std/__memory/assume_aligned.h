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

#ifndef CANN_ASC_STL_ASC_STD___MEMORY_ASSUME_ALIGNED_H
#define CANN_ASC_STL_ASC_STD___MEMORY_ASSUME_ALIGNED_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__bit/bit_cast.h>
#include <asc/std/__memory/is_valid_alignment.h>
#include <asc/std/__type_traits/is_constant_evaluated.h>
#include <asc/std/__type_traits/remove_volatile.h>
#include <asc/std/cstddef>
#include <asc/std/cstdint>

// The shared configuration provides no assertion macro, so inline the minimal
// equivalent here, #ifndef-guarded against a future centralized definition.
#ifndef CANN_ASC_STL_DETAIL_ASSERT
// No-op on the device side (no assertion mechanism there); on the host side,
// checked only when ASC_ENABLE_HOST_ASSERTIONS is explicitly enabled.
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || !defined(ASC_ENABLE_HOST_ASSERTIONS)
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    ((expression) ? static_cast<void>(0) : (__builtin_trap(), static_cast<void>(0)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSERT

CANN_ASC_STL_BEGIN_NAMESPACE

template <size_t Alignment, class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr T* assume_aligned(T* pointer) noexcept
{
    static_assert(__is_valid_alignment<T>(Alignment), "invalid alignment for T");
    // Make no runtime alignment assumption during constant evaluation: return
    // the pointer unchanged (the conservative fallback assumes constant
    // evaluation).
    if (!__default_is_constant_evaluated()) {
        CANN_ASC_STL_DETAIL_ASSERT(
            reinterpret_cast<uintptr_t>(pointer) % Alignment == 0, "Alignment assumption is violated");
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_assume_aligned) || defined(__GNUC__)
        // The builtin does not accept volatile pointers: strip it and return in
        // the original pointer type.
        using ValueType = remove_volatile_t<T>;
        return static_cast<T*>(__builtin_assume_aligned(const_cast<ValueType*>(pointer), Alignment));
#endif
    }
    return pointer;
}

template <size_t Alignment, class T>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API bool is_sufficiently_aligned(T* pointer) noexcept
{
    static_assert(__is_valid_alignment<T>(Alignment), "invalid alignment for T");
    return (reinterpret_cast<uintptr_t>(pointer) & static_cast<uintptr_t>(Alignment - 1)) == 0;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MEMORY_ASSUME_ALIGNED_H
