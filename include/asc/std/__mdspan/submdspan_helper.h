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

#ifndef CANN_ASC_STL_ASC_STD___MDSPAN_SUBMDSPAN_HELPER_H
#define CANN_ASC_STL_ASC_STD___MDSPAN_SUBMDSPAN_HELPER_H

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
#include <asc/std/__fwd/mdspan.h>
#include <asc/std/__mdspan/concepts.h>
#include <asc/std/__mdspan/extents.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/is_unsigned.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/array>
#include <asc/std/tuple>

CANN_ASC_STL_BEGIN_NAMESPACE

struct full_extent_t {};
inline constexpr full_extent_t full_extent{};

template <class OffsetType, class ExtentType, class StrideType>
struct strided_slice {
    OffsetType offset;
    ExtentType extent;
    StrideType stride;
};

template <class T>
inline constexpr bool __is_strided_slice = false;

template <class OffsetType, class ExtentType, class StrideType>
inline constexpr bool __is_strided_slice<strided_slice<OffsetType, ExtentType, StrideType>> = true;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_SUBMDSPAN_HELPER_H
