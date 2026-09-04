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

#ifndef CANN_ASC_STL_STD_DETAIL_MEMORY_USES_ALLOCATOR_H
#define CANN_ASC_STL_STD_DETAIL_MEMORY_USES_ALLOCATOR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__fwd/tuple.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp, class = void>
inline constexpr bool __has_allocator_type_v = false;
template <class _Tp>
inline constexpr bool __has_allocator_type_v<_Tp, void_t<typename _Tp::allocator_type>> = true;

template <class _Tp, class _Alloc, bool = __has_allocator_type_v<_Tp>>
inline constexpr bool __uses_allocator_v = false;
template <class _Tp, class _Alloc>
inline constexpr bool __uses_allocator_v<_Tp, _Alloc, true> = is_convertible_v<_Alloc, typename _Tp::allocator_type>;

template <class _Tp, class _Alloc>
struct uses_allocator : public integral_constant<bool, __uses_allocator_v<_Tp, _Alloc>> {};

template <class _Tp, class _Alloc>
inline constexpr bool uses_allocator_v = __uses_allocator_v<_Tp, _Alloc>;

template <class... _Tp, class _Alloc>
struct uses_allocator<tuple<_Tp...>, _Alloc> : true_type {};

template <class... _Tp, class _Alloc>
inline constexpr bool uses_allocator_v<tuple<_Tp...>, _Alloc> = true;  // NOLINT(build/include_what_you_use)

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_MEMORY_USES_ALLOCATOR_H
