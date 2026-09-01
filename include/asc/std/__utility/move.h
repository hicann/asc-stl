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

#ifndef CANN_ASC_STL_STD_DETAIL_UTILITY_MOVE_H
#define CANN_ASC_STL_STD_DETAIL_UTILITY_MOVE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/remove_reference.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_DETAIL_INTRINSIC CANN_ASC_STL_API constexpr remove_reference_t<_Tp>&& move(
    _Tp&& __value) noexcept
{
    return static_cast<remove_reference_t<_Tp>&&>(__value);
}

template <class _Tp>
using __move_if_noexcept_result_t =
    conditional_t<!is_nothrow_move_constructible_v<_Tp> && is_copy_constructible_v<_Tp>, const _Tp&, _Tp&&>;

template <class _Tp>
[[nodiscard]] CANN_ASC_STL_DETAIL_INTRINSIC CANN_ASC_STL_API constexpr __move_if_noexcept_result_t<_Tp>
move_if_noexcept(_Tp& __value) noexcept
{
    return ::asc::std::move(__value);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_UTILITY_MOVE_H
