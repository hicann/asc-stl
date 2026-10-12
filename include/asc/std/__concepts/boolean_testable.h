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
#ifndef CANN_ASC_STL_ASC_STDDETAIL__CONCEPTS_BOOLEAN_TESTABLE_H
#define CANN_ASC_STL_ASC_STDDETAIL__CONCEPTS_BOOLEAN_TESTABLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/forward.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class T, class = void>
inline constexpr bool __boolean_testable_v = false;

template <class T>
inline constexpr bool __boolean_testable_v<T, decltype(void(!::asc::std::forward<T>(::asc::std::declval<T>())))> =
    is_convertible_v<T, bool> && is_convertible_v<decltype(!::asc::std::forward<T>(::asc::std::declval<T>())), bool>;

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class T>
concept __boolean_testable_impl = convertible_to<T, bool>;
template <class T>
concept __boolean_testable = __boolean_testable_impl<T> && requires(T&& value) {
    { !::asc::std::forward<T>(value) } -> __boolean_testable_impl;  // NOLINT(build/include_what_you_use)
};
#else
template <class T>
inline constexpr bool __boolean_testable_impl = is_convertible_v<T, bool>;

template <class T, class = void>
inline constexpr bool __boolean_testable_impl_2 = false;

template <class T>
inline constexpr bool __boolean_testable_impl_2<T, void_t<decltype(!::asc::std::declval<T>())> > =
    __boolean_testable_impl<T> && __boolean_testable_impl<decltype(!::asc::std::declval<T>())>;

template <class T>
inline constexpr bool __boolean_testable = __boolean_testable_impl_2<T>;
#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STDDETAIL__CONCEPTS_BOOLEAN_TESTABLE_H
