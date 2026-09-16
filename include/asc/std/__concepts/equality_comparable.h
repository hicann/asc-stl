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

#ifndef CANN_ASC_STL_ASC_STD___CONCEPTS_EQUALITY_COMPARABLE_H
#define CANN_ASC_STL_ASC_STD___CONCEPTS_EQUALITY_COMPARABLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/boolean_testable.h>
#include <asc/std/__concepts/common_reference_with.h>
#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__type_traits/common_reference.h>
#include <asc/std/__type_traits/is_comparable.h>
#include <asc/std/__type_traits/make_const_lvalue_ref.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class T, class U>
concept __weakly_equality_comparable_with = requires(const remove_reference_t<T>& t, const remove_reference_t<U>& u) {
    { t == u } -> __boolean_testable;
    { t != u } -> __boolean_testable;
    { u == t } -> __boolean_testable;
    { u != t } -> __boolean_testable;
};

template <class T>
concept equality_comparable = __weakly_equality_comparable_with<T, T>;

template <class T, class U>
concept equality_comparable_with = equality_comparable<T> && equality_comparable<U> &&
    common_reference_with<__make_const_lvalue_ref<T>, __make_const_lvalue_ref<U>> &&
    equality_comparable<common_reference_t<__make_const_lvalue_ref<T>, __make_const_lvalue_ref<U>>> &&
    __weakly_equality_comparable_with<T, U>;
#endif

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___CONCEPTS_EQUALITY_COMPARABLE_H
