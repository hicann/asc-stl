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
#ifndef CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_H
#define CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_H

#include <asc/__config>

#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)
#pragma GCC system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_CLANG)
#pragma clang system_header
#elif defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_MSVC)
#pragma system_header
#endif

#include <asc/__detail/attributes.h>
#include <asc/std/__cstddef/types.h>
#include <asc/std/__fwd/get.h>
#include <asc/std/__fwd/tuple.h>
#include <asc/std/__memory/allocator_arg_t.h>
#include <asc/std/__tuple/tuple_constraints.h>
#include <asc/std/__tuple/tuple_element.h>
#include <asc/std/__tuple/tuple_indices.h>
#include <asc/std/__tuple/tuple_leaf.h>
#include <asc/std/__tuple/tuple_size.h>
#include <asc/std/__tuple/tuple_types.h>
#include <asc/std/__type_traits/common_reference.h>
#include <asc/std/__type_traits/common_type.h>
#include <asc/std/__type_traits/integral_constant.h>
#include <asc/std/__type_traits/is_nothrow_assignable.h>
#include <asc/std/__type_traits/is_nothrow_constructible.h>
#include <asc/std/__type_traits/is_nothrow_default_constructible.h>
#include <asc/std/__type_traits/is_same.h>
#include <asc/std/__type_traits/remove_cvref.h>
#include <asc/std/__utility/forward.h>
#include <asc/std/__utility/move.h>
#include <asc/std/__utility/pair.h>
#include <asc/std/__utility/swap.h>

CANN_ASC_STL_BEGIN_NAMESPACE

template <class Indices, class... Types>
class __tuple_impl;
template <size_t... Indices, class... Types>
class __tuple_impl<__tuple_indices<Indices...>, Types...> : public __tuple_leaf<Indices, Types>... {
public:
    CANN_ASC_STL_API constexpr __tuple_impl() = default;
    template <class... Values, enable_if_t<sizeof...(Values) == sizeof...(Types), int> = 0>
    CANN_ASC_STL_API constexpr explicit __tuple_impl(Values&&... values)
        : __tuple_leaf<Indices, Types>(::asc::std::forward<Values>(values))...
    {}
    template <size_t Index>
    CANN_ASC_STL_API constexpr tuple_element_t<Index, tuple<Types...>>& get() noexcept
    {
        using leaf = __tuple_leaf<Index, tuple_element_t<Index, tuple<Types...>>>;
        return static_cast<leaf&>(*this).get();
    }
    template <size_t Index>
    CANN_ASC_STL_API constexpr const tuple_element_t<Index, tuple<Types...>>& get() const noexcept
    {
        using leaf = __tuple_leaf<Index, tuple_element_t<Index, tuple<Types...>>>;
        return static_cast<const leaf&>(*this).get();
    }
    CANN_ASC_STL_API constexpr void swap(__tuple_impl& other) noexcept(
        (noexcept(static_cast<__tuple_leaf<Indices, Types>&>(*this).swap(
             static_cast<__tuple_leaf<Indices, Types>&>(other))) &&
            ...))
    {
        (static_cast<__tuple_leaf<Indices, Types>&>(*this).swap(static_cast<__tuple_leaf<Indices, Types>&>(other)),
            ...);
    }
};
template <class... Types>
class tuple : public __tuple_impl<__make_tuple_indices_t<sizeof...(Types)>, Types...> {
    using base = __tuple_impl<__make_tuple_indices_t<sizeof...(Types)>, Types...>;

public:
    CANN_ASC_STL_API constexpr tuple() = default;
    tuple(const tuple&) = default;
    tuple(tuple&&) = default;
    CANN_ASC_STL_API constexpr tuple& operator=(const tuple& other)
    {
        __assign(other, __make_tuple_indices_t<sizeof...(Types)>{});
        return *this;
    }
    CANN_ASC_STL_API constexpr tuple& operator=(tuple&& other)
    {
        __assign(::asc::std::move(other), __make_tuple_indices_t<sizeof...(Types)>{});
        return *this;
    }
    template <class... Other, enable_if_t<sizeof...(Other) == sizeof...(Types), int> = 0>
    CANN_ASC_STL_API constexpr tuple& operator=(const tuple<Other...>& other)
    {
        __assign(other, __make_tuple_indices_t<sizeof...(Types)>{});
        return *this;
    }
    template <class... Other, enable_if_t<sizeof...(Other) == sizeof...(Types), int> = 0>
    CANN_ASC_STL_API constexpr tuple& operator=(tuple<Other...>&& other)
    {
        __assign(::asc::std::move(other), __make_tuple_indices_t<sizeof...(Types)>{});
        return *this;
    }
    template <class... Values, enable_if_t<sizeof...(Values) == sizeof...(Types), int> = 0>
    CANN_ASC_STL_API constexpr explicit tuple(Values&&... values) : base(::asc::std::forward<Values>(values)...)
    {}
    template <size_t Index>
    CANN_ASC_STL_API constexpr decltype(auto) __get() & noexcept
    {
        return base::template get<Index>();
    }
    template <size_t Index>
    CANN_ASC_STL_API constexpr decltype(auto) __get() const& noexcept
    {
        return base::template get<Index>();
    }
    template <size_t Index>
    CANN_ASC_STL_API constexpr decltype(auto) __get() && noexcept
    {
        return ::asc::std::move(base::template get<Index>());
    }
    template <size_t Index>
    CANN_ASC_STL_API constexpr decltype(auto) __get() const&& noexcept
    {
        return ::asc::std::move(base::template get<Index>());
    }
    CANN_ASC_STL_API constexpr void swap(tuple& other) noexcept(noexcept(base::swap(other)))
    {
        base::swap(other);
    }

private:
    template <class Other, size_t... Indices>
    CANN_ASC_STL_API constexpr void __assign(Other&& other, __tuple_indices<Indices...>)
    {
        ((this->template __get<Indices>() =                                 // NOLINT(build/include_what_you_use)
             ::asc::std::forward<Other>(other).template __get<Indices>()),  // NOLINT(build/include_what_you_use)
            ...);
    }
};
template <class... Types>
struct tuple_size<tuple<Types...>> : integral_constant<size_t, sizeof...(Types)> {};
template <size_t Index, class Head, class... Tail>
struct tuple_element<Index, tuple<Head, Tail...>> : tuple_element<Index - 1, tuple<Tail...>> {};
template <class Head, class... Tail>
struct tuple_element<0, tuple<Head, Tail...>> {
    using type = Head;
};
template <size_t Index>
struct tuple_element<Index, tuple<>> {};
template <size_t Index, class Left, class Right>
CANN_ASC_STL_API constexpr bool __tuple_equal(const Left& left, const Right& right)
{
    if constexpr (Index == tuple_size<Left>::value) {
        return true;
    } else {
        return left.template __get<Index>() == right.template __get<Index>() && __tuple_equal<Index + 1>(left, right);
    }
}
template <size_t Index, class Left, class Right>
CANN_ASC_STL_API constexpr bool __tuple_less(const Left& left, const Right& right)
{
    if constexpr (Index == tuple_size<Left>::value) {
        return false;
    } else if (left.template __get<Index>() < right.template __get<Index>()) {
        return true;
    } else if (right.template __get<Index>() < left.template __get<Index>()) {
        return false;
    } else {
        return __tuple_less<Index + 1>(left, right);
    }
}
template <class... Left, class... Right>
CANN_ASC_STL_API constexpr bool operator==(const tuple<Left...>& left, const tuple<Right...>& right)
{
    static_assert(sizeof...(Left) == sizeof...(Right), "tuple sizes must match");
    return __tuple_equal<0>(left, right);
}
template <class... Left, class... Right>
CANN_ASC_STL_API constexpr bool operator!=(const tuple<Left...>& left, const tuple<Right...>& right)
{
    return !(left == right);
}
template <class... Left, class... Right>
CANN_ASC_STL_API constexpr bool operator<(const tuple<Left...>& left, const tuple<Right...>& right)
{
    static_assert(sizeof...(Left) == sizeof...(Right), "tuple sizes must match");
    return __tuple_less<0>(left, right);
}
template <class... Left, class... Right>
CANN_ASC_STL_API constexpr bool operator>(const tuple<Left...>& left, const tuple<Right...>& right)
{
    return right < left;
}
template <class... Left, class... Right>
CANN_ASC_STL_API constexpr bool operator<=(const tuple<Left...>& left, const tuple<Right...>& right)
{
    return !(right < left);
}
template <class... Left, class... Right>
CANN_ASC_STL_API constexpr bool operator>=(const tuple<Left...>& left, const tuple<Right...>& right)
{
    return !(left < right);
}
template <class... Types>
CANN_ASC_STL_API constexpr void swap(                             // NOLINT(build/include_what_you_use)
    tuple<Types...>& left,                                        // NOLINT(build/include_what_you_use)
    tuple<Types...>& right) noexcept(noexcept(left.swap(right)))  // NOLINT(build/include_what_you_use)
{
    left.swap(right);  // NOLINT(build/include_what_you_use)
}

CANN_ASC_STL_END_NAMESPACE

#endif  // CANN_ASC_STL_ASC_STD___TUPLE_TUPLE_H
