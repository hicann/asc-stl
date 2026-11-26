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

#ifndef CANN_ASC_STL_ASC_STD___LINALG_TRANSPOSED_H
#define CANN_ASC_STL_ASC_STD___LINALG_TRANSPOSED_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/array>
#include <asc/std/mdspan>

// Minimal inline equivalent of the <asc/std/__asc/assert.h> assertion chain,
// guarded with #ifndef against duplicate definitions:
// debug builds (_DEBUG/DEBUG) enable host assertions; the device side has no
// assertion mechanism and is always a no-op.
#ifndef CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#if defined(_DEBUG) || defined(DEBUG)
#define CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#endif  // defined(_DEBUG) || defined(DEBUG)
#endif  // !CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE

#ifndef ASC_ENABLE_ASSERTIONS
#ifdef CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#define ASC_ENABLE_ASSERTIONS
#endif  // CANN_ASC_STL_DETAIL_ENABLE_DEBUG_MODE
#endif  // !ASC_ENABLE_ASSERTIONS

#ifndef ASC_ENABLE_HOST_ASSERTIONS
#ifdef ASC_ENABLE_ASSERTIONS
#define ASC_ENABLE_HOST_ASSERTIONS
#endif  // ASC_ENABLE_ASSERTIONS
#endif  // !ASC_ENABLE_HOST_ASSERTIONS

#ifndef CANN_ASC_STL_DETAIL_ASSERT
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION()
// The ASC device side has no assertion mechanism
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#elif defined(ASC_ENABLE_HOST_ASSERTIONS)
#ifdef NDEBUG
// <assert.h> is not necessarily included under NDEBUG, so declare
// __assert_fail manually
extern "C" {
void __assert_fail(const char* __assertion, const char* __file, unsigned int __line, const char* __function) noexcept
    __attribute__((__noreturn__));
}  // extern "C"
#else
#include <assert.h>
#endif  // NDEBUG
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    __builtin_expect(static_cast<bool>(expression), 1) ? (void)0 : __assert_fail(message, __FILE__, __LINE__, __func__)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#endif  // ASC_ENABLE_HOST_ASSERTIONS
#endif  // !CANN_ASC_STL_DETAIL_ASSERT

namespace asc::std::linalg {

namespace __detail {

// Impose the rank == 2 constraint on the alias itself (SFINAE-friendly).
template <class Extents, enable_if_t<Extents::rank() == 2, int> = 0>
struct __transpose_extents_t_impl {
    using type = extents<typename Extents::index_type, Extents::static_extent(1), Extents::static_extent(0)>;
};

template <class Extents>
using __transpose_extents_t = typename __transpose_extents_t_impl<Extents>::type;

template <class Extents>
CANN_ASC_STL_API constexpr __transpose_extents_t<Extents> __transpose_extents(const Extents& e)
{
    static_assert(is_same_v<typename __transpose_extents_t<Extents>::index_type, typename Extents::index_type>,
        "Please fix __transpose_extents_t to account for P2553, which adds a template parameter SizeType to "
        "extents.");
    constexpr size_t ext0 = Extents::static_extent(0);
    constexpr size_t ext1 = Extents::static_extent(1);
    if constexpr (ext0 == dynamic_extent) {
        if constexpr (ext1 == dynamic_extent) {
            return __transpose_extents_t<Extents>{e.extent(1), e.extent(0)};
        } else {
            return __transpose_extents_t<Extents>{e.extent(0)};
        }
    } else {
        if constexpr (ext1 == dynamic_extent) {
            return __transpose_extents_t<Extents>{e.extent(1)};
        } else {
            return __transpose_extents_t<Extents>{};  // all extents are static
        }
    }
}

}  // namespace __detail

template <class Layout>
class layout_transpose {
public:
    using nested_layout_type = Layout;

    template <class Extents>
    class mapping {
    private:
        using nested_mapping_type = typename Layout::template mapping<__detail::__transpose_extents_t<Extents>>;

        static constexpr bool required_span_size_noexcept = noexcept(nested_mapping_type{}.required_span_size());

        static constexpr bool is_nested_unique_noexcept = noexcept(nested_mapping_type{}.is_unique());

        static constexpr bool is_exhaustive_noexcept = noexcept(nested_mapping_type{}.is_exhaustive());

        static constexpr bool is_strided_noexcept = noexcept(nested_mapping_type{}.is_strided());

    public:
        using extents_type = Extents;
        using index_type = typename extents_type::index_type;
        using size_type = typename extents_type::size_type;
        using rank_type = typename extents_type::rank_type;
        using layout_type = layout_transpose;

        CANN_ASC_STL_API constexpr explicit mapping(const nested_mapping_type& map)
            : nested_mapping_(map), extents_(__detail::__transpose_extents(map.extents()))
        {}

        CANN_ASC_STL_API constexpr const extents_type& extents() const noexcept
        {
            return extents_;
        }

        CANN_ASC_STL_API constexpr index_type required_span_size() const noexcept(required_span_size_noexcept)
        {
            return nested_mapping_.required_span_size();
        }

        template <class IndexType0, class IndexType1,
            enable_if_t<is_convertible_v<IndexType0, index_type> && is_convertible_v<IndexType1, index_type>, int> = 0>
        CANN_ASC_STL_API constexpr index_type operator()(IndexType0 i, IndexType1 j) const
        {
            return nested_mapping_(j, i);
        }

        CANN_ASC_STL_API constexpr const nested_mapping_type& nested_mapping() const noexcept
        {
            return nested_mapping_;
        }

        CANN_ASC_STL_API static constexpr bool is_always_unique() noexcept
        {
            return nested_mapping_type::is_always_unique();
        }

        CANN_ASC_STL_API static constexpr bool is_always_exhaustive() noexcept
        {
            return nested_mapping_type::is_always_exhaustive();
        }

        CANN_ASC_STL_API static constexpr bool is_always_strided() noexcept
        {
            return nested_mapping_type::is_always_strided();
        }

        CANN_ASC_STL_API constexpr bool is_unique() const noexcept(is_nested_unique_noexcept)
        {
            return nested_mapping_.is_unique();
        }

        CANN_ASC_STL_API constexpr bool is_exhaustive() const noexcept(is_exhaustive_noexcept)
        {
            return nested_mapping_.is_exhaustive();
        }

        CANN_ASC_STL_API constexpr bool is_strided() const noexcept(is_strided_noexcept)
        {
            return nested_mapping_.is_strided();
        }

        CANN_ASC_STL_API constexpr index_type stride(size_t r) const
        {
            CANN_ASC_STL_DETAIL_ASSERT(this->is_strided(), "layout must be strided");
            CANN_ASC_STL_DETAIL_ASSERT(r < extents_type::rank(), "rank must be less than extents rank");
            return nested_mapping_.stride(r == 0 ? 1 : 0);
        }

        template <class OtherExtents>
        CANN_ASC_STL_API friend constexpr bool operator==(const mapping& lhs, const mapping<OtherExtents>& rhs) noexcept
        {
            return lhs.nested_mapping() == rhs.nested_mapping();
        }

        template <class OtherExtents>
        CANN_ASC_STL_API friend constexpr bool operator!=(const mapping& lhs, const mapping<OtherExtents>& rhs) noexcept
        {
            return !(lhs == rhs);
        }

    private:
        nested_mapping_type nested_mapping_;
        extents_type extents_;
    };
};

namespace __detail {

template <class ElementType, class Accessor>
struct __transposed_element_accessor {
    using element_type = ElementType;
    using accessor_type = Accessor;

    CANN_ASC_STL_API static constexpr accessor_type __accessor(const Accessor& a)
    {
        return accessor_type(a);
    }
};

template <class ElementType>
struct __transposed_element_accessor<ElementType, default_accessor<ElementType>> {
    using element_type = ElementType;
    using accessor_type = default_accessor<element_type>;

    CANN_ASC_STL_API static constexpr accessor_type __accessor(const default_accessor<ElementType>& a)
    {
        return accessor_type(a);
    }
};

template <class Layout>
struct __transposed_layout {
    using layout_type = layout_transpose<Layout>;

    template <class OriginalMapping>
    CANN_ASC_STL_API static constexpr auto __mapping(const OriginalMapping& orig_map)
    {
        // Note: the nested mapping's public member is named extents_type and
        // layout_transpose's member class is named mapping (not the reserved
        // __extents_type/__mapping spellings); the latter would break custom or
        // padded layout paths with a compile error as soon as instantiated.
        using extents_type = __transpose_extents_t<typename OriginalMapping::extents_type>;
        using return_mapping_type = typename layout_type::template mapping<extents_type>;
        return return_mapping_type{orig_map};
    }
};

template <>
struct __transposed_layout<layout_left> {
    using layout_type = layout_right;

    template <class OriginalExtents>
    CANN_ASC_STL_API static constexpr auto __mapping(
        const typename layout_left::template mapping<OriginalExtents>& orig_map)
    {
        using original_mapping_type = typename layout_left::template mapping<OriginalExtents>;
        using extents_type = __transpose_extents_t<typename original_mapping_type::extents_type>;
        using return_mapping_type = typename layout_type::template mapping<extents_type>;
        return return_mapping_type{__transpose_extents(orig_map.extents())};
    }
};

template <>
struct __transposed_layout<layout_right> {
    using layout_type = layout_left;

    template <class OriginalExtents>
    CANN_ASC_STL_API static constexpr auto __mapping(
        const typename layout_right::template mapping<OriginalExtents>& orig_map)
    {
        using original_mapping_type = typename layout_right::template mapping<OriginalExtents>;
        using extents_type = __transpose_extents_t<typename original_mapping_type::extents_type>;
        using return_mapping_type = typename layout_type::template mapping<extents_type>;
        return return_mapping_type{__transpose_extents(orig_map.extents())};
    }
};

template <>
struct __transposed_layout<layout_stride> {
    using layout_type = layout_stride;

    template <class OriginalExtents>
    CANN_ASC_STL_API static constexpr auto __mapping(
        const typename layout_stride::template mapping<OriginalExtents>& orig_map)
    {
        using original_mapping_type = typename layout_stride::template mapping<OriginalExtents>;
        using original_extents_type = typename original_mapping_type::extents_type;
        using extents_type = __transpose_extents_t<original_extents_type>;
        using return_mapping_type = typename layout_type::template mapping<extents_type>;
        return return_mapping_type{__transpose_extents(orig_map.extents()),
            array<typename extents_type::index_type, OriginalExtents::rank()>{orig_map.stride(1), orig_map.stride(0)}};
    }
};

// Padded layouts could later get a dedicated optimization; for now they take
// the primary template's layout_transpose wrapper path.

template <class NestedLayout>
struct __transposed_layout<layout_transpose<NestedLayout>> {
    using layout_type = NestedLayout;

    // Unwrapping entry point: restores the transposed(transposed(m))
    // double-transpose round trip.
    template <class OriginalExtents>
    CANN_ASC_STL_API static constexpr auto __mapping(
        const typename layout_transpose<NestedLayout>::template mapping<OriginalExtents>& orig_map)
    {
        return orig_map.nested_mapping();
    }
};

}  // namespace __detail

template <class ElementType, class Extents, class Layout, class Accessor>
CANN_ASC_STL_API constexpr auto transposed(mdspan<ElementType, Extents, Layout, Accessor> a)
{
    using element_type = typename __detail::__transposed_element_accessor<ElementType, Accessor>::element_type;
    using layout_type = typename __detail::__transposed_layout<Layout>::layout_type;
    using accessor_type = typename __detail::__transposed_element_accessor<ElementType, Accessor>::accessor_type;
    auto mapping = __detail::__transposed_layout<Layout>::__mapping(a.mapping());
    auto accessor = __detail::__transposed_element_accessor<ElementType, Accessor>::__accessor(a.accessor());
    return mdspan<element_type, typename decltype(mapping)::extents_type, layout_type, accessor_type>{
        a.data_handle(), mapping, accessor};
}

}  // namespace asc::std::linalg

#endif  // CANN_ASC_STL_ASC_STD___LINALG_TRANSPOSED_H
