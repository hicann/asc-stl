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

#ifndef CANN_ASC_STL_ASC_STD___TYPE_TRAITS_IS_SCOPED_ENUM_H
#define CANN_ASC_STL_ASC_STD___TYPE_TRAITS_IS_SCOPED_ENUM_H

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
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_enum.h>
#include <asc/std/__type_traits/underlying_type.h>

CANN_ASC_STL_BEGIN_NAMESPACE

#if CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_scoped_enum)

template <class _Tp>
struct is_scoped_enum : bool_constant<__is_scoped_enum(_Tp)> {};

template <class _Tp>
inline constexpr bool is_scoped_enum_v = __is_scoped_enum(_Tp);

#else

// An enumeration is scoped exactly when its values do not implicitly convert
// to the enumeration's underlying type.  The underlying type is only named
// for actual enumerations so non-enum arguments never instantiate it.
template <class _Tp, bool = is_enum_v<_Tp> >
struct __scoped_enum_impl {
    static constexpr bool value = false;
};

template <class _Tp>
struct __scoped_enum_impl<_Tp, true> {
    static constexpr bool value = !is_convertible_v<_Tp, underlying_type_t<_Tp> >;
};

template <class _Tp>
inline constexpr bool is_scoped_enum_v = __scoped_enum_impl<_Tp>::value;

template <class _Tp>
struct is_scoped_enum : bool_constant<is_scoped_enum_v<_Tp> > {};

#endif  // CANN_ASC_STL_DETAIL_HAS_BUILTIN(__is_scoped_enum)

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TYPE_TRAITS_IS_SCOPED_ENUM_H
