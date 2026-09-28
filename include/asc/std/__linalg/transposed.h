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

#ifndef CANN_ASC_STL_ASC_STD___LINALG_TRANSPOSED_H
#define CANN_ASC_STL_ASC_STD___LINALG_TRANSPOSED_H

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
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/array>
#include <asc/std/mdspan>

namespace asc::std::linalg {

namespace __detail {

template <class Extents>
struct transpose_extents;

template <class IndexType, size_t First, size_t Second>
struct transpose_extents<asc::std::extents<IndexType, First, Second>> {
    using type = asc::std::extents<IndexType, Second, First>;
};

template <class Extents>
using transpose_extents_t = typename transpose_extents<Extents>::type;

template <class Extents>
CANN_ASC_STL_API constexpr transpose_extents_t<Extents> transpose_extents_value(const Extents& value)
{
    static_assert(Extents::rank() == 2);
    return transpose_extents_t<Extents>(value.extent(1), value.extent(0));
}

}  // namespace __detail

template <class Layout>
class layout_transpose {
public:
    using nested_layout_type = Layout;

    template <class Extents>
    class mapping {
    public:
        using extents_type = Extents;
        using index_type = typename Extents::index_type;
        using size_type = typename Extents::size_type;
        using rank_type = typename Extents::rank_type;
        using layout_type = layout_transpose;
        using nested_mapping_type = typename Layout::template mapping<__detail::transpose_extents_t<Extents>>;

        CANN_ASC_STL_API constexpr explicit mapping(const nested_mapping_type& nested)
            : nested_(nested), extents_(__detail::transpose_extents_value(nested.extents()))
        {}

        CANN_ASC_STL_API constexpr const Extents& extents() const noexcept
        {
            return extents_;
        }
        CANN_ASC_STL_API constexpr index_type required_span_size() const noexcept
        {
            return nested_.required_span_size();
        }
        CANN_ASC_STL_API constexpr index_type operator()(index_type first, index_type second) const noexcept
        {
            return nested_(second, first);
        }
        CANN_ASC_STL_API constexpr const nested_mapping_type& nested_mapping() const noexcept
        {
            return nested_;
        }
        CANN_ASC_STL_API static constexpr bool is_always_unique() noexcept
        {
            return nested_mapping_type::is_always_unique();
        }
        CANN_ASC_STL_API static constexpr bool is_always_exhaustive() noexcept
        {
            return nested_mapping_type::is_always_exhaustive();
        }
        CANN_ASC_STL_API static constexpr bool is_always_strided() noexcept
        {
            return nested_mapping_type::is_always_strided();
        }
        CANN_ASC_STL_API constexpr bool is_unique() const noexcept
        {
            return nested_.is_unique();
        }
        CANN_ASC_STL_API constexpr bool is_exhaustive() const noexcept
        {
            return nested_.is_exhaustive();
        }
        CANN_ASC_STL_API constexpr bool is_strided() const noexcept
        {
            return nested_.is_strided();
        }
        CANN_ASC_STL_API constexpr index_type stride(size_t rank) const noexcept
        {
            return nested_.stride(rank == 0 ? 1 : 0);
        }

        template <class OtherExtents>
        CANN_ASC_STL_API friend constexpr bool operator==(
            const mapping& left, const mapping<OtherExtents>& right) noexcept
        {
            return left.nested_mapping() == right.nested_mapping();
        }

    private:
        nested_mapping_type nested_;
        Extents extents_;
    };
};

namespace __detail {

template <class Layout>
struct transposed_layout {
    using type = layout_transpose<Layout>;

    template <class Mapping>
    CANN_ASC_STL_API static constexpr auto make(const Mapping& mapping)
    {
        using result_extents = transpose_extents_t<typename Mapping::extents_type>;
        return typename type::template mapping<result_extents>(mapping);
    }
};

template <>
struct transposed_layout<asc::std::layout_right> {
    using type = asc::std::layout_left;

    template <class Mapping>
    CANN_ASC_STL_API static constexpr auto make(const Mapping& mapping)
    {
        using result_extents = transpose_extents_t<typename Mapping::extents_type>;
        return typename type::template mapping<result_extents>(transpose_extents_value(mapping.extents()));
    }
};

template <>
struct transposed_layout<asc::std::layout_left> {
    using type = asc::std::layout_right;

    template <class Mapping>
    CANN_ASC_STL_API static constexpr auto make(const Mapping& mapping)
    {
        using result_extents = transpose_extents_t<typename Mapping::extents_type>;
        return typename type::template mapping<result_extents>(transpose_extents_value(mapping.extents()));
    }
};

template <>
struct transposed_layout<asc::std::layout_stride> {
    using type = asc::std::layout_stride;

    template <class Mapping>
    CANN_ASC_STL_API static constexpr auto make(const Mapping& mapping)
    {
        using result_extents = transpose_extents_t<typename Mapping::extents_type>;
        const asc::std::array<typename result_extents::index_type, 2> strides{{mapping.stride(1), mapping.stride(0)}};
        return typename type::template mapping<result_extents>(transpose_extents_value(mapping.extents()), strides);
    }
};

template <class NestedLayout>
struct transposed_layout<layout_transpose<NestedLayout>> {
    using type = NestedLayout;

    template <class Extents>
    CANN_ASC_STL_API static constexpr auto make(
        const typename layout_transpose<NestedLayout>::template mapping<Extents>& mapping)
    {
        return mapping.nested_mapping();
    }
};

}  // namespace __detail

template <class Element, class Extents, class Layout, class Accessor>
CANN_ASC_STL_API constexpr auto transposed(mdspan<Element, Extents, Layout, Accessor> input)
{
    static_assert(Extents::rank() == 2);
    using result_layout = typename __detail::transposed_layout<Layout>::type;
    const auto result_mapping = __detail::transposed_layout<Layout>::make(input.mapping());
    return mdspan<Element, typename decltype(result_mapping)::extents_type, result_layout, Accessor>(
        input.data_handle(), result_mapping, input.accessor());
}

}  // namespace asc::std::linalg

#endif  // CANN_ASC_STL_ASC_STD___LINALG_TRANSPOSED_H
