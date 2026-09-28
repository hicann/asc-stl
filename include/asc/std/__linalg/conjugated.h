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

#ifndef CANN_ASC_STL_ASC_STD___LINALG_CONJUGATED_H
#define CANN_ASC_STL_ASC_STD___LINALG_CONJUGATED_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__linalg/conj_if_needed.h>
#include <asc/std/__type_traits/add_const.h>
#include <asc/std/__type_traits/is_arithmetic.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/mdspan>

namespace asc::std::linalg {

template <class NestedAccessor>
class conjugated_accessor {
public:
    using nested_element_type = typename NestedAccessor::element_type;
    using element_type = const decltype(conj_if_needed(::asc::std::declval<nested_element_type>()));
    using reference = remove_const_t<element_type>;
    using data_handle_type = typename NestedAccessor::data_handle_type;
    using offset_policy = conjugated_accessor<typename NestedAccessor::offset_policy>;

    CANN_ASC_STL_API constexpr conjugated_accessor() = default;
    CANN_ASC_STL_API constexpr explicit conjugated_accessor(const NestedAccessor& accessor) : accessor_(accessor)
    {}

    template <class OtherNestedAccessor>
    CANN_ASC_STL_API constexpr explicit conjugated_accessor(const conjugated_accessor<OtherNestedAccessor>& other)
        : accessor_(other.nested_accessor())
    {}

    CANN_ASC_STL_API constexpr reference access(data_handle_type pointer, size_t index) const
    {
        return conj_if_needed(nested_element_type(accessor_.access(pointer, index)));
    }

    CANN_ASC_STL_API constexpr typename offset_policy::data_handle_type offset(
        data_handle_type pointer, size_t index) const
    {
        return accessor_.offset(pointer, index);
    }

    CANN_ASC_STL_API constexpr const NestedAccessor& nested_accessor() const noexcept
    {
        return accessor_;
    }

private:
    NestedAccessor accessor_{};
};

template <class Element, class Extents, class Layout, class Accessor>
CANN_ASC_STL_API constexpr auto conjugated(mdspan<Element, Extents, Layout, Accessor> input)
{
    if constexpr (!is_arithmetic_v<Element>) {
        using result_accessor = conjugated_accessor<Accessor>;
        return mdspan<typename result_accessor::element_type, Extents, Layout, result_accessor>(
            input.data_handle(), input.mapping(), result_accessor(input.accessor()));
    } else {
        return mdspan<Element, Extents, Layout, Accessor>(input.data_handle(), input.mapping(), input.accessor());
    }
}

template <class Element, class Extents, class Layout, class NestedAccessor>
CANN_ASC_STL_API constexpr auto conjugated(mdspan<Element, Extents, Layout, conjugated_accessor<NestedAccessor>> input)
{
    return mdspan<typename NestedAccessor::element_type, Extents, Layout, NestedAccessor>(
        input.data_handle(), input.mapping(), input.accessor().nested_accessor());
}

}  // namespace asc::std::linalg

#endif  // CANN_ASC_STL_ASC_STD___LINALG_CONJUGATED_H
