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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_EXTENT_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_EXTENT_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_CHECK_BUILTIN(array_extent)

template <class _Tp, size_t _Ip = 0>
struct extent : integral_constant<size_t, __array_extent(_Tp, _Ip)> {};

template <class _Tp, unsigned _Ip = 0>
inline constexpr size_t extent_v = __array_extent(_Tp, _Ip);

#else  // ^^^ CANN_ASC_STL_DETAIL_CHECK_BUILTIN(array_extent) ^^^ / vvv !CANN_ASC_STL_DETAIL_CHECK_BUILTIN(array_extent)
       // vvv

template <class _Tp, unsigned _Ip = 0>
inline constexpr size_t extent_v = 0;
template <class _Tp>
inline constexpr size_t extent_v<_Tp[], 0> = 0;
template <class _Tp, unsigned _Ip>
inline constexpr size_t extent_v<_Tp[], _Ip> = extent_v<_Tp, _Ip - 1>;
template <class _Tp, size_t _Np>
inline constexpr size_t extent_v<_Tp[_Np], 0> = _Np;
template <class _Tp, size_t _Np, unsigned _Ip>
inline constexpr size_t extent_v<_Tp[_Np], _Ip> = extent_v<_Tp, _Ip - 1>;

template <class _Tp, unsigned _Ip = 0>
struct extent : integral_constant<size_t, extent_v<_Tp, _Ip> > {};

#endif  // !CANN_ASC_STL_DETAIL_CHECK_BUILTIN(array_extent)

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_EXTENT_H
