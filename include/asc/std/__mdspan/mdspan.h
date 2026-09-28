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

#ifndef CANN_ASC_STL_ASC_STD___MDSPAN_MDSPAN_H
#define CANN_ASC_STL_ASC_STD___MDSPAN_MDSPAN_H

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
#include <asc/std/__mdspan/concepts.h>
#include <asc/std/__mdspan/default_accessor.h>
#include <asc/std/__mdspan/empty_base.h>
#include <asc/std/__mdspan/extents.h>
#include <asc/std/__mdspan/layout_right.h>
#include <asc/std/__type_traits/extent.h>
#include <asc/std/__type_traits/is_abstract.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/rank.h>
#include <asc/std/__type_traits/remove_all_extents.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_pointer.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__utility/as_const.h>
#include <asc/std/__utility/cmp.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/__utility/move.h>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/limits>
#include <asc/std/span>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Element, class Extents, class Layout, class Accessor>
class mdspan {
public:
    using element_type = Element;
    using value_type = Element;
    using extents_type = Extents;
    using layout_type = Layout;
    using accessor_type = Accessor;
    using mapping_type = typename Layout::template mapping<Extents>;
    using index_type = typename Extents::index_type;
    using size_type = typename Extents::size_type;
    using rank_type = typename Extents::rank_type;
    using data_handle_type = typename Accessor::data_handle_type;
    using reference = typename Accessor::reference;

    CANN_ASC_STL_API static constexpr rank_type rank() noexcept
    {
        return Extents::rank();
    }
    CANN_ASC_STL_API static constexpr rank_type rank_dynamic() noexcept
    {
        return Extents::rank_dynamic();
    }
    CANN_ASC_STL_API static constexpr size_t static_extent(rank_type rank_index) noexcept
    {
        return Extents::static_extent(rank_index);
    }

    CANN_ASC_STL_API constexpr mdspan() noexcept = default;
    CANN_ASC_STL_API constexpr mdspan(const mdspan&) = default;
    CANN_ASC_STL_API constexpr mdspan(mdspan&&) = default;
    CANN_ASC_STL_API constexpr mdspan& operator=(const mdspan&) = default;
    CANN_ASC_STL_API constexpr mdspan& operator=(mdspan&&) = default;

    template <class... OtherIndexTypes>
    CANN_ASC_STL_API constexpr explicit mdspan(data_handle_type pointer, OtherIndexTypes... supplied_extents)
        : pointer_(pointer), mapping_(Extents(supplied_extents...)), accessor_()
    {}

    template <class OtherIndexType, size_t Size>
    CANN_ASC_STL_API constexpr mdspan(data_handle_type pointer, const array<OtherIndexType, Size>& supplied_extents)
        : pointer_(pointer), mapping_(Extents(supplied_extents)), accessor_()
    {}

    template <class OtherIndexType, size_t Size>
    CANN_ASC_STL_API constexpr mdspan(data_handle_type pointer, span<OtherIndexType, Size> supplied_extents)
        : pointer_(pointer), mapping_(Extents(supplied_extents)), accessor_()
    {}

    CANN_ASC_STL_API constexpr mdspan(data_handle_type pointer, const Extents& extents)
        : pointer_(pointer), mapping_(extents), accessor_()
    {}
    CANN_ASC_STL_API constexpr mdspan(data_handle_type pointer, const mapping_type& mapping)
        : pointer_(pointer), mapping_(mapping), accessor_()
    {}
    CANN_ASC_STL_API constexpr mdspan(data_handle_type pointer, const mapping_type& mapping, const Accessor& accessor)
        : pointer_(pointer), mapping_(mapping), accessor_(accessor)
    {}

    template <class OtherElement, class OtherExtents, class OtherLayout, class OtherAccessor>
    CANN_ASC_STL_API constexpr explicit mdspan(
        const mdspan<OtherElement, OtherExtents, OtherLayout, OtherAccessor>& other)
        : pointer_(other.data_handle()), mapping_(other.mapping()), accessor_(other.accessor())
    {}

private:
    template <class Indices, size_t... Positions>
    CANN_ASC_STL_API constexpr reference __access_indices(
        const Indices& indices, __mdspan_detail::index_sequence<Positions...>) const noexcept
    {
        return accessor_.access(pointer_, mapping_(indices[Positions]...));
    }

public:
#if defined(__cpp_multidimensional_subscript) && __cpp_multidimensional_subscript >= 202110L
    template <class... Indices>
    CANN_ASC_STL_API constexpr reference operator[](Indices... indices) const noexcept
    {
        static_assert(sizeof...(Indices) == Extents::rank());
        return accessor_.access(pointer_, mapping_(indices...));
    }
#else
    template <class Index>
    CANN_ASC_STL_API constexpr reference operator[](Index index) const noexcept
    {
        return accessor_.access(pointer_, mapping_(index));
    }
#endif
    template <class OtherIndexType>
    CANN_ASC_STL_API constexpr reference operator[](
        const array<OtherIndexType, Extents::rank()>& indices) const noexcept
    {
        return __access_indices(indices, typename __mdspan_detail::make_index_sequence_impl<Extents::rank()>::type{});
    }
    template <class OtherIndexType>
    CANN_ASC_STL_API constexpr reference operator[](span<OtherIndexType, Extents::rank()> indices) const noexcept
    {
        return __access_indices(indices, typename __mdspan_detail::make_index_sequence_impl<Extents::rank()>::type{});
    }
    CANN_ASC_STL_API constexpr index_type extent(rank_type rank_index) const noexcept
    {
        return mapping_.extents().extent(rank_index);
    }
    CANN_ASC_STL_API constexpr size_type size() const noexcept
    {
        size_type result = 1;
        for (rank_type rank_index = 0; rank_index < rank(); ++rank_index) {
            result *= static_cast<size_type>(extent(rank_index));
        }
        return result;
    }
    CANN_ASC_STL_API constexpr bool empty() const noexcept
    {
        for (rank_type rank_index = 0; rank_index < rank(); ++rank_index) {
            if (extent(rank_index) == 0)
                return true;
        }
        return false;
    }
    CANN_ASC_STL_API constexpr const extents_type& extents() const noexcept
    {
        return mapping_.extents();
    }
    CANN_ASC_STL_API constexpr data_handle_type data_handle() const noexcept
    {
        return pointer_;
    }
    CANN_ASC_STL_API constexpr const mapping_type& mapping() const noexcept
    {
        return mapping_;
    }
    CANN_ASC_STL_API constexpr const Accessor& accessor() const noexcept
    {
        return accessor_;
    }
    CANN_ASC_STL_API static constexpr bool is_always_unique() noexcept
    {
        return mapping_type::is_always_unique();
    }
    CANN_ASC_STL_API static constexpr bool is_always_exhaustive() noexcept
    {
        return mapping_type::is_always_exhaustive();
    }
    CANN_ASC_STL_API static constexpr bool is_always_strided() noexcept
    {
        return mapping_type::is_always_strided();
    }
    CANN_ASC_STL_API constexpr bool is_unique() const noexcept
    {
        return mapping_.is_unique();
    }
    CANN_ASC_STL_API constexpr bool is_exhaustive() const noexcept
    {
        return mapping_.is_exhaustive();
    }
    CANN_ASC_STL_API constexpr bool is_strided() const noexcept
    {
        return mapping_.is_strided();
    }
    CANN_ASC_STL_API constexpr index_type stride(rank_type rank_index) const noexcept
    {
        return mapping_.stride(rank_index);
    }

    // NOLINTNEXTLINE(build/include_what_you_use)
    CANN_ASC_STL_API friend constexpr void swap(mdspan& left, mdspan& right) noexcept
    {
        data_handle_type pointer = left.pointer_;
        left.pointer_ = right.pointer_;
        right.pointer_ = pointer;
        mapping_type mapping = left.mapping_;
        left.mapping_ = right.mapping_;
        right.mapping_ = mapping;
        accessor_type accessor = left.accessor_;
        left.accessor_ = right.accessor_;
        right.accessor_ = accessor;
    }

private:
    data_handle_type pointer_{};
    mapping_type mapping_{};
    Accessor accessor_{};
};

template <class Element, class... IndexTypes>
mdspan(Element*, IndexTypes...) -> mdspan<Element, extents<size_t, __to_dynamic_extent::template value<IndexTypes>...>>;

template <class Element, class OtherIndexType, size_t Size>
mdspan(Element*, const array<OtherIndexType, Size>&) -> mdspan<Element, dextents<size_t, Size>>;

template <class Element, class OtherIndexType, size_t Size>
mdspan(Element*, span<OtherIndexType, Size>) -> mdspan<Element, dextents<size_t, Size>>;

template <class Element, class OtherIndexType, size_t... StaticExtents>
mdspan(Element*,
    const extents<OtherIndexType, StaticExtents...>&) -> mdspan<Element, extents<OtherIndexType, StaticExtents...>>;

template <class Element, class Mapping>
mdspan(Element*, const Mapping&) -> mdspan<Element, typename Mapping::extents_type, typename Mapping::layout_type>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_MDSPAN_H
