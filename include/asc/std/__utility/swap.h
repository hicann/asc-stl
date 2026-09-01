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

#ifndef CANN_ASC_STL_STD_DETAIL_UTILITY_SWAP_H
#define CANN_ASC_STL_STD_DETAIL_UTILITY_SWAP_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
CANN_ASC_STL_API constexpr __swap_result_t<_Tp> swap(_Tp& __lhs, type_identity_t<_Tp>& __rhs) noexcept(
    is_nothrow_move_constructible_v<_Tp> && is_nothrow_move_assignable_v<_Tp>)
{
    _Tp __temporary(::asc::std::move(__lhs));
    __lhs = ::asc::std::move(__rhs);
    __rhs = ::asc::std::move(__temporary);
}

template <class _Tp, size_t _Size>
CANN_ASC_STL_API constexpr enable_if_t<__detect_adl_swap::__has_no_adl_swap_array<_Tp, _Size>::value &&
    __is_swappable<_Tp>::value>
swap(_Tp (&__lhs)[_Size], _Tp (&__rhs)[_Size]) noexcept(__is_nothrow_swappable<_Tp>::value)
{
    for (size_t __index = 0; __index != _Size; ++__index) {
        swap(__lhs[__index], __rhs[__index]);  // NOLINT(build/include_what_you_use)
    }
}

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_UTILITY_SWAP_H
