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

#ifndef CANN_ASC_STL_ASC_STD___MDSPAN_ALIGNED_ACCESSOR_H
#define CANN_ASC_STL_ASC_STD___MDSPAN_ALIGNED_ACCESSOR_H

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
#include <asc/std/__mdspan/default_accessor.h>
#include <asc/std/__memory/assume_aligned.h>
#include <asc/std/__memory/is_valid_alignment.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_abstract.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_object.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Element, size_t ByteAlignment>
class aligned_accessor {
public:
    static constexpr size_t byte_alignment = ByteAlignment;
    static_assert(__is_valid_alignment<Element>(byte_alignment), "Invalid ByteAlignment for Element");
    static_assert(is_object_v<Element> && !is_abstract_v<Element> && !is_array_v<Element>,
        "Element must be a complete object type that is neither an abstract class type nor an array type.");

    using offset_policy = default_accessor<Element>;
    using element_type = Element;
    using reference = Element&;
    using data_handle_type = Element*;

    CANN_ASC_STL_API constexpr aligned_accessor() noexcept = default;

    // 数组指针可转换判定（(*)[] 拼写集中一处，约束处用别名保持可读）。
    template <class From, class To>
    static constexpr bool __pointer_arrays_convertible_v =
        is_convertible_v<From (*)[], To (*)[]>;  // NOLINT(whitespace/parens)

    // 仅放行兼容元素类型且不降低对齐要求的转换（数组指针可转换 + 新对齐不小于旧对齐）。
    template <class OtherElement, size_t OtherByteAlignment,
        enable_if_t<__pointer_arrays_convertible_v<OtherElement, Element> && (OtherByteAlignment >= byte_alignment),
            int> = 0>
    CANN_ASC_STL_API constexpr aligned_accessor(aligned_accessor<OtherElement, OtherByteAlignment>) noexcept
    {}

    template <class OtherElement, enable_if_t<__pointer_arrays_convertible_v<OtherElement, Element>, int> = 0>
    CANN_ASC_STL_API constexpr explicit aligned_accessor(default_accessor<OtherElement>) noexcept
    {}

    template <class OtherElement, enable_if_t<__pointer_arrays_convertible_v<OtherElement, Element>, int> = 0>
    CANN_ASC_STL_API constexpr operator default_accessor<OtherElement>() const noexcept
    {
        return {};
    }

    CANN_ASC_STL_API constexpr reference access(data_handle_type pointer, size_t index) const noexcept
    {
        return ::asc::std::assume_aligned<byte_alignment>(pointer)[index];
    }

    CANN_ASC_STL_API constexpr typename offset_policy::data_handle_type offset(
        data_handle_type pointer, size_t index) const noexcept
    {
        return ::asc::std::assume_aligned<byte_alignment>(pointer) + index;
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_ALIGNED_ACCESSOR_H
