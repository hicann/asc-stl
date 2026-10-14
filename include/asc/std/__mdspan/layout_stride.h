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

#ifndef CANN_ASC_STL_ASC_STD___MDSPAN_LAYOUT_STRIDE_H
#define CANN_ASC_STL_ASC_STD___MDSPAN_LAYOUT_STRIDE_H

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
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__utility/as_const.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/__utility/swap.h>
#include <asc/std/__utility/unreachable.h>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/limits>
#include <asc/std/span>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __mdspan_detail {

// Minimal array-like container providing operator[]; the size 0 specialization is an
// empty type.
template <class T, size_t Size>
struct __possibly_empty_array {
    T values_[Size];

    CANN_ASC_STL_API constexpr T& operator[](size_t index)
    {
        return values_[index];
    }
    CANN_ASC_STL_API constexpr const T& operator[](size_t index) const
    {
        return values_[index];
    }
};

template <class T>
struct __possibly_empty_array<T, 0> {
    CANN_ASC_STL_API constexpr T& operator[](size_t __index)
    {
        CANN_ASC_STL_DETAIL_UNREACHABLE();
    }
    CANN_ASC_STL_API constexpr const T& operator[](size_t) const
    {
        CANN_ASC_STL_DETAIL_UNREACHABLE();
    }
};

// [mdspan.layout.reqmts]: whether Layout::mapping<Extents> is exactly this mapping type.
template <class Layout, class Mapping, class = void>
struct __is_mapping_of_impl : false_type {};
template <class Layout, class Mapping>
struct __is_mapping_of_impl<Layout, Mapping, void_t<typename Layout::template mapping<typename Mapping::extents_type>>>
    : is_same<typename Layout::template mapping<typename Mapping::extents_type>, Mapping> {};

template <class Layout, class Mapping>
inline constexpr bool __is_mapping_of = __is_mapping_of_impl<Layout, Mapping>::value;

// [mdspan.layout.stride.expo]/4: mapping-alike detection, written as a SFINAE-safe
// variable template instead of a concept.
template <class Mapping, class = void>
struct __layout_mapping_alike_impl : false_type {};
template <class Mapping>
struct __layout_mapping_alike_impl<Mapping,
    void_t<typename Mapping::layout_type, typename Mapping::extents_type, decltype(Mapping::is_always_unique()),
        decltype(Mapping::is_always_exhaustive()), decltype(Mapping::is_always_strided()),
        integral_constant<bool, Mapping::is_always_unique()>, integral_constant<bool, Mapping::is_always_exhaustive()>,
        integral_constant<bool, Mapping::is_always_strided()>>>
    : bool_constant<__mdspan_detail::__is_mapping_of<typename Mapping::layout_type, Mapping> &&
          __mdspan_detail::__is_asc_std_extents_v<typename Mapping::extents_type> &&
          is_same_v<bool, decltype(Mapping::is_always_strided())> &&
          is_same_v<bool, decltype(Mapping::is_always_exhaustive())> &&
          is_same_v<bool, decltype(Mapping::is_always_unique())>> {};

template <class Mapping>
inline constexpr bool __layout_mapping_alike = __layout_mapping_alike_impl<Mapping>::value;

}  // namespace __mdspan_detail

namespace __layout_stride_detail {

template <class Extents, class StrideArray, bool = (Extents::rank() == 0)>
struct __mapping_base : __mdspan_ebco<Extents, StrideArray> {
    using base = __mdspan_ebco<Extents, StrideArray>;
    using base::base;
};

template <class Extents, class StrideArray>
struct __mapping_base<Extents, StrideArray, true> : __mdspan_ebco<Extents> {
    using base = __mdspan_ebco<Extents>;
    using base::base;

    CANN_ASC_STL_API constexpr __mapping_base(const Extents& ext, const StrideArray&) noexcept(
        is_nothrow_constructible_v<base, const Extents&>)
        : base(ext)
    {}
};

// Detection of mapping-alike types convertible to layout_stride::mapping.
template <class StridedLayoutMapping, class Extents, class = void>
struct __can_convert_impl : false_type {};
template <class StridedLayoutMapping, class Extents>
struct __can_convert_impl<StridedLayoutMapping, Extents,
    void_t<decltype(StridedLayoutMapping::is_always_unique()), decltype(StridedLayoutMapping::is_always_strided()),
        typename StridedLayoutMapping::extents_type>>
    : bool_constant<__mdspan_detail::__layout_mapping_alike<StridedLayoutMapping> &&
          StridedLayoutMapping::is_always_unique() && StridedLayoutMapping::is_always_strided() &&
          is_constructible_v<Extents, typename StridedLayoutMapping::extents_type>> {};

template <class StridedLayoutMapping, class Extents>
inline constexpr bool __can_convert = __can_convert_impl<StridedLayoutMapping, Extents>::value;

struct __constraints {
    // The enable_if substitution path may be evaluated for arbitrary argument types,
    // so this must be SFINAE-safe.
    template <class StridedLayoutMapping, class Extents, class = void>
    struct __converts_implicit_impl : false_type {};
    template <class StridedLayoutMapping, class Extents>
    struct __converts_implicit_impl<StridedLayoutMapping, Extents, void_t<typename StridedLayoutMapping::extents_type>>
        : bool_constant<is_convertible_v<typename StridedLayoutMapping::extents_type, Extents> &&
              (__mdspan_detail::__is_mapping_of<layout_left, StridedLayoutMapping> ||
                  __mdspan_detail::__is_mapping_of<layout_right, StridedLayoutMapping> ||
                  __mdspan_detail::__is_mapping_of<layout_stride, StridedLayoutMapping>)> {};

    template <class StridedLayoutMapping, class Extents>
    static constexpr bool __converts_implicit = __converts_implicit_impl<StridedLayoutMapping, Extents>::value;
};

}  // namespace __layout_stride_detail

template <class Extents>
class layout_stride::mapping
    : private __layout_stride_detail::__mapping_base<Extents,
          __mdspan_detail::__possibly_empty_array<typename Extents::index_type, Extents::rank()>> {
public:
    static_assert(__mdspan_detail::__is_asc_std_extents_v<Extents>,
        "layout_stride::mapping template argument must be a specialization of extents.");

    using extents_type = Extents;
    using index_type = typename extents_type::index_type;
    using size_type = typename extents_type::size_type;
    using rank_type = typename extents_type::rank_type;
    using layout_type = layout_stride;
    using base = __layout_stride_detail::__mapping_base<Extents,
        __mdspan_detail::__possibly_empty_array<index_type, extents_type::rank()>>;

    template <class, class, class, class>
    friend class mdspan;

private:
    static constexpr rank_type rank_value = extents_type::rank();
    static constexpr auto rank_sequence = ::asc::std::make_index_sequence<extents_type::rank()>();

    using stride_array = __mdspan_detail::__possibly_empty_array<index_type, extents_type::rank()>;

    // Addition overflow detection, used by the default-construction checks and mandates.
    CANN_ASC_STL_API static constexpr bool __add_overflow(index_type x, index_type y, index_type* res) noexcept
    {
        *res = x + y;
        return *res < y;
    }

    template <class OtherIndexType>
    CANN_ASC_STL_API static constexpr bool __conversion_may_overflow(OtherIndexType stride) noexcept
    {
        if constexpr (is_integral_v<OtherIndexType>) {
            using common_type = common_type_t<index_type, OtherIndexType>;
            return static_cast<common_type>(stride) >
                static_cast<common_type>((numeric_limits<index_type>::max)());  // NOLINT(build/include_what_you_use)
        } else {
            return false;
        }
    }

    template <class StrideValues>
    CANN_ASC_STL_API static constexpr bool __required_span_size_is_representable_from(
        const extents_type& ext, const StrideValues& strides) noexcept
    {
        bool result = true;
        if constexpr (extents_type::rank() != 0) {
            index_type size = 1;
            for (rank_type r = 0; r != extents_type::rank(); ++r) {
                // The conversion can only be checked correctly when OtherIndexType is an integral type.
                if (__conversion_may_overflow(strides[r])) {
                    result = false;
                    break;
                }
                if (ext.extent(r) == index_type{0}) {
                    result = true;
                    break;
                }

                index_type product = (ext.extent(r) - 1);
                if (__mdspan_detail::__mul_overflow(product, static_cast<index_type>(strides[r]), &product)) {
                    result = false;
                    break;
                }
                if (__add_overflow(size, product, &size)) {
                    result = false;
                    break;
                }
            }
        }
        return result;
    }

    // Computes the base offset of a mapping from another layout.
    template <class StridedMapping, size_t... Position>
    CANN_ASC_STL_API static constexpr auto __offset(
        const StridedMapping& mapping_value, index_sequence<Position...>) noexcept
    {
        return static_cast<typename StridedMapping::index_type>(mapping_value((Position ? 0 : 0)...));
    }

    template <class StridedMapping>
    CANN_ASC_STL_API static constexpr index_type __offset(const StridedMapping& mapping_value) noexcept
    {
        using strided_extents = typename StridedMapping::extents_type;
        if constexpr (strided_extents::rank() != 0) {
            if (mapping_value.required_span_size() == typename StridedMapping::index_type{0}) {
                return index_type{0};
            }
            return static_cast<index_type>(__offset(mapping_value, rank_sequence));
        } else {
            return static_cast<index_type>(mapping_value());
        }
    }

    static_assert(
        (extents_type::rank_dynamic() > 0) || __mdspan_detail::__required_span_size_is_representable(extents_type()),
        "layout_stride::mapping product of static extents must be representable as index_type.");

public:
    // [mdspan.layout.stride.cons], constructors
    CANN_ASC_STL_API constexpr mapping() noexcept : base(extents_type())
    {
        if constexpr (extents_type::rank() > 0) {
            index_type stride = 1;
            for (rank_type r = rank_value - 1; r > rank_type{0}; --r) {
                strides_m()[r] = stride;
                stride *= extents().extent(r);
            }
            strides_m()[0] = stride;
        }
    }

    CANN_ASC_STL_API constexpr mapping(const mapping&) noexcept = default;

    template <class OtherIndexType, size_t... Position>
    CANN_ASC_STL_API static constexpr auto __to_strides_array(
        span<OtherIndexType, extents_type::rank()> strides, index_sequence<Position...>) noexcept
    {
        return stride_array{static_cast<index_type>(::asc::std::as_const(strides[Position]))...};
    }

    template <class OtherIndexType, size_t... Position>
    CANN_ASC_STL_API static constexpr auto __check_strides(
        span<OtherIndexType, extents_type::rank()> strides, index_sequence<Position...>) noexcept
    {
        if constexpr (is_integral_v<OtherIndexType>) {
            return ((strides[Position] > OtherIndexType{0}) && ... && true);
        } else {
            return ((static_cast<index_type>(strides[Position]) > index_type{0}) && ... && true);
        }
    }

    template <class OtherIndexType, size_t... Position>
    CANN_ASC_STL_API static constexpr auto __check_strides(
        const array<OtherIndexType, extents_type::rank()>& strides, index_sequence<Position...>) noexcept
    {
        if constexpr (is_integral_v<OtherIndexType>) {
            return ((strides[Position] > OtherIndexType{0}) && ... && true);
        } else {
            return ((static_cast<index_type>(strides[Position]) > index_type{0}) && ... && true);
        }
    }

    // Computes the sort permutation by strides (the stride array itself is not sorted).
    CANN_ASC_STL_API constexpr void __bubble_sort_by_strides(
        array<rank_type, extents_type::rank()>& permute) const noexcept
    {
        for (rank_type i = rank_value - 1; i > 0; --i) {
            for (rank_type r = 0; r < i; ++r) {
                if (strides_m()[permute[r]] > strides_m()[permute[r + 1]]) {
                    swap(permute[r], permute[r + 1]);  // NOLINT(build/include_what_you_use)
                } else {
                    // With two equal strides, one of the associated extents must be 1 or 0.
                    if ((strides_m()[permute[r]] == strides_m()[permute[r + 1]]) &&
                        (extents().extent(permute[r]) > index_type{1})) {
                        swap(permute[r], permute[r + 1]);  // NOLINT(build/include_what_you_use)
                    }
                }
            }
        }
    }

    template <size_t... Position>
    CANN_ASC_STL_API constexpr bool __check_unique_mapping(index_sequence<Position...>) const noexcept
    {
        // Sort dimensions by strides and extents; the result is recorded in the permute array.
        array<rank_type, extents_type::rank()> permute{Position...};
        __bubble_sort_by_strides(permute);

        bool result = true;
        for (rank_type i = 1; i < rank_value; ++i) {
            if (static_cast<index_type>(strides_m()[permute[i]]) <
                static_cast<index_type>(strides_m()[permute[i - 1]]) * extents().extent(permute[i - 1])) {
                result = false;
                break;
            }
        }
        return result;
    }
    CANN_ASC_STL_API constexpr bool __check_unique_mapping(index_sequence<>) const noexcept
    {
        return true;
    }

    template <class OtherIndexType,
        enable_if_t<is_constructible_v<index_type, const OtherIndexType&> &&
                is_convertible_v<const OtherIndexType&, index_type>,
            int> = 0>
    CANN_ASC_STL_API constexpr mapping(
        const extents_type& ext, span<OtherIndexType, extents_type::rank()> strides) noexcept
        : base(ext, __to_strides_array(strides, rank_sequence))
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            __check_strides(strides, rank_sequence), "layout_stride::mapping ctor: all strides must be greater than 0");
        CANN_ASC_STL_DETAIL_ASSERT(__required_span_size_is_representable_from(ext, strides),
            "layout_stride::mapping ctor: required span size is not representable as index_type.");
        CANN_ASC_STL_DETAIL_ASSERT(__check_unique_mapping(rank_sequence),
            "layout_stride::mapping ctor: the provided extents and strides lead to a non-unique mapping");
    }

    template <class OtherIndexType, size_t... Position>
    CANN_ASC_STL_API static constexpr auto __to_strides_array(
        const array<OtherIndexType, extents_type::rank()>& strides, index_sequence<Position...>) noexcept
    {
        return stride_array{static_cast<index_type>(::asc::std::as_const(strides[Position]))...};
    }

    // span has no constructor from a const array in C++17, so the array path does not
    // delegate through span.
    template <class OtherIndexType,
        enable_if_t<is_constructible_v<index_type, const OtherIndexType&> &&
                is_convertible_v<const OtherIndexType&, index_type>,
            int> = 0>
    CANN_ASC_STL_API constexpr mapping(
        const extents_type& ext, const array<OtherIndexType, extents_type::rank()>& strides) noexcept
        : base(ext, __to_strides_array(strides, rank_sequence))
    {
        CANN_ASC_STL_DETAIL_ASSERT(
            __check_strides(strides, rank_sequence), "layout_stride::mapping ctor: all strides must be greater than 0");
        CANN_ASC_STL_DETAIL_ASSERT(__required_span_size_is_representable_from(ext, strides),
            "layout_stride::mapping ctor: required span size is not representable as index_type.");
        CANN_ASC_STL_DETAIL_ASSERT(__check_unique_mapping(rank_sequence),
            "layout_stride::mapping ctor: the provided extents and strides lead to a non-unique mapping");
    }

    template <class StridedLayoutMapping, size_t... Position>
    CANN_ASC_STL_API static constexpr auto __to_strides_array(
        const StridedLayoutMapping& other, index_sequence<Position...>) noexcept
    {
        return stride_array{static_cast<index_type>(other.stride(Position))...};
    }

    // stride() only compiles for rank > 0.
    template <class StridedLayoutMapping, size_t... Position>
    CANN_ASC_STL_API static constexpr auto __check_mapped_strides(
        const StridedLayoutMapping& other, index_sequence<Position...>) noexcept
    {
        return ((static_cast<index_type>(other.stride(Position)) > index_type{0}) && ... && true);
    }
    template <class StridedLayoutMapping>
    CANN_ASC_STL_API static constexpr auto __check_mapped_strides(
        const StridedLayoutMapping&, index_sequence<>) noexcept
    {
        return true;
    }

    template <class StridedLayoutMapping,
        enable_if_t<__layout_stride_detail::__can_convert<StridedLayoutMapping, Extents> &&
                __layout_stride_detail::__constraints::__converts_implicit<StridedLayoutMapping, Extents>,
            int> = 0>
    CANN_ASC_STL_API constexpr mapping(const StridedLayoutMapping& other) noexcept
        : base(extents_type(other.extents()), __to_strides_array(other, rank_sequence))
    {
        CANN_ASC_STL_DETAIL_ASSERT(__check_mapped_strides(other, rank_sequence),
            "layout_stride::mapping converting ctor: all strides must be greater than 0");
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_representable_as<index_type>(other.required_span_size()),
            "layout_stride::mapping converting ctor: other.required_span_size() must be representable as "
            "index_type.");
        CANN_ASC_STL_DETAIL_ASSERT(index_type{0} == __offset(other),
            "layout_stride::mapping converting ctor: base offset of mapping must be zero.");
    }

    template <class StridedLayoutMapping,
        enable_if_t<__layout_stride_detail::__can_convert<StridedLayoutMapping, Extents> &&
                !__layout_stride_detail::__constraints::__converts_implicit<StridedLayoutMapping, Extents>,
            int> = 0>
    CANN_ASC_STL_API explicit constexpr mapping(const StridedLayoutMapping& other) noexcept
        : base(extents_type(other.extents()), __to_strides_array(other, rank_sequence))
    {
        CANN_ASC_STL_DETAIL_ASSERT(__check_mapped_strides(other, rank_sequence),
            "layout_stride::mapping converting ctor: all strides must be greater than 0");
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__is_representable_as<index_type>(other.required_span_size()),
            "layout_stride::mapping converting ctor: other.required_span_size() must be representable as "
            "index_type.");
        CANN_ASC_STL_DETAIL_ASSERT(index_type{0} == __offset(other),
            "layout_stride::mapping converting ctor: base offset of mapping must be zero.");
    }

    CANN_ASC_STL_API constexpr mapping& operator=(const mapping&) noexcept = default;

    // [mdspan.layout.stride.obs], observers
    CANN_ASC_STL_API constexpr const extents_type& extents() const noexcept
    {
        return this->template __get<0>();
    }

    CANN_ASC_STL_API constexpr stride_array& strides_m() noexcept
    {
        return this->template __get<1>();
    }

    CANN_ASC_STL_API constexpr const stride_array& strides_m() const noexcept
    {
        return this->template __get<1>();
    }

    template <size_t... Position>
    CANN_ASC_STL_API constexpr array<index_type, extents_type::rank()> __to_strides(
        index_sequence<Position...>) const noexcept
    {
        return array<index_type, extents_type::rank()>{strides_m()[Position]...};
    }

    CANN_ASC_STL_NODISCARD CANN_ASC_STL_API constexpr array<index_type, extents_type::rank()> strides() const noexcept
    {
        return __to_strides(rank_sequence);
    }

    template <size_t... Position>
    CANN_ASC_STL_API constexpr index_type __required_span_size(index_sequence<Position...>) const noexcept
    {
        const index_type product = (index_type{1} * ... * extents().extent(Position));
        if (product == index_type{0}) {
            return index_type{0};
        } else {
            return (index_type{1} + ... + ((extents().extent(Position) - index_type{1}) * strides_m()[Position]));
        }
    }

    CANN_ASC_STL_API constexpr index_type required_span_size() const noexcept
    {
        if constexpr (extents_type::rank() == 0) {
            return index_type{1};
        } else {
            return __required_span_size(rank_sequence);
        }
    }

    template <size_t... Position, class... Indices>
    CANN_ASC_STL_API static constexpr index_type __op_index(
        const stride_array& strides, index_sequence<Position...>, Indices... index) noexcept
    {
        return (index_type{0} + ... + (static_cast<index_type>(index) * strides[Position]));
    }

    template <class... Indices,
        enable_if_t<(sizeof...(Indices) == extents_type::rank()) &&
                __mdspan_detail::__all_convertible_to_index_type<index_type, Indices...>,
            int> = 0>
    CANN_ASC_STL_API constexpr index_type operator()(Indices... index) const noexcept
    {
        // mdspan performs its own bounds checking; keep this light to avoid double checking.
        if constexpr (extents_type::rank() == 0) {
            return index_type{0};
        } else {
            return __op_index(strides_m(), ::asc::std::make_index_sequence<sizeof...(Indices)>(), index...);
        }
    }

    CANN_ASC_STL_API static constexpr bool is_always_unique() noexcept
    {
        return true;
    }
    CANN_ASC_STL_API static constexpr bool is_always_exhaustive() noexcept
    {
        return false;
    }
    CANN_ASC_STL_API static constexpr bool is_always_strided() noexcept
    {
        return true;
    }

    CANN_ASC_STL_API static constexpr bool is_unique() noexcept
    {
        return true;
    }

    // With some extents zero the answer is subtle: the standard's definition admits no
    // simple true/false.
    template <size_t... Position>
    CANN_ASC_STL_API constexpr index_type __to_total_size(index_sequence<Position...>) const noexcept
    {
        return (index_type{1} * ... * (extents().extent(Position)));
    }

    CANN_ASC_STL_API constexpr bool is_exhaustive() const noexcept
    {
        if constexpr (extents_type::rank() == 0) {
            return true;
        } else {
            const index_type span_size = required_span_size();
            if (span_size == index_type{0}) {
                if constexpr (extents_type::rank() == 1) {
                    return strides_m()[0] == 1;
                } else {
                    rank_type r_largest = 0;
                    for (rank_type r = 1; r < rank_value; ++r) {
                        if (strides_m()[r] > strides_m()[r_largest]) {
                            r_largest = r;
                        }
                    }

                    bool result = true;
                    for (rank_type r = 0; r != rank_value; ++r) {
                        if (extents().extent(r) == 0 && r != r_largest) {
                            result = false;
                            break;
                        }
                    }
                    return result;
                }
            } else {
                const index_type total_size = __to_total_size(rank_sequence);
                return span_size == total_size;
            }
        }
    }

    CANN_ASC_STL_API static constexpr bool is_strided() noexcept
    {
        return true;
    }

    // The standard imposes no Constraints on stride(r) for rank > 0, but it still states
    // a precondition.
    CANN_ASC_STL_API constexpr index_type stride(rank_type r) const noexcept
    {
        if constexpr (rank_value > 0) {  // avoid a pointless unsigned-vs-zero comparison warning
            CANN_ASC_STL_DETAIL_ASSERT(r < rank_value, "layout_stride::mapping::stride(): invalid rank index");
            return strides_m()[r];
        } else {
            return index_type{0};
        }
    }

    template <class OtherMapping, size_t... Position>
    CANN_ASC_STL_API static constexpr bool __op_eq(
        const mapping& left, const OtherMapping& right, index_sequence<Position...>) noexcept
    {
        // Compare in the common type to avoid signed/unsigned comparison warnings.
        using common_type = common_type_t<index_type, typename OtherMapping::index_type>;
        return ((static_cast<common_type>(left.stride(Position)) == static_cast<common_type>(right.stride(Position))) &&
            ... && true);
    }

    template <class OtherMapping>
    CANN_ASC_STL_API static constexpr bool __op_eq(const mapping& left, const OtherMapping& right) noexcept
    {
        if constexpr (extents_type::rank() > 0) {
            if (__offset(right)) {
                return false;
            }
            return left.extents() == right.extents() && __op_eq(left, right, rank_sequence);
        } else {
            return (!__offset(right));
        }
    }

    template <class OtherMapping, class OtherExtents = typename OtherMapping::extents_type,
        enable_if_t<__mdspan_detail::__layout_mapping_alike<OtherMapping> &&
                (OtherExtents::rank() == Extents::rank()) && OtherMapping::is_always_strided(),
            int> = 0>
    CANN_ASC_STL_API friend constexpr bool operator==(const mapping& left, const OtherMapping& right) noexcept
    {
        return __op_eq(left, right);
    }

#if CANN_ASC_STL_DETAIL_STD_VER <= 2017
    template <class OtherMapping, class OtherExtents = typename OtherMapping::extents_type,
        enable_if_t<!__mdspan_detail::__is_mapping_of<layout_stride, OtherMapping> &&
                __mdspan_detail::__layout_mapping_alike<OtherMapping> && (OtherExtents::rank() == Extents::rank()) &&
                OtherMapping::is_always_strided(),
            int> = 0>
    CANN_ASC_STL_API friend constexpr bool operator==(const OtherMapping& left, const mapping& right) noexcept
    {
        return __op_eq(right, left);
    }

    template <class OtherMapping, class OtherExtents = typename OtherMapping::extents_type,
        enable_if_t<__mdspan_detail::__layout_mapping_alike<OtherMapping> &&
                (OtherExtents::rank() == Extents::rank()) && OtherMapping::is_always_strided(),
            int> = 0>
    CANN_ASC_STL_API friend constexpr bool operator!=(const mapping& left, const OtherMapping& right) noexcept
    {
        return !__op_eq(left, right);
    }

    template <class OtherMapping, class OtherExtents = typename OtherMapping::extents_type,
        enable_if_t<!__mdspan_detail::__is_mapping_of<layout_stride, OtherMapping> &&
                __mdspan_detail::__layout_mapping_alike<OtherMapping> && (OtherExtents::rank() == Extents::rank()) &&
                OtherMapping::is_always_strided(),
            int> = 0>
    CANN_ASC_STL_API friend constexpr bool operator!=(const OtherMapping& left, const mapping& right) noexcept
    {
        return !__op_eq(right, left);
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER <= 2017
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_LAYOUT_STRIDE_H
