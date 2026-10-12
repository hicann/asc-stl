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

#ifndef CANN_ASC_STL_ASC_STD___MDSPAN_LAYOUT_LEFT_H
#define CANN_ASC_STL_ASC_STD___MDSPAN_LAYOUT_LEFT_H

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
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Extents>
class layout_left::mapping : private __mdspan_ebco<Extents> {
public:
    static_assert(__mdspan_detail::__is_asc_std_extents_v<Extents>,
        "layout_left::mapping template argument must be a specialization of extents.");

    using extents_type = Extents;
    using index_type = typename extents_type::index_type;
    using size_type = typename extents_type::size_type;
    using rank_type = typename extents_type::rank_type;
    using layout_type = layout_left;
    using base = __mdspan_ebco<Extents>;

    template <class, class, class, class>
    friend class mdspan;

private:
    static_assert(
        (extents_type::rank_dynamic() > 0) || __mdspan_detail::__required_span_size_is_representable(extents_type()),
        "layout_left::mapping product of static extents must be representable as index_type.");

public:
    // [mdspan.layout.left.cons], constructors
    CANN_ASC_STL_API constexpr mapping() noexcept = default;
    CANN_ASC_STL_API constexpr mapping(const mapping&) noexcept = default;

    CANN_ASC_STL_API constexpr mapping(const extents_type& ext) noexcept : base(ext)
    {
        // 不拦截该错误会在后续 mdspan 访问中越界，例如
        // mapping<dextents<char, 2>> map(dextents<char, 2>(40, 40)); map(10, 3) == -126
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__required_span_size_is_representable(ext),
            "layout_left::mapping extents ctor: product of extents must be representable as index_type.");
    }

    template <class OtherExtents,
        enable_if_t<is_constructible_v<extents_type, OtherExtents> && is_convertible_v<OtherExtents, extents_type>,
            int> = 0>
    CANN_ASC_STL_API constexpr mapping(const mapping<OtherExtents>& other) noexcept : base(other.extents())
    {
        // 不拦截该错误会在后续 mdspan 访问中越界，例如
        // mapping<dextents<char, 2>> map(mapping<dextents<int, 2>>(dextents<int, 2>(40, 40))); map(10, 3) == -126
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_representable_as<index_type>(other.required_span_size()),
            "layout_left::mapping converting ctor: other.required_span_size() must be representable as "
            "index_type.");
    }

    template <class OtherExtents,
        enable_if_t<is_constructible_v<extents_type, OtherExtents> && !is_convertible_v<OtherExtents, extents_type>,
            int> = 0>
    CANN_ASC_STL_API explicit constexpr mapping(const mapping<OtherExtents>& other) noexcept : base(other.extents())
    {
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_representable_as<index_type>(other.required_span_size()),
            "layout_left::mapping converting ctor: other.required_span_size() must be representable as "
            "index_type.");
    }

    template <class OtherExtents,
        enable_if_t<(OtherExtents::rank() <= 1) && is_constructible_v<extents_type, OtherExtents> &&
                is_convertible_v<OtherExtents, extents_type>,
            int> = 0>
    CANN_ASC_STL_API constexpr mapping(const layout_right::mapping<OtherExtents>& other) noexcept
        : base(other.extents())
    {
        // 该构造被约束为 rank <= 1，extents 自身会先拦截非法转换，此处断言仅保持一致性。
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_representable_as<index_type>(other.required_span_size()),
            "layout_left::mapping converting ctor: other.required_span_size() must be representable as "
            "index_type.");
    }

    template <class OtherExtents,
        enable_if_t<(OtherExtents::rank() <= 1) && is_constructible_v<extents_type, OtherExtents> &&
                !is_convertible_v<OtherExtents, extents_type>,
            int> = 0>
    CANN_ASC_STL_API explicit constexpr mapping(const layout_right::mapping<OtherExtents>& other) noexcept
        : base(other.extents())
    {
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_representable_as<index_type>(other.required_span_size()),
            "layout_left::mapping converting ctor: other.required_span_size() must be representable as "
            "index_type.");
    }

    template <class OtherMapping>
    CANN_ASC_STL_API constexpr bool __check_strides(const OtherMapping& other) const noexcept
    {
        // 用公共类型比较，避免有符号/无符号比较告警。
        using common_type = common_type_t<index_type, typename OtherMapping::index_type>;
        bool result = true;
        for (rank_type r = 0; r != extents_type::rank(); ++r) {
            if (static_cast<common_type>(stride(r)) != static_cast<common_type>(other.stride(r))) {
                result = false;
                break;
            }
        }
        return result;
    }

    template <class OtherExtents,
        enable_if_t<is_constructible_v<extents_type, OtherExtents> && (extents_type::rank() > 0), int> = 0>
    CANN_ASC_STL_API explicit constexpr mapping(const layout_stride::mapping<OtherExtents>& other) noexcept
        : base(other.extents())
    {
        CANN_ASC_STL_DETAIL_ASSERT(__check_strides(other),
            "layout_left::mapping from layout_stride ctor: strides are not compatible with layout_left.");
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_representable_as<index_type>(other.required_span_size()),
            "layout_left::mapping from layout_stride ctor: other.required_span_size() must be representable as "
            "index_type.");
    }

    template <class OtherExtents,
        enable_if_t<is_constructible_v<extents_type, OtherExtents> && (extents_type::rank() == 0), int> = 0>
    CANN_ASC_STL_API constexpr mapping(const layout_stride::mapping<OtherExtents>& other) noexcept
        : base(other.extents())
    {}

    CANN_ASC_STL_API constexpr mapping& operator=(const mapping&) noexcept = default;

    // [mdspan.layout.left.obs], observers
    CANN_ASC_STL_API constexpr const extents_type& extents() const noexcept
    {
        return this->template __get<0>();
    }

    CANN_ASC_STL_API constexpr index_type required_span_size() const noexcept
    {
        index_type size = 1;
        if constexpr (extents_type::rank() != 0) {
            for (size_t r = 0; r != extents_type::rank(); ++r) {
                size *= extents().extent(r);
            }
        }
        return size;
    }

    template <size_t... Position>
    CANN_ASC_STL_API constexpr index_type __op_index(
        const array<index_type, Extents::rank()>& index_array, index_sequence<Position...>) const noexcept
    {
        index_type result = 0;
        ((result = index_array[extents_type::rank() - 1 - Position] +
                 extents().extent(extents_type::rank() - 1 - Position) * result),
            ...);
        return result;
    }
    CANN_ASC_STL_API constexpr index_type __op_index(
        const array<index_type, extents_type::rank()>&, index_sequence<>) const noexcept
    {
        return 0;
    }

    template <class... Indices,
        enable_if_t<(sizeof...(Indices) == extents_type::rank()) &&
                __mdspan_detail::__all_convertible_to_index_type<index_type, Indices...>,
            int> = 0>
    CANN_ASC_STL_API constexpr index_type operator()(Indices... index) const noexcept
    {
        // mdspan 自身会做越界检查，此处避免双重检查。
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_multidimensional_index_in(extents(), index...),
            "layout_left::mapping: out of bounds indexing");

        const array<index_type, extents_type::rank()> index_array{static_cast<index_type>(index)...};
        return __op_index(index_array, make_index_sequence<sizeof...(Indices)>());
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
        // 过大的 r 等价于对存储信息越界访问。
        CANN_ASC_STL_DETAIL_ASSERT(r < extents_type::rank(), "layout_left::mapping::stride(): invalid rank index");
        index_type s = 1;
        for (rank_type i = 0; i < r; ++i) {
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

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_LAYOUT_LEFT_H
