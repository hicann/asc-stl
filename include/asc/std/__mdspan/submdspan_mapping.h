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
#include <asc/std/__mdspan/empty_base.h>
#include <asc/std/__mdspan/extents.h>
#include <asc/std/__mdspan/layout_left.h>
#include <asc/std/__mdspan/layout_right.h>
#include <asc/std/__mdspan/layout_stride.h>
#include <asc/std/__mdspan/mdspan.h>
#include <asc/std/__mdspan/submdspan_extents.h>
#include <asc/std/__mdspan/submdspan_helper.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_copy_assignable.h>
#include <asc/std/__type_traits/is_copy_constructible.h>
#include <asc/std/__type_traits/is_move_assignable.h>
#include <asc/std/__type_traits/is_nothrow_move_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__type_traits/remove_const.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/array>
#include <asc/std/cstddef>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __mdspan_detail {

// [mdspan.sub.extents]：切片序列到子 extents 的变参计算（合入源树位于
// submdspan_extents.h 公开重载，基座该头仅有 rank-2 定式重载且不在本批合入
// 范围，故内联等价实现于内部命名空间，不与基座公开重载产生交集）。

// 取出"不可转换为 index_type"（即会贡献结果 extent）的切片下标序列。
template <class IndexType, class... Slices, size_t... FilteredIndices>
CANN_ASC_STL_API constexpr auto __filter_slices_convertible_to_index(
    ::asc::std::index_sequence<FilteredIndices...>, ::asc::std::index_sequence<>) noexcept
{
    return ::asc::std::index_sequence<FilteredIndices...>{};
}

template <class IndexType, class... Slices, size_t... SliceIndices, size_t CurrentIndex, size_t... Remaining>
CANN_ASC_STL_API constexpr auto __filter_slices_convertible_to_index(
    ::asc::std::index_sequence<SliceIndices...>, ::asc::std::index_sequence<CurrentIndex, Remaining...>) noexcept
{
    using slice_type = __get_slice_type<CurrentIndex, Slices...>;
    if constexpr (is_convertible_v<slice_type, IndexType>) {
        return ::asc::std::__mdspan_detail::__filter_slices_convertible_to_index<IndexType, Slices...>(
            ::asc::std::index_sequence<SliceIndices...>{}, ::asc::std::index_sequence<Remaining...>{});
    } else {
        return ::asc::std::__mdspan_detail::__filter_slices_convertible_to_index<IndexType, Slices...>(
            ::asc::std::index_sequence<SliceIndices..., CurrentIndex>{}, ::asc::std::index_sequence<Remaining...>{});
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

struct __subextents_impl {
    // [mdspan.sub.extents-4.2.1]-[mdspan.sub.extents-4.2.5]
    template <class Extents, size_t SliceIndex, class SliceType>
    CANN_ASC_STL_API static constexpr size_t __get_static_subextents() noexcept
    {
        if constexpr (is_convertible_v<SliceType, full_extent_t>) {
            return Extents::static_extent(SliceIndex);
        } else if constexpr (__subextents_is_index_pair<Extents, SliceType>) {
            return ::asc::std::__de_ice(tuple_element_t<1, remove_cv_t<SliceType>>()) -
                ::asc::std::__de_ice(tuple_element_t<0, remove_cv_t<SliceType>>());
        } else if constexpr (__subextents_is_strided_slice_zero_extent<Extents, SliceType>) {
            return 0;
        } else if constexpr (__subextents_is_strided_slice<SliceType>) {
            return 1 +
                (::asc::std::__de_ice(typename remove_cv_t<SliceType>::extent_type()) - 1) /
                ::asc::std::__de_ice(typename remove_cv_t<SliceType>::stride_type());
        } else {
            return dynamic_extent;
        }
    }

    // [mdspan.sub.extents-5.1]-[mdspan.sub.extents-5.2]
    template <size_t SliceIndex, class Extents, class... Slices>
    CANN_ASC_STL_API static constexpr typename Extents::index_type __get_dynamic_subextents(
        const Extents& source, Slices... slices) noexcept
    {
        using slice_type = __get_slice_type<SliceIndex, Slices...>;
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
    CANN_ASC_STL_API static constexpr auto __impl(
        ::asc::std::index_sequence<SliceIndices...>, const Extents& source, Slices... slices) noexcept
    {
        using index_type = typename Extents::index_type;
        using sub_extents = extents<index_type,
            __get_static_subextents<Extents, SliceIndices, __get_slice_type<SliceIndices, Slices...>>()...>;
        return sub_extents{__get_dynamic_subextents<SliceIndices>(source, slices...)...};
    }

    template <class Extents, class... Slices>
    CANN_ASC_STL_API constexpr auto operator()(const Extents& source, Slices... slices) noexcept
    {
        const auto filtered_indices =
            ::asc::std::__mdspan_detail::__filter_slices_convertible_to_index<typename Extents::index_type, Slices...>(
                ::asc::std::index_sequence<>{}, ::asc::std::index_sequence_for<Slices...>());
        return __impl(filtered_indices, source, slices...);
    }
};

// 变参子 extents 计算（等价于合入源树的 submdspan_extents 变参重载）。
template <class Extents, class... Slices>
CANN_ASC_STL_API constexpr auto __subextents_of(const Extents& source, Slices... slices) noexcept
{
    return __subextents_impl{}(source, slices...);
}

template <class Extents, class... Slices>
using __get_subextents_t = decltype(::asc::std::__mdspan_detail::__subextents_of(
    ::asc::std::declval<Extents>(), ::asc::std::declval<Slices>()...));

// [mdspan.submdspan.submdspan.mapping.result] 的 layout mapping 要求判定
// （合入源树为 concept，此处为 SFINAE 安全的变量模板近似）。
template <class Mapping, class = void>
struct __layout_mapping_req_impl : false_type {};
template <class Mapping>
struct __layout_mapping_req_impl<Mapping,
    void_t<typename Mapping::extents_type, typename Mapping::index_type, typename Mapping::rank_type,
        typename Mapping::layout_type, decltype(::asc::std::declval<const Mapping&>().extents()),
        decltype(::asc::std::declval<const Mapping&>().required_span_size()),
        decltype(::asc::std::declval<const Mapping&>().is_unique()),
        decltype(::asc::std::declval<const Mapping&>().is_exhaustive()),
        decltype(::asc::std::declval<const Mapping&>().is_strided()),
        decltype(::asc::std::declval<const Mapping&>() == ::asc::std::declval<const Mapping&>())>>
    : bool_constant<is_copy_constructible_v<Mapping> && is_copy_assignable_v<Mapping> &&
          is_nothrow_move_constructible_v<Mapping> && is_move_assignable_v<Mapping> &&
          is_nothrow_swappable_v<Mapping> && __mdspan_detail::__is_asc_std_extents_v<typename Mapping::extents_type> &&
          is_same_v<typename Mapping::index_type, typename Mapping::extents_type::index_type> &&
          is_same_v<typename Mapping::rank_type, typename Mapping::extents_type::rank_type> &&
          __mdspan_detail::__is_mapping_of<typename Mapping::layout_type, Mapping> &&
          is_same_v<decltype(::asc::std::declval<const Mapping&>().extents()), const typename Mapping::extents_type&> &&
          is_same_v<decltype(::asc::std::declval<const Mapping&>().required_span_size()),
              typename Mapping::index_type>> {};

template <class Mapping>
inline constexpr bool __layout_mapping_req = __layout_mapping_req_impl<Mapping>::value;

}  // namespace __mdspan_detail

// [mdspan.sub.map]

// [mdspan.submdspan.submdspan.mapping.result]
template <class Mapping>
struct submdspan_mapping_result {
    static_assert(__mdspan_detail::__layout_mapping_req<Mapping>,
        "[mdspan.submdspan.submdspan.mapping.result] shall meet the layout mapping requirements");

    CANN_ASC_STL_NO_UNIQUE_ADDRESS Mapping mapping{};
    size_t offset{};
};

// [mdspan.sub.map.common]
// mdspan.sub.map.common-2
template <class Extents, class... Slices>
inline constexpr bool __matching_number_of_slices = sizeof...(Slices) == Extents::rank();

template <size_t SliceIndex, class LayoutMapping, class... Slices>
CANN_ASC_STL_API constexpr auto __get_submdspan_strides(const LayoutMapping& mapping, Slices... slices) noexcept
{
    using slice_type = __get_slice_type<SliceIndex, Slices...>;
    using extents_type = typename LayoutMapping::extents_type;
    using index_type = typename extents_type::index_type;
    if constexpr (__is_strided_slice<remove_cv_t<slice_type>>) {
        slice_type& slice = ::asc::std::__get_slice_at<SliceIndex>(slices...);
        using unsigned_stride = make_unsigned_t<typename slice_type::stride_type>;
        using unsigned_extent = make_unsigned_t<typename slice_type::extent_type>;
        return static_cast<index_type>(mapping.stride(SliceIndex) *
            (static_cast<unsigned_stride>(slice.stride) < static_cast<unsigned_extent>(slice.extent) ?
                    ::asc::std::__de_ice(slice.stride) :
                    1));
    } else {
        return static_cast<index_type>(mapping.stride(SliceIndex));
    }
}

template <class LayoutMapping, class... Slices, size_t... SliceIndices>
CANN_ASC_STL_API constexpr auto __submdspan_strides(
    ::asc::std::index_sequence<SliceIndices...>, const LayoutMapping& mapping, Slices... slices) noexcept
{
    using extents_type = typename LayoutMapping::extents_type;
    using index_type = typename extents_type::index_type;
    using sub_extents = __mdspan_detail::__get_subextents_t<extents_type, Slices...>;
    return array<index_type, sub_extents::rank()>{
        ::asc::std::__get_submdspan_strides<SliceIndices>(mapping, slices...)...};
}

template <class LayoutMapping, class... Slices,
    enable_if_t<__matching_number_of_slices<typename LayoutMapping::extents_type, Slices...>, int> = 0>
CANN_ASC_STL_API constexpr auto __submdspan_strides(const LayoutMapping& mapping, Slices... slices) noexcept
{
    using extents_type = typename LayoutMapping::extents_type;
    using index_type = typename extents_type::index_type;
    const auto filtered_indices =
        ::asc::std::__mdspan_detail::__filter_slices_convertible_to_index<index_type, Slices...>(
            ::asc::std::index_sequence<>{}, ::asc::std::index_sequence_for<Slices...>());
    return ::asc::std::__submdspan_strides(filtered_indices, mapping, slices...);
}

// [mdspan.sub.map.common-8]
template <class LayoutMapping, class... Slices, size_t... SliceIndices>
CANN_ASC_STL_API constexpr size_t __submdspan_offset(
    ::asc::std::index_sequence<SliceIndices...>, const LayoutMapping& mapping, Slices... slices) noexcept
{
    using extents_type = typename LayoutMapping::extents_type;
    using index_type = typename extents_type::index_type;
    // first_<index_type, k>(slices...) 的值
    const array<index_type, extents_type::rank()> offsets = {
        ::asc::std::__first_extent_from_slice<index_type, SliceIndices>(slices...)...};

    for (size_t index = 0; index != extents_type::rank(); ++index) {
        // 若任一 first_<index_type, k>(slices...) 等于 extents().extent(k)，
        // 则 offset 为 (*this).required_span_size()
        if (offsets[index] == mapping.extents().extent(index)) {
            return static_cast<size_t>(mapping.required_span_size());
        }
    }
    // 否则 offset 为 (*this)(first_<index_type, P>(slices...)...)
    return static_cast<size_t>(mapping(offsets[SliceIndices]...));
}

template <class LayoutMapping, class... Slices,
    enable_if_t<__matching_number_of_slices<typename LayoutMapping::extents_type, Slices...>, int> = 0>
CANN_ASC_STL_API constexpr size_t __submdspan_offset(const LayoutMapping& mapping, Slices... slices) noexcept
{
    return ::asc::std::__submdspan_offset(::asc::std::index_sequence_for<Slices...>(), mapping, slices...);
}

// [mdspan.sub.map.common-9]
// [mdspan.sub.map.common-9.1]
template <class SliceType, class = void>
struct __is_strided_slice_stride_of_one_impl : false_type {};
template <class SliceType>
struct __is_strided_slice_stride_of_one_impl<SliceType,
    void_t<typename SliceType::stride_type, decltype(SliceType::stride_type::value)>>
    : bool_constant<__is_strided_slice<remove_cv_t<SliceType>> &&
          __mdspan_detail::__integral_constant_like_v<typename SliceType::stride_type> &&
          (SliceType::stride_type::value == 1)> {};

template <class SliceType>
inline constexpr bool __is_strided_slice_stride_of_one = __is_strided_slice_stride_of_one_impl<SliceType>::value;

template <class LayoutMapping, class SliceType>
CANN_ASC_STL_API constexpr bool __is_unit_stride_slice()
{
    // [mdspan.sub.map.common-9.1]
    if constexpr (__is_strided_slice_stride_of_one<SliceType>) {
        return true;
    } else if constexpr (__index_pair_like<SliceType, typename LayoutMapping::index_type>) {
        // [mdspan.sub.map.common-9.2]
        return true;
    } else if constexpr (is_convertible_v<SliceType, full_extent_t>) {
        // [mdspan.sub.map.common-9.3]
        return true;
    } else {
        return false;
    }
}

// [mdspan.sub.map.left]
template <class LayoutMapping, class SubExtents, class... Slices>
CANN_ASC_STL_API constexpr bool __can_layout_left()
{
    if constexpr (SubExtents::rank() == 0) {
        return true;
    } else {
        constexpr bool indexed[] = {is_convertible_v<Slices, typename LayoutMapping::index_type>...};
        constexpr bool full[] = {is_convertible_v<Slices, full_extent_t>...};
        constexpr bool unit[] = {::asc::std::__is_unit_stride_slice<LayoutMapping, Slices>()...};
        size_t last = sizeof...(Slices);
        while (last != 0 && indexed[last - 1]) {
            --last;
        }
        if (last == 0 || !unit[last - 1]) {
            return false;
        }
        for (size_t index = 0; index + 1 < last; ++index) {
            if (!full[index]) {
                return false;
            }
        }
        return true;
    }
}

template <class Extents, class... Slices, enable_if_t<__matching_number_of_slices<Extents, Slices...>, int> = 0>
CANN_ASC_STL_API constexpr auto __submdspan_mapping_impl(
    const typename layout_left::mapping<Extents>& mapping, Slices... slices)
{
    // [mdspan.sub.map.left-1.1]
    if constexpr (Extents::rank() == 0) {
        return submdspan_mapping_result{mapping, 0};
    } else {
        // [mdspan.sub.map.left-1.2]
        // [mdspan.sub.map.left-1.3]
        using sub_extents = __mdspan_detail::__get_subextents_t<Extents, Slices...>;
        const auto sub_ext = ::asc::std::__mdspan_detail::__subextents_of(mapping.extents(), slices...);
        const auto offset = ::asc::std::__submdspan_offset(mapping, slices...);
        if constexpr (::asc::std::__can_layout_left<typename layout_left::mapping<Extents>, sub_extents, Slices...>()) {
            using sub_mapping_t = layout_left::template mapping<sub_extents>;
            return submdspan_mapping_result<sub_mapping_t>{sub_mapping_t{sub_ext}, offset};
        } else {
            // [mdspan.sub.map.left-1.4]
            // TODO: 实现填充布局（padded layouts）
            // [mdspan.sub.map.left-1.5]
            using sub_mapping_t = layout_stride::template mapping<sub_extents>;
            const auto sub_strides = ::asc::std::__submdspan_strides(mapping, slices...);
            return submdspan_mapping_result<sub_mapping_t>{sub_mapping_t{sub_ext, sub_strides}, offset};
        }
    }
}

// [mdspan.sub.map.right]
template <class LayoutMapping, class SubExtents, class... Slices>
CANN_ASC_STL_API constexpr bool __can_layout_right()
{
    if constexpr (SubExtents::rank() == 0) {
        return true;
    } else {
        constexpr bool indexed[] = {is_convertible_v<Slices, typename LayoutMapping::index_type>...};
        constexpr bool full[] = {is_convertible_v<Slices, full_extent_t>...};
        constexpr bool unit[] = {::asc::std::__is_unit_stride_slice<LayoutMapping, Slices>()...};
        size_t first = 0;
        while (first != sizeof...(Slices) && indexed[first]) {
            ++first;
        }
        if (first == sizeof...(Slices) || !unit[first]) {
            return false;
        }
        for (size_t index = first + 1; index < sizeof...(Slices); ++index) {
            if (!full[index]) {
                return false;
            }
        }
        return true;
    }
}

template <class Extents, class... Slices, enable_if_t<__matching_number_of_slices<Extents, Slices...>, int> = 0>
CANN_ASC_STL_API constexpr auto __submdspan_mapping_impl(
    const typename layout_right::mapping<Extents>& mapping, Slices... slices)
{
    // [mdspan.sub.map.right-1.1]
    if constexpr (Extents::rank() == 0) {
        return submdspan_mapping_result{mapping, 0};
    } else {
        // [mdspan.sub.map.right-1.2]
        // [mdspan.sub.map.right-1.3]
        using sub_extents = __mdspan_detail::__get_subextents_t<Extents, Slices...>;
        const auto sub_ext = ::asc::std::__mdspan_detail::__subextents_of(mapping.extents(), slices...);
        const auto offset = ::asc::std::__submdspan_offset(mapping, slices...);
        if constexpr (::asc::std::__can_layout_right<typename layout_right::mapping<Extents>, sub_extents,
                          Slices...>()) {
            using sub_mapping_t = layout_right::template mapping<sub_extents>;
            return submdspan_mapping_result<sub_mapping_t>{sub_mapping_t{sub_ext}, offset};
        } else {
            // [mdspan.sub.map.right-1.4]
            // TODO: 实现填充布局（padded layouts）
            // [mdspan.sub.map.right-1.5]
            using sub_mapping_t = layout_stride::template mapping<sub_extents>;
            const auto sub_strides = ::asc::std::__submdspan_strides(mapping, slices...);
            return submdspan_mapping_result<sub_mapping_t>{sub_mapping_t{sub_ext, sub_strides}, offset};
        }
    }
}

template <class Extents, class... Slices, enable_if_t<__matching_number_of_slices<Extents, Slices...>, int> = 0>
CANN_ASC_STL_API constexpr auto __submdspan_mapping_impl(
    const typename layout_stride::mapping<Extents>& mapping, Slices... slices)
{
    // [mdspan.sub.map.stride-1.1]
    if constexpr (Extents::rank() == 0) {
        return submdspan_mapping_result{mapping, 0};
    } else {
        // [mdspan.sub.map.stride-1.2]
        using sub_extents = __mdspan_detail::__get_subextents_t<Extents, Slices...>;
        using sub_mapping_t = layout_stride::template mapping<sub_extents>;
        const auto sub_ext = ::asc::std::__mdspan_detail::__subextents_of(mapping.extents(), slices...);
        const auto offset = ::asc::std::__submdspan_offset(mapping, slices...);
        const auto sub_strides = ::asc::std::__submdspan_strides(mapping, slices...);
        return submdspan_mapping_result<sub_mapping_t>{sub_mapping_t{sub_ext, sub_strides}, offset};
    }
}

template <class LayoutMapping, class... Slices,
    enable_if_t<__matching_number_of_slices<typename LayoutMapping::extents_type, Slices...>, int> = 0>
CANN_ASC_STL_API constexpr auto submdspan_mapping(const LayoutMapping& mapping, Slices... slices)
{
    return ::asc::std::__submdspan_mapping_impl(mapping, slices...);
}

// [mdspan.sub.sub]
template <class AlwaysVoid, class LayoutMapping, class... Slices>
struct __can_submdspan_mapping_impl : false_type {};
template <class LayoutMapping, class... Slices>
struct __can_submdspan_mapping_impl<
    void_t<decltype(::asc::std::submdspan_mapping(
        ::asc::std::declval<const LayoutMapping&>(), ::asc::std::declval<Slices>()...))>,
    LayoutMapping, Slices...> : true_type {};

template <class LayoutMapping, class... Slices>
inline constexpr bool __can_submdspan_mapping = __can_submdspan_mapping_impl<void, LayoutMapping, Slices...>::value;

template <class T, class Extents, class Layout, class Accessor, class... Slices,
    enable_if_t<__matching_number_of_slices<Extents, Slices...> &&
            __can_submdspan_mapping<typename Layout::template mapping<Extents>, Slices...>,
        int> = 0>
CANN_ASC_STL_API constexpr auto submdspan(const mdspan<T, Extents, Layout, Accessor>& source, Slices... slices)
{
    auto sub_map_result = ::asc::std::submdspan_mapping(source.mapping(), slices...);
    // 纯 SIMT 编译把未标注的推导指引按宿主函数处理，设备侧无法经 CTAD 命中，
    // 故显式拼出指引本应推导出的类型。
    using sub_mapping_t = ::asc::std::remove_cvref_t<decltype(sub_map_result.mapping)>;
    return mdspan<T, typename sub_mapping_t::extents_type, typename sub_mapping_t::layout_type,
        typename Accessor::offset_policy>(source.accessor().offset(source.data_handle(), sub_map_result.offset),
        sub_map_result.mapping, typename Accessor::offset_policy(source.accessor()));
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_SUBMDSPAN_MAPPING_H
