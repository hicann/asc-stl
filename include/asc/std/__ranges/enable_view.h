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

#ifndef CANN_ASC_STL_ASC_STD___RANGES_ENABLE_VIEW_H
#define CANN_ASC_STL_ASC_STD___RANGES_ENABLE_VIEW_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_base_of.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/void_t.h>

namespace asc::std::ranges {

struct view_base {};

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()
template <class Derived>
    requires is_class_v<Derived> && same_as<Derived, remove_cv_t<Derived>>
class view_interface;
#else
template <class Derived, enable_if_t<is_class_v<Derived> && is_same_v<Derived, remove_cv_t<Derived>>, int> = 0>
class view_interface;
#endif

template <class Op, class Yp, enable_if_t<is_convertible_v<Op*, view_interface<Yp>*>, int> = 0>
CANN_ASC_STL_API void __is_derived_from_view_interface(const Op*, const view_interface<Yp>*);

template <class T, class = void>
struct __enable_view : false_type {};

template <class T>
struct __enable_view<T, void_t<T*>>
    : bool_constant<is_base_of_v<view_base, T> && is_convertible_v<const volatile T*, const volatile view_base*>> {};

template <class T, class = void>
struct __has_view_interface : false_type {};

template <class T>
struct __has_view_interface<T,
    void_t<decltype(__is_derived_from_view_interface(static_cast<T*>(nullptr), static_cast<T*>(nullptr)))>>
    : true_type {};

template <class T>
inline constexpr bool enable_view = __enable_view<T>::value || __has_view_interface<T>::value;

}  // namespace asc::std::ranges

// Preserve this header's original observable behavior: view_interface used to be
// fully defined in this file, so downstream code including only this file must get
// the complete type. The definition lives in view_interface.h, included here after
// the forward declaration; skip it while in the middle of the concepts.h include
// chain (the concept names used in its body are not visible yet) — in that case
// downstream code includes view_interface.h directly, as usual.
#ifndef CANN_ASC_STL_ASC_STD___RANGES_CONCEPTS_H
#include <asc/std/__ranges/view_interface.h>
#endif

#endif  // CANN_ASC_STL_ASC_STD___RANGES_ENABLE_VIEW_H
