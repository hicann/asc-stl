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

#ifndef CANN_ASC_STL_ASC_STD___FWD_MDSPAN_H
#define CANN_ASC_STL_ASC_STD___FWD_MDSPAN_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/void_t.h>
// No forward-declaration header for extents exists (extents is defined in
// __mdspan/extents.h), and this header's body does not reference extents, so
// such an include is deliberately not introduced.

CANN_ASC_STL_BEGIN_NAMESPACE

template <class ElementType>
struct default_accessor;
struct layout_left {
    template <class Extents>
    class mapping;
};
struct layout_right {
    template <class Extents>
    class mapping;
};
struct layout_stride {
    template <class Extents>
    class mapping;
};

template <class ElementType, class Extents, class LayoutPolicy = layout_right,
    class AccessorPolicy = default_accessor<ElementType>>
class mdspan;

template <class T>
inline constexpr bool __is_asc_std_mdspan_v = false;
template <class ElementType, class Extents, class LayoutPolicy, class AccessorPolicy>
inline constexpr bool __is_asc_std_mdspan_v<mdspan<ElementType, Extents, LayoutPolicy, AccessorPolicy>> = true;

// Layout-mapping detection traits: recognize mapping specializations of
// layout_left/layout_right. The __mdspan_detail::__is_valid_layout_mapping
// probe is intentionally not redefined here: __mdspan/mdspan.h already holds
// that definition in the same namespace, and duplicating it would clash when
// both headers are included.
template <class Layout>
inline constexpr bool __is_asc_std_layout_left_mapping_v = false;
template <class Extents>
inline constexpr bool __is_asc_std_layout_left_mapping_v<layout_left::mapping<Extents>> = true;

template <class Layout>
inline constexpr bool __is_asc_std_layout_right_mapping_v = false;
template <class Extents>
inline constexpr bool __is_asc_std_layout_right_mapping_v<layout_right::mapping<Extents>> = true;

template <class Layout>
inline constexpr bool __is_asc_std_layout_left_or_right_mapping_v =
    __is_asc_std_layout_left_mapping_v<Layout> || __is_asc_std_layout_right_mapping_v<Layout>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___FWD_MDSPAN_H
