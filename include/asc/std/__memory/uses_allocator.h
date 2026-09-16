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

#ifndef CANN_ASC_STL_ASC_STD___MEMORY_USES_ALLOCATOR_H
#define CANN_ASC_STL_ASC_STD___MEMORY_USES_ALLOCATOR_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__fwd/tuple.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T, class = void>
inline constexpr bool __has_allocator_type_v = false;
template <class T>
inline constexpr bool __has_allocator_type_v<T, void_t<typename T::allocator_type>> = true;
template <class T, class Alloc, bool = __has_allocator_type_v<T>>
inline constexpr bool __uses_allocator_v = false;
template <class T, class Alloc>
inline constexpr bool __uses_allocator_v<T, Alloc, true> = is_convertible_v<Alloc, typename T::allocator_type>;
template <class T, class Alloc>
struct uses_allocator : integral_constant<bool, __uses_allocator_v<T, Alloc>> {};
template <class T, class Alloc>
inline constexpr bool uses_allocator_v = uses_allocator<T, Alloc>::value;
template <class... T, class Alloc>
struct uses_allocator<tuple<T...>, Alloc> : true_type {};  // NOLINT(build/include_what_you_use)

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MEMORY_USES_ALLOCATOR_H
