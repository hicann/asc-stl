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

#ifndef CANN_ASC_STL_STD_DETAIL_FWD_SPAN_H
#define CANN_ASC_STL_STD_DETAIL_FWD_SPAN_H

#include <asc/std/detail/__config>

#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

inline constexpr size_t dynamic_extent = static_cast<size_t>(-1);

template <typename _Tp, size_t _Extent = dynamic_extent>
class span;

template <class _Tp>
inline constexpr bool __is_asc_std_span_v = false;

template <class _Tp, size_t _Extent>
inline constexpr bool __is_asc_std_span_v<span<_Tp, _Extent>> = true;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FWD_SPAN_H
