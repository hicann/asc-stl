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

#ifndef CANN_ASC_STL_ASC_STD___NEW_NONALLOCATING_NEW_H
#define CANN_ASC_STL_ASC_STD___NEW_NONALLOCATING_NEW_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#if !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
#include <new>
#endif

#ifndef CANN_ASC_STL_DETAIL_PLACEMENT_NEW_DECLARED
#define CANN_ASC_STL_DETAIL_PLACEMENT_NEW_DECLARED
#if CANN_ASC_STL_DETAIL_SIMD_COMPILATION()
CANN_ASC_STL_DEVICE_API void* operator new(__SIZE_TYPE__, void* address) noexcept
{
    return address;
}
#elif CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
void* operator new(__SIZE_TYPE__, void* address) noexcept;
#endif
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

enum class align_val_t : __SIZE_TYPE__ {};
// The tag vocabulary is portable; compiler destroying-delete semantics remain
// a separate language capability and are not provided by declaring this type.
struct destroying_delete_t {
    explicit destroying_delete_t() = default;
};
inline constexpr destroying_delete_t destroying_delete{};
struct nothrow_t {
    explicit nothrow_t() = default;
};
inline constexpr nothrow_t nothrow{};

template <class T>
CANN_ASC_STL_API constexpr T* launder(T* pointer) noexcept
{
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_launder) || defined(__GNUC__)
    return __builtin_launder(pointer);
#else
    return pointer;
#endif
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___NEW_NONALLOCATING_NEW_H
