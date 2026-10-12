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

#ifndef CANN_ASC_STL_ASC_STD___MEMORY_RUNTIME_ASSUME_ALIGNED_H
#define CANN_ASC_STL_ASC_STD___MEMORY_RUNTIME_ASSUME_ALIGNED_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__type_traits/remove_volatile.h>
#include <asc/std/cstdint>

// 基座 __config 未提供 dev 的 CANN_ASC_STL_DETAIL_ASSUME（dev 定义于
// asc/std/__asc/attributes.h）：内联其语义的最小等价，#ifndef 守卫防重。
#ifndef CANN_ASC_STL_DETAIL_ASSUME
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_assume)
#define CANN_ASC_STL_DETAIL_ASSUME(...) __builtin_assume(__VA_ARGS__)
#else
#define CANN_ASC_STL_DETAIL_ASSUME(...) ((void)sizeof(!(__VA_ARGS__)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSUME

CANN_ASC_STL_BEGIN_NAMESPACE

template <typename _Tp>
[[nodiscard]] CANN_ASC_STL_API _Tp* __runtime_assume_aligned(_Tp* __ptr, ::asc::std::size_t __alignment) noexcept
{
#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_assume_aligned) || CANN_ASC_STL_DETAIL_COMPILER_GCC
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
    // 无 builtin 时仍保留对齐假设（优化提示不丢），而非透传丢弃。
    CANN_ASC_STL_DETAIL_ASSUME(reinterpret_cast< ::asc::std::uintptr_t>(__ptr) % __alignment == 0);
    return __ptr;
#endif  // CANN_ASC_STL_DETAIL_HAS_BUILTIN(__builtin_assume_aligned) || CANN_ASC_STL_DETAIL_COMPILER_GCC
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MEMORY_RUNTIME_ASSUME_ALIGNED_H
