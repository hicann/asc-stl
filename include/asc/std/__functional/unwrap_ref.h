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

#ifndef CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_UNWRAP_REF_H
#define CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_UNWRAP_REF_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__fwd/reference_wrapper.h>
#include <asc/std/__type_traits/decay.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _Tp>
struct unwrap_reference {
    using type = _Tp;
};

template <class _Tp>
struct unwrap_reference<reference_wrapper<_Tp>> {
    using type = _Tp&;
};

template <class _Tp>
using unwrap_reference_t = typename unwrap_reference<_Tp>::type;

template <class _Tp>
struct unwrap_ref_decay : unwrap_reference<decay_t<_Tp>> {};

template <class _Tp>
using unwrap_ref_decay_t = typename unwrap_ref_decay<_Tp>::type;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FUNCTIONAL_UNWRAP_REF_H
