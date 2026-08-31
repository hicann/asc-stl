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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_VALID_EXPANSION_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_VALID_EXPANSION_H

#include <asc/std/detail/__config>

#include <asc/std/__type_traits/integral_constant.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <template <class...> class _Templ, class... _Args, class = _Templ<_Args...>>
CANN_ASC_STL_API true_type __sfinae_test_impl(int);
template <template <class...> class, class...>
CANN_ASC_STL_API false_type __sfinae_test_impl(long);

template <template <class...> class _Templ, class... _Args>
using _IsValidExpansion = decltype(asc::std::__sfinae_test_impl<_Templ, _Args...>(0));

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_VALID_EXPANSION_H
