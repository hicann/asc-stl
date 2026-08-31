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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_EXTENT_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_EXTENT_H

#include <asc/std/detail/__config>

#include <asc/std/__cstddef/types.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
struct remove_extent {
    using type = _Tp;
};
template <class _Tp>
struct remove_extent<_Tp[]> {
    using type = _Tp;
};
template <class _Tp, size_t _Np>
struct remove_extent<_Tp[_Np]> {
    using type = _Tp;
};

template <class _Tp>
using remove_extent_t = typename remove_extent<_Tp>::type;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_EXTENT_H
