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

#ifndef CANN_ASC_STL_STD_DETAIL_FWD_ARRAY_H
#define CANN_ASC_STL_STD_DETAIL_FWD_ARRAY_H

#include <asc/std/detail/__config>

#include <asc/std/cstddef>

// std:: forward declarations

#if CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_STD

#if CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL)
template <class _Tp, size_t _Size>
class array;
#else   // ^^^ CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL) ^^^ / vvv !CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL) vvv
template <class _Tp, size_t _Size>
struct array;
#endif  // !CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL)

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_STD
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()

// asc::std:: forward declaration

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp, size_t _Size>
struct array;

template <class _Tp>
inline constexpr bool __is_asc_std_array_v = false;

template <class _Tp, size_t _Sz>
inline constexpr bool __is_asc_std_array_v<array<_Tp, _Sz>> = true;

#if CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()
template <class _Tp>
inline constexpr bool __is_std_array_v = false;

template <class _Tp, size_t _Sz>
inline constexpr bool __is_std_array_v<::std::array<_Tp, _Sz>> = true;
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FWD_ARRAY_H
