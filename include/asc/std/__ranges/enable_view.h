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

#ifndef CANN_ASC_STL_STD_DETAIL_RANGES_ENABLE_VIEW_H
#define CANN_ASC_STL_STD_DETAIL_RANGES_ENABLE_VIEW_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/derived_from.h>
#include <asc/std/__concepts/same_as.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_class.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/void_t.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD_RANGES

struct view_base {};

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Derived>
    requires is_class_v<_Derived> && same_as<_Derived, remove_cv_t<_Derived>>
class view_interface;

#else

template <class _Derived, enable_if_t<is_class_v<_Derived> && same_as<_Derived, remove_cv_t<_Derived>>, int> = 0>
class view_interface;

#endif

template <class _Op, class _Yp, enable_if_t<is_convertible_v<_Op*, view_interface<_Yp>*>, int> = 0>
CANN_ASC_STL_API void __is_derived_from_view_interface(const _Op*, const view_interface<_Yp>*);

#if CANN_ASC_STL_DETAIL_HAS_CONCEPTS()

template <class _Tp>
inline constexpr bool enable_view = derived_from<_Tp, view_base> || requires {
    // NOLINTNEXTLINE(readability/casting)
    ::asc::std::ranges::__is_derived_from_view_interface((_Tp*)nullptr, (_Tp*)nullptr);
};

#else

template <class _Tp, class = void>
inline constexpr bool enable_view = derived_from<_Tp, view_base>;

template <class _Tp>
inline constexpr bool enable_view<
    // NOLINTNEXTLINE(readability/casting)
    _Tp, void_t<decltype(::asc::std::ranges::__is_derived_from_view_interface((_Tp*)nullptr, (_Tp*)nullptr))>> = true;

#endif

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD_RANGES

#endif  // CANN_ASC_STL_STD_DETAIL_RANGES_ENABLE_VIEW_H
