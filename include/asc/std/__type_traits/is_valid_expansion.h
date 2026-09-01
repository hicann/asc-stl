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

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/integral_constant.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class...>
using __expansion_void_t = void;
template <template <class...> class Template, class, class... Arguments>
struct __is_valid_expansion_impl : false_type {};
template <template <class...> class Template, class... Arguments>
struct __is_valid_expansion_impl<Template, __expansion_void_t<Template<Arguments...>>, Arguments...> : true_type {};
template <template <class...> class Template, class... Arguments>
using _IsValidExpansion = __is_valid_expansion_impl<Template, void, Arguments...>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_VALID_EXPANSION_H
