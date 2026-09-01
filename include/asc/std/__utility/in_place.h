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

#ifndef CANN_ASC_STL_STD_DETAIL_UTILITY_IN_PLACE_H
#define CANN_ASC_STL_STD_DETAIL_UTILITY_IN_PLACE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

struct in_place_t {
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI explicit in_place_t() = default;
};
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT in_place_t in_place{};

template <class _Tp>
struct in_place_type_t {
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI explicit in_place_type_t() = default;
};
template <class _Tp>
inline constexpr in_place_type_t<_Tp> in_place_type{};

template <size_t _Idx>
struct in_place_index_t {
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI explicit in_place_index_t() = default;
};
template <size_t _Idx>
inline constexpr in_place_index_t<_Idx> in_place_index{};

template <class _Tp>
inline constexpr bool __is_asc_std_inplace_type_v = false;
template <class _Tp>
inline constexpr bool __is_asc_std_inplace_type_v<in_place_type_t<_Tp>> = true;

template <class _Tp>
inline constexpr bool __is_asc_std_inplace_index_v = false;
template <size_t _Idx>
inline constexpr bool __is_asc_std_inplace_index_v<in_place_index_t<_Idx>> = true;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

// ASC-STL extension: construct an object from a callable/factory result.
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC

struct in_place_from_t {
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI explicit in_place_from_t() = default;
};
CANN_ASC_STL_DETAIL_GLOBAL_CONSTANT in_place_from_t in_place_from{};

template <class _Tp>
struct in_place_from_type_t {
    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI explicit in_place_from_type_t() = default;
};
template <class _Tp>
inline constexpr in_place_from_type_t<_Tp> in_place_from_type{};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC

#endif  // CANN_ASC_STL_STD_DETAIL_UTILITY_IN_PLACE_H
