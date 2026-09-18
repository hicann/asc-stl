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

#ifndef CANN_ASC_STL_STD_DETAIL_FWD_SUBRANGE_H
#define CANN_ASC_STL_STD_DETAIL_FWD_SUBRANGE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__iterator/concepts.h>
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

enum class subrange_kind : bool { unsized, sized };

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <input_or_output_iterator _Iter, sentinel_for<_Iter> _Sent = _Iter,
    subrange_kind _Kind = sized_sentinel_for<_Sent, _Iter> ? subrange_kind::sized : subrange_kind::unsized>
    requires(_Kind == subrange_kind::sized || !sized_sentinel_for<_Sent, _Iter>)
class subrange;
#else   // ^^^ C++20 ^^^ / vvv C++17 vvv
template <class _Iter, class _Sent = _Iter,
    subrange_kind _Kind = sized_sentinel_for<_Sent, _Iter> ? subrange_kind::sized : subrange_kind::unsized,
    enable_if_t<input_or_output_iterator<_Iter>, int> = 0, enable_if_t<sentinel_for<_Sent, _Iter>, int> = 0,
    enable_if_t<(_Kind == subrange_kind::sized || !sized_sentinel_for<_Sent, _Iter>), int> = 0>
class subrange;
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class>
inline constexpr bool __is_asc_std_ranges_subrange_v = false;

template <class _Iter, class _Sent, ::asc::std::ranges::subrange_kind _Kind>
inline constexpr bool __is_asc_std_ranges_subrange_v<::asc::std::ranges::subrange<_Iter, _Sent, _Kind>> = true;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD
#endif  // CANN_ASC_STL_STD_DETAIL_FWD_SUBRANGE_H
