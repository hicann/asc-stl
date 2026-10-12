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

#ifndef CANN_ASC_STL_ASC_STD___MDSPAN_SUBMDSPAN_HELPER_H
#define CANN_ASC_STL_ASC_STD___MDSPAN_SUBMDSPAN_HELPER_H

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
#include <asc/std/__tuple/tie.h>
#include <asc/std/__tuple/tuple_element.h>
#include <asc/std/__tuple/tuple_like.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/is_unsigned.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/type_list.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/tuple>

CANN_ASC_STL_BEGIN_NAMESPACE

// [mdspan.sub.overview]-2.5：切片序列到结果秩的映射。
template <class IndexType, class... SliceTypes>
CANN_ASC_STL_API constexpr array<size_t, sizeof...(SliceTypes)> __map_rank(size_t count = 0) noexcept
{
    return {(is_convertible_v<SliceTypes, IndexType> ? dynamic_extent : count++)...};
}

// index-pair-like 判定（合入源树为 concept，此处为 SFINAE 安全的变量模板形态，
// 基于 tuple_size/tuple_element 检测）。
template <class T, class IndexType, class = void>
struct __index_pair_like_impl : false_type {};
template <class T, class IndexType>
struct __index_pair_like_impl<T, IndexType,
    void_t<decltype(tuple_size<remove_cvref_t<T>>::value), tuple_element_t<0, remove_cvref_t<T>>,
        tuple_element_t<1, remove_cvref_t<T>>>>
    : bool_constant<__tuple_like_ext<remove_cvref_t<T>> && (tuple_size_v<remove_cvref_t<T>> == 2) &&
          is_convertible_v<tuple_element_t<0, remove_cvref_t<T>>, IndexType> &&
          is_convertible_v<tuple_element_t<1, remove_cvref_t<T>>, IndexType>> {};

template <class T, class IndexType>
inline constexpr bool __index_pair_like = __index_pair_like_impl<T, IndexType>::value;

// [mdspan.submdspan.strided.slice]
template <class OffsetType, class ExtentType, class StrideType>
struct strided_slice {
    using offset_type = OffsetType;
    using extent_type = ExtentType;
    using stride_type = StrideType;

    static_assert(is_signed_v<offset_type> || is_unsigned_v<offset_type> ||
            __mdspan_detail::__integral_constant_like_v<offset_type>,
        "[mdspan.submdspan.strided.slice] asc::std::strided_slice::offset_type must be signed or unsigned or "
        "integral-constant-like");
    static_assert(is_signed_v<extent_type> || is_unsigned_v<extent_type> ||
            __mdspan_detail::__integral_constant_like_v<extent_type>,
        "[mdspan.submdspan.strided.slice] asc::std::strided_slice::extent_type must be signed or unsigned or "
        "integral-constant-like");
    static_assert(is_signed_v<stride_type> || is_unsigned_v<stride_type> ||
            __mdspan_detail::__integral_constant_like_v<stride_type>,
        "[mdspan.submdspan.strided.slice] asc::std::strided_slice::stride_type must be signed or unsigned or "
        "integral-constant-like");

    CANN_ASC_STL_NO_UNIQUE_ADDRESS offset_type offset{};
    CANN_ASC_STL_NO_UNIQUE_ADDRESS extent_type extent{};
    CANN_ASC_STL_NO_UNIQUE_ADDRESS stride_type stride{};
};

template <class OffsetType, class ExtentType, class StrideType>
strided_slice(OffsetType, ExtentType, StrideType) -> strided_slice<OffsetType, ExtentType, StrideType>;

template <class T>
inline constexpr bool __is_strided_slice = false;

template <class OffsetType, class ExtentType, class StrideType>
inline constexpr bool __is_strided_slice<strided_slice<OffsetType, ExtentType, StrideType>> = true;

struct full_extent_t {
    explicit full_extent_t() = default;
};
inline constexpr full_extent_t full_extent{};

// [mdspan.submdspan.helpers]
template <class T, enable_if_t<!__mdspan_detail::__integral_constant_like_v<T>, int> = 0>
CANN_ASC_STL_API constexpr T __de_ice(T value) noexcept
{
    return value;
}

template <class T, enable_if_t<__mdspan_detail::__integral_constant_like_v<T>, int> = 0>
CANN_ASC_STL_API constexpr auto __de_ice(T) noexcept
{
    return T::value;
}

template <class IndexType, class From>
CANN_ASC_STL_API constexpr auto __index_cast(From&& from) noexcept
{
    if constexpr (is_integral_v<From> && !is_same_v<From, bool>) {
        return from;
    } else {
        return static_cast<IndexType>(from);
    }
}

template <size_t Index, class... Slices>
CANN_ASC_STL_API constexpr decltype(auto) __get_slice_at(Slices&&... slices) noexcept
{
    // 经 ADL 引入 ::asc::std::get 以支持宿主库类型。
    using ::asc::std::get;
    auto tuple_value =
        ::asc::std::forward_as_tuple(::asc::std::forward<Slices>(slices)...);  // NOLINT(build/include_what_you_use)
    return get<Index>(tuple_value);
}

template <size_t Index, class... Slices>
using __get_slice_type = __type_at_c<Index, __type_list<Slices...>>;

template <class IndexType, size_t Index, class... Slices>
CANN_ASC_STL_API constexpr IndexType __first_extent_from_slice(Slices... slices) noexcept
{
    static_assert(is_signed_v<IndexType> || is_unsigned_v<IndexType>,
        "[mdspan.sub.helpers] mandates IndexType to be a signed or unsigned integral");
    using slice_type = __get_slice_type<Index, Slices...>;
    [[maybe_unused]] slice_type& slice = ::asc::std::__get_slice_at<Index>(slices...);
    if constexpr (is_convertible_v<slice_type, IndexType>) {
        return ::asc::std::__index_cast<IndexType>(slice);
    } else {
        if constexpr (__index_pair_like<slice_type, IndexType>) {
            // 经 ADL 引入 ::asc::std::get 以支持宿主库类型。
            using ::asc::std::get;
            return ::asc::std::__index_cast<IndexType>(get<0>(slice));
        } else if constexpr (__is_strided_slice<slice_type>) {
            return ::asc::std::__index_cast<IndexType>(::asc::std::__de_ice(slice.offset));
        } else {
            return 0;
        }
    }
}

template <size_t Index, class Extents, class... Slices>
CANN_ASC_STL_API constexpr typename Extents::index_type __last_extent_from_slice(
    const Extents& source, Slices... slices) noexcept
{
    static_assert(__mdspan_detail::__is_asc_std_extents_v<Extents>,
        "[mdspan.sub.helpers] mandates Extents to be a specialization of extents");
    using index_type = typename Extents::index_type;
    using slice_type = __get_slice_type<Index, Slices...>;
    [[maybe_unused]] slice_type& slice = ::asc::std::__get_slice_at<Index>(slices...);
    if constexpr (is_convertible_v<slice_type, index_type>) {
        return ::asc::std::__index_cast<index_type>(::asc::std::__de_ice(slice) + 1);
    } else {
        if constexpr (__index_pair_like<slice_type, index_type>) {
            // 经 ADL 引入 ::asc::std::get 以支持宿主库类型。
            using ::asc::std::get;
            return ::asc::std::__index_cast<index_type>(get<1>(slice));
        } else if constexpr (__is_strided_slice<slice_type>) {
            return ::asc::std::__index_cast<index_type>(
                ::asc::std::__de_ice(slice.offset) * ::asc::std::__de_ice(slice.extent));
        } else {
            return ::asc::std::__index_cast<index_type>(source.extent(Index));
        }
    }
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_SUBMDSPAN_HELPER_H
