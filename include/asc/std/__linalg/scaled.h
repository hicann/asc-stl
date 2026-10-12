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
#include <asc/std/__type_traits/add_const.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/mdspan>

namespace asc::std::linalg {

template <class ScalingFactor, class NestedAccessor>
class scaled_accessor {
public:
    using element_type = add_const_t<decltype(::asc::std::declval<ScalingFactor>() *
        ::asc::std::declval<typename NestedAccessor::element_type>())>;
    using reference = remove_const_t<element_type>;
    using data_handle_type = typename NestedAccessor::data_handle_type;
    using offset_policy = scaled_accessor<ScalingFactor, typename NestedAccessor::offset_policy>;

    CANN_ASC_STL_API constexpr scaled_accessor() = default;

    // 嵌套访问器不可隐式转换：显式转换构造（标准要求按可转换性分档）。
    template <class OtherScalingFactor, class OtherNestedAccessor,
        enable_if_t<is_constructible_v<NestedAccessor, const OtherNestedAccessor&> &&
                is_constructible_v<ScalingFactor, OtherScalingFactor> &&
                !is_convertible_v<OtherNestedAccessor, NestedAccessor>,
            int> = 0>
    CANN_ASC_STL_API explicit constexpr scaled_accessor(
        const scaled_accessor<OtherScalingFactor, OtherNestedAccessor>& other)
        : scaling_factor_(other.scaling_factor()), nested_accessor_(other.nested_accessor())
    {}

    // 嵌套访问器可隐式转换：非显式转换构造。
    template <class OtherScalingFactor, class OtherNestedAccessor,
        enable_if_t<is_constructible_v<NestedAccessor, const OtherNestedAccessor&> &&
                is_constructible_v<ScalingFactor, OtherScalingFactor> &&
                is_convertible_v<OtherNestedAccessor, NestedAccessor>,
            int> = 0>
    CANN_ASC_STL_API constexpr scaled_accessor(const scaled_accessor<OtherScalingFactor, OtherNestedAccessor>& other)
        : scaling_factor_(other.scaling_factor()), nested_accessor_(other.nested_accessor())
    {}

    CANN_ASC_STL_API constexpr scaled_accessor(const ScalingFactor& factor, const NestedAccessor& accessor)
        : scaling_factor_(factor), nested_accessor_(accessor)
    {}

    CANN_ASC_STL_API constexpr reference access(data_handle_type pointer, size_t index) const
    {
        return scaling_factor_ * typename NestedAccessor::element_type(nested_accessor_.access(pointer, index));
    }

    CANN_ASC_STL_API
    typename offset_policy::data_handle_type constexpr offset(data_handle_type pointer, size_t index) const
    {
        return nested_accessor_.offset(pointer, index);
    }

    CANN_ASC_STL_API constexpr NestedAccessor nested_accessor() const noexcept
    {
        return nested_accessor_;
    }

    CANN_ASC_STL_API constexpr ScalingFactor scaling_factor() const noexcept
    {
        return scaling_factor_;
    }

private:
    // 无默认初始化器（与上游一致）：默认构造后的成员值不确定，标准未规定该值。
    ScalingFactor scaling_factor_;
    NestedAccessor nested_accessor_;
};

namespace __detail {

template <class ScalingFactor, class NestedAccessor>
using __scaled_element_type = add_const_t<typename scaled_accessor<ScalingFactor, NestedAccessor>::element_type>;

}  // namespace __detail

template <class ScalingFactor, class Element, class Extents, class Layout, class Accessor>
CANN_ASC_STL_API constexpr mdspan<__detail::__scaled_element_type<ScalingFactor, Accessor>, Extents, Layout,
    scaled_accessor<ScalingFactor, Accessor>>
scaled(ScalingFactor scaling_factor, mdspan<Element, Extents, Layout, Accessor> input)
{
    using accessor_type = scaled_accessor<ScalingFactor, Accessor>;
    return {input.data_handle(), input.mapping(), accessor_type{scaling_factor, input.accessor()}};
}

}  // namespace asc::std::linalg

#endif  // CANN_ASC_STL_ASC_STD___LINALG_SCALED_H
