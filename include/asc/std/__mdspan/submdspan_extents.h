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
#include <asc/std/__mdspan/empty_base.h>
#include <asc/std/__mdspan/extents.h>
#include <asc/std/__mdspan/submdspan_helper.h>
#include <asc/std/__tuple/tuple_like.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/is_unsigned.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/array>
#include <asc/std/tuple>

CANN_ASC_STL_BEGIN_NAMESPACE

// 过滤出"不可转换为 index_type"（即会贡献结果 extent）的切片下标序列。
template <class IndexType, class... Slices, size_t... FilteredIndices>
CANN_ASC_STL_API constexpr auto __filter_slices_convertible_to_index(
    index_sequence<FilteredIndices...>, index_sequence<>) noexcept
{
    return index_sequence<FilteredIndices...>{};
}

template <class IndexType, class... Slices, size_t... SliceIndices, size_t CurrentIndex, size_t... Remaining>
CANN_ASC_STL_API constexpr auto __filter_slices_convertible_to_index(
    index_sequence<SliceIndices...>, index_sequence<CurrentIndex, Remaining...>) noexcept
{
    using slice_type = __get_slice_type<CurrentIndex, Slices...>;
    if constexpr (is_convertible_v<slice_type, IndexType>) {
        return ::asc::std::__filter_slices_convertible_to_index<IndexType, Slices...>(
            index_sequence<SliceIndices...>{}, index_sequence<Remaining...>{});
    } else {
        return ::asc::std::__filter_slices_convertible_to_index<IndexType, Slices...>(
            index_sequence<SliceIndices..., CurrentIndex>{}, index_sequence<Remaining...>{});
    }
}

// [mdspan.sub.extents-4.2.2]：index-pair-like 且两端为整型常量。
template <class Extents, class SliceType, class = void>
struct __subextents_is_index_pair_impl : false_type {};

template <class Extents, class SliceType>
struct __subextents_is_index_pair_impl<Extents, SliceType,
    void_t<tuple_element_t<0, remove_cv_t<SliceType>>, tuple_element_t<1, remove_cv_t<SliceType>>>>
    : bool_constant<__index_pair_like<SliceType, typename Extents::index_type> &&
          __mdspan_detail::__integral_constant_like_v<tuple_element_t<0, remove_cv_t<SliceType>>> &&
          __mdspan_detail::__integral_constant_like_v<tuple_element_t<1, remove_cv_t<SliceType>>>> {};

template <class Extents, class SliceType>
inline constexpr bool __subextents_is_index_pair = __subextents_is_index_pair_impl<Extents, SliceType>::value;

// [mdspan.sub.extents-4.2.3]：整型常量 extent 为 0 的 strided_slice。
template <class Extents, class SliceType, class = void>
struct __subextents_is_strided_slice_zero_extent_impl : false_type {};

template <class Extents, class SliceType>
struct __subextents_is_strided_slice_zero_extent_impl<Extents, SliceType,
    void_t<typename remove_cv_t<SliceType>::extent_type,
        integral_constant<decltype(remove_cv_t<SliceType>::extent_type::value),
            remove_cv_t<SliceType>::extent_type::value>>>
    : bool_constant<__is_strided_slice<remove_cv_t<SliceType>> &&
          __mdspan_detail::__integral_constant_like_v<typename remove_cv_t<SliceType>::extent_type> &&
          (remove_cv_t<SliceType>::extent_type::value == 0)> {};

template <class Extents, class SliceType>
inline constexpr bool __subextents_is_strided_slice_zero_extent =
    __subextents_is_strided_slice_zero_extent_impl<Extents, SliceType>::value;

// [mdspan.sub.extents-4.2.4]：extent/stride 均为整型常量的 strided_slice。
template <class SliceType, class = void>
struct __subextents_is_strided_slice_impl : false_type {};

template <class SliceType>
struct __subextents_is_strided_slice_impl<SliceType,
    void_t<typename remove_cv_t<SliceType>::extent_type, typename remove_cv_t<SliceType>::stride_type>>
    : bool_constant<__is_strided_slice<remove_cv_t<SliceType>> &&
          __mdspan_detail::__integral_constant_like_v<typename remove_cv_t<SliceType>::extent_type> &&
          __mdspan_detail::__integral_constant_like_v<typename remove_cv_t<SliceType>::stride_type>> {};

template <class SliceType>
inline constexpr bool __subextents_is_strided_slice = __subextents_is_strided_slice_impl<SliceType>::value;

struct __get_subextent {
    // [mdspan.sub.extents-4.2.1]-[mdspan.sub.extents-4.2.5]
    template <class Extents, size_t SliceIndex, class SliceType>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr size_t __get_static_subextents() noexcept
    {
        // [mdspan.sub.extents-4.2.1]-[mdspan.sub.extents-4.2.5]
        if constexpr (is_convertible_v<SliceType, full_extent_t>) {
            return Extents::static_extent(SliceIndex);
        } else if constexpr (__subextents_is_index_pair<Extents, SliceType>) {  // 4.2.2
            return ::asc::std::__de_ice(tuple_element_t<1, remove_cv_t<SliceType>>()) -
                ::asc::std::__de_ice(tuple_element_t<0, remove_cv_t<SliceType>>());
        } else if constexpr (__subextents_is_strided_slice_zero_extent<Extents, SliceType>) {  // 4.2.3
            return 0;
        } else if constexpr (__subextents_is_strided_slice<SliceType>) {  // 4.2.4
            return 1 +
                (::asc::std::__de_ice(typename remove_cv_t<SliceType>::extent_type()) - 1) /
                ::asc::std::__de_ice(typename remove_cv_t<SliceType>::stride_type());
        } else {
            return dynamic_extent;  // 4.2.5
        }
    }

    // [mdspan.sub.extents-5.1]-[mdspan.sub.extents-5.2]
    template <size_t SliceIndex, class Extents, class... Slices>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr typename Extents::index_type __get_dynamic_subextents(
        const Extents& source, Slices... slices) noexcept
    {
        using slice_type = __get_slice_type<SliceIndex, Slices...>;
        // [mdspan.sub.extents-5.1]-[mdspan.sub.extents-5.2]
        if constexpr (__is_strided_slice<remove_cv_t<slice_type>>) {
            slice_type& slice = ::asc::std::__get_slice_at<SliceIndex>(slices...);
            return slice.extent == 0 ?
                0 :
                1 + (::asc::std::__de_ice(slice.extent) - 1) / ::asc::std::__de_ice(slice.stride);
        } else {
            return ::asc::std::__last_extent_from_slice<SliceIndex>(source, slices...) -
                ::asc::std::__first_extent_from_slice<typename Extents::index_type, SliceIndex>(slices...);
        }
    }

    template <class Extents, class... Slices, size_t... SliceIndices>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API static constexpr auto __impl(
        index_sequence<SliceIndices...>, const Extents& source, Slices... slices) noexcept
    {
        using index_type = typename Extents::index_type;
        using sub_extents = extents<index_type,
            __get_static_subextents<Extents, SliceIndices, __get_slice_type<SliceIndices, Slices...>>()...>;
        return sub_extents{__get_dynamic_subextents<SliceIndices>(source, slices...)...};
    }

    template <class Extents, class... Slices>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr auto operator()(const Extents& source, Slices... slices) noexcept
    {
        const auto filtered_indices =
            ::asc::std::__filter_slices_convertible_to_index<typename Extents::index_type, Slices...>(
                index_sequence<>{}, index_sequence_for<Slices...>());
        return __impl(filtered_indices, source, slices...);
    }
};

template <class IndexType, class SliceType>
inline constexpr bool __is_valid_subextents =
    is_convertible_v<SliceType, IndexType> || __index_pair_like<SliceType, IndexType> ||
    is_convertible_v<SliceType, full_extent_t> || __is_strided_slice<remove_cv_t<SliceType>>;

// [mdspan.sub.extents]
template <class Extents, class... Slices, enable_if_t<(Extents::rank() == sizeof...(Slices)), int> = 0>
CANN_ASC_STL_API constexpr auto submdspan_extents(const Extents& source, Slices... slices)
{
    static_assert(((__is_valid_subextents<typename Extents::index_type, Slices>) && ... && true),
        "[mdspan.sub.extents] For each rank index k of src.extents(), exactly one of the following is true:");
    return __get_subextent{}(source, slices...);
}

template <class Extents, class... Slices>
using __get_subextents_t =
    decltype(::asc::std::submdspan_extents(::asc::std::declval<Extents>(), ::asc::std::declval<Slices>()...));

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_SUBMDSPAN_EXTENTS_H
