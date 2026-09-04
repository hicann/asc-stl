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

#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_TYPES_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_TYPES_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__cstddef/types.h>
#include <asc/std/__tuple_dir/tuple_element.h>
#include <asc/std/__tuple_dir/tuple_size.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/type_list.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class... _Tp>
struct __tuple_types {};

template <class... _Tp>
struct tuple_size<__tuple_types<_Tp...>> : integral_constant<size_t, sizeof...(_Tp)> {};

template <size_t _Ip, class... _Types>
struct tuple_element<_Ip, __tuple_types<_Types...>>
    : enable_if<(_Ip < sizeof...(_Types)), __type_index_c<_Ip, _Types...>> {};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_TYPES_H
