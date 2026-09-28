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

#ifndef CANN_ASC_STL_ASC_STD___LINALG_SCALED_H
#define CANN_ASC_STL_ASC_STD___LINALG_SCALED_H

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
#include <asc/std/__type_traits/add_const.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/mdspan>

namespace asc::std::linalg {

template <class ScalingFactor, class NestedAccessor>
class scaled_accessor {
public:
    using element_type = const decltype(::asc::std::declval<ScalingFactor>() *
        ::asc::std::declval<typename NestedAccessor::element_type>());
    using reference = remove_const_t<element_type>;
    using data_handle_type = typename NestedAccessor::data_handle_type;
    using offset_policy = scaled_accessor<ScalingFactor, typename NestedAccessor::offset_policy>;

    CANN_ASC_STL_API constexpr scaled_accessor() = default;

    template <class OtherScalingFactor, class OtherNestedAccessor>
    CANN_ASC_STL_API constexpr explicit scaled_accessor(
        const scaled_accessor<OtherScalingFactor, OtherNestedAccessor>& other)
        : factor_(other.scaling_factor()), accessor_(other.nested_accessor())
    {}

    CANN_ASC_STL_API constexpr scaled_accessor(const ScalingFactor& factor, const NestedAccessor& accessor)
        : factor_(factor), accessor_(accessor)
    {}

    CANN_ASC_STL_API constexpr reference access(data_handle_type pointer, size_t index) const
    {
        return factor_ * typename NestedAccessor::element_type(accessor_.access(pointer, index));
    }

    CANN_ASC_STL_API constexpr typename offset_policy::data_handle_type offset(
        data_handle_type pointer, size_t index) const
    {
        return accessor_.offset(pointer, index);
    }

    CANN_ASC_STL_API constexpr NestedAccessor nested_accessor() const noexcept
    {
        return accessor_;
    }
    CANN_ASC_STL_API constexpr ScalingFactor scaling_factor() const noexcept
    {
        return factor_;
    }

private:
    ScalingFactor factor_{};
    NestedAccessor accessor_{};
};

template <class ScalingFactor, class Element, class Extents, class Layout, class Accessor>
CANN_ASC_STL_API constexpr auto scaled(ScalingFactor factor, mdspan<Element, Extents, Layout, Accessor> input)
{
    using result_accessor = scaled_accessor<ScalingFactor, Accessor>;
    return mdspan<typename result_accessor::element_type, Extents, Layout, result_accessor>(
        input.data_handle(), input.mapping(), result_accessor(factor, input.accessor()));
}

}  // namespace asc::std::linalg

#endif  // CANN_ASC_STL_ASC_STD___LINALG_SCALED_H
