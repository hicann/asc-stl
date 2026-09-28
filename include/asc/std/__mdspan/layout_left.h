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
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/limits>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Extents>
class layout_left::mapping {
public:
    using extents_type = Extents;
    using index_type = typename Extents::index_type;
    using layout_type = layout_left;

    CANN_ASC_STL_API constexpr mapping() noexcept = default;
    CANN_ASC_STL_API constexpr explicit mapping(const Extents& extents) : extents_(extents)
    {}
    template <class OtherExtents>
    CANN_ASC_STL_API constexpr explicit mapping(const mapping<OtherExtents>& other) noexcept : extents_(other.extents())
    {}
    template <class... Indices>
    CANN_ASC_STL_API constexpr index_type operator()(Indices... supplied) const noexcept
    {
        static_assert(sizeof...(Indices) == Extents::rank());
        const index_type indices[Extents::rank() == 0 ? 1 : Extents::rank()] = {static_cast<index_type>(supplied)...};
        if constexpr (Extents::rank() == 0) {
            return index_type{0};
        } else {
            index_type offset = indices[Extents::rank() - 1];
            for (size_t rank = Extents::rank() - 1; rank > 0; --rank) {
                offset = offset * extents_.extent(rank - 1) + indices[rank - 1];
            }
            return offset;
        }
    }
    CANN_ASC_STL_API constexpr const Extents& extents() const noexcept
    {
        return extents_;
    }
    CANN_ASC_STL_API constexpr index_type stride(size_t rank) const noexcept
    {
        index_type value = 1;
        for (size_t index = 0; index < rank; ++index) {
            value *= extents_.extent(index);
        }
        return value;
    }
    CANN_ASC_STL_API constexpr index_type required_span_size() const noexcept
    {
        index_type value = 1;
        for (size_t index = 0; index < Extents::rank(); ++index) {
            value *= extents_.extent(index);
        }
        return value;
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
    CANN_ASC_STL_API constexpr bool is_unique() const noexcept
    {
        return true;
    }
    CANN_ASC_STL_API constexpr bool is_exhaustive() const noexcept
    {
        return true;
    }
    CANN_ASC_STL_API constexpr bool is_strided() const noexcept
    {
        return true;
    }
    template <class OtherExtents>
    CANN_ASC_STL_API friend constexpr bool operator==(const mapping& left, const mapping<OtherExtents>& right) noexcept
    {
        return left.extents() == right.extents();
    }

private:
    Extents extents_;
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_LAYOUT_LEFT_H
