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

#ifndef CANN_ASC_STL_STD_DETAIL_FWD_GET_H
#define CANN_ASC_STL_STD_DETAIL_FWD_GET_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/copyable.h>
#include <asc/std/__fwd/array.h>
#include <asc/std/__fwd/complex.h>
#include <asc/std/__fwd/pair.h>
#include <asc/std/__fwd/subrange.h>
#include <asc/std/__fwd/tuple.h>
#include <asc/std/__tuple_dir/tuple_element.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/cstddef>
CANN_ASC_STL_BEGIN_NAMESPACE

// tuple get() overloads are defined in tuple.h, not forward-declared here

template <size_t _Ip, class _T1, class _T2>
[[nodiscard]] CANN_ASC_STL_API constexpr tuple_element_t<_Ip, pair<_T1, _T2>>& get(pair<_T1, _T2>&) noexcept;

template <size_t _Ip, class _T1, class _T2>
[[nodiscard]] CANN_ASC_STL_API constexpr const tuple_element_t<_Ip, pair<_T1, _T2>>& get(
    const pair<_T1, _T2>&) noexcept;

template <size_t _Ip, class _T1, class _T2>
[[nodiscard]] CANN_ASC_STL_API constexpr tuple_element_t<_Ip, pair<_T1, _T2>>&& get(pair<_T1, _T2>&&) noexcept;

template <size_t _Ip, class _T1, class _T2>
[[nodiscard]] CANN_ASC_STL_API constexpr const tuple_element_t<_Ip, pair<_T1, _T2>>&& get(
    const pair<_T1, _T2>&&) noexcept;

template <size_t _Ip, class _Tp, size_t _Size>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp& get(array<_Tp, _Size>&) noexcept;

template <size_t _Ip, class _Tp, size_t _Size>
[[nodiscard]] CANN_ASC_STL_API constexpr const _Tp& get(const array<_Tp, _Size>&) noexcept;

template <size_t _Ip, class _Tp, size_t _Size>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp&& get(array<_Tp, _Size>&&) noexcept;

template <size_t _Ip, class _Tp, size_t _Size>
[[nodiscard]] CANN_ASC_STL_API constexpr const _Tp&& get(const array<_Tp, _Size>&&) noexcept;

template <size_t _Ip, class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp& get(complex<_Tp>&) noexcept;

template <size_t _Ip, class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr _Tp&& get(complex<_Tp>&&) noexcept;

template <size_t _Ip, class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr const _Tp& get(const complex<_Tp>&) noexcept;

template <size_t _Ip, class _Tp>
[[nodiscard]] CANN_ASC_STL_API constexpr const _Tp&& get(const complex<_Tp>&&) noexcept;

CANN_ASC_STL_END_NAMESPACE

#if 0  // subrange is a later-wave migration; get() for subrange is deferred
namespace asc { namespace std { namespace ranges {

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <size_t _Index, class _Iter, class _Sent, subrange_kind _Kind>
  requires((_Index == 0) && copyable<_Iter>) || (_Index == 1)
#else   // ^^^ C++20 ^^^ / vvv C++17 vvv
template <size_t _Index,
          class _Iter,
          class _Sent,
          subrange_kind _Kind,
          enable_if_t<((_Index == 0) && copyable<_Iter>) || (_Index == 1), int> = 0>
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^
CANN_ASC_STL_API constexpr auto get(const subrange<_Iter, _Sent, _Kind>& __subrange);

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <size_t _Index, class _Iter, class _Sent, subrange_kind _Kind>
  requires(_Index < 2)
#else   // ^^^ C++20 ^^^ / vvv C++17 vvv
template <size_t _Index,
          class _Iter,
          class _Sent,
          subrange_kind _Kind,
          enable_if_t<_Index<2, int> = 0>
#endif  // ^^^ !CANN_ASC_STL_DETAIL_HAS_CONCEPTS() ^^^
CANN_ASC_STL_API constexpr auto get(subrange<_Iter, _Sent, _Kind>&& __subrange);

} } }  // NOLINT(readability/namespace)
#endif

CANN_ASC_STL_BEGIN_NAMESPACE

#if 0  // ranges::get deferred with subrange
using ::asc::std::ranges::get;
#endif

// Explicitly rely on ADL, mostly for constructors of host STL types, where we cannot squeze using ::asc::std::get; in
template <size_t _Ip, class _TupleLike>
[[nodiscard]] CANN_ASC_STL_API constexpr decltype(auto) __adl_get(_TupleLike&& __t) noexcept
{
    using ::asc::std::get;
    return get<_Ip>(::asc::std::forward<_TupleLike>(__t));  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE
#endif  // CANN_ASC_STL_STD_DETAIL_FWD_GET_H
