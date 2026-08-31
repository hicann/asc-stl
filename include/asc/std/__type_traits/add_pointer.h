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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_ADD_POINTER_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_ADD_POINTER_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/is_referenceable.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__type_traits/remove_reference.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp, bool = __asc_is_referenceable<_Tp>::value || is_void<_Tp>::value>
struct __add_pointer_impl {
    using type = remove_reference_t<_Tp>*;
};

template <class _Tp>
struct __add_pointer_impl<_Tp, false> {
    using type = _Tp;
};

template <class _Tp>
using add_pointer_t = typename __add_pointer_impl<_Tp>::type;

template <class _Tp>
struct add_pointer {
    using type = add_pointer_t<_Tp>;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_ADD_POINTER_H
