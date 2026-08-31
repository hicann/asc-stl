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

#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_ELEMENT_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_ELEMENT_H

#include <asc/std/detail/__config>

#include <asc/std/__cstddef/types.h>

// asc::std::tuple_element

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <size_t _Ip, class _Tp>
struct tuple_element;

template <size_t _Ip, class _Tp>
using tuple_element_t = typename tuple_element<_Ip, _Tp>::type;

template <size_t _Ip, class _Tp>
struct tuple_element<_Ip, const _Tp> {
    using type = const tuple_element_t<_Ip, _Tp>;
};

template <size_t _Ip, class _Tp>
struct tuple_element<_Ip, volatile _Tp> {
    using type = volatile tuple_element_t<_Ip, _Tp>;
};

template <size_t _Ip, class _Tp>
struct tuple_element<_Ip, const volatile _Tp> {
    using type = const volatile tuple_element_t<_Ip, _Tp>;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

// std::tuple_element

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_STD

template <size_t _Ip, class _Tp>
struct tuple_element;

#if CANN_ASC_STL_DETAIL_FREESTANDING() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
template <size_t _Ip, class _Tp>
struct tuple_element<_Ip, const _Tp> {
    using type = const typename tuple_element<_Ip, _Tp>::type;
};

template <size_t _Ip, class _Tp>
struct tuple_element<_Ip, volatile _Tp> {
    using type = volatile typename tuple_element<_Ip, _Tp>::type;
};

template <size_t _Ip, class _Tp>
struct tuple_element<_Ip, const volatile _Tp> {
    using type = const volatile typename tuple_element<_Ip, _Tp>::type;
};
#endif  // CANN_ASC_STL_DETAIL_FREESTANDING() && !CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_ELEMENT_H
