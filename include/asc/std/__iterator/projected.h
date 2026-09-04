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

#ifndef CANN_ASC_STL_STD_DETAIL_ITERATOR_PROJECTED_H
#define CANN_ASC_STL_STD_DETAIL_ITERATOR_PROJECTED_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__iterator/concepts.h>
#include <asc/std/__iterator/incrementable_traits.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/remove_cvref.h>
CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _It, class _Proj, class = void>
struct __projected_impl {
    struct __type {
        using value_type = remove_cvref_t<indirect_result_t<_Proj, _It>>;
        CANN_ASC_STL_API indirect_result_t<_Proj, _It> operator*() const;  // not defined
    };
};

template <class _It, class _Proj>
struct __projected_impl<_It, _Proj, enable_if_t<weakly_incrementable<_It>>> {
    struct __type {
        using value_type = remove_cvref_t<indirect_result_t<_Proj, _It>>;
        using difference_type = iter_difference_t<_It>;
        CANN_ASC_STL_API indirect_result_t<_Proj, _It> operator*() const;  // not defined
    };
};

CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _It, class _Proj)
CANN_ASC_STL_DETAIL_ACCL_REQUIRES(
    indirectly_readable<_It> CANN_ASC_STL_DETAIL_ACCL_AND indirectly_regular_unary_invocable<_Proj, _It>)
using projected = typename __projected_impl<_It, _Proj>::__type;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD
#endif  // CANN_ASC_STL_STD_DETAIL_ITERATOR_PROJECTED_H
