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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REFERENCE_CONVERTS_FROM_TEMPORARY_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REFERENCE_CONVERTS_FROM_TEMPORARY_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/always_false.h>
#include <asc/std/__type_traits/integral_constant.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if defined(CANN_ASC_STL_DETAIL_BUILTIN_REFERENCE_CONVERTS_FROM_TEMPORARY)
template <class _Tp, class _Up>
struct reference_converts_from_temporary
    : integral_constant<bool, CANN_ASC_STL_DETAIL_BUILTIN_REFERENCE_CONVERTS_FROM_TEMPORARY(_Tp, _Up)> {};

template <class _Tp, class _Up>
inline constexpr bool reference_converts_from_temporary_v =
    CANN_ASC_STL_DETAIL_BUILTIN_REFERENCE_CONVERTS_FROM_TEMPORARY(_Tp, _Up);

#else

template <class _Tp, class _Up>
struct reference_converts_from_temporary : integral_constant<bool, false> {
    static_assert(__always_false_v<_Tp>, "The compiler does not support __reference_converts_from_temporary");
};

template <class _Tp, class _Up>
inline constexpr bool reference_converts_from_temporary_v = reference_converts_from_temporary<_Tp, _Up>::value;

#endif  // !CANN_ASC_STL_DETAIL_BUILTIN_REFERENCE_CONVERTS_FROM_TEMPORARY

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REFERENCE_CONVERTS_FROM_TEMPORARY_H
