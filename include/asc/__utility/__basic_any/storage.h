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

#ifndef CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_STORAGE_H
#define CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_STORAGE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/__utility/__basic_any/basic_any_fwd.h>
#include <asc/std/__algorithm/max.h>
#include <asc/std/__tuple_dir/ignore.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/type_identity.h>
#include <asc/std/__utility/swap.h>
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr auto __buffer_size(size_t __size) -> size_t
{
    //! round up to the nearest multiple of `__word`, which is the size of a
    //! void*.
    return ((__size ? (::asc::std::max)(__size, sizeof(void*)) : __default_small_object_size) + __word - 1) / __word *
        __word;
}

[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr auto __buffer_align(size_t __align) -> size_t
{
    //! need to be able to store a void* in the buffer.
    return __align ? (::asc::std::max)(__align, alignof(void*)) : __default_small_object_align;
}

template <class _Tp, bool _RequiresMovable = true>
[[nodiscard]] CANN_ASC_STL_DETAIL_HOST_DEVICE_API constexpr auto __is_small(
    size_t __size, size_t __align) noexcept -> bool
{
    return (sizeof(_Tp) <= __size) && (__align % alignof(_Tp) == 0) &&
        (!_RequiresMovable || ::asc::std::is_nothrow_move_constructible_v<_Tp>);
}

CANN_ASC_STL_DETAIL_HOST_DEVICE_API void __swap_ptr_ptr(void* __lhs, void* __rhs) noexcept
{
    ::asc::std::swap(*static_cast<void**>(__lhs), *static_cast<void**>(__rhs));  // NOLINT(build/include_what_you_use)
}

template <class _Tp, class _Up,
    class _Vp = decltype(true ? ::asc::std::type_identity_t<_Tp*>() : ::asc::std::type_identity_t<_Up*>())>
[[nodiscard]] CANN_ASC_STL_DETAIL_NODEBUG_API auto __ptr_eq(_Tp* __lhs, _Up* __rhs) noexcept -> bool
{
    return static_cast<_Vp>(__lhs) == static_cast<_Vp>(__rhs);
}

[[nodiscard]]
CANN_ASC_STL_DETAIL_NODEBUG_API constexpr auto __ptr_eq(::asc::std::__ignore_t, ::asc::std::__ignore_t) noexcept -> bool
{
    return false;
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC
#endif  // CANN_ASC_STL_DETAIL_UTILITY_DETAIL_BASIC_ANY_STORAGE_H
