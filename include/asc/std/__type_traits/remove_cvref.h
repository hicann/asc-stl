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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_CVREF_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_CVREF_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_reference.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
using remove_cvref_t = remove_cv_t<remove_reference_t<_Tp>>;

template <class _Tp, class _Up>
struct __is_same_uncvref : _IsSame<remove_cvref_t<_Tp>, remove_cvref_t<_Up>> {};

template <class _Tp>
struct remove_cvref {
    using type = remove_cvref_t<_Tp>;
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_REMOVE_CVREF_H
