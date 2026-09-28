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

#ifndef CANN_ASC_STL_ASC_STD___MDSPAN_EXTENTS_H
#define CANN_ASC_STL_ASC_STD___MDSPAN_EXTENTS_H

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
#include <asc/std/__mdspan/concepts.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_integer.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/make_nbit_int.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__utility/cmp.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/__utility/unreachable.h>
#include <asc/std/array>
#include <asc/std/concepts>
#include <asc/std/cstddef>
#include <asc/std/limits>
#include <asc/std/span>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class IndexType, size_t... StaticExtents>
class extents {
public:
    using index_type = IndexType;
    using size_type = size_t;
    using rank_type = size_t;

    CANN_ASC_STL_API constexpr extents()
    {
        const size_t static_values[rank() == 0 ? 1 : rank()] = {StaticExtents...};
        for (size_t index = 0; index < rank(); ++index) {
            values_[index] =
                static_values[index] == dynamic_extent ? index_type{} : static_cast<index_type>(static_values[index]);
        }
    }

    template <class... OtherIndexTypes>
    CANN_ASC_STL_API constexpr explicit extents(OtherIndexTypes... supplied)
    {
        constexpr size_t supplied_count = sizeof...(OtherIndexTypes);
        static_assert(supplied_count == rank() || supplied_count == rank_dynamic(),
            "extents construction requires rank() or rank_dynamic() values");
        const index_type supplied_values[supplied_count == 0 ? 1 : supplied_count] = {
            static_cast<index_type>(supplied)...};
        const size_t static_values[rank() == 0 ? 1 : rank()] = {StaticExtents...};
        size_t dynamic_index = 0;
        for (size_t index = 0; index < rank(); ++index) {
            if constexpr (supplied_count == rank()) {
                values_[index] = static_values[index] == dynamic_extent ? supplied_values[index] :
                                                                          static_cast<index_type>(static_values[index]);
            } else {
                values_[index] = static_values[index] == dynamic_extent ? supplied_values[dynamic_index++] :
                                                                          static_cast<index_type>(static_values[index]);
            }
        }
    }

    template <class OtherIndexType, size_t Size>
    CANN_ASC_STL_API constexpr explicit extents(const array<OtherIndexType, Size>& supplied)
    {
        const size_t static_values[rank() == 0 ? 1 : rank()] = {StaticExtents...};
        size_t dynamic_index = 0;
        for (size_t index = 0; index < rank(); ++index) {
            if constexpr (Size == rank()) {
                values_[index] = static_values[index] == dynamic_extent ? static_cast<index_type>(supplied[index]) :
                                                                          static_cast<index_type>(static_values[index]);
            } else {
                values_[index] = static_values[index] == dynamic_extent ?
                    static_cast<index_type>(supplied[dynamic_index++]) :
                    static_cast<index_type>(static_values[index]);
            }
        }
    }

    template <class OtherIndexType, size_t Size>
    CANN_ASC_STL_API constexpr explicit extents(span<OtherIndexType, Size> supplied)
    {
        const size_t static_values[rank() == 0 ? 1 : rank()] = {StaticExtents...};
        size_t dynamic_index = 0;
        for (size_t index = 0; index < rank(); ++index) {
            if constexpr (Size == rank()) {
                values_[index] = static_values[index] == dynamic_extent ? static_cast<index_type>(supplied[index]) :
                                                                          static_cast<index_type>(static_values[index]);
            } else {
                values_[index] = static_values[index] == dynamic_extent ?
                    static_cast<index_type>(supplied[dynamic_index++]) :
                    static_cast<index_type>(static_values[index]);
            }
        }
    }

    template <class OtherIndexType, size_t... OtherStaticExtents>
    CANN_ASC_STL_API constexpr explicit extents(const extents<OtherIndexType, OtherStaticExtents...>& other)
    {
        const size_t static_values[rank() == 0 ? 1 : rank()] = {StaticExtents...};
        for (size_t index = 0; index < rank(); ++index) {
            values_[index] = static_values[index] == dynamic_extent ? static_cast<index_type>(other.extent(index)) :
                                                                      static_cast<index_type>(static_values[index]);
        }
    }

    CANN_ASC_STL_API static constexpr rank_type rank() noexcept
    {
        return sizeof...(StaticExtents);
    }

    CANN_ASC_STL_API static constexpr rank_type rank_dynamic() noexcept
    {
        const size_t static_values[rank() == 0 ? 1 : rank()] = {StaticExtents...};
        size_t count = 0;
        for (size_t index = 0; index < rank(); ++index) {
            count += static_values[index] == dynamic_extent ? 1 : 0;
        }
        return count;
    }

    CANN_ASC_STL_API static constexpr size_t static_extent(rank_type index) noexcept
    {
        const size_t static_values[rank() == 0 ? 1 : rank()] = {StaticExtents...};
        return static_values[index];
    }

    CANN_ASC_STL_API constexpr index_type extent(rank_type index) const noexcept
    {
        return values_[index];
    }

    template <class OtherIndexType, size_t... OtherStaticExtents>
    CANN_ASC_STL_API friend constexpr bool operator==(
        const extents& left, const extents<OtherIndexType, OtherStaticExtents...>& right) noexcept
    {
        if constexpr (sizeof...(OtherStaticExtents) != rank()) {
            return false;
        } else {
            for (size_t index = 0; index < rank(); ++index) {
                if (left.extent(index) != right.extent(index))
                    return false;
            }
            return true;
        }
    }

private:
    index_type values_[rank() == 0 ? 1 : rank()]{};
};

namespace __mdspan_detail {

template <size_t... Indices>
struct index_sequence {};

template <size_t Remaining, size_t... Indices>
struct make_index_sequence_impl : make_index_sequence_impl<Remaining - 1, Remaining - 1, Indices...> {};

template <size_t... Indices>
struct make_index_sequence_impl<0, Indices...> {
    using type = index_sequence<Indices...>;
};

template <class IndexType, size_t... Indices>
CANN_ASC_STL_API auto make_dextents(
    index_sequence<Indices...>) -> extents<IndexType, (static_cast<void>(Indices), dynamic_extent)...>;

}  // namespace __mdspan_detail

template <class IndexType, size_t Rank>
using dextents = decltype(__mdspan_detail::make_dextents<IndexType>(
    typename __mdspan_detail::make_index_sequence_impl<Rank>::type{}));

struct __to_dynamic_extent {
    template <class>
    static constexpr size_t value = dynamic_extent;
};

template <class... IndexTypes>
extents(IndexTypes...) -> extents<size_t, __to_dynamic_extent::template value<IndexTypes>...>;

template <size_t Rank, class IndexType = size_t>
using dims = dextents<IndexType, Rank>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_EXTENTS_H
