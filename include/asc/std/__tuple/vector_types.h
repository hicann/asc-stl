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

#ifndef CANN_ASC_STL_ASC_STD___TUPLE_VECTOR_TYPES_H
#define CANN_ASC_STL_ASC_STD___TUPLE_VECTOR_TYPES_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__fwd/get.h>
#include <asc/std/__tuple/tuple_element.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <size_t Index>
struct __vector_get_element;
template <>
struct __vector_get_element<0> {
    template <class Vector>
    CANN_ASC_STL_API static constexpr decltype(auto) get(Vector&& value) noexcept
    {
        return (::asc::std::forward<Vector>(value).x);
    }
};
template <>
struct __vector_get_element<1> {
    template <class Vector>
    CANN_ASC_STL_API static constexpr decltype(auto) get(Vector&& value) noexcept
    {
        return (::asc::std::forward<Vector>(value).y);
    }
};
template <>
struct __vector_get_element<2> {
    template <class Vector>
    CANN_ASC_STL_API static constexpr decltype(auto) get(Vector&& value) noexcept
    {
        return (::asc::std::forward<Vector>(value).z);
    }
};
template <>
struct __vector_get_element<3> {
    template <class Vector>
    CANN_ASC_STL_API static constexpr decltype(auto) get(Vector&& value) noexcept
    {
        return (::asc::std::forward<Vector>(value).w);  // NOLINT(build/include_what_you_use)
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TUPLE_VECTOR_TYPES_H
