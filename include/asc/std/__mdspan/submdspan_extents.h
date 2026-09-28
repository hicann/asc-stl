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

#ifndef CANN_ASC_STL_ASC_STD___MDSPAN_SUBMDSPAN_EXTENTS_H
#define CANN_ASC_STL_ASC_STD___MDSPAN_SUBMDSPAN_EXTENTS_H

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
#include <asc/std/__concepts/convertible_to.h>
#include <asc/std/__fwd/mdspan.h>
#include <asc/std/__mdspan/concepts.h>
#include <asc/std/__mdspan/extents.h>
#include <asc/std/__mdspan/submdspan_helper.h>
#include <asc/std/__tuple/tuple_like.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/is_unsigned.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/array>
#include <asc/std/tuple>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class...>
using __submdspan_void_t = void;
template <class Pair, class = void>
struct __submdspan_has_pair_members {
    static constexpr bool value = false;
};
template <class Pair>
struct __submdspan_has_pair_members<Pair,
    __submdspan_void_t<decltype(static_cast<Pair*>(nullptr)->first), decltype(static_cast<Pair*>(nullptr)->second)>> {
    static constexpr bool value = true;
};
template <class Pair, class = void>
struct __submdspan_has_tuple_pair {
    static constexpr bool value = false;
};
template <class Pair>
struct __submdspan_has_tuple_pair<Pair,
    __submdspan_void_t<decltype(tuple_size<Pair>::value), decltype(::asc::std::get<0>(*static_cast<Pair*>(nullptr))),
        decltype(::asc::std::get<1>(*static_cast<Pair*>(nullptr)))>> {
    static constexpr bool value = tuple_size<Pair>::value == 2;
};
template <class Pair>
inline constexpr bool __submdspan_pair_slice_v =
    __submdspan_has_pair_members<Pair>::value || __submdspan_has_tuple_pair<Pair>::value;

template <class Pair>
CANN_ASC_STL_API constexpr auto __submdspan_slice_first(const Pair& value)
{
    if constexpr (__submdspan_has_pair_members<Pair>::value)
        return value.first;
    else
        return ::asc::std::get<0>(value);
}
template <class Pair>
CANN_ASC_STL_API constexpr auto __submdspan_slice_second(const Pair& value)
{
    if constexpr (__submdspan_has_pair_members<Pair>::value)
        return value.second;
    else
        return ::asc::std::get<1>(value);
}

template <class Extents, class Pair, enable_if_t<__submdspan_pair_slice_v<Pair>, int> = 0>
CANN_ASC_STL_API constexpr auto submdspan_extents(const Extents& source, const Pair& first_slice, full_extent_t)
{
    using result_extents = extents<typename Extents::index_type, dynamic_extent, dynamic_extent>;
    return result_extents(static_cast<typename Extents::index_type>(
                              __submdspan_slice_second(first_slice) - __submdspan_slice_first(first_slice)),
        source.extent(1));
}

template <class Extents, class Pair, enable_if_t<__submdspan_pair_slice_v<Pair>, int> = 0>
CANN_ASC_STL_API constexpr auto submdspan_extents(const Extents& source, full_extent_t, const Pair& second_slice)
{
    using result_extents = extents<typename Extents::index_type, dynamic_extent, dynamic_extent>;
    return result_extents(source.extent(0),
        static_cast<typename Extents::index_type>(
            __submdspan_slice_second(second_slice) - __submdspan_slice_first(second_slice)));
}

template <class Extents, class Offset, class SliceExtent, class Stride>
CANN_ASC_STL_API constexpr auto submdspan_extents(
    const Extents& source, const strided_slice<Offset, SliceExtent, Stride>& first_slice, full_extent_t)
{
    using index_type = typename Extents::index_type;
    using result_extents = extents<index_type, dynamic_extent, dynamic_extent>;
    const index_type result_first =
        static_cast<index_type>((first_slice.extent + first_slice.stride - 1) / first_slice.stride);
    return result_extents(result_first, source.extent(1));
}

template <class Extents, class Offset, class SliceExtent, class Stride>
CANN_ASC_STL_API constexpr auto submdspan_extents(
    const Extents& source, full_extent_t, const strided_slice<Offset, SliceExtent, Stride>& second_slice)
{
    using index_type = typename Extents::index_type;
    using result_extents = extents<index_type, dynamic_extent, dynamic_extent>;
    const index_type result_second =
        static_cast<index_type>((second_slice.extent + second_slice.stride - 1) / second_slice.stride);
    return result_extents(source.extent(0), result_second);
}

template <class Extents>
CANN_ASC_STL_API constexpr auto submdspan_extents(const Extents& source, full_extent_t, full_extent_t)
{
    return source;
}

template <class Extents, class Index, enable_if_t<is_integral_v<Index>, int> = 0>
CANN_ASC_STL_API constexpr auto submdspan_extents(const Extents& source, Index, full_extent_t)
{
    using result_extents = extents<typename Extents::index_type, Extents::static_extent(1)>;
    return result_extents(source.extent(1));
}

template <class Extents, class Index, enable_if_t<is_integral_v<Index>, int> = 0>
CANN_ASC_STL_API constexpr auto submdspan_extents(const Extents& source, full_extent_t, Index)
{
    using result_extents = extents<typename Extents::index_type, Extents::static_extent(0)>;
    return result_extents(source.extent(0));
}

template <class Extents, class FirstIndex, class SecondIndex,
    enable_if_t<is_integral_v<FirstIndex> && is_integral_v<SecondIndex>, int> = 0>
CANN_ASC_STL_API constexpr auto submdspan_extents(const Extents&, FirstIndex, SecondIndex)
{
    return extents<typename Extents::index_type>{};
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_SUBMDSPAN_EXTENTS_H
