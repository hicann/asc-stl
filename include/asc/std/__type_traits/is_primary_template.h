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

#ifndef CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_PRIMARY_TEMPLATE_H
#define CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_PRIMARY_TEMPLATE_H

#include <asc/std/detail/__config>

#include <asc/std/__fwd/iterator.h>
#include <asc/std/__type_traits/conditional.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_base_of.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_valid_expansion.h>
#include <asc/std/__type_traits/void_t.h>

#if CANN_ASC_STL_DETAIL_HOSTED()
#include <iterator>
#endif  // CANN_ASC_STL_DETAIL_HOSTED()

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_COMPILER(MSVC)

template <class _Iter, class = void>
struct __is_primary_accl_template : false_type {};

template <class _Iter>
struct __is_primary_accl_template<_Iter, void_t<typename iterator_traits<_Iter>::__accl_primary_template>>
    : public is_same<iterator_traits<_Iter>, typename iterator_traits<_Iter>::__accl_primary_template> {};

#else  // ^^^ CANN_ASC_STL_DETAIL_COMPILER(MSVC) ^^^ / vvv !CANN_ASC_STL_DETAIL_COMPILER(MSVC) vvv

template <class _Traits>
using __test_for_primary_template = enable_if_t<_IsSame<_Traits, typename _Traits::__accl_primary_template>::value>;
template <class _Iter>
using __is_primary_accl_template = _IsValidExpansion<__test_for_primary_template, iterator_traits<_Iter>>;

#endif  // !CANN_ASC_STL_DETAIL_COMPILER(MSVC)

#if CANN_ASC_STL_DETAIL_FREESTANDING()

// No ::std::traits with freestanding implementations
template <class _Iter>
struct __is_primary_std_template : true_type {};

template <class _Iter, class _OtherTraits>
using __select_traits = conditional_t<__is_primary_accl_template<_Iter>::value, _OtherTraits, iterator_traits<_Iter>>;

#else  // ^^^ CANN_ASC_STL_DETAIL_FREESTANDING() ^^^ / vvv CANN_ASC_STL_DETAIL_HOSTED() vvv

// We also need to respect what the user is defining to std::iterator_traits
#if CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBSTDCXX)
// libstdc++ uses `is_base_of`
template <class _Iter, bool>
inline constexpr bool __is_primary_std_template_impl =
    is_base_of_v<::std::__iterator_traits<_Iter>, ::std::iterator_traits<_Iter>>;
template <class _Iter>
inline constexpr bool __is_primary_std_template_impl<_Iter, true> = true;

// This is needed because with a defaulted template argument subsumption fails for C++20 for concepts
// that involve incrementable_traits
template <class _Iter>
struct __is_primary_std_template : bool_constant<__is_primary_std_template_impl<_Iter, is_pointer_v<_Iter>>> {};
#elif CANN_ASC_STL_DETAIL_HOST_STD_LIB(LIBCXX)

// libc++ uses the same mechanism than we do with __primary_template
template <class _Traits>
using __test_for_primary_std_template = enable_if_t<_IsSame<_Traits, typename _Traits::__primary_template>::value>;
template <class _Iter>
using __is_primary_std_template = _IsValidExpansion<__test_for_primary_std_template, ::std::iterator_traits<_Iter>>;

#elif CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL)
// On MSVC we must check for the base class because `_From_primary` is only defined in C++20
template <class _Iter, bool>
inline constexpr bool __is_primary_std_template_impl =
    is_base_of_v<::std::_Iterator_traits_base<_Iter>, ::std::iterator_traits<_Iter>>;
template <class _Iter>
inline constexpr bool __is_primary_std_template_impl<_Iter, true> = true;

// This is needed because with a defaulted template argument subsumption fails for C++20 for concepts
// that involve incrementable_traits
template <class _Iter>
struct __is_primary_std_template : bool_constant<__is_primary_std_template_impl<_Iter, is_pointer_v<_Iter>>> {};
#endif  // ^^^ CANN_ASC_STL_DETAIL_HOST_STD_LIB(STL) ^^^

template <class _Iter, class _OtherTraits>
using __select_traits = conditional_t<__is_primary_std_template<_Iter>::value,
    conditional_t<__is_primary_accl_template<_Iter>::value, _OtherTraits, iterator_traits<_Iter>>,
    ::std::iterator_traits<_Iter>>;

#endif  // CANN_ASC_STL_DETAIL_HOSTED()

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_TYPE_TRAITS_IS_PRIMARY_TEMPLATE_H
