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

#ifndef CANN_ASC_STL_ASC_STD___MDSPAN_LAYOUT_STRIDE_H
#define CANN_ASC_STL_ASC_STD___MDSPAN_LAYOUT_STRIDE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__fwd/mdspan.h>
#include <asc/std/__mdspan/concepts.h>
#include <asc/std/__mdspan/empty_base.h>
#include <asc/std/__mdspan/extents.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__utility/as_const.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/__utility/swap.h>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Extents>
class layout_stride::mapping {
public:
    using extents_type = Extents;
    using index_type = typename Extents::index_type;
    using layout_type = layout_stride;

    CANN_ASC_STL_API constexpr mapping() noexcept : extents_{}
    {
        index_type stride_value = 1;
        for (size_t rank = Extents::rank(); rank > 0; --rank) {
            strides_[rank - 1] = stride_value;
            stride_value *= extents_.extent(rank - 1);
        }
    }

    template <class StrideArray>
    CANN_ASC_STL_API constexpr mapping(const Extents& extents, const StrideArray& strides) : extents_(extents)
    {
        for (size_t rank = 0; rank < Extents::rank(); ++rank) {
            strides_[rank] = static_cast<index_type>(strides[rank]);
        }
    }

    template <class OtherMapping>
    CANN_ASC_STL_API constexpr explicit mapping(const OtherMapping& other) noexcept : extents_(other.extents())
    {
        for (size_t rank = 0; rank < Extents::rank(); ++rank) {
            strides_[rank] = static_cast<index_type>(other.stride(rank));
        }
    }

    template <class... Indices>
    CANN_ASC_STL_API constexpr index_type operator()(Indices... supplied) const noexcept
    {
        static_assert(sizeof...(Indices) == Extents::rank());
        const index_type indices[Extents::rank() == 0 ? 1 : Extents::rank()] = {static_cast<index_type>(supplied)...};
        index_type offset = 0;
        for (size_t rank = 0; rank < Extents::rank(); ++rank) {
            offset += indices[rank] * strides_[rank];
        }
        return offset;
    }
    CANN_ASC_STL_API constexpr const Extents& extents() const noexcept
    {
        return extents_;
    }
    CANN_ASC_STL_API constexpr index_type required_span_size() const noexcept
    {
        index_type value = 1;
        for (size_t rank = 0; rank < Extents::rank(); ++rank) {
            if (extents_.extent(rank) == 0)
                return 0;
            value += (extents_.extent(rank) - 1) * strides_[rank];
        }
        return value;
    }
    CANN_ASC_STL_API constexpr index_type stride(size_t rank) const noexcept
    {
        return strides_[rank];
    }
    CANN_ASC_STL_API static constexpr bool is_always_unique() noexcept
    {
        return true;
    }
    CANN_ASC_STL_API static constexpr bool is_always_exhaustive() noexcept
    {
        return false;
    }
    CANN_ASC_STL_API static constexpr bool is_always_strided() noexcept
    {
        return true;
    }
    CANN_ASC_STL_API constexpr bool is_unique() const noexcept
    {
        return true;
    }
    CANN_ASC_STL_API constexpr bool is_exhaustive() const noexcept
    {
        index_type product = 1;
        for (size_t rank = 0; rank < Extents::rank(); ++rank) {
            product *= extents_.extent(rank);
        }
        return required_span_size() == product;
    }
    CANN_ASC_STL_API constexpr bool is_strided() const noexcept
    {
        return true;
    }
    template <class OtherExtents>
    CANN_ASC_STL_API friend constexpr bool operator==(const mapping& left, const mapping<OtherExtents>& right) noexcept
    {
        if (!(left.extents() == right.extents()))
            return false;
        for (size_t rank = 0; rank < Extents::rank(); ++rank) {
            if (left.stride(rank) != right.stride(rank))
                return false;
        }
        return true;
    }

private:
    Extents extents_;
    index_type strides_[Extents::rank() == 0 ? 1 : Extents::rank()]{};
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_LAYOUT_STRIDE_H
