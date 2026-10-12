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

#ifndef CANN_ASC_STL_ASC_STD___MDSPAN_EXTENTS_H
#define CANN_ASC_STL_ASC_STD___MDSPAN_EXTENTS_H

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
#include <asc/std/__fwd/span.h>
#include <asc/std/__mdspan/concepts.h>
#include <asc/std/__mdspan/empty_base.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/fold.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_integer.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/make_nbit_int.h>
#include <asc/std/__type_traits/make_unsigned.h>
#include <asc/std/__utility/cmp.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/__utility/unreachable.h>
#include <asc/std/array>
#include <asc/std/concepts>
#include <asc/std/cstddef>
#include <asc/std/limits>
#include <asc/std/span>

CANN_ASC_STL_BEGIN_NAMESPACE

namespace __mdspan_detail {

// ------------------------------------------------------------------
// ------------ __static_array --------------------------------------
// ------------------------------------------------------------------
// 提供静态值序列的按索引读取（值全部编码在模板参数中，无运行期存储）。
template <class Tp, Tp... Values>
struct __static_array {
    CANN_ASC_STL_API static constexpr size_t __size() noexcept
    {
        return sizeof...(Values);
    }

    CANN_ASC_STL_API static constexpr Tp __get(size_t index) noexcept
    {
        constexpr array<Tp, sizeof...(Values)> values = {Values...};
        return values[index];
    }

    template <size_t Index>
    CANN_ASC_STL_API static constexpr Tp __get()
    {
        return __get(Index);
    }
};

// ------------------------------------------------------------------
// ------------ __extents_dynamic_array -----------------------------
// ------------------------------------------------------------------
// 类 array 的最小运行期存储：size 0 特化为真正的空类型，使全静态 extents
// 不占存储（空基类优化）。上游实现名为 __possibly_empty_array，因
// layout_stride.h 已内联同名副本，此处换名避免同一定义域重定义。
template <class Tp, size_t Size>
struct __extents_dynamic_array {
    Tp values_[Size];

    CANN_ASC_STL_API constexpr Tp& operator[](size_t index)
    {
        return values_[index];
    }
    CANN_ASC_STL_API constexpr const Tp& operator[](size_t index) const
    {
        return values_[index];
    }
};

template <class Tp>
struct __extents_dynamic_array<Tp, 0> {
    CANN_ASC_STL_API constexpr Tp& operator[](size_t /*index*/)  // NOLINT(readability/casting)
    {
        CANN_ASC_STL_DETAIL_UNREACHABLE();
    }
    CANN_ASC_STL_API constexpr const Tp& operator[](size_t /*index*/) const
    {
        CANN_ASC_STL_DETAIL_UNREACHABLE();
    }
};

// ------------------------------------------------------------------
// ------------ __static_partial_sums --------------------------------
// ------------------------------------------------------------------
// 编译期前缀和（动态值下标映射用），可按索引读取。
template <size_t... Values>
struct __static_partial_sums {
    CANN_ASC_STL_API static constexpr array<size_t, sizeof...(Values)> __static_partial_sums_impl()
    {
        array<size_t, sizeof...(Values)> input{Values...};
        array<size_t, sizeof...(Values)> partial_sums{};
        size_t running_sum = 0;
        for (size_t index = 0; index != sizeof...(Values); ++index) {
            partial_sums[index] = running_sum;
            running_sum += input[index];
        }
        return partial_sums;
    }

    CANN_ASC_STL_API static constexpr size_t __get(size_t index)
    {
        constexpr array<size_t, sizeof...(Values)> result = __static_partial_sums_impl();
        return result[index];
    }
};

// ------------------------------------------------------------------
// ------------ __maybe_static_array --------------------------------
// ------------------------------------------------------------------
// 静态/动态混合值序列：静态值编码在模板参数中，仅动态值占用运行期存储；
// 动态值的位置以标签值（dynamic_extent）标记。构造时校验提供的值与
// 静态值一致（防止把长度错误的实参悄悄映射到静态维度）。

template <class TStatic, TStatic DynTag, TStatic... Values>
inline constexpr size_t __count_dynamic_v = (size_t{0} + ... + static_cast<size_t>(Values == DynTag));

template <class TDynamic, class TStatic, TStatic DynTag, TStatic... Values>
struct __maybe_static_array : private __extents_dynamic_array<TDynamic, __count_dynamic_v<TStatic, DynTag, Values...>> {
    static_assert(is_convertible_v<TStatic, TDynamic>, "__maybe_static_array: TStatic must be convertible to TDynamic");
    static_assert(is_convertible_v<TDynamic, TStatic>, "__maybe_static_array: TDynamic must be convertible to TStatic");

private:
    // 静态值成员与动态值下标映射
    static constexpr size_t __size_ = sizeof...(Values);
    static constexpr size_t __size_dynamic_ = __count_dynamic_v<TStatic, DynTag, Values...>;
    using __static_values = __static_array<TStatic, Values...>;
    using __dynamic_values = __extents_dynamic_array<TDynamic, __size_dynamic_>;
    using __dynamic_idx_map = __static_partial_sums<static_cast<size_t>(Values == DynTag)...>;

    template <size_t... Indices>
    CANN_ASC_STL_API static constexpr __dynamic_values __zeros(index_sequence<Indices...>) noexcept
    {
        return __dynamic_values{((void)Indices, 0)...};
    }

public:
    CANN_ASC_STL_API constexpr __maybe_static_array() noexcept
        : __dynamic_values{__zeros(make_index_sequence<__size_dynamic_>())}
    {}

    template <class Tp, size_t Size>
    CANN_ASC_STL_API constexpr __maybe_static_array(span<Tp, Size> vals) noexcept : __dynamic_values{}
    {
        if constexpr (Size == __size_dynamic_) {
            for (size_t index = 0; index != Size; ++index) {
                (*static_cast<__dynamic_values*>(this))[index] = static_cast<TDynamic>(vals[index]);
            }
        } else {
            for (size_t index = 0; index != __size_; ++index) {
                TStatic static_val = __static_values::__get(index);
                if (static_val == DynTag) {
                    (*static_cast<__dynamic_values*>(this))[__dynamic_idx_map::__get(index)] =
                        static_cast<TDynamic>(vals[index]);
                } else {
                    // 不校验会让越界在后续才暴露，例如：
                    // mdspan<int, extents<int, 10>> m(new int[N], span<int, 1>(&N));
                    // 分配和长度看似匹配，但 m 仍认为其范围是 10 而非 N。
                    CANN_ASC_STL_DETAIL_ASSERT(static_cast<TDynamic>(vals[index]) == static_cast<TDynamic>(static_val),
                        "extents construction: mismatch of provided arguments with static extents.");
                }
            }
        }
    }

    // 仅动态值构造（覆盖 rank() == 0 的情形）；排除全 span 实参以免与 span 构造二义。
    template <class... DynVals,
        enable_if_t<(sizeof...(DynVals) == __size_dynamic_) && !__fold_and_v<__is_asc_std_span_v<DynVals>...>, int> = 0>
    CANN_ASC_STL_API constexpr __maybe_static_array(DynVals... vals) noexcept
        : __dynamic_values{static_cast<TDynamic>(vals)...}
    {}

    // 全值构造（rank > 0 时按 rank 提供全部维度）
    template <class... DynVals,
        enable_if_t<(sizeof...(DynVals) != __size_dynamic_) && !__fold_and_v<__is_asc_std_span_v<DynVals>...>, int> = 0>
    CANN_ASC_STL_API constexpr __maybe_static_array(DynVals... vals) noexcept : __dynamic_values{}
    {
        static_assert(sizeof...(DynVals) == __size_, "Invalid number of values.");
        TDynamic all_values[__size_] = {static_cast<TDynamic>(vals)...};
        for (size_t index = 0; index != __size_; ++index) {
            TStatic static_val = __static_values::__get(index);
            if (static_val == DynTag) {
                (*static_cast<__dynamic_values*>(this))[__dynamic_idx_map::__get(index)] = all_values[index];
            } else {
                // 不校验会让越界在后续才暴露，例如：
                // mdspan<int, extents<int, 10>> m(new int[5], 5);
                // 右侧构造看似正确，但 m 仍认为其范围是 10 而非 5。
                CANN_ASC_STL_DETAIL_ASSERT(all_values[index] == static_cast<TDynamic>(static_val),
                    "extents construction: mismatch of provided arguments with static extents.");
            }
        }
    }

    // 访问
    CANN_ASC_STL_API static constexpr TStatic __static_value(size_t index) noexcept
    {
        if constexpr (__size_ > 0) {
            CANN_ASC_STL_DETAIL_ASSERT(index < __size_, "extents access: index must be less than rank");
        }
        return __static_values::__get(index);
    }

    CANN_ASC_STL_API constexpr TDynamic __value(size_t index) const
    {
        if constexpr (__size_ > 0) {
            CANN_ASC_STL_DETAIL_ASSERT(index < __size_, "extents access: index must be less than rank");
        }
        TStatic static_val = __static_values::__get(index);
        return static_val == DynTag ? (*static_cast<const __dynamic_values*>(this))[__dynamic_idx_map::__get(index)] :
                                      static_cast<TDynamic>(static_val);
    }

    CANN_ASC_STL_API constexpr TDynamic operator[](size_t index) const
    {
        if constexpr (__size_ > 0) {
            CANN_ASC_STL_DETAIL_ASSERT(index < __size_, "extents access: index must be less than rank");
        }
        return __value(index);
    }

    // 观察器
    CANN_ASC_STL_API static constexpr size_t __size()
    {
        return __size_;
    }
    CANN_ASC_STL_API static constexpr size_t __size_dynamic()
    {
        return __size_dynamic_;
    }
};

// 目标类型能否无损表示源类型的极值（按无符号量级比较，判窄化）。
template <class To, class From>
inline constexpr bool __potentially_narrowing = static_cast<make_unsigned_t<To>>((numeric_limits<To>::max)()) <
    static_cast<make_unsigned_t<From>>((numeric_limits<From>::max)());  // NOLINT(build/include_what_you_use)

// 一组值是否都能以目标整数类型表示且非负（复数变参与 span 两种入口；
// 单值判定 __is_representable_as 由 __mdspan/empty_base.h 提供）。
template <class To, class... From, enable_if_t<__is_integer_v<To>, int> = 0>
CANN_ASC_STL_API constexpr bool __are_representable_as(From... values)
{
    return (__mdspan_detail::__is_representable_as<To>(values) && ... && true);
}

template <class To, class From, size_t Size, enable_if_t<__is_integer_v<To>, int> = 0>
CANN_ASC_STL_API constexpr bool __are_representable_as(span<From, Size> values)
{
    bool result = true;
    for (size_t index = 0; index != Size; ++index) {
        if (!__mdspan_detail::__is_representable_as<To>(values[index])) {
            result = false;
            break;
        }
    }
    return result;
}

}  // namespace __mdspan_detail

// ------------------------------------------------------------------
// ------------ extents ----------------------------------------------
// ------------------------------------------------------------------

// 用于在不同（非）explicit 构造间委托的标签。
struct __extent_delegate_tag {};

// 多维数组的维度描述，mdspan/mdarray 与布局映射共用。
template <class IndexType, size_t... Extents>
class extents : private __mdspan_detail::__maybe_static_array<IndexType, size_t, dynamic_extent, Extents...> {
public:
    using index_type = IndexType;
    using size_type = make_unsigned_t<index_type>;
    using rank_type = size_t;

    static_assert(__is_integer_v<index_type>, "extents::index_type must be a signed or unsigned integer type");
    static_assert(((::asc::std::in_range<index_type>(Extents) || (Extents == dynamic_extent)) && ...),
        "extents ctor: arguments must be representable as index_type and nonnegative");

private:
    static constexpr rank_type __rank_ = sizeof...(Extents);
    static constexpr rank_type __rank_dynamic_ =
        (rank_type(0) + ... + (static_cast<rank_type>(Extents == dynamic_extent)));

    using __storage_base = __mdspan_detail::__maybe_static_array<IndexType, size_t, dynamic_extent, Extents...>;

public:
    // [mdspan.extents.obs]，多维索引空间观察器
    CANN_ASC_STL_API static constexpr rank_type rank() noexcept
    {
        return __rank_;
    }
    CANN_ASC_STL_API static constexpr rank_type rank_dynamic() noexcept
    {
        return __rank_dynamic_;
    }

    CANN_ASC_STL_API constexpr index_type extent(rank_type r) const noexcept
    {
        return this->__value(r);
    }
    CANN_ASC_STL_API static constexpr size_t static_extent(rank_type r) noexcept
    {
        return __storage_base::__static_value(r);
    }

    // [mdspan.extents.cons]，构造
    CANN_ASC_STL_API constexpr extents() noexcept = default;

    // 按动态维度数或全 rank 提供值；前置条件校验在 __maybe_static_array 构造中完成。
    template <class... OtherIndexTypes,
        enable_if_t<(sizeof...(OtherIndexTypes) == __rank_ || sizeof...(OtherIndexTypes) == __rank_dynamic_) &&
                __mdspan_detail::__all_convertible_to_index_type<index_type, OtherIndexTypes...>,
            int> = 0>
    CANN_ASC_STL_API constexpr explicit extents(OtherIndexTypes... dynvals) noexcept
        : __storage_base(static_cast<index_type>(dynvals)...)
    {
        // 不校验会导致越界在后续才暴露，例如
        // mdspan m(ptr, dextents<char, 1>(200u)); 会让 m 得到 -56 的维度。
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__are_representable_as<index_type>(dynvals...),
            "extents ctor: arguments must be representable as index_type and nonnegative");
    }

    template <class OtherIndexType>
    static constexpr bool __is_convertible_to_index_type = is_convertible_v<const OtherIndexType&, index_type> &&
        is_nothrow_constructible_v<index_type, const OtherIndexType&>;

    template <class OtherIndexType, size_t Size,
        enable_if_t<(Size == __rank_dynamic_) && __is_convertible_to_index_type<OtherIndexType>, int> = 0>
    CANN_ASC_STL_API constexpr extents(const array<OtherIndexType, Size>& exts) noexcept
        : extents(span<const OtherIndexType, Size>(exts.data(), Size))
    {}

    template <class OtherIndexType, size_t Size,
        enable_if_t<(Size == __rank_) && (Size != __rank_dynamic_) && __is_convertible_to_index_type<OtherIndexType>,
            int> = 0>
    CANN_ASC_STL_API explicit constexpr extents(const array<OtherIndexType, Size>& exts) noexcept
        : extents(span<const OtherIndexType, Size>(exts.data(), Size))
    {}

    template <class OtherIndexType, size_t Size,
        enable_if_t<(Size == __rank_dynamic_) && __is_convertible_to_index_type<OtherIndexType>, int> = 0>
    CANN_ASC_STL_API constexpr extents(span<OtherIndexType, Size> exts) noexcept : __storage_base(exts)
    {
        // 不校验会导致越界在后续才暴露，例如
        // array a{200u}; mdspan<int, dextents<char, 1>> m(ptr, extents(span<unsigned, 1>(a)));
        // 会让 m 得到 -56 的维度。
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__are_representable_as<index_type>(exts),
            "extents ctor: arguments must be representable as index_type and nonnegative");
    }

    template <class OtherIndexType, size_t Size,
        enable_if_t<(Size != __rank_dynamic_) && (Size == __rank_) && __is_convertible_to_index_type<OtherIndexType>,
            int> = 0>
    CANN_ASC_STL_API explicit constexpr extents(span<OtherIndexType, Size> exts) noexcept : __storage_base(exts)
    {
        CANN_ASC_STL_DETAIL_ASSERT(__mdspan_detail::__are_representable_as<index_type>(exts),
            "extents ctor: arguments must be representable as index_type and nonnegative");
    }

private:
    // 从其他 extents 特化构造存储：静态位取其当前值，动态位按位收集。
    template <size_t DynCount, size_t Idx, class OtherExtents, class... DynamicValues>
    CANN_ASC_STL_API constexpr __storage_base __construct_vals_from_extents(integral_constant<size_t, DynCount>,
        integral_constant<size_t, Idx>, const OtherExtents& exts, DynamicValues... dynamic_values) noexcept
    {
        if constexpr (Idx == __rank_) {
            if constexpr (DynCount == __rank_dynamic_) {
                return __storage_base{static_cast<index_type>(dynamic_values)...};
            } else {
                static_assert(DynCount == __rank_dynamic_, "Constructor of invalid extents passed to extent::extent");
                CANN_ASC_STL_DETAIL_UNREACHABLE();
            }
        } else {  // Idx < __rank_
            if constexpr (static_extent(Idx) == dynamic_extent) {
                return __construct_vals_from_extents(integral_constant<size_t, DynCount + 1>(),
                    integral_constant<size_t, Idx + 1>(), exts, dynamic_values..., exts.extent(Idx));
            } else {  // static_extent(Idx) != dynamic_extent
                return __construct_vals_from_extents(integral_constant<size_t, DynCount>(),
                    integral_constant<size_t, Idx + 1>(), exts, dynamic_values...);
            }
        }
    }

    template <class OtherIndexType, size_t... OtherExtents>
    CANN_ASC_STL_API constexpr extents(
        __extent_delegate_tag, const extents<OtherIndexType, OtherExtents...>& other) noexcept
        : __storage_base(
              __construct_vals_from_extents(integral_constant<size_t, 0>(), integral_constant<size_t, 0>(), other))
    {
        if constexpr (rank() != 0) {
            for (size_t r = 0; r != rank(); ++r) {
                CANN_ASC_STL_DETAIL_ASSERT(::asc::std::in_range<index_type>(other.extent(r)),
                    "extents ctor: arguments must be representable as index_type and nonnegative");

                // 不校验会导致越界在后续才暴露，例如
                // mdspan<int, extents<int, 10>> m = mdspan<int, dextents<int, 1>>(new int[5], 5);
                // 右侧构造正确，但 m 仍认为其范围是 10 而非 5。
                CANN_ASC_STL_DETAIL_ASSERT((__storage_base::__static_value(r) == dynamic_extent) ||
                        (static_cast<index_type>(other.extent(r)) ==
                            static_cast<index_type>(__storage_base::__static_value(r))),
                    "extents construction: mismatch of provided arguments with static extents.");
            }
        }
    }

public:
    // 跨 extents 特化的转换构造（按标准显式性拆分两个约束重载）
    template <class OtherIndexType, size_t... OtherExtents>
    static constexpr bool __is_explicit_conversion =
        (((Extents != dynamic_extent) && (OtherExtents == dynamic_extent)) || ...) ||
        __mdspan_detail::__potentially_narrowing<index_type, OtherIndexType>;

    template <size_t... OtherExtents>
    static constexpr bool __is_matching_extents =
        ((OtherExtents == dynamic_extent || Extents == dynamic_extent || OtherExtents == Extents) && ... && true);

    template <class OtherIndexType, size_t... OtherExtents,
        enable_if_t<(sizeof...(OtherExtents) == sizeof...(Extents)) && __is_matching_extents<OtherExtents...> &&
                !__is_explicit_conversion<OtherIndexType, OtherExtents...>,
            int> = 0>
    CANN_ASC_STL_API constexpr extents(const extents<OtherIndexType, OtherExtents...>& other) noexcept
        : extents(__extent_delegate_tag{}, other)
    {}

    template <class OtherIndexType, size_t... OtherExtents,
        enable_if_t<(sizeof...(OtherExtents) == sizeof...(Extents)) && __is_matching_extents<OtherExtents...> &&
                __is_explicit_conversion<OtherIndexType, OtherExtents...>,
            int> = 0>
    CANN_ASC_STL_API explicit constexpr extents(const extents<OtherIndexType, OtherExtents...>& other) noexcept
        : extents(__extent_delegate_tag{}, other)
    {}

    // 相等比较
    template <class OtherIndexType, size_t... OtherExtents>
    CANN_ASC_STL_API friend constexpr bool operator==(
        const extents& left, const extents<OtherIndexType, OtherExtents...>& right) noexcept
    {
        if constexpr (rank() != sizeof...(OtherExtents)) {
            return false;
        } else if constexpr (rank() != 0) {
            bool result = true;
            for (rank_type r = 0; r != __rank_; ++r) {
                if (::asc::std::cmp_not_equal(left.extent(r), right.extent(r))) {
                    result = false;
                    break;
                }
            }
            return result;
        } else {
            return true;
        }
    }

#if CANN_ASC_STL_DETAIL_STD_VER <= 2017
    template <class OtherIndexType, size_t... OtherExtents>
    CANN_ASC_STL_API friend constexpr bool operator!=(
        const extents& left, const extents<OtherIndexType, OtherExtents...>& right) noexcept
    {
        return !(left == right);
    }
#endif  // CANN_ASC_STL_DETAIL_STD_VER <= 2017
};

// 无 nvcc 式类型转换问题的推导辅助。
struct __to_dynamic_extent {
    template <class>
    static constexpr size_t value = dynamic_extent;
};

// extents 的推导指引
template <class... IndexTypes>
extents(IndexTypes...) -> extents<size_t, __to_dynamic_extent::template value<IndexTypes>...>;

namespace __mdspan_detail {

template <class IndexType, size_t... Indices>
CANN_ASC_STL_API auto make_dextents(
    index_sequence<Indices...>) -> extents<IndexType, (static_cast<void>(Indices), dynamic_extent)...>;

}  // namespace __mdspan_detail

template <class IndexType, size_t Rank>
using dextents = decltype(__mdspan_detail::make_dextents<IndexType>(make_index_sequence<Rank>()));

template <size_t Rank, class IndexType = size_t>
using dims = dextents<IndexType, Rank>;

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_EXTENTS_H
