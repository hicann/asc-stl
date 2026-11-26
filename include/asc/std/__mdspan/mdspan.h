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

#ifndef CANN_ASC_STL_ASC_STD___MDSPAN_MDSPAN_H
#define CANN_ASC_STL_ASC_STD___MDSPAN_MDSPAN_H

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
#include <asc/std/__mdspan/default_accessor.h>
#include <asc/std/__mdspan/empty_base.h>
#include <asc/std/__mdspan/extents.h>
#include <asc/std/__mdspan/layout_right.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/extent.h>
#include <asc/std/__type_traits/is_abstract.h>
#include <asc/std/__type_traits/is_array.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_pointer.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/rank.h>
#include <asc/std/__type_traits/remove_all_extents.h>
#include <asc/std/__type_traits/remove_cv.h>
#include <asc/std/__type_traits/remove_pointer.h>
#include <asc/std/__type_traits/remove_reference.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/as_const.h>
#include <asc/std/__utility/cmp.h>
#include <asc/std/__utility/declval.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/__utility/move.h>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/limits>
#include <asc/std/span>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __mdspan_detail {

// For deduction guides: integral-constant-like arguments map to a static extent, all
// others to a dynamic extent.
template <class T, bool = __mdspan_detail::__integral_constant_like_v<T>>
inline constexpr size_t __maybe_static_ext = dynamic_extent;

template <class T>
inline constexpr size_t __maybe_static_ext<T, true> = {static_cast<size_t>(T::value)};

// Whether the argument count of the array/span construction paths matches the
// dynamic-rank or full-rank requirement; variable-template form of a concept.
template <class Extents, size_t Size>
inline constexpr bool __matches_dynamic_rank_helper = (Size == Extents::rank_dynamic());

template <class Extents, size_t Size>
inline constexpr bool __matches_static_rank_helper = (Size == Extents::rank()) && (Size != Extents::rank_dynamic());

// [mdspan.layout.general]: whether the LayoutPolicy is valid for its Extents.
template <class Layout, class Extents, class = void>
struct __is_valid_layout_mapping_impl : false_type {};
template <class Layout, class Extents>
struct __is_valid_layout_mapping_impl<Layout, Extents, void_t<typename Layout::template mapping<Extents>>> : true_type {
};

template <class Layout, class Extents>
inline constexpr bool __is_valid_layout_mapping = __is_valid_layout_mapping_impl<Layout, Extents>::value;

// Whether the accessor provides the __detectably_invalid debug probe.
template <class AccessorPolicy, class = void>
struct __has_detect_invalidity_impl : false_type {};
template <class AccessorPolicy>
struct __has_detect_invalidity_impl<AccessorPolicy,
    void_t<decltype(declval<AccessorPolicy&>().__detectably_invalid(
        declval<typename AccessorPolicy::data_handle_type>(), declval<size_t>()))>> : true_type {};

template <class AccessorPolicy>
inline constexpr bool __has_detect_invalidity = __has_detect_invalidity_impl<AccessorPolicy>::value;

}  // namespace __mdspan_detail

template <class Extents, class LayoutPolicy, class AccessorPolicy>
struct __mdspan_constraints {
    using extents_type = Extents;
    using layout_type = LayoutPolicy;
    using accessor_type = AccessorPolicy;
    using mapping_type = typename layout_type::template mapping<extents_type>;
    using index_type = typename extents_type::index_type;
    using data_handle_type = typename accessor_type::data_handle_type;

    static constexpr bool __can_default_construct = (Extents::rank_dynamic() > 0) &&
        is_default_constructible_v<data_handle_type> && is_default_constructible_v<mapping_type> &&
        is_default_constructible_v<accessor_type>;

    template <class... OtherIndexTypes>
    static constexpr bool __can_construct_from_handle_and_variadic =
        (__mdspan_detail::__matches_dynamic_rank_helper<extents_type, sizeof...(OtherIndexTypes)> ||
            __mdspan_detail::__matches_static_rank_helper<extents_type, sizeof...(OtherIndexTypes)>) &&
        __mdspan_detail::__all_convertible_to_index_type<index_type, OtherIndexTypes...> &&
        is_constructible_v<mapping_type, extents_type> && is_default_constructible_v<accessor_type>;

    template <class OtherIndexType>
    static constexpr bool __is_constructible_from_index_type = is_convertible_v<const OtherIndexType&, index_type> &&
        is_nothrow_constructible_v<index_type, const OtherIndexType&> &&
        is_constructible_v<mapping_type, extents_type> && is_default_constructible_v<accessor_type>;

    template <class OtherExtents, class OtherLayoutPolicy, class OtherAccessor>
    static constexpr bool __is_convertible_from =
        is_constructible_v<mapping_type, const typename OtherLayoutPolicy::template mapping<OtherExtents>&> &&
        is_constructible_v<accessor_type, const OtherAccessor&>;

    template <class OtherExtents, class OtherLayoutPolicy, class OtherAccessor>
    static constexpr bool __is_implicit_convertible_from =
        is_convertible_v<const typename OtherLayoutPolicy::template mapping<OtherExtents>&, mapping_type> &&
        is_convertible_v<const OtherAccessor&, accessor_type>;
};

template <class Element, class Extents, class Layout, class Accessor>
class mdspan
    : private __mdspan_ebco<typename Accessor::data_handle_type, typename Layout::template mapping<Extents>, Accessor> {
private:
    static_assert(__mdspan_detail::__is_asc_std_extents_v<Extents>,
        "mdspan: Extents template parameter must be a specialization of extents.");
    static_assert(!is_array_v<Element>, "mdspan: ElementType template parameter may not be an array type");
    static_assert(!is_abstract_v<Element>, "mdspan: ElementType template parameter may not be an abstract class");
    static_assert(is_same_v<Element, typename Accessor::element_type>,
        "mdspan: ElementType template parameter must match AccessorPolicy::element_type");
    static_assert(__mdspan_detail::__is_valid_layout_mapping<Layout, Extents>,
        "mdspan: LayoutPolicy template parameter is invalid. A common mistake is to pass a layout mapping "
        "instead of a layout policy");

    template <class, class, class, class>
    friend class mdspan;

    using constraints = __mdspan_constraints<Extents, Layout, Accessor>;

public:
    using extents_type = Extents;
    using layout_type = Layout;
    using accessor_type = Accessor;
    using mapping_type = typename layout_type::template mapping<extents_type>;
    using element_type = Element;
    using value_type = remove_cv_t<element_type>;
    using index_type = typename extents_type::index_type;
    using size_type = typename extents_type::size_type;
    using rank_type = typename extents_type::rank_type;
    using data_handle_type = typename accessor_type::data_handle_type;
    using reference = typename accessor_type::reference;
    using base =
        __mdspan_ebco<typename accessor_type::data_handle_type, typename Layout::template mapping<Extents>, Accessor>;

    CANN_ASC_STL_API static constexpr rank_type rank() noexcept
    {
        return extents_type::rank();
    }
    CANN_ASC_STL_API static constexpr rank_type rank_dynamic() noexcept
    {
        return extents_type::rank_dynamic();
    }
    CANN_ASC_STL_API static constexpr size_t static_extent(rank_type r) noexcept
    {
        return extents_type::static_extent(r);
    }
    CANN_ASC_STL_API constexpr index_type extent(rank_type r) const noexcept
    {
        return mapping().extents().extent(r);
    }

    //--------------------------------------------------------------------------------
    // [mdspan.mdspan.cons], mdspan constructors, assignment, and destructor

    template <class Extents2 = Extents,
        enable_if_t<__mdspan_constraints<Extents2, Layout, Accessor>::__can_default_construct, int> = 0>
    CANN_ASC_STL_API constexpr mdspan() noexcept(is_nothrow_default_constructible_v<data_handle_type> &&
        is_nothrow_default_constructible_v<mapping_type> && is_nothrow_default_constructible_v<accessor_type>)
        : base()
    {
        if constexpr (__mdspan_detail::__has_detect_invalidity<accessor_type>) {
            [[maybe_unused]] const auto& tmp = mapping();  // silence unused-result warnings
            CANN_ASC_STL_DETAIL_ASSERT(!accessor().__detectably_invalid(data_handle(), tmp.required_span_size()),
                "mdspan: invalid data handle");
        }
    }

    CANN_ASC_STL_API constexpr mdspan(const mdspan&) = default;
    CANN_ASC_STL_API constexpr mdspan(mdspan&&) = default;

    template <class... OtherIndexTypes,
        enable_if_t<constraints::template __can_construct_from_handle_and_variadic<OtherIndexTypes...>, int> = 0>
    CANN_ASC_STL_API explicit constexpr mdspan(data_handle_type pointer, OtherIndexTypes... exts)
        : base(::asc::std::move(pointer), extents_type(static_cast<index_type>(::asc::std::move(exts))...))
    {
        if constexpr (__mdspan_detail::__has_detect_invalidity<accessor_type>) {
            [[maybe_unused]] const auto& tmp = mapping();
            CANN_ASC_STL_DETAIL_ASSERT(!accessor().__detectably_invalid(data_handle(), tmp.required_span_size()),
                "mdspan: invalid data handle");
        }
    }

    template <class OtherIndexType, size_t Size,
        enable_if_t<__mdspan_detail::__matches_dynamic_rank_helper<extents_type, Size> &&
                constraints::template __is_constructible_from_index_type<OtherIndexType>,
            int> = 0>
    CANN_ASC_STL_API constexpr mdspan(data_handle_type pointer, const array<OtherIndexType, Size>& exts)
        : base(::asc::std::move(pointer), extents_type{exts})
    {
        if constexpr (__mdspan_detail::__has_detect_invalidity<accessor_type>) {
            [[maybe_unused]] const auto& tmp = mapping();
            CANN_ASC_STL_DETAIL_ASSERT(!accessor().__detectably_invalid(data_handle(), tmp.required_span_size()),
                "mdspan: invalid data handle");
        }
    }

    template <class OtherIndexType, size_t Size,
        enable_if_t<__mdspan_detail::__matches_static_rank_helper<extents_type, Size> &&
                constraints::template __is_constructible_from_index_type<OtherIndexType>,
            int> = 0>
    CANN_ASC_STL_API explicit constexpr mdspan(data_handle_type pointer, const array<OtherIndexType, Size>& exts)
        : base(::asc::std::move(pointer), extents_type{exts})
    {
        if constexpr (__mdspan_detail::__has_detect_invalidity<accessor_type>) {
            [[maybe_unused]] const auto& tmp = mapping();
            CANN_ASC_STL_DETAIL_ASSERT(!accessor().__detectably_invalid(data_handle(), tmp.required_span_size()),
                "mdspan: invalid data handle");
        }
    }

    template <class OtherIndexType, size_t Size,
        enable_if_t<__mdspan_detail::__matches_dynamic_rank_helper<extents_type, Size> &&
                constraints::template __is_constructible_from_index_type<OtherIndexType>,
            int> = 0>
    CANN_ASC_STL_API constexpr mdspan(data_handle_type pointer, span<OtherIndexType, Size> exts)
        : base(::asc::std::move(pointer), extents_type{exts})
    {
        if constexpr (__mdspan_detail::__has_detect_invalidity<accessor_type>) {
            [[maybe_unused]] const auto& tmp = mapping();
            CANN_ASC_STL_DETAIL_ASSERT(!accessor().__detectably_invalid(data_handle(), tmp.required_span_size()),
                "mdspan: invalid data handle");
        }
    }

    template <class OtherIndexType, size_t Size,
        enable_if_t<__mdspan_detail::__matches_static_rank_helper<extents_type, Size> &&
                constraints::template __is_constructible_from_index_type<OtherIndexType>,
            int> = 0>
    CANN_ASC_STL_API explicit constexpr mdspan(data_handle_type pointer, span<OtherIndexType, Size> exts)
        : base(::asc::std::move(pointer), extents_type{exts})
    {
        if constexpr (__mdspan_detail::__has_detect_invalidity<accessor_type>) {
            [[maybe_unused]] const auto& tmp = mapping();
            CANN_ASC_STL_DETAIL_ASSERT(!accessor().__detectably_invalid(data_handle(), tmp.required_span_size()),
                "mdspan: invalid data handle");
        }
    }

    template <class AccessorPolicy2 = Accessor, class Mapping2 = mapping_type,
        enable_if_t<is_default_constructible_v<AccessorPolicy2> && is_constructible_v<Mapping2, const extents_type&>,
            int> = 0>
    CANN_ASC_STL_API constexpr mdspan(data_handle_type pointer, const extents_type& exts)
        : base(::asc::std::move(pointer), exts)
    {
        if constexpr (__mdspan_detail::__has_detect_invalidity<accessor_type>) {
            [[maybe_unused]] const auto& tmp = mapping();
            CANN_ASC_STL_DETAIL_ASSERT(!accessor().__detectably_invalid(data_handle(), tmp.required_span_size()),
                "mdspan: invalid data handle");
        }
    }

    template <class AccessorPolicy2 = Accessor, enable_if_t<is_default_constructible_v<AccessorPolicy2>, int> = 0>
    CANN_ASC_STL_API constexpr mdspan(data_handle_type pointer, const mapping_type& m)
        : base(::asc::std::move(pointer), m)
    {
        if constexpr (__mdspan_detail::__has_detect_invalidity<accessor_type>) {
            [[maybe_unused]] const auto& tmp = mapping();
            CANN_ASC_STL_DETAIL_ASSERT(!accessor().__detectably_invalid(data_handle(), tmp.required_span_size()),
                "mdspan: invalid data handle");
        }
    }

    CANN_ASC_STL_API constexpr mdspan(data_handle_type pointer, const mapping_type& m, const accessor_type& a)
        : base(::asc::std::move(pointer), m, a)
    {
        if constexpr (__mdspan_detail::__has_detect_invalidity<accessor_type>) {
            [[maybe_unused]] const auto& tmp = mapping();
            CANN_ASC_STL_DETAIL_ASSERT(!accessor().__detectably_invalid(data_handle(), tmp.required_span_size()),
                "mdspan: invalid data handle");
        }
    }

    template <class OtherElementType, class OtherExtents, class OtherLayoutPolicy, class OtherAccessor,
        enable_if_t<constraints::template __is_convertible_from<OtherExtents, OtherLayoutPolicy, OtherAccessor> &&
                constraints::template __is_implicit_convertible_from<OtherExtents, OtherLayoutPolicy, OtherAccessor>,
            int> = 0>
    CANN_ASC_STL_API constexpr mdspan(
        const mdspan<OtherElementType, OtherExtents, OtherLayoutPolicy, OtherAccessor>& other)
        : base(other.data_handle(), other.mapping(), other.accessor())
    {
        static_assert(is_constructible_v<data_handle_type, const typename OtherAccessor::data_handle_type&>,
            "mdspan: incompatible data_handle_type for mdspan construction");
        static_assert(
            is_constructible_v<extents_type, OtherExtents>, "mdspan: incompatible extents for mdspan construction");
        __assert_slices_match<OtherElementType, OtherExtents, OtherLayoutPolicy, OtherAccessor>(other);
    }

    template <class OtherElementType, class OtherExtents, class OtherLayoutPolicy, class OtherAccessor,
        enable_if_t<constraints::template __is_convertible_from<OtherExtents, OtherLayoutPolicy, OtherAccessor> &&
                !(constraints::template __is_implicit_convertible_from<OtherExtents, OtherLayoutPolicy, OtherAccessor>),
            int> = 0>
    CANN_ASC_STL_API explicit constexpr mdspan(
        const mdspan<OtherElementType, OtherExtents, OtherLayoutPolicy, OtherAccessor>& other)
        : base(other.data_handle(), other.mapping(), other.accessor())
    {
        static_assert(is_constructible_v<data_handle_type, const typename OtherAccessor::data_handle_type&>,
            "mdspan: incompatible data_handle_type for mdspan construction");
        static_assert(
            is_constructible_v<extents_type, OtherExtents>, "mdspan: incompatible extents for mdspan construction");
        __assert_slices_match<OtherElementType, OtherExtents, OtherLayoutPolicy, OtherAccessor>(other);
    }

    CANN_ASC_STL_API constexpr mdspan& operator=(const mdspan&) = default;
    CANN_ASC_STL_API constexpr mdspan& operator=(mdspan&&) = default;

    //--------------------------------------------------------------------------------
    // [mdspan.mdspan.members], members

#if CANN_ASC_STL_DETAIL_HAS_MULTIDIMENSIONAL_SUBSCRIPT()
    template <class... OtherIndexTypes,
        enable_if_t<(sizeof...(OtherIndexTypes) == extents_type::rank()) &&
                __mdspan_detail::__all_convertible_to_index_type<index_type, OtherIndexTypes...>,
            int> = 0>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr reference operator[](OtherIndexTypes... indices) const
    {
        // The standard layouts check this precondition, but user-defined layouts may not,
        // so check it here.
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_multidimensional_index_in(extents(), indices...),
            "mdspan: operator[] out of bounds access");
        return accessor().access(data_handle(), mapping()(static_cast<index_type>(::asc::std::move(indices))...));
    }
#else
    template <class OtherIndexType,
        enable_if_t<(extents_type::rank() == 1) && is_convertible_v<OtherIndexType, index_type> &&
                is_nothrow_constructible_v<index_type, OtherIndexType>,
            int> = 0>
    CANN_ASC_STL_API constexpr reference operator[](OtherIndexType index) const
    {
        return accessor().access(data_handle(), mapping()(static_cast<index_type>(::asc::std::move(index))));
    }
#endif  // multidimensional subscript

    template <class OtherIndexType, size_t... Idxs>
    CANN_ASC_STL_API constexpr decltype(auto) __op_bracket(
        const array<OtherIndexType, Extents::rank()>& indices, index_sequence<Idxs...>) const noexcept
    {
        // The standard layouts check this precondition, but user-defined layouts may not,
        // so check it here.
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_multidimensional_index_in(extents(), indices[Idxs]...),
            "mdspan: operator[array] out of bounds access");
        return mapping()(indices[Idxs]...);
    }

    template <class OtherIndexType, size_t... Idxs>
    CANN_ASC_STL_API constexpr decltype(auto) __op_bracket(
        span<OtherIndexType, Extents::rank()> indices, index_sequence<Idxs...>) const noexcept
    {
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_multidimensional_index_in(extents(), indices[Idxs]...),
            "mdspan: operator[span] out of bounds access");
        return mapping()(indices[Idxs]...);
    }

    template <class OtherIndexType,
        enable_if_t<is_convertible_v<const OtherIndexType&, index_type> &&
                is_nothrow_constructible_v<index_type, const OtherIndexType&>,
            int> = 0>
    CANN_ASC_STL_API constexpr reference operator[](const array<OtherIndexType, extents_type::rank()>& indices) const
    {
        return accessor().access(data_handle(), __op_bracket(indices, make_index_sequence<rank()>()));
    }

    template <class OtherIndexType,
        enable_if_t<is_convertible_v<const OtherIndexType&, index_type> &&
                is_nothrow_constructible_v<index_type, const OtherIndexType&>,
            int> = 0>
    CANN_ASC_STL_API constexpr reference operator[](span<OtherIndexType, extents_type::rank()> indices) const
    {
        return accessor().access(data_handle(), __op_bracket(indices, make_index_sequence<rank()>()));
    }

    // Non-standard extension: multidimensional subscript access through operator(),
    // kept to avoid breaking existing users.
    template <class... Indices,
        enable_if_t<__mdspan_detail::__all_convertible_to_index_type<index_type, Indices...>, int> = 0>
    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr reference operator()(Indices... indices) const
    {
        // The standard layouts check this precondition, but user-defined layouts may not,
        // so check it here.
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_multidimensional_index_in(extents(), indices...),
            "mdspan: operator() out of bounds access");
        return accessor().access(data_handle(), mapping()(indices...));
    }

    template <size_t... Idxs>
    CANN_ASC_STL_API constexpr bool __check_size() const noexcept
    {
        bool result = true;
        if constexpr (extents_type::rank() > 0) {
            size_t product = 1;
            for (size_t r = 0; r < extents_type::rank(); ++r) {
                const auto extent_value = static_cast<size_t>(mapping().extents().extent(r));
                if (__mdspan_detail::__mul_overflow(product, extent_value, &product)) {
                    result = false;
                    break;
                }
            }
        }
        return result;
    }

    template <size_t... Idxs>
    CANN_ASC_STL_API constexpr size_type __op_size(index_sequence<Idxs...>) const noexcept
    {
        return (size_type{1} * ... * static_cast<size_type>(mapping().extents().extent(Idxs)));
    }

    CANN_ASC_STL_API constexpr size_type size() const noexcept
    {
        // By its semantics size() is not guaranteed to relate to any accessible range;
        // only the representability check is kept.
        CANN_ASC_STL_DETAIL_ASSERT(__check_size(), "mdspan: size() is not representable as size_type");
        return __op_size(make_index_sequence<rank()>());
    }

    template <size_t... Idxs>
    CANN_ASC_STL_API constexpr bool __op_empty(index_sequence<Idxs...>) const noexcept
    {
        return (((mapping().extents().extent(Idxs) == index_type{0})) || ...);
    }

    CANN_ASC_STL_API constexpr bool empty() const noexcept
    {
        return __op_empty(make_index_sequence<rank()>());
    }

    CANN_ASC_STL_API friend constexpr void swap(mdspan& x, mdspan& y) noexcept
    {
        swap(static_cast<base&>(x), static_cast<base&>(y));  // NOLINT(build/include_what_you_use)
    }

    CANN_ASC_STL_API constexpr const extents_type& extents() const noexcept
    {
        return mapping().extents();
    }
    CANN_ASC_STL_API constexpr data_handle_type data_handle() const noexcept
    {
        return this->template __get<0>();
    }
    CANN_ASC_STL_API constexpr const mapping_type& mapping() const noexcept
    {
        return this->template __get<1>();
    }
    CANN_ASC_STL_API constexpr const accessor_type& accessor() const noexcept
    {
        return this->template __get<2>();
    }

    CANN_ASC_STL_API static constexpr bool is_always_unique() noexcept(noexcept(mapping_type::is_always_unique()))
    {
        return mapping_type::is_always_unique();
    }
    CANN_ASC_STL_API static constexpr bool is_always_exhaustive() noexcept(
        noexcept(mapping_type::is_always_exhaustive()))
    {
        return mapping_type::is_always_exhaustive();
    }
    CANN_ASC_STL_API static constexpr bool is_always_strided() noexcept(noexcept(mapping_type::is_always_strided()))
    {
        return mapping_type::is_always_strided();
    }

    CANN_ASC_STL_API constexpr bool is_unique() const
        noexcept(noexcept(::asc::std::declval<const mapping_type&>().is_unique()))
    {
        const auto& tmp = mapping();  // silence unused-result warnings
        return tmp.is_unique();
    }
    CANN_ASC_STL_API constexpr bool is_exhaustive() const
        noexcept(noexcept(::asc::std::declval<const mapping_type&>().is_exhaustive()))
    {
        const auto& tmp = mapping();
        return tmp.is_exhaustive();
    }
    CANN_ASC_STL_API constexpr bool is_strided() const
        noexcept(noexcept(::asc::std::declval<const mapping_type&>().is_strided()))
    {
        const auto& tmp = mapping();
        return tmp.is_strided();
    }
    CANN_ASC_STL_API constexpr index_type stride(rank_type r) const
    {
        const auto& tmp = mapping();
        return static_cast<index_type>(tmp.stride(r));
    }

private:
    // Static-extent consistency assertion for cross-mdspan construction (a standard
    // precondition).
    template <class OtherElementType, class OtherExtents, class OtherLayoutPolicy, class OtherAccessor>
    CANN_ASC_STL_API constexpr void __assert_slices_match(
        [[maybe_unused]] const mdspan<OtherElementType, OtherExtents, OtherLayoutPolicy, OtherAccessor>& other) const
    {
        if constexpr (__mdspan_detail::__has_detect_invalidity<accessor_type>) {
            [[maybe_unused]] const auto& tmp = mapping();  // silence unused-result warnings
            CANN_ASC_STL_DETAIL_ASSERT(!accessor().__detectably_invalid(data_handle(), tmp.required_span_size()),
                "mdspan: invalid data handle");
        }
        if constexpr (extents_type::rank() != 0) {
            // This precondition comes from the standard but is nearly impossible to
            // trigger: the extents constructor already checks it, and a mapping must
            // store its extents (extents() returns a const reference). It can only fire
            // when a mapping's converting constructor rebuilds its extents from the
            // dynamic extents only, e.g.
            // mdspan<int, dextents<char, 1>, ...> m = mdspan<int, dextents<unsigned, 1>, ...>(ptr, 200)
            // would give m an extent of -56.
            for (size_t r = 0; r != extents_type::rank(); ++r) {
                CANN_ASC_STL_DETAIL_ASSERT(
                    (static_extent(r) == dynamic_extent) || ::asc::std::cmp_equal(other.extent(r), static_extent(r)),
                    "mdspan: conversion mismatch of source dynamic extents with static extents");
            }
        }
    }
};

template <class Element, class... IndexTypes,
    enable_if_t<(sizeof...(IndexTypes) > 0) && (is_convertible_v<IndexTypes, size_t> && ... && true), int> = 0>
explicit mdspan(
    Element*, IndexTypes...) -> mdspan<Element, extents<size_t, __mdspan_detail::__maybe_static_ext<IndexTypes>...>>;

template <class Pointer, enable_if_t<is_pointer_v<remove_reference_t<Pointer>>, int> = 0>
mdspan(Pointer&&) -> mdspan<remove_pointer_t<remove_reference_t<Pointer>>, extents<size_t>>;

template <class CArray, enable_if_t<is_array_v<CArray> && rank_v<CArray> == 1, int> = 0>
mdspan(CArray&) -> mdspan<remove_all_extents_t<CArray>, extents<size_t, extent_v<CArray, 0>>>;

template <class Element, class OtherIndexType, size_t Size>
mdspan(Element*, const array<OtherIndexType, Size>&) -> mdspan<Element, dextents<size_t, Size>>;

template <class Element, class OtherIndexType, size_t Size>
mdspan(Element*, span<OtherIndexType, Size>) -> mdspan<Element, dextents<size_t, Size>>;

// All constructors take data_handle_type (from the accessor) rather than Element*,
// which would defeat automatic deduction, so this guide is provided explicitly.
template <class Element, class OtherIndexType, size_t... ExtentsPack>
mdspan(Element*,
    const extents<OtherIndexType, ExtentsPack...>&) -> mdspan<Element, extents<OtherIndexType, ExtentsPack...>>;

template <class Element, class MappingType>
mdspan(Element*,
    const MappingType&) -> mdspan<Element, typename MappingType::extents_type, typename MappingType::layout_type>;

template <class MappingType, class AccessorType>
mdspan(const typename AccessorType::data_handle_type, const MappingType&,
    const AccessorType&) -> mdspan<typename AccessorType::element_type, typename MappingType::extents_type,
                             typename MappingType::layout_type, AccessorType>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_MDSPAN_H
