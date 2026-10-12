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
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/mdspan>

namespace asc::std::linalg {

template <class NestedAccessor>
class conjugated_accessor {
private:
    using nested_element_type = typename NestedAccessor::element_type;
    using conj_result_type = decltype(conj_if_needed(::asc::std::declval<nested_element_type>()));

public:
    using element_type = add_const_t<conj_result_type>;
    using reference = remove_const_t<element_type>;
    using data_handle_type = typename NestedAccessor::data_handle_type;
    using offset_policy = conjugated_accessor<typename NestedAccessor::offset_policy>;

    CANN_ASC_STL_API constexpr conjugated_accessor() = default;

    CANN_ASC_STL_API constexpr conjugated_accessor(const NestedAccessor& accessor) : nested_accessor_(accessor)
    {}

    // 嵌套访问器可隐式转换：非显式转换构造（mdspan 访问器组合转换的标准要求）。
    template <class OtherNestedAccessor,
        enable_if_t<is_constructible_v<NestedAccessor, const OtherNestedAccessor&> &&
                is_convertible_v<OtherNestedAccessor, NestedAccessor>,
            int> = 0>
    CANN_ASC_STL_API constexpr conjugated_accessor(const conjugated_accessor<OtherNestedAccessor>& other)
        : nested_accessor_(other.nested_accessor())
    {}

    // 嵌套访问器不可隐式转换：显式转换构造。
    template <class OtherNestedAccessor,
        enable_if_t<is_constructible_v<NestedAccessor, const OtherNestedAccessor&> &&
                !is_convertible_v<OtherNestedAccessor, NestedAccessor>,
            int> = 0>
    CANN_ASC_STL_API explicit constexpr conjugated_accessor(const conjugated_accessor<OtherNestedAccessor>& other)
        : nested_accessor_(other.nested_accessor())
    {}

    CANN_ASC_STL_API constexpr reference access(data_handle_type pointer, size_t index) const noexcept
    {
        return conj_if_needed(nested_element_type(nested_accessor_.access(pointer, index)));
    }

    CANN_ASC_STL_API constexpr typename offset_policy::data_handle_type offset(
        data_handle_type pointer, size_t index) const noexcept
    {
        return nested_accessor_.offset(pointer, index);
    }

    CANN_ASC_STL_API constexpr const NestedAccessor& nested_accessor() const noexcept
    {
        return nested_accessor_;
    }

private:
    NestedAccessor nested_accessor_;
};

template <class Element, class Extents, class Layout, class Accessor>
CANN_ASC_STL_API constexpr auto conjugated(mdspan<Element, Extents, Layout, Accessor> input)
{
    using value_type = typename decltype(input)::value_type;
    // P3050 优化：算术类型、或找不到限定 conj 的类型不额外包装 conjugated_accessor，
    // 直接原样返回（仅嵌套 conjugated_accessor 场景由下方特化重载解包）。
    // 算术分支先短路，避免求 _HasConj<算术> 时实例化本库 float-only 的
    // complex<T>（标量 conj 重载返回 complex<T>）导致硬错误。
    if constexpr (is_arithmetic_v<value_type>) {
        return mdspan<Element, Extents, Layout, Accessor>(input.data_handle(), input.mapping(), input.accessor());
    } else if constexpr (!__conj_if_needed::_HasConj<value_type>) {
        return mdspan<Element, Extents, Layout, Accessor>(input.data_handle(), input.mapping(), input.accessor());
    } else {
        using return_element_type = typename conjugated_accessor<Accessor>::element_type;
        using return_accessor_type = conjugated_accessor<Accessor>;
        return mdspan<return_element_type, Extents, Layout, return_accessor_type>{
            input.data_handle(), input.mapping(), return_accessor_type(input.accessor())};
    }
}

// Conjugation is self-annihilating
template <class Element, class Extents, class Layout, class NestedAccessor>
CANN_ASC_STL_API constexpr auto conjugated(mdspan<Element, Extents, Layout, conjugated_accessor<NestedAccessor>> input)
{
    using return_element_type = typename NestedAccessor::element_type;
    using return_accessor_type = NestedAccessor;
    return mdspan<return_element_type, Extents, Layout, return_accessor_type>(
        input.data_handle(), input.mapping(), input.accessor().nested_accessor());
}

}  // namespace asc::std::linalg

#endif  // CANN_ASC_STL_ASC_STD___LINALG_CONJUGATED_H
