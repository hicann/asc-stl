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

#ifndef CANN_ASC_STL_ASC_STD___MDSPAN_DEFAULT_ACCESSOR_H
#define CANN_ASC_STL_ASC_STD___MDSPAN_DEFAULT_ACCESSOR_H

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
#include <asc/std/__fwd/mdspan.h>
#include <asc/std/__type_traits/is_abstract.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Element>
struct default_accessor {
    using element_type = Element;
    using reference = Element&;
    using data_handle_type = Element*;
    using offset_policy = default_accessor;
    CANN_ASC_STL_API constexpr default_accessor() noexcept = default;
    template <class OtherElement>
    CANN_ASC_STL_API constexpr default_accessor(default_accessor<OtherElement>) noexcept
    {}
    CANN_ASC_STL_API constexpr reference access(data_handle_type pointer, size_t index) const noexcept
    {
        return pointer[index];
    }
    CANN_ASC_STL_API constexpr data_handle_type offset(data_handle_type pointer, size_t index) const noexcept
    {
        return pointer + index;
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_DEFAULT_ACCESSOR_H
