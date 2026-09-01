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

#ifndef CANN_ASC_STL_STD_DETAIL_CONCEPTS_BOOLEAN_TESTABLE_H
#define CANN_ASC_STL_STD_DETAIL_CONCEPTS_BOOLEAN_TESTABLE_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Tp>
concept __boolean_testable_impl = convertible_to<_Tp, bool>;

template <class _Tp>
concept __boolean_testable = __boolean_testable_impl<_Tp> && requires(_Tp&& __value) {
    { !static_cast<_Tp&&>(__value) } -> __boolean_testable_impl;
};

#else

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __boolean_testable_impl = convertible_to<_Tp, bool>;

template <class _Tp, class = void>
inline constexpr bool __boolean_testable_impl_2 = false;

template <class _Tp>
inline constexpr bool __boolean_testable_impl_2<_Tp, void_t<decltype(!::asc::std::declval<_Tp>())> > =
    __boolean_testable_impl<_Tp> && __boolean_testable_impl<decltype(!::asc::std::declval<_Tp>())>;

template <class _Tp>
CANN_ASC_STL_DETAIL_ACCL_CONCEPT __boolean_testable = __boolean_testable_impl_2<_Tp>;

#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_CONCEPTS_BOOLEAN_TESTABLE_H
