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

#ifndef CANN_ASC_STL_ASC_STD___MDSPAN_EMPTY_BASE_H
#define CANN_ASC_STL_ASC_STD___MDSPAN_EMPTY_BASE_H

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
#include <asc/std/__type_traits/enable_if.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_constructible.h>
#include <asc/std/__type_traits/is_convertible.h>
#include <asc/std/__type_traits/is_default_constructible.h>
#include <asc/std/__type_traits/is_empty.h>
#include <asc/std/__type_traits/is_integral.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/is_swappable.h>
#include <asc/std/__type_traits/is_signed.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__type_traits/void_t.h>
#include <asc/std/__utility/cmp.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/integer_sequence.h>
#include <asc/std/__utility/swap.h>
#include <asc/std/cstddef>

// 基座未提供下列宏（合入源树定义于 __asc 方言支撑头）：内联其语义的最小等价，
// #ifndef 守卫以免与未来基座定义冲突。
#ifndef CANN_ASC_STL_DETAIL_ASSERT
// 设备侧无断言机制恒为 no-op；宿主侧仅在显式开启 ASC_ENABLE_HOST_ASSERTIONS 时检查。
#if CANN_ASC_STL_DETAIL_DEVICE_COMPILATION() || !defined(ASC_ENABLE_HOST_ASSERTIONS)
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) ((void)0)
#else
#define CANN_ASC_STL_DETAIL_ASSERT(expression, message) \
    ((expression) ? static_cast<void>(0) : (__builtin_trap(), static_cast<void>(0)))
#endif
#endif  // CANN_ASC_STL_DETAIL_ASSERT

#ifndef CANN_ASC_STL_DETAIL_STD_VER
// 与 __cplusplus 对应的简化标准版本号（合入源树 __asc/dialect.h 语义）。
#if __cplusplus <= 199711L
#define CANN_ASC_STL_DETAIL_STD_VER 2003
#elif __cplusplus <= 201103L
#define CANN_ASC_STL_DETAIL_STD_VER 2011
#elif __cplusplus <= 201402L
#define CANN_ASC_STL_DETAIL_STD_VER 2014
#elif __cplusplus <= 201703L
#define CANN_ASC_STL_DETAIL_STD_VER 2017
#elif __cplusplus <= 202002L
#define CANN_ASC_STL_DETAIL_STD_VER 2020
#elif __cplusplus <= 202302L
#define CANN_ASC_STL_DETAIL_STD_VER 2023
#else
#define CANN_ASC_STL_DETAIL_STD_VER 2024
#endif
#endif  // CANN_ASC_STL_DETAIL_STD_VER

CANN_ASC_STL_BEGIN_NAMESPACE

// 前置声明：与 __mdspan/extents.h 的主模板一致，供下方判定使用。
template <class IndexType, size_t... StaticExtents>
class extents;

namespace __mdspan_detail {

// extents 特化判定（合入源树位于 __fwd/extents.h，基座无该头，内联于此）。
template <class T>
inline constexpr bool __is_asc_std_extents_v = false;
template <class IndexType, size_t... StaticExtents>
inline constexpr bool __is_asc_std_extents_v<extents<IndexType, StaticExtents...>> = true;

// integral-constant-like 判定的类型无关实现（基座仅有 C++20 concept 版本，
// 此处为 SFINAE 安全的变量模板形态，供 C++17 路径使用）。
template <class T, class = void>
struct __integral_constant_like_impl : false_type {};
template <class T>
struct __integral_constant_like_impl<T, void_t<decltype(T::value)>> {
    using value_type = remove_cvref_t<decltype(T::value)>;
    static constexpr bool value =
        is_integral_v<value_type> && !is_same_v<bool, value_type> && is_convertible_v<T, value_type>;
};
template <class T>
inline constexpr bool __integral_constant_like_v = __integral_constant_like_impl<T>::value;

// 一组索引均可隐式且 noexcept 地转换为 index_type（合入源树为 concept，此处为
// 变量模板形态以保证 C++17 与设备编译可用）。
template <class IndexType, class... Indices>
inline constexpr bool __all_convertible_to_index_type = ((is_convertible_v<Indices, IndexType> && ... && true) &&
    (is_nothrow_constructible_v<IndexType, Indices> && ... && true));

// 乘法溢出探测：返回是否溢出，结果经 res 写出。
template <class T>
CANN_ASC_STL_API constexpr bool __mul_overflow(T left, T right, T* res) noexcept
{
    *res = left * right;
    return left != T{0} && ((*res / left) != right);
}

// 非负整数值能否无损表示为目标整数类型。
template <class To, class From, enable_if_t<__is_integer_v<To>, int> = 0>
CANN_ASC_STL_API constexpr bool __is_representable_as(From value) noexcept
{
    if constexpr (is_integral_v<From> && !is_same_v<From, bool>) {
        return in_range<To>(value);
    } else if constexpr (is_signed_v<To>) {
        return static_cast<To>(value) >= To{0};
    } else {
        return true;
    }
}

// extents 的尺寸乘积能否以 index_type 表示（不溢出）。
template <class Extents>
CANN_ASC_STL_API constexpr bool __required_span_size_is_representable(const Extents& ext) noexcept
{
    bool result = true;
    if constexpr (Extents::rank() != 0) {
        using index_type = typename Extents::index_type;
        using rank_type = typename Extents::rank_type;
        index_type product = ext.extent(0);
        for (rank_type r = 1; r < Extents::rank(); ++r) {
            if (__mul_overflow(product, ext.extent(r), &product)) {
                result = false;
                break;
            }
        }
    }
    return result;
}

// 单个索引是否落在相应 extent 的半开区间内。
template <class IndexType, class From, enable_if_t<__is_integer_v<IndexType>, int> = 0>
CANN_ASC_STL_API constexpr bool __is_index_in_extent(IndexType extent, From value) noexcept
{
    if constexpr (is_integral_v<From> && !is_same_v<From, bool>) {
        return cmp_greater_equal(value, From{0}) && cmp_less(value, extent);
    } else if constexpr (is_signed_v<From>) {
        if (static_cast<IndexType>(value) < IndexType{0}) {
            return false;
        }
        return static_cast<IndexType>(value) < extent;
    } else {
        return static_cast<IndexType>(value) < extent;
    }
}

template <size_t... Indices, class Extents, class... From>
CANN_ASC_STL_API constexpr bool __is_multidimensional_index_in_impl(
    index_sequence<Indices...>, const Extents& ext, From... values) noexcept
{
    return (__is_index_in_extent(ext.extent(Indices), values) && ...);
}

template <class Extents, class... From>
CANN_ASC_STL_API constexpr bool __is_multidimensional_index_in(const Extents& ext, From... values) noexcept
{
    return __is_multidimensional_index_in_impl(make_index_sequence<Extents::rank()>(), ext, values...);
}

}  // namespace __mdspan_detail

// EBCO（空基类优化）压缩存储：按元素是否为空类型分别以成员/基类方式保存，
// 提供 __get<I>() 受检访问、约束化构造与逐元素交换；1/2/3 元素各一特化。
template <size_t Index, class Elem, bool = is_empty_v<Elem>>
struct __mdspan_ebco_impl {
    Elem elem_;

    template <class Elem2 = Elem, enable_if_t<is_default_constructible_v<Elem2>, int> = 0>
    CANN_ASC_STL_API constexpr __mdspan_ebco_impl() noexcept(is_nothrow_default_constructible_v<Elem2>) : elem_()
    {}

    template <class... Args, enable_if_t<sizeof...(Args) != 0 && is_constructible_v<Elem, Args...>, int> = 0>
    CANN_ASC_STL_API constexpr __mdspan_ebco_impl(Args&&... args) noexcept(is_nothrow_constructible_v<Elem, Args...>)
        : elem_(::asc::std::forward<Args>(args)...)
    {}

    CANN_ASC_STL_API constexpr Elem& __get() noexcept
    {
        return elem_;
    }
    CANN_ASC_STL_API constexpr const Elem& __get() const noexcept
    {
        return elem_;
    }
};

template <size_t Index, class Elem>
struct __mdspan_ebco_impl<Index, Elem, true> : Elem {
    template <class Elem2 = Elem, enable_if_t<is_default_constructible_v<Elem2>, int> = 0>
    CANN_ASC_STL_API constexpr __mdspan_ebco_impl() noexcept(is_nothrow_default_constructible_v<Elem2>) : Elem()
    {}

    template <class... Args, enable_if_t<sizeof...(Args) != 0 && is_constructible_v<Elem, Args...>, int> = 0>
    CANN_ASC_STL_API constexpr __mdspan_ebco_impl(Args&&... args) noexcept(is_nothrow_constructible_v<Elem, Args...>)
        : Elem(::asc::std::forward<Args>(args)...)
    {}

    CANN_ASC_STL_API constexpr Elem& __get() noexcept
    {
        return *static_cast<Elem*>(this);
    }
    CANN_ASC_STL_API constexpr const Elem& __get() const noexcept
    {
        return *static_cast<const Elem*>(this);
    }
};

template <class...>
struct __mdspan_ebco;

template <class Elem1>
struct __mdspan_ebco<Elem1> : __mdspan_ebco_impl<0, Elem1> {
    using base1 = __mdspan_ebco_impl<0, Elem1>;

    template <class Elem1_ = Elem1, enable_if_t<is_default_constructible_v<Elem1_>, int> = 0>
    CANN_ASC_STL_API constexpr __mdspan_ebco() noexcept(is_nothrow_default_constructible_v<Elem1_>) : base1()
    {}

    template <class... Args, enable_if_t<sizeof...(Args) != 0 && is_constructible_v<Elem1, Args...>, int> = 0>
    CANN_ASC_STL_API constexpr __mdspan_ebco(Args&&... args) noexcept(is_nothrow_constructible_v<Elem1, Args...>)
        : base1(::asc::std::forward<Args>(args)...)
    {}

    template <size_t Index, enable_if_t<(Index < 1), int> = 0>
    CANN_ASC_STL_API constexpr Elem1& __get() noexcept
    {
        return static_cast<base1*>(this)->__get();
    }

    template <size_t Index, enable_if_t<(Index < 1), int> = 0>
    CANN_ASC_STL_API constexpr const Elem1& __get() const noexcept
    {
        return static_cast<const base1*>(this)->__get();
    }

    CANN_ASC_STL_API friend constexpr void swap(__mdspan_ebco& x, __mdspan_ebco& y) noexcept(
        is_nothrow_swappable_v<Elem1>)
    {
        swap(x.__get<0>(), y.__get<0>());
    }
};

template <class Elem1, class Elem2>
struct __mdspan_ebco<Elem1, Elem2> : __mdspan_ebco_impl<0, Elem1>, __mdspan_ebco_impl<1, Elem2> {
    using base1 = __mdspan_ebco_impl<0, Elem1>;
    using base2 = __mdspan_ebco_impl<1, Elem2>;

    template <class Elem1_ = Elem1, class Elem2_ = Elem2,
        enable_if_t<is_default_constructible_v<Elem1_> && is_default_constructible_v<Elem2_>, int> = 0>
    CANN_ASC_STL_API constexpr __mdspan_ebco() noexcept(
        is_nothrow_default_constructible_v<Elem1_> && is_nothrow_default_constructible_v<Elem2_>)
        : base1(), base2()
    {}

    CANN_ASC_STL_API constexpr __mdspan_ebco(const __mdspan_ebco&) = default;
    CANN_ASC_STL_API constexpr __mdspan_ebco(__mdspan_ebco&&) = default;
    CANN_ASC_STL_API constexpr __mdspan_ebco& operator=(const __mdspan_ebco&) = default;
    CANN_ASC_STL_API constexpr __mdspan_ebco& operator=(__mdspan_ebco&&) = default;

    template <class Arg1>
    static constexpr bool __is_constructible_from_one_arg =
        is_constructible_v<Elem1, Arg1> && is_default_constructible_v<Elem2>;

    template <class Arg1>
    static constexpr bool __is_nothrow_constructible_from_one_arg =
        is_nothrow_constructible_v<Elem1, Arg1> && is_nothrow_default_constructible_v<Elem2>;

    // 单参转换构造的自引用排除约束（避免 C++20 概念求值上的循环依赖）。
    template <class Arg1,
        enable_if_t<!is_same_v<__mdspan_ebco, remove_cvref_t<Arg1>> && __is_constructible_from_one_arg<Arg1>, int> = 0>
    CANN_ASC_STL_API constexpr __mdspan_ebco(Arg1&& arg1) noexcept(__is_nothrow_constructible_from_one_arg<Arg1>)
        : base1(::asc::std::forward<Arg1>(arg1)), base2()
    {}

    template <class Arg1, class Arg2>
    static constexpr bool __is_constructible_from_two_args =
        is_constructible_v<Elem1, Arg1> && is_constructible_v<Elem2, Arg2>;

    template <class Arg1, class Arg2>
    static constexpr bool __is_nothrow_constructible_from_two_args =
        is_nothrow_constructible_v<Elem1, Arg1> && is_nothrow_constructible_v<Elem2, Arg2>;

    template <class Arg1, class Arg2, enable_if_t<__is_constructible_from_two_args<Arg1, Arg2>, int> = 0>
    CANN_ASC_STL_API constexpr __mdspan_ebco(Arg1&& arg1, Arg2&& arg2) noexcept(
        __is_nothrow_constructible_from_two_args<Arg1, Arg2>)
        : base1(::asc::std::forward<Arg1>(arg1)), base2(::asc::std::forward<Arg2>(arg2))
    {}

    template <size_t Index, enable_if_t<(Index < 2), int> = 0>
    CANN_ASC_STL_API constexpr decltype(auto) __get() noexcept
    {
        if constexpr (Index == 0) {
            return static_cast<base1*>(this)->__get();
        } else {  // if constexpr (Index == 1)
            return static_cast<base2*>(this)->__get();
        }
    }

    template <size_t Index, enable_if_t<(Index < 2), int> = 0>
    CANN_ASC_STL_API constexpr decltype(auto) __get() const noexcept
    {
        if constexpr (Index == 0) {
            return static_cast<const base1*>(this)->__get();
        } else {  // if constexpr (Index == 1)
            return static_cast<const base2*>(this)->__get();
        }
    }

    CANN_ASC_STL_API friend constexpr void swap(__mdspan_ebco& x, __mdspan_ebco& y) noexcept(
        is_nothrow_swappable_v<Elem1> && is_nothrow_swappable_v<Elem2>)
    {
        swap(x.__get<0>(), y.__get<0>());
        swap(x.__get<1>(), y.__get<1>());
    }
};

template <class Elem1, class Elem2, class Elem3>
struct __mdspan_ebco<Elem1, Elem2, Elem3>
    : __mdspan_ebco_impl<0, Elem1>, __mdspan_ebco_impl<1, Elem2>, __mdspan_ebco_impl<2, Elem3> {
    using base1 = __mdspan_ebco_impl<0, Elem1>;
    using base2 = __mdspan_ebco_impl<1, Elem2>;
    using base3 = __mdspan_ebco_impl<2, Elem3>;

    template <class Elem1_ = Elem1, class Elem2_ = Elem2, class Elem3_ = Elem3,
        enable_if_t<is_default_constructible_v<Elem1_> && is_default_constructible_v<Elem2_> &&
                is_default_constructible_v<Elem3_>,
            int> = 0>
    CANN_ASC_STL_API constexpr __mdspan_ebco() noexcept(is_nothrow_default_constructible_v<Elem1_> &&
        is_nothrow_default_constructible_v<Elem2_> && is_nothrow_default_constructible_v<Elem3_>)
        : base1(), base2(), base3()
    {}

    CANN_ASC_STL_API constexpr __mdspan_ebco(const __mdspan_ebco&) = default;
    CANN_ASC_STL_API constexpr __mdspan_ebco(__mdspan_ebco&&) = default;
    CANN_ASC_STL_API constexpr __mdspan_ebco& operator=(const __mdspan_ebco&) = default;
    CANN_ASC_STL_API constexpr __mdspan_ebco& operator=(__mdspan_ebco&&) = default;

    template <class Arg1>
    static constexpr bool __is_constructible_from_one_arg =
        is_constructible_v<Elem1, Arg1> && is_default_constructible_v<Elem2> && is_default_constructible_v<Elem3>;

    template <class Arg1>
    static constexpr bool __is_nothrow_constructible_from_one_arg = is_nothrow_constructible_v<Elem1, Arg1> &&
        is_nothrow_default_constructible_v<Elem2> && is_nothrow_default_constructible_v<Elem3>;

    template <class Arg1,
        enable_if_t<!is_same_v<__mdspan_ebco, remove_cvref_t<Arg1>> && __is_constructible_from_one_arg<Arg1>, int> = 0>
    CANN_ASC_STL_API constexpr __mdspan_ebco(Arg1&& arg1) noexcept(__is_nothrow_constructible_from_one_arg<Arg1>)
        : base1(::asc::std::forward<Arg1>(arg1)), base2(), base3()
    {}

    template <class Arg1, class Arg2>
    static constexpr bool __is_constructible_from_two_args =
        is_constructible_v<Elem1, Arg1> && is_constructible_v<Elem2, Arg2> && is_default_constructible_v<Elem3>;

    template <class Arg1, class Arg2>
    static constexpr bool __is_nothrow_constructible_from_two_args = is_nothrow_constructible_v<Elem1, Arg1> &&
        is_nothrow_constructible_v<Elem2, Arg2> && is_nothrow_default_constructible_v<Elem3>;

    template <class Arg1, class Arg2, enable_if_t<__is_constructible_from_two_args<Arg1, Arg2>, int> = 0>
    CANN_ASC_STL_API constexpr __mdspan_ebco(Arg1&& arg1, Arg2&& arg2) noexcept(
        __is_nothrow_constructible_from_two_args<Arg1, Arg2>)
        : base1(::asc::std::forward<Arg1>(arg1)), base2(::asc::std::forward<Arg2>(arg2)), base3()
    {}

    template <class Arg1, class Arg2, class Arg3>
    static constexpr bool __is_constructible_from_three_args =
        is_constructible_v<Elem1, Arg1> && is_constructible_v<Elem2, Arg2> && is_constructible_v<Elem3, Arg3>;

    template <class Arg1, class Arg2, class Arg3>
    static constexpr bool __is_nothrow_constructible_from_three_args = is_nothrow_constructible_v<Elem1, Arg1> &&
        is_nothrow_constructible_v<Elem2, Arg2> && is_nothrow_constructible_v<Elem3, Arg3>;

    template <class Arg1, class Arg2, class Arg3,
        enable_if_t<__is_constructible_from_three_args<Arg1, Arg2, Arg3>, int> = 0>
    CANN_ASC_STL_API constexpr __mdspan_ebco(Arg1&& arg1, Arg2&& arg2, Arg3&& arg3) noexcept(
        __is_nothrow_constructible_from_three_args<Arg1, Arg2, Arg3>)
        : base1(::asc::std::forward<Arg1>(arg1)),
          base2(::asc::std::forward<Arg2>(arg2)),
          base3(::asc::std::forward<Arg3>(arg3))
    {}

    template <size_t Index, enable_if_t<(Index < 3), int> = 0>
    CANN_ASC_STL_API constexpr decltype(auto) __get() noexcept
    {
        if constexpr (Index == 0) {
            return static_cast<base1*>(this)->__get();
        } else if constexpr (Index == 1) {
            return static_cast<base2*>(this)->__get();
        } else {  // if constexpr (Index == 2)
            return static_cast<base3*>(this)->__get();
        }
    }

    template <size_t Index, enable_if_t<(Index < 3), int> = 0>
    CANN_ASC_STL_API constexpr decltype(auto) __get() const noexcept
    {
        if constexpr (Index == 0) {
            return static_cast<const base1*>(this)->__get();
        } else if constexpr (Index == 1) {
            return static_cast<const base2*>(this)->__get();
        } else {  // if constexpr (Index == 2)
            return static_cast<const base3*>(this)->__get();
        }
    }

    CANN_ASC_STL_API friend constexpr void swap(__mdspan_ebco& x, __mdspan_ebco& y) noexcept(
        is_nothrow_swappable_v<Elem1> && is_nothrow_swappable_v<Elem2> && is_nothrow_swappable_v<Elem3>)
    {
        swap(x.__get<0>(), y.__get<0>());
        swap(x.__get<1>(), y.__get<1>());
        swap(x.__get<2>(), y.__get<2>());  // NOLINT(build/include_what_you_use)
    }
};

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___MDSPAN_EMPTY_BASE_H
