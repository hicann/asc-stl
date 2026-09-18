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

#ifndef CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_H
#define CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_H

#include <asc/std/detail/__config>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__asc/host_std_lib.h>
#include <asc/std/__memory/allocator_arg_t.h>
#include <asc/std/__tuple_dir/tuple_constraints.h>
#include <asc/std/__tuple_dir/tuple_element.h>
#include <asc/std/__tuple_dir/tuple_indices.h>
#include <asc/std/__tuple_dir/tuple_leaf.h>
#include <asc/std/__tuple_dir/tuple_size.h>
#include <asc/std/__tuple_dir/tuple_types.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/swap.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class... _Types>
class tuple;

template <class... _Types>
struct __tuple_impl {};

// Recursion terminator
template <>
struct __tuple_impl<> : private __tuple_impl_base {
    CANN_ASC_STL_API void swap(__tuple_impl&) noexcept
    {}
};

template <class _Head, class... _Tail>
struct __tuple_impl<_Head, _Tail...>
    : public __tuple_leaf<sizeof...(_Tail), _Head>, public __tuple_impl<_Tail...>, private __tuple_impl_base {
    using __leaf_t = __tuple_leaf<sizeof...(_Tail), _Head>;
    using __base_t = __tuple_impl<_Tail...>;

    CANN_ASC_STL_API constexpr __tuple_impl() : __leaf_t(), __base_t()
    {}

    template <class _HeadT, class... _TailTs>
    CANN_ASC_STL_API constexpr explicit __tuple_impl(_HeadT&& __h, _TailTs&&... __t)
        : __leaf_t(::asc::std::forward<_HeadT>(__h)), __base_t(::asc::std::forward<_TailTs>(__t)...)
    {}

    CANN_ASC_STL_API constexpr __tuple_impl(const __tuple_impl& __x)
        : __leaf_t(static_cast<const __leaf_t&>(__x)), __base_t(static_cast<const __base_t&>(__x))
    {}

    CANN_ASC_STL_API constexpr __tuple_impl(__tuple_impl&& __x)
        : __leaf_t(static_cast<__leaf_t&&>(__x)), __base_t(static_cast<__base_t&&>(__x))
    {}

    CANN_ASC_STL_API __tuple_impl& operator=(const __tuple_impl& __x)
    {
        static_cast<__leaf_t&>(*this) = static_cast<const __leaf_t&>(__x);
        static_cast<__base_t&>(*this) = static_cast<const __base_t&>(__x);
        return *this;
    }

    CANN_ASC_STL_API __tuple_impl& operator=(__tuple_impl&& __x)
    {
        static_cast<__leaf_t&>(*this) = static_cast<__leaf_t&&>(__x);
        static_cast<__base_t&>(*this) = static_cast<__base_t&&>(__x);
        return *this;
    }

    CANN_ASC_STL_API void swap(__tuple_impl& __y)
    {
        static_cast<__leaf_t&>(*this).swap(static_cast<__leaf_t&>(__y));
        static_cast<__base_t&>(*this).swap(static_cast<__base_t&>(__y));
    }
};

template <class... _Types>
class tuple : public __tuple_impl<_Types...> {
    using __base = __tuple_impl<_Types...>;
    using __types = __tuple_types<_Types...>;

public:
    CANN_ASC_STL_API constexpr tuple() : __base()
    {}

    CANN_ASC_STL_API constexpr tuple(const _Types&... __args) : __base(__args...)
    {}

    template <class... _UTypes, enable_if_t<(is_constructible_v<_Types, _UTypes> && ...), int> = 0>
    CANN_ASC_STL_API constexpr explicit tuple(_UTypes&&... __args) : __base(::asc::std::forward<_UTypes>(__args)...)
    {}

    // Cross-tuple converting constructors (as in std::tuple): tuple_cat and ranges
    // adaptation results rely on them when converting into a value tuple. The implicit
    // version requires every element to be implicitly convertible; the explicit version
    // only requires constructibility. Elements are forwarded positionally through the
    // index tag into __tuple_impl's expanding constructor.
    template <class... _UTypes,
        enable_if_t<(sizeof...(_UTypes) == sizeof...(_Types)) && (is_constructible_v<_Types, const _UTypes&> && ...) &&
                (is_convertible_v<const _UTypes&, _Types> && ...),
            int> = 0>
    CANN_ASC_STL_API constexpr tuple(const tuple<_UTypes...>& __other)
        : tuple(__make_tuple_indices_t<sizeof...(_UTypes)>{}, __other)
    {}

    template <class... _UTypes,
        enable_if_t<(sizeof...(_UTypes) == sizeof...(_Types)) && (is_constructible_v<_Types, const _UTypes&> && ...) &&
                (!(is_convertible_v<const _UTypes&, _Types> && ...)),
            int> = 0>
    CANN_ASC_STL_API constexpr explicit tuple(const tuple<_UTypes...>& __other)
        : tuple(__make_tuple_indices_t<sizeof...(_UTypes)>{}, __other)
    {}

    // 2026-09-16 根因修复（tuple 债）：原实现经 ::asc::std::get<_Idx>(__other) 展开。
    // 两个问题：(1) tuple 版 get 重载声明在本类之后，此处的限定调用不可见；
    // (2) 参考元素（如 forward_as_tuple 形成的 tuple<int&&>）在 const 源上经 get 取值
    // 不能绑定右值引用。改为按叶（__tuple_leaf，逻辑下标倒序存储）直接取值展开，
    // 与 __tuple_impl 的逐叶构造同构；is_constructible 约束保证不可行组合被 SFINAE 排除。
    template <size_t... _Idx, class... _UTypes>
    CANN_ASC_STL_API constexpr tuple(__tuple_indices<_Idx...>, const tuple<_UTypes...>& __other)
        : __base(static_cast<const __tuple_leaf<(sizeof...(_UTypes) - _Idx - 1), _UTypes>&>(__other).__get()...)
    {}

    CANN_ASC_STL_API constexpr tuple(const tuple& __x) : __base(static_cast<const __base&>(__x))
    {}

    CANN_ASC_STL_API constexpr tuple(tuple&& __x) : __base(static_cast<__base&&>(__x))
    {}

    CANN_ASC_STL_API tuple& operator=(const tuple& __x)
    {
        __base::operator=(static_cast<const __base&>(__x));
        return *this;
    }

    CANN_ASC_STL_API tuple& operator=(tuple&& __x)
    {
        __base::operator=(static_cast<__base&&>(__x));
        return *this;
    }

    CANN_ASC_STL_API void swap(tuple& __y)
    {
        __base::swap(static_cast<__base&>(__y));
    }
};

// Explicit specialization for the empty tuple (mirrors the reference approach): in
// the primary template, tuple() and tuple(const _Types&...) collapse to the same
// signature for an empty pack — an illegal redeclaration of non-template members
// that hard-errors as soon as tuple<> is instantiated. The primary template stays
// unchanged; the empty tuple uses this specialization.
template <>
class tuple<> {  // NOLINT(build/include_what_you_use)
public:
    CANN_ASC_STL_API constexpr tuple() noexcept
    {}

    CANN_ASC_STL_API constexpr tuple(const tuple&) noexcept = default;
    CANN_ASC_STL_API constexpr tuple(tuple&&) noexcept = default;
    CANN_ASC_STL_API tuple& operator=(const tuple&) noexcept = default;
    CANN_ASC_STL_API tuple& operator=(tuple&&) noexcept = default;

    CANN_ASC_STL_API void swap(tuple&) noexcept
    {}
};

template <class... _Types>
struct tuple_size<::asc::std::tuple<_Types...>> : integral_constant<size_t, sizeof...(_Types)> {};

template <size_t _Ip, class... _Types>
struct tuple_element<_Ip, ::asc::std::tuple<_Types...>> {
    using type = tuple_element_t<_Ip, __tuple_types<_Types...>>;
};

template <size_t _Ip, class... _Ts>
CANN_ASC_STL_API constexpr tuple_element_t<_Ip, __tuple_types<_Ts...>>& get(::asc::std::tuple<_Ts...>& __t) noexcept
{
    using __leaf_t = __tuple_leaf<(sizeof...(_Ts) - _Ip - 1), tuple_element_t<_Ip, __tuple_types<_Ts...>>>;
    return static_cast<__leaf_t&>(__t).__get();
}

template <size_t _Ip, class... _Ts>
CANN_ASC_STL_API constexpr const tuple_element_t<_Ip, __tuple_types<_Ts...>>& get(
    const ::asc::std::tuple<_Ts...>& __t) noexcept
{
    using __leaf_t = __tuple_leaf<(sizeof...(_Ts) - _Ip - 1), tuple_element_t<_Ip, __tuple_types<_Ts...>>>;
    return static_cast<const __leaf_t&>(__t).__get();
}

template <size_t _Ip, class... _Ts>
[[nodiscard]] CANN_ASC_STL_API constexpr tuple_element_t<_Ip, __tuple_types<_Ts...>>&& get(
    ::asc::std::tuple<_Ts...>&& __t) noexcept
{
    using __leaf_t = __tuple_leaf<(sizeof...(_Ts) - _Ip - 1), tuple_element_t<_Ip, __tuple_types<_Ts...>>>;
    return ::asc::std::move(static_cast<__leaf_t&&>(__t).__get());  // NOLINT(build/include_what_you_use)
}

template <class... _Ts>
CANN_ASC_STL_API void swap(
    ::asc::std::tuple<_Ts...>& __x, ::asc::std::tuple<_Ts...>& __y)  // NOLINT(build/include_what_you_use)
{
    __x.swap(__y);
}

// std::tuple tuple-protocol bridging (host std lib only). Without this
// bridge, tuple-like detection over std::tuple (e.g. __complex/traits.h's
// __is_complex_compatible_tuple_like) wrongly evaluates false on hosted
// builds. Device/freestanding builds have no std::tuple and skip the block.
#if CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()
template <class... _Types>
struct tuple_size<::std::tuple<_Types...>> : integral_constant<size_t, sizeof...(_Types)> {};

template <size_t _Ip, class... _Types>
struct tuple_element<_Ip, ::std::tuple<_Types...>> {  // NOLINT
    using type = tuple_element_t<_Ip, __tuple_types<_Types...>>;
};
#endif  // CANN_ASC_STL_DETAIL_HAS_HOST_STD_LIB()

CANN_ASC_STL_END_NAMESPACE

// tuple protocol for asc::std::tuple (structured-binding bridge into
// namespace std).
namespace std {

template <class... _Types>
struct tuple_size<::asc::std::tuple<_Types...>> : ::asc::std::integral_constant<::asc::std::size_t, sizeof...(_Types)> {
};

template <::asc::std::size_t _Ip, class... _Types>
struct tuple_element<_Ip, ::asc::std::tuple<_Types...>> {
    using type = ::asc::std::tuple_element_t<_Ip, ::asc::std::__tuple_types<_Types...>>;
};

}  // namespace std

#endif  // CANN_ASC_STL_STD_DETAIL_TUPLE_DIR_TUPLE_H
