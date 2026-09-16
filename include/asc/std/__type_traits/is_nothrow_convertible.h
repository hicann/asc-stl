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
#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/conjunction.h>
#include <asc/std/__type_traits/disjunction.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_void.h>
#include <asc/std/__type_traits/lazy.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <typename Tp>
CANN_ASC_STL_API void __test_noexcept(Tp) noexcept;

template <typename Fm, typename To>
CANN_ASC_STL_API bool_constant<noexcept(asc::std::__test_noexcept<To>(asc::std::declval<Fm>()))>
__is_nothrow_convertible_test();

template <typename Fm, typename To>
struct __is_nothrow_convertible_helper : decltype(__is_nothrow_convertible_test<Fm, To>()) {};

template <typename Fm, typename To>
struct is_nothrow_convertible
    : _Or<_And<is_void<To>, is_void<Fm>>,
          _Lazy<_And, is_convertible<Fm, To>, __is_nothrow_convertible_helper<Fm, To>>>::type {};

template <typename Fm, typename To>
inline constexpr bool is_nothrow_convertible_v = is_nothrow_convertible<Fm, To>::value;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_NOTHROW_CONVERTIBLE_H
