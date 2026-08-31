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

#ifndef CANN_ASC_STL_STD_DETAIL_FWD_EXTENTS_H
#define CANN_ASC_STL_STD_DETAIL_FWD_EXTENTS_H

#include <asc/std/detail/__config>

#include <asc/std/__cstddef/types.h>
#include <asc/std/__fwd/span.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _IndexType, size_t... _Extents>
class extents;

template <class _Tp>
inline constexpr bool __is_asc_std_extents_v = false;
template <class _IndexType, size_t... _Extents>
inline constexpr bool __is_asc_std_extents_v<extents<_IndexType, _Extents...>> = true;

// Recursive helper classes to implement dextents alias for extents
template <class _IndexType, size_t _Rank, class _Extents = extents<_IndexType>>
struct __make_dextents;

template <class _IndexType, size_t _Rank, class _Extents = extents<_IndexType>>
using __make_dextents_t = typename __make_dextents<_IndexType, _Rank, _Extents>::type;

template <class _IndexType, size_t _Rank, size_t... _ExtentsPack>
struct __make_dextents<_IndexType, _Rank, extents<_IndexType, _ExtentsPack...>> {
    using type = __make_dextents_t<_IndexType, _Rank - 1, extents<_IndexType, dynamic_extent, _ExtentsPack...>>;
};

template <class _IndexType, size_t... _ExtentsPack>
struct __make_dextents<_IndexType, 0, extents<_IndexType, _ExtentsPack...>> {
    using type = extents<_IndexType, _ExtentsPack...>;
};

// [mdspan.extents.dextents], alias template
template <class _IndexType, size_t _Rank>
using dextents = __make_dextents_t<_IndexType, _Rank>;

template <size_t _Rank, class _IndexType = size_t>
using dims = dextents<_IndexType, _Rank>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FWD_EXTENTS_H
