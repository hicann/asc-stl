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

#ifndef CANN_ASC_STL_ASC_STD___MDSPAN_SUBMDSPAN_MAPPING_H
#define CANN_ASC_STL_ASC_STD___MDSPAN_SUBMDSPAN_MAPPING_H

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
#include <asc/std/__mdspan/extents.h>
#include <asc/std/__mdspan/layout_left.h>
#include <asc/std/__mdspan/layout_right.h>
#include <asc/std/__mdspan/layout_stride.h>
#include <asc/std/__mdspan/mdspan.h>
#include <asc/std/__mdspan/submdspan_extents.h>
#include <asc/std/__mdspan/submdspan_helper.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/array>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Mapping>
struct submdspan_mapping_result {
    Mapping mapping;
    size_t offset;
};

template <class Mapping, class Pair, enable_if_t<__submdspan_pair_slice_v<Pair>, int> = 0>
CANN_ASC_STL_API constexpr auto submdspan_mapping(const Mapping& source, const Pair& first_slice, full_extent_t)
{
    using Extents = typename Mapping::extents_type;
    const auto result_extents = submdspan_extents(source.extents(), first_slice, full_extent);
    const typename Extents::index_type strides[2] = {source.stride(0), source.stride(1)};
    using result_extents_type = decltype(result_extents);
    using result_mapping = typename layout_stride::template mapping<result_extents_type>;
    return submdspan_mapping_result<result_mapping>{result_mapping(result_extents, strides),
        static_cast<size_t>(source(static_cast<size_t>(__submdspan_slice_first(first_slice)), 0))};
}

template <class Mapping, class Pair, enable_if_t<__submdspan_pair_slice_v<Pair>, int> = 0>
CANN_ASC_STL_API constexpr auto submdspan_mapping(const Mapping& source, full_extent_t, const Pair& second_slice)
{
    using Extents = typename Mapping::extents_type;
    const auto result_extents = submdspan_extents(source.extents(), full_extent, second_slice);
    const typename Extents::index_type strides[2] = {source.stride(0), source.stride(1)};
    using result_extents_type = decltype(result_extents);
    using result_mapping = typename layout_stride::template mapping<result_extents_type>;
    return submdspan_mapping_result<result_mapping>{result_mapping(result_extents, strides),
        static_cast<size_t>(source(0, static_cast<size_t>(__submdspan_slice_first(second_slice))))};
}

template <class Mapping, class Offset, class SliceExtent, class Stride>
CANN_ASC_STL_API constexpr auto submdspan_mapping(
    const Mapping& source, const strided_slice<Offset, SliceExtent, Stride>& first_slice, full_extent_t)
{
    using Extents = typename Mapping::extents_type;
    const auto result_extents = submdspan_extents(source.extents(), first_slice, full_extent);
    const typename Extents::index_type strides[2] = {
        static_cast<typename Extents::index_type>(source.stride(0) * first_slice.stride), source.stride(1)};
    using result_extents_type = decltype(result_extents);
    using result_mapping = typename layout_stride::template mapping<result_extents_type>;
    return submdspan_mapping_result<result_mapping>{result_mapping(result_extents, strides),
        static_cast<size_t>(source(static_cast<size_t>(first_slice.offset), 0))};
}

template <class Mapping, class Offset, class SliceExtent, class Stride>
CANN_ASC_STL_API constexpr auto submdspan_mapping(
    const Mapping& source, full_extent_t, const strided_slice<Offset, SliceExtent, Stride>& second_slice)
{
    using Extents = typename Mapping::extents_type;
    const auto result_extents = submdspan_extents(source.extents(), full_extent, second_slice);
    const typename Extents::index_type strides[2] = {
        source.stride(0), static_cast<typename Extents::index_type>(source.stride(1) * second_slice.stride)};
    using result_extents_type = decltype(result_extents);
    using result_mapping = typename layout_stride::template mapping<result_extents_type>;
    return submdspan_mapping_result<result_mapping>{result_mapping(result_extents, strides),
        static_cast<size_t>(source(0, static_cast<size_t>(second_slice.offset)))};
}

template <class Mapping>
CANN_ASC_STL_API constexpr auto submdspan_mapping(const Mapping& source, full_extent_t, full_extent_t)
{
    return submdspan_mapping_result<Mapping>{source, 0};
}

template <class Mapping, class Index, enable_if_t<is_integral_v<Index>, int> = 0>
CANN_ASC_STL_API constexpr auto submdspan_mapping(const Mapping& source, Index first_index, full_extent_t)
{
    using Extents = typename Mapping::extents_type;
    const auto result_extents = submdspan_extents(source.extents(), first_index, full_extent);
    const typename Extents::index_type strides[1] = {source.stride(1)};
    using result_extents_type = decltype(result_extents);
    using result_mapping = typename layout_stride::template mapping<result_extents_type>;
    return submdspan_mapping_result<result_mapping>{
        result_mapping(result_extents, strides), static_cast<size_t>(source(static_cast<size_t>(first_index), 0))};
}

template <class Mapping, class Index, enable_if_t<is_integral_v<Index>, int> = 0>
CANN_ASC_STL_API constexpr auto submdspan_mapping(const Mapping& source, full_extent_t, Index second_index)
{
    using Extents = typename Mapping::extents_type;
    const auto result_extents = submdspan_extents(source.extents(), full_extent, second_index);
    const typename Extents::index_type strides[1] = {source.stride(0)};
    using result_extents_type = decltype(result_extents);
    using result_mapping = typename layout_stride::template mapping<result_extents_type>;
    return submdspan_mapping_result<result_mapping>{
        result_mapping(result_extents, strides), static_cast<size_t>(source(0, static_cast<size_t>(second_index)))};
}

template <class Mapping, class FirstIndex, class SecondIndex,
    enable_if_t<is_integral_v<FirstIndex> && is_integral_v<SecondIndex>, int> = 0>
CANN_ASC_STL_API constexpr auto submdspan_mapping(
    const Mapping& source, FirstIndex first_index, SecondIndex second_index)
{
    using Extents = typename Mapping::extents_type;
    const auto result_extents = submdspan_extents(source.extents(), first_index, second_index);
    const typename Extents::index_type strides[1] = {1};
    using result_extents_type = decltype(result_extents);
    using result_mapping = typename layout_stride::template mapping<result_extents_type>;
    return submdspan_mapping_result<result_mapping>{result_mapping(result_extents, strides),
        static_cast<size_t>(source(static_cast<size_t>(first_index), static_cast<size_t>(second_index)))};
}

template <class Mapping>
CANN_ASC_STL_API constexpr auto submdspan_mapping(const Mapping& source)
{
    return submdspan_mapping_result<Mapping>{source, 0};
}

template <class Element, class Extents, class Layout, class Accessor, class... Slices>
CANN_ASC_STL_API constexpr auto submdspan(
    const mdspan<Element, Extents, Layout, Accessor>& source, const Slices&... slices)
{
    const auto result = submdspan_mapping(source.mapping(), slices...);
    using result_mapping = decltype(result.mapping);
    using result_extents = typename result_mapping::extents_type;
    using result_layout = typename result_mapping::layout_type;
    using result_accessor = typename Accessor::offset_policy;
    return mdspan<Element, result_extents, result_layout, result_accessor>(
        source.accessor().offset(source.data_handle(), result.offset), result.mapping,
        result_accessor(source.accessor()));
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_SUBMDSPAN_MAPPING_H
