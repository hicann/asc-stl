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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_COPY_CV_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_COPY_CV_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/copy_cvref.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

// Let COPYCV(FROM, TO) be an alias for type TO with the addition of FROM's
// top-level cv-qualifiers.
template <class>
extern __apply_cvref_ __apply_cv;
template <class _Tp>
extern __apply_cvref_c __apply_cv<const _Tp>;
template <class _Tp>
extern __apply_cvref_v __apply_cv<volatile _Tp>;
template <class _Tp>
extern __apply_cvref_cv __apply_cv<const volatile _Tp>;

template <class _Tp>
using __apply_cv_fn = decltype(__apply_cv<_Tp>);

template <class _From, class _To>
using __copy_cv_t = typename __apply_cv_fn<_From>::template __call<_To>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_COPY_CV_H
