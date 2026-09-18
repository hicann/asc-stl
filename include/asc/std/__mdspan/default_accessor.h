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

#ifndef CANN_ASC_STL_STD_DETAIL_MDSPAN_DEFAULT_ACCESSOR_H
#define CANN_ASC_STL_STD_DETAIL_MDSPAN_DEFAULT_ACCESSOR_H

#include <asc/std/detail/__config>

CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER

#include <asc/std/__concepts/concept_macros.h>
#include <asc/std/__fwd/mdspan.h>
#include <asc/std/__type_traits/is_abstract.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/cstddef>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _ElementType>
struct default_accessor {
    static_assert(!is_array_v<_ElementType>, "default_accessor: template argument may not be an array type");
    static_assert(!is_abstract_v<_ElementType>, "default_accessor: template argument may not be an abstract class");

    using offset_policy = default_accessor;
    using element_type = _ElementType;
    using reference = _ElementType&;
    using data_handle_type = _ElementType*;

    CANN_ASC_STL_DETAIL_HIDE_FROM_ABI constexpr default_accessor() noexcept = default;

    CANN_ASC_STL_DETAIL_ACCL_TEMPLATE(class _OtherElementType)
    CANN_ASC_STL_DETAIL_ACCL_REQUIRES(is_convertible_v<_OtherElementType (*)[], element_type (*)[]>)  // NOLINT
    CANN_ASC_STL_API constexpr default_accessor(default_accessor<_OtherElementType>) noexcept
    {}

    [[nodiscard]] CANN_ASC_STL_API constexpr reference access(data_handle_type __p, size_t __i) const noexcept
    {
        return __p[__i];
    }
    [[nodiscard]] CANN_ASC_STL_API constexpr data_handle_type offset(data_handle_type __p, size_t __i) const noexcept
    {
        return __p + __i;
    }
};

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_MDSPAN_DEFAULT_ACCESSOR_H
