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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_PRIMARY_TEMPLATE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_PRIMARY_TEMPLATE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__fwd/iterator.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_base_of.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_valid_expansion.h>
#include <asc/std/__type_traits/void_t.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Traits>
using __test_for_primary_template = enable_if_t<_IsSame<Traits, typename Traits::__asc_primary_template>::value>;

template <class T>
using __is_primary_asc_template = _IsValidExpansion<__test_for_primary_template, iterator_traits<T>>;

// ASC-STL carries no host ::std::iterator_traits interop contract, so every
// iterator_traits instance is the primary standard template.
template <class T>
struct __is_primary_std_template : true_type {};

template <class T, class OtherTraits>
using __select_traits = conditional_t<__is_primary_asc_template<T>::value, OtherTraits, iterator_traits<T>>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_PRIMARY_TEMPLATE_H
