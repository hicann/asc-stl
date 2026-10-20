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

#ifndef CANN_ASC_STL_ASC_STD___FWD_SUBRANGE_H
#define CANN_ASC_STL_ASC_STD___FWD_SUBRANGE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__iterator/concepts.h>

namespace asc::std::ranges {

enum class subrange_kind : bool { unsized, sized };

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <input_or_output_iterator Iter, sentinel_for<Iter> Sent = Iter,
    subrange_kind Kind = sized_sentinel_for<Sent, Iter> ? subrange_kind::sized : subrange_kind::unsized>
    requires(Kind == subrange_kind::sized || !sized_sentinel_for<Sent, Iter>)
class subrange;
#else
template <class Iter, class Sent = Iter,
    subrange_kind Kind = sized_sentinel_for<Sent, Iter> ? subrange_kind::sized : subrange_kind::unsized>
class subrange;
#endif

}  // namespace asc::std::ranges

CANN_ASC_STL_BEGIN_NAMESPACE

template <class>
inline constexpr bool __is_asc_std_ranges_subrange_v = false;

template <class Iter, class Sent, ranges::subrange_kind Kind>
inline constexpr bool __is_asc_std_ranges_subrange_v<ranges::subrange<Iter, Sent, Kind>> = true;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FWD_SUBRANGE_H
