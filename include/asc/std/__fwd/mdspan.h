/*
 * Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

#ifndef CANN_ASC_STL_STD_DETAIL_FWD_MDSPAN_H
#define CANN_ASC_STL_STD_DETAIL_FWD_MDSPAN_H

#include <asc/std/detail/__config>

#include <asc/std/__fwd/extents.h>
#include <asc/std/__type_traits/void_t.h>

CANN_ASC_STL_DETAIL_ACCL_BEGIN_NAMESPACE_ASC_STD

template <class _ElementType>
struct default_accessor;

struct layout_left {
    template <class _Extents>
    class mapping;
};
struct layout_right {
    template <class _Extents>
    class mapping;
};
struct layout_stride {
    template <class _Extents>
    class mapping;
};

namespace __mdspan_detail {
template <class _Layout, class _Extents, class = void>
inline constexpr bool __is_valid_layout_mapping = false;
template <class _Layout, class _Extents>
inline constexpr bool
    __is_valid_layout_mapping<_Layout, _Extents, void_t<typename _Layout::template mapping<_Extents>>> = true;
}  // namespace __mdspan_detail

template <class _ElementType, class _Extents, class _LayoutPolicy = layout_right,
    class _AccessorPolicy = default_accessor<_ElementType>>
class mdspan;

template <class _Tp>
inline constexpr bool __is_asc_std_mdspan_v = false;
template <class _ElementType, class _Extents, class _LayoutPolicy, class _AccessorPolicy>
inline constexpr bool __is_asc_std_mdspan_v<mdspan<_ElementType, _Extents, _LayoutPolicy, _AccessorPolicy>> = true;

template <typename _Layout>
inline constexpr bool __is_asc_std_layout_left_mapping_v = false;
template <typename _Extents>
inline constexpr bool __is_asc_std_layout_left_mapping_v<layout_left::mapping<_Extents>> = true;

template <typename _Layout>
inline constexpr bool __is_asc_std_layout_right_mapping_v = false;
template <typename _Extents>
inline constexpr bool __is_asc_std_layout_right_mapping_v<layout_right::mapping<_Extents>> = true;

template <typename _Layout>
inline constexpr bool __is_asc_std_layout_left_or_right_mapping_v =
    __is_asc_std_layout_left_mapping_v<_Layout> || __is_asc_std_layout_right_mapping_v<_Layout>;

CANN_ASC_STL_DETAIL_ACCL_END_NAMESPACE_ASC_STD

#endif  // CANN_ASC_STL_STD_DETAIL_FWD_MDSPAN_H
