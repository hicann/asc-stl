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

#ifndef CANN_ASC_STL_STD_DETAIL_BIT_HAS_SINGLE_BIT_H
#define CANN_ASC_STL_STD_DETAIL_BIT_HAS_SINGLE_BIT_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__bit/popcount.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_unsigned_integer.h>

CANN_ASC_STL_BEGIN_NAMESPACE

// Mandated to participate only for unsigned integer types (the constraint is
// expressed with the enable_if_t idiom rather than a requires-clause).
template <class _Tp, enable_if_t<__is_unsigned_integer_v<_Tp>, int> = 0>
CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr bool has_single_bit(_Tp __t) noexcept
{
    return ::asc::std::popcount(__t) == 1;
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_BIT_HAS_SINGLE_BIT_H
