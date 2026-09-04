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

#ifndef CANN_ASC_STL_STD_DETAIL_MEMORY_ALLOCATOR_ARG_T_H
#define CANN_ASC_STL_STD_DETAIL_MEMORY_ALLOCATOR_ARG_T_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__memory/uses_allocator.h>
#include <asc/std/__new/device_new.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

struct allocator_arg_t {
    CANN_ASC_STL_API explicit allocator_arg_t() = default;
};

inline constexpr allocator_arg_t allocator_arg = allocator_arg_t();

template <class _Tp, class _Alloc, class... _Args>
struct __uses_alloc_ctor_imp {
    using _RawAlloc = remove_cvref_t<_Alloc>;
    static const bool __ua = uses_allocator<_Tp, _RawAlloc>::value;
    static const bool __ic = is_constructible_v<_Tp, allocator_arg_t, _Alloc, _Args...>;
    static const int value = __ua ? 2 - __ic : 0;
};

template <class _Tp, class _Alloc, class... _Args>
struct __uses_alloc_ctor : integral_constant<int, __uses_alloc_ctor_imp<_Tp, _Alloc, _Args...>::value> {};

template <class _Tp, class _Allocator, class... _Args>
CANN_ASC_STL_API void __user_alloc_construct_impl(
    integral_constant<int, 0>, _Tp* __storage, const _Allocator&, _Args&&... __args)
{
    new (__storage) _Tp(::asc::std::forward<_Args>(__args)...);
}

template <class _Tp, class _Allocator, class... _Args>
CANN_ASC_STL_API void __user_alloc_construct_impl(
    integral_constant<int, 1>, _Tp* __storage, const _Allocator& __a, _Args&&... __args)
{
    new (__storage) _Tp(allocator_arg, __a, ::asc::std::forward<_Args>(__args)...);
}

template <class _Tp, class _Allocator, class... _Args>
CANN_ASC_STL_API void __user_alloc_construct_impl(
    integral_constant<int, 2>, _Tp* __storage, const _Allocator& __a, _Args&&... __args)
{
    new (__storage) _Tp(::asc::std::forward<_Args>(__args)..., __a);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_MEMORY_ALLOCATOR_ARG_T_H
