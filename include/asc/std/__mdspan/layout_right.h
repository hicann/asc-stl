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

#ifndef CANN_ASC_STL_ASC_STD___MDSPAN_LAYOUT_RIGHT_H
#define CANN_ASC_STL_ASC_STD___MDSPAN_LAYOUT_RIGHT_H

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
#include <asc/std/__mdspan/empty_base.h>
#include <asc/std/__mdspan/extents.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Extents>
class layout_right::mapping : private __mdspan_ebco<Extents> {
public:
    static_assert(__mdspan_detail::__is_asc_std_extents_v<Extents>,
        "layout_right::mapping template argument must be a specialization of extents.");

    using extents_type = Extents;
    using index_type = typename extents_type::index_type;
    using size_type = typename extents_type::size_type;
    using rank_type = typename extents_type::rank_type;
    using layout_type = layout_right;
    using base = __mdspan_ebco<Extents>;

    template <class, class, class, class>
    friend class mdspan;

private:
    static_assert(
        (extents_type::rank_dynamic() > 0) || __mdspan_detail::__required_span_size_is_representable(extents_type()),
        "layout_right::mapping product of static extents must be representable as index_type.");

public:
    // [mdspan.layout.right.cons], constructors
    CANN_ASC_STL_API constexpr mapping() noexcept = default;
    CANN_ASC_STL_API constexpr mapping(const mapping&) noexcept = default;

    CANN_ASC_STL_API constexpr mapping(const extents_type& ext) noexcept : base(ext)
    {
        // Without intercepting this error a later mdspan access goes out of bounds, e.g.
        // mapping<dextents<char, 2>> map(dextents<char, 2>(40, 40)); map(3, 10) == -126
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__required_span_size_is_representable(ext),
            "layout_right::mapping extents ctor: product of extents must be representable as index_type.");
    }

    template <class OtherExtents,
        enable_if_t<is_constructible_v<extents_type, OtherExtents> && is_convertible_v<OtherExtents, extents_type>,
            int> = 0>
    CANN_ASC_STL_API constexpr mapping(const mapping<OtherExtents>& other) noexcept : base(other.extents())
    {
        // Without intercepting this error a later mdspan access goes out of bounds, e.g.
        // mapping<dextents<char, 2>> map(mapping<dextents<int, 2>>(dextents<int, 2>(40, 40))); map(3, 10) == -126
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_representable_as<index_type>(other.required_span_size()),
            "layout_right::mapping converting ctor: other.required_span_size() must be representable as "
            "index_type.");
    }

    template <class OtherExtents,
        enable_if_t<is_constructible_v<extents_type, OtherExtents> && !is_convertible_v<OtherExtents, extents_type>,
            int> = 0>
    CANN_ASC_STL_API explicit constexpr mapping(const mapping<OtherExtents>& other) noexcept : base(other.extents())
    {
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_representable_as<index_type>(other.required_span_size()),
            "layout_right::mapping converting ctor: other.required_span_size() must be representable as "
            "index_type.");
    }

    template <class OtherExtents,
        enable_if_t<(OtherExtents::rank() <= 1) && is_constructible_v<extents_type, OtherExtents> &&
                is_convertible_v<OtherExtents, extents_type>,
            int> = 0>
    CANN_ASC_STL_API constexpr mapping(const layout_left::mapping<OtherExtents>& other) noexcept : base(other.extents())
    {
        // This constructor is constrained to rank <= 1 and extents itself already rejects
        // invalid conversions; the assertion here only keeps the overloads consistent.
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_representable_as<index_type>(other.required_span_size()),
            "layout_right::mapping converting ctor: other.required_span_size() must be representable as "
            "index_type.");
    }

    template <class OtherExtents,
        enable_if_t<(OtherExtents::rank() <= 1) && is_constructible_v<extents_type, OtherExtents> &&
                !is_convertible_v<OtherExtents, extents_type>,
            int> = 0>
    CANN_ASC_STL_API explicit constexpr mapping(const layout_left::mapping<OtherExtents>& other) noexcept
        : base(other.extents())
    {
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_representable_as<index_type>(other.required_span_size()),
            "layout_right::mapping converting ctor: other.required_span_size() must be representable as "
            "index_type.");
    }

    template <class OtherMapping>
    CANN_ASC_STL_API constexpr bool __check_strides(const OtherMapping& other) const noexcept
    {
        // Compare in the common type to avoid signed/unsigned comparison warnings.
        using common_type = common_type_t<index_type, typename OtherMapping::index_type>;
        for (rank_type r = 0; r != extents_type::rank(); ++r) {
            if (static_cast<common_type>(stride(r)) != static_cast<common_type>(other.stride(r))) {
                return false;
            }
        }
        return true;
    }

    template <class OtherExtents,
        enable_if_t<is_constructible_v<extents_type, OtherExtents> && (extents_type::rank() > 0), int> = 0>
    CANN_ASC_STL_API explicit constexpr mapping(const layout_stride::mapping<OtherExtents>& other) noexcept
        : base(other.extents())
    {
        CANN_ASC_STL_DETAIL_ASSERT(__check_strides(other),
            "layout_right::mapping from layout_stride ctor: strides are not compatible with layout_left.");
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_representable_as<index_type>(other.required_span_size()),
            "layout_right::mapping from layout_stride ctor: other.required_span_size() must be representable as "
            "index_type.");
    }

    template <class OtherExtents,
        enable_if_t<is_constructible_v<extents_type, OtherExtents> && (extents_type::rank() == 0), int> = 0>
    CANN_ASC_STL_API constexpr mapping(const layout_stride::mapping<OtherExtents>& other) noexcept
        : base(other.extents())
    {}

    CANN_ASC_STL_API constexpr mapping& operator=(const mapping&) noexcept = default;

    // [mdspan.layout.right.obs], observers
    CANN_ASC_STL_API constexpr const extents_type& extents() const noexcept
    {
        return this->template __get<0>();
    }

    CANN_ASC_STL_API constexpr index_type required_span_size() const noexcept
    {
        index_type size = 1;
        if constexpr (extents_type::rank() > 0) {
            for (size_t r = 0; r < extents_type::rank(); ++r) {
                size *= extents().extent(r);
            }
        }
        return size;
    }

    template <size_t... Position, class... Indices>
    CANN_ASC_STL_API constexpr index_type __op_index(index_sequence<Position...>, Indices... index) const noexcept
    {
        index_type result = 0;
        ((result = static_cast<index_type>(index) + extents().extent(Position) * result), ...);
        return result;
    }
    CANN_ASC_STL_API constexpr index_type __op_index(index_sequence<>) const noexcept
    {
        return 0;
    }

    template <class... Indices,
        enable_if_t<(sizeof...(Indices) == extents_type::rank()) &&
                __mdspan_detail::__all_convertible_to_index_type<index_type, Indices...>,
            int> = 0>
    CANN_ASC_STL_API constexpr index_type operator()(Indices... index) const noexcept
    {
        // mdspan performs its own bounds checking; keep this light to avoid double checking.
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_multidimensional_index_in(extents(), index...),
            "layout_right::mapping: out of bounds indexing");
        return __op_index(make_index_sequence<sizeof...(Indices)>(), index...);
    }

    CANN_ASC_STL_API static constexpr bool is_always_unique() noexcept
    {
        return true;
    }
    CANN_ASC_STL_API static constexpr bool is_always_exhaustive() noexcept
    {
        return true;
    }
    CANN_ASC_STL_API static constexpr bool is_always_strided() noexcept
    {
        return true;
    }

    CANN_ASC_STL_API static constexpr bool is_unique() noexcept
    {
        return true;
    }
    CANN_ASC_STL_API static constexpr bool is_exhaustive() noexcept
    {
        return true;
    }
    CANN_ASC_STL_API static constexpr bool is_strided() noexcept
    {
        return true;
    }

    template <class Extents2 = Extents, enable_if_t<(Extents2::rank() > 0), int> = 0>
    CANN_ASC_STL_API constexpr index_type stride(rank_type r) const noexcept
    {
        // An out-of-range r is equivalent to an out-of-bounds access on the stored information.
        CANN_ASC_STL_DETAIL_ASSERT(r < extents_type::rank(), "layout_right::mapping::stride(): invalid rank index");
        index_type s = 1;
        for (rank_type i = extents_type::rank() - 1; i > r; --i) {
            s *= extents().extent(i);
        }
        return s;
    }

    template <class OtherExtents, class Extents2 = Extents,
        enable_if_t<(OtherExtents::rank() == Extents2::rank()), int> = 0>
    CANN_ASC_STL_API friend constexpr bool operator==(const mapping& left, const mapping<OtherExtents>& right) noexcept
    {
        return left.extents() == right.extents();
    }

#if CANN_ASC_STL_DETAIL_STD_VER <= 2017
    template <class OtherExtents, class Extents2 = Extents,
        enable_if_t<(OtherExtents::rank() == Extents2::rank()), int> = 0>
    CANN_ASC_STL_API friend constexpr bool operator!=(const mapping& left, const mapping<OtherExtents>& right) noexcept
    {
        return !(left.extents() == right.extents());
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER <= 2017
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_LAYOUT_RIGHT_H
