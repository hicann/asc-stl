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
#ifndef CANN_ASC_STL_ASC_STDDETAIL__UTILITY_SWAP_H
#define CANN_ASC_STL_ASC_STDDETAIL__UTILITY_SWAP_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_move_constructible.h>
#include <asc/std/__type_traits/is_nothrow_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__utility/move.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T>
CANN_ASC_STL_API constexpr __swap_result_t<T> swap(T& left, type_identity_t<T>& right) noexcept(
    is_nothrow_move_constructible_v<T> && is_nothrow_move_assignable_v<T>)
{
    T temporary(::asc::std::move(left));
    left = ::asc::std::move(right);
    right = ::asc::std::move(temporary);
}
template <class T, size_t N>
CANN_ASC_STL_API constexpr enable_if_t<__is_swappable<T>::value> swap(T (&left)[N], T (&right)[N]) noexcept(
    __is_nothrow_swappable<T>::value)
{
    for (size_t index = 0; index != N; ++index) {
        swap(left[index], right[index]);  // NOLINT(build/include_what_you_use)
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STDDETAIL__UTILITY_SWAP_H
