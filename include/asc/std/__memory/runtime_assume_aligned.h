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

#ifndef CANN_ASC_STL_STD_DETAIL_MEMORY_RUNTIME_ASSUME_ALIGNED_H
#define CANN_ASC_STL_STD_DETAIL_MEMORY_RUNTIME_ASSUME_ALIGNED_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__cstddef/types.h>
#include <asc/std/__type_traits/remove_volatile.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <typename _Tp>
[[nodiscard]] CANN_ASC_STL_API _Tp* __runtime_assume_aligned(_Tp* __ptr, ::asc::std::size_t __alignment) noexcept
{
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_assume_aligned) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
    using _Up = remove_volatile_t<_Tp>;
    if (__alignment == 1) {
        return static_cast<_Tp*>(__builtin_assume_aligned(const_cast<_Up*>(__ptr), 1));
    } else if (__alignment == 2) {
        return static_cast<_Tp*>(__builtin_assume_aligned(const_cast<_Up*>(__ptr), 2));
    } else if (__alignment == 4) {
        return static_cast<_Tp*>(__builtin_assume_aligned(const_cast<_Up*>(__ptr), 4));
    } else if (__alignment == 8) {
        return static_cast<_Tp*>(__builtin_assume_aligned(const_cast<_Up*>(__ptr), 8));
    } else if (__alignment == 16) {
        return static_cast<_Tp*>(__builtin_assume_aligned(const_cast<_Up*>(__ptr), 16));
    } else {
        return static_cast<_Tp*>(__builtin_assume_aligned(const_cast<_Up*>(__ptr), 32));
    }
#else
    CANN_ASC_STL_DETAIL_ASSUME(reinterpret_cast<__UINTPTR_TYPE__>(__ptr) % __alignment == 0);
    return __ptr;
#endif  // CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_assume_aligned) || CANN_ASC_STL_DETAIL_COMPILER(GCC)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_MEMORY_RUNTIME_ASSUME_ALIGNED_H
